//
// Created by camilo on 22/02/2022. 01:19 <3ThomasBorregaardSorensen!!
//
#pragma once


class CLASS_DECL_ACME app :
   virtual public ::app_core,
   virtual public ::acme::context,
   virtual public ::task
{
public:



   static app *                                    g_p;

   string                                          m_strAppName;
   string                                          m_strRoot;
   string                                          m_strDomain;
   string                                          m_strLibraryName;
   string                                          m_strBuild;
   string                                          m_strInstallToken;
   string_array                                    m_straAppCategory;
   bool                                            m_bLicense;
   
   enum_application_capability_array               m_eapplicationcapabilitya;


   app();
   ~app() override;


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

   
   int main_loop();



   virtual void init1();


   virtual void init_instance();


   virtual bool has_capability(enum_application_capability eapplicationcapability) const;
   virtual void add_capability(enum_application_capability ecapability);
   
   
   virtual void open_url(const ::string & strUrl);


};


