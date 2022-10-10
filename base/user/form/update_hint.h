#pragma once


namespace user
{


   class CLASS_DECL_BASE ::update:
      virtual public update_hint
   {
   public:


      enum enum_type
      {
         type_browse,
         type_after_browse,
         type_get_form_impact,
      };


      ::pointer<::user::form>          m_pform;
      enum_type                     m_etype;
      string                     m_strForm;
      ::action::action_context          m_actioncontext;


      ::update();
      virtual ~::update();




   };


} // namespace user









