#pragma once


#include "interaction.h"


namespace user
{


   class CLASS_DECL_AURA form :
      virtual public ::user::interaction
   {
   protected:


      ::pointer<form_callback>m_pcallback;
      ::pointer<form> m_pformParent;


   public:




      form();
      ~form() override;


      ::aura::application* get_app();
      ::aura::session* get_session();
//      ::aura::system* acmesystem();
      ::user::user * user();


      virtual void initialize(::particle * pparticle) override;

      void install_message_routing(::channel * pchannel) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);

      void set_form_callback(::user::form_callback* pcallback);
      void set_parent_form(::user::form* pform);


      virtual ::user::form_callback* get_form_callback();
      //virtual ::handler* get_user_callback() override;
      ::user::form * get_parent_form() override;


      //virtual enum_control_type get_control_type() const override;

      virtual bool _001AddControl(::user::interaction * pinteraction);
      //virtual bool create_interaction(::user::interaction * pinteractionParent, const ::atom & atom);


      //virtual ::pointer<control_descriptor>new_form_control();


      virtual bool open_document(const ::payload& payloadFile);

      virtual bool open_html(const ::string& str);

      virtual void soft_reload();


   };


} // namespace user


