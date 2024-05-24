#pragma once



//


namespace acid
{


   class CLASS_DECL_ACID library:
      virtual public ::particle
   {
   public:


      string                                          m_strFolder;
      string                                          m_strName;
      void *                                          m_plibrary;
      string                                          m_strMessage;
      PFN_factory                                     m_pfnFactory;


      //static ::pointer< ::mutex >                                s_pmutexLoading;
      //static ::acid::library *                        s_plibraryLoading;


      library();
      ~library() override;

      //// void assert_ok() const override;
      //void dump(dump_context &) const override;

      //void     initialize_matter(::matter * pmatter) override;
      //virtual void     initialize_library(::matter* pmatter, int iDesmabi, const ::scoped_string & scopedstrRoot = nullptr, const ::scoped_string & scopedstrName = nullptr, const ::scoped_string & scopedstrFolder = nullptr);
      //virtual void initialize_library(::matter* pmatter, const ::scoped_string & scopedstrName = nullptr, const ::scoped_string & scopedstrFolder = nullptr);

      //virtual void open(const ::file::path & path,bool bAutoClose = true,bool bCa2Path = false);

      virtual void open(const ::file::path & path);


      //static ::acid::library* loading_library();

      //virtual bool open_library(string strTitle = "");

      //library * get_library();


      //virtual ::factory::factory * factory() { return m_pfactory; }


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




      // virtual bool contains_app(const ::scoped_string & scopedstrAppId);


      //virtual void get_create_impact_id_list(::array < ::atom > & ida);


      //virtual string get_root();


      //virtual ::pointer<::object>new_application(const ::string & strAppId);
      //virtual void get_app_list(string_array & stra);

      
      //virtual ::matter* new_object(const ::scoped_string & scopedstrClass);
      

      virtual string get_library_name();

      //virtual string get_app_id(const ::scoped_string & scopedstrAppName);
      //virtual string get_app_name(const ::scoped_string & scopedstrAppId);

      //virtual void get_extension_list(string_array & stra);


      // virtual ::matter * factory_new(::particle * pparticle, const char * lpszClass);


      //virtual ::pointer<::matter>factory_create(const char * lpszClass);
      //virtual bool factory_has_object_class(const char * lpszClass);

      //library_object_allocator_base * find_allocator(const char * lpszClass);

      //virtual void initialize_factory();


      //virtual bool add_factory_item();

      //virtual ::pointer<::factory::factory>& factory(const ::string & strComponent, const ::string & strImplementation);

      //virtual ::pointer<::factory::factory>& factory(const ::string & strLibrary);

      //virtual void _load_factory(::pointer<::factory::factory>& pfactory, const ::string& strComponent);

      //virtual void factory_exchange(const ::string & strName = nullptr, ::factory::factory * pfactory = nullptr);
      //virtual ::pointer<::factory::factory>create_factory(const ::string& strLibrary);

      virtual void create_factory(::pointer<::factory::factory> & pfactory);


   };



   CLASS_DECL_ACID void * open_ca2_library(const ::scoped_string & scopedstr);






} // namespace acid





#define BEGIN_LIBRARY                                                   \
                                                                        \
                                                                        \
class library :                                                         \
   virtual public ::acid::library                                       \
{                                                                       \
public:                                                                 \
                                                                        \
                                                                        \
     library(::particle * pparticle) : ::acid::library(pparticle) {}          \
     virtual ~library(){}                                               \
                                                                        \
                                                                        \




#define BEGIN_CREATE_OBJECT                                             \
                                                                        \
                                                                        \
virtual void initialize_factory() override                              \
{


#define CREATE_OBJECT_ENTRY(name, TYPE) m_allocatorptra.add(__allocate< library_object_allocator < TYPE > >(name));

#define END_CREATE_OBJECT }

#define END_LIBRARY  };

#define BEG_ONLY_FACT BEGIN_LIBRARY \
 BEGIN_CREATE_OBJECT

#define END_ONLY_FACT(libname) END_CREATE_OBJECT \
 END_LIBRARY \
 \
CLASS_DECL_EXPORT ::acid::library * libname ## _ ## get_new_library(::particle * pparticle) \
{ \
\
   return __new< library >(pparticle); \
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
//   inline pointer< ::factory::factory_item_base < BASE_TYPE > > _add_factory_item_from(const ::atom & atomSource)
//   {
//
//      critical_section_lock lock(::factory_critical_section());
//
//      if (::acid::library::loading_library() != nullptr)
//      {
//
//         return ::acid::library::loading_library()->get_factory()->add_factory_item < TYPE, BASE_TYPE >();
//
//      }
//      
//      auto pfactoryitem = __allocate< ::factory::factory_item< TYPE, BASE_TYPE > >();
//
//      factory_item < BASE_TYPE >(atomSource) = pfactoryitem;
//
//      return pfactoryitem;
//
//   }
//
//
//} // namespace factory
//
//

CLASS_DECL_ACID string implementation_name(const ::string & strComponent, const ::string & strImplementation);


CLASS_DECL_ACID string library_name(const ::string & strComponent, const ::string & strImplementation);


CLASS_DECL_ACID string factory_name(const ::string & strLibrary);


CLASS_DECL_ACID string library_filter(const ::string & str);



