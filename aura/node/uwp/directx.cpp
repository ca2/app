#include "framework.h"
#include "app/draw2d_direct2d/_.h"
#include "aura/os/windows_common/draw2d_direct2d_global.h"
#include "_uwp.h"


::size_i32 winrt_get_big_back_buffer_size();

using namespace ::winrt::Windows::UI::Core;
using namespace ::winrt::Windows::Foundation;
using namespace Microsoft::WRL;
using namespace ::winrt::Windows::Graphics::Display;
using namespace D2D1;


extern CLASS_DECL_AURA image_array * g_pimagea;


CLASS_DECL_ACME void dpi_os_initialize();


namespace universal_windows
{


   directx_base::directx_base() :
      m_dpi(-1.0f)
   {

      m_ephase = e_phase_draw;

      m_bCreated = false;

      m_pimpl = nullptr;

      m_b3D = false;

      m_dpiIni = 1.0f;
      m_dpi = -999.0f;
      m_bInitialized = false;
      m_bInit = false;

   }


   // Initialize the DirectX resources required to run.
   void directx_base::Initialize(CoreWindow^ window,float dpi)
   {

      m_window = window;

      m_dpiIni = dpi;

      CreateDeviceIndependentResources();

      m_bInit = true;

   }


   bool directx_base::defer_init()
   {

      ::draw2d::lock draw2dlock;

      ::draw2d::device_lock devicelock(this);

      if (m_bInitialized)
      {

         return true;

      }

      if (!m_bInit)
      {

         return false;

      }

      CreateDeviceResources();

      //SetDpi(m_dpiIni);

      m_dpi = m_dpiIni;

      ::aura::get_system()->m_dpi = m_dpiIni;

      m_bInitialized = true;

      dpi_os_initialize();

      //m_pimage->alloc(get_application()->create_new, this);
      //m_pimage = create_image({1000,  1000});


      return true;

   }


   // Recreate all device resources and set them back to the current state.
   void directx_base::HandleDeviceLost()
   {

      ::draw2d::lock draw2dlock;

      ::draw2d::device_lock devicelock(this);

      //// Reset these member variables to ensure that SetDpi recreates all resources.
      float dpi = m_dpi;
      m_dpi = -1.0f;
      m_windowBounds.Width = 0;
      m_windowBounds.Height = 0;
      m_swapChain = nullptr;

      {

         ID3D11RenderTargetView * nullViews[] = { nullptr };
         if (::aura::get_system()->draw2d()->direct2d()->m_pd3devicecontext)
         {
            ::aura::get_system()->draw2d()->direct2d()->m_pd3devicecontext->OMSetRenderTargets(ARRAYSIZE(nullViews), nullViews, nullptr);

         }
         m_d3dRenderTargetView = nullptr;
         if (::aura::get_system()->draw2d()->direct2d()->m_pd2devicecontext)
         {
            ::aura::get_system()->draw2d()->direct2d()->m_pd2devicecontext->SetTarget(nullptr);
         }
         m_d2dTargetBitmap = nullptr;
         m_d3dDepthStencilView = nullptr;
         ::aura::get_system()->draw2d()->direct2d()->m_pd3devicecontext->Flush();

         m_pd2d1devicecontext = nullptr;
         m_d2dTargetBitmap = nullptr;
         m_d3dRenderTargetView = nullptr;
         m_d3dDepthStencilView = nullptr;


      }

      CreateDeviceResources();

      SetDpi(dpi);

   }


   // These are the resources required independent of the device.
   void directx_base::CreateDeviceIndependentResources()
   {

      ::draw2d::lock draw2dlock;

      ::draw2d::device_lock devicelock(this);

      D2D1_FACTORY_OPTIONS options;
      ZeroMemory(&options,sizeof(D2D1_FACTORY_OPTIONS));

#if defined(__DEBUG)
      
      // If the project is in a debug build, enable Direct2D debugging via SDK Layers.
      options.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;

#endif // __DEBUG


      ::universal_windows::throw_if_failed(
      DWriteCreateFactory(
      DWRITE_FACTORY_TYPE_SHARED,
      __uuidof(IDWriteFactory),
      &m_dwriteFactory
      )
      );

      ::universal_windows::throw_if_failed(
      CoCreateInstance(
      CLSID_WICImagingFactory,
      nullptr,
      CLSCTX_INPROC_SERVER,
      IID_PPV_ARGS(&m_wicFactory)
      )
      );






















































      //// Create a DirectWrite text format object.
      //::universal_windows::throw_if_failed(
      //m_dwriteFactory->CreateTextFormat(
      //L"Gabriola",
      //nullptr,
      //DWRITE_FONT_WEIGHT_REGULAR,
      //DWRITE_FONT_STYLE_NORMAL,
      //DWRITE_FONT_STRETCH_NORMAL,
      //64.0f,
      //L"en-US", // locale
      //&m_textFormat
      //)
      //);

      //// Center the text horizontally.
      //::universal_windows::throw_if_failed(
      //m_textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER)
      //);

      //// Center the text vertically.
      //::universal_windows::throw_if_failed(
      //m_textFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER)
      //);





   }

   // These are the resources that depend on the device.
   void directx_base::CreateDeviceResources()
   {

      ::draw2d::lock draw2dlock;

      ::draw2d::device_lock devicelock(this);

      //::aura::get_system()->draw2d()->direct2d() = __new(::draw2d_direct2d::plugin);

      //::aura::get_system()->draw2d()->direct2d()->initialize();

      // m_d3dDevice = global_draw_get_d3d11_device1();

      //::aura::get_system()->draw2d()->direct2d()->m_pd3devicecontext = global_draw_get_d3d11_device_context1();

      //m_d2dDevice = global_draw_get_d2d1_device();

      //::draw2d_direct2d::g_pdirect2dplugin->g_pd2factory.As(&m_d2dMultithread);

   }

   // Helps track the DPI in the helper class.
   // This is called in the dpiChanged event handler in the impact class.
   void directx_base::SetDpi(float dpi)
   {
      // Only handle window size_i32 changed if there is no pending DPI change.

      m_window->Dispatcher->RunAsync(CoreDispatcherPriority::Normal, ref new ::winrt::Windows::UI::Core::DispatchedHandler([this,dpi]()
      {
         OnChangeDpi(dpi);

         //         ::aura::get_system()->m_psystem->m_possystemwindow->m_bWindowSizeChange = true;

      }));

   }


   void directx_base::OnChangeDpi(float dpi)
   {

      ::draw2d::lock draw2dlock;

      ::draw2d::device_lock devicelock(this);

      if (dpi != m_dpi)
      {

         m_dpi = dpi;

         ::aura::get_system()->m_dpi = dpi;

         if (m_bCreated)
         {

            //m_size.cx = (::i32)m_window->Bounds.Width;

            //m_size.cy = (::i32)m_window->Bounds.Height;



            OnWindowSizeChange();

         }

      }

   }


   void directx_base::UpdateForWindowSizeChange()
   {

      m_window->Dispatcher->RunAsync(CoreDispatcherPriority::Normal,ref new ::winrt::Windows::UI::Core::DispatchedHandler([this]()
      {

         OnWindowSizeChange();

      }));

   }


   void directx_base::OnWindowSizeChange()
   {

      if (m_size.cx != m_windowBounds.Width || m_size.cy != m_windowBounds.Height)
      {

         ::draw2d::lock draw2dlock;

         ::draw2d::device_lock devicelock(this);

         auto psubject = m_psystem->topic(id_os_dark_mode);

         m_psystem->process(psubject);

         CreateWindowSizeDependentResources();

         if (m_size.area() > 0)
         {

            m_psystem->fork([this]()
            {

               m_psystem->on_graphics_ready();

            });

         }

      }

      if (m_pimpl->m_puserinteraction)
      {

         m_pimpl->m_puserinteraction->start_layout();

         m_pimpl->m_puserinteraction->set_dim(0, 0, m_size.cx, m_size.cy);

         m_pimpl->m_puserinteraction->order_top();

         m_pimpl->m_puserinteraction->display(e_display_normal);

         //defer_resize_top_level_windows();

         m_pimpl->m_puserinteraction->set_reposition();

         m_pimpl->m_puserinteraction->set_need_layout();

         m_pimpl->m_puserinteraction->set_need_redraw();

         m_pimpl->m_puserinteraction->post_redraw();

      }


   }


   ID2D1DeviceContext* directx_base::get_device_context()
   {

      return m_pd2d1devicecontext.Get();

   }


   //void directx_base::defer_resize_top_level_windows()
   //{

   //   if (::aura::get_system()->m_bExperienceMainFrame)
   //   {

   //      auto puserinteractionpointeraChild = m_pimpl->m_puserinteraction->m_puserinteractionpointeraChild;

   //      if (puserinteractionpointeraChild)
   //      {

   //         auto children = puserinteractionpointeraChild->m_interactiona;

   //         for (auto & pinteraction : children)
   //         {

   //            //if (pinteraction->is_window_visible())
   //            {

   //               pinteraction->set_dim(0, 0, m_size.cx, m_size.cy);

   //               pinteraction->order_top();

   //               pinteraction->display();

   //               pinteraction->set_need_layout();

   //               pinteraction->set_need_redraw();

   //            }

   //         }

   //      }

   //   }

   //}


   // Allocate all memory resources that change on a window SizeChanged event.
   void directx_base::CreateWindowSizeDependentResources()
   {

      HRESULT hr;

      ::draw2d::lock draw2dlock;

      ::draw2d::device_lock devicelock(this);

      // Store the window bounds so the next time we get a SizeChanged event we can
      // avoid rebuilding everything if the size_i32 is identical.
      m_windowBounds.Width = (float) m_size.cx;
      m_windowBounds.Height = (float) m_size.cy;

      if(m_swapChain != nullptr)
      {
         return;
         ID3D11RenderTargetView * nullViews[] = { nullptr };
         ::aura::get_system()->draw2d()->direct2d()->m_pd3devicecontext->OMSetRenderTargets(ARRAYSIZE(nullViews), nullViews, nullptr);
         m_d3dRenderTargetView = nullptr;
         m_pd2d1devicecontext->SetTarget(nullptr);
         m_d2dTargetBitmap = nullptr;
         m_d3dDepthStencilView = nullptr;
         ::aura::get_system()->draw2d()->direct2d()->m_pd3devicecontext->Flush();

         m_pd2d1devicecontext = nullptr;
         m_d2dTargetBitmap = nullptr;
         m_d3dRenderTargetView = nullptr;
         m_d3dDepthStencilView = nullptr;
         //m_windowSizeChangeInProgress = true;


         ::aura::get_system()->draw2d()->direct2d()->m_pd3devicecontext->Flush();
         ::aura::get_system()->draw2d()->direct2d()->m_pd3devicecontext->ClearState();
         ::aura::get_system()->draw2d()->direct2d()->m_pd2device->ClearResources();
         {
            comptr < ID3D11CommandList > pcommandlist;
            hr = ::aura::get_system()->draw2d()->direct2d()->m_pd3devicecontext->FinishCommandList(false, &pcommandlist);
            if (SUCCEEDED(hr))
            {
            }
         }

         // If the __swap chain already exists, resize it.
         hr = m_swapChain->ResizeBuffers(
              0,
              0, // If you specify zero, DXGI will use the width of the client area of the target window.
              0, // If you specify zero, DXGI will use the height of the client area of the target window.
              DXGI_FORMAT_UNKNOWN, // Set this value to DXGI_FORMAT_UNKNOWN to preserve the existing format of the back buffer.
              0);

         if(hr == DXGI_ERROR_DEVICE_REMOVED)
         {
            // If the device was erased for any reason, a new device and swapchain will need to be created.
            HandleDeviceLost();

            // Everything is set up now. Do not continue execution of this method.
            return;
         }
         else if(hr == DXGI_ERROR_INVALID_CALL)
         {
            // i1;
            //  return;
            TRACE("directx_base::CreateWindowSizeDependentResources(1) DXGI_ERROR_INVALID_CALL");
         }
         else
         {
            if (FAILED(hr))
            {
               ::universal_windows::throw_if_failed(hr);

            }
         }
      }
      else
      {

         m_sizeBuffer = winrt_get_big_back_buffer_size();

         // Otherwise, create a new one using the same adapter as the existing Direct3D device.
         DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {0};
         swapChainDesc.Width = m_sizeBuffer.cx;                                     // Use automatic sizing.
         swapChainDesc.Height = m_sizeBuffer.cy;
         swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;           // This is the most common __swap chain format.
         swapChainDesc.Stereo = false;
         swapChainDesc.SampleDesc.Count = 1;                          // Don't use multi-sampling.
         swapChainDesc.SampleDesc.Quality = 0;
         swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
         swapChainDesc.BufferCount = 2;                               // Use double-buffering to minimize latency.
         swapChainDesc.Scaling = DXGI_SCALING_NONE;
         swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL; // All Metro style apps must use this SwapEffect.
         //swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_PREMULTIPLIED;
         swapChainDesc.Flags = 0;

         ComPtr<IDXGIDevice1> dxgiDevice;
         
         hr = ::aura::get_system()->draw2d()->direct2d()->m_pd3device.As(&dxgiDevice);

         ::universal_windows::throw_if_failed(hr);

         ComPtr<IDXGIAdapter> dxgiAdapter;

         hr = dxgiDevice->GetAdapter(&dxgiAdapter);
            
         ::universal_windows::throw_if_failed(hr);

         ComPtr<IDXGIFactory2> dxgiFactory;

         hr = dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory));

         ::universal_windows::throw_if_failed(hr);

         CoreWindow ^ window = m_window.Get();

         hr = dxgiFactory->CreateSwapChainForCoreWindow(
            ::aura::get_system()->draw2d()->direct2d()->m_pd3device.Get(),
            reinterpret_cast<IUnknown *>(window),
            &swapChainDesc,
            nullptr,
            &m_swapChain
         );

         ::universal_windows::throw_if_failed(hr);

         // Ensure that DXGI does not queue more than one frame at a time. This both reduces latency and
         // ensures that the application will only render after each VSync, minimizing power consumption.
         hr = dxgiDevice->SetMaximumFrameLatency(1);

         ::universal_windows::throw_if_failed(hr);

      }

      if (m_b3D)
      {

         // Create a Direct3D render target impact of the __swap chain back buffer.
         ComPtr<ID3D11Texture2D> backBuffer;

         HRESULT hr = m_swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
         
         ::universal_windows::throw_if_failed(hr);

         hr = ::aura::get_system()->draw2d()->direct2d()->m_pd3device->CreateRenderTargetView(
            backBuffer.Get(),
            nullptr,
            &m_d3dRenderTargetView
         );

         ::universal_windows::throw_if_failed(hr);

         // Cache the rendertarget dimensions in our helper class for convenient use.
         D3D11_TEXTURE2D_DESC backBufferDesc = { 0 };
         backBuffer->GetDesc(&backBufferDesc);
         m_renderTargetSize.Width = static_cast<float>(backBufferDesc.Width);
         m_renderTargetSize.Height = static_cast<float>(backBufferDesc.Height);

         // Create a depth stencil impact for use with 3D rendering if needed.
         CD3D11_TEXTURE2D_DESC depthStencilDesc(
         DXGI_FORMAT_D24_UNORM_S8_UINT,
         backBufferDesc.Width,
         backBufferDesc.Height,
         1,
         1,
         D3D11_BIND_DEPTH_STENCIL
         );

         ComPtr<ID3D11Texture2D> depthStencil;
         hr = ::aura::get_system()->draw2d()->direct2d()->m_pd3device->CreateTexture2D(
            &depthStencilDesc,
            nullptr,
            &depthStencil
         );

         ::universal_windows::throw_if_failed(hr);

         auto viewDesc = CD3D11_DEPTH_STENCIL_VIEW_DESC(D3D11_DSV_DIMENSION_TEXTURE2D);
         
         hr = ::aura::get_system()->draw2d()->direct2d()->m_pd3device->CreateDepthStencilView(
         depthStencil.Get(),
         &viewDesc,
         &m_d3dDepthStencilView
         );

         ::universal_windows::throw_if_failed(hr);

         // Set the 3D rendering viewport to target the entire window.
         CD3D11_VIEWPORT viewport(
         0.0f,
         0.0f,
         static_cast<float>(backBufferDesc.Width),
         static_cast<float>(backBufferDesc.Height)
         );

         ::aura::get_system()->draw2d()->direct2d()->m_pd3devicecontext->RSSetViewports(1, &viewport);

      }

      // Create a Direct2D target bitmap associated with the
      // __swap chain back buffer and set it as the current target.
      D2D1_BITMAP_PROPERTIES1 bitmapProperties =
      BitmapProperties1(
      D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
      PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM,D2D1_ALPHA_MODE_PREMULTIPLIED),
      m_dpi,
      m_dpi
      );


      hr = ::aura::get_system()->draw2d()->direct2d()->m_pd2device->CreateDeviceContext(
         //D2D1_DEVICE_CONTEXT_OPTIONS_NONE,
         D2D1_DEVICE_CONTEXT_OPTIONS_ENABLE_MULTITHREADED_OPTIMIZATIONS,
         &m_pd2d1devicecontext
      );

      ::draw2d_direct2d::throw_if_failed(hr);


      ComPtr<IDXGISurface> dxgiBackBuffer;
      
      hr = m_swapChain->GetBuffer(0, IID_PPV_ARGS(&dxgiBackBuffer));

      ::universal_windows::throw_if_failed(hr);

      
      hr = m_pd2d1devicecontext->CreateBitmapFromDxgiSurface(
         dxgiBackBuffer.Get(),
         &bitmapProperties,
         &m_d2dTargetBitmap);
      
      ::universal_windows::throw_if_failed(hr);

      m_pd2d1devicecontext->SetTarget(m_d2dTargetBitmap.Get());

   }


   void directx_base::DestroyWindowSizeDependentResources()
   {

      HRESULT hr;

      ::draw2d::lock draw2dlock;

      ::draw2d::device_lock devicelock(this);

      // Store the window bounds so the next time we get a SizeChanged event we can
      // avoid rebuilding everything if the size_i32 is identical.
      m_windowBounds.Width = (float)m_size.cx;
      m_windowBounds.Height = (float)m_size.cy;

      m_sizeBuffer = { 0,0 };

         
      m_swapChain = nullptr;

      m_d3dRenderTargetView = nullptr;
      m_d3dDepthStencilView = nullptr;
      m_pd2d1devicecontext->SetTarget(nullptr);
      m_pd2d1devicecontext = nullptr;
      m_d2dTargetBitmap = nullptr;

   }


   void directx_base::Present()
   {

      if (m_pimpl->m_pframeworkview->m_directx->m_ephase != ::universal_windows::e_phase_present)
      {

         return ;

      }

      HRESULT hr = S_OK;

      {

         ::draw2d::lock draw2dlock;

         ::draw2d::device_lock devicelock(this);

         if (!defer_init())
         {

            return;

         }

         try
         {

            // The application may optionally specify "dirty" or "scroll" rects to improve efficiency
            // in certain scenarios.  In this sample, however, we do not utilize those features.
            DXGI_PRESENT_PARAMETERS parameters = {};

            parameters.DirtyRectsCount = 0;

            parameters.pDirtyRects = nullptr;

            parameters.pScrollRect = nullptr;

            parameters.pScrollOffset = nullptr;

            if (m_swapChain == nullptr)
            {

               return;

            }

            {


               // The first argument instructs DXGI to block until VSync, putting the application
               // to sleep until the next VSync. This ensures we don't waste any cycles rendering
               // frames that will never be displayed to the screen.
               hr = m_swapChain->Present1(1, 0, &parameters);

               if (::aura::get_system()->draw2d()->direct2d()->m_pd3devicecontext.Get())
               {

                  if (m_d3dRenderTargetView.Get())
                  {

                     // Discard the contents of the render target.
                     // This is a valid operation only when the existing contents will be entirely
                     // overwritten. If dirty or scroll rects are used, this call should be erased.
                     ::aura::get_system()->draw2d()->direct2d()->m_pd3devicecontext1->DiscardView(m_d3dRenderTargetView.Get());

                  }

                  if (m_d3dDepthStencilView.Get())
                  {

                     // Discard the contents of the depth stencil.
                     ::aura::get_system()->draw2d()->direct2d()->m_pd3devicecontext1->DiscardView(m_d3dDepthStencilView.Get());

                  }

               }

               g_pimagea->erase_all();

            }

            // If the device was erased either by a disconnect or a driver upgrade, we
            // must recreate all device resources.
            if (hr == DXGI_ERROR_DEVICE_REMOVED)
            {

               HandleDeviceLost();

            }
            else
            {
               if (FAILED(hr))
               {

                  ::universal_windows::throw_if_failed(hr);


               }

            }

         }
         catch (...)
         {

         }

         m_pimpl->m_pframeworkview->m_directx->m_ephase = ::universal_windows::e_phase_draw;

      }

      //if (m_windowSizeChangeInProgress)
      //{

      //   m_windowSizeChangeInProgress = false;

      //   m_window->Dispatcher->RunAsync(CoreDispatcherPriority::Normal, ref new ::winrt::Windows::UI::Core::DispatchedHandler([this]()
      //   {

      // A window size_i32 change has been initiated and the app has just completed presenting
      // the first frame with the new size. Notify the resize manager so we can short
      // circuit any resize animation and prevent unnecessary delays.
      //      CoreWindowResizeManager::GetForCurrentView()->NotifyLayoutCompleted();

      //   }));

      //}

   }


   void directx_base::ValidateDevice()
   {

      ::draw2d::lock draw2dlock;

      ::draw2d::device_lock devicelock(this);
      // The D3D Device is no longer valid if the default adapter changes or if
      // the device has been erased.

      // First, get the information for the adapter related to the current device.

      ComPtr<IDXGIDevice1> dxgiDevice;
      ComPtr<IDXGIAdapter> deviceAdapter;
      DXGI_ADAPTER_DESC deviceDesc;
      ::universal_windows::throw_if_failed(::aura::get_system()->draw2d()->direct2d()->m_pd3device.As(&dxgiDevice));
      ::universal_windows::throw_if_failed(dxgiDevice->GetAdapter(&deviceAdapter));
      ::universal_windows::throw_if_failed(deviceAdapter->GetDesc(&deviceDesc));

      // Next, get the information for the default adapter.

      ComPtr<IDXGIFactory2> dxgiFactory;
      ComPtr<IDXGIAdapter1> currentAdapter;
      DXGI_ADAPTER_DESC currentDesc;
      ::universal_windows::throw_if_failed(CreateDXGIFactory1(IID_PPV_ARGS(&dxgiFactory)));
      ::universal_windows::throw_if_failed(dxgiFactory->EnumAdapters1(0,&currentAdapter));
      ::universal_windows::throw_if_failed(currentAdapter->GetDesc(&currentDesc));

      // If the adapter LUIDs don't match, or if the device reports that it has been erased,
      // a new D3D device must be created.

      if((deviceDesc.AdapterLuid.LowPart != currentDesc.AdapterLuid.LowPart) ||
            (deviceDesc.AdapterLuid.HighPart != currentDesc.AdapterLuid.HighPart) ||
            FAILED(::aura::get_system()->draw2d()->direct2d()->m_pd3device->GetDeviceRemovedReason()))
      {
         // Release references to resources related to the old device.
         dxgiDevice = nullptr;
         deviceAdapter = nullptr;

         // Create a new device and __swap chain.
         HandleDeviceLost();

      }

   }


   //HRESULT directx_base::Render()
   //{

   //   ::draw2d::lock draw2dlock;

   //   if (!defer_init())
   //   {

   //      return E_FAIL;

   //   }

   //   m_pd2d1devicecontext->BeginDraw();

   //   auto colorBackground = ::winrt::Windows::UI::ViewManagement::UISettings().GetColorValue(::winrt::Windows::UI::ViewManagement::UIColorType::Background);

   //   D2D1_COLOR_F color32;

   //   color32.a = 1.0f;
   //   color32.r = colorBackground.R / 255.f;
   //   color32.g = colorBackground.G / 255.f;
   //   color32.b = colorBackground.B / 255.f;

   //   m_pd2d1devicecontext->Clear(color32);

   //   m_pd2d1devicecontext->SetTransform(D2D1::Matrix3x2F::Identity());

   //   ::draw2d::graphics_pointer dc(e_create_new, ::get_context_system());

   //   dc->attach((ID2D1DeviceContext *) m_pd2d1devicecontext.Get());

   //   auto pimpl = m_psystem->get_session()->m_puserinteractionHost->m_pimpl;

   //   //throw_todo();

   //   //if (pimpl.is_set())
   //   //{

   //   //   pimpl->_001UpdateBuffer();

   //   //   __pointer(::window_double_buffer) pbuffer = pimpl->m_spgraphics;

   //   //   if (pbuffer.is_set())
   //   //   {

   //   //      size_i32 sz = pbuffer->get_buffer().get_size();

   //   //      ::draw2d::graphics_pointer & pgraphics = pbuffer->get_buffer().get_graphics();

   //   //      //pgraphics->fill_solid_rect_dim(300, 300, 100, 100, argb(255, 200, 60, 80));

   //   //      dc->from(sz, pgraphics);

   //   //   }

   //   //}

   //   ////_001UpdateBuffer();

   //   ////Sys(::get_context_system()).m_possystemwindow->m_puserinteraction->_000OnDraw(m_pimage->g());

   //   ////dc->from(m_pimage->get_size(), m_pimage->g());
   //   ////dc->from(m_pimage->get_size(), m_pimage->g());

   //   ////synchronouslock.lock();

   //   //dc->detach();


   //   //// We ignore D2DERR_RECREATE_TARGET here. This error indicates that the device
   //   //// is lost. It will be handled during the next call to Present.
   //   //HRESULT hr = m_pd2d1devicecontext->EndDraw();

   //   //if(FAILED(hr))
   //   //{

   //   //   if(hr == D2DERR_RECREATE_TARGET)
   //   //   {

   //   //      trace_hr("directx_base::Render, EndDraw", hr);

   //   //   }
   //   //   else if(hr == D2DERR_WRONG_STATE)
   //   //   {

   //   //      trace_hr("directx_base::Render, EndDraw",hr);

   //   //   }
   //   //   else
   //   //   {

   //   //      trace_hr("directx_base::Render, EndDraw",hr);

   //   //   }

   //   //}

   //   // return hr;

   //   return E_FAIL;

   //}


} // namespace universal_windows



