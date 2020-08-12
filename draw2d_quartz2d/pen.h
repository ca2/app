#pragma once



namespace draw2d_quartz2d
{
   
   
   class CLASS_DECL_DRAW2D_QUARTZ2D pen :
      virtual public ::draw2d_quartz2d::object,
      virtual public ::draw2d::pen
   {
   public:
      
      
      
      //i32                  m_iStock;
      //i32                  m_iStyle;
      //i32                  m_iWidth;
      //COLORREF             m_color;
      
      
      pen();
      virtual ~pen();
      /*virtual void construct(i32 nPenStyle, double nWidth, COLORREF crColor);
       virtual void construct(i32 nPenStyle, double nWidth, const LOGBRUSH* pLogBrush, i32 nStyleCount = 0, const DWORD* lpStyle = nullptr);
       bool CreatePen(i32 nPenStyle, double nWidth, COLORREF crColor);
       bool CreatePen(i32 nPenStyle, double nWidth, const LOGBRUSH* pLogBrush, i32 nStyleCount = 0, const DWORD* lpStyle = nullptr);*/
      
      
      //      virtual void * get_os_data() const;
      
      virtual void dump(dump_context & dumpcontext) const;
      
   };
   
   
} // namespace draw2d_quartz2d





