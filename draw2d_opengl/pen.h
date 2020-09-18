#pragma once



#undef new
#define min min
#define max max
#include <GdiPlus.h>


namespace draw2d_opengl
{


   class CLASS_DECL_DRAW2D_OPENGL pen : 
      virtual public ::draw2d_opengl::object,
      virtual public ::draw2d::pen
   {
   public:


//      plusplus::PenAlignment m_egl2dalign;

      //::plusplus::Pen *  m_ppen;

      pen();
      /*virtual void construct(i32 nPenStyle, double nWidth, COLORREF crColor);
      virtual void construct(i32 nPenStyle, double nWidth, const LOGBRUSH* pLogBrush, i32 nStyleCount = 0, const DWORD* lpStyle = nullptr);
      bool CreatePen(i32 nPenStyle, double nWidth, COLORREF crColor);
      bool CreatePen(i32 nPenStyle, double nWidth, const LOGBRUSH* pLogBrush, i32 nStyleCount = 0, const DWORD* lpStyle = nullptr);*/


      virtual void * get_os_data() const;


      virtual ~pen();
      virtual void dump(dump_context & dumpcontext) const;

   };


} // namespace draw2d_opengl


