#include "framework.h"
#include "aura/operating_system.h"
#include "graphics.h"


#include <winapifamily.h>
#include <shlwapi.h>
#include <wrl/client.h>
#include <D2d1_1.h>


#include <DXGI1_2.h>
#include <Dwrite.h>
#include <D3D11.h>
#include <D3D11_1.h>
#include <Dxgi1_3.h>
#include <Initguid.h>
#include <DXGIDebug.h>

#include "draw2d_direct2d_global.h"


#define d2d1_fax_options D2D1_FACTORY_OPTIONS // fax of merde
#define d2d1_thread_model D2D1_FACTORY_TYPE_MULTI_THREADED // ???? muliple performance multi thread hidden option there exists cost uses?


namespace draw2d
{


   ::mutex * lock::g_pmutex = nullptr;

} // namespace draw2d



// void dpi_os_initialize();

typedef HRESULT WINAPI FN_DXGIGetDebugInterface(REFIID riid, void **ppDebug);

typedef FN_DXGIGetDebugInterface * PFN_DXGIGetDebugInterface;

class dxgidebug
{
public:

   comptr<IDXGIDebug> d;

   void init()
   {

#ifdef _UWP
      HRESULT hr = DXGIGetDebugInterface1(0, IID_IDXGIDebug1, &d);
#else

      comptr<IDXGIInfoQueue> dxgiInfoQueue;

      typedef HRESULT(WINAPI * LPDXGIGETDEBUGINTERFACE)(REFIID, void **);

      HMODULE dxgidebug = LoadLibraryExW(L"dxgidebug.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
      if (dxgidebug)
      {
         auto dxgiGetDebugInterface = reinterpret_cast<LPDXGIGETDEBUGINTERFACE>(
                                      reinterpret_cast<void*>(GetProcAddress(dxgidebug, "DXGIGetDebugInterface")));
         if (SUCCEEDED(dxgiGetDebugInterface(IID_IDXGIDebug, &d)))
         {

         }
         //d.Attach(dxgiGetDebugInterface);
         //if (SUCCEEDED(dxgiGetDebugInterface(IID_PPV_ARGS(dxgiInfoQueue.GetAddressOf()))))
         //{
         // dxgiInfoQueue->SetBreakOnSeverity(DXGI_DEBUG_ALL, DXGI_INFO_QUEUE_MESSAGE_SEVERITY_ERROR, true);
         //dxgiInfoQueue->SetBreakOnSeverity(DXGI_DEBUG_ALL, DXGI_INFO_QUEUE_MESSAGE_SEVERITY_CORRUPTION, true);
         //}
      }

#endif


   }

   void debug()
   {

      if (d.Get() != nullptr)
      {

         ::output_debug_string("MY_DEBUG : IDXGIDebug::ReportLiveObjects");

         d->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);

      }
      else
      {

         init();

      }

   }

} *g_pdxgidebug;


CLASS_DECL_AURA void directx_debug()
{

   g_pdxgidebug->debug();

}


namespace draw2d_direct2d
{



   comptr<IDWriteFactory>      plugin::s_pwritefactory;
   comptr<ID2D1Factory1>       plugin::s_pd2factory;


    //plugin * g_pdirect2dplugin = nullptr;
   CLASS_DECL_AURA void direct2d_finalize()
   {

      //delete g_pdirect2dplugin;

      delete g_pdxgidebug;

   }

   CLASS_DECL_AURA void defer_direct2d_initialize()
   {

      if (g_pdxgidebug == nullptr)
      {

         g_pdxgidebug = new dxgidebug;

         //g_pdirect2dplugin = new plugin;

         //g_pdirect2dplugin->initialize();

      }

   }


   ::e_status plugin::initialize(::object * pobject)
   {

      // This flag adds support for surfaces with a different color channel ordering
      // than the API default. It is required for compatibility with Direct2D.
      ::u32 creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#if defined(__DEBUG)

      // If the project is in a debug build, enable debugging via SDK Layers with this flag.
      creationFlags |= D3D11_CREATE_DEVICE_DEBUG;

#endif

      // This array defines the set of DirectX hardware feature levels this app will support.
      // Note the ordering should be preserved.
      // Don't forget to declare your application's minimum required feature level in its
      // description.  All applications are assumed to support 9.1 unless otherwise stated.
      D3D_FEATURE_LEVEL featureLevels[] =
      {
         D3D_FEATURE_LEVEL_11_1,
         D3D_FEATURE_LEVEL_11_0,
         D3D_FEATURE_LEVEL_10_1,
         D3D_FEATURE_LEVEL_10_0,
         D3D_FEATURE_LEVEL_9_3,
         D3D_FEATURE_LEVEL_9_2,
         D3D_FEATURE_LEVEL_9_1
      };

      // Create the Direct3D 11 API device object and a corresponding context.
      comptr<ID3D11Device> device;

      comptr<ID3D11DeviceContext> context;

      HRESULT hr = D3D11CreateDevice(
                   nullptr,                    // Specify nullptr to use the default adapter.
                   D3D_DRIVER_TYPE_HARDWARE,
                   0,
                   creationFlags,              // Set debug and Direct2D compatibility flags.
                   featureLevels,              // List of feature levels this app can support.
                   ARRAYSIZE(featureLevels),
                   D3D11_SDK_VERSION,          // Always set this to D3D11_SDK_VERSION for Metro style apps.
                   &device,                    // Returns the Direct3D device created.
                   &m_featurelevel,            // Returns feature level of device created.
                   &context                    // Returns the device immediate context.
                   );

      ::dx::throw_if_failed(hr);


      // Get the Direct3D 11.1 API device and context interfaces.
      ::dx::throw_if_failed(
      device.As(&m_pd3device)
      );

      ::dx::throw_if_failed(
      device.As(&m_pd3device1)
      );

      ::dx::throw_if_failed(
      context.As(&m_pd3devicecontext)
      );

      ::dx::throw_if_failed(
      context.As(&m_pd3devicecontext1)
      );

      // Get the underlying DXGI device of the Direct3D device.
      ::dx::throw_if_failed(
      device.As(&m_pdxgidevice)
      );

      // Create the Direct2D device object and a corresponding context.
      ::dx::throw_if_failed(
      d2d1_factory1()->CreateDevice(m_pdxgidevice.Get(), &m_pd2device)
      );


      d2d1_factory1()->QueryInterface(IID_PPV_ARGS(&m_d2dMultithread));

      return ::success;

   }


   IDWriteFactory * plugin::dwrite_factory(bool bCreate)
   {

      if (s_pwritefactory != nullptr || !bCreate)
      {

         return s_pwritefactory.Get();

      }

      HRESULT hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), &s_pwritefactory);

      if (FAILED(hr))
      {

         return nullptr;

      }

      return s_pwritefactory.Get();

   }


   ID2D1Factory1 * plugin::d2d1_factory1(bool bCreate)
   {


      if (s_pd2factory != nullptr || !bCreate)
      {

         return s_pd2factory.Get();

      }

      d2d1_fax_options options;

      __memset(&options, 0, sizeof(options));

      HRESULT hr = ::D2D1CreateFactory(d2d1_thread_model, __uuidof(ID2D1Factory1), &options, &s_pd2factory);

      if (FAILED(hr))
      {

         return nullptr;

      }

      //dpi_initialize(::draw2d::device_lock::g_pfactory);

      return s_pd2factory.Get();

   }


   ID3D11Device * plugin::draw_get_d3d11_device()
   {

      return m_pd3device.Get();

   }


   ID3D11Device1 * plugin::draw_get_d3d11_device1()
   {

      return m_pd3device1.Get();

   }


   ID3D11DeviceContext * plugin::draw_get_d3d11_device_context()
   {

      return m_pd3devicecontext.Get();

   }


   ID3D11DeviceContext1 * plugin::draw_get_d3d11_device_context1()
   {

      return m_pd3devicecontext1.Get();

   }

   IDXGIDevice * plugin::draw_get_dxgi_device()
   {

      return m_pdxgidevice.Get();

   }

   ID2D1Device * plugin::draw_get_d2d1_device()
   {

      return m_pd2device.Get();

   }


} // namespace draw2d_direct2d



