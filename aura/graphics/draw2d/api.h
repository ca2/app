#pragma once


#include "acme/prototype/geometry2d/_collection.h"
////#include "acme/prototype/prototype/object.h"


namespace draw2d
{


   class CLASS_DECL_AURA api :
      virtual public ::object
   {
   public:


      api();
      ~api() override;


      void initialize(::particle * pparticle) override;

      void destroy() override;


      void draw_and_fill_beziers(
      ::draw2d::graphics_pointer &  pgraphics,
      ::f64_point *                    ppoints,
      ::i32                           iCount,
      ::f64                        dRateX,
      ::f64_point *                    ppointOffset);


      void draw_beziers(
      ::draw2d::graphics_pointer &  pgraphics,
      ::f64_point *                    ppoints,
      ::i32                           iCount,
      ::f64                        dRateX,
      ::f64_point *                    ppointOffset);


      void draw_and_fill_beziers(
      ::draw2d::graphics_pointer &  pgraphics,
      array < f64_point_array, f64_point_array & > * pglyph,
      ::f64                        dRateX,
      ::f64_point *                      ppointOffset);


      void embossed_text_out(
      ::draw2d::graphics_pointer &  pgraphics,
      const ::f64_rectangle &                 pcrect,
      ::f64                        dRateX,
      ::f64                        dHeight,
      const ::scoped_string & scopedstr);


      void embossed_text_out(
      ::draw2d::graphics_pointer &  pgraphics,
      const ::f64_rectangle &                 pcrect,
      ::f64                        dRateX,
      ::f64                        dHeight,
      const_char_pointer psz,
      ::i32 *                         piCharsPositions,
      ::i32                           iCharsPositions,
      ::i32                           iOffset);


      void embossed_text_out(
      ::draw2d::graphics_pointer &  pgraphics,
      const_char_pointer pcsz,
      ::i32                           iLeft,
      ::i32                           iTop,
      ::i32                           iWidth,
      ::color::color                     crText,
      ::color::color                     crOutline,
      ::i32                           iLen);


      void simple_text_out(
      ::draw2d::graphics_pointer &  pgraphics,
      const ::f64_rectangle &                 pcrect,
      ::f64                        dRateX,
      ::f64                        dHeight,
      const_char_pointer psz,
      ::i32 *                         piCharsPositions,
      ::i32                           iCharsPositions,
      ::i32                           iOffset);


   };


} // namespace draw2d



