//
//  font_sink.hpp
//  nanogui
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 06/04/22 05:05
//  <3 Thomas likes number 5!!
//


namespace nano2d
{

   class NANOGUI_EXPORT font_sink :
      virtual public ::object
   {
   public:
      
      
      string_map < ::write_text::font_pointer > m_mapSharedFont;
      

      virtual ::write_text::font_pointer get_shared_font(const char * face, float size);
      
      
   };


} // namespace nano2d



