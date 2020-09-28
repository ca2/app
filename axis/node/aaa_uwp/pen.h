#pragma once


namespace uwp
{


   class CLASS_DECL_AXIS pen :
      virtual public ::_UWP::graphics_object,
      virtual public ::ca2::pen
   {
   public:


      //ID2D1SolidColorBrush *  m_psolidbrush;

      ID2D1ImageBrush *    m_pimagebrush;

      bool                 m_bMetroColor;
      COLORREF             m_crMetro;

      pen(::ca2::application * papp);
      /*virtual void construct(int nPenStyle, double nWidth, COLORREF crColor);
      virtual void construct(int nPenStyle, double nWidth, const LOGBRUSH* pLogBrush, int nStyleCount = 0, const DWORD* lpStyle = nullptr);
      bool CreatePen(int nPenStyle, double nWidth, COLORREF crColor);
      bool CreatePen(int nPenStyle, double nWidth, const LOGBRUSH* pLogBrush, int nStyleCount = 0, const DWORD* lpStyle = nullptr);*/

      virtual bool create_solid(::ca2::graphics * pgraphics, double dWidth, COLORREF crColor);

      virtual ID2D1Brush * get_os_pen_brush(::_UWP::graphics * pdc) const;


      bool destroy();

      virtual ~pen();
      virtual void dump(dump_context & dumpcontext) const;

   };

} // namespace uwp