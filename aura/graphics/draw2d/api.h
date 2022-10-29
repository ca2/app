#pragma once


#include "acme/primitive/geometry2d/_collection_basic.h"
#include "acme/primitive/primitive/object.h"


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
      ::point_f64 *                    ppoints,
      i32                           iCount,
      double                        dRateX,
      ::point_f64 *                    ppointOffset);


      void draw_beziers(
      ::draw2d::graphics_pointer &  pgraphics,
      ::point_f64 *                    ppoints,
      i32                           iCount,
      double                        dRateX,
      ::point_f64 *                    ppointOffset);


      void draw_and_fill_beziers(
      ::draw2d::graphics_pointer &  pgraphics,
      array < point_f64_array, point_f64_array & > * pglyph,
      double                        dRateX,
      point_f64 *                      ppointOffset);


      void embossed_text_out(
      ::draw2d::graphics_pointer &  pgraphics,
      const rectangle_f64 &                 pcrect,
      double                        dRateX,
      double                        dHeight,
      const ::string & str);


      void embossed_text_out(
      ::draw2d::graphics_pointer &  pgraphics,
      const rectangle_f64 &                 pcrect,
      double                        dRateX,
      double                        dHeight,
      const char *                  psz,
      int *                         piCharsPositions,
      i32                           iCharsPositions,
      i32                           iOffset);


      void embossed_text_out(
      ::draw2d::graphics_pointer &  pgraphics,
      const char *                  pcsz,
      i32                           iLeft,
      i32                           iTop,
      i32                           iWidth,
      ::color::color                     crText,
      ::color::color                     crOutline,
      i32                           iLen);


      void simple_text_out(
      ::draw2d::graphics_pointer &  pgraphics,
      const rectangle_f64 &                 pcrect,
      double                        dRateX,
      double                        dHeight,
      const char *                  psz,
      int *                         piCharsPositions,
      i32                           iCharsPositions,
      i32                           iOffset);


   };


} // namespace draw2d



