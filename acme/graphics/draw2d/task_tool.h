#pragma once


#include "acme/graphics/image/_configuration.h"
#include "acme/parallelization/tools.h"


namespace draw2d
{


   class task_tool_item :
      virtual public ::task_tool_item
   {
   public:


      ///__creatable_from_library(::draw2d::task_tool_item, ::task_tool_item, "draw2d");

      enum e_op
      {

         op_blend,

      };

      ::i32 m_ySkip;
      ::i32 m_y;
      ::i32 m_yEnd;
      ::i32 m_x;
      ::i32 m_xEnd;
      ::u8 * m_pdst2;
      ::u8 * m_psrc2;
      ::u8 * m_pdstOpacity; // opacity map if available
      ::u8 * m_psrcOpacity; // opacity map if available
      ::u8 * m_pdstTransparency; // transparency map if available
      ::u8 * m_psrcTransparency; // transparency map if available
      color_indexes m_indexes = common_system_image_color_indexes();
      ::i32 m_w;
      ::i32 m_h;
      e_op m_eop;
      ::i32 m_scanSrc;
      ::i32 m_scanDst;
      ::u8 m_bA;



      virtual void     run() override;

   };


} // namespace draw2d
