#pragma once


namespace draw2d
{


   class CLASS_DECL_AXIS water_routine
   {
   public:
      
      
      int                        m_iWidth;
      int                        m_iHeight;
      bool                       m_bDrawWithLight;
      int                        m_iLightModifier;
      int                        m_iHpage;// The current heightfield
      int                        m_density;// The water density - can machine the density...
      //  the height fields
      int*                       m_iHeightField1;
      int*                       m_iHeightField2;
      struct color_indexes       m_colorindexes;

      
      water_routine();
      virtual ~water_routine();


      struct color_indexes color_indexes() const { return m_colorindexes; }


      void create(int iWidth, int iHeight, struct color_indexes indexes);
      void to(::image32_t * pSrcImage, ::image32_t * pTargetImage);




      
      void CalcWater(int npage, int density);
      void SmoothWater(int npage);
      void FlattenWater();

      
      void SineBlob(int x, int y, int radius, int height, int page);
      void WarpBlob(int x, int y, int radius, int height, int page);
      void HeightBox (int x, int y, int radius, int height, int page);
      void HeightBlob(int x, int y, int radius, int height, int page);
      void CalcWaterBigFilter(int npage, int density);

      
      void DrawWaterNoLight(int page, ::image32_t * pSrcImage, ::image32_t * pTargetImage);
      void DrawWaterWithLight(int page, int LightModifier, ::image32_t * pSrcImage, ::image32_t * pTargetImage);
      ::image32_t GetShiftedColor(::image32_t color,int shift);


   };


} // namespace draw2d



