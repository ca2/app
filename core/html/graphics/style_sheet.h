#pragma once


namespace html
{


   class CLASS_DECL_CORE style_sheet :
      virtual public ::object
   {
   public:


      pointer_array < style > m_stylea;
      

      style_sheet(::layered * pobjectContext);


      void parse(html_data * pdocument, const char * psz);

      style * rfind(e_tag etag, const string & strClass, const string & strSubClass, id idName);
      const style * rfind(e_tag etag, const string & strClass, const string & strSubClass, id idName) const;

      style * rfind_border_width(e_tag etag, const string & strClass, const string & strSubClass, id idName, float & f);
      const style * rfind_border_width(e_tag etag, const string & strClass, const string & strSubClass, id idName, float & f) const;

      style * rfind_border_color(e_tag etag, const string & strClass, const string & strSubClass, id idName, COLORREF & cr);
      const style * rfind_border_color(e_tag etag, const string & strClass, const string & strSubClass, id idName, COLORREF & cr) const;

      style * greater(style * pstyle1, style * pstyle2);
      const style * greater(const style * pstyle1, const style * pstyle2) const;

      // retunrs true if determined
      bool greater(style * & pstyleRet, index & iRet, var & varRet, style * pstyle1, index i1, const var & var1, style * pstyle2, index i2, const var & var2) const;
      bool greater(const style * & pstyleRet, index & iRet, var & varRet, const style * pstyle1, index i1, const var & var1, const style * pstyle2, index i2, const var & var2) const;


   };

} // namespace html