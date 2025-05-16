#include "framework.h"
#include "context_glx.h"
#include "vulkan.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura_posix/_.h"
//#include "aura_posix/_library.h"
#include "operating_system-posix/windowing_system_x11/display_lock.h"
#include "aura/platform/system.h"
#include "aura/platform/session.h"
#include "aura/user/user/user.h"
#include "aura_posix/node.h"


::particle * user_synchronization();


namespace vulkan
{


   ::pointer <::gpu::context > allocate_glx_context(::particle * pparticle)
   {

      return pparticle->__create_new < context_glx >();

   }


   context_glx::context_glx()
   {

      m_emode = e_mode_glx;

   }


   context_glx::~context_glx()
   {


   }


   void context_glx::_create_offscreen_buffer(const ::int_size & size)
   {

      auto psystem = system();

      auto pgpu = psystem->get_gpu();

      ::pointer<::vulkan::vulkan>pvulkan = pgpu;

      if (::is_null(pvulkan))
      {

         throw ::exception(error_failed);

      }

      int w = size.cx();

      int h = size.cy();

      int attribList[]=
      {
         GLX_RENDER_TYPE, GLX_RGBA_BIT,
         //GLX_MAX_PBUFFER_WIDTH, w,
         //GLX_MAX_PBUFFER_HEIGHT, h,
         GLX_BUFFER_SIZE, 32,
         GLX_RED_SIZE, 8,
         GLX_GREEN_SIZE, 8,
         GLX_BLUE_SIZE, 8,
         GLX_ALPHA_SIZE, 8,
         GLX_DRAWABLE_TYPE,GLX_PBUFFER_BIT,
         GLX_DEPTH_SIZE, 24,
         GLX_STENCIL_SIZE, 8,
         None

      };

      synchronous_lock synchronouslock(user_synchronization());

      auto psession = session();

      auto puser = user();

      auto pwindowing = system()->windowing();

      auto pnode = (::aura_posix::node *) node()->m_pAuraPosix;

      auto pdisplay = (Display *) pnode->_get_Display();

      ::x11::display_lock display(pdisplay);

      int screen = DefaultScreen(pdisplay);

      int iConfigCount = 0;

      m_pconfig = glXChooseFBConfig(pdisplay, screen, attribList, &iConfigCount);

      if (m_pconfig == NULL || iConfigCount <= 0)
      {

         errorf("P-Buffers not supported.");

         throw ::exception(error_failed);

      }

        int glx_major, glx_minor;

   // FBConfigs were added in GLX version 1.3.
      if ( !glXQueryVersion(pdisplay, &glx_major, &glx_minor ) ||
         ( ( glx_major == 1 ) && ( glx_minor < 3 ) ) || ( glx_major < 1 ) )
      {

         errorf("Invalid GLX version");

         throw ::exception(error_failed);

      }


      int bufferAttribList[]=
      {
         GLX_PBUFFER_WIDTH, w,
         GLX_PBUFFER_HEIGHT, h,
         None

      };


      // Create P-Buffer
      m_pbuffer = glXCreatePbuffer(pdisplay, m_pconfig[0], bufferAttribList);

      if (m_pbuffer == None)
      {

         errorf("Failed to create P-Buffer.");

         throw ::exception(error_failed);

      }

      // Create graphics context
      m_context = glXCreateNewContext(pdisplay, m_pconfig[0], GLX_RGBA_TYPE, NULL, GL_TRUE);

      if (!m_context)
      {

         errorf("Failed to create graphics context.");

         throw ::exception(error_failed);

      }


      m_itaskGpu = ::current_itask();
      //::e_status estatus =
      //
      make_current();

//      if(!estatus)
//      {
//
//         throw ::exception(estatus);
//
//      }


      //estatus =
      //
      pvulkan->defer_init_gpu_library();

//      if (!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      return estatus;

   }


   void context_glx::make_current()
   {

      ::e_status estatus = ::success;

      synchronous_lock synchronouslock(user_synchronization());

      auto psession = session();

      auto puser = user();

      auto pwindowing = system()->windowing();

      auto pnode = (::aura_posix::node *) node()->m_pAuraPosix;

      auto pdisplay = (Display *) pnode->_get_Display();

      ::x11::display_lock display(pdisplay);

      // Activate graphics context
      if (!glXMakeContextCurrent(pdisplay, m_pbuffer, m_pbuffer, m_context))
      {

         errorf("Failed to activate graphics context.");

         estatus = ::error_failed;

      }

      if(!estatus)
      {

         throw ::exception(estatus);

      }

   }


   void context_glx::resize_offscreen_buffer(const ::int_size& size)
   {

      if(!m_pbuffer)
      {

         return create_offscreen_buffer(size);

      }

      //auto estatus =
      //
      ::gpu::context::resize_offscreen_buffer(size);

//      if(!estatus)
//      {
//
//         return estatus;
//
//      }

      int bufferAttribList[]=
      {
         GLX_PBUFFER_WIDTH, size.cx(),
         GLX_PBUFFER_HEIGHT, size.cy(),
         None

      };

      synchronous_lock synchronouslock(user_synchronization());

      auto pnode = (::aura_posix::node *) node()->m_pAuraPosix;

      auto pdisplay = (Display *) pnode->_get_Display();

      ::x11::display_lock display(pdisplay);

      int screen = DefaultScreen(pdisplay);

      // Create P-Buffer
      auto pbuffer = glXCreatePbuffer(pdisplay, m_pconfig[0], bufferAttribList);

      if (pbuffer == None)
      {

         throw ::exception(::error_failed);

      }

      auto pbufferOld = m_pbuffer;

      m_pbuffer = pbuffer;

      glXDestroyPbuffer(pdisplay, pbufferOld);

      make_current();

      //return ::success_none;

   }


   void context_glx::destroy_offscreen_buffer()
   {

//      ::e_status estatus = error_failed;
//
//      return estatus;

   }


   string context_glx::get_shader_version_text()
   {

      return "#version 300 es";

   }


   void context_glx::_translate_shader(string_array & stra)
   {

      character_count iFindPrecision = stra.case_insensitive_find_first_begins("precision ");

      if(iFindPrecision >= 0)
      {

         stra[iFindPrecision] = "precision highp float;";

      }
      else
      {

         stra.insert_at(1, "precision highp float;");

         iFindPrecision = 1;

      }

      auto iFind = stra.case_insensitive_find_first_begins("out vec4 ");

      if(::found(iFind))
      {

         stra[iFind] = "out vec4 fragmentColor;";

      }
      else
      {

         stra.insert_at(iFindPrecision + 1, "out vec4 fragmentColor;");

      }

      stra.replace_with("fragmentColor", "gl_FragColor");

   }


} // namespace gpu



