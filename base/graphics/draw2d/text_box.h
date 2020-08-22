#pragma once


namespace draw2d
{


   class CLASS_DECL_AURA text_box
   {
   public:


      ::image_pointer            m_pimage;
      ::draw2d::font_pointer     m_pfont;
      ::rect                     m_rect;
      bool                       m_bInit;
      bool                       m_bOk;
      size                       m_size;


      text_box();
      ~text_box();


      void update(font_list * pdata, int iBox, string strText);


   };


} // namespace draw2d



