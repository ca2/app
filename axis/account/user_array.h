#pragma once


//#include "acme/filesystem/filesystem/path.h"
#include "acme/prototype/collection/string_map.h"
//#include "acme/prototype/prototype/matter.h"


namespace account
{


   class CLASS_DECL_AXIS user_array :
      virtual public ::matter
   {
   public:


      department *                                 m_paccount;
      string_map < ::pointer<::account::user >>    m_map;


      user_array();
      ~user_array() override;


      virtual void initialize_user_array(department* pdepartment);


      virtual ::pointer<::account::user>allocate_user();
      
      
      virtual void logout();

      
      virtual ::account::user * get_user(const ::file::path & pathUrl = nullptr, bool bFetch = false, bool bInteractive = true);
//      virtual user * interactive_get_user(::file::path pathUrl = nullptr);
//      virtual user * noninteractive_get_user(::file::path pathUrl = nullptr);
      
      
      virtual void _get_user(const ::file::path & pathUrl, bool bInteractive);
      
      
      virtual bool is_authenticated(const ::file::path & pathUrl, bool bInteractive);
      
      //virtual ::file::path get_default_url();

      virtual void on_clock(enum_timer etimer);
      
      virtual void cleanup_users();
      
      
      void cleanup_account();
      
      void cleanup_networking();
      
      virtual bool authorize_user(::account::user * puser);
      

   };


} // namespace account



