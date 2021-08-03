#pragma once


namespace acme
{


   class CLASS_DECL_ACME library:
      virtual public ::matter
   {
   public:


      __pointer(::factory_map)      m_pfactorymap;
      string                        m_strFolder;
      string                        m_strName;
      void *                        m_plibrary;
      __pointer(library)            m_pca2library;
      string                        m_strCa2Name;
      string                        m_strRoot;
      ::file::path                  m_strPath;
      string                        m_strMessage;
      bool                          m_bAutoUnload;
      //__pointer_array(library_object_allocator_base) m_allocatorptra;                     \


      library() {}
      virtual ~library();

      virtual void assert_valid() const override;
      virtual void dump(dump_context &) const override;

      virtual ::e_status     initialize_matter(::matter * pmatter) override;
      virtual ::e_status     initialize_library(::matter* pmatter, int iDesmabi, const char * pszRoot = nullptr, const char * pszName = nullptr, const char * pszFolder = nullptr);

      virtual bool open(const char * pszPath,bool bAutoClose = true,bool bCa2Path = false);

      virtual bool open_library(string strTitle = "");

      library * get_library();


      virtual ::factory_map * factory_map() { return m_pfactorymap; }


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


      virtual void get_create_view_id_list(::array < ::id > & ida);


      virtual string get_root();


      // impl
      virtual __transport(::matter) new_application(const char * pszAppId);
      virtual void get_app_list(string_array & stra);

      
      virtual ::matter* new_object(const char* pszClass);
      
      template < typename BASE_TYPE >
      inline __pointer(BASE_TYPE) new_object()
      {
         return m_pfactorymap->new_object <BASE_TYPE>();
      }

      template < typename BASE_TYPE >
      inline ::e_status __construct(__pointer(BASE_TYPE) & p)
      {

         auto pNew = m_pfactorymap->new_object <BASE_TYPE>();

         if (!pNew)
         {

            return error_no_factory;

         }
         
         p = pNew;

         if (!p)
         {

            return error_no_interface;

         }

         return ::success;

      }


      template < typename BASE_TYPE >
      inline ::e_status __defer_construct(__pointer(BASE_TYPE)& p)
      {

         ::e_status estatus = ::success_not_constructed;

         if (!p)
         {

            estatus = __construct(p);
         }

         return estatus;

      }


      virtual __pointer(::matter) create_object(const char* pszClass);
      virtual bool has_object_class(const char * lpszClass);


      virtual string get_library_name();

      virtual string get_app_id(const char * pszAppName);
      virtual string get_app_name(const char * pszAppId);

      virtual void get_extension_list(string_array & stra);


      // virtual ::matter * factory_new(::object * pobject, const char * lpszClass);


      //virtual __pointer(::matter) factory_create(const char * lpszClass);
      //virtual bool factory_has_object_class(const char * lpszClass);

      //library_object_allocator_base * find_allocator(const char * lpszClass);

      //virtual void initialize_factory();


      //virtual bool create_factory();

      virtual ::e_status factory_exchange(::factory_map * pfactorymap);


   };



   CLASS_DECL_ACME void * open_ca2_library(const char * psz);




   
   using library_map = string_map < __pointer(::acme::library) >;


} // namespace acme






// [HERE] 
//  __node_library should be here at acme
// 
//  -- e.g. cannot lie inside a plugin, 
// because it is used to load a plugin
//
CLASS_DECL_ACME void * __node_library_open(const char * pszPath, string & strMessage);
CLASS_DECL_ACME void * __node_library_touch(const char * pszPath, string & strMessage);
CLASS_DECL_ACME void * __node_library_open_ca2(const char * pszPath, string & strMessage);
CLASS_DECL_ACME bool __node_library_close(void * plibrary);
CLASS_DECL_ACME void * __node_library_raw_get(void * plibrary,const char * pszEntryName);


//CLASS_DECL_ACME ::acme::library * lib(const char * psz);

#define LIBCALL(library, entry)  (get_system()->lib(#library)->get<decltype(&entry)>(#entry))


CLASS_DECL_ACME ::file::path libfilename(const ::string & str);





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





extern "C"
typedef ::acme::library* NEW_LIBRARY();

typedef NEW_LIBRARY* PFN_NEW_LIBRARY;



typedef ::matter * NEW_MATTER();

typedef NEW_MATTER* PFN_NEW_MATTER;



