#include "framework.h"
#include "environment.h"



CLASS_DECL_ACME bool is_wayland()
{

   return std::getenv("WAYLAND_DISPLAY") != nullptr;

}


CLASS_DECL_ACME bool is_x11()
{

   return std::getenv("DISPLAY") != nullptr &&
          std::getenv("WAYLAND_DISPLAY") == nullptr;

}




