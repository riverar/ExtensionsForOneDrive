#include "stdafx.h"
#include "resource.h"
#include "shellext_i.h"
#include "dllmain.h"

CShellExtModule _AtlModule;

extern "C" BOOL WINAPI DllMain(HINSTANCE /*hInstance*/, DWORD dwReason, LPVOID lpReserved)
{
	return _AtlModule.DllMain(dwReason, lpReserved); 
}