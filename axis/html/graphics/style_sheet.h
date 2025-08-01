#pragma once


//#include "acme/prototype/collection/pointer_array.h"


namespace html
{


   class CLASS_DECL_AXIS style_sheet :
      virtual public ::particle
   {
   public:


      pointer_array < style > m_stylea;
      

      style_sheet();


      virtual void initialize(::particle * pparticle) override;


      void parse(html_data * pdocument, ::const_ansi_range & range);

      style * rear_find(e_tag etag, const ::scoped_string & scopedstrClass, const ::scoped_string & scopedstrSubClass, const ::scoped_string & scopedstr);
      const style * rear_find(e_tag etag, const ::scoped_string & scopedstrClass, const ::scoped_string & scopedstrSubClass, const ::scoped_string & scopedstr) const;

      style * rfind_border_width(e_tag etag, const ::scoped_string & scopedstrClass, const ::scoped_string & scopedstrSubClass, const ::scoped_string & scopedstr, float & f);
      const style * rfind_border_width(e_tag etag, const ::scoped_string & scopedstrClass, const ::scoped_string & scopedstrSubClass, const ::scoped_string & scopedstr, float & f) const;

      style * rfind_border_color(e_tag etag, const ::scoped_string & scopedstrClass, const ::scoped_string & scopedstrSubClass, const ::scoped_string & scopedstr, ::color::color & color32);
      const style * rfind_border_color(e_tag etag, const ::scoped_string & scopedstrClass, const ::scoped_string & scopedstrSubClass, const ::scoped_string & scopedstr, ::color::color & color32) const;

      style * greater(style * pstyle1, style * pstyle2);
      const style * greater(const style * pstyle1, const style * pstyle2) const;

      // retunrs true if determined
      bool greater(style * & pstyleRet, ::collection::index & iRet, ::payload & varRet, style * pstyle1, ::collection::index i1, const ::payload & var1, style * pstyle2, ::collection::index i2, const ::payload & var2) const;
      bool greater(const style * & pstyleRet, ::collection::index & iRet, ::payload & varRet, const style * pstyle1, ::collection::index i1, const ::payload & var1, const style * pstyle2, ::collection::index i2, const ::payload & var2) const;


   };

} // namespace html
