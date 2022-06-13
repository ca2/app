#pragma once


namespace acme
{


   class CLASS_DECL_ACME library:
      virtual public ::matter
   {
   public:


      string                                          m_strFolder;
      string                                          m_strName;
      void *                                          m_plibrary;
      string                                          m_strMessage;
      PFN_factory                                     m_pfnFactory;


      //static ::mutex *                                s_pmutexLoading;
      //static ::acme::library *                        s_plibraryLoading;


      library();
      ~library() override;

      void assert_ok() const override;
      void dump(dump_context &) const override;

      void     initialize_matter(::matter * pmatter) override;
      //virtual void     initialize_library(::matter* pmatter, int iDesmabi, const char * pszRoot = nullptr, const char * pszName = nullptr, const char * pszFolder = nullptr);
      //virtual void initialize_library(::matter* pmatter, const char* pszName = nullptr, const char* pszFolder = nullptr);

      //virtual void open(const char * pszPath,bool bAutoClose = true,bool bCa2Path = false);

      virtual void open(const char* pszPath);


      //static ::acme::library* loading_library();

      //virtual bool open_library(string strTitle = "");

      //library * get_library();


      //virtual ::factory::factory * factory() { return m_pfactory; }


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




      // virtual bool contains_app(const char* pszAppId);


      //virtual void get_create_view_id_list(::array < ::atom > & ida);


      //virtual string get_root();


      //virtual __pointer(::object) new_application(const ::string & strAppId);
      //virtual void get_app_list(string_array & stra);

      
      //virtual ::matter* new_object(const char* pszClass);
      

      virtual string get_library_name();

      //virtual string get_app_id(const char * pszAppName);
      //virtual string get_app_name(const char * pszAppId);

      //virtual void get_extension_list(string_array & stra);


      // virtual ::matter * factory_new(::object * pobject, const char * lpszClass);


      //virtual __pointer(::matter) factory_create(const char * lpszClass);
      //virtual bool factory_has_object_class(const char * lpszClass);

      //library_object_allocator_base * find_allocator(const char * lpszClass);

      //virtual void initialize_factory();


      //virtual bool add_factory_item();

      //virtual __pointer(::factory::factory) & factory(const ::string & strComponent, const ::string & strImplementation);

      //virtual __pointer(::factory::factory) & factory(const ::string & strLibrary);

      //virtual void _load_factory(__pointer(::factory::factory) & pfactory, const ::string& strComponent);

      //virtual void factory_exchange(const ::string & strName = nullptr, ::factory::factory * pfactory = nullptr);
      //virtual __pointer(::factory::factory) create_factory(const ::string& strLibrary);

      virtual __pointer(::factory::factory) create_factory();


   };



   CLASS_DECL_ACME void * open_ca2_library(const char * psz);




   
   


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






//
//
//namespace factory
//{
//
//
//   template < typename TYPE, typename BASE_TYPE>
//   inline __pointer(::factory::factory_item_base < BASE_TYPE >) _add_factory_item_from(const ::atom & atomSource)
//   {
//
//      critical_section_lock lock(::factory::get_factory_critical_section());
//
//      if (::acme::library::loading_library() != nullptr)
//      {
//
//         return ::acme::library::loading_library()->get_factory()->add_factory_item < TYPE, BASE_TYPE >();
//
//      }
//      
//      auto pfactoryitem = __new(::factory::factory_item< TYPE, BASE_TYPE >());
//
//      ::factory::get_factory_item < BASE_TYPE >(atomSource) = pfactoryitem;
//
//      return pfactoryitem;
//
//   }
//
//
//} // namespace factory
//
//

