//
// enum_alignment and enum_orientation From Layout.h by camilo on 2022-09-08 23:57 <3ThomasBorregaardSørensen!!
//
#pragma once



namespace nanoui
{


   /// The different kinds of alignments a layout can perform.
   enum enum_alignment : uint8_t {
      e_alignment_minimum = 0, ///< Take only as much space as is required.
      e_alignment_middle,      ///< Center align.
      e_alignment_maximum,     ///< Take as much space as is allowed.
      e_alignment_fill         ///< Fill according to preferred sizes.
   };

   /// The direction of data flow for a layout.
   enum enum_orientation {
      e_orientation_horizontal = 0, ///< Layout expands on horizontal axis.
      e_orientation_vertical        ///< Layout expands on vertical axis.
   };


} // namespace nanoui



