#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE component :
      virtual public ::object
   {
   public:


      id_map < __composite(data) >                       m_datamap;

      bool                                               m_bRestoring;


      __composite(::user::multiple_document_template)    m_pdocumenttemplateForm;
      __composite(::user::multiple_document_template)    m_pdocumenttemplateOperation;

      ::file::path                                       m_pathFilemanagerProject;


      component();
      virtual ~component();



      inline ::core::session* get_session() const;
      inline ::core::user* user() const;

      //virtual i64 add_ref(OBJ_REF_DBG_PARAMS) override
      //{

      //   return ::apex::department::add_ref(OBJ_REF_DBG_ARGS);

      //}


      /*     virtual i64 dec_ref(OBJ_REF_DBG_PARAMS) override
           {

              return ::apex::department::dec_ref(OBJ_REF_DBG_ARGS);

           }*/


      virtual ::e_status initialize_filemanager_component(::object * pobject);

      virtual void filemanager_finalize();


      __pointer(data) filemanager_create_data(id id);


      id_map < __composite(data) > & datamap() { return m_datamap; }


      void filemanager_set_data(id idData, data * pdata);


      void filemanager_set_doc_template(id idTemplate, ::user::multiple_document_template * pdata);



      void filemanager_load_project(const ::file::path & pathFileManagerProject, ::create * pcreate = nullptr, ::fs::data * pfsdata = nullptr, callback * pcallback = nullptr);

      void filemanager_save_project();

      document * find_filemanager(::payload varFile);

      document * restore_filemanager(::payload varFile, ::create * pcreate = nullptr, ::fs::data * pfsdata = nullptr, callback * pcallback = nullptr);

      document * open_filemanager(::payload varFile, ::create * pcreate = nullptr, ::fs::data * pfsdata = nullptr, callback * pcallback = nullptr);

      document * add_filemanager(const ::file::path & pathFolder, ::create * pcreate = nullptr, ::fs::data * pfsdata = nullptr, callback * pcallback = nullptr);

      bool remove_filemanager(::payload varFile);

      bool remove_filemanager(document * pdocument);


      /// id = FILEMANAGER_IMPACT - behaviour
      /// if there is main "pane_view" (create this concecpt of main pane_view!!)
      /// open the (already existing concept) of "pane_view" FILEMANAGER_IMPACT
      /// (even if the tab is not already there)
      /// otherwise open a detached window

      /// other ids? SAME BEHAVIOUR!! for that/this id.

      //document * open_main(::aura::application * pappOnBehalfOf, ::id id = -1, ::create * pcreate = nullptr, ::fs::data * pfsdata = nullptr, callback * pcallback = nullptr);
      //document * open_child(bool bMakeVisible = true, bool bTransparentBackground = false, __pointer(::user::interaction) puiParent = nullptr, callback * pcallback = nullptr);
      data * filemanager(id id = FILEMANAGER_IMPACT);
      //document * get_list(id id);
      //document * get_folder_selection_list(id id);

      //document * filemanager_create_new_document(callback * pinterface, ::create * pcreate);


   };


} // namespace filemanager



