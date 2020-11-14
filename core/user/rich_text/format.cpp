#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/rich_text/_rich_text.h"
#endif


namespace user
{


   namespace rich_text
   {


      format::format(__pointer_array(format) * pcontainer) :
         m_pcontainer(pcontainer)
      {

         defer_create_mutex();
         
         m_bBold = false;
         m_bItalic = false;
         m_bUnderline = false;
         m_strFontFamily = FONT_SANS;
         m_dFontSize = 12.0;
         m_crForeground = ARGB(255, 0, 0, 0);
         m_crBackground = 0;
         m_escript = script_normal;
         m_elineheight = line_height_single;
         m_bUpdated = false;

      }


      format::format(const format & format) :
         ::object(format.get_context_object()),
         m_pcontainer(format.m_pcontainer)
      {

         defer_create_mutex();

         operator = (format);

      }


      format::~format()
      {


      }

      bool format::operator==(const format & format) const
      {

         return m_strFontFamily.compare_ci(format.m_strFontFamily) == 0
                && is_equal_bool(m_bBold, format.m_bBold)
                && is_equal_bool(m_bItalic, format.m_bItalic)
                && is_equal_bool(m_bUnderline, format.m_bUnderline)
                && is_similar_font_size(m_dFontSize, format.m_dFontSize)
                && m_crForeground == format.m_crForeground
                && m_crBackground == format.m_crBackground
                && m_escript == format.m_escript
                && m_elineheight == format.m_elineheight;

      }


      void format::apply(const format * pformat, const eattribute & eattribute)
      {

         if (eattribute & attribute_bold) 
         {

            if(!is_equal_bool(m_bBold, pformat->m_bBold))
            {

               m_bBold = pformat->m_bBold;

               m_bUpdated = false;

            }

         }

         if (eattribute & attribute_italic)
         {

            if(!is_equal_bool(m_bItalic, pformat->m_bItalic))
            {

               m_bItalic = pformat->m_bItalic;

               m_bUpdated = false;

            }

         }

         if (eattribute & attribute_underline)
         {

            if(!is_equal_bool(m_bUnderline, pformat->m_bUnderline))
            {

               m_bUnderline = pformat->m_bUnderline;

               m_bUpdated = false;

            }

         }

         if (eattribute & attribute_family)
         {

            if(m_strFontFamily != pformat->m_strFontFamily)
            {

               m_strFontFamily = pformat->m_strFontFamily;

               m_bUpdated = false;

            }

         }

         if (eattribute & attribute_size)
         {

            if(m_dFontSize != pformat->m_dFontSize)
            {

               m_dFontSize = pformat->m_dFontSize;

               m_bUpdated = false;

            }

         }

         if (eattribute & attribute_script)
         {

            if(m_escript != pformat->m_escript)
            {

               m_escript = pformat->m_escript;

               m_bUpdated = false;

            }

         }

         if (eattribute & attribute_foreground)
         {

            if(m_crForeground != pformat->m_crForeground)
            {

               m_crForeground = pformat->m_crForeground;

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


      ::draw2d::font * format::get_font(::draw2d::graphics_pointer & pgraphics) const
      {

         if (!m_bUpdated || m_font.is_null())
         {

            ((format*)this)->m_font.create();

            if (m_dFontSize < 6.0)
            {

               ((format *) this)->m_dFontSize = 6.0;

            }

            double dFontSize = m_dFontSize;

            if (m_escript == script_subscript || m_escript == script_superscript)
            {

               dFontSize /= 1.333;

            }

            m_font->create_point_font(m_strFontFamily, dFontSize,
                                      m_bBold ? e_font_weight_bold : e_font_weight_normal,
                                      m_bItalic,
                                      m_bUnderline);

            m_bUpdated = true;

         }

         return m_font;

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
            m_crForeground = format.m_crForeground;
            m_crBackground = format.m_crBackground;
            m_escript = format.m_escript;
            m_elineheight = format.m_elineheight;
            m_ealign = format.m_ealign;
            m_bUpdated = false;

         }

         return *this;

      }
      
      


      void format::exchange(::stream & stream)
      {

         stream.exchange("italic", m_bItalic);
         stream.exchange("underline", m_bUnderline);
         stream.exchange("family", m_strFontFamily);
         stream.exchange("size", m_dFontSize);
         stream.exchange("foreground", (u32 &)m_crForeground);
         stream.exchange("background", (u32 &)m_crBackground);
         stream.exchange("script", (i32 &)m_escript);
         stream.exchange("lineheight", (i32 &)m_elineheight);

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


