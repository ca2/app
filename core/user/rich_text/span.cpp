#include "framework.h"
#include "core/user/rich_text/_rich_text.h"
#include "aura/graphics/draw2d/_component.h"


namespace user
{


   namespace rich_text
   {


      span::span()
      {
         
         m_ealignNewLine = e_align_none;

         ASSERT(m_pformat != nullptr);

      }


      span::span(data * pdata) :
         m_pdata(pdata)
      {

         initialize(pdata);

         m_pformat = m_pdata->m_pformatCurrent;

         m_ealignNewLine = e_align_none;

         ASSERT(m_pformat != nullptr);

      }


      span::span(data * pdata, ::e_align ealignNewLine) :
         m_pdata(pdata)
      {

         initialize(pdata);
         m_pformat = m_pdata->m_pformatCurrent;
         m_ealignNewLine = ealignNewLine;

         ASSERT(m_pformat != nullptr);

      }


      span::span(data * pdata, const span & span) :
         m_pdata(pdata),
         m_pformat(__new(class format(*span.m_pformat))),
         m_ealignNewLine(span.m_ealignNewLine),
         m_str(span.m_str)
      {

         initialize(pdata);

         pdata->m_pformata->add(m_pformat);

         pdata->m_spana.add(this);

      }


      span::span(const span & span) :
         m_pformat(__new(class format(*span.m_pformat))),
         m_ealignNewLine(span.m_ealignNewLine),
         m_str(span.m_str)
      {

         initialize(span.m_pdata);

         ASSERT(m_pformat != nullptr);

      }


      span::~span()
      {


      }


      ::e_align span::get_align() const
      {

         ::e_align ealign = e_align_none;

         index i = m_pdata->m_spana.find_first(this);

         for (; i >= 0; i--)
         {

            if (m_pdata->m_spana[i]->is_new_line())
            {

               ealign = m_pdata->m_spana[i]->m_ealignNewLine;

               break;

            }

         }

         return ealign;

      }


      span & span::operator = (const span & span)
      {

         m_ealignNewLine= span.m_ealignNewLine;
         m_pformat.container_copy(span.m_pformat);
         m_iPosBeg = span.m_iPosBeg;
         m_iPosEnd = span.m_iPosEnd;
         m_str = span.m_str;

         return *this;

      }
      
      
      __pointer(span) span::fork()
      { 
         
         auto pspan = __new(class span(m_pdata));
         
         pspan->m_pformat = m_pformat;
         
         return pspan; 
      
      }


      __pointer(span) span::fork(const class format* pformat, const eattribute& eattribute)
      {

         auto pspan = fork();

         pspan->m_pformat.merge(m_pdata->m_pformata, pformat, eattribute);

         return pspan;

      }


      stream & span::write(::stream & stream) const
      {

         property_set set;

         set["align"] = (i32) m_ealignNewLine;
         set["text"] = m_str;
         index iFormatIndex = m_pdata->m_pformata->find_first(m_pformat);
         set["format_index"] = iFormatIndex;

         stream << set;

         return stream;

      }


      stream & span::read(::stream & stream)
      {

         property_set set;

         stream >> set;

         m_ealignNewLine = set["align"].e< ::enum_align>();
         m_str = set["text"];
         ::index iFormatIndex;

         set["format_index"].as(iFormatIndex);
         if (iFormatIndex >= 0 && iFormatIndex < m_pdata->m_pformata->get_count())
         {
            m_pformat = m_pdata->m_pformata->element_at(iFormatIndex);
         }
         else
         {
            output_debug_string("corruption... non fatal... partially recoverable...");
         }

         return stream;

      }


      //__pointer(format) span::fork_format()
      //{

      //   return __new(class format(*m_pformat));

      //}


      void span::calculate_position(::draw2d::graphics_pointer & pgraphics)
      {

         pgraphics->set(m_pformat->get_font(pgraphics));

         m_sizeSpan = pgraphics->get_text_extent(m_str);

         pgraphics->get_character_extent(m_daPositionLeft, m_daPositionRight, m_str);

      }


      //const format * span::format()
      //{

      //   return m_pdata->m_pformat;

      //}


   } // namespace rich_text


} // namespace user



