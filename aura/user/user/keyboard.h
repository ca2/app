#pragma once


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


      void initialize(::object * pobject) override;
      
      
      virtual ::user::enum_key wparam_to_userkey(wparam wparam);


      virtual void translate_os_key_message(key * pkey);

      virtual bool load_os_layout(const ::file::path & pszPath);

   };


} // namespace user



