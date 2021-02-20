#pragma once


namespace direct2d
{


   class CLASS_DECL_DIRECT2D component :
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

      static component * g_p;

      component();
      virtual ~component();

      static void initialize();
      static void terminate();
  
      virtual ::e_status initialize(::layered * pobjectContext) override;


      static IDWriteFactory * dwrite_factory(bool bCreate = true);
      static ID2D1Factory1 * d2d1_factory1(bool bCreate = true);


      ID3D11Device * draw_get_d3d11_device();
      ID3D11Device1 * draw_get_d3d11_device1();
      ID3D11DeviceContext * draw_get_d3d11_device_context();
      ID3D11DeviceContext1 * draw_get_d3d11_device_context1();
      IDXGIDevice * draw_get_dxgi_device();
      ID2D1Device * draw_get_d2d1_device();





      //float point_dpi(oswindow hwnd, float points);
      //float dpiy(oswindow hwnd, float y);
      //float dpix(oswindow hwnd, float y);
      //float y_dpi(oswindow hwnd, float y);
      //float x_dpi(oswindow hwnd, float y);

      //virtual ::e_status initialize(::layered * pobjectContext) override;

      

   };


   inline component * direct2d() { return component::g_p; }


} // namespace draw2d_direct2d



