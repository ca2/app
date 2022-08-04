#pragma once


namespace turboc
{


   class CLASS_DECL_TURBOC toggle_impact:
      virtual public ::aura::impact,
      virtual public ::user::button
   {
   public:


      top_impact * m_ptopview;


      toggle_impact(::object * pobject);
      virtual ~toggle_impact();


      virtual void install_message_handling(::message::dispatch * pdispatch);


      virtual void on_update(::aura::impact * pSender,e_update eupdate,object* pupdate);


      virtual bool keyboard_focus_is_focusable();


   };


} // namespace turboc




