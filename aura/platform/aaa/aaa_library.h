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
      __pointer(library)            m_pca2library;
      string                        m_strCa2Name;
      string                        m_strRoot;
      ::file::path                  m_strPath;
      string                        m_strMessage;
      bool                          m_bAutoUnload;
      __pointer_array(library_object_allocator_base) m_allocatorptra;                     \


      library() {}
      virtual ~library();

      virtual void     initialize(::object * pobject);
      virtual void     initialize_aura_library(::object * pobject, int iDesmabi, const ::string & pszRoot = nullptr, const ::string & pszName = nullptr, const ::string & pszFolder = nullptr);

      virtual bool open(const ::string & pszPath,bool bAutoClose = true,bool bCa2Path = false);

      virtual bool open_ca2_library(string strTitle = "");

      library * get_ca2_library();


      virtual bool close();

      virtual void * get_os_data();


      virtual bool is_opened();
      virtual bool is_closed();

      template < typename TARGET >
      TARGET get(const ::string & pszEntryName)
      {
         return reinterpret_cast <TARGET>(raw_get(pszEntryName));
      }

      template < typename TARGET >
      TARGET & get(TARGET & ptarget, const ::string & pszEntryName)
      {
         return ptarget = get<TARGET>(pszEntryName);
      }

      void * raw_get(const ::string & pszEntryName);




      virtual bool contains_app(const ::string & pszAppId);


      virtual void get_create_view_id_list(::array < id > & ida);


      virtual string get_root();


      // impl
      virtual __transport(::aura::application) get_new_application(::object * pobject, const ::string & pszAppId);
      virtual void get_app_list(string_array & stra);


      virtual ::matter* new_object(::object* pobject, const ::string & pszClass);


      virtual __pointer(::matter) create_object(::object* pobject, const ::string & pszClass);
      virtual bool has_object_class(const ::string & lpszClass);


      virtual string get_library_name();

      virtual string get_app_id(const ::string & pszAppName);
      virtual string get_app_name(const ::string & pszAppId);

      virtual void get_extension_list(string_array & stra);


      virtual ::matter * factory_new(::object * pobject, const ::string & lpszClass);


      virtual __pointer(::matter) factory_create(::object * pobject, const ::string & lpszClass);
      virtual bool factory_has_object_class(const ::string & lpszClass);

      library_object_allocator_base * find_allocator(const ::string & lpszClass);

      virtual void initialize_factory();


      virtual bool add_factory_item();


   };



   CLASS_DECL_AURA void * open_ca2_library(const ::string & psz);





   template < class APP >
   class single_application_library:
      virtual public library
   {
   public:

      string m_strFileExt;

      single_application_library(const ::string & pszRoot, const ::string & pszFileExtension = nullptr)
      {

         m_strRoot = pszRoot;

      }

      // impl
      virtual __transport(::aura::application) get_new_application(::object * pobject, const ::string & pszAppId) override;


      virtual void get_extension_list(string_array & stra) override;

   };



} // namespace aura







CLASS_DECL_AURA void * __node_library_open(const ::string & pszPath, string & strMessage);
CLASS_DECL_AURA void * __node_library_touch(const ::string & pszPath, string & strMessage);
CLASS_DECL_AURA void * __node_library_open_ca2(const ::string & pszPath, string & strMessage);
CLASS_DECL_AURA bool __node_library_close(void * plibrary);
CLASS_DECL_AURA void * __node_library_raw_get(void * plibrary, const ::string & pszEntryName);


CLASS_DECL_AURA ::acme::library * lib(const ::string & psz);

#define LIBCALL(library, entry)  (lib(#library)->get<decltype(&entry)>(#entry))


CLASS_DECL_AURA ::file::path libfilename(const ::string & str);





#define BEGIN_LIBRARY                                                   \
                                                                        \
                                                                        \
class library :                                                         \
   virtual public ::acme::library                                       \
{                                                                       \
public:                                                                 \
                                                                        \
                                                                        \
     library(::object * pobject) : ::acme::library(pobject) {}          \
     virtual ~library(){}                                               \
                                                                        \
                                                                        \




#define BEGIN_CREATE_OBJECT                                             \
                                                                        \
                                                                        \
virtual void initialize_factory() override                              \
{


#define CREATE_OBJECT_ENTRY(name, TYPE) m_allocatorptra.add(__new(library_object_allocator < TYPE >(name)));

#define END_CREATE_OBJECT }

#define END_LIBRARY  };

#define BEG_ONLY_FACT BEGIN_LIBRARY \
 BEGIN_CREATE_OBJECT

#define END_ONLY_FACT(libname) END_CREATE_OBJECT \
 END_LIBRARY \
 \
CLASS_DECL_EXPORT ::acme::library * libname ## _ ## get_new_library(::object * pobject) \
{ \
\
   return new library(pobject); \
 \
} \
 \
 \








