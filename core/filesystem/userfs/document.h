#pragma once


#include "base/user/form/document.h"
#include "acme/filesystem/filesystem/listing.h"


namespace userfs
{


   class CLASS_DECL_CORE document :
      virtual public ::form_document
   {
   public:


      ::pointer<::userfs::data>            m_puserfsdata;
      //::file::path                              m_pathFolder;
      //::pointer<::fs::set>                      m_pfsset;
      //::file::listing                           m_listingRoot;
      //::file::listing                           m_listingUser2;
      //::file::listing                           m_listingFinal2;
      //::file::listing                           m_listingFolderUser2;
      //::file::listing                           m_listingFolderFinal2;
      //::userfs::enum_mode                 m_emode;


      document();
      ~document() override;


      void initialize(::particle * pparticle) override;


      bool on_open_data(::data::data * pdata) override;


      //::user::document * get_document();

      virtual void defer_initialize_filemanager();

      ::userfs::data * filemanager_data();

      //virtual ::aura::application * get_app() const override;

//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;


      //virtual bool browse(::pointer<::file::item>pitem, const ::action_context & action_context);


            virtual void browse_initial_path(const ::action_context & action_context);
            //virtual void _001Refresh();



      virtual void browse(const ::file::path & path, const ::action_context & action_context);
      virtual bool browse(::pointer<::file::item>pitem, const ::action_context & action_context);

      virtual void OnFileManagerBrowse(const ::action_context & action_context);

   };


} // namespace userfs



