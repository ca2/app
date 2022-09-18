//
// Alignment and Orientation From Layout.h by camilo on 2022-09-08 23:57 <3ThomasBorregaardSorensen!!
//
#pragma once



namespace nanogui
{


/// The different kinds of alignments a layout can perform.
   enum class Alignment : uint8_t
   {
      Minimum = 0, ///< Take only as much space as is required.
      Middle,      ///< Center align.
      Maximum,     ///< Take as much space as is allowed.
      Fill         ///< Fill according to preferred sizes.
   };

/// The direction of data flow for a layout.
   enum class Orientation
   {
      Horizontal = 0, ///< Layout expands on horizontal axis.
      Vertical        ///< Layout expands on vertical axis.
   };


} // namespace nanogui


