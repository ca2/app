#pragma once

#include "acme/prototype/geometry2d/rectangle.h"

namespace accessibility
{
   // Compositor-global logical coordinates, before output scaling.
   struct window_geometry
   {
      ::string m_strWindowId;
      ::i32_rectangle m_rectangleClient;
      ::i32_rectangle m_rectangleFrame;
      ::i32_rectangle m_rectangleOutput;
      double m_dOutputScale = 1.0;
   };
}
