#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_graphics.h"
#endif
#include "core/id.h"
#include "core/html/html/_html.h"


namespace html
{


   style::style()
   {

      m_edisplay = display_inline;

   }

   style::style(const style & style)
   {
      operator = (style);
   }

   style & style::operator = (const style & style)
   {
      if(this != &style)
      {
         m_etag         = style.m_etag;
         m_strName      = style.m_strName;
         m_strSubClass  = style.m_strSubClass;
         m_propertyset  = style.m_propertyset;
      }
      return *this;
   }



   color32_t style::parse_color(const char * psz)
   {

      ::color::color color;

      color.parse_color(psz);

      return color;

   }


   bool style::get_dimension(bool bParent, id idName, const string & strSubClass, html_data * pdata, ::html::element* pelement, float & f)
   {

      f = 0.f;

      e_tag etag = pelement->m_etag;

      string strClass = pelement->m_strClass;

      if(m_propertyset.is_new_or_null(idName))
      {

         style * pstyle = pdata->m_pcoredata->m_stylesheeta.rfind(etag, strClass, strSubClass, idName);

         if(pstyle == nullptr)
         {

            if(bParent)
            {

               if(pelement->m_pparent != nullptr && ansi_compare_ci(idName, "background-color"))
               {

                  if(pelement->m_pparent->m_pstyle->get_dimension(true, idName, strSubClass, pdata, pelement->m_pparent, f))
                  {

                     return true;

                  }

               }

            }

            return false;

         }

         return pstyle->get_dimension(bParent, idName, strSubClass, pdata, pelement, f);

      }

      f = parse_dimension(m_propertyset[idName]);

      return true;

   }


   bool style::get_surround_box(id idName, const string & strSubClass, html_data * pdata, ::html::element * pelement, ::rectangle_f32 & rectangle)
   {

      e_tag etag = pelement->m_etag;

      string strClass = pelement->m_strClass;

      const style * pstyleCur = nullptr;
      const style * pstyle = nullptr;
      const style * pstyleLeft = nullptr;
      const style * pstyleTop = nullptr;
      const style * pstyleRight = nullptr;
      const style * pstyleBottom = nullptr;
      index i = 0;
      index iLeft = 0;
      index iTop = 0;
      index iRight = 0;
      index iBottom = 0;

      if(m_propertyset.has_property(idName))
         pstyle = this;
      else
         pstyle = pdata->m_pcoredata->m_stylesheeta.rfind(etag, strClass, strSubClass, idName);

      if(pstyle != nullptr)
         i = pstyle->m_propertyset.find_index(idName);

      __pointer(::core::session) psession = get_session();

      auto puser = psession->user();

      if(m_propertyset.has_property(puser->m_phtml->concat(idName, __id(html_css_suffix_left))))
         pstyleLeft = this;
      else
         pstyleLeft = pdata->m_pcoredata->m_stylesheeta.rfind(etag, strClass, strSubClass, puser->m_phtml->concat(idName, __id(html_css_suffix_left)));

      if(pstyleLeft != nullptr)
         iLeft = pstyleLeft->m_propertyset.find_index(puser->m_phtml->concat(idName, __id(html_css_suffix_left)));

      if (m_propertyset.has_property(puser->m_phtml->concat(idName, __id(html_css_suffix_top))))
         pstyleTop = this;
      else
         pstyleTop = pdata->m_pcoredata->m_stylesheeta.rfind(etag, strClass, strSubClass, puser->m_phtml->concat(idName, __id(html_css_suffix_top)));

      if(pstyleTop != nullptr)
         iTop = pstyleTop->m_propertyset.find_index(puser->m_phtml->concat(idName, __id(html_css_suffix_top)));

      if (m_propertyset.has_property(puser->m_phtml->concat(idName, __id(html_css_suffix_right))))
         pstyleRight = this;
      else
         pstyleRight = pdata->m_pcoredata->m_stylesheeta.rfind(etag, strClass, strSubClass, puser->m_phtml->concat(idName, __id(html_css_suffix_right)));

      if(pstyleRight != nullptr)
         iRight = pstyleRight->m_propertyset.find_index(puser->m_phtml->concat(idName, __id(html_css_suffix_right)));

      if (m_propertyset.has_property(puser->m_phtml->concat(idName, __id(html_css_suffix_bottom))))
         pstyleBottom = this;
      else
         pstyleBottom = pdata->m_pcoredata->m_stylesheeta.rfind(etag, strClass, strSubClass, puser->m_phtml->concat(idName, __id(html_css_suffix_bottom)));

      if(pstyleBottom != nullptr)
         iBottom = pstyleBottom->m_propertyset.find_index(puser->m_phtml->concat(idName, __id(html_css_suffix_bottom)));

      float f = 0.f;

      if(pstyle != nullptr)
      {

         f = parse_dimension(pstyle->m_propertyset[idName]);

      }

      pstyleCur = pdata->m_pcoredata->m_stylesheeta.greater(pstyle, pstyleLeft);

      if(pstyleCur != nullptr)
      {

         if(pstyleCur == pstyleLeft && if_then(pstyleLeft == pstyle, iLeft > i))
         {

            rectangle.left = parse_dimension(pstyleLeft->m_propertyset[iLeft].get_string());

         }
         else
         {

            rectangle.left = f;

         }

      }

      pstyleCur = pdata->m_pcoredata->m_stylesheeta.greater(pstyle, pstyleTop);

      if(pstyleCur != nullptr)
      {

         if(pstyleCur == pstyleTop && if_then(pstyleTop == pstyle, iTop > i))
         {

            rectangle.top =  parse_dimension(pstyleTop->m_propertyset[iTop].get_string());

         }
         else
         {

            rectangle.top = f;

         }

      }

      pstyleCur = pdata->m_pcoredata->m_stylesheeta.greater(pstyle, pstyleRight);

      if(pstyleCur != nullptr)
      {

         if(pstyleCur == pstyleRight && if_then(pstyleRight == pstyle, iRight > i))
         {

            rectangle.right =  parse_dimension(pstyleRight->m_propertyset[iRight].get_string());

         }
         else
         {

            rectangle.right = f;

         }

      }

      pstyleCur = pdata->m_pcoredata->m_stylesheeta.greater(pstyle, pstyleBottom);

      if(pstyleCur != nullptr)
      {

         if(pstyleCur == pstyleBottom && if_then(pstyleBottom == pstyle, iBottom > i))
         {

            rectangle.bottom =  parse_dimension(pstyleBottom->m_propertyset[iBottom].get_string());

         }
         else
         {

            rectangle.bottom = f;

         }

      }

      return true;

   }


   bool style::get_border_box(id idName, const string & strSubClass, html_data * pdata, ::html::element* pelement, border & rectangle)
   {

      e_tag etag = pelement->m_etag;

      string strClass = pelement->m_strClass;

      const style * pstyle          = nullptr;
      const style * pstyleLeft      = nullptr;
      const style * pstyleTop       = nullptr;
      const style * pstyleRight     = nullptr;
      const style * pstyleBottom    = nullptr;
      const style * pstyleW         = nullptr;
      const style * pstyleLeftW     = nullptr;
      const style * pstyleTopW      = nullptr;
      const style * pstyleRightW    = nullptr;
      const style * pstyleBottomW   = nullptr;
      index i              = -1;
      index iLeft          = -1;
      index iTop           = -1;
      index iRight         = -1;
      index iBottom        = -1;
      index iW             = -1;
      index iLeftW         = -1;
      index iTopW          = -1;
      index iRightW        = -1;
      index iBottomW       = -1;
      float f              = 0.f;
      float fLeft          = 0.f;
      float fTop           = 0.f;
      float fRight         = 0.f;
      float fBottom        = 0.f;
      float fW             = 0.f;
      float fLeftW         = 0.f;
      float fTopW          = 0.f;
      float fRightW        = 0.f;
      float fBottomW       = 0.f;

      if(m_propertyset.has_property(idName) && parse_border_width(m_propertyset[idName], f))
         pstyle = this;
      else
         pstyle = pdata->m_pcoredata->m_stylesheeta.rfind_border_width(etag, strClass, strSubClass, idName, f);
      if(pstyle != nullptr)
         i = pstyle->m_propertyset.find_index(idName);

      __pointer(::core::session) psession = get_session();

      auto puser = psession->user();

      if (m_propertyset.has_property(puser->m_phtml->concat(idName, __id(html_css_suffix_width)))
            && parse_border_width(m_propertyset[puser->m_phtml->concat(idName, __id(html_css_suffix_width))], fW))
         pstyleW = this;
      else
         pstyleW = pdata->m_pcoredata->m_stylesheeta.rfind_border_width(etag, strClass, strSubClass, idName, fW);
      if(pstyleW != nullptr)
         iW = pstyleW->m_propertyset.find_index(puser->m_phtml->concat(idName, __id(html_css_suffix_width)));

      if (m_propertyset.has_property(puser->m_phtml->concat(idName, __id(html_css_suffix_left)))
            && parse_border_width(m_propertyset[puser->m_phtml->concat(idName, __id(html_css_suffix_left))], fLeft))
         pstyleLeft = this;
      else
         pstyleLeft = pdata->m_pcoredata->m_stylesheeta.rfind_border_width(etag, strClass, strSubClass, puser->m_phtml->concat(idName, __id(html_css_suffix_left)), fLeft);

      if(pstyleLeft != nullptr)
         iLeft = pstyleLeft->m_propertyset.find_index(puser->m_phtml->concat(idName, __id(html_css_suffix_left)));

      if (m_propertyset.has_property(puser->m_phtml->concat(idName, __id(html_css_suffix_left_width))
                                     && parse_border_width(m_propertyset[puser->m_phtml->concat(idName, __id(html_css_suffix_left_width))], fLeftW)))
         pstyleLeftW = this;
      else
         pstyleLeftW = pdata->m_pcoredata->m_stylesheeta.rfind_border_width(etag, strClass, strSubClass, puser->m_phtml->concat(idName, __id(html_css_suffix_left_width)), fLeftW);

      if(pstyleLeftW != nullptr)
         iLeftW = pstyleLeftW->m_propertyset.find_index(puser->m_phtml->concat(idName, __id(html_css_suffix_left_width)));

      if (m_propertyset.has_property(puser->m_phtml->concat(idName, __id(html_css_suffix_top)))
            && parse_border_width(m_propertyset[puser->m_phtml->concat(idName, __id(html_css_suffix_top))], fTop))
         pstyleTop = this;
      else
         pstyleTop = pdata->m_pcoredata->m_stylesheeta.rfind_border_width(etag, strClass, strSubClass, puser->m_phtml->concat(idName, __id(html_css_suffix_top)), fTop);

      if(pstyleTop != nullptr)
         iTop = pstyleTop->m_propertyset.find_index(puser->m_phtml->concat(idName, __id(html_css_suffix_top)));

      if (m_propertyset.has_property(puser->m_phtml->concat(idName, __id(html_css_suffix_top_width)))
            && parse_border_width(m_propertyset[puser->m_phtml->concat(idName, __id(html_css_suffix_top_width))], fTopW))
         pstyleTopW = this;
      else
         pstyleTopW = pdata->m_pcoredata->m_stylesheeta.rfind_border_width(etag, strClass, strSubClass, puser->m_phtml->concat(idName, __id(html_css_suffix_top_width)), fTopW);

      if(pstyleTopW != nullptr)
         iTopW = pstyleTopW->m_propertyset.find_index(puser->m_phtml->concat(idName, __id(html_css_suffix_top_width)));

      if (m_propertyset.has_property(puser->m_phtml->concat(idName, __id(html_css_suffix_right)))
            && parse_border_width(m_propertyset[puser->m_phtml->concat(idName, __id(html_css_suffix_right))], fRight))
         pstyleRight = this;
      else
         pstyleRight = pdata->m_pcoredata->m_stylesheeta.rfind_border_width(etag, strClass, strSubClass, puser->m_phtml->concat(idName, __id(html_css_suffix_right)), fRight);

      if(pstyleRight != nullptr)
         iRight = pstyleRight->m_propertyset.find_index(puser->m_phtml->concat(idName, __id(html_css_suffix_right)));

      if (m_propertyset.has_property(puser->m_phtml->concat(idName, __id(html_css_suffix_right_width)))
            && parse_border_width(m_propertyset[puser->m_phtml->concat(idName, __id(html_css_suffix_right_width))], fRightW))
         pstyleRightW = this;
      else
         pstyleRightW = pdata->m_pcoredata->m_stylesheeta.rfind_border_width(etag, strClass, strSubClass, puser->m_phtml->concat(idName, __id(html_css_suffix_right_width)), fRightW);

      if(pstyleRightW != nullptr)
         iRightW = pstyleRightW->m_propertyset.find_index(puser->m_phtml->concat(idName, __id(html_css_suffix_right_width)));

      if (m_propertyset.has_property(puser->m_phtml->concat(idName, __id(html_css_suffix_bottom)))
            && parse_border_width(m_propertyset[puser->m_phtml->concat(idName, __id(html_css_suffix_bottom))], fBottom))
         pstyleBottom = this;
      else
         pstyleBottom = pdata->m_pcoredata->m_stylesheeta.rfind_border_width(etag, strClass, strSubClass, puser->m_phtml->concat(idName, __id(html_css_suffix_bottom)), fBottom);

      if(pstyleBottom != nullptr)
         iBottom = pstyleBottom->m_propertyset.find_index(puser->m_phtml->concat(idName, __id(html_css_suffix_bottom)));

      if (m_propertyset.has_property(puser->m_phtml->concat(idName, __id(html_css_suffix_bottom_width)))
            && parse_border_width(m_propertyset[puser->m_phtml->concat(idName, __id(html_css_suffix_bottom_width))], fBottomW))
         pstyleBottomW = this;
      else
         pstyleBottomW = pdata->m_pcoredata->m_stylesheeta.rfind_border_width(etag, strClass, strSubClass, puser->m_phtml->concat(idName, __id(html_css_suffix_bottom_width)), fBottomW);

      if(pstyleBottomW != nullptr)
         iBottomW = pstyleBottomW->m_propertyset.find_index(puser->m_phtml->concat(idName, __id(html_css_suffix_bottom_width)));

      const style *     pstyle1           = nullptr;
      index               i1                = -1;
      ::payload               var1              = f;
      pdata->m_pcoredata->m_stylesheeta.greater(pstyle1, i1, var1, pstyle, i, var1, pstyleW, iW, fW);


      const style *     pstyleCur;
      index               iCur;
      ::payload               varCur;

      pstyleCur         = pstyle1;
      iCur              = i1;
      varCur            = var1;
      pdata->m_pcoredata->m_stylesheeta.greater(pstyleCur, iCur, varCur, pstyleCur, iCur, varCur, pstyleLeft, iLeft, fLeft);
      pdata->m_pcoredata->m_stylesheeta.greater(pstyleCur, iCur, varCur, pstyleCur, iCur, varCur, pstyleLeftW, iLeftW, fLeftW);
      rectangle.left          = (float) (double) varCur.get_double();

      pstyleCur         = pstyle1;
      iCur              = i1;
      varCur            = var1;
      pdata->m_pcoredata->m_stylesheeta.greater(pstyleCur, iCur, varCur, pstyleCur, iCur, varCur, pstyleTop, iTop, fTop);
      pdata->m_pcoredata->m_stylesheeta.greater(pstyleCur, iCur, varCur, pstyleCur, iCur, varCur, pstyleTopW, iTopW, fTopW);
      rectangle.top           = (float) (double) varCur.get_double();

      pstyleCur         = pstyle1;
      iCur              = i1;
      varCur            = var1;
      pdata->m_pcoredata->m_stylesheeta.greater(pstyleCur, iCur, varCur, pstyleCur, iCur, varCur, pstyleRight, iRight, fRight);
      pdata->m_pcoredata->m_stylesheeta.greater(pstyleCur, iCur, varCur, pstyleCur, iCur, varCur, pstyleRightW, iRightW, fRightW);
      rectangle.right         = (float) (double) varCur.get_double();

      pstyleCur         = pstyle1;
      iCur              = i1;
      varCur            = var1;
      pdata->m_pcoredata->m_stylesheeta.greater(pstyleCur, iCur, varCur, pstyleCur, iCur, varCur, pstyleBottom, iBottom, fBottom);
      pdata->m_pcoredata->m_stylesheeta.greater(pstyleCur, iCur, varCur, pstyleCur, iCur, varCur, pstyleBottomW, iBottomW, fBottomW);
      rectangle.bottom        = (float) (double) varCur.get_double();

      return true;

   }


   bool style::get_border_color(id idName, const string & strSubClass, html_data * pdata, ::html::element * pelement, border & rectangle)
   {

      e_tag etag = pelement->m_etag;

      string strClass= pelement->m_strClass;

      const style * pstyle          = nullptr;
      const style * pstyleLeft      = nullptr;
      const style * pstyleTop       = nullptr;
      const style * pstyleRight     = nullptr;
      const style * pstyleBottom    = nullptr;
      const style * pstyleW         = nullptr;
      const style * pstyleLeftW     = nullptr;
      const style * pstyleTopW      = nullptr;
      const style * pstyleRightW    = nullptr;
      const style * pstyleBottomW   = nullptr;
      index i              = -1;
      index iLeft          = -1;
      index iTop           = -1;
      index iRight         = -1;
      index iBottom        = -1;
      index iW             = -1;
      index iLeftW         = -1;
      index iTopW          = -1;
      index iRightW        = -1;
      index iBottomW       = -1;
      color32_t cr              = 0;
      color32_t crLeft          = 0;
      color32_t crTop           = 0;
      color32_t crRight         = 0;
      color32_t crBottom        = 0;
      color32_t crW             = 0;
      color32_t crLeftW         = 0;
      color32_t crTopW          = 0;
      color32_t crRightW        = 0;
      color32_t crBottomW       = 0;

      if(m_propertyset.has_property(idName) && parse_border_color(m_propertyset[idName], cr))
         pstyle = this;
      else
         pstyle = pdata->m_pcoredata->m_stylesheeta.rfind_border_color(etag, strClass, strSubClass, idName, cr);
      if(pstyle != nullptr)
         i = pstyle->m_propertyset.find_index(idName);

      __pointer(::core::session) psession = get_session();

      auto puser = psession->user();

      if (m_propertyset.has_property(puser->m_phtml->concat(idName, __id(html_css_suffix_color)))
            && parse_border_color(m_propertyset[puser->m_phtml->concat(idName, __id(html_css_suffix_color))], crW))
         pstyleW = this;
      else
         pstyleW = pdata->m_pcoredata->m_stylesheeta.rfind_border_color(etag, strClass, strSubClass, puser->m_phtml->concat(idName, __id(html_css_suffix_color)), crW);

      if(pstyleW != nullptr)
         iW = pstyleW->m_propertyset.find_index(puser->m_phtml->concat(idName, __id(html_css_suffix_color)));

      if (m_propertyset.has_property(puser->m_phtml->concat(idName, __id(html_css_suffix_left)))
            && parse_border_color(m_propertyset[puser->m_phtml->concat(idName, __id(html_css_suffix_left))], crLeft))
         pstyleLeft = this;
      else
         pstyleLeft = pdata->m_pcoredata->m_stylesheeta.rfind_border_color(etag, strClass, strSubClass, puser->m_phtml->concat(idName, __id(html_css_suffix_left)), crLeft);

      if(pstyleLeft != nullptr)
         iLeft = pstyleLeft->m_propertyset.find_index(puser->m_phtml->concat(idName, __id(html_css_suffix_left)));

      if (m_propertyset.has_property(puser->m_phtml->concat(idName, __id(html_css_suffix_left_color)))
            && parse_border_color(m_propertyset[puser->m_phtml->concat(idName, __id(html_css_suffix_left_color))], crLeftW))
         pstyleLeftW = this;
      else
         pstyleLeftW = pdata->m_pcoredata->m_stylesheeta.rfind_border_color(etag, strClass, strSubClass, puser->m_phtml->concat(idName, __id(html_css_suffix_left_color)), crLeftW);

      if(pstyleLeftW != nullptr)
         iLeftW = pstyleLeftW->m_propertyset.find_index(puser->m_phtml->concat(idName, __id(html_css_suffix_left_color)));

      if (m_propertyset.has_property(puser->m_phtml->concat(idName, __id(html_css_suffix_top)))
            && parse_border_color(m_propertyset[puser->m_phtml->concat(idName, __id(html_css_suffix_top))], crTop))
         pstyleTop = this;
      else
         pstyleTop = pdata->m_pcoredata->m_stylesheeta.rfind_border_color(etag, strClass, strSubClass, puser->m_phtml->concat(idName, __id(html_css_suffix_top)), crTop);

      if(pstyleTop != nullptr)
         iTop = pstyleTop->m_propertyset.find_index(puser->m_phtml->concat(idName, __id(html_css_suffix_top)));

      if (m_propertyset.has_property(puser->m_phtml->concat(idName, __id(html_css_suffix_top_color)))
            && parse_border_color(m_propertyset[puser->m_phtml->concat(idName, __id(html_css_suffix_top_color))], crTopW))
         pstyleTopW = this;
      else
         pstyleTopW = pdata->m_pcoredata->m_stylesheeta.rfind_border_color(etag, strClass, strSubClass, puser->m_phtml->concat(idName, __id(html_css_suffix_top_color)), crTopW);

      if(pstyleTopW != nullptr)
         iTopW = pstyleTopW->m_propertyset.find_index(puser->m_phtml->concat(idName, __id(html_css_suffix_top_color)));

      if (m_propertyset.has_property(puser->m_phtml->concat(idName, __id(html_css_suffix_right)))
            && parse_border_color(m_propertyset[puser->m_phtml->concat(idName, __id(html_css_suffix_right))], crRight))
         pstyleRight = this;
      else
         pstyleRight = pdata->m_pcoredata->m_stylesheeta.rfind_border_color(etag, strClass, strSubClass, puser->m_phtml->concat(idName, __id(html_css_suffix_right)), crRight);

      if(pstyleRight != nullptr)
         iRight = pstyleRight->m_propertyset.find_index(puser->m_phtml->concat(idName, __id(html_css_suffix_right)));

      if (m_propertyset.has_property(puser->m_phtml->concat(idName, __id(html_css_suffix_right_color)))
            && parse_border_color(m_propertyset[puser->m_phtml->concat(idName, __id(html_css_suffix_right_color))], crRightW))
         pstyleRightW = this;
      else
         pstyleRightW = pdata->m_pcoredata->m_stylesheeta.rfind_border_color(etag, strClass, strSubClass, puser->m_phtml->concat(idName, __id(html_css_suffix_right_color)), crRightW);

      if(pstyleRightW != nullptr)
         iRightW = pstyleRightW->m_propertyset.find_index(puser->m_phtml->concat(idName, __id(html_css_suffix_right_color)));

      if (m_propertyset.has_property(puser->m_phtml->concat(idName, __id(html_css_suffix_bottom)))
            && parse_border_color(m_propertyset[puser->m_phtml->concat(idName, __id(html_css_suffix_bottom))], crBottom))
         pstyleBottom = this;
      else
         pstyleBottom = pdata->m_pcoredata->m_stylesheeta.rfind_border_color(etag, strClass, strSubClass, puser->m_phtml->concat(idName, __id(html_css_suffix_bottom)), crBottom);

      if(pstyleBottom != nullptr)
         iBottom = pstyleBottom->m_propertyset.find_index(puser->m_phtml->concat(idName, __id(html_css_suffix_bottom)));

      if (m_propertyset.has_property(puser->m_phtml->concat(idName, __id(html_css_suffix_bottom_color)))
            && parse_border_color(m_propertyset[puser->m_phtml->concat(idName, __id(html_css_suffix_bottom_color))], crBottomW))
         pstyleBottomW = this;
      else
         pstyleBottomW = pdata->m_pcoredata->m_stylesheeta.rfind_border_color(etag, strClass, strSubClass, puser->m_phtml->concat(idName, __id(html_css_suffix_bottom_color)), crBottomW);

      if(pstyleBottomW != nullptr)
         iBottomW = pstyleBottomW->m_propertyset.find_index(puser->m_phtml->concat(idName, __id(html_css_suffix_bottom_color)));

      const style *     pstyle1           = nullptr;
      index               i1                 = -1;
      ::payload               var1                 = (u32) cr;
      pdata->m_pcoredata->m_stylesheeta.greater(pstyle1, i1, var1, pstyle, i, var1, pstyleW, iW, (u32 &) crW);


      const style *     pstyleCur;
      index               iCur;
      ::payload               varCur;

      pstyleCur         = pstyle1;
      iCur              = i1;
      varCur            = var1;
      pdata->m_pcoredata->m_stylesheeta.greater(pstyleCur, iCur, varCur, pstyleCur, iCur, varCur, pstyleLeft, iLeft, (u32 &) crLeft);
      pdata->m_pcoredata->m_stylesheeta.greater(pstyleCur, iCur, varCur, pstyleCur, iCur, varCur, pstyleLeftW, iLeftW, (u32 &) crLeftW);
      rectangle.crLeft        = (u32) varCur;

      pstyleCur         = pstyle1;
      iCur              = i1;
      varCur            = var1;
      pdata->m_pcoredata->m_stylesheeta.greater(pstyleCur, iCur, varCur, pstyleCur, iCur, varCur, pstyleTop, iTop, (u32 &) crTop);
      pdata->m_pcoredata->m_stylesheeta.greater(pstyleCur, iCur, varCur, pstyleCur, iCur, varCur, pstyleTopW, iTopW, (u32 &) crTopW);
      rectangle.crTop         = (u32) varCur;

      pstyleCur         = pstyle1;
      iCur              = i1;
      varCur            = var1;
      pdata->m_pcoredata->m_stylesheeta.greater(pstyleCur, iCur, varCur, pstyleCur, iCur, varCur, pstyleRight, iRight, (u32 &) crRight);
      pdata->m_pcoredata->m_stylesheeta.greater(pstyleCur, iCur, varCur, pstyleCur, iCur, varCur, pstyleRightW, iRightW, (u32 &) crRightW);
      rectangle.crRight       = (u32) varCur;

      pstyleCur         = pstyle1;
      iCur              = i1;
      varCur            = var1;
      pdata->m_pcoredata->m_stylesheeta.greater(pstyleCur, iCur, varCur, pstyleCur, iCur, varCur, pstyleBottom, iBottom, (u32 &) crBottom);
      pdata->m_pcoredata->m_stylesheeta.greater(pstyleCur, iCur, varCur, pstyleCur, iCur, varCur, pstyleBottomW, iBottomW, (u32 &) crBottomW);
      rectangle.crBottom      = (u32) varCur;

      return true;

   }


   bool style::get_color(id idName, const string & strSubClass, html_data * pdata, const ::html::element * pelement, color32_t & cr)
   {

      e_tag etag = pelement->m_etag;

      string strClass = pelement->m_strClass;

      if(m_propertyset.is_new_or_null(idName))
      {

         style * pstyle = pdata->m_pcoredata->m_stylesheeta.rfind(etag, strClass, strSubClass, idName);

         if(pstyle == nullptr)
         {

            if(pelement->m_pparent != nullptr && ansi_compare_ci(idName, "background-color"))
            {

               if(pelement->m_pparent->m_pstyle->get_color(idName, strSubClass, pdata, pelement->m_pparent, cr))
               {
                  return true;
               }
            }
            return false;
         }
         return pstyle->get_color(idName, strSubClass, pdata, pelement, cr);
      }
      cr = parse_color(m_propertyset[idName]);
      return true;
   }


   bool style::get_text(id idName, const string & strSubClass, html_data * pdata, const ::html::element * pelement, string & str)
   {

      e_tag etag = pelement->m_etag;

      string strClass = pelement->m_strClass;

      if(m_propertyset.is_new_or_null(idName))
      {

         style * pstyle = pdata->m_pcoredata->m_stylesheeta.rfind(etag, strClass, strSubClass, idName);
         if(pstyle == nullptr)
         {
            if(pelement->m_pparent != nullptr
                  && ansi_compare_ci(idName, "padding") != 0
                  && ansi_compare_ci(idName, "margin") != 0
                  && ansi_compare_ci(idName, "border") != 0)
            {
               if(pelement->m_pparent->m_pstyle->get_text(idName, strSubClass, pdata, pelement->m_pparent, str))
               {
                  return true;
               }
            }
            if(etag == tag_h1)



            {
               if(ansi_compare_ci("font-family", idName) == 0)
               {
                  auto psystem = m_psystem->m_paurasystem;
                  auto pnode = psystem->node();
                  str = pnode->font_name(e_font_serif);
                  return true;
               }
               else if(ansi_compare_ci("font-size_i32", idName) == 0)
               {
                  str = "30";
                  return true;
               }
               else if(ansi_compare_ci("font-weight", idName) == 0)
               {
                  str = "bold";
                  return true;
               }
               else
               {
                  return false;
               }
            }
            else if(etag == tag_h2)
            {
               if(ansi_compare_ci("font-family", idName) == 0)
               {
                  auto psystem = m_psystem->m_paurasystem;
                  auto pnode = psystem->node();

                  str = pnode->font_name(e_font_serif);
                  return true;
               }
               else if(ansi_compare_ci("font-size_i32", idName) == 0)
               {
                  str = "23";
                  return true;
               }
               else if(ansi_compare_ci("font-weight", idName) == 0)
               {
                  str = "bold";
                  return true;
               }
               else
               {
                  return false;
               }
            }
            else if(etag == tag_p)
            {
               if(ansi_compare_ci("font-family", idName) == 0)
               {
                  auto psystem = m_psystem->m_paurasystem;
                  auto pnode = psystem->node();

                  str = pnode->font_name(e_font_serif);
                  return true;
               }
               else if(ansi_compare_ci("font-size_i32", idName) == 0)
               {
                  str = "11";
                  return true;
               }
               else if(ansi_compare_ci("font-weight", idName) == 0)
               {
                  str = "normal";
                  return true;
               }
               else
               {
                  return false;
               }
            }
            else if(etag == tag_h3)
            {
               if(ansi_compare_ci("font-family", idName) == 0)
               {
                  auto psystem = m_psystem->m_paurasystem;
                  auto pnode = psystem->node();

                  str = pnode->font_name(e_font_serif);
                  return true;
               }
               else if(ansi_compare_ci("font-size_i32", idName) == 0)
               {
                  str = "18";
                  return true;
               }
               else if(ansi_compare_ci("font-weight", idName) == 0)
               {
                  str = "bold";
                  return true;
               }
               else
               {
                  return false;
               }
            }
            else if (etag == tag_strong)
            {
               if (ansi_compare_ci("font-weight", idName) == 0)
               {
                  str = "bold";
                  return true;
               }
               else
               {
                  return false;
               }
            }
            else
            {
               return false;
            }
         }
         return pstyle->get_text(idName, strSubClass, pdata, pelement, str);
      }
      str = m_propertyset[idName];
      string strEm = str;
      if(string(idName).compare_ci("font-size_i32") == 0)
      {
         if(::str::find_awwci("em", str) > 0)
         {
            if(pelement->m_pparent != nullptr)
            {
               string strParent;
               if(pelement->m_pparent->m_pstyle->get_text(idName, strSubClass, pdata, pelement->m_pparent, strParent))
               {
                  str = __str((i32)((double) atof(str) * atoi(strParent)));
               }
               else
               {
                  str = __str((i32)((double) atof(str) * 12));
               }
            }
            else
            {
               str = __str((i32)((double) atof(str) * 12));
            }
         }
      }
      return true;
   }


   bool style::get_alpha(const string & strSubClass, html_data * pdata, const ::html::element * pelement, double & d)
   {

      const char* idName = "opacity";

      e_tag etag = pelement->m_etag;

      string strClass = pelement->m_strClass;

      if(m_propertyset.is_new_or_null(idName))
      {

         style * pstyle = pdata->m_pcoredata->m_stylesheeta.rfind(etag, strClass, strSubClass, idName);

         if(pstyle == nullptr)
            return false;

         return pstyle->get_alpha(strSubClass, pdata, pelement, d);

      }

      d = m_propertyset["opacity"];

      return true;

   }


   const char * style::parse(html_data * pdata, const char * psz)
   {
      UNREFERENCED_PARAMETER(pdata);
      while(*psz != '\0' && *psz != '}')
      {
         const char * pszStart = psz;
         while(*psz != ':' && *psz != '\0' && *psz != '}')
         {
            psz++;
         }
         if(*psz == '\0' || *psz == '}')
            return psz;
         string strKey(pszStart, psz - pszStart);
         strKey.trim();

         char chQuote = '\0';
         psz++;
         pszStart = psz;
         while((chQuote != '\0' || *psz != ';') && *psz != '\0' && *psz != '}')
         {
            psz++;
            if(chQuote != '\0' && chQuote == *psz && *(psz - 1) != '\\')
            {
               chQuote = '\0';
            }
            else if(*psz == '\"' || *psz == '\'')
            {
               chQuote = *psz;
            }
         }
         string strValue(pszStart, psz - pszStart);
         m_propertyset[strKey] = strValue;
         if(*psz == ';')
         {
            psz++;
         }
      }

      return psz;

   }


   bool style::matches(e_tag etag, const string & strClass, const string & strSubClass, id idName)
   {

      if(etag != tag_none && m_etag != tag_none)
         if(m_etag != etag)
            return false;
      if(m_strName.has_char())
         if(m_strName != strClass)
            return false;
      if(m_strSubClass.has_char())
         if(m_strSubClass != strSubClass)
            return false;
      if(!idName.is_empty())
         if(!m_propertyset.has_property(idName))
            return false;
      return true;
   }


   bool style::matches_border_width(e_tag etag, const string & strClass, const string & strSubClass, id idName, float & f)
   {
      if(etag != tag_none && m_etag != tag_none)
         if(m_etag != etag)
            return false;
      if(m_strName.has_char())
         if(m_strName != strClass)
            return false;
      if(m_strSubClass.has_char())
         if(m_strSubClass != strSubClass)
            return false;
      if(idName.is_null())
         return false;
      index i = m_propertyset.find_index(idName);
      if(i < 0)
         return false;
      if(!parse_border_width(m_propertyset[i].get_string(),f))
         return false;
      return true;
   }


   bool style::matches_border_color(e_tag etag, const string & strClass, const string & strSubClass, id idName, color32_t & cr)
   {

      if (etag != tag_none && m_etag != tag_none)
      {

         if (m_etag != etag)
         {

            return false;

         }

      }

      if (m_strName.has_char())
      {

         if (m_strName != strClass)
         {

            return false;

         }

      }

      if (m_strSubClass.has_char())
      {

         if (m_strSubClass != strSubClass)
         {

            return false;

         }

      }

      if (idName.is_null())
      {

         return false;

      }

      index i = m_propertyset.find_index(idName);

      if (i < 0)
      {

         return false;

      }

      if (!parse_border_color(m_propertyset[i].get_string(), cr))
      {

         return false;

      }

      return true;
   }


   float style::parse_dimension(const char * psz)
   {

      string str(psz);

      str.trim();
      if(::str::ends_eat_ci(str, "px"))
      {
         str.trim();
         return (float) strtod(str, nullptr);
      }
      else if(::str::ends_eat_ci(str, "::point_f32"))
      {
         str.trim();
         return (float) (strtod(str, nullptr) * 96.0 / 72.0);
      }
      else
      {
         return (float) strtod(str, nullptr);
      }

   }

   bool style::parse_border_width(const char * psz, float & f)
   {

      if(psz == nullptr)
         return false;

      string str(psz);

      str.trim();

      if(str.is_empty())
         return false;

      // todo ::str::find_cssci would find thick between spaces but not concatenated
      if(str.find_ci("thick") >= 0)
      {
         f = 5.0;
         return true;
      }
      else if(str.find_ci("thin") >= 0)
      {
         f = 1.0;
         return true;
      }

      strsize iFindRgb = str.find_ci("rgb");
      strsize iFindSharp = str.find_ci("#");
      strsize iFindColor = -1;
      strsize iFindDigit = str.FindOneOf("0123456789");
      if(iFindRgb >= 0)
      {
         if(iFindSharp >= 0)
         {
            // invalid border specification... two colors?!?!?
            return false;
         }
         iFindColor = iFindRgb + 3;
      }
      else if(iFindSharp >= 0)
         iFindColor = iFindSharp + 1;

      if(iFindDigit >= 0 && iFindColor >= 0 && iFindDigit > iFindColor)
      {
         const char * psz = &str[iFindColor];
         const char * pszStart = psz;
         if(iFindRgb >= 0)
         {
            try
            {
               ::str::consume_spaces(psz, 0);
               ::str::consume(psz, "(");
               ::str::consume_spaces(psz, 0);
               ::str::consume_natural(psz, 255);
               ::str::consume_spaces(psz, 0);
               ::str::consume(psz, ",");
               ::str::consume_spaces(psz, 0);
               ::str::consume_natural(psz, 255);
               ::str::consume_spaces(psz, 0);
               ::str::consume(psz, ",");
               ::str::consume_spaces(psz, 0);
               ::str::consume_natural(psz, 255);
               ::str::consume_spaces(psz, 0);
               ::str::consume(psz, ")");
            }
            catch(...)
            {
               return false;
            }
         }
         else if(iFindSharp >= 0)
         {
            try
            {
               ::str::consume_hex(psz);
            }
            catch(...)
            {
               return false;
            }
         }
         else
         {
            // unexpected condition
            return false;
         }
         iFindColor += psz - pszStart;
         iFindDigit = str.FindOneOf("0123456789", iFindColor);
         if(iFindDigit < 0)
            return false; // no more numeric width
      }

      strsize i = iFindDigit;

      if(i < 0)
         return false;

      while(i < str.get_length() && i < isdigit(str[i]))
      {
         i++;
      }
      if(i >= str.get_length())
      {
         f = (float) strtod(&str[iFindDigit], nullptr);
         return true;
      }
      if(str[i] == '.')
      {
         i++;
      }
      if(i >= str.get_length())
      {
         f = (float) strtod(&str[iFindDigit], nullptr);
         return true;
      }
      while(i < str.get_length() && i < isdigit(str[i]))
      {
         i++;
      }
      if(i >= str.get_length())
      {
         f = (float) strtod(&str[iFindDigit], nullptr);
         return true;
      }
      while(i < str.get_length() && i < isspace(str[i]))
      {
         i++;
      }
      if(i >= str.get_length())
      {
         f = (float) strtod(&str[iFindDigit], nullptr);
         return true;
      }
      f = (float) strtod(&str[iFindDigit], nullptr);
      str = str.Mid(i);
      if(::str::begins_ci(str, "::point_f32"))
      {
         str.trim();
         if(str.get_length() == 2 || isspace(str[3]))
         {
            f = f * 96.f / 72.f;
         }
      }
      return true;
   }

   bool style::parse_border_color(const char * pszParam, color32_t & cr)
   {

      if(pszParam == nullptr)
         return false;

      string str(pszParam);

      str.trim();

      if(str.is_empty())
         return false;

      // todo ::str::find_cssci would find red between spaces but not concatenated
      if(str.find_ci("magenta") >= 0)
      {
         cr = argb(255, 255, 0, 255);
         return true;
      }
      else if(str.find_ci("green") >= 0)
      {
         cr = argb(255, 0, 255, 0);
         return true;
      }

      strsize iFindRgb = str.find_ci("rgb");
      strsize iFindSharp = str.find_ci("#");
      strsize iFindColor = -1;
//      strsize iFindDigit = str.FindOneOf("0123456789");
      if(iFindRgb >= 0)
      {
         if(iFindSharp >= 0)
         {
            // invalid border specification... two colors?!?!?
            return false;
         }
         iFindColor = iFindRgb + 3;
      }
      else if(iFindSharp >= 0)
         iFindColor = iFindSharp + 1;

      if(iFindColor < 0)
         return false;

      const char * psz = &str[iFindColor];
      const char * pszStart = psz;
      if(iFindRgb >= 0)
      {
         try
         {
            ::str::consume_spaces(psz, 0);
            ::str::consume(psz, "(");
            ::str::consume_spaces(psz, 0);
            i32 R = (i32) ::str::consume_natural(psz, 255);
            ::str::consume_spaces(psz, 0);
            ::str::consume(psz, ",");
            ::str::consume_spaces(psz, 0);
            i32 G = (i32) ::str::consume_natural(psz, 255);
            ::str::consume_spaces(psz, 0);
            ::str::consume(psz, ",");
            ::str::consume_spaces(psz, 0);
            i32 B = (i32) ::str::consume_natural(psz, 255);
            ::str::consume_spaces(psz, 0);
            ::str::consume(psz, ")");
            cr = argb(255, R, G, B);
            return true;
         }
         catch(...)
         {
            return false;
         }
      }
      else if(iFindSharp >= 0)
      {
         try
         {
            ::str::consume_hex(psz);
            cr = parse_color(pszStart - 1);
            return true;
         }
         catch(...)
         {
            return false;
         }
      }
      else
      {
         // unexpected condition
         return false;
      }

      return false;
   }


   void style::initialize_style(e_tag etag)
   {

      __pointer(::core::session) psession = get_session();

      auto puser = psession->user();

      if (m_propertyset.has_property(__id(html_display)))
      {

         m_edisplay = puser->m_phtml->display_name_to_id(m_propertyset[__id(html_display)], etag);

      }
      else
      {

         m_edisplay = puser->m_phtml->tag_to_display(etag);

      }

   }


} // namespace html



