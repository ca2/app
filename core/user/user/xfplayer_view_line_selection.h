#pragma once

class xfplayer_view_line;

class CLASS_DECL_CORE XfplayerViewLineSelectionItem  
{
protected:

   index               m_iLineStart;
   index               m_iLineEnd;
   strsize               m_iCharStart;
   strsize               m_iCharEnd;


      // Construction / Destruction
public:
   XfplayerViewLineSelectionItem();
   XfplayerViewLineSelectionItem(
      index      iLineStart,
      index      iLineEnd,
      strsize      iCharStart,
      strsize      iCharEnd
      );
   virtual ~XfplayerViewLineSelectionItem();

   XfplayerViewLineSelectionItem & operator =(const XfplayerViewLineSelectionItem & item);

   void NormalizeSel();
   bool Intersect(xfplayer_view_line & viewline);
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


class CLASS_DECL_CORE XfplayerViewLineSelection :
   virtual object
{
public:
   enum enum_state
   {
      state_initial = 1,
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

   array < XfplayerViewLineSelectionItem, XfplayerViewLineSelectionItem> m_itema;

   XfplayerViewLineSelectionItem m_item;
      

   index               m_iLineStartSource;
   index               m_iLineEndSource;
   strsize               m_iCharStartSource;
   strsize               m_iCharEndSource;

   i32               m_etype; 
   enum_state            m_estate;

   XfplayerViewLineSelection();
   virtual ~XfplayerViewLineSelection();

   bool get_item(XfplayerViewLineSelectionItem & item, xfplayer_view_line & viewline);
   enum_state GetState();

   virtual void relay_event(xfplayer_view_line & viewline, ::message::message * pmessage);
   virtual void OnSelEvent(xfplayer_view_line & viewline, enum_event eselevent);
   bool SetSelBefore(xfplayer_view_line & viewline);
   bool SetSelAfter(xfplayer_view_line & viewline);
   void NormalizeSel(xfplayer_view_line & viewline);
   void GetNormalSelection(index & iLineStart, strsize & iCharStart, index & iLineEnd, strsize & iCharEnd);

   void Select(
      index      iLineStart,
      index      iLineEnd,
      strsize      iCharStart,
      strsize      iCharEnd,
      bool   bMerge);



   XfplayerViewLineSelection & operator =(XfplayerViewLineSelection & selection);

   bool OnMouseMove(xfplayer_view_line & viewline, ::u32 user, const ::point & point);
   bool OnLButtonDown(xfplayer_view_line & viewline, ::u32 user, const ::point & point);
   bool OnLButtonUp(xfplayer_view_line & viewline, ::u32 user, const ::point & point);
   bool OnTimer(xfplayer_view_line & viewline, ::u32 user);

};

