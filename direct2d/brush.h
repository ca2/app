#pragma once


namespace draw2d_direct2d
{


   class CLASS_DECL_DRAW2D_DIRECT2D brush :
      virtual public ::draw2d_direct2d::object,
      virtual public ::draw2d::brush
   {
   public:


      //      Gdiplus::Brush * m_pbrush;


      Microsoft::WRL::ComPtr<ID2D1Brush>                 m_pbrush;
      Microsoft::WRL::ComPtr<ID2D1SolidColorBrush>       m_psolidbrush;
      Microsoft::WRL::ComPtr<ID2D1LinearGradientBrush>   m_plineargradientbrush;
      Microsoft::WRL::ComPtr<ID2D1RadialGradientBrush>   m_pradialgradientbrush;
      Microsoft::WRL::ComPtr<ID2D1ImageBrush>            m_pimagebrush;


      brush();
      virtual ~brush();


      virtual void destroy() override;
      virtual bool create(::draw2d::graphics * pgraphics, i8 iCreate) override;

      //virtual ID2D1Brush * get_os_brush(::draw2d_direct2d::graphics * pgraphics) const;

      //bool CreateSolidBrush(color32_t crColor);
      //bool CreateHatchBrush(int nIndex, color32_t crColor);
      //bool CreatePatternBrush(::draw2d::bitmap* pBitmap);
      //bool CreateDIBPatternBrush(HGLOBAL hPackedDIB, ::u32 nUsage);
      //bool CreateDIBPatternBrush(const void * lpPackedDIB, ::u32 nUsage);
      //bool CreateSysColorBrush(int nIndex);


      //bool destroy();

      virtual void dump(dump_context & dumpcontext) const;
   };


} // namespace draw2d_direct2d



