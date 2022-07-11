#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/userex/_userex.h"
#endif

#include "aura/id.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/userex/_userex.h"
#endif



dialog::dialog()
{

   m_pdocument = nullptr;
   m_pframe = nullptr;

}

dialog::dialog(const ::string & pszMatter, __pointer(::user::interaction) puiParent)
{

   initialize(puiParent);

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


void dialog::handle(::topic * ptopic, ::context * pcontext)
{

   if(::is_set(ptopic->user_interaction()) && m_pform == nullptr)
   {

      if(ptopic->m_atom == ::id_create)
      {

         m_pform = ptopic->user_interaction();

      }

   }

}


bool dialog::show(const ::string & pszMatter)
{

   string strMatter(pszMatter);

   if(!::str().begins_ci(strMatter, "matter://"))
   {

      strMatter = "matter://" + strMatter;

   }

   m_strMatter = ::file::path(strMatter);

   ::payload payload;

   payload["url"] = strMatter;

   payload["hold"] = false;

   ::payload varArgs;

   varArgs["window_frame"] = true;

   auto pcontext = m_pcontext;
   
   auto psession = pcontext->m_pcoresession;
   
   auto puser = psession->m_puser->m_pcoreuser;

   m_pdocument = puser->create_form(this, this, psession->get_user_interaction_host(), payload, varArgs);

   if(m_pdocument == nullptr)
   {

      string str;

      str.format("Could not show dialog %s", pszMatter.c_str());

      TRACE(str);

      return false;

   }

   m_pframe = m_pdocument->get_view()->parent_frame();

   m_pframe->m_bCloseApplicationIfLastVisibleFrame = false;

   //m_pframe->add_each_routine_from(DIALOG_RESULT_PROCESS, this);

   m_pform = m_pdocument->get_type_impact<::user::form>();

   on_position_parent_frame();

   on_show(m_strMatter);

   //m_pframe->_001FancyInitialFramePlacement();
//
   //m_pframe->RunModalLoop();

   //m_pframe->DestroyWindow();

   //m_pdocument->close_document();

   //m_pform.release();

   //m_pframe.release();

   //m_pdocument.release();

   return true;

}


void dialog::on_show(const ::string & pszMatter)
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

   m_pframe->EndModalLoop(idResult);

}







void dialog::on_position_parent_frame()
{

   ::rectangle_i32 rectangleOpen;

   m_pframe->best_monitor(rectangleOpen);

   i32 iWidth = rectangleOpen.width();

   i32 iHeight = rectangleOpen.height();

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

CLASS_DECL_CORE void DDV_MaxChars(::user::data_exchange * pdx, string & str, i32 iMax)
{
}

CLASS_DECL_CORE void DDX_Check(::user::data_exchange * pdx, atom idControl, i32 & iBool)
{
}

CLASS_DECL_CORE void DDX_Check(::user::data_exchange * pdx, atom idControl, bool & b)
{
}


