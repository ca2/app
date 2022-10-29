#pragma once


#include "acme/primitive/geometry2d/rectangle.h"
#include "acme/primitive/geometry2d/size.h"


namespace write_text
{


   class CLASS_DECL_AURA text_box
   {
   protected:


      bool                          m_bInit : 1;
      bool                          m_bOk : 1;


   public:


      ::image_pointer               m_pimage;
      ::write_text::font_pointer    m_pfont;
      ::rectangle_i32               m_rectangle;
      size_i32                      m_size;
      bool                          m_bDarkMode;


      text_box();
      ~text_box();


      bool is_layout_ok(font_list* plist);
      bool is_drawing_ok(font_list* plist);

      void set_text_box_init(bool bSet = true);
      void set_text_box_ok(bool bSet = true);

      void update(font_list * pdata, int iBox, string strText);


   };


} // namespace write_text



