#include "framework.h"
#include "xfplayer_impact_line_selection.h"
#include "xfplayer_impact_line.h"
#include "acme/constant/message.h"
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


void xfplayer_impact_line_selection::relay_event(xfplayer_impact_line & viewline, ::message::message * pmessage)
{
   ::pointer<::user::message>pusermessage(pmessage);

   auto emessage = pusermessage->m_atom.as_emessage();

   if(emessage != e_message_mouse_move
         && emessage != e_message_timer
         && emessage != e_message_left_button_down
         && emessage != e_message_left_button_up)
   {
      return;
   }

   index iLine;

   strsize iChar;

   if((emessage == e_message_mouse_move && GetState() == e_state_tracking)
         || emessage == e_message_left_button_down
         || emessage == e_message_left_button_up)
   {
      
      bool bInside;
      
      auto pointCursor = pusermessage->m_lparam.point();

      ::rectangle_i32 rectanglePlacement;
      
      viewline.GetPlacement(&rectanglePlacement);
      
      bInside = rectanglePlacement.contains(pointCursor) != 0;
      
      if(!bInside && GetState() == e_state_tracking)
      {
         if(emessage == e_message_left_button_up
               || emessage == e_message_mouse_move)
         {
            if(pointCursor.y() < rectanglePlacement.top
                  ||
                  (pointCursor.y() <= rectanglePlacement.bottom &&
                   pointCursor.x() < rectanglePlacement.left))
            {
               SetSelBefore(viewline);
               //                   viewline.get_interaction()->set_need_redraw();
            }
            else
            {
               SetSelAfter(viewline);
               //                viewline.get_interaction()->set_need_redraw();
            }
            if(emessage == e_message_left_button_up)
            {
               OnSelEvent(viewline, e_event_end);
            }
         }
         return;
      }
      else if(bInside)
      {
         //u32 fwKeys = pusermessage->m_wparam; // key flags
         if(emessage == e_message_left_button_down)
         {
            if(viewline.CalcChar(pointCursor, iChar))
            {
               iLine = viewline.m_iIndex;
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
            //                viewline.get_interaction()->set_need_redraw();
            OnSelEvent(viewline, e_event_start);
            pusermessage->m_bRet = true;
            return;
         }
         else if(
         (emessage == e_message_left_button_up
          || emessage == e_message_mouse_move)
         && GetState() == e_state_tracking)
         {
            if(viewline.CalcChar(pointCursor, iChar))
            {
               iLine = viewline.m_iIndex;
               m_item.SetLineEnd(iLine);
               m_item.SetCharEnd(iChar);
               //                m_item.NormalizeSel();
               //                m_etype |= TypeMaskEndHere;
               //viewline.get_interaction()->set_need_redraw();
            }
            else
            {
               if(pointCursor.x() < viewline.m_iaPosition[0])
               {
                  SetSelBefore(viewline);
               }
               {
                  SetSelAfter(viewline);
               }
               //viewline.get_interaction()->set_need_redraw();

            }
            if(emessage == e_message_left_button_up)
            {
               OnSelEvent(viewline, e_event_end);
               if(m_iLineStartSource == m_item.GetLineStart()
                     && m_iLineEndSource == m_item.GetLineEnd()
                     && m_iCharStartSource == m_item.GetCharStart()
                     && m_iCharEndSource == m_item.GetCharEnd())
               {

                  string str;

                  auto pwindow = m_puserinteraction->window();

                  auto pointCursor = pwindow->get_cursor_position();

                  if(viewline.get_link(str, pointCursor))
                  {
                     //usersp(::user::impact) pimpact = viewline.get_interaction();
                     //pimpact->on_link_click(str);
                  }
               }
            }
            pusermessage->m_bRet = true;
            return;
         }
         else if(emessage == e_message_mouse_move)
         {

            auto pwindow = m_puserinteraction->window();

            auto pointCursor = pwindow->get_cursor_position();

            viewline.update_hover(pointCursor);

         }

      }

   }
   else if(emessage == e_message_timer)
   {

      uptr uEvent = pusermessage->m_wparam;

      if(uEvent == ::e_timer_hover)
      {

         auto pwindow = m_puserinteraction->window();

         auto pointCursor = pwindow->get_cursor_position();

         viewline.update_hover(pointCursor);

         if(!viewline.is_hover())
         {
            ::pointer<::user::interaction>puserinteraction = viewline.get_interaction();
            puserinteraction->KillTimer(::e_timer_hover);
         }
      }
   }
}

void xfplayer_impact_line_selection::OnSelEvent(xfplayer_impact_line & viewline, xfplayer_impact_line_selection::enum_event eevent)
{
   __UNREFERENCED_PARAMETER(viewline);
   switch(eevent)
   {
   case e_event_start:
      m_iLineStartSource  = m_item.GetLineStart();
      m_iLineEndSource      = m_item.GetLineEnd();
      m_iCharStartSource   = m_item.GetCharStart();
      m_iCharEndSource      = m_item.GetCharEnd();
      m_estate               = e_state_tracking;

      //         viewline.GetTemplate()->OnSelStart(&viewline);
      break;
   case e_event_end:
      //NormalizeSel(viewline);
      //         m_item.NormalizeSel();
      Select(
      m_item.GetLineStart(),
      m_item.GetLineEnd(),
      m_item.GetCharStart(),
      m_item.GetCharEnd(), false);
      m_estate = e_state_initial;
      //      viewline.GetTemplate()->OnSelEnd(&viewline);

      break;
   default:
      ASSERT(false);
   }
}

bool xfplayer_impact_line_selection::SetSelBefore(xfplayer_impact_line & viewline)
{
   /*   if(m_etype & TypeMaskEndHere)
   {
   if(m_etype & TypeMaskStartHere)
   {
   m_etype &= ~TypeMaskStartHere;*/
   m_item.SetLineStart(viewline.m_iIndex);
   m_item.SetCharStart(0);
   /*      }
   }
   else if(m_etype &  TypeMaskStartHere)
   {
   m_etype &= ~TypeMaskStartHere;
   m_etype |= TypeMaskEndHere;
   m_item.SetLineStart(viewline.GetFirstLine());
   m_item.SetCharStart(0);
   }
   else
   {
   string str;
   viewline.m_tokenaMain.element_at(viewline.GetLineCount() - 1).GetText(str);
   m_item.SetLineStart(viewline.GetFirstLine());
   m_item.SetCharStart(0);
   m_item.SetLineEnd(viewline.GetFirstLine() + viewline.GetLineCount() - 1);
   m_item.SetCharEnd(viewline.m_tokenaMain.last().GetCharCount() - 1);
   }*/
   return true;
}

bool xfplayer_impact_line_selection::SetSelAfter(xfplayer_impact_line & viewline)
{
   if(viewline.m_iaPosition.get_count() > 0)
   {
      m_item.SetLineEnd(viewline.m_iIndex);
      m_item.SetCharEnd(viewline.m_iaPosition.get_upper_bound());
   }

   /*   if(m_etype & TypeMaskEndHere)
   {
   if(m_etype & TypeMaskStartHere)
   {*/
   /*         string str;
   viewline.m_tokenaMain.element_at(viewline.GetLineCount() - 1).GetText(str);
   //         m_etype &= ~TypeMaskEndHere;
   m_item.SetLineEnd(viewline.GetFirstLine() + viewline.m_tokenaMain.get_size() - 1);
   m_item.SetCharEnd(str.length());*/
   /*      }
   else
   {
   string str;
   viewline.m_tokenaMain.element_at(viewline.GetLineCount() - 1).GetText(str);
   m_etype &= ~TypeMaskEndHere;
   m_etype |= TypeMaskStartHere;
   m_item.SetLineEnd(viewline.GetFirstLine() + viewline.m_tokenaMain.get_size() - 1);
   m_item.SetCharEnd(str.length() - 1);
   }
   }
   else if(m_etype &  TypeMaskStartHere)
   {
   }
   else
   {
   string str;
   viewline.m_tokenaMain.element_at(viewline.GetLineCount() - 1).GetText(str);
   m_item.SetLineStart(viewline.GetFirstLine());
   m_item.SetCharStart(0);
   m_item.SetLineEnd(viewline.GetFirstLine() + viewline.m_tokenaMain.get_size() - 1);
   m_item.SetCharEnd(str.length() - 1);
   }*/
   return true;
}

void xfplayer_impact_line_selection::NormalizeSel(xfplayer_impact_line & viewline)
{
   __UNREFERENCED_PARAMETER(viewline);
   ASSERT(false);
   /*   string str;
   if(m_item.m_iLineStart < 0)
   {
   }
   else if(m_item.m_iLineStart >= viewline.m_tokenaMain.get_size())
   {
   m_item.m_iLineStart = viewline.m_tokenaMain.get_size() - 1;
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
   viewline.m_tokenaMain[m_item.m_iLineStart].GetText(str);
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

   if(m_item.m_iLineEnd >= viewline.m_tokenaMain.get_size())
   {
   m_item.m_iLineEnd = viewline.m_tokenaMain.get_size() - 1;
   if(m_item.m_iLineEnd < 0)
   {
   m_item.m_iCharEnd = -1;
   }
   else
   {
   viewline.m_tokenaMain[m_item.m_iLineEnd].GetText(str);
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
   viewline.m_tokenaMain[m_item.m_iLineEnd].GetText(str);
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
index      iLineStart,
index      iLineEnd,
strsize      iCharStart,
strsize      iCharEnd
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
index      iLineStart,
index      iLineEnd,
strsize      iCharStart,
strsize      iCharEnd,
bool    bMerge)
{
   __UNREFERENCED_PARAMETER(bMerge);
   for(index i = 0; i < m_itema.get_size(); i++)
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


bool xfplayer_impact_line_selection::OnLButtonDown(xfplayer_impact_line & viewline, ::user::e_button_state ebuttonstate, const ::point_i32 & point)
{
   
   __UNREFERENCED_PARAMETER(ebuttonstate);

   auto point1 = point;
   
   viewline.get_interaction()->screen_to_client()(point1);

   bool bInside;

   index iLine;
   strsize iChar;
   ::rectangle_i32 rectanglePlacement;
   viewline.GetPlacement(&rectanglePlacement);
   bInside = rectanglePlacement.contains(point1) != 0;
   if(!bInside && GetState() == e_state_tracking)
   {
      return false;
   }
   else if(bInside)
   {
      //             u32 fwKeys = user; // key flags
      if(viewline.CalcChar(point1, iChar))
      {
         iLine = viewline.m_iIndex;
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
      //               viewline.get_interaction()->set_need_redraw();
      OnSelEvent(viewline, e_event_start);
      return true;
   }

   return false;
}


bool xfplayer_impact_line_selection::OnMouseMove(xfplayer_impact_line & viewline, ::user::e_button_state ebuttonstate, const ::point_i32 & point)
{
   
   if (!viewline.IsVisible())
   {

      return false;

   }

   bool bInside;

   auto point1 = point;
   
   viewline.get_interaction()->screen_to_client()(point1);

   index iLine;

   strsize iChar;

   ::rectangle_i32 rectanglePlacement;

   viewline.GetPlacement(&rectanglePlacement);

   bInside = rectanglePlacement.contains(point1) != 0;

   if(!bInside && GetState() == e_state_tracking)
   {
      if(point1.y() < rectanglePlacement.top
            ||
            (rectanglePlacement.contains_y(point1.y()) &&
             point1.x() < rectanglePlacement.left))
      {
         SetSelBefore(viewline);
         //             viewline.get_interaction()->set_need_redraw();
      }
      else
      {
         SetSelAfter(viewline);
         //          viewline.get_interaction()->set_need_redraw();
      }
      return false;
   }
   else if(bInside && GetState() == e_state_tracking)
   {
      //u32 fwKeys = user; // key flags
      if(GetState() == e_state_tracking)
      {
         if(viewline.m_iaPosition.get_size() <= 0)
            return false;
         if(viewline.CalcChar(point1, iChar))
         {
            iLine = viewline.m_iIndex;
            m_item.SetLineEnd(iLine);
            m_item.SetCharEnd(iChar);
            //m_item.NormalizeSel();
            //             m_etype |= TypeMaskEndHere;
            //               viewline.get_interaction()->set_need_redraw();
         }
         else
         {
            if(point1.x() < viewline.m_iaPosition[0])
            {
               SetSelBefore(viewline);
            }
            {
               SetSelAfter(viewline);
            }
            //                viewline.get_interaction()->set_need_redraw();

         }
         //OnSelEvent(viewline, e_event_end);
         if(m_iLineStartSource == m_item.GetLineStart()
               && m_iLineEndSource == m_item.GetLineEnd()
               && m_iCharStartSource == m_item.GetCharStart()
               && m_iCharEndSource == m_item.GetCharEnd())
         {
            string str;
            if(viewline.get_link(str, point) == ::user::e_line_hit_link)
            {
               //                   usersp(::user::impact) pimpact = viewline.get_interaction();
               //                 pimpact->on_link_click(str);
            }
         }
         return true;
      }
   }

   return false;
}

bool xfplayer_impact_line_selection::OnLButtonUp(xfplayer_impact_line & viewline, ::user::e_button_state ebuttonstate, const ::point_i32 & point)
{
   __UNREFERENCED_PARAMETER(ebuttonstate);
   if(!viewline.IsVisible())
      return false;

   bool bInside;

   ::point_i32 point1 = point;
   
   viewline.get_interaction()->screen_to_client()(point1);

   index iLine;
   strsize iChar;

   ::rectangle_i32 rectanglePlacement;
   
   viewline.GetPlacement(&rectanglePlacement);
   
   bInside = rectanglePlacement.contains(point1) != 0;
   
   if(!bInside && GetState() == e_state_tracking)
   {
      if(point1.y() < rectanglePlacement.top
            ||
            (point1.y() <= rectanglePlacement.bottom &&
             point1.x() < rectanglePlacement.left))
      {
         SetSelBefore(viewline);
         //             viewline.get_interaction()->set_need_redraw();
      }
      else
      {
         SetSelAfter(viewline);
         //          viewline.get_interaction()->set_need_redraw();
      }
      return false;
   }
   else if(bInside)
   {
      //u32 fwKeys = user; // key flags
      if(GetState() == e_state_tracking)
      {
         if(viewline.m_iaPosition.get_size() <= 0)
            return false;
         if(viewline.CalcChar(point1, iChar))
         {
            iLine = viewline.m_iIndex;
            m_item.SetLineEnd(iLine);
            m_item.SetCharEnd(iChar);

            //             m_etype |= TypeMaskEndHere;
            //               viewline.get_interaction()->set_need_redraw();
         }
         else
         {
            if(point1.x() < viewline.m_iaPosition[0])
            {
               SetSelBefore(viewline);
            }
            {
               SetSelAfter(viewline);
            }
            //                viewline.get_interaction()->set_need_redraw();

         }
         OnSelEvent(viewline, e_event_end);
         if(m_iLineStartSource == m_item.GetLineStart()
               && m_iLineEndSource == m_item.GetLineEnd()
               && m_iCharStartSource == m_item.GetCharStart()
               && m_iCharEndSource == m_item.GetCharEnd())
         {
            string str;
            if(viewline.get_link(str, point) == ::user::e_line_hit_link)
            {
               //                   usersp(::user::impact) pimpact = viewline.get_interaction();
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

bool xfplayer_impact_line_selection::OnTimer(xfplayer_impact_line & viewline, ::u32 user)
{
   ::u32 uEvent = user;
   if(uEvent == ::e_timer_hover)
   {
      if(viewline.is_hover())
      {
         
         auto pwindow = m_puserinteraction->window();

         auto pointCursor = pwindow->get_cursor_position();

         viewline.get_interaction()->screen_to_client()(pointCursor);

         viewline.update_hover(pointCursor);

         if(!viewline.is_hover())
         {
            
            ::rectangle_i32 rectanglePlacement;
            
            viewline.GetPlacement(&rectanglePlacement);
            
            viewline.get_interaction()->set_need_redraw();
            
         }
         
      }
      
   }
   
   return false;
   
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


void xfplayer_impact_line_selection::GetNormalSelection(index & iLineStart, strsize & iCharStart, index & iLineEnd, strsize & iCharEnd)
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

index xfplayer_impact_line_selection_item::GetLineStart()
{
   return m_iLineStart;
}

index xfplayer_impact_line_selection_item::GetLineEnd()
{
   return m_iLineEnd;
}

strsize xfplayer_impact_line_selection_item::GetCharStart()
{
   return m_iCharStart;
}

strsize xfplayer_impact_line_selection_item::GetCharEnd()
{
   return m_iCharEnd;
}

void xfplayer_impact_line_selection_item::SetLineStart(index iLine)
{
   m_iLineStart = iLine;
}

void xfplayer_impact_line_selection_item::SetLineEnd(index iLine)
{
   m_iLineEnd = iLine;
}

void xfplayer_impact_line_selection_item::SetCharStart(strsize iChar)
{
   m_iCharStart = iChar;
}

void xfplayer_impact_line_selection_item::SetCharEnd(strsize iChar)
{
   m_iCharEnd = iChar;
}

bool xfplayer_impact_line_selection_item::Intersect(xfplayer_impact_line &viewline)
{
   return Intersect(viewline.m_iIndex, viewline.m_iaPosition.get_upper_bound());
}



xfplayer_impact_line_selection::enum_state xfplayer_impact_line_selection::GetState()
{
   return m_estate;
}


bool xfplayer_impact_line_selection_item::Intersect(index iFirstLine, index iLastLine)
{

   return maximum(iFirstLine, m_iLineStart) <= minimum(iLastLine, m_iLineEnd);

}

bool xfplayer_impact_line_selection::get_item(xfplayer_impact_line_selection_item &item, xfplayer_impact_line &viewline)
{
   if(m_item.Intersect(viewline))
   {
      item = m_item;
      item.NormalizeSel();
      return true;
   }
   for(index iItem = 0; iItem < m_itema.get_size(); iItem++)
   {
      xfplayer_impact_line_selection_item & itemTest = m_itema.element_at(iItem);
      if(itemTest.Intersect(viewline))
      {
         item = itemTest;
         item.NormalizeSel();
         return true;
      }

   }
   return false;
}
