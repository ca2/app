//
// Created by camilo on 12/04-April/2022. 22:11 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "display.h"
//#include "acme/parallelization/asynchronous.h"
//#include "acme/parallelization/synchronous_lock.h"
#include "acme/prototype/geometry2d/size.h"
#include "acme/platform/system.h"
#include "acme/nano/nano.h"
#include "acme/user/micro/user.h"
#include "acme/platform/node.h"
#include "acme/windowing/windowing.h"


namespace acme
{


   namespace windowing
   {


      display::display() : m_pointCursor2(I32_MINIMUM)

      {


         m_bDisplayOpened = false;

         defer_create_synchronization();

         //m_edisplaytype = e_display_type_none;


      }


      display::~display()
      {


      }


      void display::open_display()
      {


      }


      ::collection::count display::get_monitor_count()
      {


         return 1;


      }




      void display::destroy()
      {

         ::object::destroy();

      }


      void display::kick_idle()
      {


      }


      void display::display_post(const ::procedure& procedure)
      {

         //      synchronous_lock synchronouslock(this->synchronization());

         //      m_procedureaPost.add(procedure);

         //      kick_idle();

         system()->acme_windowing()->main_post(procedure);

      }


      void display::display_send(const ::procedure& procedure)
      {

         //auto bIsCurrentBranch = is_branch_current();

         //__matter_send_procedure(this, this, &display::display_post, procedure);

         system()->acme_windowing()->main_send(procedure);

      }


      // bool display::display_posted_routine_step()
      // {
      //
      //    _synchronous_lock synchronouslock(this->synchronization());
      //
      //    if (m_procedureaPost.has_element())
      //    {
      //
      //       auto function = m_procedureaPost.pick_first();
      //
      //       if (function)
      //       {
      //
      //          synchronouslock.unlock();
      //
      //          function();
      //
      //          return true;
      //
      //       }
      //
      //    }
      //
      //    return false;
      //
      // }


      ::int_size display::get_main_screen_size()
      {

         return {800, 600};

      }


      //      enum_display_type display::get_display_type()
      //      {
      //
      //         return m_edisplaytype;
      //
      //      }
      //
      //
      //      void display::initialize_display_type(enum_display_type edisplaytype)
      //      {
      //
      //         m_edisplaytype = edisplaytype;
      //
      //      }


      void* display::raw_x11_display()
      {

         return nullptr;

      }


      // void display::release_mouse_capture()
      // {
      //
      //
      // }


      string_array display::get_wallpaper()
      {

         auto psession = session();

         ::collection::count iMonitorCount = get_monitor_count();

         string_array stra;

         for (::collection::index iScreen = 0; iScreen < iMonitorCount; iScreen++)
         {

            stra.add(get_wallpaper(iScreen));

         }

         bool bAllEqual = true;

         for (::collection::index iScreen = 1; iScreen < iMonitorCount; iScreen++)
         {

            if (stra[iScreen] != stra[iScreen - 1])
            {

               bAllEqual = false;

            }

         }

         if (bAllEqual && stra.get_count() >= 2)
         {

            stra.set_size(1);

         }

         return stra;

      }


      void display::set_wallpaper(const string_array& straWallpaper)
      {

         if (straWallpaper.is_empty())
         {

            return;

         }

         auto psession = session();

         ::collection::count iMonitorCount = get_monitor_count();

#ifdef LINUX

         if (iMonitorCount > 0)
         {

            set_wallpaper(0, straWallpaper[0]);

         }

#else

      for (::collection::index iScreen = 0; iScreen < iMonitorCount; iScreen++)
      {

         string strWallpaper = iScreen % straWallpaper;

         set_wallpaper(iScreen, strWallpaper);

      }

#endif

      }


      bool display::is_dark_mode_through_theming()
      {

         return false;

      }


      bool display::is_wallpaper_associated_with_dark_mode()
      {

         return false;

      }


      bool display::is_wallpaper_associated_with_theming()
      {

         return false;

      }



      string display::theming_ui_name()
      {

         return "System Theme";

      }



      string display::get_wallpaper(::collection::index iScreen)
      {

         return _get_wallpaper(iScreen);

      }


      string display::_get_wallpaper(::collection::index)
      {

         return "";

      }


      string display::get_desktop_theme()
      {

         return impl_get_desktop_theme();

      }


      string display::impl_get_desktop_theme()
      {

         return "";

      }


      void display::set_desktop_theme(const ::scoped_string & scopedstrTheme)
      {

         impl_set_desktop_theme(scopedstrTheme);

      }


      void display::impl_set_desktop_theme(const ::scoped_string & scopedstrDesktopTheme)
      {

         //return false;

      }


      // todo color:// gradient:// if the operating system doesn't have this, create the file, please.
      void display::_set_wallpaper(::collection::index iMonitorIndex, const ::scoped_string & scopedstrWallpaper)
      {

//         node()->set_wallpaper(iMonitorIndex, scopedstrWallpaper, this);
//         if ()
          //{

         //    return true;

          //}
         //
         //return "";
         //return false;

      }


      void display::set_wallpaper(::collection::index iScreen, const ::scoped_string & scopedstrWallpaper)
      {

         //return "";
         _set_wallpaper(iScreen,scopedstrWallpaper);

      }


      void display::enable_wallpaper_change_notification()
      {


      }


      ::string display::get_desktop_icon_theme()
      {

         return {};

      }


      void display::set_desktop_icon_theme(const ::scoped_string& scopedtrDesktopIconTheme)
      {


      }


   } // namespace windowing


} // namespace acme
