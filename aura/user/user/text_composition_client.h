// From text_composition.h by camilo on 2022-08-27 19:20 <3ThomasBorregaardSørensen!!
#pragma once


#include "text_composition_client_base.h"


namespace user
{


	class CLASS_DECL_AURA text_composition_client :
		virtual public text_composition_client_base
	{
	public:


		string												m_strImeComposition;


		text_composition_client();
		~text_composition_client() override;


		virtual void initialize_text_composition_client(::channel * pchannel, ::user::interaction * puserinteraction);


		//DECLARE_MESSAGE_HANDLER(on_message_key_down);
		//DECLARE_MESSAGE_HANDLER(_011OnChar);
		//DECLARE_MESSAGE_HANDLER(_001OnIme);
		//DECLARE_MESSAGE_HANDLER(on_message_set_focus);
		//DECLARE_MESSAGE_HANDLER(on_message_kill_focus);

		//virtual int on_text_composition_message(int iMessage) override;

		void on_text_composition_done() override;

		void on_text_composition(string strMessage) override;

		void insert_text(string str, bool bForceNewStep, const ::action_context & context) override;

		bool is_text_composition_active() const override;

		virtual void set_text_composition_active(bool bActive = true);

		string get_ime_composition() const override;

		void clear_ime_composition() override;


	};



} // namespace user



