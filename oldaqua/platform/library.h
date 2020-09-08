#pragma once



namespace aqua
{


   class CLASS_DECL_AQUA library:
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

      virtual ::estatus     initialize(::object * pobjectContext);
      virtual ::estatus     initialize_aura_library(::object * pobjectContext, int iDesmabi, const char * pszRoot = nullptr, const char * pszName = nullptr, const char * pszFolder = nullptr);

      virtual bool open(const char * pszPath,bool bAutoClose = true,bool bCa2Path = false);

      virtual bool open_ca2_library(string strTitle = "");

      library * get_ca2_library();


      virtual bool close();

      virtual void * get_os_data();


      virtual bool is_opened();
      virtual bool is_closed();

      template < typename TARGET >
      TARGET get(const char * pszEntryName)
      {
         return reinterpret_cast <TARGET>(raw_get(pszEntryName));
      }

      template < typename TARGET >
      TARGET & get(TARGET & ptarget, const char* pszEntryName)
      {
         return ptarget = get<TARGET>(pszEntryName);
      }

      void * raw_get(const char * pszEntryName);




      virtual bool contains_app(const char * pszAppId);


      virtual void get_create_view_id_list(::array < id > & ida);


      virtual string get_root();


      // impl
      virtual __result(::aqua::application) get_new_application(::object * pobjectContext, const char * pszAppId);
      virtual void get_app_list(string_array & stra);


      virtual ::generic_object* new_object(::object* pobjectContext, const char* pszClass);


      virtual __pointer(::generic_object) create_object(::object* pobjectContext, const char* pszClass);
      virtual bool has_object_class(const char * lpszClass);


      virtual string get_library_name();

      virtual string get_app_id(const char * pszAppName);
      virtual string get_app_name(const char * pszAppId);

      virtual void get_extension_list(string_array & stra);


      virtual ::generic_object * factory_new(::object * pobjectContext, const char * lpszClass);


      virtual __pointer(::generic_object) factory_create(::object * pobjectContext, const char * lpszClass);
      virtual bool factory_has_object_class(const char * lpszClass);

      library_object_allocator_base * find_allocator(const char * lpszClass);

      virtual void initialize_factory();


      virtual bool create_factory();


   };



   CLASS_DECL_AQUA void * open_ca2_library(const char * psz);





   template < class APP >
   class single_application_library:
      virtual public library
   {
   public:

      string m_strFileExt;

      single_application_library(const char * pszRoot, const char * pszFileExtension = nullptr)
      {

         m_strRoot = pszRoot;

      }

      // impl
      virtual __result(::aqua::application) get_new_application(::object * pobject, const char * pszAppId) override;


      virtual void get_extension_list(string_array & stra) override;

   };



} // namespace aqua







CLASS_DECL_AQUA void * __node_library_open(const char * pszPath, string & strMessage);
CLASS_DECL_AQUA void * __node_library_touch(const char * pszPath, string & strMessage);
CLASS_DECL_AQUA void * __node_library_open_ca2(const char * pszPath, string & strMessage);
CLASS_DECL_AQUA bool __node_library_close(void * plibrary);
CLASS_DECL_AQUA void * __node_library_raw_get(void * plibrary,const char * pszEntryName);


CLASS_DECL_AQUA ::aqua::library * lib(const char * psz);

#define LIBCALL(library, entry)  (lib(#library)->get<decltype(&entry)>(#entry))


CLASS_DECL_AQUA ::file::path libfilename(const string & str);





#define BEGIN_LIBRARY                                                   \
                                                                        \
                                                                        \
class library :                                                         \
   virtual public ::aqua::library                                       \
{                                                                       \
public:                                                                 \
                                                                        \
                                                                        \
     library(::object * pobject) : ::aqua::library(pobject) {}          \
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
CLASS_DECL_EXPORT ::aqua::library * libname ## _ ## get_new_library(::object * pobject) \
{ \
\
   return new library(pobject); \
 \
} \
 \
 \








