#include "framework.h"
#include "graphics.h"


namespace draw2d
{

   ID2D1Factory1 * device_lock::g_pfactory = nullptr;


   ::mutex * lock::g_pmutex = nullptr;

} // namespace draw2d

