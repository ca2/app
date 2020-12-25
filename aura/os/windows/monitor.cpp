#include "framework.h"
#include "_windows.h"
#include <highlevelmonitorconfigurationapi.h>


CLASS_DECL_AURA void black_body(float * r, float * g, float * b, ::u32 dwTemp);


MC_COLOR_TEMPERATURE kelvin_mc_color(::u32 kelvin);

MC_COLOR_TEMPERATURE kelvin_mc_color(::u32 kelvin)
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
   else if (kelvin < 10750)
   {

      return MC_COLOR_TEMPERATURE_10000K;

   }
   else
   {

      return MC_COLOR_TEMPERATURE_11500K;

   }

}






namespace aura
{


   bool session::os_adjust_monitor(index iMonitor, ::u32 dwTemperature, double dBrightness, double dGamma)
   {

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

      sleep(500_ms);

      //MC_COLOR_TEMPERATURE e = kelvin_mc_color(dwTemperature);



      //if (!SetMonitorColorTemperature(monitor.hPhysicalMonitor, e))
      //{

      //   return false;

      //}
      //return true;


      if (!GetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_RED_GAIN, &dwMinGainR, &dwCurGainR, &dwMaxGainR))
      {

         DWORD dwLastError = GetLastError();

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

      if (!GetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_RED_DRIVE, &dwMinDriveR, &dwCurDriveR,
         &dwMaxDriveR))
      {

         return false;

      }

      if (!GetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_GREEN_DRIVE, &dwMinDriveG, &dwCurDriveG,
         &dwMaxDriveG))
      {

         return false;

      }

      if (!GetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_BLUE_DRIVE, &dwMinDriveB, &dwCurDriveB,
         &dwMaxDriveB))
      {

         return false;

      }


      //    SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_RED_GAIN, dwMinGainR);
      //    SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_GREEN_GAIN, dwMinGainG);
      //    SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_BLUE_GAIN, dwMinGainB);
      //SetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_RED_DRIVE, (::u32)(dwMinDriveR + (dwMaxDriveR - dwMinDriveR) * r));
      //SetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_GREEN_DRIVE, (::u32)(dwMinDriveG + (dwMaxDriveG - dwMinDriveG) * g));
      //SetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_BLUE_DRIVE, (::u32)(dwMinDriveB + (dwMaxDriveB - dwMinDriveB) * b));
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


      /* helper macro used in the fill functions */
//#define F(Y, C)  pow(dBrightness * C, 1.0 / dGamma)
#define F(C)  pow(dBrightness * C, 1.0 / dGamma)

      ::u32 dwR = (::u32)(dwMinGainR + (dwMaxGainR - dwMinGainR) * F(fR));
      ::u32 dwG = (::u32)(dwMinGainG + (dwMaxGainG - dwMinGainG) * F(fG));
      ::u32 dwB = (::u32)(dwMinGainB + (dwMaxGainB - dwMinGainB) * F(fB));

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

      if (GetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_RED_DRIVE, &dwMinDriveR, &dwCurDriveR,
         &dwMaxDriveR))
      {

         if (dwCurDriveR != dwMaxDriveR)
         {
            sleep(500_ms);
            SetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_RED_DRIVE, dwMaxDriveR);
            sleep(500_ms);
            bDifferent = true;
         }

      }

      if (GetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_GREEN_DRIVE, &dwMinDriveG, &dwCurDriveG,
         &dwMaxDriveG))
      {

         if (dwCurDriveG != dwMaxDriveG)
         {
            sleep(500_ms);
            SetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_GREEN_DRIVE, dwMaxDriveG);
            sleep(500_ms);
            bDifferent = true;
         }

      }

      if (GetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_BLUE_DRIVE, &dwMinDriveB, &dwCurDriveB,
         &dwMaxDriveB))
      {

         if (dwCurDriveB != dwMaxDriveB)
         {
            sleep(500_ms);
            SetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_BLUE_DRIVE, dwMaxDriveB);
            sleep(500_ms);
            bDifferent = true;
         }

      }

      if (GetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_RED_GAIN, &dwMinGainR, &dwCurGainR, &dwMaxGainR))
      {

         if (dwCurGainR != dwR)
         {
            sleep(500_ms);
            SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_RED_GAIN, dwR);
            sleep(500_ms);
            bDifferent = true;
         }


      }

      if (GetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_GREEN_GAIN, &dwMinGainG, &dwCurGainG, &dwMaxGainG))
      {

         if (dwCurGainG != dwG)
         {
            sleep(500_ms);
            SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_GREEN_GAIN, dwG);
            sleep(500_ms);
            bDifferent = true;
         }

      }

      if (GetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_BLUE_GAIN, &dwMinGainB, &dwCurGainB, &dwMaxGainB))
      {

         if (dwCurGainB != dwB)
         {
            sleep(500_ms);
            SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_BLUE_GAIN, dwB);
            sleep(500_ms);
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
      sleep(500_ms);
   finalize:;
      DestroyPhysicalMonitors(1, &monitor);
      return true;
   error:;
      sleep(500_ms);
      // Close the monitor handles.
      DestroyPhysicalMonitors(1, &monitor);
      return false;

   }


} // namespace aura



