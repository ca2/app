#pragma once


namespace draw2d_direct2d
{


   class CLASS_DECL_DRAW2D_DIRECT2D pen :
      virtual public ::draw2d_direct2d::object,
      virtual public ::draw2d::pen
   {
   public:


      Microsoft::WRL::ComPtr<ID2D1SolidColorBrush>    m_pbrush;
      bool                                            m_bMetroColor;
      color32_t                                        m_crMetro;


      pen();
      virtual ~pen();



      virtual void destroy() override;
      virtual bool create(::draw2d::graphics * pgraphics, i8 iCreate) override;

      /*virtual void construct(int nPenStyle, double nWidth, color32_t crColor);
      virtual void construct(int nPenStyle, double nWidth, const LOGBRUSH* pLogBrush, int nStyleCount = 0, const ::u32* lpStyle = nullptr);
      bool CreatePen(int nPenStyle, double nWidth, color32_t crColor);
      bool CreatePen(int nPenStyle, double nWidth, const LOGBRUSH* pLogBrush, int nStyleCount = 0, const ::u32* lpStyle = nullptr);*/

      //virtual bool create_solid(::draw2d::graphics * pgraphics, double dWidth, color32_t crColor);

      //virtual ID2D1Brush * get_os_pen_brush(::draw2d_direct2d::graphics * pgraphics) const;


      //bool destroy();

      virtual void dump(dump_context & dumpcontext) const;

      static HRESULT s_RenderPatternToCommandList(ID2D1RenderTarget * pgraphics,D2D1_COLOR_F *pcr);
      static HRESULT s_CreatePatternBrush(ID2D1DeviceContext *pDeviceContext, D2D1_COLOR_F * pcr, ID2D1ImageBrush **ppImageBrush);


   };

} // namespace draw2d_direct2d