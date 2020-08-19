#pragma once


namespace user
{


   class CLASS_DECL_AURA ::update:
      virtual public update_hint
   {
   public:


      enum e_type
      {
         type_browse,
         type_after_browse,
         type_get_form_view,
      };


      __pointer(::user::form)           m_pform;
      e_type                     m_etype;
      string                     m_strForm;
      ::action::action_context          m_actioncontext;


      ::update();
      virtual ~::update();




   };


} // namespace user









