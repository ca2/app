#pragma once

//
//namespace windows
//{
//
//
//   namespace axis
//   {
//
//
//      class CLASS_DECL_AXIS dir:
//         virtual public ::windows::dir,
//         virtual public ::file::dir::axis::system
//      {
//      public:
//
//
//
//         dir(::object * pobject);
//
//
//         //virtual string relpath(const char * pcszSource,const char * lpcszRelative,const char * lpcsz2 = nullptr);
//
//         virtual ::file::listing & ls(::object * pobject, ::file::listing & ls);
//         virtual ::file::listing & ls_relative_name(::object * pobject, ::file::listing & ls);
//
//         //virtual bool  is(const char * pcsz,::object * pobject);
//
//         virtual bool  is_impl(const ::file::path & str,::object * pobject) override;
//         //virtual bool  name_is(const ::file::path & str,::object * pobject);
//         //virtual bool  is_inside(const char * pcszDir,const char * lpcszPath,::object * pobject);
//
//         //virtual bool  is_inside_time(const char * pcsz,::object * pobject);
//
//         //virtual bool mk(const char * pcsz,::object * pobject);
//
//         //virtual bool rm(::object * pobject,const char * psz,bool bRecursive = true);
//
//
//         //virtual string name(const char * pcsz);
//
//         //virtual string name(const string & str);
//
//         //virtual string time(const char * pcsz = nullptr,const char * lpcsz2 = nullptr);
//
//         //virtual string stage(const char * pcsz = nullptr,const char * lpcsz2 = nullptr);
//
//         //virtual string stageapp(const char * pcsz = nullptr,const char * lpcsz2 = nullptr);
//
//         //virtual string netseed(const char * pcsz = nullptr,const char * lpcsz2 = nullptr);
//
//
//         //// stage in ca2os spalib
//         //virtual string element(const char * pcsz,const char * lpcsz2 = nullptr);
//
//         //virtual string element();
//         //virtual string element(const string & str);
//         //virtual string element(const string & str,const string & str2);
//         //virtual string element(const char * pcsz,const string & str2);
//
//         //virtual string element(const string & str,const char * pcsz2);
//
//
//         //virtual string module(const char * pcsz = nullptr,const char * lpcsz2 = nullptr);
//
//         //virtual string ca2module(const char * pcsz = nullptr,const char * lpcsz2 = nullptr);
//
//         //virtual void time_square(string &str);
//         //virtual string time_log(const char * pszId);
//
//
//         //virtual string trash_that_is_not_trash(const char * psz);
//
//         //virtual string appdata(const char * pcsz = nullptr,const char * lpcsz2 = nullptr);
//
//         //virtual string commonappdata(const char * pcsz = nullptr,const char * lpcsz2 = nullptr);
//
//         //virtual string element_commonappdata(const string & strElement,const char * pcsz = nullptr,const char * lpcsz2 = nullptr);
//
//
//         //virtual string usersystemappdata(::object * pobject,const char * pcszPrefix,const char * lpcsz = nullptr,const char * lpcsz2 = nullptr);
//
//         //virtual string userappdata(::object * pobject,const char * pcsz = nullptr,const char * lpcsz2 = nullptr);
//
//         //virtual string userdata(::object * pobject,const char * pcsz = nullptr,const char * lpcsz2 = nullptr);
//
//         //virtual string userfolder(::object * pobject,const char * pcsz = nullptr,const char * lpcsz2 = nullptr);
//
//         //virtual string default_os_user_path_prefix(::object * pobject);
//         //virtual string default_userappdata(::object * pobject,const string & pcszPrefix,const string & lpcszLogin,const char * pszRelativePath = nullptr);
//
//         //virtual string default_userdata(::object * pobject,const string & pcszPrefix,const string & lpcszLogin,const char * pszRelativePath = nullptr);
//
//         //virtual string default_userfolder(::object * pobject,const string & pcszPrefix,const string & lpcszLogin,const char * pszRelativePath = nullptr);
//
//         //virtual string userquicklaunch(::object * pobject,const char * pszRelativePath = nullptr,const char * pcsz2 = nullptr);
//
//         //virtual string userprograms(::object * pobject,const char * pszRelativePath = nullptr,const char * pcsz2 = nullptr);
//
//
//         //virtual string commonprograms(const char * pszRelativePath = nullptr,const char * pcsz2 = nullptr);
//
//
//         virtual bool initialize();
//
//
//      };
//
//
//   } // namespace axis
//
//
//} // namespace windows
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
