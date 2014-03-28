#include "stdafx.h"
#include "ContextMenuHandler.h"

#include <Strsafe.h>
#include <propkey.h>
#include <Pathcch.h>

using namespace std;

#define IS_FLAG_SET(val, flag) ((val & flag) == (flag))
#define IS_FLAG_CLEAR(val, flag) ((val & flag) == 0)

CContextMenuHandler::CContextMenuHandler() : _fShowMenuItem(false)
{
}

CContextMenuHandler::~CContextMenuHandler()
{
}

IFACEMETHODIMP CContextMenuHandler::Initialize(PCIDLIST_ABSOLUTE /*pidlFolder*/, IDataObject *pdtobj, HKEY /*hkeyProgID*/)
{
    this->_fShowMenuItem = false;

    HRESULT hr = EnsureOneDriveFolderCached();
    if (SUCCEEDED(hr))
    {
        CComPtr<IShellItemArray> spShellItemArray;
        hr = SHCreateShellItemArrayFromDataObject(pdtobj, IID_PPV_ARGS(&spShellItemArray));
        if (SUCCEEDED(hr))
        {
            DWORD dwNumItems;
            hr = spShellItemArray->GetCount(&dwNumItems);
            if (SUCCEEDED(hr) && dwNumItems == 1)
            {
                CComPtr<IShellItem> spShellItem;
                hr = spShellItemArray->GetItemAt(0, &spShellItem);
                if (SUCCEEDED(hr))
                {
                    CComHeapPtr<wchar_t> spszDisplayName;
                    hr = spShellItem->GetDisplayName(SIGDN_DESKTOPABSOLUTEPARSING, &spszDisplayName);
                    if (SUCCEEDED(hr))
                    {
                        SFGAOF sfgaoAttributes;
                        hr = spShellItem->GetAttributes(SFGAO_STREAM | SFGAO_FOLDER, &sfgaoAttributes);

                        // Some dastardly shell items, like .zips, may have SFGAO_FOLDER set.
                        // We use the SFGAO_STREAM to sniff those out.
                        if (SUCCEEDED(hr) &&
                            (!IS_FLAG_SET(sfgaoAttributes, SFGAO_FOLDER) ||
                            (IS_FLAG_SET(sfgaoAttributes, SFGAO_FOLDER) && IS_FLAG_SET(sfgaoAttributes, SFGAO_STREAM))))
                        {
                            size_t cchOneDriveFolderLength = wcslen(this->_spszCachedOneDriveFolder);
                            size_t lengthOfTargetName = wcslen(spszDisplayName);

                            if (lengthOfTargetName > cchOneDriveFolderLength && CompareStringOrdinal(
                                this->_spszCachedOneDriveFolder, cchOneDriveFolderLength, spszDisplayName, cchOneDriveFolderLength, TRUE) == CSTR_EQUAL)
                            {
                                this->_spszTargetPath = spszDisplayName;
                                this->_fShowMenuItem = true;
                            }
                            else
                            {
                                hr = S_FALSE;
                            }
                        }
                    }
                }
            }
        }
    }

    return hr;
}

IFACEMETHODIMP CContextMenuHandler::GetCommandString(UINT_PTR /*idCmd*/, UINT /*uFlags*/, UINT * /*pwReserved*/, LPSTR /*pszName*/, UINT /*cchMax*/)
{
    return E_NOTIMPL;
}

IFACEMETHODIMP CContextMenuHandler::QueryContextMenu(HMENU hMenu, UINT indexMenu, UINT idCmdFirst, UINT /*idCmdLast*/, UINT uFlags)
{
    HRESULT hr = S_OK;

    if (IS_FLAG_CLEAR(uFlags, CMF_DEFAULTONLY) && this->_fShowMenuItem)
    {
        UINT uFlags = MF_STRING | MF_BYPOSITION;

        if (InsertMenu(hMenu, indexMenu, uFlags, idCmdFirst, L"Copy public OneDrive &link"))
        {
            // Quirky return semantics
            // http://msdn.microsoft.com/en-us/library/windows/desktop/bb776097.aspx
            hr = MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_NULL, 1);
        }
        else
        {
            hr = HRESULT_FROM_WIN32(GetLastError());
        }
    }

    return hr;
}

IFACEMETHODIMP CContextMenuHandler::InvokeCommand(LPCMINVOKECOMMANDINFO /*pici*/)
{
    HRESULT hr = E_FAIL;

    if (OpenClipboard(nullptr) && EmptyClipboard() && CloseClipboard())
    {
        CComPtr<IShellItem2> spShellItem;
        hr = SHCreateItemFromParsingName(this->_spszTargetPath, NULL, IID_PPV_ARGS(&spShellItem));
        if (SUCCEEDED(hr))
        {
            CComPtr<IPropertyStore> spPropertyStore;
            hr = spShellItem->GetPropertyStore(GPS_EXTRINSICPROPERTIES, IID_PPV_ARGS(&spPropertyStore));
            if (SUCCEEDED(hr))
            {
                PROPVARIANT pvFileIdentifier;
                PropVariantInit(&pvFileIdentifier);
                hr = spPropertyStore->GetValue(PKEY_StorageProviderFileIdentifier, &pvFileIdentifier);
                if (SUCCEEDED(hr))
                {
                    hr = HandoffToService(pvFileIdentifier.pwszVal);
                    PropVariantClear(&pvFileIdentifier);
                }
            }
        }
    }

    return hr;
}

bool CContextMenuHandler::IsServiceRunning()
{
    bool fRunning = false;

    HANDLE hMutex = OpenMutex(SYNCHRONIZE, FALSE, L"ExtensionsForOneDrive_Mutex");
    if (hMutex != nullptr)
    {
        fRunning = true;
        CloseHandle(hMutex);
    }

    return fRunning;
}

HRESULT CContextMenuHandler::HandoffToService(LPCWSTR pwszFileIdentifier)
{
    size_t cbFileIdentifier;
    HRESULT hr = StringCbLength(pwszFileIdentifier, sizeof(wchar_t) * MAX_PATH, &cbFileIdentifier);
    if (SUCCEEDED(hr))
    {
        hr = HRESULT_FROM_WIN32(RegSetKeyValue(HKEY_CURRENT_USER, L"Software\\Rafael\\ExtensionsForOneDrive", L"Drop", REG_SZ, pwszFileIdentifier, cbFileIdentifier));
        if (SUCCEEDED(hr))
        {
            if (!CContextMenuHandler::IsServiceRunning())
            {
                LPTHREAD_START_ROUTINE lpThreadStart = [](LPVOID) -> DWORD
                {
                    HRESULT hr = CContextMenuHandler::StartHelperService();
                    if (SUCCEEDED(hr))
                    {
                        hr = HRESULT_FROM_WIN32(ERROR_TIMEOUT);
                        for (int i = 0; i < 10; i++)
                        {
                            if (CContextMenuHandler::IsServiceRunning())
                            {
                                hr = SignalDataAvailable();
                                break;
                            }
                            Sleep(1000);
                        }
                    }
                    return 0;
                };

                if (SHCreateThread(lpThreadStart, nullptr, 0, nullptr))
                {
                    hr = S_OK;
                }
                else
                {
                    hr = HRESULT_FROM_WIN32(GetLastError());
                }
            }
            else
            {
                hr = SignalDataAvailable();
            }
        }
    }

    return hr;
}

HRESULT CContextMenuHandler::StartHelperService()
{
    HRESULT hr = S_OK;

    if (!IsServiceRunning())
    {
        CComHeapPtr<wchar_t> spszServicePath;
        hr = GetServiceExecutablePath(&spszServicePath);
        if (SUCCEEDED(hr))
        {
            HINSTANCE hInstance = ShellExecuteW(nullptr, L"open", spszServicePath, nullptr, nullptr, SW_SHOWDEFAULT);
            if (reinterpret_cast<int>(hInstance) <= 32)
            {
                hr = E_FAIL;
            }
        }
    }

    return hr;
}

HRESULT CContextMenuHandler::SignalDataAvailable()
{
    HRESULT hr = E_FAIL;

    HANDLE hEvent = OpenEvent(EVENT_MODIFY_STATE, FALSE, L"ExtensionsForOneDrive_DataAvailableEvent");
    if (hEvent != NULL)
    {
        if (SetEvent(hEvent) == TRUE)
        {
            hr = S_OK;
        }

        CloseHandle(hEvent);
    }
    else
    {
        hr = HRESULT_FROM_WIN32(GetLastError());
    }

    return hr;
}

HRESULT CContextMenuHandler::GetServiceExecutablePath(LPWSTR* ppszServiceExecutablePath)
{
    *ppszServiceExecutablePath = nullptr;

    HKEY hkInproc;

    HRESULT    hr = HRESULT_FROM_WIN32(RegOpenKey(HKEY_CLASSES_ROOT, L"CLSID\\{98BEF305-AD58-410A-9864-93ED872F8549}\\InprocServer32", &hkInproc));
    if (SUCCEEDED(hr))
    {
        wchar_t szLibPath[MAX_PATH];
        long cchLibPath = ARRAYSIZE(szLibPath);
        long cbLibPath = sizeof(szLibPath[0]) * cchLibPath;

        hr = HRESULT_FROM_WIN32(RegQueryValueW(hkInproc, nullptr, szLibPath, &cbLibPath));
        if (SUCCEEDED(hr))
        {
            hr = PathCchRemoveFileSpec(szLibPath, cchLibPath);
            if (SUCCEEDED(hr))
            {
                hr = PathCchAppend(szLibPath, ARRAYSIZE(szLibPath), L"ExtensionsForOneDrive.Service.exe");
                if (SUCCEEDED(hr))
                {
                    hr = SHStrDup(szLibPath, ppszServiceExecutablePath);
                }
            }
        }
    }

    return hr;
}