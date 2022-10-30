#pragma once


#include "base/user/form/document.h"


namespace userfs
{


   class CLASS_DECL_CORE document :
      virtual public ::form_document
   {
   public:


      ::file::path                              m_pathFolder;
      ::pointer<::fs::set>                   m_pfsset;
      ::file::listing                           m_listingRoot;
      ::file::listing                           m_listingUser2;
      ::file::listing                           m_listingFinal2;
      ::file::listing                           m_listingFolderUser2;
      ::file::listing                           m_listingFolderFinal2;


      document();
      ~document() override;


      void initialize(::particle * pparticle) override;


      ::user::document * get_document();


      //virtual ::aura::application * get_app() const override;

//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;


      virtual bool browse(::pointer<::file::item>pitem, const ::action_context & action_context);


      inline ::fs::set * fs_data() { return m_pfsset; }


   };


} // namespace userfs



