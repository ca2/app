// Created by camilo on 2021-06-08 02:30 BRT <3ThomasBorregaardSørensen__!!
#include "framework.h"


namespace write_text
{


   drawer::drawer()
   {

   }


   drawer::~drawer()
   {

   }


   ::write_text::font* drawer::get_current_font()
   {

      return m_pfont;

   }


   ::e_status drawer::set(::write_text::font* pfont)
   {

      if (::is_null(pfont))
      {

         return ::error_failed;

      }

      // SIOOT - Should implemennt one of them
      // OASOWO - otherwise a stack overflow will occur
      // BTAIOM - because these are interface only methods

      m_pfont = pfont;

      return ::success;

   }



   ::e_status drawer::draw(const ::write_text::text_out* ptextout)
   {

      if (ptextout->m_pfont && m_pfont != ptextout->m_pfont)
      {

         set(ptextout->m_pfont);

      }

      bool bOk = TextOutRaw(ptextout->m_point.x, ptextout->m_point.y, ptextout->m_strText);

      if (!bOk)
      {

         return error_failed;

      }

      return ::success;

   }

   ::e_status drawer::draw(const ::write_text::text_out_array& textouta)
   {

      for (auto& ptextout : textouta.text_outa())
      {

         draw(ptextout);

      }

      return ::success;

   }


   ::size_f64 drawer::get_text_extent(const ::block& block)
   {

      return ::size_f64();

   }


   ::write_text::text_metric drawer::get_text_metrics()
   {

      ::write_text::text_metric metrics;

      get_text_metrics(&metrics);

      return metrics;

   }


   ::e_status drawer::get_text_metrics(::write_text::text_metric* pmetrics)
   {

      __throw(error_interface_only);

      return error_interface_only;

   }


   ::e_status drawer::TextOutRaw(double x, double y, const block& block)
   {

      __throw(error_interface_only);

      return error_interface_only;

   }

   
   ::e_status drawer::split_text(string_array & stra, int w, enum_text_wrap etextwrap)
   {

      if (etextwrap == e_text_wrap_none)
      {

         return ::success;

      }

      for (::index i = 0; i < stra.get_size(); i++)
      {

         ::count c = _split_text(stra, i, w, etextwrap);

         i += c;

      }

   }


   ::count drawer::_split_text(string_array & stra, ::index i, int w, enum_text_wrap etextwrap)
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


   ::count drawer::_split_text_word(string_array & stra, ::index i, int w)
   {

      return _split_text_character(stra, i, w);

   }
   
   
   ::count drawer::_split_text_word_then_character(string_array & stra, ::index i, int w)
   {
      
      return _split_text_character(stra, i, w);

   }


   ::count drawer::_split_text_character(string_array & stra, ::index i, int w)
   {

      ::count c = 0;

      string str = stra[i];

      const char * pszStart = str;

      auto pszEnd = pszStart;

      string strNow;

      while (pszEnd)
      {

         auto pszLast = pszEnd;

         pszEnd = ::str::utf8_inc(pszEnd);

         string strNow = string(pszStart, pszEnd - pszStart);

         if (get_text_extent(strNow).cx > w)
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



   ::e_status drawer::create_simple_multiline_layout(::write_text::text_out_array& textouta, const string& str, const ::rectangle_i32& rectangle, ::write_text::font* pfont, const ::e_align& ealign, enum_text_wrap etextwrap)
   {

      string_array stra;

      stra.add_lines(str, true);

      set(pfont);

      auto textmetric = get_text_metrics();

      double y = 0.;

      double w = rectangle.width();

      double h = rectangle.height();

      double cx = 0.;

      split_text(stra, w, etextwrap);

      for (auto& strLine : stra)
      {

         if (strLine.has_char())
         {

            auto ptextout = __create_new < text_out >();

            ptextout->m_strText = strLine;

            ptextout->m_size = get_text_extent(strLine);

            ptextout->m_point.x = 0;

            ptextout->m_point.y = y;

            textouta.add_text_out(ptextout);

            cx = maximum(cx, ptextout->m_size.cx);

         }

         y += textmetric.get_line_spacing();

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

         for (auto& ptextout : textouta.text_outa())
         {

            ptextout->m_point.x = (w - ptextout->m_size.cx) * dRate;

         }

      }

      if (ealign & (e_align_vertical_center | e_align_bottom))
      {

         double dy = (h - cy);

         if (ealign & e_align_vertical_center)
         {

            dy /= 2.0;

         }

         for (auto& ptextout : textouta.text_outa())
         {

            ptextout->m_point.y += dy;

         }

      }

      return ::success;

   }


} // namespace write_text



