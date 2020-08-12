#pragma once


namespace user
{

   class keyboard_layout;

   class CLASS_DECL_AURA keyboard :
      virtual public ::object
   {
   public:


      __pointer(::user::primitive)              m_pprimitiveSoftwareKeyboard;
      index                                     m_iSoftwareKeyboardEventId;


      ::int_map < ::user::e_key >              m_mapExt;
      ::int_map < ::user::e_key >              m_mapScan;
      ::int_map < ::user::e_key >              m_mapKey;
      __pointer(keyboard_layout)                    m_playout;

      keyboard();
      virtual ~keyboard();

      virtual class keyboard_layout & on_layout();

      virtual ::estatus initialize(::object * pobjectContext) override;

      bool load_layout(const char * pszPath, const ::action_context & action_context);

      string process_key(key * pkey);

      string process_key(::user::e_key ekey);

      string process_char(const char * pszChar);

      string process_escape(const char * pszChar);

      //void process_escape(__pointer(::xml::node) pnode, property_set & set);

      string get_current_system_layout();

      bool initialize(::user::keyboard_layout_id * playoutid, const char * pszPath);

      void translate_os_key_message(key * pkey);

      virtual bool load_os_layout(const ::file::path & pszPath);

      virtual void defer_show_software_keyboard(::user::primitive* pprimitive, bool bShow, string str, strsize iBeg, strsize iEnd);


   };

} // namespace user
