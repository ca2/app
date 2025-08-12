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
      unsigned char * m_pdst2;
      unsigned char * m_psrc2;
      unsigned char * m_pdstOpacity; // opacity map_base if available
      unsigned char * m_psrcOpacity; // opacity map_base if available
      unsigned char * m_pdstTransparency; // transparency map_base if available
      unsigned char * m_psrcTransparency; // transparency map_base if available
      color_indexes m_indexes = common_system_image_color_indexes();
      int m_w;
      int m_h;
      e_op m_eop;
      int m_scanSrc;
      int m_scanDst;
      unsigned char m_bA;



      virtual void     run() override;

   };


} // namespace draw2d
