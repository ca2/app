#pragma once


#include "acme/primitive/primitive/object.h"
#include "acme/primitive/collection/int_map.h"


namespace user
{

   //class keyboard_layout;

   class CLASS_DECL_AURA keyboard :
      virtual public ::object
   {
   public:


      ::i32_map < ::user::enum_key >              m_mapExt;
      ::i32_map < ::user::enum_key >              m_mapScan;
      ::i32_map < ::user::enum_key >              m_mapKey;

      
      keyboard();
      ~keyboard() override;


      void initialize(::particle * pparticle) override;
      
      
      virtual ::user::enum_key wparam_to_userkey(wparam wparam);


      virtual void translate_os_key_message(key * pkey);

      virtual bool load_os_layout(const ::file::path & pszPath);

   };


} // namespace user



