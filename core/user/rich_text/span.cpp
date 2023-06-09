#include "framework.h"
#include "span.h"
#include "data.h"
#include "format.h"
#include "acme/primitive/collection/_array_binary_stream.h"
#include "acme/primitive/data/listener.h"
#include "aura/graphics/draw2d/graphics.h"


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
      
      
      ::pointer<span>span::fork()
      { 
         
         auto pspan = __new(class span(m_pdata));
         
         pspan->m_pformat = m_pformat;
         
         return pspan; 
      
      }


      ::pointer<span>span::fork(const class format* pformat, const e_attribute& eattribute)
      {

         auto pspan = fork();

         pspan->m_pformat.merge(m_pdata->m_pformata, pformat, eattribute);

         return pspan;

      }


      ::pointer<format>span::fork_format()
      {

         return __new(class format(*m_pformat));

      }


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



