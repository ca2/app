// From ProfileLogger by camilo on 2026-04-25 03:51 <3ThomasBorregaardSørensen!!, Mummi!!, Bilbo!!
#include "framework.h"
#include "acme/platform/ProfileLogger.h"

//#include <algorithm>
//#include <numeric>
//#include <utility>
///#include "thread/AutoLock.h"
#include "acme/operating_system/GetCPUTime.h"

// does not works on XP
// #include "Realtimeapiset.h"

namespace platform
{


   static ProfileLogger * g_pprofilerlogger = nullptr;


   ProfileLogger::ProfileLogger()
   {

      if (g_pprofilerlogger)
      {

         throw "there should be only one ProfileLogger in the process";

      }

      g_pprofilerlogger = this;

      m_dropRate = 5.;

      m_lastDrop = ::time::now();

   }


   ProfileLogger::~ProfileLogger()
   {

      g_pprofilerlogger = nullptr;

   }


   ProcessorTimes ProfileLogger::checkPoint(const char *description)
   {
      critical_section_lock al(&m_criticalsection);

      /*
      try {
        QueryProcessCycleTime(GetCurrentProcess(), &m_last.m_cycle);
      }
      catch (...) {
        m_lastCycle = 0;
      }*/
      ProcessorTimes t;
      t.m_cycle = m_last.m_cycle;
      m_last.m_cycle = rdtsc();
      t.m_cycle = m_last.m_cycle - t.m_cycle;

      t.m_process = m_last.m_process;
      m_last.m_process = getCPUTime();
      t.m_process = m_last.m_process - t.m_process;

      t.m_kernel = m_last.m_kernel;
      m_last.m_kernel = getKernelTime();
      t.m_kernel = m_last.m_kernel - t.m_kernel;

      t.m_time = m_last.m_time;
      m_last.m_time.Now();
      t.m_time = m_last.m_time - t.m_time;

      // #if DROP_TIME_STAT  // test code
      m_checkPoints[description].add(m_last);
      // #endif
      return t;
   }


   typedef ::pair<ProcessorTimes, const char *> CHECKPPOINTPAIR;
   typedef ::pair<const char *, const char *> STRINGPAIR;
   // helper function for std::sort
   bool pairCompare(const CHECKPPOINTPAIR &firstElem, const CHECKPPOINTPAIR &secondElem)
   {
      return firstElem.m_element1.m_cycle < secondElem.m_element1.m_cycle;
   }


   ::string printVectorStats(const char *header, const char *tag1, const char *tag2, const double_array &da)
   {
      double min = da.get_minimum_value();
      double max = da.get_maximum_value();
      int num = da.size();
      double avg = da.get_sum() / (double)num;
      ::string str;
      str.formatf("%s for %s - %s distance: avg: %f, min: %f, max: %f, executed %d times\n",
                  header, tag1, tag2, avg, min, max, num);
      //int count = );
      //count++;
      //std::vector<TCHAR> formattedString(count);
      //_stprintf_s(&formattedString.front(), count, fmt, header, tag1, tag2, avg, min, max, num);
      //return formattedString;
      return str;
   }


   ::string_array ProfileLogger::dropStat()
   {
      critical_section_lock al(&m_criticalsection);
      ::string_array resultStrings;
      if (m_checkPoints.size() == 0)
         return resultStrings;
      auto dt = m_lastDrop.elapsed();
      if (dt.floating_second() < m_dropRate)
      {
         return resultStrings;
      }
      m_lastDrop.Now();

      ::array_base<CHECKPPOINTPAIR> checkPointPairs;
      //std::map<const TCHAR *, std::vector<ProcessorTimes>>::iterator i;
      // Build vector with times-description pairs and sort it by times order
      for (auto i = m_checkPoints.begin(); i != m_checkPoints.end(); i++)
      {
         auto &times = (*i).m_element2;
         for (auto t = times.begin(); t != times.end(); t++)
         {
            checkPointPairs.add(CHECKPPOINTPAIR((*t), (*i).m_element1));
         }
      }
      checkPointPairs.predicate_sort([](auto &i1, auto &i2)
      {

         return pairCompare(i1, i2);

      });
      //std::sort(checkPointPairs.begin(), checkPointPairs.end(), );

      if (checkPointPairs.size() == 0)
         return resultStrings;

      // calc deltas for consequent points
      struct ProcessorTimesDeltas
      {
         double_array deltac; // CPU cycles deltas
         double_array deltap; // Process time deltas
         double_array deltak; // Kernel time deltas
      };
      ::map<STRINGPAIR, ProcessorTimesDeltas> deltas;
      auto p = checkPointPairs.begin();
      for (;;)
      {
         auto tag1 = (*p).m_element2;
         ProcessorTimes pt1 = (*p).m_element1;
         ++p;
         if (p == checkPointPairs.end())
            break;
         ProcessorTimes pt2 = (*p).m_element1;
         auto tag2 = (*p).m_element2;
         STRINGPAIR sp = STRINGPAIR(tag1, tag2);
         deltas[sp].deltac.add(double(pt2.m_cycle - pt1.m_cycle) / 1000000.);
         deltas[sp].deltap.add(pt2.m_process - pt1.m_process);
         deltas[sp].deltak.add(pt2.m_kernel - pt1.m_kernel);
      }

      //;
      //;
      //::map<STRINGPAIR, ProcessorTimesDeltas>::iterator d;
      // print results
      for (auto d = deltas.begin(); d != deltas.end(); ++d)
      {
         auto *tag1 = (*d).m_element1.m_element1;
         auto *tag2 = (*d).m_element1.m_element2;
         auto str = printVectorStats("CPU cycles", tag1, tag2, (*d).m_element2.deltac);
         resultStrings.add(str);
         str = printVectorStats("Process times", tag1, tag2, (*d).m_element2.deltap);
         resultStrings.add(str);
         str = printVectorStats("Kernel times", tag1, tag2, (*d).m_element2.deltak);
         resultStrings.add(str);
      }
      m_checkPoints.clear();
      return resultStrings;
   }


} // namespace platform


CLASS_DECL_ACME ::platform::ProfileLogger &ProfileLogger()
{

   return *::platform::g_pprofilerlogger;

}
