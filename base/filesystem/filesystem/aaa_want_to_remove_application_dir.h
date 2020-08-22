#pragma once


namespace file
{


   class CLASS_DECL_AURA application_dir :
      virtual public ::object
   {
   public:

      application_dir();
      virtual ~application_dir();


      //virtual string_array locale_schema_matter(string & strLocale, const string & strStyle);
      //virtual string_array locale_schema_matter(string & strLocale, const string & strStyle, const string & pathRoot, const ::file::path & pathDomain);
      virtual string matter(const ::file::patha & patha, bool bDir = false);
      virtual string matter(const ::file::path & path, bool bDir = false);

      virtual void   matter_ls(const ::file::path & str, ::file::patha & stra);
      virtual ::file::path matter_file(const ::file::path & path,bool bDir = false);
      virtual void   matter_ls_file(const ::file::path & str,::file::patha & stra);

      //virtual ::file::path usersystemappdata(const string & pcszPrefix);

      //virtual ::file::path userappdata();
      //virtual ::file::path userdata();
      //virtual ::file::path userfolder();
      //virtual ::file::path default_os_user_path_prefix();
      //virtual ::file::path default_userappdata(const string & pcszPrefix, const string & lpcszLogin );

      //virtual ::file::path default_userdata(const string & pcszPrefix, const string & lpcszLogin);

      //virtual ::file::path default_userfolder(const string & pcszPrefix, const string & lpcszLogin);



      virtual ::file::path userquicklaunch();
      virtual ::file::path userprograms();


      virtual listing & ls(listing & listing);
      virtual listing & ls_relative_name(listing & listing);


      virtual bool  has_subdir(const ::file::path & pcsz);

      virtual bool  is(const ::file::path & pcsz);

      //virtual bool  is(const string & str);
      //virtual bool  is(const var & var);
      virtual bool  is_inside(const ::file::path & pcszDir, const ::file::path & lpcszPath);

      virtual bool  is_inside_time(const ::file::path & pcsz);

      virtual ::file::listing & root_ones(::file::listing & listing);
      virtual bool  mk(const ::file::path & pcsz);

      virtual bool  rm(const ::file::path & psz, bool bRecursive = true);

      virtual ::file::path pathfind(const string & pszEnv,const string & pszTopic,const string & pszMode);

      virtual ::file::path dropbox();
         
         
      virtual ::file::path onedrive();


   };


   typedef pointer < application_dir > application_dir_pointer;



} // namespace file







