#include "framework.h"
#include "acme/handler/topic.h"
#include "aura/user/user/interaction.h"
#include "base/user/form/document.h"
#include "base/user/form/impact.h"
#include "base/user/simple/frame_window.h"
#include "core/platform/session.h"
#include "core/user/user/user.h"

#include "acme/constant/id.h"
#include "dialog.h"
//#include "user.h"


dialog::dialog()
{

   m_pformdocument = nullptr;
   m_pframe = nullptr;

}


dialog::dialog(const ::scoped_string & scopedstrMatter, ::pointer<::user::interaction>puiParent)
{

   initialize(puiParent);

   m_strMatter = scopedstrMatter;
   m_pformdocument    = nullptr;
   m_pframe       = nullptr;

}


dialog::~dialog()
{
   if(m_pformdocument != nullptr)
   {
      m_pformdocument->on_close_document();
      m_pformdocument = nullptr;
   }
   if(m_pframe != nullptr)
   {
//      m_pframe->DestroyWindow();
      // m_pframe = nullptr;
   }
}


void dialog::handle(::topic * ptopic, ::handler_context * phandlercontext)
{

   if(::is_set(ptopic->user_interaction()) && m_pform == nullptr)
   {

      if(ptopic->id() == ::id_create)
      {

         m_pform = ptopic->user_interaction();

      }

   }

}


bool dialog::show(const ::scoped_string & scopedstrMatter)
{

   string strMatter(scopedstrMatter);

   if(!case_insensitive_string_begins(strMatter, "matter://"))
   {

      strMatter = "matter://" + strMatter;

   }

   m_strMatter = ::file::path(strMatter);

   ::payload payload;

   payload["url"] = strMatter;

   payload["hold"] = false;

   ::payload varArgs;

   varArgs["window_frame"] = true;

   auto pcontext = m_papplication;
   
   auto psession = pcontext->m_psession;
   
   auto puser = psession->m_puser;

   m_pformdocument = puser->create_form(this, nullptr, this, psession->get_user_interaction_host(), payload, varArgs);

   if(m_pformdocument == nullptr)
   {

      string str;

      str.formatf("Could not show dialog %s", scopedstrMatter.c_str());

      informationf(str);

      return false;

   }

   m_pframe = m_pformdocument->get_impact()->parent_frame();

   m_pframe->m_bCloseApplicationIfLastVisibleFrame = false;

   //m_pframe->add_each_routine_from(DIALOG_RESULT_PROCESS, this);

   m_pform = m_pformdocument->get_typed_impact<::user::form>();

   on_position_parent_frame();

   on_show(m_strMatter);

   //m_pframe->_001FancyInitialFramePlacement();
//
   //m_pframe->RunModalLoop();

   //m_pframe->DestroyWindow();

   //m_pformdocument->close_document();

   //m_pform.release();

   //m_pframe.release();

   //m_pformdocument.release();

   return true;

}


void dialog::on_show(const ::scoped_string & scopedstrMatter)
{

   m_pform->set_need_redraw();

   m_pform->post_redraw();

}


void dialog::EndModalLoop(atom idResult)
{

   if (m_pframe == nullptr)
   {

      return;

   }

   m_pframe->display(e_display_none);

   m_pframe->set_need_redraw();

   m_pframe->post_redraw();

   m_pframe->set_dialog_result(idResult);

}







void dialog::on_position_parent_frame()
{

   ::int_rectangle rectangleOpen;

   m_pframe->best_monitor(&rectangleOpen);

   int iWidth = rectangleOpen.width();

   int iHeight = rectangleOpen.height();

   rectangleOpen.deflate(iWidth / 5, iHeight / 5);

   m_pframe->order(e_zorder_top);

   m_pframe->place(rectangleOpen);

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



CLASS_DECL_CORE void DDX_Control(::user::data_exchange * pdx, atom idControl, ::user::interaction & control)
{
}

CLASS_DECL_CORE void DDX_Text(::user::data_exchange * pdx, atom idControl, string & str)
{
}

CLASS_DECL_CORE void DDV_MaxChars(::user::data_exchange * pdx, string & str, int iMax)
{
}

CLASS_DECL_CORE void DDX_Check(::user::data_exchange * pdx, atom idControl, int & iBool)
{
}

CLASS_DECL_CORE void DDX_Check(::user::data_exchange * pdx, atom idControl, bool & b)
{
}


