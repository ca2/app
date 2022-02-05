#include "framework.h"
#include "_user.h"
#include "aura/update.h"
#include "aura/graphics/draw2d/context_image.h"


html_form::html_form()
{

   m_pelementLButtonDown = nullptr;
   m_pelementHover = nullptr;

   //m_flagNonClient.erase(non_client_background);
   m_flagNonClient.erase(non_client_focus_rect);

   //m_phtmlform = new html::form();



}

html_form::~html_form()
{

   //::acme::del(m_phtmlform);

}


void html_form::initialize(::object * pobject)
{

   //auto estatus = 
   
   ::user::form_view::initialize(pobject);

   //if (!estatus)
   //{

   //   return estatus;

   //}

   auto psystem = get_system()->m_pcoresystem;

   //estatus = 
   
   psystem->defer_create_html();

   //if (!estatus)
   //{

   //   return estatus;

   //}

   //return estatus;

}


void html_form::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
{

   //pgraphics->fill_solid_rect_dim(5, 5, 100, 100, argb(255, 255, 255, 0));

   ::html_data * phtmldata = nullptr;

   try
   {

      phtmldata = get_html_data();

   }
   catch(...)
   {

   }

   if(phtmldata != nullptr)
   {

      phtmldata->_001OnDraw(pgraphics);

   }

}


void html_form::_001DrawChildren(::draw2d::graphics_pointer & pgraphics)
{

   __pointer(::user::interaction) pinteraction = first_child();

   while(pinteraction != nullptr)
   {

      try
      {

         if(pinteraction->is_this_visible() && (get_html_data() == nullptr || !get_html_data()->contains(pinteraction)))
         {

            pinteraction->_000CallOnDraw(pgraphics);

         }

         pinteraction = pinteraction->above_sibling();

      }
      catch(...)
      {

      }

   }

}


void html_form::_001OnImageLoaded(::message::message * pmessage)
{
   
   __UNREFERENCED_PARAMETER(pmessage);
   
   if(get_html_data() != nullptr)
   {

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      if(rectangleClient.area() > 0)
      {

         get_html_data()->m_pcoredata->m_box = rectangleClient;

         synchronous_lock lock(get_html_data()->mutex());

         auto pimage = m_pcontext->context_image()->create_image({ 50,  50 });

         get_html_data()->delete_implementation();

         ::draw2d::graphics_pointer pgraphics = pimage->g();

         get_html_data()->on_layout(pgraphics);

         set_need_redraw();

      }

   }

}


void html_form::install_message_routing(::channel * pchannel)
{

   ::user::form_view::install_message_routing(pchannel);

   MESSAGE_LINK(e_message_create, pchannel, this, &html_form::on_message_create);

   //MESSAGE_LINK(e_message_left_button_down, pchannel, this, &::user::interaction::on_message_left_button_down);
   //MESSAGE_LINK(e_message_left_button_up, pchannel, this, &::user::interaction::on_message_left_button_up);
   MESSAGE_LINK(e_message_key_down, pchannel, this, &::html_form::on_message_key_down);
   //MESSAGE_LINK(e_message_key_up, pchannel, this, &::user::interaction::on_message_key_up);

   MESSAGE_LINK(e_message_left_button_down, pchannel, this, &html_form::on_message_left_button_down);
   MESSAGE_LINK(e_message_mouse_move, pchannel, this, &html_form::on_message_mouse_move);
   MESSAGE_LINK(e_message_mouse_leave, pchannel, this, &html_form::on_message_mouse_leave);
   MESSAGE_LINK(e_message_left_button_up, pchannel, this, &html_form::on_message_left_button_up);

   MESSAGE_LINK(html::message_on_image_loaded, pchannel, this, &html_form::_001OnImageLoaded);

   MESSAGE_LINK(e_message_create, pchannel, this, &html_form::on_message_destroy);

}


void html_form::GetClientBox(::rectangle_f32 & box)
{

   ::rectangle_i32 rectangleClient;

   get_client_rect(rectangleClient);

   box = rectangleClient;

}


void html_form::on_layout(::draw2d::graphics_pointer & pgraphics)
{

   synchronous_lock synchronouslock(mutex());

   if(get_html_data() == nullptr)
   {

      set_need_layout();

      return;

   }

   get_html_data()->layout(this);

   {

      auto ptopic = create_subject(::id_layout);

      ptopic->m_pextendedtopic->m_puserelement = this;

      route(ptopic);

   }

   if (m_bNeedLoadFormData)
   {

      update_data(false);

   }

}


void html_form::on_message_create(::message::message * pmessage)
{

   __pointer(::message::create) pcreate(pmessage);

   auto psystem = m_psystem->m_pcoresystem;

   psystem->defer_create_html();

   if(pcreate->previous())
   {

      return;

   }

}


void html_form::on_message_left_button_down(::message::message * pmessage)
{

   auto pmouse = pmessage->m_union.m_pmouse;

   ::point_i32 point;

   point = pmouse->m_point;

   screen_to_client(point);

   if(get_html_data() != nullptr && get_html_data()->m_pcoredata != nullptr)
   {

      m_pelementLButtonDown = get_html_data()->m_pcoredata->m_pelement->hit_test(get_html_data(), point);

   }

   if(m_pelementLButtonDown != nullptr)
   {

      ::html::message htmlmessage;

      htmlmessage.m_phtmldata = get_html_data();

      htmlmessage.m_pmessage = pmouse;

      htmlmessage.m_pchannel = pmouse->m_pchannel;

      m_pelementLButtonDown->OnLButtonDown(&htmlmessage);

   }
   else
   {

      clear_keyboard_focus();

   }

   pmouse->m_bRet = true;

   pmouse->m_lresult = 1;

}


void html_form::on_message_mouse_move(::message::message * pmessage)
{

   auto pmouse = pmessage->m_union.m_pmouse;

   track_mouse_hover();

   ::point_i32 point(pmouse->m_point);

   screen_to_client(point);

   synchronous_lock synchronouslock(mutex());

   if(::is_set(get_html_data()) && ::is_set(get_html_data()->m_pcoredata))
   {

      synchronous_lock synchronouslock(get_html_data()->mutex());

      html::element * pelement = get_html_data()->m_pcoredata->m_pelement->hit_test(get_html_data(), point);

      if(pelement != nullptr)
      {

         if (pelement != m_pelementHover)
         {

            if (m_pelementHover != nullptr)
            {

               if (m_pelementHover->m_pimpl != nullptr)
               {

                  m_pelementHover->m_pimpl->m_bHover = false;

               }

            }

            m_pelementHover = pelement;

         }

         ::html::message htmlmessage;

         htmlmessage.m_phtmldata = get_html_data();

         htmlmessage.m_pmessage = pmouse;

         htmlmessage.m_puserinteraction = this;

         htmlmessage.m_pchannel = pmouse->m_pchannel;

         pelement->OnMouseMove(&htmlmessage);

      }

   }

}


void html_form::on_message_mouse_leave(::message::message * pmessage)
{

   if(m_pelementHover != nullptr)
   {

      if (m_pelementHover->m_pimpl != nullptr)
      {

         m_pelementHover->m_pimpl->m_bHover = false;

      }

      m_pelementHover = nullptr;

   }

}


void html_form::on_message_left_button_up(::message::message * pmessage)
{

   auto pmouse = pmessage->m_union.m_pmouse;

   ::point_i32 point(pmouse->m_point);

   screen_to_client(point);

   html::element * pelement = nullptr;

   if(get_html_data() != nullptr
      && get_html_data()->m_pcoredata != nullptr)
   {

      get_html_data()->m_pcoredata->m_pelement->hit_test(get_html_data(), point);

   }

   if(m_pelementLButtonDown != nullptr && pelement == m_pelementLButtonDown)
   {

      ::html::message htmlmessage;

      htmlmessage.m_phtmldata = get_html_data();

      htmlmessage.m_pmessage = pmouse;

      htmlmessage.m_pchannel = pmouse->m_pchannel;

      m_pelementLButtonDown->OnLButtonUp(&htmlmessage);

   }
   
}


void html_form::on_message_destroy(::message::message * pmessage)
{

   if (get_document() != nullptr)
   {

      ::html_data * pdata = get_html_data();

      if (pdata != nullptr)
      {

         if (pdata->m_pcoredata->m_pform == this)
         {

            pdata->m_pcoredata->m_pform = nullptr;

         }

         if (pdata->m_pcoredata->m_puserinteraction == this)
         {

            pdata->m_pcoredata->m_puserinteraction = nullptr;

         }

      }

   }

}


string html_form::get_path()
{

   return m_strPath;

}


void html_form::soft_reload()
{

   string str;

   {

      auto phtmldata = get_html_data();

      auto psync = phtmldata->mutex();

      synchronous_lock lock(psync);

      str = phtmldata->m_pcoredata->m_strSource;

   }

   m_pformParent->open_html(str);

}


void html_form::set_need_load_form_data()
{

   auto phtmldata = get_html_data();

   if (!phtmldata->m_pcoredata->m_bImplemented)
   {

      m_bNeedLoadFormData = true;

      set_need_layout();

   }
   else
   {

      ::user::form_window::set_need_load_form_data();

   }

}


bool html_form::open_document(const ::payload & payloadFile)
{

   auto path = payloadFile.get_file_path();

   auto psystem = m_psystem->m_paurasystem;

   if (path.is_empty())
   {

      if (payloadFile.get_type() == ::e_type_property_set && payloadFile.propset()["url"].has_char())
      {

         path = payloadFile.propset()["url"];

      }
      else if (payloadFile.cast < ::file::file >() != nullptr)
      {

         auto psystem = m_psystem;

         auto pdatetime = psystem->datetime();

         path = pdatetime->international().get_date_time() + "." + get_document()->get_document_template()->find_string("default_extension");

      }
      else
      {

         path = payloadFile;

      }

   }

   auto phtmldata = get_html_data();

   phtmldata->open_document(payloadFile);

   //if(!phtmldata->open_document(payloadFile))
   //{

   //   return false;

   //}

   m_strPath = path;

   //return true;

   return true;

}


bool html_form::open_html(const ::string & str)
{

   auto phtmldata = get_html_data();

   //if (::is_null(phtmldata))
   //{

   //   return error_failed;

   //}

   ///auto estatus =
   
   phtmldata->open_html(str);

   //if(::failed(estatus))
   //{

   //   return estatus;

   //}

   //return estatus;

   return true;

}


void html_form::_001GetText(string & str) const
{

   ((html_form *) this)->get_html_data()->m_pcoredata->m_pelement->get_html((const_cast < html_form * > (this)->get_html_data()), str);

}


void html_form::_001SetText(const ::string & str, const ::action_context & context)
{

   auto psession = get_session();

   auto puserinteraction = get_keyboard_focus()->cast < ::user::interaction >();

   bool bFocus = has_keyboard_focus() || is_descendant(puserinteraction, true);

   auto phtmldata = get_html_data();

   phtmldata->m_pcoredata->m_pform = this;

   phtmldata->load(str);

   phtmldata->implement_and_layout(this);

   if(bFocus)
   {

      __pointer(::user::primitive) pfocus = get_focusable_descendant();

      if(pfocus != nullptr)
      {

         auto psession = get_session();

         pfocus->set_keyboard_focus();

      }

   }

   _001OnInitializeForm();

}


//html_document * html_form::get_document()
//{
//
//   return dynamic_cast <html_document*> (::user::impact::get_document());
//
//}


::html_data* html_form::get_html_data()
{

   if (!m_phtmldata)
   {

      create_html_data();

   }

   return m_phtmldata;

}


void html_form::create_html_data()
{

   //auto estatus = 
   
   __construct_new(m_phtmldata);

   //if (!estatus)
   //{

   //   return estatus;

   //}
      
   //estatus = 
   
   m_phtmldata->__compose_new(m_phtmldata->m_pcompositeCoreData);

   //if (!estatus)
   //{

   //   return estatus;

   //}

   m_phtmldata->m_pcoredata = m_phtmldata->m_pcompositeCoreData;

   m_phtmldata->m_pcoredata->initialize_html_data(m_phtmldata);

   m_phtmldata->m_pimplHtml = m_phtmldata->m_pcoredata;

   m_phtmldata->::form_data::m_pimpl = m_phtmldata->m_pimplHtml;

   m_phtmldata->m_pcoredata->m_puserinteraction = this;

   m_phtmldata->m_pcoredata->m_pform = this;

   m_phtmldata->m_pcoredata->m_pcallback = this;

   //return estatus;

}


void html_form::on_message_key_down(::message::message * pmessage)
{
   
   auto pkey = pmessage->m_union.m_pkey;
   
   if(pkey->m_ekey == ::user::e_key_tab)
   {
      
      pkey->m_bRet = true;
      
      return;
      
   }
   
}


void html_form::defer_implement()
{

   if(get_html_data() == nullptr)
   {

      return;
      
   }

   GetClientBox(get_html_data()->m_pcoredata->m_box);

   if(get_html_data()->m_pcoredata->m_box.area() <= 0.f)
   {

      return;
      
   }

   auto pimage = m_pcontext->context_image()->create_image({ 50,  50 });

   get_html_data()->m_pcoredata->m_puserinteraction = this;

   get_html_data()->m_pcoredata->m_pform = this;

   ::draw2d::graphics_pointer pgraphics = pimage->g();

   get_html_data()->implement(pgraphics);

}


void html_form::defer_html_layout()
{

   if(get_html_data() == nullptr)
      return;

   GetClientBox(get_html_data()->m_pcoredata->m_box);

   if(get_html_data()->m_pcoredata->m_box.area() <= 0.f)
      return;

   auto pimage = m_pcontext->context_image()->create_image({ 50,  50 });

   get_html_data()->m_pcoredata->m_puserinteraction = this;

   get_html_data()->m_pcoredata->m_pform = this;

   ::draw2d::graphics_pointer pgraphics = pimage->g();

   get_html_data()->on_layout(pgraphics);

   set_need_redraw();

}


bool html_form::get_edit_mode()
{

   return get_html_data()->m_pcoredata->m_bEdit;

}


void html_form::set_edit_mode(bool bSet)
{

   get_html_data()->m_pcoredata->m_bEdit = bSet;

}


bool html_form::load_html(const ::string & str)
{

   get_html_data()->load(str);

   return true;

}




void html_form::handle(::topic * ptopic, ::context * pcontext)
{

   ::user::form_view::handle(ptopic, pcontext);

   ////__update(::update)
   {

      if (ptopic->m_id == id_document_complete)
      {

         //m_phtmldata = get_html_data();

      }

   }

   if (ptopic->m_id == id_open_document)
   {

      if (m_strOpenOnCreate.has_char())
      {

         get_document()->on_open_document(m_strOpenOnCreate);

         m_strOpenOnCreate.Empty();

      }

   }

}



void html_form_view::handle(::topic * ptopic, ::context * pcontext)
{

   ::html_form::handle(ptopic, pcontext);

   ////__update(::update)
   {

      if (ptopic->m_id == id_document_complete)
      {

         ASSERT(get_html_data() != nullptr);

         defer_implement();

         _001InitializeFormPreData();

         _001UpdateFunctionStatic();

         for (auto pinteraction : proper_children())
         {

            _001Update(pinteraction);

         }

         defer_html_layout();

         on_document_complete(ptopic->m_pextendedtopic->payload(id_url));

         get_parent_frame()->set_active_view(this);

         set_keyboard_focus();

      }

   }

   ////__update(::update)
   {

      if (ptopic->m_id == id_browse)
      {

         if (!ptopic->m_pextendedtopic->payload(id_form).is_empty())
         {

            ::file::path matter;

            auto pcontext = get_context();

            matter = pcontext->m_papexcontext->dir().matter(ptopic->m_pextendedtopic->payload(id_form));

            if (get_document()->on_open_document(matter))
            {

               m_strPath = ptopic->m_pextendedtopic->payload(id_form);

            }

         }
         else if (ptopic->m_id == id_get_form_view)
         {

            ptopic->m_pextendedtopic->payload(id_form) = this;

         }

      }

      if (m_pcallback != nullptr)
      {

         ptopic->m_pextendedtopic->payload(id_form) = this;

         m_pcallback->handle(ptopic, pcontext);

      }

   }

}


void html_view::handle(::topic * ptopic, ::context * pcontext)
{

   ::html_form::handle(ptopic, pcontext);

   ////__update(::update)
   {

      if (ptopic->m_id == id_document_complete)
      {

         {

            synchronous_lock synchronouslock(mutex());

            if (get_html_data() == nullptr)
            {

               return;

            }

            get_html_data()->implement(this);

         }
         
         on_document_complete(ptopic->m_pextendedtopic->payload(id_url));

         set_need_layout();

         set_need_redraw();

      }

   }

}


void html_form::on_form_implemented()
{
   
   auto pdocument = get_document();
   
   if(::is_set(pdocument))
   {
      
      pdocument->call_routines_with_id("load");
      
   }
   
}



