#pragma once

using namespace ATL;

class CExtensionBase
{
public:
    CExtensionBase()
    {
        InitializeCriticalSection(&this->_cs);
    }

    ~CExtensionBase()
    {
        DeleteCriticalSection(&this->_cs);
    }

    HRESULT EnsureOneDriveFolderCached()
    {
        HRESULT hr = S_OK;

        if (this->_spszCachedOneDriveFolder == nullptr)
        {
            CComHeapPtr<wchar_t> spszLocatedOneDriveFolder;

            hr = SHGetKnownFolderPath(FOLDERID_SkyDrive, KF_FLAG_DONT_VERIFY | KF_FLAG_NO_ALIAS, nullptr, &spszLocatedOneDriveFolder);
            if (SUCCEEDED(hr))
            {
                EnterCriticalSection(&this->_cs);

                if (this->_spszCachedOneDriveFolder == nullptr)
                {
                    this->_spszCachedOneDriveFolder = spszLocatedOneDriveFolder;
                }

                LeaveCriticalSection(&this->_cs);
            }
        }

        return hr;
    }

    CComHeapPtr<wchar_t> _spszCachedOneDriveFolder;
    CRITICAL_SECTION _cs;
};