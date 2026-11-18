#pragma once

#include "acme/prototype/geometry2d/rectangle_array.h"

namespace image
{
   enum class pixel_usage { unknown, static_source, frame_buffer };

   struct alpha_statistics
   {
      ::u64 transparent = 0;
      ::u64 opaque = 0;
      ::u64 translucent = 0;
      ::u64 opaque_region_pixels = 0;
      ::i32_size size;
      ::i32_point origin;
      // Disjoint, fully opaque rectangles, in logical image coordinates.
      ::rectangle_array_base<::i32> opaque_regions;
      ::u64 total() const { return transparent + opaque + translucent; }
      double opaque_fraction() const { return total() ? (double)opaque / total() : 0.0; }
      double translucent_fraction() const { return total() ? (double)translucent / total() : 0.0; }
      double opaque_region_fraction() const { return total() ? (double)opaque_region_pixels / total() : 0.0; }
      bool fully_opaque() const { return total() && opaque == total(); }
      // Bias diagnostics toward large sources likely to benefit. This is a
      // performance hint, not evidence that drawing a mixed image is incorrect.
      bool optimization_candidate() const
      {
         return total() >= 65536 && (fully_opaque()
            || opaque_region_fraction() >= 0.5
            || (opaque_fraction() >= 0.95 && translucent_fraction() <= 0.01));
      }
   };

   // Reusable, platform-neutral pixel classification cache composed into image
   // metadata. Synchronization remains owned by image, alongside pixel access.
   struct alpha_statistics_cache
   {
      pixel_usage usage = pixel_usage::unknown;
      alpha_statistics statistics;
      bool valid = false;
      bool candidate_reported = false;
   };
}
