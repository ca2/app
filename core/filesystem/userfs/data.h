#pragma once


#include "acme/prototype/data/data.h"
#include "base/user/form/document.h"
#include "acme/filesystem/filesystem/listing.h"


namespace userfs
{


   class CLASS_DECL_CORE data :
      virtual public ::data::data
   {
   public:


      ::file::path                              m_pathFolder;
      ::pointer<::fs::set>                      m_pfsset;
      //::pointer<::userfs::list_data>            m_puserfslistdata;
      ::file::listing                           m_listingRoot2;
      ::file::listing                           m_listingUser2;
      ::file::listing                           m_listingFinal2;
      ::file::listing                           m_listingFolderUser2;
      ::file::listing                           m_listingFolderFinal2;
      ::userfs::enum_mode                       m_emode;

      ::pointer<::file::item>                   m_pitem;

      bool                                m_bFullBrowse;


      data();
      ~data() override;


      void initialize(::particle * pparticle) override;


      ::user::document * get_document();

      //virtual string get_last_browse_path(::particle * pparticle, const ::string & pszDefault = nullptr);

      //virtual ::aura::application * get_app() const override;

//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;


      virtual void browse_initial_path(const ::action_context & action_context);
      virtual void browse(const ::file::path & path, const ::action_context & action_context);
      virtual void browse(::pointer<::file::item>pitem, const ::action_context & action_context);

      virtual void __browse(::pointer<::file::item>pitem, const ::action_context & action_context);

//      virtual void __full_browse(::pointer<::file::item>pitem, const ::action_context & action_context);

      virtual ::fs::set * fs_data();


      //inline ::fs::set * fs_data() { return m_pfsset; }


   };


} // namespace userfs



