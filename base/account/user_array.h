#pragma once


namespace account
{


   class CLASS_DECL_AURA user_array :
      virtual public ::object
   {
   public:


      department *               m_pdepartment;
      string_map < __pointer(user) >    m_map;


      user_array(department * pdepartment);
      virtual ~user_array();


      virtual __pointer(user) allocate_user();
      
      
      virtual void logout();

      
      virtual user * get_user(::file::path pathUrl = nullptr, bool bFetch = false, bool bInteractive = true);
//      virtual user * interactive_get_user(::file::path pathUrl = nullptr);
//      virtual user * noninteractive_get_user(::file::path pathUrl = nullptr);
      
      
      virtual void _get_user(::file::path pathUrl, bool bInteractive);
      
      
      virtual bool is_authenticated(::file::path pathUrl, bool bInteractive);
      
      //virtual ::file::path get_default_url();

      virtual void on_clock(e_clock eclock);
      
      virtual void cleanup_users();
      
      
      void cleanup_account();
      
      void cleanup_networking();
      
      virtual bool authorize_user(user * puser);
      

   };


} // namespace account



