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


      virtual void initialize_filemanager_component(::object * pobject);

      virtual void filemanager_finalize();


      __pointer(data) filemanager_create_data(atom atom);


      id_map < __composite(data) > & datamap() { return m_datamap; }


      void filemanager_set_data(atom idData, data * pdata);


      void filemanager_set_doc_template(atom idTemplate, ::user::multiple_document_template * pdata);



      void filemanager_load_project(const ::file::path & pathFileManagerProject, ::create * pcreate = nullptr, ::fs::data * pfsdata = nullptr, callback * pcallback = nullptr);

      void filemanager_save_project();

      document * find_filemanager(::payload payloadFile);

      document * restore_filemanager(::payload payloadFile, ::create * pcreate = nullptr, ::fs::data * pfsdata = nullptr, callback * pcallback = nullptr);

      document * open_filemanager(::payload payloadFile, ::create * pcreate = nullptr, ::fs::data * pfsdata = nullptr, callback * pcallback = nullptr);

      document * add_filemanager(const ::file::path & pathFolder, ::create * pcreate = nullptr, ::fs::data * pfsdata = nullptr, callback * pcallback = nullptr);

      bool erase_filemanager(::payload payloadFile);

      bool erase_filemanager(document * pdocument);


      /// atom = FILEMANAGER_IMPACT - behaviour
      /// if there is main "pane_impact" (create this concecpt of main pane_impact!!)
      /// open the (already existing concept) of "pane_impact" FILEMANAGER_IMPACT
      /// (even if the tab is not already there)
      /// otherwise open a detached window

      /// other ids? SAME BEHAVIOUR!! for that/this atom.

      //document * open_main(::aura::application * pappOnBehalfOf, ::atom atom = -1, ::create * pcreate = nullptr, ::fs::data * pfsdata = nullptr, callback * pcallback = nullptr);
      //document * open_child(bool bMakeVisible = true, bool bTransparentBackground = false, __pointer(::user::interaction) puiParent = nullptr, callback * pcallback = nullptr);
      data * filemanager(atom atom = FILEMANAGER_IMPACT);
      //document * get_list(atom atom);
      //document * get_folder_selection_list(atom atom);

      //document * filemanager_create_new_document(callback * pinterface, ::create * pcreate);


   };


} // namespace filemanager



