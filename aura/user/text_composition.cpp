// created by Camilo 2021-02-02 05:58 BRT <3CamiloSasukeThomasBorregaardSoerensen
#include "framework.h"
#include "aura/user/_user.h"
#include "text_composition.h"


namespace user
{


	text_composition_client::text_composition_client()
	{

	   m_bTextCompositionActive = false;

	}


	text_composition_client::~text_composition_client()
	{

	}


	void text_composition_client::on_text_composition_done()
	{

		m_ptextcompositionclient->on_text_composition_done();

	}


	void text_composition_client::on_text_composition(string strMessage)
	{

		m_ptextcompositionclient->on_text_composition(strMessage);

	}


	void text_composition_client::insert_text(string str, bool bForceNewStep, const ::action_context & context)
	{

		m_ptextcompositionclient->insert_text(str, bForceNewStep, context);

	}


	bool text_composition_client::is_text_composition_active() const
	{

	   //return m_ptextcompositionclient;

		return m_ptextcompositionclient->is_text_composition_active();

	}


	string text_composition_client::get_ime_composition() const
	{

	   //return m_strImeComposition;

		return m_ptextcompositionclient->get_ime_composition();

	}


	void text_composition_client::clear_ime_composition()
	{

		return m_ptextcompositionclient->clear_ime_composition();

	}




	text_composition_composite::text_composition_composite()
	{


	}


	text_composition_composite::~text_composition_composite()
	{


	}


	::e_status text_composition_composite::initialize_text_composition_client()
	{

		auto estatus = __construct(m_ptextcompositionclient);

		if (!estatus)
		{

			return estatus;

		}

		m_ptextcompositionclient->m_ptextcompositionclient = this;

		m_ptextcompositionclient->install_message_routing(this);

		return estatus;

	}


} // namespace text



