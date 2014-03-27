#include "stdafx.h"

#include <string>
#include <propkey.h>
#include <KnownFolders.h>

#include "OverlayHandler.h"

using namespace std;

COverlayHandler::COverlayHandler()
{
}

HRESULT COverlayHandler::GetOverlayInfo(PWSTR pwszIconFile, int cchMax, int* pIndex, DWORD* pdwFlags)
{
    *pdwFlags = ISIOI_ICONFILE;
    HRESULT hr = S_OK;

    int cbCopied = GetModuleFileName(_AtlBaseModule.GetModuleInstance(), pwszIconFile, cchMax);
    if (cbCopied <= 0)
    {
        hr = HRESULT_FROM_WIN32(GetLastError());
    }

    return hr;
}

HRESULT COverlayHandler::GetPriority(int* pPriority)
{
    *pPriority = 0;

    return S_OK;
}

HRESULT COverlayHandler::IsMemberOf(PCWSTR pwszPath, DWORD dwAttrib)
{
    HRESULT hr = EnsureOneDriveFolderCached();
    if (SUCCEEDED(hr))
    {
        hr = S_FALSE;

        wstring spszPath(pwszPath);
        if (spszPath.length() > 0 &&
            spszPath.find(this->_spszCachedOneDriveFolder) != string::npos &&
            CompareStringOrdinal(pwszPath, -1, this->_spszCachedOneDriveFolder, -1, TRUE) != CSTR_EQUAL)
        {
            CComPtr<IShellItem2> spShellItem;
            hr = SHCreateItemFromParsingName(pwszPath, nullptr, IID_PPV_ARGS(&spShellItem));
            if (SUCCEEDED(hr))
            {
                ULONG ulStatus = 0;
                hr = spShellItem->GetUInt32(PKEY_FilePlaceholderStatus, &ulStatus);
                if (SUCCEEDED(hr))
                {
                    if (ulStatus == 7)
                    {
                        hr = S_OK;
                    }
                    else
                    {
                        hr = S_FALSE;
                    }
                }
            }
        }
    }

    if (FAILED(hr))
    {
        hr = E_FAIL;
    }
    
    // S_OK        The icon overlay should be displayed.
    // S_FALSE    The icon overlay should not be displayed.
    // E_FAIL    The operation failed.

    return hr;
}