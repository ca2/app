#include "framework.h"
#include "aura/graphics/image/image.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_html.h"
#endif



html_data::html_data()
{

}


html_data::~html_data()
{

}


void html_data::initialize_html_data(::html_data * phtmldata)
{

   //auto estatus =
   
   ::form_data::initialize(phtmldata);

   //if (!estatus)
   //{

   //   return estatus;

   //}

   m_pimplHtml = phtmldata;

   //return estatus;

}


i64 html_data::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

   return ::object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

}


i64 html_data::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

   return ::object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

}


::html::font * html_data::get_font(::html::element* pelemental)
{

   return m_pcoredata->get_font(pelemental);

}


i32 html_data::create_font(::html::element* pelemental)
{

   return m_pcoredata->create_font(pelemental);
}


void html_data::delete_contents()
{

   synchronous_lock lock(mutex());

   destroy();

}


void html_data::destroy()
{

   if (m_pcoredata)
   {

      m_pcoredata->destroy();

   }

}


void html_data::delete_implementation()
{

   m_pcoredata->delete_implementation();

}


void html_data::load(const ::string & psz)
{

   m_pcoredata->load(psz);

}


void html_data::implement(::draw2d::graphics_pointer & pgraphics)
{

   m_pcoredata->implement(pgraphics);

}


void html_data::on_message_key_down(::message::message * pmessage)
{

   auto pkey = pmessage->m_union.m_pkey;

   if(pkey->m_ekey == ::user::e_key_tab)
   {

      auto pfocus = get_form()->get_keyboard_focus();

      if (pfocus != nullptr)
      {

         pfocus = pfocus->keyboard_get_next_focusable();

      }

      if (pfocus != nullptr)
      {

         pfocus->set_keyboard_focus();

      }

      pkey->m_bRet = true;

      return;

   }

}


void html_data::on_layout(::draw2d::graphics_pointer & pgraphics)
{

   m_pcoredata->on_layout(pgraphics);

}


void html_data::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
{
   
   if(::is_null(m_pcoredata))
   {
      
      return;
      
   }

   m_pcoredata->_001OnDraw(pgraphics);

}


html::element* html_data::get_element_by_name(atom atom)
{

   return m_pcoredata->get_element_by_name(atom);

}


html::element* html_data::get_element_by_id(atom atom)
{

   return m_pcoredata->get_element_by_name(atom);

}


image_pointer html_data::get_image(const ::string & pszUrl)
{

   return m_pcoredata->get_image(pszUrl);

}


bool html_data::contains(__pointer(::user::interaction) pinteraction)
{

   return m_pcoredata->contains(pinteraction);

}


bool html_data::on_create_interaction(__pointer(::user::interaction) pinteraction)
{

   return m_pcoredata->on_create_interaction(pinteraction);

}


bool html_data::open_link(const ::string & pszPath)
{

   return m_pcoredata->open_link(pszPath);

}


bool html_data::open_document(const ::payload & payloadFile)
{

 return m_pcoredata->open_document(payloadFile);

}


bool html_data::open_html(const ::string & str)
{

   return m_pcoredata->open_html(str);

}


//void html_data::on_before_navigate(::payload & payloadFile, u32 nFlags, const ::string & pszTargetFrameName, byte_array& baPostedData, const ::string & pszHeaders, bool* pbCancel)
//{
//
//   m_pcoredata->on_before_navigate(payloadFile, nFlags, pszTargetFrameName, baPostedData, pszHeaders, pbCancel);
//
//}

::user::form * html_data::get_form()
{
   return m_pcoredata->m_pform;
}

__pointer(::user::interaction) html_data::get_frame()
{
   return  (get_form()->get_parent_frame());
}


void html_data::implement_and_layout(::html_form * pform)
{

   m_pcoredata->implement_and_layout(pform);


}

void html_data::implement(::html_form * pform)
{

   m_pcoredata->implement(pform);

}


void html_data::layout(::html_form * pform)
{

   m_pcoredata->layout(pform);
   
}



