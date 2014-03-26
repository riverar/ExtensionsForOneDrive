

/* this ALWAYS GENERATED file contains the proxy stub code */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Wed Mar 26 00:30:35 2014
 */
/* Compiler settings for shellext.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#if defined(_M_AMD64)


#pragma warning( disable: 4049 )  /* more than 64k source lines */
#if _MSC_VER >= 1200
#pragma warning(push)
#endif

#pragma warning( disable: 4211 )  /* redefine extern to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma warning( disable: 4024 )  /* array to pointer mapping*/
#pragma warning( disable: 4152 )  /* function/data pointer conversion in expression */

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 475
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif /* __RPCPROXY_H_VERSION__ */


#include "shellext_i.h"

#define TYPE_FORMAT_STRING_SIZE   3                                 
#define PROC_FORMAT_STRING_SIZE   1                                 
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   0            

typedef struct _shellext_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } shellext_MIDL_TYPE_FORMAT_STRING;

typedef struct _shellext_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } shellext_MIDL_PROC_FORMAT_STRING;

typedef struct _shellext_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } shellext_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const shellext_MIDL_TYPE_FORMAT_STRING shellext__MIDL_TypeFormatString;
extern const shellext_MIDL_PROC_FORMAT_STRING shellext__MIDL_ProcFormatString;
extern const shellext_MIDL_EXPR_FORMAT_STRING shellext__MIDL_ExprFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IOverlayHandler_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IOverlayHandler_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IContextMenuHandler_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IContextMenuHandler_ProxyInfo;



#if !defined(__RPC_WIN64__)
#error  Invalid build platform for this stub.
#endif

static const shellext_MIDL_PROC_FORMAT_STRING shellext__MIDL_ProcFormatString =
    {
        0,
        {

			0x0
        }
    };

static const shellext_MIDL_TYPE_FORMAT_STRING shellext__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */

			0x0
        }
    };


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IOverlayHandler, ver. 0.0,
   GUID={0xE9BF8D5F,0x8F02,0x479E,{0x94,0xC5,0x75,0xD2,0x6A,0x20,0x4F,0xFC}} */

#pragma code_seg(".orpc")
static const unsigned short IOverlayHandler_FormatStringOffsetTable[] =
    {
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IOverlayHandler_ProxyInfo =
    {
    &Object_StubDesc,
    shellext__MIDL_ProcFormatString.Format,
    &IOverlayHandler_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IOverlayHandler_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    shellext__MIDL_ProcFormatString.Format,
    &IOverlayHandler_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(3) _IOverlayHandlerProxyVtbl = 
{
    0,
    &IID_IOverlayHandler,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy
};

const CInterfaceStubVtbl _IOverlayHandlerStubVtbl =
{
    &IID_IOverlayHandler,
    &IOverlayHandler_ServerInfo,
    3,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IContextMenuHandler, ver. 0.0,
   GUID={0xE58341FD,0x11BA,0x4150,{0x92,0xAB,0xF8,0x02,0x03,0xBF,0x58,0xFC}} */

#pragma code_seg(".orpc")
static const unsigned short IContextMenuHandler_FormatStringOffsetTable[] =
    {
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IContextMenuHandler_ProxyInfo =
    {
    &Object_StubDesc,
    shellext__MIDL_ProcFormatString.Format,
    &IContextMenuHandler_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IContextMenuHandler_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    shellext__MIDL_ProcFormatString.Format,
    &IContextMenuHandler_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(3) _IContextMenuHandlerProxyVtbl = 
{
    0,
    &IID_IContextMenuHandler,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy
};

const CInterfaceStubVtbl _IContextMenuHandlerStubVtbl =
{
    &IID_IContextMenuHandler,
    &IContextMenuHandler_ServerInfo,
    3,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    shellext__MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x50002, /* Ndr library version */
    0,
    0x800025b, /* MIDL Version 8.0.603 */
    0,
    0,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0
    };

const CInterfaceProxyVtbl * const _shellext_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IOverlayHandlerProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IContextMenuHandlerProxyVtbl,
    0
};

const CInterfaceStubVtbl * const _shellext_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IOverlayHandlerStubVtbl,
    ( CInterfaceStubVtbl *) &_IContextMenuHandlerStubVtbl,
    0
};

PCInterfaceName const _shellext_InterfaceNamesList[] = 
{
    "IOverlayHandler",
    "IContextMenuHandler",
    0
};


#define _shellext_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _shellext, pIID, n)

int __stdcall _shellext_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _shellext, 2, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _shellext, 2, *pIndex )
    
}

const ExtendedProxyFileInfo shellext_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _shellext_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _shellext_StubVtblList,
    (const PCInterfaceName * ) & _shellext_InterfaceNamesList,
    0, /* no delegation */
    & _shellext_IID_Lookup, 
    2,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* defined(_M_AMD64)*/

