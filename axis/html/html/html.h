#pragma once


namespace html
{


   class CLASS_DECL_AXIS html:
      public ::apex::department
   {
   public:



      color32_t                               m_clrInvalid;   // an invalid color
      u16                                    m_percentMax;   // maximum allowable percentage value
      CNamedColors                           m_namedColors;   // collection of named colors
      __composite(LiteHTMLEntityResolver)    m_pentitysolver;


      html();
      virtual ~html();


      virtual ::estatus initialize(::layered * pobjectContext) override;


      string special_chars(const char * psz);
      string entities(const char * psz);
      string htmlpre(const char * psz);
      i32 resolve_entity(const char * pszEntity,string & strChar);

      string resolve_entities(const string & str);


      e_tag tag_name_to_id(id idTag);
      edisplay display_name_to_id(const var & varDisplay,e_tag e_tag);
      edisplay tag_to_display(e_tag etag);
      id concat(id id1,id id2);

      virtual bool defer_get_html(string& strHtml, ::file::path& pathHtml, ::object* pobjectContext, const ::var& var);

      static bool tag_visible(e_tag etag);

   };


} // namespace html



