#pragma once


namespace draw2d
{


   class CLASS_DECL_AXIS water_routine
   {
   public:
      
      
      i32            m_iWidth;
      i32            m_iHeight;
      bool           m_bDrawWithLight;
      i32            m_iLightModifier;
      i32            m_iHpage;// The current heightfield
      i32            m_density;// The water density - can machine the density...
      //  the height fields
      i32*            m_iHeightField1;
      i32*            m_iHeightField2;

      
      water_routine();
      virtual ~water_routine();


      void create(i32 iWidth, i32 iHeight);
      void to(::color32_t * pSrcImage, ::color32_t * pTargetImage);

      
      void CalcWater(i32 npage, i32 density);
      void SmoothWater(i32 npage);
      void FlattenWater();

      
      void SineBlob(i32 x, i32 y, i32 radius, i32 height, i32 page);
      void WarpBlob(i32 x, i32 y, i32 radius, i32 height, i32 page);
      void HeightBox (i32 x, i32 y, i32 radius, i32 height, i32 page);
      void HeightBlob(i32 x, i32 y, i32 radius, i32 height, i32 page);
      void CalcWaterBigFilter(i32 npage, i32 density);

      
      void DrawWaterNoLight(i32 page, ::color32_t * pSrcImage, ::color32_t * pTargetImage);
      void DrawWaterWithLight(i32 page, i32 LightModifier, ::color32_t * pSrcImage, ::color32_t * pTargetImage);
      ::color32_t GetShiftedColor(::color32_t color,i32 shift);


   };


} // namespace draw2d



