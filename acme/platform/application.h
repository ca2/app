//
// Created by camilo on 22/02/2022. 01:19 <3ThomasBorregaardSorensen!!
//
// app to application and back to acme namespace by camilo on 2022-09-17 18:51 <3ThomasBorregaardSorensen!!
#pragma once


//#define IMPLEMENT_APPLICATION_ALLOCATOR(APPLICATION, ALLOCATOR) \
//CLASS_DECL_EXPORT ::acme::application * IDENTIFIER_CONCATENATE(new_, ALLOCATOR)() \
//{ \
//  \
//   return new ::APPLICATION::application();  \
//  \
//}
//
//
//#define IMPLEMENT_APPLICATION(APPLICATION) \
//IMPLEMENT_APPLICATION_ALLOCATOR(APPLICATION, APPLICATION)
//
//
//#define DECLARE_APPLICATION(APPLICATION) \
//CLASS_DECL_IMPORT ::acme::application * IDENTIFIER_CONCATENATE(new_, APPLICATION)()


class main_hold_base;


namespace acme
{


   class CLASS_DECL_ACME application :
      virtual public ::app_core,
      virtual public ::acme::context,
      virtual public ::task
   {
   public:



      __pointer(main_hold_base)                       m_pmainholdbase;


      string                                          m_strAppName;
      string                                          m_strRoot;
      string                                          m_strDomain;
      string                                          m_strLibraryName;
      string                                          m_strBuild;
      string                                          m_strInstallToken;
      string_array                                    m_straAppCategory;
      bool                                            m_bLicense;

      enum_application_capability_array               m_eapplicationcapabilitya;


      application();
      ~application() override;


      void initialize(::object * pobject) override;


      virtual bool is_application() const;

      virtual bool is_system() const;
      virtual bool is_session() const;

      virtual bool is_service() const;
      virtual bool is_user_service() const;

#ifdef WINDOWS

      void get_arguments_from_command_line();

#else

      void set_args(int argc, char * argv[], char * envp[]);

#endif

      virtual int __implement();

      virtual int main_loop();



      virtual void init1();


      virtual void init_instance();


      virtual bool has_capability(enum_application_capability eapplicationcapability) const;
      virtual void add_capability(enum_application_capability ecapability);


      virtual void handle_url(const ::string & strUrl);


   };


} // namespace acme



