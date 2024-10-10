#pragma once



#include "core/filesystem/userfs/data.h"
#include "apex/database/key.h"
#include "acme/prototype/prototype/action_context.h"


namespace user
{

   
   class tree;


} // namespace user


namespace filemanager
{


   class CLASS_DECL_CORE data :
      virtual public ::userfs::data
   {
   public:


      // most changed parameters
      /// ::aura::application *   m_pappOnBehalfOf; use this data app; (through * pobjec parameter)
      /// a filemanager doesn't actually act in behalf of app but of user!
      /// user->>> session
      /// the only current app things are matter resource assets
      /// fix this concept if there are app exclusive file systems.... but,
      /// other file systems can be included in more incluse fs::data
      /// (or just exclusive file systems at fs::data (ftp only file system?)
      ::pointer<::request>                   m_prequest;
      ::file::path                           m_filepath;
      bool                                   m_bMakeVisible;
      bool                                   m_bTransparentBackground;
      //::user::interaction *                  m_puserinteractionParent;
      ::pointer<::fs::data>                  m_pfsdata;
      ::pointer < ::filemanager::callback >  m_pfilemanagercallback;
      //bool bMakeVisible = true, bool bTransparentBackground = false, ::pointer<::user::interaction>puiParent = nullptr, ::fs::data * pfsdata = nullptr, ::pointer<data>data = nullptr, callback * pcallback = nullptr
      //::user::multiple_document_template *   m_pimpactsystem;
      ::write_text::font_pointer             m_pfont;
      ::pointer < ::user::document >         m_pdocumentTopic;
      ::pointer < ::filemanager::document >  m_pfilemanagerdocument;
      string                                 m_strTitle;
      ::type_atom                            m_typeatomFileList;
      // callback *                          m_pfilemanager;
      // callback *                          m_pcallback;
      // bool                                m_bTransparentBackground;
      ::string                               m_strDataKey;
      ::user::place_holder *                 m_pholderFileList;
      ::user::tree *                         m_ptreeFileTreeMerge;
      bool                                   m_bSetBergedgeTopicFile;
      property_set                           m_setToolbar;
      bool                                   m_bEnableRecursiveFolderSelectionList;
      atom                                   m_atom;
      string                                 m_strCopy;
      ::file::path                           m_pathDefault;
      string                                 m_strMenuBar;
      string                                 m_strDialogBar;
      string                                 m_strPopup;
      string                                 m_strXmlPopup;
      string                                 m_strXmlPopupSubstId;

      string                                 m_strFolderPopup;

      atom                                   m_atomExpandBox;
      atom                                   m_atomCollapseBox;

      ::string                               m_strDataKeyStatic;


      ::pointer<file_list_callback>          m_pfilelistcallback;

      string                                 m_strLevelUp;
      i32                                    m_iIconSize;
      bool                                   m_bListText;
      bool                                   m_bListSelection;
      bool                                   m_bFileSize;
      bool                                   m_bPassBk;
      bool                                   m_bIconImpact;


      data();
      ~data() override;


      // void assert_ok() const override;
      // virtual void dump(dump_context& dumpcontext) const override;


      bool is_topic();


      virtual void initialize_filemanager_data(::particle * pparticle);

      
      //bool open(::apex::application * pappOnBehalfOf = nullptr, ::file::path path = "", const ::action_context & action_context = ::e_source_system);
      void browse_initial_path(const ::action_context & action_context) override;
      //virtual void __browse_initial_path(const ::action_context & action_context);
      
      //::filemanager::document * open(::file::path path = "");
      //virtual ::filemanager::document * document();
      

      //virtual bool do_prompt_file_name(::payload & payloadFile, string nIDSTitle, u32 lFlags, bool bOpenFileDialog, ::user::impact_system * ptemplate, ::user::document * pdocument);

      //virtual bool open_document(::user::document * pdocument);

      virtual void save_document(::user::document * pdocument);


      //virtual void defer_update_data_key() override;


      virtual ::atom get_local_machine_id();
      virtual string get_last_browse_path(::particle * pparticle, const ::string & pszDefault = nullptr);
      virtual void set_last_browse_path(::particle * pparticle, const ::file::path & path);


   };


} // namespace filemanager




