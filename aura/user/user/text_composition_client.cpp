// created by Camilo 2021-02-02 05:58 BRT <3CamiloSasukeThomasBorregaardSoerensen
// From text_composition.cpp by camilo on 2022-08-27 19:31 <3ThomasBorregaardSorensen!!
#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/user/_component.h"
#endif
#include "text_composition_client.h"
#include "interaction.h"


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


	void text_composition_client::set_text_composition_active(bool bActive)
	{

		throw interface_only();

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




} // namespace text



