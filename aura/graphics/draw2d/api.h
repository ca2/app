#pragma once


namespace draw2d
{


   class CLASS_DECL_AURA api :
      virtual public ::object
   {
   public:


      api();
      virtual ~api();


      bool open();

      bool close();

      void draw_and_fill_beziers(
      ::draw2d::graphics_pointer &  pgraphics,
      ::pointd *                    ppoints,
      i32                           iCount,
      double                        dRateX,
      ::pointd *                    ppointOffset);


      void draw_beziers(
      ::draw2d::graphics_pointer &  pgraphics,
      ::pointd *                    ppoints,
      i32                           iCount,
      double                        dRateX,
      ::pointd *                    ppointOffset);


      void draw_and_fill_beziers(
      ::draw2d::graphics_pointer &  pgraphics,
      array < pointd_array, pointd_array & > * pglyph,
      double                        dRateX,
      pointd *                      ppointOffset);


      void embossed_text_out(
      ::draw2d::graphics_pointer &  pgraphics,
      const rectd &                 pcrect,
      double                        dRateX,
      double                        dHeight,
      const char *                  psz);


      void embossed_text_out(
      ::draw2d::graphics_pointer &  pgraphics,
      const rectd &                 pcrect,
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
      color32_t                     crText,
      color32_t                     crOutline,
      i32                           iLen);


      void simple_text_out(
      ::draw2d::graphics_pointer &  pgraphics,
      const rectd &                 pcrect,
      double                        dRateX,
      double                        dHeight,
      const char *                  psz,
      int *                         piCharsPositions,
      i32                           iCharsPositions,
      i32                           iOffset);


   };


} // namespace draw2d



