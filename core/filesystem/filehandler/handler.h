#pragma once

#include "acme/prototype/data/tree_item.h"
#include "acme/prototype/data/tree.h"
#include "item.h"


namespace filehandler
{


   class tree_interface;
   class library;
   class menu_library;


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
      string_array_base                     m_straHandlerLibrary;
      string_array_base                     m_straMenuLibrary;
      string_array_base                     m_straApp;


      handler();
      virtual ~handler();


      virtual void initialize(::particle * pparticle) override;


      string get_text(::pointer<::data::tree<item>>ptree);
      ::collection::index get_image(::pointer<::data::tree<item>>ptree);


      void defer_add_library(::acme::library * plibrary);
      void add_library(::filehandler::library * plibrary);
      void add_menu_library(menu_library * plibrary);


      ::pointer<::data::tree_item<item>>get_extension_tree_item(const ::scoped_string & scopedstrExtension, bool bCreate);
      ::pointer<::data::tree_item<item>>get_mime_type_tree_item(const ::scoped_string & scopedstrMimeType, bool bCreate);


      virtual void get_extension_app(string_array_base & straAppId, const ::scoped_string & scopedstrExtension);
      virtual void get_mime_type_app(string_array_base & straAppId, const ::scoped_string & scopedstrMimeType);


      //virtual ::stream & write(::stream & stream) const override;
      //virtual ::stream & read(::stream & stream) override;


   };


} // namespace filehandler






