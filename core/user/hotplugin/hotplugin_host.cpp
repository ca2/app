#include "framework.h"




#if defined(LINUX) || defined(ANDROID) || defined(APPLEOS) || defined(SOLARIS)
iptr get_map_failed();
void my_munmap(void * pcolorref,HANDLE hfile);
void * my_open_map(const char * psz,HANDLE * pfile,bool bRead,bool bWrite,i64 size);
#endif


namespace hotplugin
{


   host::host()
   {

      m_pbasecomposer            = nullptr;
      m_pplugin                  = nullptr;
      m_dProgressRate            = 0.0;
      m_bShowProgress            = true;
      m_bCa2InstallationReady    = false;
      m_bStream                  = false;

      m_pmutexBitmap             = nullptr;
      m_bHostStarterStart        = false;

   }


   host::~host()
   {

      free_memory();

   }


   bool host::open_link(const string & strLink,const string & strTarget)
   {

      if(m_pbasecomposer != nullptr)
      {

         return m_pbasecomposer->open_link(strLink, strTarget);

      }

      return false;

   }


   bool host::reload_plugin()
   {

      return false;

   }


   string host::get_host_location_url()
   {

      if(m_pbasecomposer != nullptr)
      {

         return m_pbasecomposer->m_strHostPluginLocation;

      }

      return "";

   }


   void host::redraw()
   {

   }


   void host::post_message(const ::id & id, WPARAM wparam, LPARAM lparam)

   {

   }


   oswindow host::get_host_window()
   {

      return nullptr;

   }


   void host::set_memory(void * puchMemory, ::count c)
   {

      m_memory.assign(puchMemory, c);

   }


   void host::append_memory(void * puchMemory, ::count c)
   {

      m_memory.append(puchMemory, c);

   }


   ::count host::get_memory_length()
   {

      return m_memory.get_size();

   }


   ::count host::read_memory(void * puchMemory, ::count c)
   {

      if (c > m_memory.get_size())
         c = m_memory.get_size();

      memcpy_dup(puchMemory, m_memory.get_data(), c);

      return c;

   }


   void host::free_memory()
   {

      m_memory.set_size(0);

   }


   i32 host::start_ca2_system()
   {

      if(m_pplugin != nullptr)
      {

         return m_pplugin->start_ca2_system();

      }

      return -1;

   }


   void host::on_paint(::draw2d::graphics_pointer & pgraphics,const ::rect & rect)

   {

      if(m_pplugin != nullptr)
      {

         try
         {
            //::u32 dwTime1 = ::get_tick();

            m_pplugin->on_paint(pgraphics, rect);

            //::u32 dwTime9 = ::get_tick();

            //TRACE("plugin->on_paint %d",dwTime9 - dwTime1);

         }
         catch(...)
         {

         }

      }
      else
      {

         plugin::on_paint(pgraphics, rect);


      }

      if(::user::interaction::m_pimpl != nullptr && pgraphics != nullptr)
      {
         //::u32 dwTime1 = ::get_tick();


         ::user::interaction::m_pimpl->_001Print(pgraphics);
         //::u32 dwTime9 = ::get_tick();

         //TRACE("m_pimpl->_001Print %d",dwTime9 - dwTime1);

      }
      //::u32 dwTime1 = ::get_tick();

      deferred_prodevian_redraw();
      //::u32 dwTime9 = ::get_tick();

      //TRACE("deferred_prodevian_redraw %d",dwTime9 - dwTime1);

   }


   void host::set_ready()
   {

      m_bOk = true;

      if(is_ok() && m_pplugin != nullptr && m_pplugin->is_ok())
      {

         on_ready();

      }

   }


   void host::on_ready()
   {

      if(m_pplugin != nullptr)
      {

         m_pplugin->on_ready();

      }

   }

   bool host::plugin_initialize()
   {

      if(m_pplugin != nullptr)
      {

         return m_pplugin->plugin_initialize();

      }

      return true;

   }

   bool host::plugin_finalize()
   {

      if(m_pplugin != nullptr)
      {

         plugin * pplugin = m_pplugin;

         m_pplugin = nullptr;

         pplugin->plugin_finalize();

         return true;

      }

      return true;

   }

   void host::start_plugin()
   {

      {

         __pointer(::mutex) pmutex = __new(::mutex(e_create_new, "Global\\::ca::account::ca2_spa::7807e510-5579-11dd-ae16-0800200c7784"));

         if(::get_last_error() == ERROR_ALREADY_EXISTS)
         {

            m_bRunningSpaAdmin = true;

            return;

         }

      }

      throw todo();

      //m_pplugin = new install::plugin(get_object());

      //m_pplugin->set_host(this);

   }


   void host::start_ca2()
   {

      if(m_pplugin != nullptr)
      {

         m_pplugin->start_ca2();

      }
      else
      {

         ::hotplugin::plugin::start_ca2();

      }

   }


   void host::set_progress_rate(double dRate)
   {

      m_dProgressRate = dRate;

   }


   double host::get_progress_rate()
   {

      if(m_dProgressRate < 0.0)
         return 0.0;
      else if(m_dProgressRate > 1.0)
         return 1.0;
      else
         return m_dProgressRate;

   }


   void host::set_ca2_installation_ready(bool bReady)
   {

      m_bCa2InstallationReady = bReady;

   }


   bool host::is_ca2_installation_ready()
   {

      return m_bCa2InstallationReady;

   }


   i32 host::start_app_install(const char * pszCommandLine)
   {

      return start_app_install(pszCommandLine, get_context_application(), this);

   }


   i32 host::s_start_app_install(const char * pszCommandLine, ::aura::application * papp, host * phost, plugin * pplugin)
   {

      return phost->start_app_install(pszCommandLine, papp, pplugin);

   }


   i32 host::start_app_install(const char * pszCommandLine, ::aura::application * papp, plugin * pplugin)
   {

      if(m_bHostStarterStart)
         return 0;

      m_bHostStarterStart = true;

      __throw(todo());

      //::install::starter_start * pstart    = new ::install::starter_start(pobject);

      //pstart->m_phost               = phost;

      //pstart->m_pplugin             = pplugin;

      //pstart->m_strCommandLine      = pszCommandLine;

      //::create_thread(nullptr, 0, &::install::_ca2_starter_start, pstart, 0, pplugin == nullptr ? nullptr : &pplugin->m_nCa2StarterStartThreadID);

      return 0;

   }


   i32 host::s_host_starter_start_sync(const char * pszCommandLine, ::aura::application * papp, host * phost, plugin * pplugin)
   {

      return phost->host_starter_start_sync(pszCommandLine, papp, pplugin);

   }


   i32 host::host_starter_start_sync(const char * pszCommandLine, ::aura::application * papp, plugin * pplugin)
   {

      if (m_bHostStarterStart)
         return 0;

      m_bHostStarterStart = true;

      __throw(todo());

      //::install::starter_start * pstart = new ::install::starter_start(pobject);

      //pstart->m_phost               = phost;

      //pstart->m_pplugin             = pplugin;

      //pstart->m_strCommandLine      = pszCommandLine;

      //::install::_ca2_starter_start(pstart);

      return 0;

   }



   void host::deferred_prodevian_redraw()
   {

      if(m_pplugin != nullptr)
      {

         m_pplugin->deferred_prodevian_redraw();

      }

   }


   void * host::get_context_system()
   {

      return this;

   }


   void host::set_status(const char * pszStatus)
   {

      ::hotplugin::plugin::set_status(pszStatus);

      if(m_pplugin != nullptr)
      {

         m_pplugin->set_status(pszStatus);

      }

   }


   void host::set_bitmap(::draw2d::graphics_pointer & pgraphics,const ::rect & rect)
   {

      ensure_bitmap_data(rect.size(), false);

      if (!m_memorymapBitmap.is_mapped())
      {
       
         return;

      }

      sync_lock ml(m_pmutexBitmap);

      m_sizeBitmap = abs(rect.size());


      try
      {

         __throw(todo());

         //::draw2d::bitmap_pointer b(e_create);

         //b->create_from_data(m_sizeBitmap.cx, m_sizeBitmap.cy, m_pcolorref, pgraphics);

         //::draw2d::graphics_pointer g(e_create);

         //g->create_from_bitmap(b);

         //g.bit_blt(0, 0, m_sizeBitmap.cx, m_sizeBitmap.cy, pgraphics, prect.left, prect.top, SRCCOPY);


      }
      catch(...)
      {

      }

      return;

   }


   void host::paint_bitmap(::draw2d::graphics_pointer & pgraphics,const ::rect & rect)
   {

      ensure_bitmap_data(rect, false);

      if(!m_memorymapBitmap.is_mapped())
         return;

      sync_lock ml(m_pmutexBitmap);

      m_sizeBitmap = abs(rect.size());

      try
      {

         __throw(todo());

         //simple_bitmap b;

         //b.create_from_data(m_sizeBitmap.cx, m_sizeBitmap.cy, m_pcolorref, pgraphics);

         //simple_graphics g;

         //g.create_from_bitmap(b);

         //pgraphics.bit_blt(prect.left, prect.top, m_sizeBitmap.cx, m_sizeBitmap.cy, g, 0, 0, SRCCOPY);


      }
      catch(...)
      {

      }

      return;

   }


   void host::blend_bitmap(::draw2d::graphics_pointer & pgraphics,const ::rect & rectOut)
   {

      auto rect = get_window_rect();

      m_sizeBitmap = abs(rect.size());

      ensure_bitmap_data(m_sizeBitmap, false);

      if(!m_memorymapBitmap.is_mapped())
         return;

      sync_lock ml(m_pmutexBitmap);

      m_pimage = create_image(m_sizeBitmap);

      if (!m_pimage)
      {

         return;

      }

      m_pimage->map();

      ::memcpy_dup(m_pimage->colorref(), m_memorymapBitmap.get_data(), (size_t) (m_pimage->area() * sizeof(color32_t)));

      pgraphics->draw((const POINT32 *) &rectOut, m_sizeBitmap, m_pimage->g());


   }


   void host::translate_mouse_message(int * px, int * py)
   {

   }


   //bool host::get_window_rect(RECT64 * prect)
   //{

   //   ::copy(prect, m_rectWindow);

   //   return true;

   //}


   //bool host::get_client_rect(RECT64 * prect)
   //{

   //   ::copy(prect,m_rectClient);

   //   return true;

   //}


   void host::message_handler(::message::base * pbase)
   {

      if(pbase == nullptr)
         return;

      if(m_pplugin != nullptr)
      {

         m_pplugin->message_handler(pbase);

      }

      ::user::interaction::message_handler(pbase);

   }


   void host::plugin_message_handler(const ::id & id,WPARAM wparam,LPARAM lparam, bool bEnsureTx)

   {

      if(m_pplugin != nullptr)
      {

         m_pplugin->plugin_message_handler(message, wparam, lparam, bEnsureTx);


      }

   }


   void host::plugin_message_handler(MESSAGE * pmsg,bool bEnsureTx)
   {

      if(m_pplugin != nullptr)
      {

         m_pplugin->plugin_message_handler(pmsg, bEnsureTx);

      }

   }



   bool host::hotplugin_host_begin()
   {

      try
      {

         if(!begin())
            return false;

      }
      catch(...)
      {

         return false;

      }


      return true;

   }


   bool host::hotplugin_host_is_initialized()
   {

      return m_bInitialized;

   }


   bool host::hotplugin_host_initialize()
   {

      m_bInitialized = true;

      return true;

   }


   void host::hotplugin_host_on_write()
   {


   }



   //bool host::set_window_pos(class ::user::zorder zorder, i32 x, i32 y, i32 cx, i32 cy, ::u32 nFlags)
   //{

   //   bool bOk = ::hotplugin::plugin::set_window_pos(zorder, x, y, cx, cy, nFlags);

   //   for(index i = 0; i < m_uiptraChild.get_count(); i++)
   //   {

   //      m_uiptraChild[i]->on_layout(::draw2d::graphics_pointer & pgraphics);

   //   }

   //   try
   //   {

   //      if(m_pplugin != nullptr)
   //      {

   //         m_pplugin->set_window_pos(zorder, x, y, cx, cy, nFlags);

   //      }

   //   }
   //   catch(...)
   //   {
   //   }

   //   return bOk;

   //}



} // namespace hotplugin


