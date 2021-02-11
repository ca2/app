#pragma once


namespace user
{


	enum enum_text_composition_state
	{

		e_text_composition_state_none,
		e_text_composition_state_composing,
		e_text_composition_state_selected,

	};


	class CLASS_DECL_AURA text_composition_client :
		virtual public ::user::interaction
	{
	public:


		__pointer(text_composition_client)		 m_ptextcompositionclient;


		text_composition_client();
		virtual ~text_composition_client();


		//virtual void install_message_routing(::channel * pchannel) override;


		//DECL_GEN_SIGNAL(_001OnKeyDown);
		//DECL_GEN_SIGNAL(_011OnChar);
		//DECL_GEN_SIGNAL(_001OnIme);
		//DECL_GEN_SIGNAL(_001OnSetFocus);
		//DECL_GEN_SIGNAL(_001OnKillFocus);

		//virtual int on_text_composition_message(int iMessage) override;

		virtual void on_text_composition_done();

		virtual void on_text_composition(string strMessage);

		virtual void insert_text(string str, bool bForceNewStep, const ::action_context & context);

		virtual bool is_text_composition_active() const;

		virtual string get_ime_composition() const;
			
		virtual void clear_ime_composition();


	};


	class CLASS_DECL_AURA text_composition_composite :
		virtual public text_composition_client
	{
	public:


		text_composition_composite();
		virtual ~text_composition_composite();


		virtual ::e_status initialize_text_composition_client();


		//DECL_GEN_SIGNAL(_001OnKeyDown);
		//DECL_GEN_SIGNAL(_011OnChar);
		//DECL_GEN_SIGNAL(_001OnIme);
		//DECL_GEN_SIGNAL(_001OnSetFocus);
		//DECL_GEN_SIGNAL(_001OnKillFocus);

		//virtual int on_text_composition_message(int iMessage) override;

		//virtual void on_text_composition_done();

		//virtual void on_text_composition(string strMessage);

		//virtual void insert_text(string str, bool bForceNewStep, const ::action_context & context);

		//virtual bool is_text_composition_active() const;


	};


} // namespace text



