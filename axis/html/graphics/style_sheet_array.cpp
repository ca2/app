#include "framework.h"
#include "style_sheet_array.h"
#include "style.h"
//#include "acme/prototype/prototype/payload.h"


namespace html
{


   style_sheet_array::style_sheet_array()
   {

   }


   style * style_sheet_array::rear_find(e_tag etag, const ::scoped_string & scopedstrClass, const ::scoped_string & scopedstrSubClass, const atom & idName)
   {

      style * pstyle = nullptr;

      ::collection::index i;

      for(i = get_upper_bound(); i >= 0; i--)
      {

         style_sheet & sheet = *this->element_at(i);

         pstyle = sheet.rear_find(etag, scopedstrClass, scopedstrSubClass, idName);

         if(pstyle != nullptr)
            break;

      }

      return pstyle;

   }


   style * style_sheet_array::rfind_border_width(e_tag etag, const ::scoped_string & scopedstrClass, const ::scoped_string & scopedstrSubClass, const atom & idName, float & f)
   {

      style * pstyle = nullptr;

      ::collection::index i;

      for(i = get_upper_bound(); i >= 0; i--)
      {

         style_sheet & sheet = *this->element_at(i);

         pstyle = sheet.rfind_border_width(etag, scopedstrClass, scopedstrSubClass, idName, f);

         if(pstyle != nullptr)
            break;

      }

      return pstyle;

   }


   style * style_sheet_array::rfind_border_color(e_tag etag, const ::scoped_string & scopedstrClass, const ::scoped_string & scopedstrSubClass, const atom & idName, ::color::color & color32)
   {

      style * pstyle = nullptr;

      ::collection::index i;

      for(i = get_upper_bound(); i >= 0; i--)
      {

         style_sheet & sheet = *this->element_at(i);

         pstyle = sheet.rfind_border_color(etag, scopedstrClass, scopedstrSubClass, idName, color32);

         if(pstyle != nullptr)
            break;

      }

      return pstyle;

   }

   const style * style_sheet_array::greater(const style * pstyle1, const style * pstyle2) const
   {

      return ((style_sheet_array *)this)->greater((style *)pstyle1, (style *)pstyle2);

   }


   style * style_sheet_array::greater( style * pstyle1,  style * pstyle2)
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

      style * pstyle;

      ::collection::index i;

      for(i = get_upper_bound(); i >= 0; i--)
      {

         style_sheet & sheet = *this->element_at(i);

         pstyle = sheet.greater(pstyle1, pstyle2);

         if(pstyle != nullptr)
            return pstyle;

      }

      return nullptr;

   }


   bool style_sheet_array::greater(style *& pstyleRet, ::collection::index & iRet, ::payload & varRet, style * pstyle1, ::collection::index i1, const ::payload & var1, style * pstyle2, ::collection::index i2, const ::payload & var2)
   {

      return ((const style_sheet_array *)this)->greater((const style * &) pstyleRet, iRet, varRet, pstyle1, i1, var1, pstyle2, i2, var2);

   }


   bool style_sheet_array::greater(const style *& pstyleRet, ::collection::index & iRet, ::payload & varRet, const style * pstyle1, ::collection::index i1, const ::payload & var1, const style * pstyle2, ::collection::index i2, const ::payload & var2) const
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

      ::collection::index i;

      for(i = get_upper_bound(); i >= 0; i--)
      {

         const style_sheet & sheet = *this->element_at(i);

         if(sheet.greater(pstyleRet, iRet, varRet, pstyle1, i1, var1, pstyle2, i2, var2))
            return true;

      }

      return false;

   }


} // namespace html





