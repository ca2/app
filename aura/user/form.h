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


      virtual ::user::form_callback* get_form_callback();
      virtual ::user::callback* get_user_callback() override;
      virtual ::user::form * get_parent_form() override;



      virtual bool create_control(class control_descriptor * pdescriptor, index iItem);


      virtual __pointer(control_descriptor) new_form_control();


      virtual ::estatus open_html(const ::string& str);

      virtual ::estatus open_document(const payload& varFile);

      virtual void soft_reload();


   };


} // namespace user


