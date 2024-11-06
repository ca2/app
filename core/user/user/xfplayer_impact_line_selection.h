#pragma once


class xfplayer_impact_line;


//#include "acme/prototype/geometry2d/_geometry2d.h"


class CLASS_DECL_CORE xfplayer_impact_line_selection_item
{
protected:

   
   ::collection::index                m_iLineStart;
   ::collection::index                m_iLineEnd;
   character_count              m_iCharStart;
   character_count              m_iCharEnd;


public:


   xfplayer_impact_line_selection_item();
   xfplayer_impact_line_selection_item(
      ::collection::index      iLineStart,
      ::collection::index      iLineEnd,
      character_count      iCharStart,
      character_count      iCharEnd
      );
   ~xfplayer_impact_line_selection_item();

   xfplayer_impact_line_selection_item & operator =(const xfplayer_impact_line_selection_item & item);

   void NormalizeSel();
   bool Intersect(xfplayer_impact_line & viewline);
   bool Intersect(::collection::index iLineStart, ::collection::index iLineEnd);

   ::collection::index GetLineStart();
   ::collection::index GetLineEnd();
   ::collection::index GetCharStart();
   ::collection::index GetCharEnd();
   void SetLineStart(::collection::index iLine);
   void SetLineEnd(::collection::index iLine);
   void SetCharStart(character_count iChar);
   void SetCharEnd(::collection::index iChar);


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
      

   ::collection::index                   m_iLineStartSource;
   ::collection::index                   m_iLineEndSource;
   character_count                 m_iCharStartSource;
   character_count                 m_iCharEndSource;

   int                     m_etype; 
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
   void GetNormalSelection(::collection::index & iLineStart, character_count & iCharStart, ::collection::index & iLineEnd, character_count & iCharEnd);

   void Select(
      ::collection::index      iLineStart,
      ::collection::index      iLineEnd,
      character_count      iCharStart,
      character_count      iCharEnd,
      bool   bMerge);


   xfplayer_impact_line_selection & operator =(xfplayer_impact_line_selection & selection);


   bool OnMouseMove(xfplayer_impact_line & viewline, ::user::e_button_state ebuttonstate, const ::int_point & point);
   bool OnLButtonDown(xfplayer_impact_line & viewline, ::user::e_button_state ebuttonstate, const ::int_point & point);
   bool OnLButtonUp(xfplayer_impact_line & viewline, ::user::e_button_state ebuttonstate, const ::int_point & point);
   bool OnTimer(xfplayer_impact_line & viewline, unsigned int user);


};



