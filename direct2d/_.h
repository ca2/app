#pragma once


#include "aura/_.h"
#include "aura/operating_system.h"
//#include "aura/os/windows_common/graphics.h"
//#include "aura/os/windows/d2d1_1.h"


#include <winapifamily.h>
#include <windows.h>
#include <shlwapi.h>
#include <wrl/client.h>
#include <DXGI1_2.h>
#include <Dwrite.h>
#include <D2D1.h>
#include <D2D1_1.h>
#include <D3D11.h>
#include <D3D11_1.h>

//#include <DXGI1_2.h>
//#include <Dwrite.h>
//#include <D3D11.h>
//#include <D3D11_1.h>
#include <Dxgi1_3.h>
#include <Initguid.h>
#include <DXGIDebug.h>


// Windows Desktop Thread Local Storage for Draw2d Direct2d plugin


interface IDWriteFactory;
interface ID2D1Factory1;
interface ID3D11Device;
interface ID3D11DeviceContext;
interface ID3D11Device1;
interface IDXGIDevice;


//CLASS_DECL_AURA ID2D1Factory1 * get_d2d1_factory1(bool bCreate = true);
//CLASS_DECL_AURA IDWriteFactory * global_draw_get_write_factory(bool bCreate = true);
//CLASS_DECL_AURA ID3D11Device * global_draw_get_d3d11_device();
//CLASS_DECL_AURA ID3D11Device1 * global_draw_get_d3d11_device1();
//CLASS_DECL_AURA ID3D11DeviceContext * global_draw_get_d3d11_device_context(); // Immediate Device Context
//CLASS_DECL_AURA ID3D11DeviceContext1 * global_draw_get_d3d11_device_context1(); // Immediate Device Context
//CLASS_DECL_AURA IDXGIDevice * global_draw_get_dxgi_device();
//CLASS_DECL_AURA ID2D1Device * global_draw_get_d2d1_device();
#ifdef _DIRECT2D_LIBRARY
#define CLASS_DECL_DIRECT2D  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_DIRECT2D  CLASS_DECL_IMPORT
#endif



//
//namespace draw2d_direct2d
//{
//
//
//   class CLASS_DECL_AURA plugin :
//      virtual public ::matter
//   {
//
//   };
//
//   //extern plugin  * g_pdirect2dplugin;
//
//
//   CLASS_DECL_AURA void direct2d_finalize();
//
//   CLASS_DECL_AURA void defer_direct2d_initialize();
//
//
//} // namespace draw2d

namespace dx
{

   inline void throw_if_failed(HRESULT hr)
   {

      if (FAILED(hr))
      {
       
         __throw(hresult_exception(hr));

      }
      //if(FAILED(hr))
      // __throw(hr);

   }


} // namespace dx


CLASS_DECL_DIRECT2D void directx_debug();










#include "direct2d.h"

