#pragma once


#include "aura/graphics/draw2d/pen.h"
#include "object.h"


//#define minimum minimum
// #define maximum maximum
//#include <GdiPlus.h>


namespace draw2d_gpu
{


   class CLASS_DECL_DRAW2D_GPU pen : 
      virtual public ::draw2d_gpu::object,
      virtual public ::draw2d::pen
   {
   public:


//      plusplus::PenAlignment m_egl2dalign;

      //::plusplus::Pen *  m_ppen;

      pen();
      /*virtual void construct(::i32 nPenStyle, ::f64 nWidth, color32_t crColor);
      virtual void construct(::i32 nPenStyle, ::f64 nWidth, const LOGBRUSH* pLogBrush, ::i32 nStyleCount = 0, const ::u32* lpStyle = nullptr);
      bool CreatePen(::i32 nPenStyle, ::f64 nWidth, color32_t crColor);
      bool CreatePen(::i32 nPenStyle, ::f64 nWidth, const LOGBRUSH* pLogBrush, ::i32 nStyleCount = 0, const ::u32* lpStyle = nullptr);*/


      virtual void * get_os_data() const;


      virtual ~pen();
      // void dump(dump_context & dumpcontext) const override;

   };


} // namespace draw2d_gpu


