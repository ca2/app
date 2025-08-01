// Created by camilo on 2021-06-08 02:30 BRT <3ThomasBorregaardSorensen__!!
#include "framework.h"
#include "drawer.h"
#include "text_out.h"
#include "text_out_array.h"
#include "text_metric.h"
#include "font.h"
#include "acme/exception/interface_only.h"
//#include "acme/prototype/collection/string_array.h"
//#include "acme/prototype/geometry2d/_geometry2d.h"


namespace write_text
{


   drawer::drawer()
   {

   }


   drawer::~drawer()
   {

   }


   ::write_text::font * drawer::get_current_font()
   {

      return m_pfont;

   }


   void drawer::set(::write_text::font * pfont)
   {

      if (::is_null(pfont))
      {

         throw ::exception(error_null_pointer);

         //return ::error_failed;

      }

      // SIOOT - Should implemennt one of them
      // OASOWO - otherwise a stack overflow will occur
      // BTAIOM - because these are interface only methods

      m_pfont = pfont;

      //return ::success;

   }


   void drawer::draw(const ::write_text::text_out * ptextout)
   {

      if (ptextout->m_pfont && m_pfont != ptextout->m_pfont)
      {

         set(ptextout->m_pfont);

      }

      //bool bOk = 
      TextOutRaw(ptextout->m_point.x(), ptextout->m_point.y(), ptextout->m_strText);

      //if (!bOk)
      //{

      //   return error_failed;

      //}

      //return ::success;

   }

   void drawer::draw(const ::write_text::text_out_array & textouta)
   {

      for (auto & ptextout : textouta.text_outa())
      {

         draw(ptextout);

      }

      //return ::success;

   }


   ::double_size drawer::get_text_extent(const ::scoped_string & scopedstr)
   {

      return ::double_size();

   }


   ::write_text::text_metric drawer::get_text_metrics()
   {

      ::write_text::text_metric metrics;

      get_text_metrics(&metrics);

      return metrics;

   }


   void drawer::get_text_metrics(::write_text::text_metric * pmetrics)
   {

      throw ::interface_only();

      //throw ::interface_only();

   }


   void drawer::TextOutRaw(double x, double y, const ::scoped_string & scopedstr)
   {

      throw ::interface_only();

      //throw ::interface_only();

   }


   void drawer::split_text(string_array & stra, double w, enum_text_wrap etextwrap)
   {

      if (etextwrap == e_text_wrap_none)
      {

         //return ::success;

         return;

      }

      for (::collection::index i = 0; i < stra.get_size(); i++)
      {

         ::collection::count c = _split_text(stra, i, w, etextwrap);

         i += c;

      }

      //return ::success;

   }


   ::collection::count drawer::_split_text(string_array & stra, ::collection::index i, double w, enum_text_wrap etextwrap)
   {

      switch (etextwrap)
      {
      case e_text_wrap_word:
         return _split_text_word(stra, i, w);
      case e_text_wrap_word_then_character:
         return _split_text_word_then_character(stra, i, w);
      case e_text_wrap_character:
         return _split_text_character(stra, i, w);
      default:
         return 0;
      };

   }


   ::collection::count drawer::_split_text_word(string_array & stra, ::collection::index i, double w)
   {

      return _split_text_character(stra, i, w);

   }


   ::collection::count drawer::_split_text_word_then_character(string_array & stra, ::collection::index i, double w)
   {

      ::collection::count c = 0;

      string str = stra[i];

      const_char_pointer pszStart = str;

      auto pszEnd = pszStart;

      string strNow;

      // currently only whitespace characters indicate word boundaries
      auto pszLastWordboundaryStart = pszStart;
      auto pszLastWordboundaryEnd = pszStart;

      bool bWhitespace = true;

      while (pszEnd)
      {

         auto pszLast = pszEnd;

         bool bWhitespaceNow = unicode_is_whitespace(pszEnd);

         if (bWhitespaceNow && !bWhitespace)
         {

            pszLastWordboundaryStart = pszEnd;

         }
         else if (!bWhitespaceNow && bWhitespace)
         {

            pszLastWordboundaryEnd = pszEnd;

         }

         bWhitespace = bWhitespaceNow;

         pszEnd = unicode_increment(pszEnd);

         if (::is_empty(pszEnd))
         {

            break;

         }

         string strNow = string(pszStart, pszEnd - pszStart);

         auto extent = get_text_extent(strNow).cx();

         if (extent > w || is_empty(pszEnd))
         {

            if (extent <= w)
            {

               strNow = string(pszStart, ::is_null(pszEnd) ? -1:pszEnd - pszStart);

               pszStart = pszEnd;

            }
            else if (pszLastWordboundaryStart > pszStart)
            {

               strNow = string(pszStart, pszLastWordboundaryStart - pszStart);

               pszStart = pszLastWordboundaryEnd;

            }
            else if (pszLast > pszStart)
            {

               strNow = string(pszStart, pszLast - pszStart);

               pszStart = pszLast;

            }
            else
            {

               pszStart = pszEnd;

            }

            if (c == 0)
            {

               stra.set_at(i, strNow);

            }
            else
            {

               stra.insert_at(i + c, strNow);

            }

            c++;

         }

         if (is_empty(pszEnd) && !is_empty(pszStart))
         {

            strNow = string(pszStart, ::is_null(pszEnd) ? -1 : pszEnd - pszStart);

            if (strNow.has_character())
            {

               stra.insert_at(i + c, strNow);

            }

            break;

         }

      }

      return c;

   }


   ::collection::count drawer::_split_text_character(string_array & stra, ::collection::index i, double w)
   {

      ::collection::count c = 0;

      string str = stra[i];

      const_char_pointer pszStart = str;

      auto pszEnd = pszStart;

      string strNow;

      while (pszEnd)
      {

         auto pszLast = pszEnd;

         unicode_increment(pszEnd);

         string strNow = string(pszStart, pszEnd - pszStart);
         
         auto extentx = get_text_extent(strNow).cx();

         if (extentx > w || *pszEnd == '\0')
         {
            
            if(extentx > w)
            {
               
               if (pszLast > pszStart)
               {

                  strNow = string(pszStart, pszLast - pszStart);

                  pszStart = pszLast;

               }
               else
               {

                  pszStart = pszEnd;

               }
               
            }

            if (c == 0)
            {

               stra.set_at(i, strNow);

            }
            else
            {

               stra.insert_at(i + c, strNow);

            }

            c++;

         }

         if (*pszEnd == '\0')
         {

            break;

         }

      }

      return c;

   }



   void drawer::create_simple_multiline_layout(::write_text::text_out_array & textouta, const ::scoped_string & scopedstr, const ::int_rectangle & rectangle, ::write_text::font * pfont, const ::e_align & ealign, enum_text_wrap etextwrap)
   {

      string_array stra;

      stra.add_lines(scopedstr, true);

      set(pfont);

      auto textmetric = get_text_metrics();

      double y = 0.;

      double w = rectangle.width();
      
      w++;

      double h = rectangle.height();
      
      h++;

      double cx = 0.;

      split_text(stra, w, etextwrap);

      for (auto & strLine : stra)
      {

         if (strLine.has_character())
         {

            auto ptextout = __create_new < text_out >();

            ptextout->m_strText = strLine;

            ptextout->m_size = get_text_extent(strLine);

            ptextout->m_point.x() = 0;

            ptextout->m_point.y() = y;

            ptextout->m_pfont = pfont;

            textouta.add_text_out(ptextout);

            cx = maximum(cx, ptextout->m_size.cx());

         }

         y += textmetric.get_line_height();

      }

      double cy = y;

      if (ealign & (e_align_horizontal_center | e_align_right))
      {

         double dRate;

         if (ealign & e_align_horizontal_center)
         {

            dRate = 0.5;

         }
         else
         {

            dRate = 1.0;

         }

         for (auto & ptextout : textouta.text_outa())
         {

            ptextout->m_point.x() = (w - ptextout->m_size.cx()) * dRate;

         }

      }

      if (ealign & (e_align_vertical_center | e_align_bottom))
      {

         double Δy = (h - cy);

         if (ealign & e_align_vertical_center)
         {

            Δy /= 2.0;

         }

         for (auto & ptextout : textouta.text_outa())
         {

            ptextout->m_point.y() += Δy;

         }

      }

      //return ::success;

   }


} // namespace write_text



