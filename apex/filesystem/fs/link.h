#pragma once


namespace fs
{


   // fs::interface - file system interface


   class CLASS_DECL_APEX link:
      virtual public ::fs::native
   {
   public:



      ::file::path                  m_strTitle;
      __pointer(::file::listing)    m_plisting;


      link();
      virtual ~link();

      virtual ::e_status initialize(::object * pobject) override;

      virtual ::file::listing & ls(::file::listing & listing) override;


      virtual void defer_fill_folder(string strTitle, ::file::path pathFolder);

      virtual bool has_subdir(const ::file::path & pszPath) override;
      virtual int is_dir(const ::file::path & path) override;
      virtual ::file::listing & root_ones(::file::listing & listing) override;

      virtual void fill_os_user();

      virtual void fill_os_user_desktop();

      virtual bool tree_show_subdir(const ::file::path & pszPath) override;


   };



} // namespace fs







