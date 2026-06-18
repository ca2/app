#include "framework.h"
#include "xfplayer_impact_line_selection.h"
#include "xfplayer_impact_line.h"
#include "acme/constant/user_message.h"
#include "acme/constant/timer.h"
#include "aura/windowing/window.h"
#include "aura/message/user.h"
#include "aura/user/user/interaction.h"


xfplayer_impact_line_selection::xfplayer_impact_line_selection(::user::interaction * puserinteraction) :
   m_puserinteraction(puserinteraction)
{

   m_estate = e_state_initial;

}


xfplayer_impact_line_selection::~xfplayer_impact_line_selection()
{

}


void xfplayer_impact_line_selection::relay_event(xfplayer_impact_line * pline, ::message::message * pmessage)
{

   ::pointer<::user::message>pusermessage(pmessage);

   auto emessage = pusermessage->m_eusermessage;

   if(emessage != ::user::e_message_mouse_move
         && emessage != ::user::e_message_timer
         && emessage != ::user::e_message_left_button_down
         && emessage != ::user::e_message_left_button_up)
   {
      return;
   }

   ::collection::index iLine;

   character_count iChar;

   if((emessage == ::user::e_message_mouse_move && GetState() == e_state_tracking)
         || emessage == ::user::e_message_left_button_down
         || emessage == ::user::e_message_left_button_up)
   {
      
      bool bInside;
      
      auto pointCursor = pusermessage->m_lparam.point();

      ::i32_rectangle rectanglePlacement;
      
      pline->GetPlacement(&rectanglePlacement);
      
      bInside = rectanglePlacement.contains(pointCursor) != 0;
      
      if(!bInside && GetState() == e_state_tracking)
      {
         if(emessage == ::user::e_message_left_button_up
               || emessage == ::user::e_message_mouse_move)
         {
            if(pointCursor.y < rectanglePlacement.top
                  ||
                  (pointCursor.y <= rectanglePlacement.bottom &&
                   pointCursor.x < rectanglePlacement.left))
            {
               SetSelBefore(pline);
               //                   pline->get_interaction()->set_need_redraw();
            }
            else
            {
               SetSelAfter(pline);
               //                pline->get_interaction()->set_need_redraw();
            }
            if(emessage == ::user::e_message_left_button_up)
            {
               OnSelEvent(pline, e_event_end);
            }
         }
         return;
      }
      else if(bInside)
      {
         //::u32 fwKeys = pusermessage->m_wparam; // key flags
         if(emessage == ::user::e_message_left_button_down)
         {
            if(pline->CalcChar(pointCursor, iChar))
            {
               iLine = pline->m_iIndex;
               m_item.SetLineStart(iLine);
               m_item.SetCharStart(iChar);
               m_item.SetLineEnd(iLine);
               m_item.SetCharEnd(iChar);
               //                m_etype = TypeMaskStartHere;
            }
            else
            {
               m_item.SetLineStart(-1);
               m_item.SetCharStart(-1);
               m_item.SetLineEnd(-1);
               m_item.SetCharEnd(-1);
            }
            //                pline->get_interaction()->set_need_redraw();
            OnSelEvent(pline, e_event_start);
            pusermessage->m_bRet = true;
            return;
         }
         else if(
         (emessage == ::user::e_message_left_button_up
          || emessage == ::user::e_message_mouse_move)
         && GetState() == e_state_tracking)
         {
            if(pline->CalcChar(pointCursor, iChar))
            {
               iLine = pline->m_iIndex;
               m_item.SetLineEnd(iLine);
               m_item.SetCharEnd(iChar);
               //                m_item.NormalizeSel();
               //                m_etype |= TypeMaskEndHere;
               //pline->get_interaction()->set_need_redraw();
            }
            else
            {
               if(pointCursor.x < pline->m_iaPosition[0])
               {
                  SetSelBefore(pline);
               }
               {
                  SetSelAfter(pline);
               }
               //pline->get_interaction()->set_need_redraw();

            }
            if(emessage == ::user::e_message_left_button_up)
            {
               OnSelEvent(pline, e_event_end);
               if(m_iLineStartSource == m_item.GetLineStart()
                     && m_iLineEndSource == m_item.GetLineEnd()
                     && m_iCharStartSource == m_item.GetCharStart()
                     && m_iCharEndSource == m_item.GetCharEnd())
               {

                  string str;

                  auto pointCursor = m_puserinteraction->mouse_cursor_position();

                  if(pline->get_link(str, pointCursor))
                  {
                     //usersp(::user::impact) pimpact = pline->get_interaction();
                     //pimpact->on_link_click(str);
                  }
               }
            }
            pusermessage->m_bRet = true;
            return;
         }
         else if(emessage == ::user::e_message_mouse_move)
         {

            auto pointCursor = m_puserinteraction->mouse_cursor_position();

            pline->update_hover(pointCursor);

         }

      }

   }
   else if(emessage == ::user::e_message_timer)
   {

      uptr uEvent = pusermessage->m_wparam;

      if(uEvent == ::e_timer_hover_update)
      {

         auto pointCursor = m_puserinteraction->mouse_cursor_position();

         pline->update_hover(pointCursor);

         if(!pline->is_hover())
         {

            ::pointer<::user::interaction>puserinteraction = pline->get_interaction();

            puserinteraction->kill_timer(::e_timer_hover_update);

         }

      }

   }

}


void xfplayer_impact_line_selection::OnSelEvent(xfplayer_impact_line * pline, xfplayer_impact_line_selection::enum_happening ehappening)
{
   __UNREFERENCED_PARAMETER(pline);
   switch(ehappening)
   {
   case e_event_start:
      m_iLineStartSource  = m_item.GetLineStart();
      m_iLineEndSource      = m_item.GetLineEnd();
      m_iCharStartSource   = m_item.GetCharStart();
      m_iCharEndSource      = m_item.GetCharEnd();
      m_estate               = e_state_tracking;

      //         pline->GetTemplate()->OnSelStart(&pline);
      break;
   case e_event_end:
      //NormalizeSel(pline);
      //         m_item.NormalizeSel();
      Select(
      m_item.GetLineStart(),
      m_item.GetLineEnd(),
      m_item.GetCharStart(),
      m_item.GetCharEnd(), false);
      m_estate = e_state_initial;
      //      pline->GetTemplate()->OnSelEnd(&pline);

      break;
   default:
      ASSERT(false);
   }
}

bool xfplayer_impact_line_selection::SetSelBefore(xfplayer_impact_line * pline)
{
   /*   if(m_etype & TypeMaskEndHere)
   {
   if(m_etype & TypeMaskStartHere)
   {
   m_etype &= ~TypeMaskStartHere;*/
   m_item.SetLineStart(pline->m_iIndex);
   m_item.SetCharStart(0);
   /*      }
   }
   else if(m_etype &  TypeMaskStartHere)
   {
   m_etype &= ~TypeMaskStartHere;
   m_etype |= TypeMaskEndHere;
   m_item.SetLineStart(pline->GetFirstLine());
   m_item.SetCharStart(0);
   }
   else
   {
   string str;
   pline->m_tokenaMain.element_at(pline->GetLineCount() - 1).GetText(str);
   m_item.SetLineStart(pline->GetFirstLine());
   m_item.SetCharStart(0);
   m_item.SetLineEnd(pline->GetFirstLine() + pline->GetLineCount() - 1);
   m_item.SetCharEnd(pline->m_tokenaMain.last().GetCharCount() - 1);
   }*/
   return true;
}

bool xfplayer_impact_line_selection::SetSelAfter(xfplayer_impact_line * pline)
{
   if(pline->m_iaPosition.get_count() > 0)
   {
      m_item.SetLineEnd(pline->m_iIndex);
      m_item.SetCharEnd(pline->m_iaPosition.get_upper_bound());
   }

   /*   if(m_etype & TypeMaskEndHere)
   {
   if(m_etype & TypeMaskStartHere)
   {*/
   /*         string str;
   pline->m_tokenaMain.element_at(pline->GetLineCount() - 1).GetText(str);
   //         m_etype &= ~TypeMaskEndHere;
   m_item.SetLineEnd(pline->GetFirstLine() + pline->m_tokenaMain.get_size() - 1);
   m_item.SetCharEnd(str.length());*/
   /*      }
   else
   {
   string str;
   pline->m_tokenaMain.element_at(pline->GetLineCount() - 1).GetText(str);
   m_etype &= ~TypeMaskEndHere;
   m_etype |= TypeMaskStartHere;
   m_item.SetLineEnd(pline->GetFirstLine() + pline->m_tokenaMain.get_size() - 1);
   m_item.SetCharEnd(str.length() - 1);
   }
   }
   else if(m_etype &  TypeMaskStartHere)
   {
   }
   else
   {
   string str;
   pline->m_tokenaMain.element_at(pline->GetLineCount() - 1).GetText(str);
   m_item.SetLineStart(pline->GetFirstLine());
   m_item.SetCharStart(0);
   m_item.SetLineEnd(pline->GetFirstLine() + pline->m_tokenaMain.get_size() - 1);
   m_item.SetCharEnd(str.length() - 1);
   }*/
   return true;
}

void xfplayer_impact_line_selection::NormalizeSel(xfplayer_impact_line * pline)
{
   __UNREFERENCED_PARAMETER(pline);
   ASSERT(false);
   /*   string str;
   if(m_item.m_iLineStart < 0)
   {
   }
   else if(m_item.m_iLineStart >= pline->m_tokenaMain.get_size())
   {
   m_item.m_iLineStart = pline->m_tokenaMain.get_size() - 1;
   if(m_item.m_iLineStart < 0)
   {
   m_item.m_iCharStart = -1;
   }
   else
   {
   m_item.m_iCharStart = 0;
   }
   }
   if(m_item.m_iLineStart < 0)
   {
   }
   else
   {
   pline->m_tokenaMain[m_item.m_iLineStart].GetText(str);
   if(m_item.m_iCharStart >= str.length())
   {
   if(str.is_empty())
   {
   m_item.m_iCharStart = 0;
   }
   else
   {
   m_item.m_iCharStart = str.length() - 1;
   }
   }
   if(m_item.m_iLineEnd < 0)
   {
   m_item.m_iLineEnd = m_item.m_iLineStart;
   m_item.m_iCharEnd = m_item.m_iCharStart;
   }
   else if(m_item.m_iCharEnd < 0)
   {
   m_item.m_iCharEnd = m_item.m_iCharStart;
   }

   if(m_item.m_iLineEnd >= pline->m_tokenaMain.get_size())
   {
   m_item.m_iLineEnd = pline->m_tokenaMain.get_size() - 1;
   if(m_item.m_iLineEnd < 0)
   {
   m_item.m_iCharEnd = -1;
   }
   else
   {
   pline->m_tokenaMain[m_item.m_iLineEnd].GetText(str);
   if(str.is_empty())
   {
   m_item.m_iCharEnd = 0;
   }
   else
   {
   m_item.m_iCharEnd = str.length() - 1;
   }
   }
   }
   pline->m_tokenaMain[m_item.m_iLineEnd].GetText(str);
   if(m_item.m_iCharEnd >= str.length())
   {
   if(str.is_empty())
   {
   m_item.m_iCharEnd = 0;
   }
   else
   {
   m_item.m_iCharEnd = str.length() - 1;
   }
   }
   }*/

}

xfplayer_impact_line_selection & xfplayer_impact_line_selection::operator =(xfplayer_impact_line_selection & selection)
{
   m_estate = selection.m_estate;
   m_etype = selection.m_etype;
   return *this;
}


xfplayer_impact_line_selection_item::xfplayer_impact_line_selection_item()
{
   m_iLineStart = -1;
   m_iLineEnd = -1;
   m_iCharStart = -1;
   m_iCharEnd = -1;
}
xfplayer_impact_line_selection_item::xfplayer_impact_line_selection_item(
::collection::index      iLineStart,
::collection::index      iLineEnd,
character_count      iCharStart,
character_count      iCharEnd
)
{
   m_iLineStart = iLineStart;
   m_iLineEnd = iLineEnd;
   m_iCharStart = iCharStart;
   m_iCharEnd = iCharEnd;
}
xfplayer_impact_line_selection_item::~xfplayer_impact_line_selection_item()
{
}

xfplayer_impact_line_selection_item & xfplayer_impact_line_selection_item::operator =(const xfplayer_impact_line_selection_item & item)
{
   m_iLineStart   = item.m_iLineStart;
   m_iLineEnd      = item.m_iLineEnd;
   m_iCharStart   = item.m_iCharStart;
   m_iCharEnd      = item.m_iCharEnd;
   return *this;
}

void xfplayer_impact_line_selection::Select(
::collection::index      iLineStart,
::collection::index      iLineEnd,
character_count      iCharStart,
character_count      iCharEnd,
bool    bMerge)
{
   __UNREFERENCED_PARAMETER(bMerge);
   for(::collection::index i = 0; i < m_itema.get_size(); i++)
   {
      if(m_itema.element_at(i).Intersect(iLineStart, iLineEnd))
      {
         m_itema.element_at(i).SetLineStart(iLineStart);
         m_itema.element_at(i).SetLineEnd(iLineEnd);
         m_itema.element_at(i).SetCharStart(iCharStart);
         m_itema.element_at(i).SetCharEnd(iCharEnd);
         return;
      }
   }
   m_itema.erase_all();
   m_itema.add(
   xfplayer_impact_line_selection_item(
   iLineStart,
   iLineEnd,
   iCharStart,
   iCharEnd));
}


//bool xfplayer_impact_line_selection::OnLButtonDown(xfplayer_impact_line * pline, const ::user::keyboard_state & keyboardstate, const ::i32_point & point)
bool xfplayer_impact_line_selection::OnLButtonDown(xfplayer_impact_line *pline, const ::i32_point & point)
{
   
   //__UNREFERENCED_PARAMETER(keyboardstate);

   auto point1 = point;
   
   pline->get_interaction()->screen_to_client()(point1);

   bool bInside;

   ::collection::index iLine;
   character_count iChar;
   ::i32_rectangle rectanglePlacement;
   pline->GetPlacement(&rectanglePlacement);
   bInside = rectanglePlacement.contains(point1) != 0;
   if(!bInside && GetState() == e_state_tracking)
   {
      return false;
   }
   else if(bInside)
   {
      //             ::u32 fwKeys = user; // key flags
      if(pline->CalcChar(point1, iChar))
      {
         iLine = pline->m_iIndex;
         m_item.SetLineStart(iLine);
         m_item.SetCharStart(iChar);
         m_item.SetLineEnd(iLine);
         m_item.SetCharEnd(iChar);
         //                m_etype = TypeMaskStartHere;
         m_estate = e_state_tracking;
      }
      else
      {
         m_item.SetLineStart(-1);
         m_item.SetCharStart(-1);
         m_item.SetLineEnd(-1);
         m_item.SetCharEnd(-1);
      }
      //               pline->get_interaction()->set_need_redraw();
      OnSelEvent(pline, e_event_start);
      return true;
   }

   return false;
}


//bool xfplayer_impact_line_selection::OnMouseMove(xfplayer_impact_line * pline, const ::user::keyboard_state & keyboardstate, const ::i32_point & point)
bool xfplayer_impact_line_selection::OnMouseMove(xfplayer_impact_line * pline, const ::i32_point & point)
{
   
   if (!pline->IsVisible())
   {

      return false;

   }

   bool bInside;

   auto point1 = point;
   
   pline->get_interaction()->screen_to_client()(point1);

   ::collection::index iLine;

   character_count iChar;

   ::i32_rectangle rectanglePlacement;

   pline->GetPlacement(&rectanglePlacement);

   bInside = rectanglePlacement.contains(point1) != 0;

   if(!bInside && GetState() == e_state_tracking)
   {
      if(point1.y < rectanglePlacement.top
            ||
            (rectanglePlacement.contains_y(point1.y) &&
             point1.x < rectanglePlacement.left))
      {
         SetSelBefore(pline);
         //             pline->get_interaction()->set_need_redraw();
      }
      else
      {
         SetSelAfter(pline);
         //          pline->get_interaction()->set_need_redraw();
      }
      return false;
   }
   else if(bInside && GetState() == e_state_tracking)
   {
      //::u32 fwKeys = user; // key flags
      if(GetState() == e_state_tracking)
      {
         if(pline->m_iaPosition.get_size() <= 0)
            return false;
         if(pline->CalcChar(point1, iChar))
         {
            iLine = pline->m_iIndex;
            m_item.SetLineEnd(iLine);
            m_item.SetCharEnd(iChar);
            //m_item.NormalizeSel();
            //             m_etype |= TypeMaskEndHere;
            //               pline->get_interaction()->set_need_redraw();
         }
         else
         {
            if(point1.x < pline->m_iaPosition[0])
            {
               SetSelBefore(pline);
            }
            {
               SetSelAfter(pline);
            }
            //                pline->get_interaction()->set_need_redraw();

         }
         //OnSelEvent(pline, e_event_end);
         if(m_iLineStartSource == m_item.GetLineStart()
               && m_iLineEndSource == m_item.GetLineEnd()
               && m_iCharStartSource == m_item.GetCharStart()
               && m_iCharEndSource == m_item.GetCharEnd())
         {
            string str;
            if(pline->get_link(str, point) == ::user::e_line_hit_link)
            {
               //                   usersp(::user::impact) pimpact = pline->get_interaction();
               //                 pimpact->on_link_click(str);
            }
         }
         return true;
      }
   }

   return false;
}

//bool xfplayer_impact_line_selection::OnLButtonUp(xfplayer_impact_line * pline, const ::user::keyboard_state & keyboardstate, const ::i32_point & point)
bool xfplayer_impact_line_selection::OnLButtonUp(xfplayer_impact_line * pline, const ::i32_point & point)
{
//   __UNREFERENCED_PARAMETER(keyboardstate);
   if(!pline->IsVisible())
      return false;

   bool bInside;

   ::i32_point point1 = point;
   
   pline->get_interaction()->screen_to_client()(point1);

   ::collection::index iLine;
   character_count iChar;

   ::i32_rectangle rectanglePlacement;
   
   pline->GetPlacement(&rectanglePlacement);
   
   bInside = rectanglePlacement.contains(point1) != 0;
   
   if(!bInside && GetState() == e_state_tracking)
   {
      if(point1.y < rectanglePlacement.top
            ||
            (point1.y <= rectanglePlacement.bottom &&
             point1.x < rectanglePlacement.left))
      {
         SetSelBefore(pline);
         //             pline->get_interaction()->set_need_redraw();
      }
      else
      {
         SetSelAfter(pline);
         //          pline->get_interaction()->set_need_redraw();
      }
      return false;
   }
   else if(bInside)
   {
      //::u32 fwKeys = user; // key flags
      if(GetState() == e_state_tracking)
      {
         if(pline->m_iaPosition.get_size() <= 0)
            return false;
         if(pline->CalcChar(point1, iChar))
         {
            iLine = pline->m_iIndex;
            m_item.SetLineEnd(iLine);
            m_item.SetCharEnd(iChar);

            //             m_etype |= TypeMaskEndHere;
            //               pline->get_interaction()->set_need_redraw();
         }
         else
         {
            if(point1.x < pline->m_iaPosition[0])
            {
               SetSelBefore(pline);
            }
            {
               SetSelAfter(pline);
            }
            //                pline->get_interaction()->set_need_redraw();

         }
         OnSelEvent(pline, e_event_end);
         if(m_iLineStartSource == m_item.GetLineStart()
               && m_iLineEndSource == m_item.GetLineEnd()
               && m_iCharStartSource == m_item.GetCharStart()
               && m_iCharEndSource == m_item.GetCharEnd())
         {
            string str;
            if(pline->get_link(str, point) == ::user::e_line_hit_link)
            {
               //                   usersp(::user::impact) pimpact = pline->get_interaction();
               //                 pimpact->on_link_click(str);
            }
         }
         return true;
      }
   }
   if(GetState() == e_state_tracking)
      m_estate = e_state_initial;
   return false;
}

void xfplayer_impact_line_selection::operator()(::timer * ptimer)
{
    ::cast < xfplayer_impact_line > pline = ptimer->m_pcarrier1;
   //::u32 uEvent = user;
   if(ptimer->m_etimer == ::e_timer_hover_update)
   {
      if(pline->is_hover())
      {
         
         auto pointCursor = m_puserinteraction->mouse_cursor_position();

         pline->update_hover(pointCursor);

         if(!pline->is_hover())
         {
            
            ::i32_rectangle rectanglePlacement;
            
            pline->GetPlacement(&rectanglePlacement);
            
            pline->get_interaction()->set_need_redraw();
            
         }
         
      }
      
   }
   
   //return false;
   
}


void xfplayer_impact_line_selection_item::NormalizeSel()
{
   
   if(m_iLineStart > m_iLineEnd)
   {
      
      __swap(m_iLineEnd, m_iLineStart);
      
      __swap(m_iCharEnd, m_iCharStart);

   }
   else if(m_iLineStart == m_iLineEnd && m_iCharStart > m_iCharEnd)
   {

      __swap(m_iCharEnd, m_iCharStart);

   }

}


void xfplayer_impact_line_selection::GetNormalSelection(::collection::index & iLineStart, character_count & iCharStart, ::collection::index & iLineEnd, character_count & iCharEnd)
{

   if(m_item.GetLineStart() > m_item.GetLineEnd())
   {

      iLineStart = m_item.GetLineEnd();
      iCharStart = m_item.GetCharEnd();
      iLineEnd = m_item.GetLineStart();
      iCharEnd = m_item.GetCharStart();

   }
   else if(m_item.GetLineStart() == m_item.GetLineEnd())
   {

      iLineStart = m_item.GetLineStart();
      iLineEnd = m_item.GetLineEnd();
      if(m_item.GetCharStart() > m_item.GetCharEnd())
      {
         iCharStart = m_item.GetCharEnd();
         iCharEnd = m_item.GetCharStart();
      }
      else
      {
         iCharStart = m_item.GetCharStart();
         iCharEnd = m_item.GetCharEnd();
      }
   }
   else
   {
      iLineStart = m_item.GetLineStart();
      iCharStart = m_item.GetCharStart();
      iLineEnd = m_item.GetLineEnd();
      iCharEnd = m_item.GetCharEnd();
   }
}

::collection::index xfplayer_impact_line_selection_item::GetLineStart()
{
   return m_iLineStart;
}

::collection::index xfplayer_impact_line_selection_item::GetLineEnd()
{
   return m_iLineEnd;
}

character_count xfplayer_impact_line_selection_item::GetCharStart()
{
   return m_iCharStart;
}

character_count xfplayer_impact_line_selection_item::GetCharEnd()
{
   return m_iCharEnd;
}

void xfplayer_impact_line_selection_item::SetLineStart(::collection::index iLine)
{
   m_iLineStart = iLine;
}

void xfplayer_impact_line_selection_item::SetLineEnd(::collection::index iLine)
{
   m_iLineEnd = iLine;
}

void xfplayer_impact_line_selection_item::SetCharStart(character_count iChar)
{
   m_iCharStart = iChar;
}

void xfplayer_impact_line_selection_item::SetCharEnd(character_count iChar)
{
   m_iCharEnd = iChar;
}

bool xfplayer_impact_line_selection_item::Intersect(xfplayer_impact_line * pline)
{
   return Intersect(pline->m_iIndex, pline->m_iaPosition.get_upper_bound());
}



xfplayer_impact_line_selection::enum_state xfplayer_impact_line_selection::GetState()
{
   return m_estate;
}


bool xfplayer_impact_line_selection_item::Intersect(::collection::index iFirstLine, ::collection::index iLastLine)
{

   return maximum(iFirstLine, m_iLineStart) <= minimum(iLastLine, m_iLineEnd);

}

bool xfplayer_impact_line_selection::get_item(xfplayer_impact_line_selection_item &item, xfplayer_impact_line * pline)
{
   if(m_item.Intersect(pline))
   {
      item = m_item;
      item.NormalizeSel();
      return true;
   }
   for(::collection::index iItem = 0; iItem < m_itema.get_size(); iItem++)
   {
      xfplayer_impact_line_selection_item & itemTest = m_itema.element_at(iItem);
      if(itemTest.Intersect(pline))
      {
         item = itemTest;
         item.NormalizeSel();
         return true;
      }

   }
   return false;
}
