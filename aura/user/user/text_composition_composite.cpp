// From text_composition.cpp by camilo on 2022-08-27 19:31 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "text_composition_composite.h"
#include "text_composition_client.h"
#include "interaction.h"


namespace user
{


	text_composition_composite::text_composition_composite()
	{


	}


	text_composition_composite::~text_composition_composite()
	{


	}


   void text_composition_composite::destroy()
   {
      
      m_ptextcompositionclient.defer_destroy();
      
      text_composition_client_base::destroy();

   }



	void text_composition_composite::initialize_text_composition_client(::channel * pchannel, ::user::interaction * puserinteraction)
	{

		//auto estatus =

		puserinteraction->__øconstruct(m_ptextcompositionclient);

		//if (!estatus)
		//{

		//	return estatus;

		//}

		//m_ptextcompositionclient->m_ptextcompositionclient = this;

		m_ptextcompositionclient->initialize_text_composition_client(pchannel, puserinteraction);

		//return estatus;

	}


	void text_composition_composite::on_text_composition_done()
	{

		m_ptextcompositionclient->on_text_composition_done();

	}


	void text_composition_composite::on_text_composition(const ::scoped_string & scopedstrMessage)
	{

		m_ptextcompositionclient->on_text_composition(scopedstrMessage);

	}


	void text_composition_composite::insert_text(const ::scoped_string & scopedstr, bool bForceNewStep, const ::action_context & actioncontext)
	{

		m_ptextcompositionclient->insert_text(scopedstr, bForceNewStep, actioncontext);

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


} //  namespace user



