#include "framework.h"
#include "style_sheet.h"
#include "aura/user/user/interaction.h"
#include "axis/html/graphics/style.h"
#include "axis/html/html/html.h"
#include "axis/platform/session.h"
#include "axis/platform/session.h"
#include "axis/user/user/user.h"


namespace html
{


   style_sheet::style_sheet()
   {

   }


   void style_sheet::initialize(::particle * pparticle)
   {

      //auto estatus = 
      
      ::particle::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void style_sheet::parse(html_data * pdata, const_ansi_range & range)
   {

      while(range.has_char())
      {
         const ::ansi_character * pszStart = range.m_begin;
         while(*range.m_begin != '{' && *range.m_begin != '\0')
         {
            range.m_begin++;
         }
         if(range.is_empty())
            return;
         const ::ansi_character * pszRestart = range.m_begin + 1;
         string str(pszStart, pszRestart - pszStart);
         str.trim();
         if(str.length() <= 0)
            return;

         pszStart = str;
         range.m_begin = pszStart;
         while(*range.m_begin != '.' && *range.m_begin != '\0')
         {
            range.m_begin++;
         }

         auto pstyle = __create_new < class style >();

         string strStyle = str.left(range.m_begin - pszStart);

         if(*range.m_begin == '.')
         {

            str = str.substr(range.m_begin - pszStart + 1);

            pstyle->m_etag = tag_none;

         }
         else
         {

            strStyle.make_lower();

            auto psession = m_pcontext->m_pacmesession->m_paxissession;

            auto puser = psession->user();

            pstyle->m_etag = puser->m_phtml->tag_name_to_id(strStyle);

            if (pstyle->m_etag == tag_unknown)
               pstyle->m_etag = tag_none;

            str.empty();

         }

         str.trim();

         if(str.length() > 0)
         {
            pszStart = str;
            range.m_begin = pszStart;
            while(*range.m_begin != ':' && *range.m_begin != '\0')
            {
               range.m_begin++;
            }
            pstyle->m_strName = str.left(range.m_begin - pszStart);
            if(*range.m_begin == ':')
            {
               str = str.substr(range.m_begin - pszStart + 1);
            }
            else
            {
               str.empty();
            }
            pstyle->m_strSubClass = str;
         }

         pstyle->parse(pdata, range(pszRestart));

         if(*range.m_begin == '}')
            range.m_begin++;

         m_stylea.add(pstyle);

      }

   }


   style * style_sheet::rear_find(e_tag etag, const ::string & strClass, const ::string & strSubClass, const ::scoped_string & scopedstrName)
   {

      for(index i = m_stylea.get_upper_bound(); i >= 0; i--)
      {

         class style & style = *m_stylea.element_at(i);

         if (style.matches(etag, strClass, strSubClass, scopedstrName))
         {

            return &style;

         }

      }

      return nullptr;

   }


   const style * style_sheet::rear_find(e_tag etag, const ::string & strClass, const ::string & strSubClass, const ::scoped_string & scopedstrName) const
   {

      return ((style_sheet *) this)->rear_find(etag, strClass, strSubClass, scopedstrName);

   }


   style * style_sheet::rfind_border_width(e_tag etag, const ::string & strClass, const ::string & strSubClass, const ::scoped_string & scopedstrName, float & f)
   {

      for(index i = m_stylea.get_upper_bound(); i >= 0; i--)
      {

         class style & style = *m_stylea.element_at(i);

         if(style.matches_border_width(etag, strClass, strSubClass, scopedstrName, f)) {

            return &style;

         }

      }

      return nullptr;

   }


   const style * style_sheet::rfind_border_width(e_tag etag, const ::string & strClass, const ::string & strSubClass, const ::scoped_string & scopedstrName, float & f) const
   {

      return ((style_sheet *) this)->rfind_border_width(etag, strClass, strSubClass, scopedstrName, f);

   }


   style * style_sheet::rfind_border_color(e_tag etag, const ::string & strClass, const ::string & strSubClass, const ::scoped_string & scopedstrName, ::color::color & color32)
   {

      for(index i = m_stylea.get_upper_bound(); i >= 0; i--)
      {

         class style & style = *m_stylea.element_at(i);

         if(style.matches_border_color(etag, strClass, strSubClass, scopedstrName, color32)) {

            return &style;

         }

      }

      return nullptr;

   }


   const style * style_sheet::rfind_border_color(e_tag etag, const ::string & strClass, const ::string & strSubClass, const ::scoped_string & scopestrName, ::color::color & color32) const
   {

      return ((style_sheet *) this)->rfind_border_color(etag, strClass, strSubClass, scopestrName, color32);

   }


   const style * style_sheet::greater(const style * pstyle1, const style * pstyle2) const
   {

      if(pstyle1 == nullptr)
      {

         if(pstyle2 == nullptr)
         {

            return nullptr;

         }
         else
         {

            return pstyle2;

         }

      }
      else if(pstyle2 == nullptr)
      {

         return pstyle1;

      }

      for(index i = m_stylea.get_upper_bound(); i >= 0; i--)
      {

         const class style & style = *m_stylea.element_at(i);

         if(&style == pstyle1)
            return pstyle1;
         else if(&style == pstyle2)
            return pstyle2;

      }

      return nullptr;

   }


   style * style_sheet::greater(style * pstyle1, style * pstyle2)
   {

      return (style *)((const style_sheet *) this)->greater(pstyle1,  pstyle2);

   }


   bool style_sheet::greater(style * & pstyleRet, index & iRet, ::payload & varRet, style * pstyle1, index i1, const ::payload & var1, style * pstyle2, index i2, const ::payload & var2) const
   {

      if(pstyle1 == nullptr)
      {

         if(pstyle2 == nullptr)
         {

            return false;

         }
         else
         {

            pstyleRet   = pstyle2;
            iRet        = i2;
            varRet      = var2;

            return true;

         }

      }
      else if(pstyle2 == nullptr)
      {

         pstyleRet   = pstyle1;
         iRet        = i1;
         varRet      = var1;

         return true;

      }
      else if(pstyle1 == pstyle2)
      {

         if(i1 > i2)
         {

            pstyleRet   = pstyle1;
            iRet        = i1;
            varRet      = var1;

         }
         else
         {

            pstyleRet   = pstyle2;
            iRet        = i2;
            varRet      = var2;

         }

         return true;

      }

      for(index i = m_stylea.get_upper_bound(); i >= 0; i--)
      {

         const class style & style = *m_stylea.element_at(i);

         if(&style == pstyle1)
         {

            pstyleRet   = pstyle1;
            iRet        = i1;
            varRet      = var1;

         }
         else if(&style == pstyle2)
         {

            pstyleRet   = pstyle2;
            iRet        = i2;
            varRet      = var2;

         }

      }

      return false;

   }


   bool style_sheet::greater(const style * & pstyleRet, index & iRet, ::payload & varRet, const style * pstyle1, index i1, const ::payload & var1, const style * pstyle2, index i2, const ::payload & var2) const
   {

      return greater((style * &) pstyleRet, iRet, varRet, (style *) pstyle1, i1, var1, (style *) pstyle2, i2, var2);

   }


} // namespace html





