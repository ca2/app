#pragma once


namespace write_text
{


   class CLASS_DECL_AURA text_box
   {
   public:


      ::image_pointer               m_pimage;
      ::write_text::font_pointer    m_pfont;
      ::rectangle_i32               m_rectangle;
      bool                          m_bInit;
      bool                          m_bOk;
      size_i32                      m_size;


      text_box();
      ~text_box();


      void update(font_list * pdata, int iBox, string strText);


   };


} // namespace write_text



