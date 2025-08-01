#pragma once


#include "style_sheet.h"


namespace html
{


   class CLASS_DECL_AXIS style_sheet_array :
      public pointer_array < style_sheet >
   {
   public:


      style_sheet_array();


      style * rear_find(e_tag etag, const ::scoped_string & scopedstrClass, const ::scoped_string & scopedstrSubClass, const atom & idName);
      style * rfind_border_width(e_tag etag, const ::scoped_string & scopedstrClass, const ::scoped_string & scopedstrSubClass, const atom & idName, float & f);
      style * rfind_border_color(e_tag etag, const ::scoped_string & scopedstrClass, const ::scoped_string & scopedstrSubClass, const atom & idName, ::color::color & color32);

      style * greater(style * pstyle1, style * pstyle2);
      const style * greater(const style * pstyle1, const style * pstyle2) const;

      // retunrs true if determined
      bool greater(style *& pstyleRet, ::collection::index & iRet, ::payload & varRet, style * pstyle1, ::collection::index i1, const ::payload & var1, style * pstyle2, ::collection::index i2, const ::payload & var2) ;
      bool greater(const style * & pstyleRet, ::collection::index & iRet, ::payload & varRet, const style * pstyle1, ::collection::index i1, const ::payload & var1, const style * pstyle2, ::collection::index i2, const ::payload & var2) const;

   };


} // namespace html



