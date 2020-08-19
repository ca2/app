#pragma once


class CLASS_DECL_AURA zip_context :
   virtual public ::object
{
public:


   zip_context(::object * pobjectContext);
   virtual ~zip_context();


   virtual bool ls(::file::listing & listing);

   virtual __result(::zip::in_file) get_in_file(::file::file * pfile, const string_array & strPath, ::file::e_type * petype = nullptr);
   virtual bool is_file_or_dir(::file::file * pfile, const string_array & strPath, ::file::e_type * petype);
   virtual bool extract(memory & m, ::file::file * pfile, const string_array & strPath, ::file::e_type * petype = nullptr);

   //virtual bool extract(const char * pszFileName, const char * pszExtractFileName, ::file::e_type * petype = nullptr);

   virtual bool extract_all(const char * pszDir,var varFile, ::file::patha * ppatha = nullptr, string_array * pstraFilter = nullptr,bool_array * pbaBeginsFilterEat = nullptr);
   virtual bool is_unzippable(const char * pszFileName);

   virtual bool has_sub_folder(const char * pszFileName);



};





