#pragma once


// circles, chain, daisies, sunflowers
// you need to profile the top start for bergedge
// from profiler in beggining bottom for veriwellfair


namespace acme
{


   namespace profiler
   {

#ifdef WINDOWS

      extern CLASS_DECL_ACME i64 g_iFrequency;

#endif

      CLASS_DECL_ACME void initialize();

      CLASS_DECL_ACME i64 micros();


      inline float millis()
      {

         return micros() / 1000.0f;

      }


      CLASS_DECL_ACME int profile_sleep();

   }


} // namespace acme




