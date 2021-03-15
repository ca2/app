#pragma once


namespace filehandler
{


   class CLASS_DECL_CORE handler :
      virtual public ::object
   {
   public:



      enum e_topic_type
      {
         topic_type_root,
         topic_type_extension,
         topic_type_mime_type
      };


      __composite(tree_interface)      m_ptree;


      e_topic_type                     m_etopictype;
      string                           m_strTopic;
      string_array                     m_straHandlerLibrary;
      string_array                     m_straMenuLibrary;
      string_array                     m_straApp;


      handler();
      virtual ~handler();


      virtual ::e_status initialize(::context_object * pcontextobject) override;


      string get_text(__pointer(::data::tree) ptree);
      index get_image(__pointer(::data::tree) ptree);


      void defer_add_library(::apex::library * plibrary);
      void add_library(::filehandler::library * plibrary);
      void add_menu_library(menu_library * plibrary);


      __pointer(::data::tree_item) get_extension_tree_item(const char * pszExtension, bool bCreate);
      __pointer(::data::tree_item) get_mime_type_tree_item(const char * pszMimeType, bool bCreate);


      virtual void get_extension_app(string_array & straAppId, const char * pszExtension);
      virtual void get_mime_type_app(string_array & straAppId, const char * pszMimeType);


      //virtual ::stream & write(::stream & stream) const override;
      //virtual ::stream & read(::stream & stream) override;


   };


} // namespace filehandler






