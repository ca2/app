// From text_composition.h by camilo on 2022-08-27 19:19 <3ThomasBorregaardSorensen!!
#pragma once


namespace user
{


	class CLASS_DECL_AURA text_composition_client_base :
		virtual public ::matter
	{
	public:


		//string                                 m_strImeComposition;
		//::pointer<text_composition_client>	m_ptextcompositionclient;


		//text_composition_client();
		//virtual ~text_composition_client();


		//void install_message_routing(::channel * pchannel) override;


		//DECLARE_MESSAGE_HANDLER(on_message_key_down);
		//DECLARE_MESSAGE_HANDLER(_011OnChar);
		//DECLARE_MESSAGE_HANDLER(_001OnIme);
		//DECLARE_MESSAGE_HANDLER(on_message_set_focus);
		//DECLARE_MESSAGE_HANDLER(on_message_kill_focus);

		//virtual int on_text_composition_message(int iMessage) override;

		virtual void on_text_composition_done() = 0;

		virtual void on_text_composition(string strMessage) = 0;

		virtual void insert_text(string str, bool bForceNewStep, const ::action_context& context) = 0;

		virtual bool is_text_composition_active() const = 0;

		virtual string get_ime_composition() const = 0;

		virtual void clear_ime_composition() = 0;


	};





} // namespace text



