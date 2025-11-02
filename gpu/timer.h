// Transferred from SceneFoundry_opengl_pbr_renderer/Timer by
// camilo <3ThomasBorregaardSorensen!!
#pragma once

#include <chrono>


namespace gpu
{
   /**
    * Class for timing anything.
    */
   class CLASS_DECL_GPU Timer
   {
   public:
      
      Timer();
      
      void logDifference(const ::scoped_string &logText);

      std::chrono::steady_clock::time_point start;

   };


} // namespace gpu



