#pragma once


class CLASS_DECL_APEX zip_context :
   virtual public ::object
{
public:


   zip_context(::particle * pparticle);
   virtual ~zip_context();


   virtual bool ls(::file::listing_base & listing);

   ::pointer<::file_container>get_in_file(::file::file * pfile, const string_array_base & strPath, ::file::enum_type * petype);
   virtual bool is_file_or_dir(::file::file * pfile, const string_array_base & strPath, ::file::enum_type * petype);
   virtual bool extract(memory & m, ::file::file * pfile, const string_array_base & strPath, ::file::enum_type * petype = nullptr);

   //virtual bool extract(const ::file::path & path, const ::scoped_string & scopedstrExtractFileName, ::file::enum_type * petype = nullptr);

   virtual bool e_extract_all(const ::scoped_string& scopedstrDir, ::payload payloadFile, ::file::path_array_base* ppatha = nullptr, string_array_base* pstraFilter = nullptr, bool_array* pbaBeginsFilterEat = nullptr, , ::function<void(const::scoped_string& scopedstr) > functionCallback = {});
   virtual bool is_unzippable(const ::file::path & path);

   virtual bool has_sub_folder(const ::file::path & path);



};





