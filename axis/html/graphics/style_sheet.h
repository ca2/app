#pragma once


//#include "acme/primitive/collection/pointer_array.h"


namespace html
{


   class CLASS_DECL_AXIS style_sheet :
      virtual public ::particle
   {
   public:


      pointer_array < style > m_stylea;
      

      style_sheet();


      virtual void initialize(::particle * pparticle) override;


      void parse(html_data * pdocument, const ::string & psz);

      style * rear_find(e_tag etag, const ::string & strClass, const ::string & strSubClass, const atom & idName);
      const style * rear_find(e_tag etag, const ::string & strClass, const ::string & strSubClass, const atom & idName) const;

      style * rfind_border_width(e_tag etag, const ::string & strClass, const ::string & strSubClass, const atom & idName, float & f);
      const style * rfind_border_width(e_tag etag, const ::string & strClass, const ::string & strSubClass, const atom & idName, float & f) const;

      style * rfind_border_color(e_tag etag, const ::string & strClass, const ::string & strSubClass, const atom & idName, ::color::color & color32);
      const style * rfind_border_color(e_tag etag, const ::string & strClass, const ::string & strSubClass, const atom & idName, ::color::color & color32) const;

      style * greater(style * pstyle1, style * pstyle2);
      const style * greater(const style * pstyle1, const style * pstyle2) const;

      // retunrs true if determined
      bool greater(style * & pstyleRet, index & iRet, ::payload & varRet, style * pstyle1, index i1, const ::payload & var1, style * pstyle2, index i2, const ::payload & var2) const;
      bool greater(const style * & pstyleRet, index & iRet, ::payload & varRet, const style * pstyle1, index i1, const ::payload & var1, const style * pstyle2, index i2, const ::payload & var2) const;


   };

} // namespace html
