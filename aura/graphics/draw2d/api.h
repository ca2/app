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
      ::double_point *                    ppoints,
      int                           iCount,
      double                        dRateX,
      ::double_point *                    ppointOffset);


      void draw_beziers(
      ::draw2d::graphics_pointer &  pgraphics,
      ::double_point *                    ppoints,
      int                           iCount,
      double                        dRateX,
      ::double_point *                    ppointOffset);


      void draw_and_fill_beziers(
      ::draw2d::graphics_pointer &  pgraphics,
      array < double_point_array, double_point_array & > * pglyph,
      double                        dRateX,
      double_point *                      ppointOffset);


      void embossed_text_out(
      ::draw2d::graphics_pointer &  pgraphics,
      const double_rectangle &                 pcrect,
      double                        dRateX,
      double                        dHeight,
      const ::scoped_string & scopedstr);


      void embossed_text_out(
      ::draw2d::graphics_pointer &  pgraphics,
      const double_rectangle &                 pcrect,
      double                        dRateX,
      double                        dHeight,
      const char *                  psz,
      int *                         piCharsPositions,
      int                           iCharsPositions,
      int                           iOffset);


      void embossed_text_out(
      ::draw2d::graphics_pointer &  pgraphics,
      const char *                  pcsz,
      int                           iLeft,
      int                           iTop,
      int                           iWidth,
      ::color::color                     crText,
      ::color::color                     crOutline,
      int                           iLen);


      void simple_text_out(
      ::draw2d::graphics_pointer &  pgraphics,
      const double_rectangle &                 pcrect,
      double                        dRateX,
      double                        dHeight,
      const char *                  psz,
      int *                         piCharsPositions,
      int                           iCharsPositions,
      int                           iOffset);


   };


} // namespace draw2d



