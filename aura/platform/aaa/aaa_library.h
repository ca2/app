#pragma once



namespace aura
{


   class CLASS_DECL_AURA library:
      virtual public ::object
   {
   public:

      
      string                        m_strFolder;
      string                        m_strName;
      void *                        m_plibrary;
      ::pointer<library>           m_pca2library;
      string                        m_strCa2Name;
      string                        m_strRoot;
      ::file::path                  m_strPath;
      string                        m_strMessage;
      bool                          m_bAutoUnload;
      pointer_array < library_object_allocator_base > m_allocatorptra;                     \


      library() {}
      virtual ~library();

      virtual void     initialize(::particle * pparticle);
      virtual void     initialize_aura_library(::particle * pparticle, int iDesmabi, const ::scoped_string & scopedstrRoot = nullptr, const ::scoped_string & scopedstrName = nullptr, const ::scoped_string & scopedstrFolder = nullptr);

      virtual bool open(const ::scoped_string & scopedstrPath,bool bAutoClose = true,bool bCa2Path = false);

      virtual bool open_ca2_library(string strTitle = "");

      library * get_ca2_library();


      virtual bool close();

      virtual void * get_os_data();


      virtual bool is_opened();
      virtual bool is_closed();

      template < typename TARGET >
      TARGET get(const ::scoped_string & scopedstrEntryName)
      {
         return reinterpret_cast <TARGET>(raw_get(scopedstrEntryName));
      }

      template < typename TARGET >
      TARGET & get(TARGET & ptarget, const ::scoped_string & scopedstrEntryName)
      {
         return ptarget = get<TARGET>(scopedstrEntryName);
      }

      void * raw_get(const ::scoped_string & scopedstrEntryName);




      virtual bool contains_app(const ::scoped_string & scopedstrAppId);


      virtual void get_create_impact_id_list(::array < atom > & ida);


      virtual string get_root();


      // impl
      virtual ::pointer<::aura::application>get_new_application(::particle * pparticle, const ::scoped_string & scopedstrAppId);
      virtual void get_app_list(string_array_base & stra);


      virtual ::matter* new_object(::object* pparticle, const ::scoped_string & scopedstrClass);


      virtual ::pointer<::matter>create_object(::object* pparticle, const ::scoped_string & scopedstrClass);
      virtual bool has_object_class(const ::string & lpszClass);


      virtual string get_library_name();

      virtual string get_app_id(const ::scoped_string & scopedstrAppName);
      virtual string get_app_name(const ::scoped_string & scopedstrAppId);

      virtual void get_extension_list(string_array_base & stra);


      virtual ::matter * factory_new(::particle * pparticle, const ::string & lpszClass);


      virtual ::pointer<::matter>factory_create(::particle * pparticle, const ::string & lpszClass);
      virtual bool factory_has_object_class(const ::string & lpszClass);

      library_object_allocator_base * find_allocator(const ::string & lpszClass);

      virtual void initialize_factory();


      virtual bool add_factory_item();


   };



   CLASS_DECL_AURA void * open_ca2_library(const ::scoped_string & scopedstr);





   template < class APP >
   class single_application_library:
      virtual public library
   {
   public:

      string m_strFileExt;

      single_application_library(const ::scoped_string & scopedstrRoot, const ::scoped_string & scopedstrFileExtension = nullptr)
      {

         m_strRoot = pszRoot;

      }

      // impl
      virtual ::pointer<::aura::application>get_new_application(::particle * pparticle, const ::scoped_string & scopedstrAppId) override;


      virtual void get_extension_list(string_array_base & stra) override;

   };



} // namespace aura







CLASS_DECL_AURA void * __node_library_open(const ::scoped_string & scopedstrPath, string & strMessage);
CLASS_DECL_AURA void * __node_library_touch(const ::scoped_string & scopedstrPath, string & strMessage);
CLASS_DECL_AURA void * __node_library_open_ca2(const ::scoped_string & scopedstrPath, string & strMessage);
CLASS_DECL_AURA bool __node_library_close(void * plibrary);
CLASS_DECL_AURA void * __node_library_raw_get(void * plibrary, const ::scoped_string & scopedstrEntryName);


CLASS_DECL_AURA ::acme::library * lib(const ::scoped_string & scopedstr);

#define LIBCALL(library, entry)  (lib(#library)->get<decltype(&entry)>(#entry))


CLASS_DECL_AURA ::file::path library_file_name(const ::scoped_string & scopedstr);





#define BEGIN_LIBRARY                                                   \
                                                                        \
                                                                        \
class library :                                                         \
   virtual public ::acme::library                                       \
{                                                                       \
public:                                                                 \
                                                                        \
                                                                        \
     library(::particle * pparticle) : ::acme::library(pparticle) {}          \
     virtual ~library(){}                                               \
                                                                        \
                                                                        \




#define BEGIN_CREATE_OBJECT                                             \
                                                                        \
                                                                        \
virtual void initialize_factory() override                              \
{


#define CREATE_OBJECT_ENTRY(name, TYPE) m_allocatorptra.add(__allocate library_object_allocator < TYPE > (name));

#define END_CREATE_OBJECT }

#define END_LIBRARY  };

#define BEG_ONLY_FACT BEGIN_LIBRARY \
 BEGIN_CREATE_OBJECT

#define END_ONLY_FACT(libname) END_CREATE_OBJECT \
 END_LIBRARY \
 \
CLASS_DECL_EXPORT ::acme::library * libname ## _ ## get_new_library(::particle * pparticle) \
{ \
\
   return aaa_primitive_new library(pparticle); \
 \
} \
 \
 \








