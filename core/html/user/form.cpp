#include "framework.h"
#include "_user.h"
#include "aura/update.h"


html_form::html_form()
{

   m_pelementLButtonDown = nullptr;
   m_pelementHover = nullptr;

   //m_flagNonClient.remove(non_client_background);
   m_flagNonClient.remove(non_client_focus_rect);

   //m_phtmlform = new html::form();



}

html_form::~html_form()
{

   //::acme::del(m_phtmlform);

}


::estatus html_form::initialize(::layered * pobjectContext)
{

   auto estatus = ::user::form_view::initialize(pobjectContext);

   if (!estatus)
   {

      return estatus;

   }

   estatus = System.defer_create_html();

   if (!estatus)
   {

      return estatus;

   }

   return estatus;

}


void html_form::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
{

   //pgraphics->fill_solid_rect_dim(5, 5, 100, 100, ARGB(255, 255, 255, 0));

   ::html_data * sphtmldata = nullptr;

   try
   {

      sphtmldata = get_html_data();

   }
   catch(...)
   {

   }

   if(sphtmldata != nullptr)
   {

      sphtmldata->_001OnDraw(pgraphics);

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
   UNREFERENCED_PARAMETER(pmessage);
   if(get_html_data() != nullptr)
   {

      ::rect rectClient;

      get_client_rect(rectClient);

      if(rectClient.area() > 0)
      {

         get_html_data()->m_pcoredata->m_box = rectClient;

         sync_lock lock(get_html_data()->mutex());

         auto pimage = create_image({ 50,  50 });

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

   MESSAGE_LINK(e_message_create, pchannel, this, &html_form::_001OnCreate);

   //MESSAGE_LINK(e_message_left_button_down, pchannel, this, &::user::interaction::_001OnLButtonDown);
   //MESSAGE_LINK(e_message_left_button_up, pchannel, this, &::user::interaction::_001OnLButtonUp);
   MESSAGE_LINK(e_message_key_down, pchannel, this, &::html_form::_001OnKeyDown);
   //MESSAGE_LINK(e_message_key_up, pchannel, this, &::user::interaction::_001OnKeyUp);

   MESSAGE_LINK(e_message_left_button_down, pchannel, this, &html_form::_001OnLButtonDown);
   MESSAGE_LINK(e_message_mouse_move, pchannel, this, &html_form::_001OnMouseMove);
   MESSAGE_LINK(e_message_mouse_leave, pchannel, this, &html_form::_001OnMouseLeave);
   MESSAGE_LINK(e_message_left_button_up, pchannel, this, &html_form::_001OnLButtonUp);

   MESSAGE_LINK(html::message_on_image_loaded, pchannel, this, &html_form::_001OnImageLoaded);

   MESSAGE_LINK(e_message_create, pchannel, this, &html_form::_001OnDestroy);

}


void html_form::GetClientBox(::rectf & box)
{

   ::rect rectClient;

   get_client_rect(rectClient);

   box = rectClient;

}


void html_form::on_layout(::draw2d::graphics_pointer & pgraphics)
{

   sync_lock sl(mutex());

   if(get_html_data() == nullptr)
   {

      return;

   }

   get_html_data()->layout(this);

   ::user::control_event ev;

   ev.m_eevent = ::user::event_layout;

   ev.m_puie = this;

   on_control_event(&ev);

   if (m_bNeedLoadFormData)
   {

      update_data(false);

   }


}


void html_form::_001OnCreate(::message::message * pmessage)
{

   SCAST_PTR(::message::create, pcreate, pmessage);

   System.defer_create_html();

   if(pcreate->previous())
   {

      return;

   }

}


void html_form::_001OnLButtonDown(::message::message * pmessage)
{

   SCAST_PTR(::message::mouse, pmouse, pmessage);

   ::point point;

   point = pmouse->m_point;

   _001ScreenToClient(point);

   if(get_html_data() != nullptr
      && get_html_data()->m_pcoredata != nullptr)
   {

      m_pelementLButtonDown = get_html_data()->m_pcoredata->m_element.hit_test(get_html_data(), point);

   }

   if(m_pelementLButtonDown != nullptr)
   {

      ::html::message htmlmessage;

      htmlmessage.m_pdata = get_html_data();

      htmlmessage.m_psignal = pmouse;

      htmlmessage.m_pchannel = pmouse->m_pchannel;

      m_pelementLButtonDown->OnLButtonDown(&htmlmessage);

   }
   else
   {

      auto psession = Session;

      psession->clear_focus();

   }

   pmouse->m_bRet = true;

   pmouse->m_lresult = 1;

}


void html_form::_001OnMouseMove(::message::message * pmessage)
{

   SCAST_PTR(::message::mouse, pmouse, pmessage);

   track_mouse_hover();

   ::point point(pmouse->m_point);

   _001ScreenToClient(point);

   sync_lock sl(mutex());

   if(::is_set(get_html_data()))
   {

      sync_lock sl(get_html_data()->mutex());

      html::element * pelement = get_html_data()->m_pcoredata->m_element.hit_test(get_html_data(), point);

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

         htmlmessage.m_pdata = get_html_data();

         htmlmessage.m_psignal = pmouse;

         htmlmessage.m_puserinteraction = this;

         htmlmessage.m_pchannel = pmouse->m_pchannel;

         pelement->OnMouseMove(&htmlmessage);

      }

   }

}


void html_form::_001OnMouseLeave(::message::message * pmessage)
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


void html_form::_001OnLButtonUp(::message::message * pmessage)
{

   SCAST_PTR(::message::mouse, pmouse, pmessage);

   ::point point(pmouse->m_point);

   _001ScreenToClient(point);

   html::element * pelement = nullptr;

   if(get_html_data() != nullptr
      && get_html_data()->m_pcoredata != nullptr)
   {

      get_html_data()->m_pcoredata->m_element.hit_test(get_html_data(), point);

   }

   if(m_pelementLButtonDown != nullptr && pelement == m_pelementLButtonDown)
   {

      ::html::message htmlmessage;

      htmlmessage.m_pdata = get_html_data();

      htmlmessage.m_psignal = pmouse;

      htmlmessage.m_pchannel = pmouse->m_pchannel;

      m_pelementLButtonDown->OnLButtonUp(&htmlmessage);

   }
}


void html_form::_001OnDestroy(::message::message * pmessage)
{

   if (get_document() != nullptr)
   {

      ::html_data * pdata = get_document()->get_html_data();

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

      sync_lock lock(psync);

      str = phtmldata->m_pcoredata->m_strSource;

   }

   m_pformParent->open_html(str);

}


void html_form::set_need_load_form_data()
{

   if (!m_phtmldata->m_pcoredata->m_bImplemented)
   {

      m_bNeedLoadFormData = true;

      set_need_layout();

   }
   else
   {

      ::user::form_window::set_need_load_form_data();

   }

}


::estatus html_form::open_document(const payload & varFile)
{

   auto path = varFile.get_file_path();

   if (path.is_empty())
   {

      if (varFile.get_type() == ::type_propset && varFile.propset()["url"].get_string().has_char())
      {

         path = varFile.propset()["url"];

      }
      else if (varFile.cast < ::file::file >() != nullptr)
      {

         path = System.datetime().international().get_gmt_date_time() + "." + get_document()->get_document_template()->find_string("default_extension");

      }
      else
      {

         path = varFile;

      }

   }

   auto phtmldata = get_html_data();

   if(!phtmldata->open_document(varFile))
   {

      return false;

   }

   m_strPath = path;

   return true;

}


::estatus html_form::open_html(const ::string & str)
{

   auto phtmldata = get_html_data();

   auto estatus = phtmldata->open_html(str);

   if(::failed(estatus))
   {

      return estatus;

   }

   return estatus;

}


void html_form::_001GetText(string & str) const
{

   ((html_form *) this)->get_html_data()->m_pcoredata->m_element.get_html((const_cast < html_form * > (this)->get_html_data()), str);

}


void html_form::_001SetText(const string & str, const ::action_context & context)
{

   auto psession = Session;

   bool bFocus = has_focus() || is_descendant(dynamic_cast < ::user::interaction * > (psession->get_keyboard_focus()));

   __pointer(::html_data) sphtmldata;

   sphtmldata = __new(::html_data);

   sphtmldata->m_pcoredata->m_pform = this;

   sphtmldata->load(str);

   sphtmldata->implement_and_layout(this);

   m_phtmldata = sphtmldata;

   if(bFocus)
   {
      __pointer(::user::primitive) pfocus = get_focusable_descendant();
      if(pfocus != nullptr)
      {
         auto psession = Session;

         psession->set_keyboard_focus(pfocus);
      }
   }
   _001OnInitializeForm();
}


html_document * html_form::get_document()
{

   return dynamic_cast <html_document*> (::user::impact::get_document());

}


::html_data * html_form::get_html_data()
{

   auto pdata = m_phtmldata;

   if (pdata)
   {

      return pdata;

   }

   pdata = __new(html_data);

   pdata->initialize(this);

   pdata->m_pcoredata = new ::html::core_data;

   pdata->m_pcoredata->initialize_html_data(pdata);

   pdata->m_pimplHtml = ::move(pdata->m_pcoredata);

   pdata->::form_data::m_pimpl = pdata->m_pimplHtml;

   pdata->m_pcoredata->m_puserinteraction = this;

   pdata->m_pcoredata->m_pform = this;

   pdata->m_pcoredata->m_pcallback = this;

   m_phtmldata = pdata;

   return pdata;

}


void html_form::_001OnKeyDown(::message::message * pmessage)
{
   SCAST_PTR(::message::key, pkey, pmessage);
   if(pkey->m_ekey == ::user::key_tab)
   {
      pkey->m_bRet = true;
      return;
   }
}


void html_form::defer_implement()
{

   if(get_html_data() == nullptr)
      return;

   GetClientBox(get_html_data()->m_pcoredata->m_box);

   if(get_html_data()->m_pcoredata->m_box.area() <= 0.f)
      return;

   auto pimage = create_image({ 50,  50 });

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

   auto pimage = create_image({ 50,  50 });

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


bool html_form::load_html(const string & str)
{

   get_html_data()->load(str);

   return true;

}




void html_form::on_subject(::promise::subject * psubject, ::promise::context * pcontext)
{

   ::user::form_view::on_subject(psubject, pcontext);

   ////__update(::update)
   {

      if (psubject->id() == id_document_complete)
      {

         m_phtmldata = get_document()->get_html_data();

      }

   }

   if (psubject->id() == id_open_document)
   {

      if (m_strOpenOnCreate.has_char())
      {

         get_document()->on_open_document(m_strOpenOnCreate);

         m_strOpenOnCreate.Empty();

      }

   }

}



void html_form_view::on_subject(::promise::subject * psubject, ::promise::context * pcontext)
{

   ::html_form::on_subject(psubject, pcontext);

   ////__update(::update)
   {

      if (psubject->id() == id_document_complete)
      {

         ASSERT(get_html_data() != nullptr);

         defer_implement();

         _001InitializeFormPreData();

         _001UpdateFunctionStatic();

         for (auto & pdescriptor : m_controldescriptorset.ptra())
         {

            auto pinteraction = pdescriptor->m_pinteraction;

            if (pinteraction)
            {

               _001Update(pinteraction);

            }

         }

         defer_html_layout();

         on_document_complete(psubject->value(id_url));

         GetParentFrame()->SetActiveView(this);

         SetFocus();

      }

   }

   ////__update(::update)
   {

      if (psubject->id() == id_browse)
      {

         if (!psubject->value(id_form).is_empty())
         {

            ::file::path matter;

            matter = Context.dir().matter(psubject->value(id_form));

            if (get_document()->on_open_document(matter))
            {

               m_strPath = psubject->value(id_form);

            }

         }
         else if (psubject->id() == id_get_form_view)
         {

            psubject->value(id_form) = this;

         }

      }

      if (m_pcallback != nullptr)
      {

         psubject->value(id_form) = this;

         m_pcallback->process(psubject);

      }

   }

}



void html_view::on_subject(::promise::subject * psubject, ::promise::context * pcontext)
{

   ::html_form::on_subject(psubject, pcontext);

   ////__update(::update)
   {

      if (psubject->id() == id_document_complete)
      {

         {

            sync_lock sl(mutex());

            if (get_html_data() == nullptr)
            {

               return;

            }

            get_html_data()->implement(this);

         }

         on_document_complete(psubject->value(id_url));

         set_need_layout();

         set_need_redraw();

      }

   }

}

