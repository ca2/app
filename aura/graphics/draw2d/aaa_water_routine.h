#pragma once


namespace draw2d
{


   class CLASS_DECL_AURA water_routine
   {
   public:
      water_routine();
      virtual ~water_routine();


      void create(int iWidth,int iHeight);
      void to(color32_t * pSrcImage, color32_t * pTargetImage);

      void CalcWater(int npage, int density);
      void SmoothWater(int npage);
      void FlattenWater();

      void SineBlob(int x, int y, int radius, int height, int page);
      void WarpBlob(int x, int y, int radius, int height, int page);
      void HeightBox (int x, int y, int radius, int height, int page);
      void HeightBlob(int x, int y, int radius, int height, int page);
      void CalcWaterBigFilter(int npage, int density);

      void DrawWaterNoLight(int page, color32_t * pSrcImage, color32_t * pTargetImage);
      void DrawWaterWithLight(int page, int LightModifier, color32_t * pSrcImage, color32_t * pTargetImage);
      color32_t GetShiftedColor(color32_t color,int shift);

      int            m_iWidth;
      int            m_iHeight;
      bool            m_bDrawWithLight;
      int            m_iLightModifier;
      int            m_iHpage;// The current heightfield
      int            m_density;// The water density - can machine the density...
      //  the height fields
      int*            m_iHeightField1;
      int*            m_iHeightField2;


   };


}



