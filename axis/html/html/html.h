#pragma once


namespace html
{


   class CLASS_DECL_AXIS html:
      public ::acme::department
   {
   public:



      ::color::color                              m_clrInvalid;   // an invalid color
      u16                                    m_percentMax;   // maximum allowable percentage value
      named_color                            m_namedcolor;   // collection of named colors
      __composite(LiteHTMLEntityResolver)    m_pentitysolver;


      html();
      virtual ~html();


      virtual void initialize(::object * pobject) override;


      string special_chars(const ::string & psz);
      string entities(const ::string & psz);
      string htmlpre(const ::string & psz);
      i32 resolve_entity(const ::string & pszEntity,string & strChar);

      string resolve_entities(const ::string & str);


      e_tag tag_name_to_id(atom idTag);
      edisplay display_name_to_id(const ::payload & varDisplay,e_tag e_tag);
      edisplay tag_to_display(e_tag etag);
      atom concat(atom id1,atom id2);

      virtual bool defer_get_html(string& strHtml, ::file::path& pathHtml, ::object* pobject, const ::payload & payload);

      static bool tag_visible(e_tag etag);

   };


} // namespace html



