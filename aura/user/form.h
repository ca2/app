#pragma once


namespace user
{


   class CLASS_DECL_AURA form :
      virtual public ::user::interaction
   {
   protected:


      __reference(form_callback) m_pcallback;
      __reference(form)  m_pformParent;


   public:




      form();
      virtual ~form();


      virtual ::e_status initialize(::layered * pobjectContext) override;

      virtual void install_message_routing(::channel * pchannel) override;

      DECL_GEN_SIGNAL(_001OnCreate);

      ::e_status set_form_callback(::user::form_callback* pcallback);
      ::e_status set_parent_form(::user::form* pform);


      virtual ::user::form_callback* get_form_callback();
      virtual ::user::callback* get_user_callback() override;
      virtual ::user::form * get_parent_form() override;


      //virtual enum_control_type get_control_type() const override;

      virtual bool _001AddControl(::user::interaction * pinteraction);
      //virtual bool create_control(::user::interaction * pinteractionParent, const ::id & id);


      //virtual __pointer(control_descriptor) new_form_control();


      virtual ::e_status open_html(const ::string& str);

      virtual ::e_status open_document(const payload& varFile);

      virtual void soft_reload();


   };


} // namespace user


