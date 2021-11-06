#pragma once



namespace html
{

   class CLASS_DECL_CORE style_sheet_array :
      public pointer_array < style_sheet >
   {
   public:


      style_sheet_array();


      style * rfind(e_tag etag, const ::string & strClass, const ::string & strSubClass, id idName);
      style * rfind_border_width(e_tag etag, const ::string & strClass, const ::string & strSubClass, id idName, float & f);
      style * rfind_border_color(e_tag etag, const ::string & strClass, const ::string & strSubClass, id idName, ::color::color & color32);

      style * greater(style * pstyle1, style * pstyle2);
      const style * greater(const style * pstyle1, const style * pstyle2) const;

      // retunrs true if determined
      bool greater(style *& pstyleRet, index & iRet, ::payload & varRet, style * pstyle1, index i1, const ::payload & var1, style * pstyle2, index i2, const ::payload & var2) ;
      bool greater(const style * & pstyleRet, index & iRet, ::payload & varRet, const style * pstyle1, index i1, const ::payload & var1, const style * pstyle2, index i2, const ::payload & var2) const;

   };

} // namespace html
