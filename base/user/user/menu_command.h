#pragma once


namespace user
{


   class CLASS_DECL_AURA menu_command :
      virtual public ::user::command,
      virtual public ::user::check,
      virtual public ::user::text
   {
   public:


      menu_item_ptra *     m_pitema;
      menu_item *          m_pitemContainer;


      menu_command(::object * pobject);


      //void delete_this() override;

      virtual void Enable(bool bOn, const ::action_context & action_context) override;
      virtual void _001SetCheck(::enum_check echeck, const ::action_context & action_context) override;
      virtual void _001SetText(const string & pszText, const ::action_context & action_context) override;


   };


} // namespace user



