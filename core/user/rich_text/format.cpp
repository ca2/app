#include "framework.h"
#include "format.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/write_text/font.h"
#include "aura/platform/system.h"
#include "aura/platform/node.h"


namespace user
{


   namespace rich_text
   {


      format::format()
      {

         defer_create_mutex();
         
         m_bBold = false;
         m_bItalic = false;
         m_bUnderline = false;
         m_dFontSize = 12.0;
         m_colorForeground = argb(255, 0, 0, 0);
         m_colorBackground = 0;
         m_escript = e_script_normal;
         m_elineheight = e_line_height_single;
         m_bUpdated = false;


      }


      //format::format(__pointer_array(format)* pcontainer)
      //{


      //   defer_create_mutex();

      //   m_bBold = false;
      //   m_bItalic = false;
      //   m_bUnderline = false;
      //   m_dFontSize = 12.0;
      //   m_colorForeground = argb(255, 0, 0, 0);
      //   m_colorBackground = 0;
      //   m_escript = script_normal;
      //   m_elineheight = line_height_single;
      //   m_bUpdated = false;

      //   initialize_user_rich_text_format(pcontainer);

      //}



      //format::format(const format & format)
      //{

      //   initialize_user_rich_text_format(format.m_pcontainer);

      //   defer_create_mutex();

      //   operator = (format);

      //}


      format::~format()
      {


      }


      void format::initialize_user_rich_text_format(__pointer_array(format)* pcontainer)
      {

         m_pcontainer = pcontainer;

         auto psystem = m_psystem->m_paurasystem;

         auto pnode = psystem->node();

         m_strFontFamily = pnode->font_name(e_font_sans);

         //return ::success;

      }


      bool format::operator==(const format & format) const
      {

         return m_strFontFamily.compare_ci(format.m_strFontFamily) == 0
                && is_equal_bool(m_bBold, format.m_bBold)
                && is_equal_bool(m_bItalic, format.m_bItalic)
                && is_equal_bool(m_bUnderline, format.m_bUnderline)
                && is_similar_font_size(m_dFontSize, format.m_dFontSize)
                && m_colorForeground == format.m_colorForeground
                && m_colorBackground == format.m_colorBackground
                && m_escript == format.m_escript
                && m_elineheight == format.m_elineheight;

      }


      void format::apply(const format * pformat, const e_attribute & eattribute)
      {

         if (eattribute & e_attribute_bold) 
         {

            if(!is_equal_bool(m_bBold, pformat->m_bBold))
            {

               m_bBold = pformat->m_bBold;

               m_bUpdated = false;

            }

         }

         if (eattribute & e_attribute_italic)
         {

            if(!is_equal_bool(m_bItalic, pformat->m_bItalic))
            {

               m_bItalic = pformat->m_bItalic;

               m_bUpdated = false;

            }

         }

         if (eattribute & e_attribute_underline)
         {

            if(!is_equal_bool(m_bUnderline, pformat->m_bUnderline))
            {

               m_bUnderline = pformat->m_bUnderline;

               m_bUpdated = false;

            }

         }

         if (eattribute & e_attribute_family)
         {

            if(m_strFontFamily != pformat->m_strFontFamily)
            {

               m_strFontFamily = pformat->m_strFontFamily;

               m_bUpdated = false;

            }

         }

         if (eattribute & e_attribute_size)
         {

            if(m_dFontSize != pformat->m_dFontSize)
            {

               m_dFontSize = pformat->m_dFontSize;

               m_bUpdated = false;

            }

         }

         if (eattribute & e_attribute_script)
         {

            if(m_escript != pformat->m_escript)
            {

               m_escript = pformat->m_escript;

               m_bUpdated = false;

            }

         }

         if (eattribute & e_attribute_foreground)
         {

            if(m_colorForeground != pformat->m_colorForeground)
            {

               m_colorForeground = pformat->m_colorForeground;

               m_bUpdated = false;

            }

         }

      }


      void format::intersect(const format & format)
      {

         if (!is_equal_bool(m_bBold, format.m_bBold))
         {

            m_bBold = false;

         }

         if (!is_equal_bool(m_bItalic, format.m_bItalic))
         {

            m_bItalic = false;

         }

         if (!is_equal_bool(m_bUnderline, format.m_bUnderline))
         {

            m_bItalic = false;

         }

         if (m_strFontFamily.compare_ci(format.m_strFontFamily) != 0)
         {

            m_strFontFamily.Empty();

         }

         if (!is_similar_font_size(m_dFontSize, format.m_dFontSize))
         {

            m_dFontSize = -1.0;

         }

         if (m_ealign != format.m_ealign)
         {

            m_ealign = e_align_left;

         }

      }


      ::write_text::font * format::get_font(::draw2d::graphics_pointer & pgraphics) const
      {

         if (!m_bUpdated || m_pfont.is_null())
         {

            pgraphics->__defer_construct(((format*)this)->m_pfont);

            if (m_dFontSize < 6.0)
            {

               ((format *) this)->m_dFontSize = 6.0;

            }

            double dFontSize = m_dFontSize;

            if (m_escript == e_script_subscript || m_escript == e_script_superscript)
            {

               dFontSize /= 1.333;

            }

            m_pfont->create_point_font(m_strFontFamily, dFontSize,
                                      m_bBold ? e_font_weight_bold : e_font_weight_normal,
                                      m_bItalic,
                                      m_bUnderline);

            m_bUpdated = true;

         }

         return m_pfont;

      }


      format & format::operator =(const format & format)
      {

         if (this != &format)
         {

            m_bBold = format.m_bBold;
            m_bItalic = format.m_bItalic;
            m_bUnderline = format.m_bUnderline;
            m_strFontFamily = format.m_strFontFamily;
            m_dFontSize = format.m_dFontSize;
            m_colorForeground = format.m_colorForeground;
            m_colorBackground = format.m_colorBackground;
            m_escript = format.m_escript;
            m_elineheight = format.m_elineheight;
            m_ealign = format.m_ealign;
            m_bUpdated = false;

         }

         return *this;

      }
      


      //void format::write(::binary_stream & stream) const
      //{

      //   stream.exchange("italic", m_bItalic);
      //   stream.exchange("underline", m_bUnderline);
      //   stream.exchange("family", m_strFontFamily);
      //   stream.exchange("size_i32", m_dFontSize);
      //   stream.exchange("foreground", (u32 &)m_colorForeground);
      //   stream.exchange("background", (u32 &)m_colorBackground);
      //   stream.exchange("script", (i32 &)m_escript);
      //   stream.exchange("lineheight", (i32 &)m_elineheight);

      //}



      void format::write(::binary_stream & stream) const
      {

         stream << m_bItalic;
         stream << m_bUnderline;
         stream << m_strFontFamily;
         stream << m_dFontSize;
         stream << (u32) m_colorForeground;
         stream << (u32)m_colorBackground;
         stream << (i32)m_escript;
         stream << (i32)m_elineheight;

      }


      void format::read(::binary_stream & stream)
      {

         stream>>  m_bItalic;
         stream>> m_bUnderline;
         stream>> m_strFontFamily;
         stream>> m_dFontSize;
         stream>> (u32 &)m_colorForeground;
         stream>> (u32 &)m_colorBackground;
         stream>> (i32 &)m_escript;
         stream>> (i32 &)m_elineheight;

      }

      //stream & format::write(::stream & stream) const
      //{

      //   do_property_exchange(stream);

      //   return stream;

      //}


      //stream & format::read(::stream & stream)
      //{

      //   do_property_exchange(stream);

      //   return stream;

      //}


   } // namespace rich_text


} // namespace user


