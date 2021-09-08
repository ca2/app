// created by Camilo 2021-02-02 05:58 BRT <3CamiloSasukeThomasBorregaardSoerensen
#include "framework.h"
#include "aura/user/_user.h"
#include "text_composition.h"


namespace user
{


	text_composition_client::text_composition_client()
	{

	   //m_bTextCompositionActive = false;

	}


	text_composition_client::~text_composition_client()
	{

	}


	void text_composition_client::initialize_text_composition_client(::channel * pchannel, ::user::interaction * pusertext)
	{

		//m_pusertext = pusertext;

	}


	void text_composition_client::on_text_composition_done()
	{

		//m_ptextcompositionclient->on_text_composition_done();

	}


	void text_composition_client::on_text_composition(string strMessage)
	{

		//m_ptextcompositionclient->on_text_composition(strMessage);

	}


	void text_composition_client::insert_text(string str, bool bForceNewStep, const ::action_context & context)
	{

		//m_ptextcompositionclient->insert_text(str, bForceNewStep, context);

	}


	bool text_composition_client::is_text_composition_active() const
	{

		//return m_ptextcompositionclient->is_text_composition_active();

		return false;

	}


	string text_composition_client::get_ime_composition() const
	{

	   //return m_strImeComposition;

		//return m_ptextcompositionclient->get_ime_composition();

		return "";

	}


	void text_composition_client::clear_ime_composition()
	{

		//return m_ptextcompositionclient->clear_ime_composition();

	}




	text_composition_composite::text_composition_composite()
	{


	}


	text_composition_composite::~text_composition_composite()
	{


	}


	::e_status text_composition_composite::initialize_text_composition_client(::channel* pchannel, ::user::interaction * puserinteraction)
	{

		auto estatus = __construct(m_ptextcompositionclient);

		if (!estatus)
		{

			return estatus;

		}

		//m_ptextcompositionclient->m_ptextcompositionclient = this;

		m_ptextcompositionclient->initialize_text_composition_client(pchannel, puserinteraction);

		return estatus;

	}


	void text_composition_composite::on_text_composition_done()
	{

		m_ptextcompositionclient->on_text_composition_done();

	}


	void text_composition_composite::on_text_composition(string strMessage)
	{

		m_ptextcompositionclient->on_text_composition(strMessage);

	}


	void text_composition_composite::insert_text(string str, bool bForceNewStep, const ::action_context& context)
	{

		m_ptextcompositionclient->insert_text(str, bForceNewStep, context);

	}

	
	bool text_composition_composite::is_text_composition_active() const
	{

		if (!m_ptextcompositionclient)
		{

			return false;

		}

		bool bTextCompositionActive = m_ptextcompositionclient->is_text_composition_active();

		return bTextCompositionActive;
	}


	string text_composition_composite::get_ime_composition() const
	{

		string strImeComposition = m_ptextcompositionclient->get_ime_composition();

		return strImeComposition;

	}

	
	void text_composition_composite::clear_ime_composition()
	{

		m_ptextcompositionclient->clear_ime_composition();

	}


} // namespace text



