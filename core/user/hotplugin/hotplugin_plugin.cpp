#include "framework.h"







#ifdef LINUX
//#include "axis/os/linux/linux_cross_win_gdi_internal.h"
#elif defined(__ANDROID__)
////#include "axis/os/android/android_cross_win_gdi_internal.h"
#endif



#if defined(LINUX) || defined(__ANDROID__) || defined(APPLEOS) || defined(SOLARIS)
iptr get_map_failed();
void my_munmap(void * pimage32,HANDLE hfile);
void * my_open_map(const ::scoped_string & scopedstr,HANDLE * pfile,bool bRead,bool bWrite,::i64 i32_size);
#endif


//void fastblur(::u32 * pdata, ::i32 w, ::i32 h, ::i32 radius);


namespace hotplugin
{


   plugin::plugin()
   {

      m_iDelta = 5000;

      m_puserstyle      = this;
      m_phost           = nullptr;
      m_bInitialized    = false;
      m_bOk             = false;

      m_strStatus       = "Thank you";

      m_bReload         = false;
      m_bInstalling     = false;

      m_pointCursorPhase.x = 0;
      m_pointCursorPhase.y = 0;

      m_etheme = ::user::e_theme_lite;

      //get_app() = this;
      //get_app()->m_psession = this;
      //::aura::application::m_psession = this;

   }


   plugin::~plugin()
   {

      free_memory();

   }


   void plugin::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);
      ::aura::session::install_message_routing(pchannel);

   }

   void plugin::delete_this()
   {

      ::user::interaction::delete_this();

   }


   bool plugin::open_link(const ::scoped_string & scopedstrLink, const ::scoped_string & scopedstrTarget)
   {

      if(m_phost != nullptr)
      {

         return m_phost->open_link(strLink, strTarget);

      }

      return false;

   }


   bool plugin::reload_plugin()
   {
      if(m_phost != nullptr)
      {
         return m_phost->reload_plugin();
      }
      return false;
   }


   void plugin::destroy()
   {

      ::user::interaction::destroy();

      ::berg::session::destroy();

   }


   string plugin::get_host_location_url()
   {

      if(m_phost != nullptr)
      {

         return m_phost->get_host_location_url();

      }

      return "";

   }


   void plugin::redraw()
   {
      if(m_phost != nullptr)
      {
         m_phost->redraw();
      }
   }

   void plugin::post_message(::user::enum_message eusermessage, ::wparam wparam, ::lparam lparam)

   {
      if(m_phost != nullptr)
      {
         m_phost->post_message(eusermessage, wparam, lparam);

      }
   }

   oswindow plugin::get_host_user_interaction()
   {
      if(m_phost != nullptr)
      {
         return m_phost->get_host_user_interaction();
      }
      return nullptr;
   }

   //// ca.dll-absence-(ca.dll-delay-load)-safe
   //void plugin::window_rectangle(::i32_rectangle * prectangle)

   //{

   //   *prectangle = m_rectangle;


   //}

   //void plugin::set_window_rect(const ::i32_rectangle & rectangle)
   //{

   //   m_rectangle = *rectangle;


   //}

   void plugin::set_memory(void * puchMemory, ::collection::count c)
   {
      if(m_phost != nullptr)
      {
         m_phost->set_memory(puchMemory, c);
      }
   }


   void plugin::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      ::user::interaction::handle(ptopic, phandlercontext);

   }


   void plugin::append_memory(void * puchMemory, ::collection::count c)
   {
      if(m_phost != nullptr)
      {
         m_phost->append_memory(puchMemory, c);
      }
   }

   ::collection::count plugin::get_memory_length()
   {
      if(m_phost != nullptr)
      {
         return m_phost->get_memory_length();
      }
      return 0;
   }

   ::collection::count plugin::read_memory(void * puchMemory, ::collection::count c)
   {
      if(m_phost != nullptr)
      {
         return m_phost->read_memory(puchMemory, c);
      }
      return 0;
   }

   void plugin::free_memory()
   {
   }


   void plugin::on_paint(::draw2d::graphics_pointer & pgraphics,const ::i32_rectangle & rectangle)
   {

      on_bare_paint(pgraphics, rectangle);

   }


#ifdef WINDOWS

   /*   LRESULT plugin::message_handler(::user::enum_message eusermessage, ::wparam wparam, ::lparam lparam)

      {
         return 0;
      }*/

#elif defined(LINUX) || defined(SOLARIS)

   ::i32 plugin::x11_message_handler(void  * pevent)
   {
      return 0;
   }

#endif


   ::i32 plugin::start_ca2_system()
   {
      return -1;
   }

   bool plugin::is_ok()
   {
      return m_bOk;
   }

   void plugin::set_ready()
   {

      m_bOk = true;

      if(m_bOk && m_phost != nullptr && m_phost->is_ok())
      {

         on_ready();

      }
      else if(m_phost != nullptr)
      {

#ifdef WINDOWS_DESKTOP

         ::PostMessage(m_phost->::aura::ipc::ipc::m_pacmewindowingwindow, WM_USER + 100, 3, 1);

#else

         throw ::exception(::exception("not implemented"));

#endif

      }

   }

   void plugin::on_ready()
   {
   }

   bool plugin::plugin_initialize()
   {
      return true;
   }

   bool plugin::plugin_finalize()
   {

      plugin_message_handler(::user::e_message_close,0,0,false);

      destroy();

      return true;

   }

   /*::f64 cos_prec_dup(::f64 x,::f64 prec)
   {
   ::f64 t , s ;
   ::i32 i32_point;
   point = 0;
   s = 1.0;
   t = 1.0;
   while(fabs(t/s) > prec)
   {
   i32_point++;
   t = (-t * x * x) / ((2 * i32_point - 1) * (2 * i32_point));
   s += t;
   }
   return s;
   }*/

   ::f64 sin_dup(::f64 x);

   ::f64 cos_dup(::f64 x)
   {

      ::f64 sin = sin_dup(x / 2.0);

      return 1.0 - 2.0 * sin * sin;

   }

   ::f64 sin_dup(::f64 x)
   {

      if(x < 0.0)
      {

         return -sin_dup(-x);

      }
      else if(x < 3.1415 / 16.0)
      {

         ::f64 sin = 0.0;
         ::f64 pow = x;
         ::f64 fact = 1.0;

         for(::f64 d = 0.0; d < 16.0; d += 1.0)
         {
            sin += pow / fact;
            pow *= x * x;
            fact *= (2.0 * (d + 1.0)) * (2.0 * (d + 1.0) + 1.0);
         }

         return sin;

      }
      else
      {

         return 2.0 * sin_dup(x / 2.0) * cos_dup(x / 2.0);

      }

   }

   void plugin::get_progress_color(::u8 & uchR, ::u8 & uchG, ::u8 & uchB, ::f64 dRate, ::i32 iProfile)
   {
      ::f64 dH = dRate; // blue ==> red => green
      ::f64 dL;
      ::f64 dS;

      if(iProfile == 0)
      {
         dL = 0.49;
         dS = 0.77;
      }
      else if(iProfile == 1)
      {
         dL = 0.63;
         dS = 0.84;
      }
      else
      {
         dL = 0.54;
         dS = 0.84;
      }

      {
         if(dH >= 1.0)
            dH = 0.0;
         else if(dH < 0.0)
            dH = 0.0;

         if(dL > 1.0)
            dL = 1.0;
         else if(dL < 0.0)
            dL = 0.0;

         if(dS > 1.0)
            dS = 1.0;
         else if(dS < 0.0)
            dS = 0.0;

         ::f64 dR;
         ::f64 dG;
         ::f64 dB;

         dH *= 6.0;

#if CA2_PLATFORM_VERSION == CA2_BASIS
         dH += 5.0;
#else
         dH += 2.0;
#endif
         if(dH >= 6.0)
            dH -= 6.0;

         ::f64 dA;
         if(dH >= 5.0)
            dA = dH - 5.0;
         else if(dH >= 4.0)
            dA = dH - 4.0;
         else if(dH >= 3.0)
            dA = dH - 3.0;
         else if(dH >= 2.0)
            dA = dH - 2.0;
         else if(dH >= 1.0)
            dA = dH - 1.0;
         else
            dA = dH;

         if(dH >= 3.0)
         {
            if(dH >= 4.0)
            {
               if(dH >= 5.0)
               {
                  // 5.0
                  // magenta to red
                  dR = 1.0;
                  dG = 0.0;
                  dB = 1.0 - dA;
               }
               else
               {
                  // 4.0
                  // blue to magenta
                  dR = dA;
                  dG = 0.0;
                  dB = 1.0;
               }
            }
            else
            {
               // 3.0
               // cyan to blue
               dR = 0.0;
               dG = 1.0 - dA;
               dB = 1.0;
            }
         }
         else /// if(dH >= 0.0)
         {
            if(dH >= 2.0)
            {
               // 2
               // green to cyan
               dR = 0.0;
               dG = 1.0;
               dB = dA;
            }
            else // (dH >= 0.0 && dH < 2.0)
            {
               if(dH >= 1.0)
               {
                  // 1
                  // yellow to green
                  dR = 1.0 - dA;
                  dG = 1.0;
                  dB = 0.0;
               }
               else // if(dh >= 0 && dH < 1.0);
               {
                  // 0
                  // red to yellow
                  dR = 1.0;
                  dG = dA;
                  dB = 0.0;
               }
            }
         }

         ::f64 dCMin;
         ::f64 dCAdd;
         ::f64 dSL = dS * dL;
         if(dL >= 0.5)
         {
            dCMin = dL - dS + dSL;
            dCAdd = 2.0 * dS - 2.0 * dSL;
         }
         else
         {
            dCMin = dL - dSL;
            dCAdd = 2.0 * dSL;
         }


         dR      = (dCMin + dR * dCAdd);
         dG      = (dCMin + dG * dCAdd);
         dB      = (dCMin + dB * dCAdd);

         /*uchR      = (::u8) ftol(dR * 255.0);
         uchG      = (::u8) ftol(dG * 255.0);
         uchB      = (::u8) ftol(dB * 255.0);*/
         uchR      = (::u8) (dR * 255.0);
         uchG      = (::u8) (dG * 255.0);
         uchB      = (::u8) (dB * 255.0);

      }

   }


   void plugin::on_bare_paint(::draw2d::graphics_pointer & pgraphics,const ::i32_rectangle & rectangle)

   {

      if(pgraphics == nullptr)
         return;

      if (m_iHealingSurface == 0)
      {

         on_bare_paint_veri_discreet(pgraphics, rectangle);


      }
      else if(m_iHealingSurface == 1)
      {

         on_bare_paint_discreet(pgraphics, rectangle);


      }
      else
      {

         on_bare_paint_full_screen(pgraphics, rectangle);

      }

   }


   void plugin::start_ca2()
   {
   }

   /*void plugin::free_memory(::u8 ** ppuchMemory)
   {
      host::free_memory(ppuchMemory);
   }*/

   void plugin::set_progress_rate(::f64 dRate)
   {
      if(m_phost != nullptr)
      {
         m_phost->set_progress_rate(dRate);
      }
   }


   ::f64 plugin::get_progress_rate()
   {

      if(m_phost != nullptr)
      {

         return m_phost->get_progress_rate();

      }

      return 0.0;

   }


   ::f64 plugin::extract_spa_progress_rate()
   {

      if (m_phost != nullptr)
      {

         return m_phost->extract_spa_progress_rate();

      }

      return 0.0;

   }


   void plugin::on_update_progress()
   {

      set_progress_rate(extract_spa_progress_rate());

   }


   void plugin::on_paint_progress(::draw2d::graphics_pointer & pgraphics,const ::i32_rectangle & rectangleParam)

   {

      if(m_phost != nullptr && !m_phost->m_bShowProgress)
         return;

      ::i32_rectangle rectangleWindow(rectangleParam);

      ::i32 cx = rectangleWindow.right - rectangleWindow.left;

      ::i32 cy = rectangleWindow.bottom - rectangleWindow.top;

      ::f64 dRate = get_progress_rate();

      ::i32 iLineCount = 25;

      ::i32 x;

      ::i32 y = rectangleWindow.top;

      ::i32 pcx = cx;

      ::i32 pcy = cy / iLineCount;

      ::i32_rectangle rectangleP;

      for(::i32 iLine = 0; iLine < iLineCount; iLine++)
      {

         ::f64 dStart = (::f64) iLine / (::f64) iLineCount;

         ::f64 dEnd = (::f64) (iLine + 1) / (::f64) iLineCount;

         if(dRate <= dEnd)
         {

            if(dRate < dStart)
               x = rectangleWindow.left;
            else
               x = (::i32) (rectangleWindow.left + ((((dRate - dStart) * (::f64) pcx) / (dEnd - dStart))));

            if(iLine >= (iLineCount - 1))
               pcy = rectangleWindow.bottom - y;

            rectangleP.top      = y;

            rectangleP.bottom   = y + pcy;

            rectangleP.left     = x;

            rectangleP.right    = rectangleWindow.right;

            pgraphics->fill_rectangle(rectangleP, argb(90, 90, 90, 80));

         }

         y = y + pcy;

      }

   }


   void plugin::start_plugin()
   {

      if(m_phost != nullptr)
      {
         m_phost->start_plugin();
      }

   }


   void plugin::deferred_prodevian_redraw()
   {

      m_phost->plugin_system_redraw();

   }


   void plugin::plugin_system_redraw()
   {

      if(m_phost != nullptr)
      {
         m_phost->plugin_system_redraw();
      }

   }

   void plugin::set_ca2_installation_ready(bool bReady)
   {

      if(m_phost != nullptr)
      {
         m_phost->set_ca2_installation_ready(bReady);
      }

   }


   void plugin::set_status(const ::scoped_string & scopedstrStatus)
   {

      m_strStatus = pszStatus;

   }


   void plugin::restart_aura_ipc()
   {

      if(m_phost != nullptr && m_phost != this)
      {

         m_phost->restart_aura_ipc();

      }
      else
      {

#ifndef UNIVERSAL_WINDOWS

         ::aura::ipc::ipc::close();

#endif

         m_phost->m_bReload = true;

      }

   }


   void plugin::ensure_bitmap_data(const ::i32_size & size, bool bCreate)
   {

      if (!i32_size)
      {

         return;

      }

      if(m_memorymapBitmap.get_data() == nullptr
            || m_sizeBitmapData != i32_size)
      {

         m_sizeBitmapData = size;

         //m_memB
         //{
         //   my_munmap(m_pcolorref, m_hfileBitmap);
         //   m_pcolorref = (::u32 *)get_map_failed();
         //}

                  auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->create(dir::appdata() / "time" / "aura");

         //::i32 iOpen;

//         if(bCreateFile)
//         {
//#ifdef WINDOWS
//            iOpen = OPEN_ALWAYS;
//#else
//            iOpen = O_RDWR | O_CREAT;
//#endif
//         }
//         else
//         {
//#ifdef WINDOWS
//            iOpen = OPEN_EXISTING;
//#else
//            iOpen = O_RDWR;
//#endif
//         }

         uptr size = m_sizeBitmapData.cx * m_sizeBitmapData.cy * sizeof(color32_t);

         ::file::path pathName = directory()->appdata() / "time" / "aura/app_app_nest-" + m_strBitmapChannel;

         if(!m_memorymapBitmap.open(pathName,true,true,bCreate, size))
         {

            if(bCreate)
            {

               throw ::exception(::exception("resource_exception"));

            }

            return;

         }


         //m_pcolorref = my_open_map(dir::path(dir::appdata("time"),string("aura\\app_app_nest-") + m_strBitmapChannel,&m_hfileBitmap, size);

//#ifdef UNIVERSAL_WINDOWS
//         CREATEFILE2_EXTENDED_PARAMETERS ps;
//         zero(&ps, sizeof(ps));
//         ps.dwSize = sizeof(ps);
//         ps.dwFileAttributes = FILE_ATTRIBUTE_NORMAL;
//         wstring wstr(dir::path(dir::appdata("time"), string("aura\\app_app_nest-") + m_strBitmapChannel));
//         m_hfileBitmap = CreateFile2(wstr, FILE_READ_DATA | FILE_WRITE_DATA, FILE_SHARE_WRITE | FILE_SHARE_READ, iOpen, &ps);
//#elif defined(WINDOWS)
//         wstring wstr(dir::path(dir::appdata("time"), string("aura\\app_app_nest-") + m_strBitmapChannel));
//         m_hfileBitmap = CreateFileW(wstr, FILE_READ_DATA | FILE_WRITE_DATA, FILE_SHARE_WRITE | FILE_SHARE_READ, nullptr, iOpen, FILE_ATTRIBUTE_NORMAL, nullptr);
//#else
//         m_hfileBitmap = ::open(), iOpen, S_IRUSR | S_IWUSR);
//#endif
//
//
//#ifdef WINDOWS
//         ::u32 dwError = get_last_error();
//         if(m_hfileBitmap == INVALID_HANDLE_VALUE)
//#else
//         if(m_hfileBitmap == -1)
//#endif
//         {
//
//            if(bCreateFile)
//            {
//
//               throw ::exception(::exception("resource exception"));
//
//            }
//            else
//            {
//
//               return;
//
//            }
//
//         }
//
//         uptr size = m_sizeBitmapData.cx * m_sizeBitmapData.cy * sizeof(color32_t);
//
//
//#ifdef UNIVERSAL_WINDOWS
//
//         ensure_file_size_handle(m_hfileBitmap, size);
//
//         m_hfilemapBitmap = CreateFileMappingFromApp(
//            m_hfileBitmap,
//            nullptr,
//            PAGE_READWRITE,
//            size,
//            nullptr);
//
//         if(m_hfilemapBitmap == nullptr)
//         {
//            CloseHandle(m_hfileBitmap);
//            m_hfileBitmap = INVALID_HANDLE_VALUE;
//            throw ::exception(::exception("resource exception"));
//         }
//
//#elif defined(WINDOWS)
//
//         ensure_file_size_handle(m_hfileBitmap, size);
//
//         m_hfilemapBitmap = CreateFileMapping(
//            m_hfileBitmap,
//            nullptr,
//            PAGE_READWRITE,
//            0,
//            0,
//            nullptr);
//
//         if(m_hfilemapBitmap == nullptr)
//         {
//            CloseHandle(m_hfileBitmap);
//            m_hfileBitmap = INVALID_HANDLE_VALUE;
//            throw ::exception(::exception("resource exception"));
//         }
//#else
//
//         ensure_file_size_fd(m_hfileBitmap, size);
//
//#endif
//
//#ifdef UNIVERSAL_WINDOWS
//      m_pcolorref = (color32_t *) MapimpactOfFileFromApp(
//         m_hfilemapBitmap,
//         FILE_MAP_READ | FILE_MAP_WRITE,
//         0,
//         0);
//#elif defined(WINDOWS)
//         m_pcolorref = (color32_t *) MapimpactOfFile(
//            m_hfilemapBitmap,
//            FILE_MAP_READ | FILE_MAP_WRITE,
//            0,
//            0,
//            0
//            );
//#else
//         m_pcolorref = (color32_t *) mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, m_hfileBitmap, 0);
//#endif
//
//#ifdef WINDOWS
//         if(m_pcolorref == nullptr)
//#else
//         if(m_pcolorref == MAP_FAILED)
//#endif
//         {
//#ifdef WINDOWS
//            CloseHandle(m_hfilemapBitmap);
//            m_hfilemapBitmap = nullptr;
//            CloseHandle(m_hfileBitmap);
//            m_hfileBitmap = INVALID_HANDLE_VALUE;
//#else
//            ::close(m_hfileBitmap);
//            m_hfileBitmap = -1;
//#endif
//            throw ::exception(::exception("resource exception"));
//         }

         m_pmutexBitmap = ___new ::pointer < ::mutex (e_create_new, false, string("Global\\app_app_nest-") + hex::lower_from( >(iptr)this));

      }


   }

   //bool plugin::client_to_screen(::i32_point * ppt)
   //{

   //   ::user::interaction::client_to_screen(ppt);

   //   return true;

   //}

   //bool plugin::screen_to_client(::i32_point * ppt)
   //{

   //   ::user::interaction::screen_to_client(ppt);

   //   return true;

   //}


   //bool plugin::window_rectangle(::i64_rectangle * prectangle)
   //{

   //   if(m_phost == nullptr)
   //   {

   //      return false;

   //   }

   //   if(!m_phost->window_rectangle(prectangle))
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   //bool plugin::this->rectangle(::i64_rectangle * prectangle)
   //{

   //   if(m_phost == nullptr)
   //   {

   //      return false;

   //   }


   //   if(!m_phost->rectangle(prectangle))
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   void plugin::translate_mouse_message(::i32 * px, ::i32 * py)
   {

      if (m_phost != nullptr)
      {

         m_phost->translate_mouse_message(px, py);

      }

   }


   //bool plugin::show_window(bool bShow)
   //{

   //   if (m_phost != nullptr)
   //   {

   //      return m_phost->show_window(bShow);

   //   }

   //   return false;

   //}


   //bool plugin::destroy_window()
   //{

   //   if (m_phost != nullptr)
   //   {

   //      return m_phost->destroy_window();

   //   }
   //
   //   return true;

   //}


   bool plugin::set_host(::hotplugin::host * phost)
   {

      m_phost = phost;
      set_context_session(m_phost);
      //::aura::application::m_psession = m_phost;

      return true;


   }


   void plugin::on_host_timer()
   {

   }


   void plugin::message_handler(::user::message * pusermessage)
   {

      const ::atom & atom;

      wparam wparam;

      lparam lparam;


      message = (::u32) (LPARAM) pusermessage->id().i64;

      wparam     = pusermessage->m_wparam;

      ::pointer<::message::mouse>spmouse = pusermessage;

      if(spmouse.is_set())
      {

         lparam     = spmouse->m_point.lparam();


      }
      else
      {

         lparam     = pusermessage->m_lparam;


      }

      plugin_message_handler(message, wparam, lparam, true);


   }


   void plugin::plugin_message_handler(::user::enum_message eusermessage, ::wparam wparam, ::lparam lparam, bool bEnsureTx)

   {

      MESSAGE msg;

      zero(msg);

      msg.message = message;

      msg.wParam = wparam;

      msg.lParam = lparam;


      plugin_message_handler(&msg, bEnsureTx);

   }


   void plugin::plugin_message_handler(MESSAGE * pmsg,bool bEnsureTx)
   {

      if(pmsg->message == ::user::e_message_window_position_changed)
         return;

      if(pmsg->message == ::user::e_message_window_position_changing)
         return;

#ifndef UNIVERSAL_WINDOWS

#if !defined(LINUX) && !defined(APPLEOS) && !defined(__ANDROID__)
      if(bEnsureTx || ::IsWindow(::aura::ipc::tx::m_pacmewindowingwindow))
#endif
      {

         ensure_tx(::hotplugin::message_message,pmsg,sizeof(*pmsg));

      }

#endif

   }


} // namespace hotplugin


