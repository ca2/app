#pragma once


//#include "acme/prototype/geometry2d/_geometry2d.h"
//#include "acme/prototype/prototype/pointer.h"
#include "aura/graphics/image/image.h"


namespace write_text
{


   class CLASS_DECL_AURA text_box
   {
   protected:


      bool                          m_bInit : 1;
      bool                          m_bOk : 1;


   public:


      ::image::image_pointer               m_pimage;
      ::write_text::font_pointer    m_pfont;
      ::int_rectangle               m_rectangle;
      int_size                      m_size;
      bool                          m_bDarkMode;


      text_box();
      ~text_box();


      bool is_layout_ok(font_list* plist);
      bool is_drawing_ok(font_list* plist);

      void set_text_box_init(bool bSet = true);
      void set_text_box_ok(bool bSet = true);

      void update(font_list * pdata, int iBox, const ::scoped_string & scopedstrText);


   };


} // namespace write_text



