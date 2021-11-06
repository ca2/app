#pragma once


namespace draw2d
{


   class task_tool_item :
      virtual public ::task_tool_item
   {
   public:

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
      int m_w;
      int m_h;
      e_op m_eop;
      int m_scanSrc;
      int m_scanDst;
      byte m_bA;



      virtual ::e_status     run() override;

   };


} // namespace draw2d
