#pragma once

class xfplayer_impact_line;

class CLASS_DECL_CORE XfplayerImpactLineSelectionItem  
{
protected:

   index               m_iLineStart;
   index               m_iLineEnd;
   strsize               m_iCharStart;
   strsize               m_iCharEnd;


      // Construction / Destruction
public:
   XfplayerImpactLineSelectionItem();
   XfplayerImpactLineSelectionItem(
      index      iLineStart,
      index      iLineEnd,
      strsize      iCharStart,
      strsize      iCharEnd
      );
   virtual ~XfplayerImpactLineSelectionItem();

   XfplayerImpactLineSelectionItem & operator =(const XfplayerImpactLineSelectionItem & item);

   void NormalizeSel();
   bool Intersect(xfplayer_impact_line & viewline);
   bool Intersect(index iLineStart, index iLineEnd);

   index GetLineStart();
   index GetLineEnd();
   index GetCharStart();
   index GetCharEnd();
   void SetLineStart(index iLine);
   void SetLineEnd(index iLine);
   void SetCharStart(strsize iChar);
   void SetCharEnd(index iChar);


};


class CLASS_DECL_CORE XfplayerImpactLineSelection :
   virtual public element
{
public:


   enum enum_state
   {
      e_state_initial = 1,
      StateTracking = 2
   };
      
   enum enum_event
   {
      EventStart = 1,
      EventEnd = 2
   };
      
   enum ETypeMask
   {
//      TypeMaskStartHere = 1,
//      TypeMaskEndHere = 2,
   };

   ::user::interaction * m_puserinteraction;

   array < XfplayerImpactLineSelectionItem, XfplayerImpactLineSelectionItem> m_itema;

   XfplayerImpactLineSelectionItem m_item;
      

   index               m_iLineStartSource;
   index               m_iLineEndSource;
   strsize               m_iCharStartSource;
   strsize               m_iCharEndSource;

   i32               m_etype; 
   enum_state            m_estate;

   
   XfplayerImpactLineSelection(::user::interaction * puserinteraction);
   ~XfplayerImpactLineSelection() override;


   bool get_item(XfplayerImpactLineSelectionItem & item, xfplayer_impact_line & viewline);
   enum_state GetState();

   virtual void relay_event(xfplayer_impact_line & viewline, ::message::message * pmessage);
   virtual void OnSelEvent(xfplayer_impact_line & viewline, enum_event eselevent);
   bool SetSelBefore(xfplayer_impact_line & viewline);
   bool SetSelAfter(xfplayer_impact_line & viewline);
   void NormalizeSel(xfplayer_impact_line & viewline);
   void GetNormalSelection(index & iLineStart, strsize & iCharStart, index & iLineEnd, strsize & iCharEnd);

   void Select(
      index      iLineStart,
      index      iLineEnd,
      strsize      iCharStart,
      strsize      iCharEnd,
      bool   bMerge);



   XfplayerImpactLineSelection & operator =(XfplayerImpactLineSelection & selection);

   bool OnMouseMove(xfplayer_impact_line & viewline, ::u32 user, const ::point_i32 & point);
   bool OnLButtonDown(xfplayer_impact_line & viewline, ::u32 user, const ::point_i32 & point);
   bool OnLButtonUp(xfplayer_impact_line & viewline, ::u32 user, const ::point_i32 & point);
   bool OnTimer(xfplayer_impact_line & viewline, ::u32 user);

};

