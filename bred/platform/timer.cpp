// Transferred from SceneFoundry_opengl_pbr_renderer/Timer by
// camilo <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "timer.h"


namespace bred
{


   Timer::Timer() 
   {
      
      start = std::chrono::steady_clock::now(); 
   
   }

   void Timer::logDifference(const ::scoped_string &logText)
   {
      auto stop = std::chrono::steady_clock::now();
      auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
      ::information() << logText << " [" << diff << " ms]";
   }

} // namespace bred

