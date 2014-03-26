#pragma once

#include "resource.h"

#include <Shlobj.h>
#include <string>

#include "shellext_i.h"
#include "ExtensionBase.h"

using namespace std;
using namespace ATL;

class ATL_NO_VTABLE COverlayHandler :
	public CExtensionBase,
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<COverlayHandler, &CLSID_OverlayHandler>,
	public IShellIconOverlayIdentifier
{
public:
	COverlayHandler();

	DECLARE_REGISTRY_RESOURCEID(IDR_OVERLAYHANDLER)

	DECLARE_NOT_AGGREGATABLE(COverlayHandler)

	BEGIN_COM_MAP(COverlayHandler)
		COM_INTERFACE_ENTRY(IShellIconOverlayIdentifier)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	// IShellIconOverlayIdentifier
	HRESULT __stdcall GetOverlayInfo(PWSTR pwszIconFile, int cchMax, int* pIndex, DWORD* pdwFlags);
	HRESULT __stdcall GetPriority(int* pPriority);
	HRESULT __stdcall IsMemberOf(PCWSTR pwszPath, DWORD dwAttrib);
	
private:
	HRESULT GetOneDriveUserFolder(LPWSTR* ppszOneDriveFolder);
};

OBJECT_ENTRY_AUTO(__uuidof(OverlayHandler), COverlayHandler)