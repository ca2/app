#include "framework.h"


#include "base/node/_node.h"


#ifdef WINDOWS_DESKTOP
//#include "aura/os/windows/windows_system_interaction_impl.h"
#elif defined(_UWP)
#include "aura/os/metrowin/metrowin_user_impl.h"
#endif


//#if !defined(WINDOWS) && !defined(MACOS)
//#include <ft2build.h>
//#include FT_FREETYPE_H
//#endif

CLASS_DECL_BASE void black_body(float * r, float * g, float * b, DWORD dwTemp);


#ifdef WINDOWS_DESKTOP



//#include "base/os/windows/windows_system_interaction_impl.h"


#include <HighLevelMonitorConfigurationAPI.h>

DWORD mc_color_kelvin(MC_COLOR_TEMPERATURE e)
{
   switch (e)
   {
   case MC_COLOR_TEMPERATURE_4000K:
      return 4000;
   case MC_COLOR_TEMPERATURE_5000K:
      return 5000;
   case MC_COLOR_TEMPERATURE_6500K:
      return 6500;
   case MC_COLOR_TEMPERATURE_7500K:
      return 7500;
   case MC_COLOR_TEMPERATURE_8200K:
      return 8200;
   case MC_COLOR_TEMPERATURE_9300K:
      return 9300;
   case MC_COLOR_TEMPERATURE_10000K:
      return 10000;
   case MC_COLOR_TEMPERATURE_11500K:
      return 11500;
   default:
      return 0;
   }
}

MC_COLOR_TEMPERATURE kelvin_mc_color(DWORD kelvin)
{
   if (kelvin < 4500)
   {
      return MC_COLOR_TEMPERATURE_4000K;
   }
   else if (kelvin < 5750)
   {
      return MC_COLOR_TEMPERATURE_5000K;
   }
   else if (kelvin < 7000)
   {
      return MC_COLOR_TEMPERATURE_6500K;
   }
   else if (kelvin < 7850)
   {
      return MC_COLOR_TEMPERATURE_7500K;
   }
   else if (kelvin < 8750)
   {
      return MC_COLOR_TEMPERATURE_8200K;
   }
   else if (kelvin < 9650)
   {
      return MC_COLOR_TEMPERATURE_9300K;
   }
   else if(kelvin < 10750)
   {
      return MC_COLOR_TEMPERATURE_10000K;
   }
   else
   {
      return MC_COLOR_TEMPERATURE_11500K;
   }
}

#elif defined(LINUX)


#endif


namespace base
{



   system::system()
   {


   }


   system::~system()
   {

   }


   ::estatus system::initialize_system(::object * pobjectContext, ::app_core * pappcore)
   {

      auto estatus = ::aura::system::initialize_system(pobjectContext, pappcore);

      if (!estatus)
      {

         return estatus;

      }

      //estatus = ::base::application::initialize(pobjectContext);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //m_strAppId = "base_system";
      //m_strAppName = "base_system";
      //m_strBaseSupportId = "base_system";
      //m_strInstallToken = "base_system";

      create_factory < ::draw2d::icon >();

      g_pszCooperativeLevel = "base";

#if defined(_UWP) || defined(APPLE_IOS) || defined(ANDROID)

      m_possystemwindow = new os_system_window();

#endif

      return estatus;

   }


   void system::term_system()
   {

      //base::application::term_application();
      aura::system::term_system();

   }


   void system::set_active_guie(::user::interaction * pinteraction)
   {

      if (pinteraction == nullptr)
      {

         ::set_active_window(nullptr);

      }
      else
      {

         ::set_active_window(pinteraction->get_wnd()->get_safe_handle());

      }

   }


   void system::set_focus_guie(::user::interaction * pinteraction)
   {

      if (pinteraction == nullptr)
      {

         ::set_focus(nullptr);

         return;

      }


      ::set_focus(pinteraction->get_safe_handle());

      if (pinteraction->get_wnd() != nullptr)
      {

         pinteraction->SetFocus();

      }

      return;

   }


   ::count system::get_monitor_count()
   {

      return ::aura::system::get_monitor_count();

   }


   DWORD system::get_monitor_color_temperature(index iMonitor)
   {

#ifdef _UWP

      return 0;

#elif defined(LINUX)

      return 0;

#elif defined(MACOS)

      return 0;

#elif defined(APPLE_IOS)

      return 0;

#elif defined(ANDROID)

      return 0;

#else

      if (iMonitor < 0)
      {

         return 0;

      }

      if (iMonitor >= m_hmonitora.get_count())
      {

         return 0;

      }

      MC_COLOR_TEMPERATURE e;

      if (!GetMonitorColorTemperature(m_hmonitora[iMonitor], &e))
      {

         return 0;

      }

      return mc_color_kelvin(e);

#endif

   }

   ::mutex g_monitor_adjust;

   bool system::adjust_monitor(index iMonitor, DWORD dwTemperature, double dBrightness, double dGamma)
   {

#ifdef _UWP

      return true;

#elif defined(LINUX)

      return true;

#elif defined(MACOS)

      return true;

#elif defined(APPLE_IOS)

      return true;

#elif defined(ANDROID)

      return true;

#else

      sync_lock sl(&g_monitor_adjust);

      if (iMonitor < 0)
      {

         return 0;

      }

      if (iMonitor >= m_hmonitora.get_count())
      {

         return 0;

      }

      if (dBrightness <= 0.0)
      {

         dBrightness = 0.1;

      }

      if (dBrightness >= 1.0)
      {

         dBrightness = 1.0;

      }

      if (dGamma <= 0.1)
      {

         dGamma = 0.1;

      }

      if (dGamma >= 10.0)
      {

         dGamma = 10.0;

      }


      DWORD dwMinDriveR;
      DWORD dwCurDriveR;
      DWORD dwMaxDriveR;
      DWORD dwMinDriveG;
      DWORD dwCurDriveG;
      DWORD dwMaxDriveG;
      DWORD dwMinDriveB;
      DWORD dwCurDriveB;
      DWORD dwMaxDriveB;
      DWORD dwMinGainR;
      DWORD dwCurGainR;
      DWORD dwMaxGainR;
      DWORD dwMinGainG;
      DWORD dwCurGainG;
      DWORD dwMaxGainG;
      DWORD dwMinGainB;
      DWORD dwCurGainB;
      DWORD dwMaxGainB;

      float fR;
      float fG;
      float fB;

      //dwTemperature = 4000;

      black_body(&fR, &fG, &fB, dwTemperature);

      MC_COLOR_TEMPERATURE e = kelvin_mc_color(dwTemperature);

      HMONITOR hMonitor = nullptr;
      DWORD cPhysicalMonitors;
      LPPHYSICAL_MONITOR pPhysicalMonitors = nullptr;

      // Get the number of physical monitors.
      BOOL bSuccess = GetNumberOfPhysicalMonitorsFromHMONITOR(
                      m_hmonitora[iMonitor],
                      &cPhysicalMonitors
                      );

      if (!bSuccess || cPhysicalMonitors <= 0)
      {

         return 0;

      }

      PHYSICAL_MONITOR monitor;

      bSuccess = GetPhysicalMonitorsFromHMONITOR(m_hmonitora[iMonitor], 1, &monitor);

      Sleep(500);

      //MC_COLOR_TEMPERATURE e = kelvin_mc_color(dwTemperature);



      //if (!SetMonitorColorTemperature(monitor.hPhysicalMonitor, e))
      //{

      //   return false;

      //}
      //return true;


      if (!GetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_RED_GAIN, &dwMinGainR, &dwCurGainR, &dwMaxGainR))
      {

         DWORD dwLastError = get_last_error();

         TRACELASTERROR();

         goto error;

      }

      if (!GetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_GREEN_GAIN, &dwMinGainG, &dwCurGainG, &dwMaxGainG))
      {

         return false;

      }

      if (!GetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_BLUE_GAIN, &dwMinGainB, &dwCurGainB, &dwMaxGainB))
      {

         return false;

      }

      if (!GetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_RED_DRIVE, &dwMinDriveR, &dwCurDriveR, &dwMaxDriveR))
      {

         return false;

      }

      if (!GetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_GREEN_DRIVE, &dwMinDriveG, &dwCurDriveG, &dwMaxDriveG))
      {

         return false;

      }

      if (!GetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_BLUE_DRIVE, &dwMinDriveB, &dwCurDriveB, &dwMaxDriveB))
      {

         return false;

      }


//    SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_RED_GAIN, dwMinGainR);
//    SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_GREEN_GAIN, dwMinGainG);
//    SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_BLUE_GAIN, dwMinGainB);
      //SetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_RED_DRIVE, (DWORD)(dwMinDriveR + (dwMaxDriveR - dwMinDriveR) * r));
      //SetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_GREEN_DRIVE, (DWORD)(dwMinDriveG + (dwMaxDriveG - dwMinDriveG) * g));
      //SetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_BLUE_DRIVE, (DWORD)(dwMinDriveB + (dwMaxDriveB - dwMinDriveB) * b));
      //SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_RED_GAIN, dwMaxGainR);
      //SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_GREEN_GAIN, dwMaxGainG);
      //SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_BLUE_GAIN, dwMaxGainB);
      bool bDifferent = false;
      if (dwMaxDriveR != dwCurDriveR)
      {
         SetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_RED_DRIVE, dwMaxDriveR);
         bDifferent = true;
      }
      if (dwMaxDriveG != dwCurDriveG)
      {
         SetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_GREEN_DRIVE, dwMaxDriveG);
         bDifferent = true;
      }
      if (dwMaxDriveB != dwCurDriveB)
      {
         SetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_BLUE_DRIVE, dwMaxDriveB);
         bDifferent = true;
      }


      /* Helper macro used in the fill functions */
//#define F(Y, C)  pow(dBrightness * C, 1.0 / dGamma)
#define F(C)  pow(dBrightness * C, 1.0 / dGamma)

      DWORD dwR = (DWORD)(dwMinGainR + (dwMaxGainR - dwMinGainR) * F(fR));
      DWORD dwG = (DWORD)(dwMinGainG + (dwMaxGainG - dwMinGainG) * F(fG));
      DWORD dwB = (DWORD)(dwMinGainB + (dwMaxGainB - dwMinGainB) * F(fB));

      if (dwR != dwCurGainR)
      {
         SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_RED_GAIN, dwR);
         bDifferent = true;
      }
      if (dwG != dwCurGainG)
      {
         SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_GREEN_GAIN, dwG);
         bDifferent = true;
      }
      if (dwB != dwCurGainB)
      {
         SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_BLUE_GAIN, dwB);
         bDifferent = true;
      }

#undef F

      if (!bDifferent)
      {

         goto finalize;

      }

      int iRepeat = 0;
repeat:

      bDifferent = false;

      if (GetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_RED_DRIVE, &dwMinDriveR, &dwCurDriveR, &dwMaxDriveR))
      {

         if (dwCurDriveR != dwMaxDriveR)
         {
            Sleep(500);
            SetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_RED_DRIVE, dwMaxDriveR);
            Sleep(500);
            bDifferent = true;
         }

      }

      if (GetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_GREEN_DRIVE, &dwMinDriveG, &dwCurDriveG, &dwMaxDriveG))
      {

         if (dwCurDriveG != dwMaxDriveG)
         {
            Sleep(500);
            SetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_GREEN_DRIVE, dwMaxDriveG);
            Sleep(500);
            bDifferent = true;
         }

      }

      if (GetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_BLUE_DRIVE, &dwMinDriveB, &dwCurDriveB, &dwMaxDriveB))
      {

         if (dwCurDriveB != dwMaxDriveB)
         {
            Sleep(500);
            SetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_BLUE_DRIVE, dwMaxDriveB);
            Sleep(500);
            bDifferent = true;
         }

      }

      if (GetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_RED_GAIN, &dwMinGainR, &dwCurGainR, &dwMaxGainR))
      {

         if (dwCurGainR != dwR)
         {
            Sleep(500);
            SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_RED_GAIN, dwR);
            Sleep(500);
            bDifferent = true;
         }


      }

      if (GetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_GREEN_GAIN, &dwMinGainG, &dwCurGainG, &dwMaxGainG))
      {

         if (dwCurGainG != dwG)
         {
            Sleep(500);
            SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_GREEN_GAIN, dwG);
            Sleep(500);
            bDifferent = true;
         }

      }

      if (GetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_BLUE_GAIN, &dwMinGainB, &dwCurGainB, &dwMaxGainB))
      {

         if (dwCurGainB != dwB)
         {
            Sleep(500);
            SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_BLUE_GAIN, dwB);
            Sleep(500);
            bDifferent = true;
         }

      }

      if (bDifferent)
      {

         iRepeat++;

         if (iRepeat < 3)
         {

            goto repeat;

         }

      }
      Sleep(500);
finalize:
      ;
      DestroyPhysicalMonitors(1, &monitor);
      return true;
error:
      ;
      Sleep(500);
      // Close the monitor handles.
      DestroyPhysicalMonitors(1, &monitor);
      return false;

#endif

   }


   bool system::get_monitor_rect(index iMonitor, RECT * prect)

   {

#ifdef _UWP

      get_window_rect(m_possystemwindow->m_pwindow, prect);


      return true;

#elif defined(LINUX)


      return ::aura::system::get_monitor_rect(iMonitor, prect);

      //return os_get_monitor_rect(iMonitor, prect);



#else

      return ::aura::system::get_monitor_rect(iMonitor, prect);


#endif

   }


   bool system::get_wkspace_rect(index iWkspace, RECT * prect)

   {

      //#ifdef LINUX
      //
      //      xdisplay  d;
      //
      //      if(!d.open(nullptr))
      //         return false;
      //
      //      prect->left = 0;

      //      prect->right = WidthOfScreen(DefaultScreenOfDisplay(d.m_pdata->m_pdisplay));

      //      prect->top = 0;

      //      prect->bottom= HeightOfScreen(DefaultScreenOfDisplay(d.m_pdata->m_pdisplay));

      //
      //      return true;
      //
      //#else

      return ::aura::system::get_wkspace_rect(iWkspace, prect);


      //#endif

   }


   ::estatus system::process_init()
   {


      //::aura::application * papp = ::get_context_application(get_object());

      //if (papp == nullptr)
      //{

      //   set("parent_system") = nullptr;

      //}
      //else
      //{

      //   set("parent_system") = papp->m_psystem;

      //}
//#if !defined(WINDOWS) && !defined(MACOS)
//
//      i32 error = FT_Init_FreeType((FT_Library *)&m_ftlibrary);
//
//      if (error)
//      {
//
//         TRACE("an error occurred during Free Type library initialization");
//
//         return false;
//
//      }
//
//#endif

      //if (m_peengine != nullptr)
      //{

      //   m_peengine = new ::exception::engine(this);

      //}


      //if (!::base::application::process_init())
        // return false;

      if (!::aura::system::process_init())
         return false;


      //create_factory < ::OS::window_buffer >   (__type(::window_graphics));



      //m_spos.create(this);





      return true;

   }


   bool system::initialize_native_window1()
   {

#if !defined(LINUX) && !defined(WINDOWS_DESKTOP) && !defined(MACOS)

      m_possystemwindow->m_puserinteraction = new ::user::interaction(this);

#endif

      return true;

   }



   void system::update(::update * pupdate)
   {

      //::update updateSetting(pupdate);

      //fork([this, updateSetting]
      //     ()
      //     {

      //        ::update update(updateSetting);

      //        __pointer(::user::interaction) pinteraction;

      //        __pointer(::base::session) psession = m_psession;

      //        if(psession == nullptr)
      //        {

      //           return;

      //        }

      //        int iFrame = 0;

      //        while(psession->get_frame(pinteraction))
      //        {

      //           iFrame++;

      //           pinteraction->call_update(pupdate);

      //        }

      //     });

   }

} // namespace base














