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


      application();
      ~application() override;


      virtual void open_by_module_path(const ::scoped_string & scopedstr);

      virtual void post_close();


   };


} // namespace operating_system



