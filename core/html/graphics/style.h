#pragma once



namespace html
{

   
   class element;

   
   /*enum edisplay
   {
      display_block,
      display_inline,
   };*/


   class CLASS_DECL_CORE style :
      virtual public ::object
   {
   public:

      
      e_tag                m_etag;
      string               m_strName;
      string               m_strSubClass;

      property_set         m_propertyset;

      edisplay             m_edisplay;


      style();
      style(const style & style);

      void initialize_style(e_tag etag);

      //static edisplay display_name_to_id(const ::payload & varDisplay, e_tag e_tag);
      //static edisplay tag_to_display(e_tag e_tag);

      style & operator = (const style & style);
      
      const char * parse(html_data * pdata, const ::string & psz);

      static ::color::color parse_color(const ::string & str);
      static float parse_dimension(const ::string & str);
      static bool parse_border_width(const ::string & str, float & f);
      static bool parse_border_color(const ::string & str, ::color::color & color);

      static ::color::color _parse_color(const ::string & psz);
      static float _parse_dimension(const ::string & psz);
      static bool _parse_border_width(const ::string & psz, float & f);
      static bool _parse_border_color(const ::string & psz, ::color::color & color32);

      bool get_dimension(bool bParent, id idName, const ::string & strSubClass, html_data * pdata, ::html::element * pelemental, float & f);
      bool get_surround_box(id idName, const ::string & strSubClass, html_data * pdata, ::html::element * pelemental, ::rectangle_f32 & rectangle);
      bool get_border_box(id idName, const ::string & strSubClass, html_data * pdata, ::html::element * pelemental, border & border);
      bool get_border_color(id idName, const ::string & strSubClass, html_data * pdata, ::html::element * pelemental, border & border);
      // todo
      // bool get_border_style(id idName, const ::string & strSubClass, const html_data * pdata, ::html::element * pelemental, ::color::color & color32);
      bool get_color(id idName, const ::string & strSubClass, html_data * pdata, const ::html::element * pelemental, ::color::color & color);
      bool get_text(id idName, const ::string & strSubClass, html_data * pdata, const ::html::element * pelemental, string & str);
      bool get_alpha(const ::string & strSubClass, html_data * pdata, const ::html::element * pelemental, double & d);

      bool matches(e_tag etag, const ::string & strClass, const ::string & strSubClass, id idName);
      bool matches_border_width(e_tag etag, const ::string & strClass, const ::string & strSubClass, id idName, float & f);
      bool matches_border_color(e_tag etag, const ::string & strClass, const ::string & strSubClass, id idName, ::color::color & color32);

      
   };


} // namespace html



