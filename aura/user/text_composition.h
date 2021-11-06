#pragma once


namespace user
{


	enum enum_text_composition_state
	{

		e_text_composition_state_none,
		e_text_composition_state_composing,
		e_text_composition_state_selected,

	};


	class CLASS_DECL_AURA text_composition_client_base :
		virtual public ::matter
	{
	public:


		//string                                 m_strImeComposition;
		//__pointer(text_composition_client)		m_ptextcompositionclient;


		//text_composition_client();
		//virtual ~text_composition_client();


		//void install_message_routing(::channel * pchannel) override;


		//DECLARE_MESSAGE_HANDLER(on_message_key_down);
		//DECLARE_MESSAGE_HANDLER(_011OnChar);
		//DECLARE_MESSAGE_HANDLER(_001OnIme);
		//DECLARE_MESSAGE_HANDLER(_001OnSetFocus);
		//DECLARE_MESSAGE_HANDLER(_001OnKillFocus);

		//virtual int on_text_composition_message(int iMessage) override;

		virtual void on_text_composition_done() = 0;

		virtual void on_text_composition(string strMessage) = 0;

		virtual void insert_text(string str, bool bForceNewStep, const ::action_context& context) = 0;

		virtual bool is_text_composition_active() const = 0;

		virtual string get_ime_composition() const = 0;

		virtual void clear_ime_composition() = 0;


	};


	class CLASS_DECL_AURA text_composition_client :
		virtual public text_composition_client_base
	{
	public:


	   string												m_strImeComposition;


		text_composition_client();
		virtual ~text_composition_client();


		virtual void initialize_text_composition_client(::channel * pchannel, ::user::interaction * puserinteraction);


		//DECLARE_MESSAGE_HANDLER(on_message_key_down);
		//DECLARE_MESSAGE_HANDLER(_011OnChar);
		//DECLARE_MESSAGE_HANDLER(_001OnIme);
		//DECLARE_MESSAGE_HANDLER(_001OnSetFocus);
		//DECLARE_MESSAGE_HANDLER(_001OnKillFocus);

		//virtual int on_text_composition_message(int iMessage) override;

		virtual void on_text_composition_done() override;

		virtual void on_text_composition(string strMessage) override;

		virtual void insert_text(string str, bool bForceNewStep, const ::action_context & context) override;

		virtual bool is_text_composition_active() const override;

		virtual string get_ime_composition() const override;
			
		virtual void clear_ime_composition() override;


	};


	class CLASS_DECL_AURA text_composition_composite :
		virtual public text_composition_client_base
	{
	public:


		__pointer(text_composition_client)	m_ptextcompositionclient;


		text_composition_composite();
		virtual ~text_composition_composite();


		virtual ::e_status initialize_text_composition_client(::channel * pchannel, ::user::interaction * puserinteraction);




		//DECLARE_MESSAGE_HANDLER(on_message_key_down);
		//DECLARE_MESSAGE_HANDLER(_011OnChar);
		//DECLARE_MESSAGE_HANDLER(_001OnIme);
		//DECLARE_MESSAGE_HANDLER(_001OnSetFocus);
		//DECLARE_MESSAGE_HANDLER(_001OnKillFocus);

		//virtual int on_text_composition_message(int iMessage) override;

		//virtual void on_text_composition_done();

		//virtual void on_text_composition(string strMessage);

		//virtual void insert_text(string str, bool bForceNewStep, const ::action_context & context);

		//virtual bool is_text_composition_active() const;

		virtual void on_text_composition_done();

		virtual void on_text_composition(string strMessage);

		virtual void insert_text(string str, bool bForceNewStep, const ::action_context& context);

		virtual bool is_text_composition_active() const;

		virtual string get_ime_composition() const;

		virtual void clear_ime_composition();

	};


} // namespace text



