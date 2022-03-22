#pragma once


namespace user
{

   //class keyboard_layout;

   class CLASS_DECL_AURA keyboard :
      virtual public ::object
   {
   public:


      __pointer(::user::primitive)              m_pprimitiveSoftwareKeyboard;
      index                                     m_iSoftwareKeyboardEventId;


      ::i32_map < ::user::enum_key >              m_mapExt;
      ::i32_map < ::user::enum_key >              m_mapScan;
      ::i32_map < ::user::enum_key >              m_mapKey;
      //__pointer(keyboard_layout)                    m_playout;

      keyboard();
      ~keyboard() override;

      //virtual class keyboard_layout & on_layout();

      virtual void initialize(::object * pobject) override;
      
      
      virtual ::user::enum_key wparam_to_userkey(wparam wparam);

      //bool load_layout(const ::string & pszPath, const ::action_context & action_context);

      //string process_key(key * pkey);

      //string process_key(::user::enum_key ekey);

      //string process_char(const ::string & pszChar);

      //string process_escape(const ::string & pszChar);

      //void process_escape(__pointer(::xml::node) pnode, property_set & set);

      //string get_current_system_layout();

      //bool initialize(::user::keyboard_layout_id * playoutid, const ::string & pszPath);

      virtual void translate_os_key_message(key * pkey);

      virtual bool load_os_layout(const ::file::path & pszPath);

      virtual void show_software_keyboard(::user::primitive * pprimitive, string str, strsize iBeg, strsize iEnd);

      virtual void hide_software_keyboard(::user::primitive * pprimitive);


   };

} // namespace user
