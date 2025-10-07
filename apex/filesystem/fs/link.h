#pragma once


#include "native.h"
//#include "acme/filesystem/filesystem/path.h"


namespace fs
{


   // fs::interface - file system interface


   class CLASS_DECL_APEX link:
      virtual public ::fs::native
   {
   public:



      ::file::path                     m_strTitle;
      ::pointer < ::file::listing >    m_plisting;


      link();
      ~link() override;

      virtual void initialize(::particle * pparticle) override;

      //virtual bool _enumerates(::file::listing_base & listing) override;
      bool enumerate(::file::listing_base & listing) override;


      virtual void defer_fill_folder(const ::scoped_string & scopedstrTitle, ::file::path pathFolder);

      virtual bool has_subdir(const ::file::path & path) override;
      virtual int is_dir(const ::file::path & path) override;
      virtual ::file::listing_base & root_ones(::file::listing_base & listing) override;

      virtual void fill_os_user();

      virtual void fill_os_user_desktop();

      virtual bool tree_show_subdir(const ::file::path & path) override;


   };



} // namespace fs







