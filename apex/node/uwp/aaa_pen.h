#pragma once


namespace universal_windows
{


   class CLASS_DECL_APEX pen :
      virtual public ::_UWP::graphics_object,
      virtual public ::ca2::pen
   {
   public:


      //ID2D1SolidColorBrush *  m_psolidbrush;

      ID2D1ImageBrush *    m_pimagebrush;

      bool                 m_bMetroColor;
      color32_t             m_colorMetro;

      pen(::ca2::application * papp);
      /*virtual void construct(int nPenStyle, double nWidth, color32_t crColor);
      virtual void construct(int nPenStyle, double nWidth, const LOGBRUSH* pLogBrush, int nStyleCount = 0, const ::u32* lpStyle = nullptr);
      bool CreatePen(int nPenStyle, double nWidth, color32_t crColor);
      bool CreatePen(int nPenStyle, double nWidth, const LOGBRUSH* pLogBrush, int nStyleCount = 0, const ::u32* lpStyle = nullptr);*/

      virtual bool create_solid(::ca2::graphics * pgraphics, double dWidth, color32_t crColor);

      virtual ID2D1Brush * get_os_pen_brush(::_UWP::graphics * pdc) const;


      bool destroy();

      virtual ~pen();
      void dump(dump_context & dumpcontext) const override;

   };

} // namespace universal_windows
