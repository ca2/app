#pragma once


#include "aura/operating_system.h"


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


//CLASS_DECL_AURA ID2D1Factory1 * get_d2d1_factory1(bool bCreate = true);
//CLASS_DECL_AURA IDWriteFactory * global_draw_get_write_factory(bool bCreate = true);
//CLASS_DECL_AURA ID3D11Device * global_draw_get_d3d11_device();
//CLASS_DECL_AURA ID3D11Device1 * global_draw_get_d3d11_device1();
//CLASS_DECL_AURA ID3D11DeviceContext * global_draw_get_d3d11_device_context(); // Immediate Device Context
//CLASS_DECL_AURA ID3D11DeviceContext1 * global_draw_get_d3d11_device_context1(); // Immediate Device Context
//CLASS_DECL_AURA IDXGIDevice * global_draw_get_dxgi_device();
//CLASS_DECL_AURA ID2D1Device * global_draw_get_d2d1_device();



CLASS_DECL_AURA float point_dpi(oswindow hwnd, float points);
CLASS_DECL_AURA float dpiy(oswindow hwnd, float y);
CLASS_DECL_AURA float dpix(oswindow hwnd, float y);
CLASS_DECL_AURA float y_dpi(oswindow hwnd, float y);
CLASS_DECL_AURA float x_dpi(oswindow hwnd, float y);


namespace draw2d_direct2d
{


   class CLASS_DECL_AURA plugin :
      virtual public ::matter
   {
   protected:


      static Microsoft::WRL::ComPtr<IDWriteFactory>      s_pwritefactory;
      static Microsoft::WRL::ComPtr<ID2D1Factory1>       s_pd2factory;


   public:


      Microsoft::WRL::ComPtr<ID2D1Device> m_pd2device;
      Microsoft::WRL::ComPtr<ID2D1DeviceContext> m_pd2devicecontext;
      Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_pd3devicecontext;
      Microsoft::WRL::ComPtr<ID3D11DeviceContext1> m_pd3devicecontext1;
      Microsoft::WRL::ComPtr<ID3D11Device> m_pd3device;
      Microsoft::WRL::ComPtr<ID3D11Device1> m_pd3device1;
      Microsoft::WRL::ComPtr<IDXGIDevice> m_pdxgidevice;

      Microsoft::WRL::ComPtr<ID2D1Multithread> m_d2dMultithread;

      D3D_FEATURE_LEVEL m_featurelevel;

      virtual ::e_status initialize(::context_object * pcontextobject) override;


      static IDWriteFactory * dwrite_factory(bool bCreate = true);
      static ID2D1Factory1 * d2d1_factory1(bool bCreate = true);


      ID3D11Device * draw_get_d3d11_device();
      ID3D11Device1 * draw_get_d3d11_device1();
      ID3D11DeviceContext * draw_get_d3d11_device_context();
      ID3D11DeviceContext1 * draw_get_d3d11_device_context1();
      IDXGIDevice * draw_get_dxgi_device();
      ID2D1Device * draw_get_d2d1_device();


   } ;

   //extern plugin  * g_pdirect2dplugin;


   CLASS_DECL_AURA void direct2d_finalize();

   CLASS_DECL_AURA void defer_direct2d_initialize();


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


CLASS_DECL_AURA void directx_debug();

