#pragma once


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

// Windows Desktop Thread Local Storage for Draw2d Direct2d plugin


interface IDWriteFactory;
interface ID2D1Factory1;
interface ID3D11Device;
interface ID3D11DeviceContext;
interface ID3D11Device1;
interface IDXGIDevice;


CLASS_DECL_CORE ID2D1Factory1 * get_d2d1_factory1(bool bCreate = true);
CLASS_DECL_CORE IDWriteFactory * global_draw_get_write_factory(bool bCreate = true);
CLASS_DECL_CORE ID3D11Device * global_draw_get_d3d11_device();
CLASS_DECL_CORE ID3D11Device1 * global_draw_get_d3d11_device1();
CLASS_DECL_CORE ID3D11DeviceContext * global_draw_get_d3d11_device_context(); // Immediate Device Context
CLASS_DECL_CORE ID3D11DeviceContext1 * global_draw_get_d3d11_device_context1(); // Immediate Device Context
CLASS_DECL_CORE IDXGIDevice * global_draw_get_dxgi_device();
CLASS_DECL_CORE ID2D1Device * global_draw_get_d2d1_device();



CLASS_DECL_CORE float point_dpi(oswindow hwnd, float points);
CLASS_DECL_CORE float dpiy(oswindow hwnd, float y);
CLASS_DECL_CORE float dpix(oswindow hwnd, float y);
CLASS_DECL_CORE float y_dpi(oswindow hwnd, float y);
CLASS_DECL_CORE float x_dpi(oswindow hwnd, float y);


namespace draw2d_direct2d
{


   CLASS_DECL_CORE void direct2d_finalize();

   CLASS_DECL_CORE void direct2d_initialize();


} // namespace draw2d

namespace dx
{

   inline void throw_if_failed(HRESULT hr)
   {

      if (FAILED(hr))
         __throw(hresult_exception(hr));
      //if(FAILED(hr))
      // __throw(hr);

   }


} // namespace dx


CLASS_DECL_CORE void directx_debug();

