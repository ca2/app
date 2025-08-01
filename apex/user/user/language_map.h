#pragma once


////#include "acme/prototype/prototype/object.h"
#include "acme/prototype/collection/string_map.h"
//#include "acme/prototype/collection/string_array.h"


namespace user
{


   class CLASS_DECL_APEX language_map :
      virtual public ::object
   {
   public:


      ::int_sz *                                      m_pintstring;
      string_map < ::pointer<::user::language >>      m_languagemap;
      string_array                                    m_straLang;
      string                                          m_strLang;
      string_to_string *                              m_pstringmap;
      ::pointer<::user::language>                     m_planguage;


      language_map();
      ~language_map() override;


      virtual void initialize(::particle * pparticle) override;


      virtual bool set_language_resource_map(::int_sz * pstringintLanguageResourceMap);

      virtual string load_podata(const ::scoped_string & scopedstrLang, bool bOnlyHeader = false);

      virtual string get_language();
      virtual bool set_language(::apex::application * papp, const ::scoped_string & scopedstrLang);
      virtual bool set_default_language(::apex::application * papp);

      //virtual bool set_language_sel(::collection::index iSel);


      ///// get_current_language() -> data_get_current_language() -> datastream()->get("language")
      //virtual string get_current_language();
      ///// set_current_language() -> data_set_current_language() -> datastream()->set("language")
      //virtual bool set_current_language(const ::scoped_string & scopedstrLang);
      //virtual bool set_current_language(::collection::index iSel);


      virtual ::collection::index get_language_list(string_array & stra);
      virtual ::collection::index get_text_list(string_array & stra, const ::scoped_string & scopedstrText, bool bFull = false);
      virtual string_array get_text_list(const ::scoped_string & scopedstrText, bool bFull = false);


      virtual void parse_podata(const ::scoped_string & scopedstrPoData);


      //virtual bool _load_text(const ::scoped_string & scopedstrLang);
      //virtual string _get_text(const ::scoped_string & scopedstrLang, const ::scoped_string & scopedstr);

      string __get_text(const ::scoped_string & scopedstrId);


   };


} // namespace user



