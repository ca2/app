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


      inline ::aura::application* get_application() const;
      inline ::aura::session* get_session() const;
      inline ::aura::system* get_system() const { return ::is_set(m_psystem) ? dynamic_cast <::aura::system*> (m_psystem) : nullptr; }
      inline ::user::user * user() const { return get_session() ? get_session()->user() : nullptr; }


      virtual ::e_status initialize(::object * pobject) override;

      void install_message_routing(::channel * pchannel) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);

      ::e_status set_form_callback(::user::form_callback* pcallback);
      ::e_status set_parent_form(::user::form* pform);


      virtual ::user::form_callback* get_form_callback();
      //virtual ::handler* get_user_callback() override;
      virtual ::user::form * get_parent_form() override;


      //virtual enum_control_type get_control_type() const override;

      virtual bool _001AddControl(::user::interaction * pinteraction);
      //virtual bool create_interaction(::user::interaction * pinteractionParent, const ::id & id);


      //virtual __pointer(control_descriptor) new_form_control();


      virtual ::e_status open_html(const ::string& str);

      virtual ::e_status open_document(const ::payload& payloadFile);

      virtual void soft_reload();


   };


} // namespace user


