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

      void DrawAndFillBeziers(
      ::draw2d::graphics_pointer & pgraphics,
      POINT32 *             ppoints,

      i32                  iCount,
      double               dRateX,
      POINT32 *               ppointOffset);


      void DrawBeziers(
      ::draw2d::graphics_pointer & pgraphics,
      POINT32 *             ppoints,

      i32                  iCount,
      double               dRateX,
      POINT32 *               ppointOffset);


      void DrawAndFillBeziers(
      ::draw2d::graphics_pointer & pgraphics,
      array<point_array, point_array &> *
      pglyph,

      double               dRateX,
      POINT32 *               ppointOffset);


      void EmbossedTextOut(
      ::draw2d::graphics_pointer & pgraphics,
      const rect &               pcrect,

      double               dRateX,
      double               dHeight,
      const char *         psz);

      void EmbossedTextOut(
      ::draw2d::graphics_pointer & pgraphics,
      const rect &               pcrect,

      double               dRateX,
      double               dHeight,
      const char *         psz,
      LPINT                  piCharsPositions,

      i32                  iCharsPositions,
      i32                  iOffset);

      void EmbossedTextOut(
      ::draw2d::graphics_pointer & pgraphics,
      const char *      pcsz,

      i32               iLeft,
      i32               iTop,
      i32               iWidht,
      color32_t          crText,
      color32_t          crOutline,
      i32               iLen);


      void SimpleTextOut(
      ::draw2d::graphics_pointer & pgraphics,
      const rect &            pcrect,

      double            dRateX,
      double            dHeight,
      const char *      psz,
      LPINT               piCharsPositions,

      i32               iCharsPositions,
      i32               iOffset);


   };


} // namespace draw2d



