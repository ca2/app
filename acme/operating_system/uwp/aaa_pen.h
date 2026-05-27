#pragma once


namespace universal_windows
{


   class CLASS_DECL_ACME pen :
      virtual public ::UNIVERSAL_WINDOWS::graphics_object,
      virtual public ::ca2::pen
   {
   public:


      //ID2D1SolidColorBrush *  m_psolidbrush;

      ID2D1ImageBrush *    m_pimagebrush;

      bool                 m_bMetroColor;
      color32_t             m_colorMetro;

      pen(::ca2::application * papp);
      /*virtual void construct(::i32 nPenStyle, ::f64 nWidth, color32_t crColor);
      virtual void construct(::i32 nPenStyle, ::f64 nWidth, const LOGBRUSH* pLogBrush, ::i32 nStyleCount = 0, const ::u32* lpStyle = nullptr);
      bool CreatePen(::i32 nPenStyle, ::f64 nWidth, color32_t crColor);
      bool CreatePen(::i32 nPenStyle, ::f64 nWidth, const LOGBRUSH* pLogBrush, ::i32 nStyleCount = 0, const ::u32* lpStyle = nullptr);*/

      virtual bool create_solid(::ca2::graphics * pgraphics, ::f64 dWidth, color32_t crColor);

      virtual ID2D1Brush * get_os_pen_brush(::UNIVERSAL_WINDOWS::graphics * pdc) const;


      bool destroy();

      virtual ~pen();
      // void dump(dump_context & dumpcontext) const override;

   };

} // namespace universal_windows
