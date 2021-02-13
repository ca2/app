#include "framework.h"
#include "core/user/userex/_userex.h"
#include "aura/id.h"
#include "core/user/userex/_userex.h"


dialog::dialog()
{

   m_pdocument = nullptr;
   m_pframe = nullptr;

}

dialog::dialog(const char * pszMatter, __pointer(::user::interaction) puiParent) :
   object(puiParent->get_context_application())
{

   m_strMatter = pszMatter;
   m_pdocument    = nullptr;
   m_pframe       = nullptr;

}


dialog::~dialog()
{
   if(m_pdocument != nullptr)
   {
      m_pdocument->on_close_document();
      m_pdocument = nullptr;
   }
   if(m_pframe != nullptr)
   {
//      m_pframe->DestroyWindow();
      // m_pframe = nullptr;
   }
}


void dialog::on_control_event(::user::control_event * pevent)
{

   if(::is_set(pevent->m_puie) && m_pform == nullptr)
   {

      if(pevent->m_eevent == ::user::e_event_create)
      {

         m_pform = pevent->m_puie;

      }

   }

}


bool dialog::show(const char * pszMatter)
{

   string strMatter(pszMatter);

   if(!::str::begins_ci(strMatter, "matter://"))
   {

      strMatter = "matter://" + strMatter;

   }

   m_strMatter = ::file::path(strMatter);

   ::payload payload;

   payload["url"] = strMatter;

   payload["hold"] = false;

   ::payload varArgs;

   varArgs["window_frame"] = true;

   auto puser = User;

   auto psession = Session;

   m_pdocument = puser->create_form(this, this, psession->m_puiHost.get(), payload, varArgs);

   if(m_pdocument == nullptr)
   {

      string str;

      str.Format("Could not show dialog %s", pszMatter);

      TRACE(str);

      return false;

   }

   m_pframe = m_pdocument->get_view()->get_parent_frame();

   m_pframe->m_bCloseApplicationIfLastVisibleFrame = false;

   m_pframe->add_each_routine_from(DIALOG_RESULT_PROCESS, this);

   m_pform = m_pdocument->get_typed_view<::user::form>();

   on_position_parent_frame();

   on_show(m_strMatter);

   m_pframe->InitialFramePosition();

   //m_pframe->RunModalLoop();

   //m_pframe->DestroyWindow();

   //m_pdocument->close_document();

   //m_pform.release();

   //m_pframe.release();

   //m_pdocument.release();

   return true;

}


void dialog::on_show(const char * pszMatter)
{

   m_pform->set_need_redraw();

   m_pform->post_redraw();

}


void dialog::EndModalLoop(id idResult)
{

   if (m_pframe == nullptr)
   {

      return;

   }

   m_pframe->display(e_display_none);

   m_pframe->set_need_redraw();

   m_pframe->post_redraw();

   m_pframe->EndModalLoop(idResult);

}







void dialog::on_position_parent_frame()
{

   ::rectangle_i32 rectOpen;

   m_pframe->best_monitor(rectOpen);

   i32 iWidth = rectOpen.width();

   i32 iHeight = rectOpen.height();

   rectOpen.deflate(iWidth / 5, iHeight / 5);

   m_pframe->order(e_zorder_top);

   m_pframe->place(rectOpen);

   m_pframe->ActivateFrame();

   m_pframe->set_need_layout();

   m_pframe->set_need_redraw();

   m_pframe->display();

}

void dialog::OnCancel()
{
}

void dialog::OnOK()
{
}

void dialog::form_from_user()
{
}

void dialog::form_to_user()
{
}


void dialog::do_data_exchange(::user::data_exchange * pdx)
{
}


int_bool dialog::on_init_dialog()
{

   return true;

}



CLASS_DECL_CORE void DDX_Control(::user::data_exchange * pdx, id idControl, ::user::interaction & control)
{
}

CLASS_DECL_CORE void DDX_Text(::user::data_exchange * pdx, id idControl, string & str)
{
}

CLASS_DECL_CORE void DDV_MaxChars(::user::data_exchange * pdx, string & str, i32 iMax)
{
}

CLASS_DECL_CORE void DDX_Check(::user::data_exchange * pdx, id idControl, i32 & iBool)
{
}

CLASS_DECL_CORE void DDX_Check(::user::data_exchange * pdx, id idControl, bool & b)
{
}


