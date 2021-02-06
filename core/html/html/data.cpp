#include "framework.h"
#include "_html.h"


html_data::html_data()
{

}


html_data::~html_data()
{

}


::e_status html_data::initialize_html_data(::html_data * phtmldata)
{

   auto estatus = ::form_data::initialize(phtmldata);

   if (!estatus)
   {

      return estatus;

   }

   m_pimplHtml = phtmldata;

   return estatus;

}


i64 html_data::add_ref(OBJ_REF_DBG_PARAMS_DEF)
{

   return ::object::add_ref(OBJ_REF_DBG_ARGS);

}


i64 html_data::dec_ref(OBJ_REF_DBG_PARAMS_DEF)
{

   return ::object::dec_ref(OBJ_REF_DBG_ARGS);

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

   sync_lock lock(mutex());

   destroy();

}


void html_data::destroy()
{

   m_pcoredata->destroy();

}


void html_data::delete_implementation()
{

   m_pcoredata->delete_implementation();

}


void html_data::load(const char * psz)
{

   m_pcoredata->load(psz);

}


void html_data::implement(::draw2d::graphics_pointer & pgraphics)
{

   m_pcoredata->implement(pgraphics);

}


void html_data::_001OnKeyDown(::message::message * pmessage)
{

   __pointer(::message::key) pkey(pmessage);

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

   m_pcoredata->_001OnDraw(pgraphics);

}


html::element* html_data::get_element_by_name(id id)
{

   return m_pcoredata->get_element_by_name(id);

}


html::element* html_data::get_element_by_id(id id)
{

   return m_pcoredata->get_element_by_name(id);

}


image_pointer html_data::get_image(const char * pszUrl)
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


bool html_data::open_link(const char * pszPath)
{

   return m_pcoredata->open_link(pszPath);

}


bool html_data::open_document(const ::payload & varFile)
{

 return m_pcoredata->open_document(varFile);

}


::e_status     html_data::open_html(const ::string & str)
{

   return m_pcoredata->open_html(str);

}


//void html_data::on_before_navigate(::payload & varFile, u32 nFlags, const char * pszTargetFrameName, byte_array& baPostedData, const char * pszHeaders, bool* pbCancel)
//{
//
//   m_pcoredata->on_before_navigate(varFile, nFlags, pszTargetFrameName, baPostedData, pszHeaders, pbCancel);
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

