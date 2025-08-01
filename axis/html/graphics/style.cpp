#include "framework.h"
#include "style.h"
#include "font.h"
#include "border.h"
#include "acme/prototype/data/listener.h"
#include "acme/prototype/geometry2d/_collection.h"
#include "acme/prototype/string/str.h"
#include "axis/html/element/element.h"
#include "axis/html/html/data.h"
#include "axis/html/html/core_data.h"
#include "axis/html/html/html.h"
#include "axis/platform/session.h"
#include "axis/user/user/user.h"
#include "aura/user/user/interaction.h"
#include "aura/platform/system.h"
#include "aura/platform/node.h"


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

   ::color::color style::parse_color(const ::scoped_string & scopedstr)
   {

      return _parse_color(scopedstr);

   }


   float style::parse_dimension(const ::scoped_string & scopedstr)
   {

      return _parse_dimension(scopedstr);

   }


   bool style::parse_border_width(const ::scoped_string & scopedstr, float & f)
   {

      return _parse_border_width(scopedstr, f);

   }


   bool style::parse_border_color(const ::scoped_string & scopedstr, ::color::color & color)
   {

      return _parse_border_color(scopedstr, color);

   }


   ::color::color style::_parse_color(const ::scoped_string & scopedstr)
   {

      ::color::color color;

      color.parse_color(scopedstr);

      return color;

   }


   bool style::get_dimension(bool bParent, const_ansi_range rangeName, const ::scoped_string & scopedstrSubClass, html_data * pdata, ::html::element * pelement, float & f)
   {

      f = 0.f;

      e_tag etag = pelement->m_etag;

      string strClass = pelement->m_strClass;

      if(m_propertyset.is_new_or_null(rangeName))
      {

         style * pstyle = pdata->m_pcoredata->m_stylesheeta.rear_find(etag, strClass, scopedstrSubClass, rangeName);

         if(pstyle == nullptr)
         {

            if(bParent)
            {

               if(pelement->m_pparent != nullptr && rangeName.case_insensitive_equals("background-color"))
               {

                  if(pelement->m_pparent->m_pstyle->get_dimension(true, rangeName, scopedstrSubClass, pdata, pelement->m_pparent, f))
                  {

                     return true;

                  }

               }

            }

            return false;

         }

         return pstyle->get_dimension(bParent, rangeName, scopedstrSubClass, pdata, pelement, f);

      }

      f = parse_dimension(m_propertyset[rangeName].as_string());

      return true;

   }


   bool style::get_surround_box(const_ansi_range rangeName, const ::scoped_string & scopedstrSubClass, html_data * pdata, ::html::element * pelement, ::float_rectangle & rectangle)
   {

      e_tag etag = pelement->m_etag;

      string strClass = pelement->m_strClass;

      const style * pstyleCur = nullptr;
      const style * pstyle = nullptr;
      const style * pstyleLeft = nullptr;
      const style * pstyleTop = nullptr;
      const style * pstyleRight = nullptr;
      const style * pstyleBottom = nullptr;
      ::collection::index i = 0;
      ::collection::index iLeft = 0;
      ::collection::index iTop = 0;
      ::collection::index iRight = 0;
      ::collection::index iBottom = 0;

      if(m_propertyset.has_property(rangeName))
         pstyle = this;
      else
         pstyle = pdata->m_pcoredata->m_stylesheeta.rear_find(etag, strClass, scopedstrSubClass, rangeName);

      if(pstyle != nullptr)
         i = pstyle->m_propertyset.index_of(rangeName);

      auto psession = m_papplication->m_psession;

      auto puser = user();

      if(m_propertyset.has_property(puser->m_phtml->concat(rangeName, "html_css_suffix_left")))
         pstyleLeft = this;
      else
         pstyleLeft = pdata->m_pcoredata->m_stylesheeta.rear_find(etag, strClass, scopedstrSubClass, puser->m_phtml->concat(rangeName, "html_css_suffix_left"));

      if(pstyleLeft != nullptr)
         iLeft = pstyleLeft->m_propertyset.index_of(puser->m_phtml->concat(rangeName, "html_css_suffix_left"));

      if (m_propertyset.has_property(puser->m_phtml->concat(rangeName, "html_css_suffix_top")))
         pstyleTop = this;
      else
         pstyleTop = pdata->m_pcoredata->m_stylesheeta.rear_find(etag, strClass, scopedstrSubClass, puser->m_phtml->concat(rangeName, "html_css_suffix_top"));

      if(pstyleTop != nullptr)
         iTop = pstyleTop->m_propertyset.index_of(puser->m_phtml->concat(rangeName, "html_css_suffix_top"));

      if (m_propertyset.has_property(puser->m_phtml->concat(rangeName, "html_css_suffix_right")))
         pstyleRight = this;
      else
         pstyleRight = pdata->m_pcoredata->m_stylesheeta.rear_find(etag, strClass, scopedstrSubClass, puser->m_phtml->concat(rangeName, "html_css_suffix_right"));

      if(pstyleRight != nullptr)
         iRight = pstyleRight->m_propertyset.index_of(puser->m_phtml->concat(rangeName, "html_css_suffix_right"));

      if (m_propertyset.has_property(puser->m_phtml->concat(rangeName, "html_css_suffix_bottom")))
         pstyleBottom = this;
      else
         pstyleBottom = pdata->m_pcoredata->m_stylesheeta.rear_find(etag, strClass, scopedstrSubClass, puser->m_phtml->concat(rangeName, "html_css_suffix_bottom"));

      if(pstyleBottom != nullptr)
         iBottom = pstyleBottom->m_propertyset.index_of(puser->m_phtml->concat(rangeName, "html_css_suffix_bottom"));

      float f = 0.f;

      if(pstyle != nullptr)
      {

         f = parse_dimension(pstyle->m_propertyset[rangeName].as_string());

      }

      pstyleCur = pdata->m_pcoredata->m_stylesheeta.greater(pstyle, pstyleLeft);

      if(pstyleCur != nullptr)
      {

         if(pstyleCur == pstyleLeft && if_then(pstyleLeft == pstyle, iLeft > i))
         {

            rectangle.left() = parse_dimension(pstyleLeft->m_propertyset[iLeft].as_string());

         }
         else
         {

            rectangle.left() = f;

         }

      }

      pstyleCur = pdata->m_pcoredata->m_stylesheeta.greater(pstyle, pstyleTop);

      if(pstyleCur != nullptr)
      {

         if(pstyleCur == pstyleTop && if_then(pstyleTop == pstyle, iTop > i))
         {

            rectangle.top() =  parse_dimension(pstyleTop->m_propertyset[iTop].as_string());

         }
         else
         {

            rectangle.top() = f;

         }

      }

      pstyleCur = pdata->m_pcoredata->m_stylesheeta.greater(pstyle, pstyleRight);

      if(pstyleCur != nullptr)
      {

         if(pstyleCur == pstyleRight && if_then(pstyleRight == pstyle, iRight > i))
         {

            rectangle.right() =  parse_dimension(pstyleRight->m_propertyset[iRight].as_string());

         }
         else
         {

            rectangle.right() = f;

         }

      }

      pstyleCur = pdata->m_pcoredata->m_stylesheeta.greater(pstyle, pstyleBottom);

      if(pstyleCur != nullptr)
      {

         if(pstyleCur == pstyleBottom && if_then(pstyleBottom == pstyle, iBottom > i))
         {

            rectangle.bottom() =  parse_dimension(pstyleBottom->m_propertyset[iBottom].as_string());

         }
         else
         {

            rectangle.bottom() = f;

         }

      }

      return true;

   }


   bool style::get_border_box(const_ansi_range rangeName, const ::scoped_string & scopedstrSubClass, html_data * pdata, ::html::element * pelement, border & rectangle)
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
      ::collection::index i              = -1;
      ::collection::index iLeft          = -1;
      ::collection::index iTop           = -1;
      ::collection::index iRight         = -1;
      ::collection::index iBottom        = -1;
      ::collection::index iW             = -1;
      ::collection::index iLeftW         = -1;
      ::collection::index iTopW          = -1;
      ::collection::index iRightW        = -1;
      ::collection::index iBottomW       = -1;
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

      if(m_propertyset.has_property(rangeName) && parse_border_width(m_propertyset[rangeName], f))
         pstyle = this;
      else
         pstyle = pdata->m_pcoredata->m_stylesheeta.rfind_border_width(etag, strClass, scopedstrSubClass, rangeName, f);
      if(pstyle != nullptr)
         i = pstyle->m_propertyset.index_of(rangeName);

      auto psession = m_papplication->m_psession;

      auto puser = user();

      if (m_propertyset.has_property(puser->m_phtml->concat(rangeName, "html_css_suffix_width"))
            && parse_border_width(m_propertyset[puser->m_phtml->concat(rangeName, "html_css_suffix_width")], fW))
         pstyleW = this;
      else
         pstyleW = pdata->m_pcoredata->m_stylesheeta.rfind_border_width(etag, strClass, scopedstrSubClass, rangeName, fW);
      if(pstyleW != nullptr)
         iW = pstyleW->m_propertyset.index_of(puser->m_phtml->concat(rangeName, "html_css_suffix_width"));

      if (m_propertyset.has_property(puser->m_phtml->concat(rangeName, "html_css_suffix_left"))
            && parse_border_width(m_propertyset[puser->m_phtml->concat(rangeName, "html_css_suffix_left")], fLeft))
         pstyleLeft = this;
      else
         pstyleLeft = pdata->m_pcoredata->m_stylesheeta.rfind_border_width(etag, strClass, scopedstrSubClass, puser->m_phtml->concat(rangeName, "html_css_suffix_left"), fLeft);

      if(pstyleLeft != nullptr)
         iLeft = pstyleLeft->m_propertyset.index_of(puser->m_phtml->concat(rangeName, "html_css_suffix_left"));

      if (m_propertyset.has_property(puser->m_phtml->concat(rangeName, "html_css_suffix_left_width"))
                                     && parse_border_width(m_propertyset[puser->m_phtml->concat(rangeName, "html_css_suffix_left_width")], fLeftW))
         pstyleLeftW = this;
      else
         pstyleLeftW = pdata->m_pcoredata->m_stylesheeta.rfind_border_width(etag, strClass, scopedstrSubClass, puser->m_phtml->concat(rangeName, "html_css_suffix_left_width"), fLeftW);

      if(pstyleLeftW != nullptr)
         iLeftW = pstyleLeftW->m_propertyset.index_of(puser->m_phtml->concat(rangeName, "html_css_suffix_left_width"));

      if (m_propertyset.has_property(puser->m_phtml->concat(rangeName, "html_css_suffix_top"))
            && parse_border_width(m_propertyset[puser->m_phtml->concat(rangeName, "html_css_suffix_top")], fTop))
         pstyleTop = this;
      else
         pstyleTop = pdata->m_pcoredata->m_stylesheeta.rfind_border_width(etag, strClass, scopedstrSubClass, puser->m_phtml->concat(rangeName, "html_css_suffix_top"), fTop);

      if(pstyleTop != nullptr)
         iTop = pstyleTop->m_propertyset.index_of(puser->m_phtml->concat(rangeName, "html_css_suffix_top"));

      if (m_propertyset.has_property(puser->m_phtml->concat(rangeName, "html_css_suffix_top_width"))
            && parse_border_width(m_propertyset[puser->m_phtml->concat(rangeName, "html_css_suffix_top_width")], fTopW))
         pstyleTopW = this;
      else
         pstyleTopW = pdata->m_pcoredata->m_stylesheeta.rfind_border_width(etag, strClass, scopedstrSubClass, puser->m_phtml->concat(rangeName, "html_css_suffix_top_width"), fTopW);

      if(pstyleTopW != nullptr)
         iTopW = pstyleTopW->m_propertyset.index_of(puser->m_phtml->concat(rangeName, "html_css_suffix_top_width"));

      if (m_propertyset.has_property(puser->m_phtml->concat(rangeName, "html_css_suffix_right"))
            && parse_border_width(m_propertyset[puser->m_phtml->concat(rangeName, "html_css_suffix_right")], fRight))
         pstyleRight = this;
      else
         pstyleRight = pdata->m_pcoredata->m_stylesheeta.rfind_border_width(etag, strClass, scopedstrSubClass, puser->m_phtml->concat(rangeName, "html_css_suffix_right"), fRight);

      if(pstyleRight != nullptr)
         iRight = pstyleRight->m_propertyset.index_of(puser->m_phtml->concat(rangeName, "html_css_suffix_right"));

      if (m_propertyset.has_property(puser->m_phtml->concat(rangeName, "html_css_suffix_right_width"))
            && parse_border_width(m_propertyset[puser->m_phtml->concat(rangeName, "html_css_suffix_right_width")], fRightW))
         pstyleRightW = this;
      else
         pstyleRightW = pdata->m_pcoredata->m_stylesheeta.rfind_border_width(etag, strClass, scopedstrSubClass, puser->m_phtml->concat(rangeName, "html_css_suffix_right_width"), fRightW);

      if(pstyleRightW != nullptr)
         iRightW = pstyleRightW->m_propertyset.index_of(puser->m_phtml->concat(rangeName, "html_css_suffix_right_width"));

      if (m_propertyset.has_property(puser->m_phtml->concat(rangeName, "html_css_suffix_bottom"))
            && parse_border_width(m_propertyset[puser->m_phtml->concat(rangeName, "html_css_suffix_bottom")], fBottom))
         pstyleBottom = this;
      else
         pstyleBottom = pdata->m_pcoredata->m_stylesheeta.rfind_border_width(etag, strClass, scopedstrSubClass, puser->m_phtml->concat(rangeName, "html_css_suffix_bottom"), fBottom);

      if(pstyleBottom != nullptr)
         iBottom = pstyleBottom->m_propertyset.index_of(puser->m_phtml->concat(rangeName, "html_css_suffix_bottom"));

      if (m_propertyset.has_property(puser->m_phtml->concat(rangeName, "html_css_suffix_bottom_width"))
            && parse_border_width(m_propertyset[puser->m_phtml->concat(rangeName, "html_css_suffix_bottom_width")], fBottomW))
         pstyleBottomW = this;
      else
         pstyleBottomW = pdata->m_pcoredata->m_stylesheeta.rfind_border_width(etag, strClass, scopedstrSubClass, puser->m_phtml->concat(rangeName, "html_css_suffix_bottom_width"), fBottomW);

      if(pstyleBottomW != nullptr)
         iBottomW = pstyleBottomW->m_propertyset.index_of(puser->m_phtml->concat(rangeName, "html_css_suffix_bottom_width"));

      const style *     pstyle1           = nullptr;
      ::collection::index               i1                = -1;
      ::payload               var1              = f;
      pdata->m_pcoredata->m_stylesheeta.greater(pstyle1, i1, var1, pstyle, i, var1, pstyleW, iW, fW);


      const style *     pstyleCur;
      ::collection::index               iCur;
      ::payload               payloadCurrent;

      pstyleCur         = pstyle1;
      iCur              = i1;
      payloadCurrent            = var1;
      pdata->m_pcoredata->m_stylesheeta.greater(pstyleCur, iCur, payloadCurrent, pstyleCur, iCur, payloadCurrent, pstyleLeft, iLeft, fLeft);
      pdata->m_pcoredata->m_stylesheeta.greater(pstyleCur, iCur, payloadCurrent, pstyleCur, iCur, payloadCurrent, pstyleLeftW, iLeftW, fLeftW);
      rectangle.left()          = (float) payloadCurrent.as_double();

      pstyleCur         = pstyle1;
      iCur              = i1;
      payloadCurrent            = var1;
      pdata->m_pcoredata->m_stylesheeta.greater(pstyleCur, iCur, payloadCurrent, pstyleCur, iCur, payloadCurrent, pstyleTop, iTop, fTop);
      pdata->m_pcoredata->m_stylesheeta.greater(pstyleCur, iCur, payloadCurrent, pstyleCur, iCur, payloadCurrent, pstyleTopW, iTopW, fTopW);
      rectangle.top()           = (float)payloadCurrent.as_double();

      pstyleCur         = pstyle1;
      iCur              = i1;
      payloadCurrent            = var1;
      pdata->m_pcoredata->m_stylesheeta.greater(pstyleCur, iCur, payloadCurrent, pstyleCur, iCur, payloadCurrent, pstyleRight, iRight, fRight);
      pdata->m_pcoredata->m_stylesheeta.greater(pstyleCur, iCur, payloadCurrent, pstyleCur, iCur, payloadCurrent, pstyleRightW, iRightW, fRightW);
      rectangle.right()         = (float)payloadCurrent.as_double();

      pstyleCur         = pstyle1;
      iCur              = i1;
      payloadCurrent            = var1;
      pdata->m_pcoredata->m_stylesheeta.greater(pstyleCur, iCur, payloadCurrent, pstyleCur, iCur, payloadCurrent, pstyleBottom, iBottom, fBottom);
      pdata->m_pcoredata->m_stylesheeta.greater(pstyleCur, iCur, payloadCurrent, pstyleCur, iCur, payloadCurrent, pstyleBottomW, iBottomW, fBottomW);
      rectangle.bottom()        = (float)payloadCurrent.as_double();

      return true;

   }


   bool style::get_border_color(const_ansi_range rangeName, const ::scoped_string & scopedstrSubClass, html_data * pdata, ::html::element * pelement, border & rectangle)
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
      ::collection::index i              = -1;
      ::collection::index iLeft          = -1;
      ::collection::index iTop           = -1;
      ::collection::index iRight         = -1;
      ::collection::index iBottom        = -1;
      ::collection::index iW             = -1;
      ::collection::index iLeftW         = -1;
      ::collection::index iTopW          = -1;
      ::collection::index iRightW        = -1;
      ::collection::index iBottomW       = -1;
      ::color::color color                = ::color::transparent;
      ::color::color colorLeft            = ::color::transparent;
      ::color::color colorTop             = ::color::transparent;
      ::color::color colorRight           = ::color::transparent;
      ::color::color colorBottom          = ::color::transparent;
      ::color::color crW                  = ::color::transparent;
      ::color::color colorLeftW           = ::color::transparent;
      ::color::color colorTopW            = ::color::transparent;
      ::color::color colorRightW          = ::color::transparent;
      ::color::color colorBottomW         = ::color::transparent;

      if(m_propertyset.has_property(rangeName) && parse_border_color(m_propertyset[rangeName], color))
         pstyle = this;
      else
         pstyle = pdata->m_pcoredata->m_stylesheeta.rfind_border_color(etag, strClass, scopedstrSubClass, rangeName, color);
      if(pstyle != nullptr)
         i = pstyle->m_propertyset.index_of(rangeName);

      auto psession = m_papplication->m_psession;

      auto puser = user();

      if (m_propertyset.has_property(puser->m_phtml->concat(rangeName, "html_css_suffix_color"))
            && parse_border_color(m_propertyset[puser->m_phtml->concat(rangeName, "html_css_suffix_color")], crW))
         pstyleW = this;
      else
         pstyleW = pdata->m_pcoredata->m_stylesheeta.rfind_border_color(etag, strClass, scopedstrSubClass, puser->m_phtml->concat(rangeName, "html_css_suffix_color"), crW);

      if(pstyleW != nullptr)
         iW = pstyleW->m_propertyset.index_of(puser->m_phtml->concat(rangeName, "html_css_suffix_color"));

      if (m_propertyset.has_property(puser->m_phtml->concat(rangeName, "html_css_suffix_left"))
            && parse_border_color(m_propertyset[puser->m_phtml->concat(rangeName, "html_css_suffix_left")], colorLeft))
         pstyleLeft = this;
      else
         pstyleLeft = pdata->m_pcoredata->m_stylesheeta.rfind_border_color(etag, strClass, scopedstrSubClass, puser->m_phtml->concat(rangeName, "html_css_suffix_left"), colorLeft);

      if(pstyleLeft != nullptr)
         iLeft = pstyleLeft->m_propertyset.index_of(puser->m_phtml->concat(rangeName, "html_css_suffix_left"));

      if (m_propertyset.has_property(puser->m_phtml->concat(rangeName, "html_css_suffix_left_color"))
            && parse_border_color(m_propertyset[puser->m_phtml->concat(rangeName, "html_css_suffix_left_color")], colorLeftW))
         pstyleLeftW = this;
      else
         pstyleLeftW = pdata->m_pcoredata->m_stylesheeta.rfind_border_color(etag, strClass, scopedstrSubClass, puser->m_phtml->concat(rangeName, "html_css_suffix_left_color"), colorLeftW);

      if(pstyleLeftW != nullptr)
         iLeftW = pstyleLeftW->m_propertyset.index_of(puser->m_phtml->concat(rangeName, "html_css_suffix_left_color"));

      if (m_propertyset.has_property(puser->m_phtml->concat(rangeName, "html_css_suffix_top"))
            && parse_border_color(m_propertyset[puser->m_phtml->concat(rangeName, "html_css_suffix_top")], colorTop))
         pstyleTop = this;
      else
         pstyleTop = pdata->m_pcoredata->m_stylesheeta.rfind_border_color(etag, strClass, scopedstrSubClass, puser->m_phtml->concat(rangeName, "html_css_suffix_top"), colorTop);

      if(pstyleTop != nullptr)
         iTop = pstyleTop->m_propertyset.index_of(puser->m_phtml->concat(rangeName, "html_css_suffix_top"));

      if (m_propertyset.has_property(puser->m_phtml->concat(rangeName, "html_css_suffix_top_color"))
            && parse_border_color(m_propertyset[puser->m_phtml->concat(rangeName, "html_css_suffix_top_color")], colorTopW))
         pstyleTopW = this;
      else
         pstyleTopW = pdata->m_pcoredata->m_stylesheeta.rfind_border_color(etag, strClass, scopedstrSubClass, puser->m_phtml->concat(rangeName, "html_css_suffix_top_color"), colorTopW);

      if(pstyleTopW != nullptr)
         iTopW = pstyleTopW->m_propertyset.index_of(puser->m_phtml->concat(rangeName, "html_css_suffix_top_color"));

      if (m_propertyset.has_property(puser->m_phtml->concat(rangeName, "html_css_suffix_right"))
            && parse_border_color(m_propertyset[puser->m_phtml->concat(rangeName, "html_css_suffix_right")], colorRight))
         pstyleRight = this;
      else
         pstyleRight = pdata->m_pcoredata->m_stylesheeta.rfind_border_color(etag, strClass, scopedstrSubClass, puser->m_phtml->concat(rangeName, "html_css_suffix_right"), colorRight);

      if(pstyleRight != nullptr)
         iRight = pstyleRight->m_propertyset.index_of(puser->m_phtml->concat(rangeName, "html_css_suffix_right"));

      if (m_propertyset.has_property(puser->m_phtml->concat(rangeName, "html_css_suffix_right_color"))
            && parse_border_color(m_propertyset[puser->m_phtml->concat(rangeName, "html_css_suffix_right_color")], colorRightW))
         pstyleRightW = this;
      else
         pstyleRightW = pdata->m_pcoredata->m_stylesheeta.rfind_border_color(etag, strClass, scopedstrSubClass, puser->m_phtml->concat(rangeName, "html_css_suffix_right_color"), colorRightW);

      if(pstyleRightW != nullptr)
         iRightW = pstyleRightW->m_propertyset.index_of(puser->m_phtml->concat(rangeName, "html_css_suffix_right_color"));

      if (m_propertyset.has_property(puser->m_phtml->concat(rangeName, "html_css_suffix_bottom"))
            && parse_border_color(m_propertyset[puser->m_phtml->concat(rangeName, "html_css_suffix_bottom")], colorBottom))
         pstyleBottom = this;
      else
         pstyleBottom = pdata->m_pcoredata->m_stylesheeta.rfind_border_color(etag, strClass, scopedstrSubClass, puser->m_phtml->concat(rangeName, "html_css_suffix_bottom"), colorBottom);

      if(pstyleBottom != nullptr)
         iBottom = pstyleBottom->m_propertyset.index_of(puser->m_phtml->concat(rangeName, "html_css_suffix_bottom"));

      if (m_propertyset.has_property(puser->m_phtml->concat(rangeName, "html_css_suffix_bottom_color"))
            && parse_border_color(m_propertyset[puser->m_phtml->concat(rangeName, "html_css_suffix_bottom_color")], colorBottomW))
         pstyleBottomW = this;
      else
         pstyleBottomW = pdata->m_pcoredata->m_stylesheeta.rfind_border_color(etag, strClass, scopedstrSubClass, puser->m_phtml->concat(rangeName, "html_css_suffix_bottom_color"), colorBottomW);

      if(pstyleBottomW != nullptr)
         iBottomW = pstyleBottomW->m_propertyset.index_of(puser->m_phtml->concat(rangeName, "html_css_suffix_bottom_color"));

      const style *     pstyle1           = nullptr;
      ::collection::index               i1                 = -1;
      ::payload var1 = color;
      pdata->m_pcoredata->m_stylesheeta.greater(pstyle1, i1, var1, pstyle, i, var1, pstyleW, iW, (unsigned int &) crW);


      const style *     pstyleCur;
      ::collection::index               iCur;
      ::payload               payloadCurrent;

      pstyleCur         = pstyle1;
      iCur              = i1;
      payloadCurrent            = var1;
      pdata->m_pcoredata->m_stylesheeta.greater(pstyleCur, iCur, payloadCurrent, pstyleCur, iCur, payloadCurrent, pstyleLeft, iLeft, (::color::color &) colorLeft);
      pdata->m_pcoredata->m_stylesheeta.greater(pstyleCur, iCur, payloadCurrent, pstyleCur, iCur, payloadCurrent, pstyleLeftW, iLeftW, (::color::color &) colorLeftW);
      rectangle.colorLeft        = payloadCurrent;

      pstyleCur         = pstyle1;
      iCur              = i1;
      payloadCurrent            = var1;
      pdata->m_pcoredata->m_stylesheeta.greater(pstyleCur, iCur, payloadCurrent, pstyleCur, iCur, payloadCurrent, pstyleTop, iTop, (::color::color &) colorTop);
      pdata->m_pcoredata->m_stylesheeta.greater(pstyleCur, iCur, payloadCurrent, pstyleCur, iCur, payloadCurrent, pstyleTopW, iTopW, (::color::color &) colorTopW);
      rectangle.colorTop         = payloadCurrent;

      pstyleCur         = pstyle1;
      iCur              = i1;
      payloadCurrent            = var1;
      pdata->m_pcoredata->m_stylesheeta.greater(pstyleCur, iCur, payloadCurrent, pstyleCur, iCur, payloadCurrent, pstyleRight, iRight, (::color::color &) colorRight);
      pdata->m_pcoredata->m_stylesheeta.greater(pstyleCur, iCur, payloadCurrent, pstyleCur, iCur, payloadCurrent, pstyleRightW, iRightW, (::color::color &) colorRightW);
      rectangle.colorRight       = payloadCurrent;

      pstyleCur         = pstyle1;
      iCur              = i1;
      payloadCurrent            = var1;
      pdata->m_pcoredata->m_stylesheeta.greater(pstyleCur, iCur, payloadCurrent, pstyleCur, iCur, payloadCurrent, pstyleBottom, iBottom, (::color::color &) colorBottom);
      pdata->m_pcoredata->m_stylesheeta.greater(pstyleCur, iCur, payloadCurrent, pstyleCur, iCur, payloadCurrent, pstyleBottomW, iBottomW, (::color::color &) colorBottomW);
      rectangle.colorBottom      = payloadCurrent;

      return true;

   }


   bool style::get_color(const_ansi_range rangeName, const ::scoped_string & scopedstrSubClass, html_data * pdata, const ::html::element * pelement, ::color::color & color32)
   {

      e_tag etag = pelement->m_etag;

      string strClass = pelement->m_strClass;

      if(m_propertyset.is_new_or_null(rangeName))
      {

         style * pstyle = pdata->m_pcoredata->m_stylesheeta.rear_find(etag, strClass, scopedstrSubClass, rangeName);

         if(pstyle == nullptr)
         {

            if(pelement->m_pparent != nullptr && case_insensitive_ansi_compare(rangeName, "background-color"))
            {

               if(pelement->m_pparent->m_pstyle->get_color(rangeName, scopedstrSubClass, pdata, pelement->m_pparent, color32))
               {
                  return true;
               }
            }
            return false;
         }
         return pstyle->get_color(rangeName, scopedstrSubClass, pdata, pelement, color32);
      }
      color32 = parse_color(m_propertyset[rangeName]);
      return true;
   }


   bool style::get_text(const_ansi_range rangeName, const ::scoped_string & scopedstrSubClass, html_data * pdata, const ::html::element * pelement, string & str)
   {

      e_tag etag = pelement->m_etag;

      string strClass = pelement->m_strClass;

      if(m_propertyset.is_new_or_null(rangeName))
      {

         style * pstyle = pdata->m_pcoredata->m_stylesheeta.rear_find(etag, strClass, scopedstrSubClass, rangeName);
         if(pstyle == nullptr)
         {
            if(::is_set(pelement->m_pparent)
               && ::is_set(pelement->m_pparent->m_pstyle)
                  && case_insensitive_ansi_compare(rangeName, "padding") != 0
                  && case_insensitive_ansi_compare(rangeName, "margin") != 0
                  && case_insensitive_ansi_compare(rangeName, "border") != 0)
            {
               if(pelement->m_pparent->m_pstyle->get_text(rangeName, scopedstrSubClass, pdata, pelement->m_pparent, str))
               {
                  return true;
               }
            }
            if(etag == tag_h1)



            {
               if(case_insensitive_ansi_compare("font-family", rangeName) == 0)
               {
                  auto psystem = system();
                  auto pnode = psystem->node();
                  str = pnode->font_name(e_font_serif);
                  return true;
               }
               else if(case_insensitive_ansi_compare("font-size", rangeName) == 0)
               {
                  str = "30";
                  return true;
               }
               else if(case_insensitive_ansi_compare("font-weight", rangeName) == 0)
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
               if(case_insensitive_ansi_compare("font-family", rangeName) == 0)
               {
                  auto psystem = system();
                  auto pnode = psystem->node();

                  str = pnode->font_name(e_font_serif);
                  return true;
               }
               else if(case_insensitive_ansi_compare("font-size", rangeName) == 0)
               {
                  str = "23";
                  return true;
               }
               else if(case_insensitive_ansi_compare("font-weight", rangeName) == 0)
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
               if(case_insensitive_ansi_compare("font-family", rangeName) == 0)
               {
                  auto psystem = system();
                  auto pnode = psystem->node();

                  str = pnode->font_name(e_font_serif);
                  return true;
               }
               else if(case_insensitive_ansi_compare("font-size", rangeName) == 0)
               {
                  str = "11";
                  return true;
               }
               else if(case_insensitive_ansi_compare("font-weight", rangeName) == 0)
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
               if(case_insensitive_ansi_compare("font-family", rangeName) == 0)
               {
                  auto psystem = system();
                  auto pnode = psystem->node();

                  str = pnode->font_name(e_font_serif);
                  return true;
               }
               else if(case_insensitive_ansi_compare("font-size", rangeName) == 0)
               {
                  str = "18";
                  return true;
               }
               else if(case_insensitive_ansi_compare("font-weight", rangeName) == 0)
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
               if (case_insensitive_ansi_compare("font-weight", rangeName) == 0)
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
         return pstyle->get_text(rangeName, scopedstrSubClass, pdata, pelement, str);
      }
      str = m_propertyset[rangeName];
      string strEm = str;
      if(string(rangeName).case_insensitive_order("font-size") == 0)
      {
         if(::str::find_awwci("em", str) > 0)
         {
            if(pelement->m_pparent != nullptr)
            {
               string strParent;
               if(pelement->m_pparent->m_pstyle->get_text(rangeName, scopedstrSubClass, pdata, pelement->m_pparent, strParent))
               {
                  str = ::as_string((int)((double) atof(str) * atoi(strParent)));
               }
               else
               {
                  str = ::as_string((int)((double) atof(str) * 12));
               }
            }
            else
            {
               str = ::as_string((int)((double) atof(str) * 12));
            }
         }
      }
      return true;
   }


   bool style::get_alpha(const ::scoped_string & scopedstrSubClass, html_data * pdata, const ::html::element * pelement, double & d)
   {

      const_char_pointer  rangeName = "opacity";

      e_tag etag = pelement->m_etag;

      string strClass = pelement->m_strClass;

      if(m_propertyset.is_new_or_null(rangeName))
      {

         style * pstyle = pdata->m_pcoredata->m_stylesheeta.rear_find(etag, strClass, scopedstrSubClass, rangeName);

         if(pstyle == nullptr)
            return false;

         return pstyle->get_alpha(scopedstrSubClass, pdata, pelement, d);

      }

      d = m_propertyset["opacity"].as_double();

      return true;

   }


   const_char_pointer  style::parse(html_data * pdata, const ::scoped_string & scopedstrParam)
   {

      const_char_pointer  psz = scopedstrParam;
      __UNREFERENCED_PARAMETER(pdata);
      while(*psz != '\0' && *psz != '}')
      {
         const_char_pointer  pszStart = psz;
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


   bool style::matches(e_tag etag, const ::scoped_string & scopedstrClass, const ::scoped_string & scopedstrSubClass, const_ansi_range rangeName)
   {

      if(etag != tag_none && m_etag != tag_none)
         if(m_etag != etag)
            return false;
      if(m_strName.has_character())
         if(m_strName != scopedstrClass)
            return false;
      if(m_strSubClass.has_character())
         if(m_strSubClass != scopedstrSubClass)
            return false;
      if(!rangeName.is_empty())
         if(!m_propertyset.has_property(rangeName))
            return false;
      return true;
   }


   bool style::matches_border_width(e_tag etag, const ::scoped_string & scopedstrClass, const ::scoped_string & scopedstrSubClass, const_ansi_range rangeName, float & f)
   {
      if(etag != tag_none && m_etag != tag_none)
         if(m_etag != etag)
            return false;
      if(m_strName.has_character())
         if(m_strName != scopedstrClass)
            return false;
      if(m_strSubClass.has_character())
         if(m_strSubClass != scopedstrSubClass)
            return false;
      if(rangeName.is_empty())
         return false;
      ::collection::index i = m_propertyset.index_of(rangeName);
      if(i < 0)
         return false;
      if(!parse_border_width(m_propertyset[i].as_string(),f))
         return false;
      return true;
   }


   bool style::matches_border_color(e_tag etag, const ::scoped_string & scopedstrClass, const ::scoped_string & scopedstrSubClass, const_ansi_range rangeName, ::color::color & color32)
   {

      if (etag != tag_none && m_etag != tag_none)
      {

         if (m_etag != etag)
         {

            return false;

         }

      }

      if (m_strName.has_character())
      {

         if (m_strName != scopedstrClass)
         {

            return false;

         }

      }

      if (m_strSubClass.has_character())
      {

         if (m_strSubClass != scopedstrSubClass)
         {

            return false;

         }

      }

      if (rangeName.is_empty())
      {

         return false;

      }

      auto i = m_propertyset.index_of(rangeName);

      if (i < 0)
      {

         return false;

      }

      if (!parse_border_color(m_propertyset[i].as_string(), color32))
      {

         return false;

      }

      return true;
   }


   float style::_parse_dimension(const ::scoped_string & scopedstrParam)
   {

      string str(scopedstrParam);

      str.trim();
      if(str.case_insensitive_ends_eat("px"))
      {
         str.trim();
         return (float) strtod(str, nullptr);
      }
      else if(str.case_insensitive_ends_eat("::float_point"))
      {
         str.trim();
         return (float) (strtod(str, nullptr) * 96.0 / 72.0);
      }
      else
      {
         return (float) strtod(str, nullptr);
      }

   }


   bool style::_parse_border_width(const ::scoped_string & scopedstr, float & f)
   {

      if (scopedstr.is_empty())
      {
       
         return false;

      }

      string str(scopedstr);

      str.trim();

      if (str.is_empty())
      {

         return false;

      }

      // todo ::str::find_cssci would find thick between spaces but not concatenated
      if(str.case_insensitive_contains("thick"))
      {
         f = 5.0;
         return true;
      }
      else if(str.case_insensitive_contains("thin"))
      {
         f = 1.0;
         return true;
      }

      character_count iFindRgb = str.case_insensitive_find_index("rgb");
      character_count iFindSharp = str.case_insensitive_find_index("#");
      character_count iFindColor = -1;
      character_count iFindDigit = str.find_first_character_in_index("0123456789");
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
         auto range = str(iFindColor);
         const_char_pointer  pszStart = range.m_begin;
         if(iFindRgb >= 0)
         {
            try
            {
               range.consume_spaces(0);
               range.consume("(");
               range.consume_spaces(0);
               range.consume_natural(255);
               range.consume_spaces(0);
               range.consume(",");
               range.consume_spaces(0);
               range.consume_natural(255);
               range.consume_spaces(0);
               range.consume(",");
               range.consume_spaces(0);
               range.consume_natural(255);
               range.consume_spaces(0);
               range.consume(")");
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
               range.consume_hex();
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
         iFindColor += range.m_begin - pszStart;
         iFindDigit = str.find_first_character_in_index("0123456789", iFindColor);
         if(iFindDigit < 0)
            return false; // no more numeric width
      }

      character_count i = iFindDigit;

      if(i < 0)
         return false;

      while(i < str.length() && character_isdigit(str[i]))
      {
         i++;
      }
      if(i >= str.length())
      {
         f = (float) strtod(&str[iFindDigit], nullptr);
         return true;
      }
      if(str[i] == '.')
      {
         i++;
      }
      if(i >= str.length())
      {
         f = (float) strtod(&str[iFindDigit], nullptr);
         return true;
      }
      while(i < str.length() && character_isdigit(str[i]))
      {
         i++;
      }
      if(i >= str.length())
      {
         f = (float) strtod(&str[iFindDigit], nullptr);
         return true;
      }
      while(i < str.length() && character_isspace(str[i]))
      {
         i++;
      }
      if(i >= str.length())
      {
         f = (float) strtod(&str[iFindDigit], nullptr);
         return true;
      }
      f = (float) strtod(&str[iFindDigit], nullptr);
      str = str.substr(i);
      if(case_insensitive_string_begins(str, "::float_point"))
      {
         str.trim();
         if(str.length() == 2 || character_isspace(str[3]))
         {
            f = f * 96.f / 72.f;
         }
      }
      return true;
   }

   bool style::_parse_border_color(const ::scoped_string & scopedstrParam, ::color::color & color32)
   {

      if(scopedstrParam.is_empty())
         return false;

      string str(scopedstrParam);

      str.trim();

      if(str.is_empty())
         return false;

      // todo ::str::find_cssci would find red between spaces but not concatenated
      if(str.case_insensitive_contains("magenta"))
      {
         color32 = argb(255, 255, 0, 255);
         return true;
      }
      else if(str.case_insensitive_contains("green"))
      {
         color32 = argb(255, 0, 255, 0);
         return true;
      }

      character_count iFindRgb = str.case_insensitive_find_index("rgb");
      character_count iFindSharp = str.case_insensitive_find_index("#");
      character_count iFindColor = -1;
//      character_count iFindDigit = str.FindOneOf("0123456789");
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

      auto range = scopedstrParam(iFindColor);
      const_char_pointer  pszStart = range.m_begin;
      if(iFindRgb >= 0)
      {
         try
         {
            range.consume_spaces(0);
            range.consume("(");
            range.consume_spaces(0);
            int R = (int) range.consume_natural(255);
            range.consume_spaces(0);
            range.consume(",");
            range.consume_spaces(0);
            int G = (int) range.consume_natural(255);
            range.consume_spaces(0);
            range.consume(",");
            range.consume_spaces(0);
            int B = (int) range.consume_natural(255);
            range.consume_spaces(0);
            range.consume(")");
            color32 = argb(255, R, G, B);
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
            range.consume_hex();
            color32 = parse_color(pszStart - 1);
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

      auto psession = m_papplication->m_psession;

      auto puser = user();

      if (m_propertyset.has_property("html_display"))
      {

         m_edisplay = puser->m_phtml->display_name_to_id(m_propertyset["html_display"], etag);

      }
      else
      {

         m_edisplay = puser->m_phtml->tag_to_display(etag);

      }

   }


} // namespace html



