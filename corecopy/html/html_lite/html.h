#pragma once


typedef string_map < COLORREF > string_to_colorref;


namespace html
{


   typedef string_to_colorref CNamedColors;


   class CLASS_DECL_CORE html:
      public ::aura::department
   {
   public:



      COLORREF                               m_clrInvalid;   // an invalid color
      u16                                    m_percentMax;   // maximum allowable percentage value
      CNamedColors                           m_namedColors;   // collection of named colors
      __composite(LiteHTMLEntityResolver)    m_pentitysolver;


      html();
      virtual ~html();


      virtual ::estatus initialize(::object * pobjectContext) override;


      string special_chars(const char * psz);
      string entities(const char * psz);
      string htmlpre(const char * psz);
      i32 resolve_entity(const char * pszEntity,string & strChar);

      string resolve_entities(const string & str);


      e_tag tag_name_to_id(id idTag);
      edisplay display_name_to_id(const var & varDisplay,e_tag e_tag);
      edisplay tag_to_display(e_tag etag);
      id concat(id id1,id id2);


      static bool tag_visible(e_tag etag);

   };


} // namespace html



