#pragma once


// circles, chain, daisies, sunflowers
// you need to profile the top start for bergedge
// from profiler in beggining bottom for veriwellfair


namespace aqua
{


   namespace profiler
   {

#ifdef WINDOWS

      extern CLASS_DECL_AQUA i64 g_iFrequency;

#endif

      CLASS_DECL_AQUA void initialize();

      CLASS_DECL_AQUA i64 micros();


      inline float millis()
      {

         return micros() / 1000.0f;

      }


      CLASS_DECL_AQUA int profile_sleep();

   }


} // namespace aqua




