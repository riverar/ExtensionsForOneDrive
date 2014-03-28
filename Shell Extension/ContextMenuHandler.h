#pragma once

#include <Shlobj.h>

#include "resource.h"
#include "shellext_i.h"
#include "ExtensionBase.h"

using namespace std;
using namespace ATL;

class ATL_NO_VTABLE CContextMenuHandler :
    public CExtensionBase,
    public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<CContextMenuHandler, &CLSID_ContextMenuHandler>,
    public IShellExtInit,
    public IContextMenu
{
public:
    CContextMenuHandler();
    ~CContextMenuHandler();

    DECLARE_REGISTRY_RESOURCEID(IDR_CONTEXTMENUHANDLER)

    DECLARE_NOT_AGGREGATABLE(CContextMenuHandler)

    BEGIN_COM_MAP(CContextMenuHandler)
        COM_INTERFACE_ENTRY(IShellExtInit)
        COM_INTERFACE_ENTRY(IContextMenu)
    END_COM_MAP()

    DECLARE_PROTECT_FINAL_CONSTRUCT()

    // IShellExtInit
    IFACEMETHODIMP Initialize(PCIDLIST_ABSOLUTE pidlFolder, IDataObject *pdtobj, HKEY hkeyProgID);
    
    // IContextMenu
    IFACEMETHODIMP GetCommandString(UINT_PTR idCmd, UINT uFlags, UINT *pwReserved, LPSTR pszName, UINT cchMax);
    IFACEMETHODIMP QueryContextMenu(HMENU hmenu, UINT indexMenu, UINT idCmdFirst, UINT idCmdLast, UINT uFlags);
    IFACEMETHODIMP InvokeCommand(LPCMINVOKECOMMANDINFO pici);

private:
    HRESULT HandoffToService(LPCWSTR pwszIdentifier);

    static HRESULT GetServiceExecutablePath(LPWSTR* ppszServiceExecutablePath);
    static bool IsServiceRunning();
    static HRESULT StartHelperService();
    static HRESULT SignalDataAvailable();

    bool _fShowMenuItem;
    CComHeapPtr<wchar_t> _spszTargetPath;
};

OBJECT_ENTRY_AUTO(__uuidof(ContextMenuHandler), CContextMenuHandler)
