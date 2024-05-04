// Create on 2021-03-21 00:11 <3ThomasBS_
#pragma once


class string_to_string_lookup;


class CLASS_DECL_ACME acme_path :
   virtual public particle
{
public:


   ::IDENTIFIER_SUFFIX_OPERATING_SYSTEM(acme_)::acme_path *    m_pplatformpath;
   ::acme_directory *                                          m_pacmedirectory;
   ::acme_file *                                               m_pacmefile;


   acme_path();
   ~acme_path() override;
   
   
   virtual ::string icloud_container_identifier(const char * psz_iCloudContainerIdentifier);
   
   virtual ::file::path defer_get_icloud_container_path(const ::file::path & path, const char * psz_iCloudContainerIdentifier);

   virtual void defer_get_icloud_container_path_name(::string & strName, ::string & str_iCloudContainerIdentifier, const ::file::path & path);


   virtual  string from(string str);

   virtual void safe_real_path(::file::path & path);

   virtual ::file::path get_uniform_resource_locator(const ::file::path& path);

   virtual ::file::path safe_get_real_path(const ::file::path & path);

   virtual ::file::path _safe_real_path(const ::file::path & path);

   virtual ::file::path real_path(const ::file::path & path);

   virtual ::file::path _real_path(const ::file::path & path);



   virtual bool case_insensitive_real_path_begins_eat(string & str, const ::scoped_string & scopedstrPrefix);

   virtual bool real_path_is_same(const ::file::path & path1, const ::file::path & path2);

   virtual ::file::enum_type get_type(const ::file::path & path);

   virtual ::file::enum_type safe_get_type(const ::file::path & path);

   virtual void create_symbolic_link(const ::scoped_string & scopedstrLink, const ::scoped_string & scopedstrSource);

   virtual bool is_symbolic_link(const ::scoped_string & scopedstrLink);

   virtual ::file::path symbolic_link_destination(const ::scoped_string & scopedstrLink);



   virtual bool has_custom_icon(const ::file::path & path);


   ::file::path defer_process_relative_path(const ::file::path & path, const ::file::path & pathFolder = "");

   virtual bool defer_process_protocol_path(::file::path & path);
   
   virtual ::file::path get_absolute_path(const ::scoped_string & scopedstr);
   virtual bool is_absolute_path(const ::scoped_string & scopedstr);

   
   //::pointer < ::file::link > resolve_link(const ::file::path &path);
   virtual ::pointer < ::file::link > resolve_link(const ::file::path & path, ::file::e_link elink = ::file::e_link_all);



   virtual void rename(const ::file::path& pathNewName, const ::file::path& pathOldName);
   virtual ::file::path get_sequence_path(const ::file::path& path, ::raw::index iSequence, int iZeroPaddingWidth = 1);
   virtual void defer_free_name_by_renaming_to_last_in_sequence(const ::file::path& path, int iZeroPaddingWidth = 1);


   virtual ::file::e_type executable_type(const ::file::path & path);

   virtual void determine_executable(::file::path & path);

   virtual ::file::path defer_apply_working_directory(const ::file::path &path, const ::file::path &working_directory);
   /// A Default search path for PATH environment variable;
   virtual ::string get_default_path();

   /// get next entry in a PATH-environment-variable-like value
   bool get_next_path(::scoped_string & scopedstr, ::string::RANGE & rangePath);


   virtual ::file::path _path_get_path(const scoped_string & scopedstrCommand, const ::scoped_string & scopedstrPath, string_to_string_lookup * plookupEnvironment);


   virtual ::file::path path_get_path(const scoped_string & scopedstrCommand, string_to_string_lookup * plookupEnvironment);


   virtual ::file::path path_try_get_path(const scoped_string & scopedstrCommand, string_to_string_lookup * plookupEnvironment);


};



