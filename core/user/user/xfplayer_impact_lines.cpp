#include "framework.h"
#include "xfplayer_impact_line.h"
#include "xfplayer_impact_lines.h"
#include "xfplayer_impact_line_selection.h"
#include "acme/constant/message.h"
#include "acme/parallelization/synchronous_lock.h"
#include "apex/message/channel.h"
#include "apex/message/message.h"


xfplayer_impact_linea::xfplayer_impact_linea(::user::interaction * puserinteraction) :
   m_pselection(__initialize_new xfplayer_impact_line_selection(puserinteraction)),
   m_puserinteraction(puserinteraction)
{

   defer_create_synchronization();
   m_iFirstVisible = -1;
   m_iLastVisible = -1;

}


xfplayer_impact_linea::~xfplayer_impact_linea()
{

}



void xfplayer_impact_linea::OnChildSetVisible(xfplayer_impact_line * pline, bool bVisible)
{

   _synchronous_lock synchronouslock(this->synchronization());

   ::collection::index iLineIndex = FindLine(pline);

   ::collection::index iIndex;

   if (bVisible)
   {
      if (iLineIndex < m_iFirstVisible)
         m_iFirstVisible = iLineIndex;
      else if (iLineIndex > m_iLastVisible)
         m_iLastVisible = iLineIndex;
   }
   else
   {
      iIndex = iLineIndex;
      if (iIndex >= m_iFirstVisible)
      {
         while (!this->line_at(iIndex)->IsVisible())
         {
            iIndex++;
            if (iIndex >= this->line_count())
               break;
         }
      }
      m_iFirstVisible = iIndex;
      iIndex = iLineIndex;
      if (iIndex <= m_iLastVisible)
      {
         while (!this->line_at(iIndex)->IsVisible())
         {
            iIndex--;
            if (iIndex < 0)
               break;
         }
      }
      m_iLastVisible = iIndex;
   }

}

::collection::index xfplayer_impact_linea::GetFirstVisibleLineIndex()
{
   return m_iFirstVisible;
}

::collection::index xfplayer_impact_linea::GetLastVisibleLineIndex()
{
   return m_iLastVisible;
}

void xfplayer_impact_linea::Prepare()
{
   _synchronous_lock synchronouslock(this->synchronization());
   for (int i = 0; i < this->line_count(); i++)
   {
      this->line_at(i)->m_pContainer = this;
      this->line_at(i)->m_iIndex = i;
   }
}

void xfplayer_impact_linea::Prepare(xfplayer_impact_line *pImpactLine)

{
   _synchronous_lock synchronouslock(this->synchronization());
   pImpactLine->m_pContainer = this;

}

//void xfplayer_impact_linea::set_user_interaction(::pointer<::user::interaction>pinteraction)
//{
//   
//   m_pinteraction = pinteraction;
//
//}


void xfplayer_impact_linea::SetEffect(int iEffect)
{
   _synchronous_lock synchronouslock(this->synchronization());
   for (int i = 0; i < this->line_count(); i++)
   {
      this->line_at(i)->SetTextEffect(iEffect);
   }
}

//void xfplayer_impact_linea::SetRenderWindow(::windowing::window * pwindow)
//{
//   __UNREFERENCED_PARAMETER(pwindow);
//}

::collection::index xfplayer_impact_linea::FindLine(xfplayer_impact_line * pline)
{
   _synchronous_lock synchronouslock(this->synchronization());
   for (int iLine = 0; iLine < this->line_count(); iLine++)
   {
      if (line_at(iLine) == pline)
         return iLine;
   }
   return -1;
}

::user::enum_line_hit xfplayer_impact_linea::hit_test(const int_point &pointCursor, ::collection::index &iLine, character_count &iChar)
{
   _synchronous_lock synchronouslock(this->synchronization());
   for (::collection::index i = 0; i < this->line_count(); i++)
   {
      ::user::enum_line_hit etest = this->line_at(i)->hit_test(pointCursor, iChar);
      if (etest != ::user::e_line_hit_none)
      {
         iLine = i;
         return  etest;
      }
   }
   return ::user::e_line_hit_none;

}

void xfplayer_impact_linea::install_message_routing(::channel * pchannel)
{
   MESSAGE_LINK(::user::e_message_mouse_move, pchannel, this, &xfplayer_impact_linea::OnMouseMove);
   MESSAGE_LINK(::user::e_message_set_cursor, pchannel, this, &xfplayer_impact_linea::OnSetCursor);
   //MESSAGE_LINK(::user::e_message_timer,        pchannel, this, &xfplayer_impact_linea::OnTimer);
   MESSAGE_LINK(::user::e_message_left_button_down, pchannel, this, &xfplayer_impact_linea::OnLButtonDown);
   MESSAGE_LINK(::user::e_message_left_button_up, pchannel, this, &xfplayer_impact_linea::OnLButtonUp);
}

void xfplayer_impact_linea::OnMouseMove(::message::message * pmessage)
{
   _synchronous_lock synchronouslock(this->synchronization());
   for (int i = 0; i < this->line_count(); i++)
   {
      this->line_at(i)->m_pContainer = this;
      this->line_at(i)->m_iIndex = i;
      this->line_at(i)->OnMouseMove(pmessage);
      if (pmessage->m_bRet)
         return;
   }
}

void xfplayer_impact_linea::OnLButtonDown(::message::message * pmessage)
{
   _synchronous_lock synchronouslock(this->synchronization());
   for (int i = 0; i < this->line_count(); i++)
   {
      this->line_at(i)->m_pContainer = this;
      this->line_at(i)->m_iIndex = i;
      this->line_at(i)->OnLButtonDown(pmessage);
      if (pmessage->m_bRet)
         return;
   }
}

void xfplayer_impact_linea::OnLButtonUp(::message::message * pmessage)
{
   _synchronous_lock synchronouslock(this->synchronization());
   for (int i = 0; i < this->line_count(); i++)
   {
      this->line_at(i)->OnLButtonUp(pmessage);
      if (pmessage->m_bRet)
         return;
   }
}

void xfplayer_impact_linea::on_timer(::timer * ptimer)
{
   _synchronous_lock synchronouslock(this->synchronization());
   for (int i = 0; i < this->line_count(); i++)
   {
      this->line_at(i)->on_timer(ptimer);
   }
}

void xfplayer_impact_linea::OnSetCursor(::message::message * pmessage)
{
   _synchronous_lock synchronouslock(this->synchronization());
   for (int i = 0; i < this->line_count(); i++)
   {
      this->line_at(i)->OnSetCursor(pmessage);
      if (pmessage->m_bRet)
         return;
   }
}

void xfplayer_impact_linea::set_blend(double dBlend)
{
   _synchronous_lock synchronouslock(this->synchronization());
   for (int iLine = 0; iLine < this->line_count(); iLine++)
   {
      line_at(iLine)->set_blend(dBlend);
   }
}


xfplayer_impact_line_selection & xfplayer_impact_linea::GetSelection()
{
   
   return *m_pselection;

}


void xfplayer_impact_linea::get_sel_text(string & strSelText, const ::scoped_string & scopedstrLineSeparator)
{
   _synchronous_lock synchronouslock(this->synchronization());
   ::collection::index iLineStart;
   ::collection::index iCharStart;
   ::collection::index iLineEnd;
   ::collection::index iCharEnd;

   m_pselection->GetNormalSelection(iLineStart, iCharStart, iLineEnd, iCharEnd);

   if (iLineEnd >= iLineStart)
   {

      if (iLineStart < 0)
         return;

      if (iLineEnd < 0)
         return;

      if (iLineEnd == iLineStart)
      {

         strSelText = line_at(iLineStart)->m_str.substr(iCharStart, iCharEnd - iCharStart + 1);

      }
      else
      {

         strSelText = line_at(iLineStart)->m_str.substr(iCharStart);

         for (::collection::index iLine = iLineStart + 1; iLine < iLineEnd; iLine++)
         {

            strSelText += scopedstrLineSeparator;

            strSelText += line_at(iLine)->m_str;

         }

         if (iLineEnd > iLineStart)
         {

            strSelText += scopedstrLineSeparator;

            strSelText += line_at(iLineEnd)->m_str.substr(0, iCharEnd + 1);

         }
      }

   }

}

string xfplayer_impact_linea::get_sel_text(const ::scoped_string & scopedstrLineSeparator)
{

   string strSelText;

   get_sel_text(strSelText, scopedstrLineSeparator);

   return strSelText;

}


void xfplayer_impact_linea::get_text(string & strText, const ::scoped_string & scopedstrLineSeparator)
{
   _synchronous_lock synchronouslock(this->synchronization());
   if (line_count() > 0)
   {

      strText = line_at(0)->m_str;

   }

   for (int iLine = 1; iLine < line_count(); iLine++)
   {

      strText += scopedstrLineSeparator;

      strText += line_at(iLine)->m_str;

   }

}

string xfplayer_impact_linea::get_text(const ::scoped_string & scopedstrLineSeparator)
{

   string strText;

   //linetext(strText, pszLineSeparator);

   return strText;

}
