#include "../circle_stroke_alignment.h"
#ifdef NDEBUG
#undef NDEBUG
#endif
#include <cassert>
#include <initializer_list>
#include <limits>
#include <cstdio>

int main()
{
   using namespace nano2d;
   for (float radius : {4.f, 100.f, 175.f})
   {
      for (float width : {1.f, 2.f, 4.f})
      {
         const auto centered = geometry_aligned_circle_radius(radius, width, e_circle_stroke_align_center);
         const auto inset = geometry_aligned_circle_radius(radius, width, e_circle_stroke_align_inset);
         const auto outset = geometry_aligned_circle_radius(radius, width, e_circle_stroke_align_outset);
         assert(centered == radius);
         assert(inset + width / 2 == radius);
         assert(outset - width / 2 == radius);
      }
   }
   assert(geometry_aligned_circle_radius(1.f, 2.f, e_circle_stroke_align_inset) == 0.f);
   assert(geometry_aligned_circle_radius(1.f, 4.f, e_circle_stroke_align_inset) == 0.f);
   assert(geometry_aligned_circle_radius(0.f, 1.f, e_circle_stroke_align_center) == 0.f);
   assert(geometry_aligned_circle_radius(-1.f, 1.f, e_circle_stroke_align_outset) == 0.f);
   assert(geometry_aligned_circle_radius(10.f, 0.f, e_circle_stroke_align_center) == 0.f);
   assert(geometry_aligned_circle_radius(10.f, -1.f, e_circle_stroke_align_outset) == 0.f);
   assert(geometry_aligned_circle_radius(std::numeric_limits<float>::infinity(), 1.f,
                                       e_circle_stroke_align_center) == 0.f);
   assert(geometry_aligned_circle_radius(10.f, std::numeric_limits<float>::quiet_NaN(),
                                       e_circle_stroke_align_outset) == 0.f);
   assert(geometry_aligned_circle_radius(std::numeric_limits<float>::max(),
                                       std::numeric_limits<float>::max(), e_circle_stroke_align_outset) == 0.f);
   std::puts("Circle center/inset/outset boundaries and invalid/collapsed inputs passed.");
}
