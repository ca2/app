#pragma once

#include <cmath>

namespace nano2d
{

   // Geometry emulation for circles only, not a backend pen-alignment mode.
   enum enum_circle_stroke_align
   {
      e_circle_stroke_align_center,
      e_circle_stroke_align_inset,
      e_circle_stroke_align_outset,
   };

   inline float geometry_aligned_circle_radius(float radius, float width,
                                               enum_circle_stroke_align alignment)
   {
      if (!std::isfinite(radius) || !std::isfinite(width) || radius <= 0.f || width <= 0.f)
      {
         return 0.f;
      }

      switch (alignment)
      {
      case e_circle_stroke_align_center:
         return radius;
      case e_circle_stroke_align_inset:
         // A collapsed centerline cannot represent an inset circle stroke.
         return radius > width * 0.5f ? radius - width * 0.5f : 0.f;
      case e_circle_stroke_align_outset:
      {
         const float adjusted = radius + width * 0.5f;
         return std::isfinite(adjusted) ? adjusted : 0.f;
      }
      default:
         return 0.f;
      }
   }

}
