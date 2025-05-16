#pragma once


#include "aura/graphics/draw2d/pen.h"
#include "object.h"


#define minimum minimum
#define maximum maximum
#include <GdiPlus.h>


namespace draw2d_vulkan
{


   class CLASS_DECL_DRAW2D_VULKAN pen : 
      virtual public ::draw2d_vulkan::object,
      virtual public ::draw2d::pen
   {
   public:


//      plusplus::PenAlignment m_egl2dalign;

      //::plusplus::Pen *  m_ppen;

      pen();
      /*virtual void construct(int nPenStyle, double nWidth, color32_t crColor);
      virtual void construct(int nPenStyle, double nWidth, const LOGBRUSH* pLogBrush, int nStyleCount = 0, const unsigned int* lpStyle = nullptr);
      bool CreatePen(int nPenStyle, double nWidth, color32_t crColor);
      bool CreatePen(int nPenStyle, double nWidth, const LOGBRUSH* pLogBrush, int nStyleCount = 0, const unsigned int* lpStyle = nullptr);*/


      virtual void * get_os_data() const;


      virtual ~pen();
      // void dump(dump_context & dumpcontext) const override;

   };


} // namespace draw2d_vulkan


