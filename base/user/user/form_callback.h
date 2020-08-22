#pragma once


namespace user
{


   class CLASS_DECL_AURA form_callback :
      virtual public callback
   {
   public:


      //::form_property_set *         m_pformpropertyset;
      

      //form_callback();
      //virtual ~form_callback();


      virtual void _001OnInitializeForm();
      virtual void _001OnInitializeControl(control * pcontrol);


      //virtual void OnUser123(WPARAM wparam,LPARAM lparam);


      virtual void _001InitializeFormPreData(::user::form * pform);
      

   };


} // namespace user


