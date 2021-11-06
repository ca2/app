#pragma once


class CLASS_DECL_APEX zip_context :
   virtual public ::object
{
public:


   zip_context(::object * pobject);
   virtual ~zip_context();


   virtual bool ls(::file::listing & listing);

   virtual __transport(::zip::in_file) get_in_file(::file::file * pfile, const string_array & strPath, ::file::enum_type * petype = nullptr);
   virtual bool is_file_or_dir(::file::file * pfile, const string_array & strPath, ::file::enum_type * petype);
   virtual bool extract(memory & m, ::file::file * pfile, const string_array & strPath, ::file::enum_type * petype = nullptr);

   //virtual bool extract(const char * pszFileName, const char * pszExtractFileName, ::file::enum_type * petype = nullptr);

   virtual bool extract_all(const char * pszDir,::payload payloadFile, ::file::patha * ppatha = nullptr, string_array * pstraFilter = nullptr,bool_array * pbaBeginsFilterEat = nullptr);
   virtual bool is_unzippable(const char * pszFileName);

   virtual bool has_sub_folder(const char * pszFileName);



};





