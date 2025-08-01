#pragma once


////#include "acme/prototype/prototype/object.h"
#include "acme/prototype/collection/int_map.h"


namespace user
{

   //class keyboard_layout;

   class CLASS_DECL_AURA keyboard :
      virtual public ::object
   {
   public:


      ::int_map < ::user::enum_key >              m_mapExt;
      ::int_map < ::user::enum_key >              m_mapScan;
      ::int_map < ::user::enum_key >              m_mapKey;

      
      keyboard();
      ~keyboard() override;


      void initialize(::particle * pparticle) override;
      
      
      virtual ::user::enum_key wparam_to_userkey(wparam wparam);


      virtual void translate_os_key_message(key * pkey);

      virtual bool load_os_layout(const ::file::path & path);

   };


} // namespace user



