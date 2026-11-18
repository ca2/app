#include "../graphics_configuration.h"
#include <cassert>
#include <iostream>

int main()
{
   using namespace aura::graphics_configuration;
   assert(gpu_api("", "") == "opengl");
   assert(gpu_api("", " GPU_VULKAN\r\n") == "vulkan");
   assert(output("", "") == "off_screen");
   assert(output("", " swap_chain ") == "on_screen");
   for (auto gpu : {"opengl", "vulkan", "directx11", "directx12"})
   {
      for (bool memory : {true, false})
      {
         auto mode = memory ? "off_screen" : "on_screen";
         // Deliberately contradictory saved settings must not override the app.
         assert(gpu_api(gpu, gpu == std::string("opengl") ? "vulkan" : "opengl") == gpu);
         assert(output(mode, memory ? "on_screen" : "off_screen") == mode);
         auto available = draw2d_apis(gpu, memory, true, false);
         assert(draw2d_api("", available) == gpu);
         assert(draw2d_api("unsupported", available) == gpu);
         auto alternative = gpu == std::string("opengl") ? "nanovg" :
            gpu == std::string("vulkan") ? "vkvg" :
            gpu == std::string("directx11") ? "direct2d_for_directx11" : "direct2d_for_directx12";
         assert(draw2d_api(alternative, available) == alternative);
         assert(draw2d_api("draw2d_" + std::string(alternative), available) == alternative);
         assert(draw2d_api("gdiplus", available) == (memory ? "gdiplus" : gpu));
      }
   }
   assert(draw2d_api("nanovg", draw2d_apis("vulkan", true, true, false)) == "vulkan");
   assert(draw2d_api("vkvg", draw2d_apis("opengl", false, true, false)) == "opengl");
   assert(draw2d_api("direct2d_for_directx12", draw2d_apis("directx11", false, true, false)) == "directx11");
   assert(draw2d_api("cairo", draw2d_apis("vulkan", true, false, false)) == "cairo");
   assert(draw2d_api("quartz2d", draw2d_apis("opengl", true, false, true)) == "quartz2d");
   std::cout << "PASS: override priority, file defaults, all eight fuel variants, compatible draw2d choices\n";
}
