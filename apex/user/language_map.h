#pragma once


namespace user
{


   class CLASS_DECL_APEX language_map :
      virtual public ::object
   {
   public:


      INT_STRING *                                 m_pintstring;
      string_map < __pointer(::user::language) >   m_languagemap;
      string_array                                 m_straLang;
      string                                       m_strLang;
      string_to_string *                           m_pstringmap;
      __pointer(::user::language)                  m_planguage;


      language_map();
      virtual ~language_map();


      virtual void initialize(::object * pobject) override;


      virtual bool set_language_resource_map(INT_STRING * pstringintLanguageResourceMap);

      virtual string load_podata(string strLang, bool bOnlyHeader = false);

      virtual string get_language();
      virtual bool set_language(::application * papp, string strLang);
      virtual bool set_default_language(::application * papp);

      //virtual bool set_language_sel(index iSel);


      ///// get_current_language() -> data_get_current_language() -> data_get("language")
      //virtual string get_current_language();
      ///// set_current_language() -> data_set_current_language() -> data_set("language")
      //virtual bool set_current_language(string strLang);
      //virtual bool set_current_language(index iSel);


      virtual index get_language_list(string_array & stra);
      virtual index get_text_list(string_array & stra, string strText, bool bFull = false);
      virtual string_array get_text_list(string strText, bool bFull = false);


      virtual void parse_podata(string strPoData);


      //virtual bool _load_text(string strLang);
      //virtual string _get_text(string strLang, string str);

      string __get_text(const ::string & strId);


   };


} // namespace user



