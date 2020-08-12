#pragma once


namespace user
{


   class CLASS_DECL_BASE form_callback :
      virtual public ::object
      //,
      //virtual public ::form_property_set
   {
   public:


      ::form_property_set *         m_pformpropertyset;
      

      form_callback();
      virtual ~form_callback();


      virtual void _001OnInitializeForm();
      virtual void _001OnInitializeControl(__pointer(control) pcontrol);


      virtual void on_control_event(::user::control_event * pevent);
      virtual void OnUser123(WPARAM wparam,LPARAM lparam);


      virtual void _001InitializeFormPreData(::user::form * pform);
      

   };


} // namespace user


