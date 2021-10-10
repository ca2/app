#pragma once


namespace userfs
{


   class CLASS_DECL_CORE document :
      virtual public ::form_document
   {
   public:


      ::file::path                              m_pathFolder;
      __composite(::fs::set)                    m_pfsset;
      ::file::listing                           m_listingRoot;
      ::file::listing                           m_listingUser2;
      ::file::listing                           m_listingFinal2;
      ::file::listing                           m_listingFolderUser2;
      ::file::listing                           m_listingFolderFinal2;


      document();
      virtual ~document();


      virtual ::e_status initialize(::object * pobject) override;


      ::user::document * get_document();


      //virtual ::aura::application * get_application() const override;

      void assert_valid() const override;
      void dump(dump_context & dumpcontext) const override;


      virtual bool browse(__pointer(::file::item) pitem, const ::action_context & action_context);


      inline __pointer(::fs::set) fs_data() { return m_pfsset; }


   };


} // namespace userfs



