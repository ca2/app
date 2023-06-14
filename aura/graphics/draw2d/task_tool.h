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

      int m_ySkip;
      int m_y;
      int m_yEnd;
      int m_x;
      int m_xEnd;
      u8 * m_pdst2;
      u8 * m_psrc2;
      u8 * m_pdstOpacity; // opacity map if available
      u8 * m_psrcOpacity; // opacity map if available
      u8 * m_pdstTransparency; // transparency map if available
      u8 * m_psrcTransparency; // transparency map if available
      color_indexes m_indexes = common_system_image_color_indexes();
      int m_w;
      int m_h;
      e_op m_eop;
      int m_scanSrc;
      int m_scanDst;
      ::u8 m_bA;



      virtual void     run() override;

   };


} // namespace draw2d
