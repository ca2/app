// Created by camilo on 2023-04-15 19:07 <3ThomasBorregaardSorensen!!
#pragma once


namespace operating_system
{

   
   class main_window;


   class CLASS_DECL_ACME application :
      virtual public ::particle
   {
   public:


      ::process_identifier       m_processidentifier;
      ::string                   m_strRepos;
      ::string                   m_strApp;
      

      application();
      ~application() override;
      
      
      virtual void open_by_process_identifier(::process_identifier processidentifier);

      virtual void open_by_module_path(const ::scoped_string & scopedstr);

      virtual void open_by_app_id(const ::scoped_string & scopedstrRepos,
                                  const ::scoped_string & scopedstrApp);
      
      virtual void post_close();

      virtual void post_exit();
      
      virtual ::string name();

      virtual ::string main_window_title();
      
      virtual ::file::path module_path();
      
      virtual ::collection::count window_count() const;
      
      inline bool has_window() const { return this->window_count(); }
      
      
   };


} // namespace operating_system



