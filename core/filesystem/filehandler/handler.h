#pragma once


////#include "acme/primitive/primitive/object.h"


namespace filehandler
{


   class CLASS_DECL_CORE handler :
      virtual public ::object
   {
   public:



      enum id_type
      {
         topic_type_root,
         topic_type_extension,
         topic_type_mime_type
      };


      ::pointer<tree_interface>     m_ptree;


      id_type                     m_etopictype;
      string                           m_strTopic;
      string_array                     m_straHandlerLibrary;
      string_array                     m_straMenuLibrary;
      string_array                     m_straApp;


      handler();
      virtual ~handler();


      virtual void initialize(::particle * pparticle) override;


      string get_text(::pointer<::data::tree>ptree);
      index get_image(::pointer<::data::tree>ptree);


      void defer_add_library(::acme::library * plibrary);
      void add_library(::filehandler::library * plibrary);
      void add_menu_library(menu_library * plibrary);


      ::pointer<::data::tree_item>get_extension_tree_item(const ::string & pszExtension, bool bCreate);
      ::pointer<::data::tree_item>get_mime_type_tree_item(const ::string & pszMimeType, bool bCreate);


      virtual void get_extension_app(string_array & straAppId, const ::string & pszExtension);
      virtual void get_mime_type_app(string_array & straAppId, const ::string & pszMimeType);


      //virtual ::stream & write(::stream & stream) const override;
      //virtual ::stream & read(::stream & stream) override;


   };


} // namespace filehandler






