#pragma once


namespace user
{


   class control_descriptor;


   class CLASS_DECL_AURA form :
      virtual public ::user::interaction
   {
   protected:


      __reference(form_callback) m_pcallback;
      __reference(form)  m_pformParent;


   public:




      form();
      virtual ~form();


      ::estatus set_form_callback(::user::form_callback* pcallback);
      ::estatus set_parent_form(::user::form* pform);

      inline ::user::form_callback* get_form_callback() { return m_pcallback.get(); }
      virtual ::user::callback* get_user_callback() { return get_form_callback(); }
      inline ::user::form* get_parent_form() { return m_pformParent.get(); }



      virtual bool create_control(class control_descriptor * pdescriptor, index iItem);


      virtual __pointer(control_descriptor) new_form_control();


      virtual ::estatus open_html(const ::string& str);

   };


} // namespace user


