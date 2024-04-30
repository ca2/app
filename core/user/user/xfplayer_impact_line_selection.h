#pragma once


class xfplayer_impact_line;


//#include "acme/primitive/geometry2d/_geometry2d.h"


class CLASS_DECL_CORE xfplayer_impact_line_selection_item
{
protected:

   
   ::raw::index                m_iLineStart;
   ::raw::index                m_iLineEnd;
   strsize              m_iCharStart;
   strsize              m_iCharEnd;


public:


   xfplayer_impact_line_selection_item();
   xfplayer_impact_line_selection_item(
      ::raw::index      iLineStart,
      ::raw::index      iLineEnd,
      strsize      iCharStart,
      strsize      iCharEnd
      );
   ~xfplayer_impact_line_selection_item();

   xfplayer_impact_line_selection_item & operator =(const xfplayer_impact_line_selection_item & item);

   void NormalizeSel();
   bool Intersect(xfplayer_impact_line & viewline);
   bool Intersect(::raw::index iLineStart, ::raw::index iLineEnd);

   ::raw::index GetLineStart();
   ::raw::index GetLineEnd();
   ::raw::index GetCharStart();
   ::raw::index GetCharEnd();
   void SetLineStart(::raw::index iLine);
   void SetLineEnd(::raw::index iLine);
   void SetCharStart(strsize iChar);
   void SetCharEnd(::raw::index iChar);


};


class CLASS_DECL_CORE xfplayer_impact_line_selection :
   virtual public ::particle
{
public:


   enum enum_state
   {
      
      e_state_initial = 1,
      e_state_tracking = 2

   };
      

   enum enum_event
   {

      e_event_start = 1,
      e_event_end = 2

   };

      
   ::user::interaction *                                                                  m_puserinteraction;

   array < xfplayer_impact_line_selection_item, xfplayer_impact_line_selection_item >     m_itema;

   xfplayer_impact_line_selection_item                                                    m_item;
      

   ::raw::index                   m_iLineStartSource;
   ::raw::index                   m_iLineEndSource;
   strsize                 m_iCharStartSource;
   strsize                 m_iCharEndSource;

   i32                     m_etype; 
   enum_state              m_estate;

   
   xfplayer_impact_line_selection(::user::interaction * puserinteraction);
   ~xfplayer_impact_line_selection() override;


   bool get_item(xfplayer_impact_line_selection_item & item, xfplayer_impact_line & viewline);
   enum_state GetState();

   virtual void relay_event(xfplayer_impact_line & viewline, ::message::message * pmessage);
   virtual void OnSelEvent(xfplayer_impact_line & viewline, enum_event eselevent);
   bool SetSelBefore(xfplayer_impact_line & viewline);
   bool SetSelAfter(xfplayer_impact_line & viewline);
   void NormalizeSel(xfplayer_impact_line & viewline);
   void GetNormalSelection(::raw::index & iLineStart, strsize & iCharStart, ::raw::index & iLineEnd, strsize & iCharEnd);

   void Select(
      ::raw::index      iLineStart,
      ::raw::index      iLineEnd,
      strsize      iCharStart,
      strsize      iCharEnd,
      bool   bMerge);


   xfplayer_impact_line_selection & operator =(xfplayer_impact_line_selection & selection);


   bool OnMouseMove(xfplayer_impact_line & viewline, ::user::e_button_state ebuttonstate, const ::point_i32 & point);
   bool OnLButtonDown(xfplayer_impact_line & viewline, ::user::e_button_state ebuttonstate, const ::point_i32 & point);
   bool OnLButtonUp(xfplayer_impact_line & viewline, ::user::e_button_state ebuttonstate, const ::point_i32 & point);
   bool OnTimer(xfplayer_impact_line & viewline, ::u32 user);


};



