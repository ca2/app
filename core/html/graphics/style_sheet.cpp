#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_graphics.h"
#endif

#include "core/user/user/_user.h"


namespace html
{


   style_sheet::style_sheet()
   {

   }


   void style_sheet::initialize(::object * pobject)
   {

      //auto estatus = 
      
      ::object::initialize(pobject);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void style_sheet::parse(html_data * pdata, const ::string & strParam)
   {

      const char * psz = strParam;

      while(*psz != '\0')
      {
         const char * pszStart = psz;
         while(*psz != '{' && *psz != '\0')
         {
            psz++;
         }
         if(*psz == '\0')
            return;
         const char * pszRestart = psz + 1;
         string str(pszStart, psz - pszStart);
         str.trim();
         if(str.get_length() <= 0)
            return;

         pszStart = str;
         psz = pszStart;
         while(*psz != '.' && *psz != '\0')
         {
            psz++;
         }

         auto pstyle = __create_new < class style >();

         string strStyle = str.Left(psz - pszStart);

         if(*psz == '.')
         {

            str = str.Mid(psz - pszStart + 1);

            pstyle->m_etag = tag_none;

         }
         else
         {

            strStyle.make_lower();

            __pointer(::core::session) psession = get_session();

            auto puser = psession->user();

            pstyle->m_etag = puser->m_phtml->tag_name_to_id(strStyle);

            if (pstyle->m_etag == tag_unknown)
               pstyle->m_etag = tag_none;

            str.Empty();

         }

         str.trim();

         if(str.get_length() > 0)
         {
            pszStart = str;
            psz = pszStart;
            while(*psz != ':' && *psz != '\0')
            {
               psz++;
            }
            pstyle->m_strName = str.Left(psz - pszStart);
            if(*psz == ':')
            {
               str = str.Mid(psz - pszStart + 1);
            }
            else
            {
               str.Empty();
            }
            pstyle->m_strSubClass = str;
         }

         psz = pstyle->parse(pdata, pszRestart);

         if(*psz == '}')
            psz++;

         m_stylea.add(pstyle);

      }

   }


   style * style_sheet::rfind(e_tag etag, const ::string & strClass, const ::string & strSubClass, atom idName)
   {

      for(index i = m_stylea.get_upper_bound(); i >= 0; i--)
      {

         class style & style = *m_stylea.element_at(i);

         if(style.matches(etag, strClass, strSubClass, idName))
            return &style;

      }

      return nullptr;

   }

   const style * style_sheet::rfind(e_tag etag, const ::string & strClass, const ::string & strSubClass, atom idName) const
   {

      return ((style_sheet *) this)->rfind(etag, strClass, strSubClass, idName);

   }


   style * style_sheet::rfind_border_width(e_tag etag, const ::string & strClass, const ::string & strSubClass, atom idName, float & f)
   {

      for(index i = m_stylea.get_upper_bound(); i >= 0; i--)
      {

         class style & style = *m_stylea.element_at(i);

         if(style.matches_border_width(etag, strClass, strSubClass, idName, f))
            return &style;

      }

      return nullptr;

   }


   const style * style_sheet::rfind_border_width(e_tag etag, const ::string & strClass, const ::string & strSubClass, atom idName, float & f) const
   {

      return ((style_sheet *) this)->rfind_border_width(etag, strClass, strSubClass, idName, f);

   }


   style * style_sheet::rfind_border_color(e_tag etag, const ::string & strClass, const ::string & strSubClass, atom idName, ::color::color & color32)
   {

      for(index i = m_stylea.get_upper_bound(); i >= 0; i--)
      {

         class style & style = *m_stylea.element_at(i);

         if(style.matches_border_color(etag, strClass, strSubClass, idName, color32))
            return &style;

      }

      return nullptr;

   }


   const style * style_sheet::rfind_border_color(e_tag etag, const ::string & strClass, const ::string & strSubClass, atom idName, ::color::color & color32) const
   {

      return ((style_sheet *) this)->rfind_border_color(etag, strClass, strSubClass, idName, color32);

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





