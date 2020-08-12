#pragma once

class ::user::control_bar;
class ::user::frame_window;

class BaseDockContext
{
public:
// Construction
   BaseDockContext(::user::control_bar* pBar);

// Attributes
   point m_pointLast;            // last mouse position during drag
   ::rect m_rectLast;
   ::size m_sizeLast;
   bool m_bDitherLast;

   // Rectangles used during dragging or resizing
   ::rect m_rectDragHorz;
   ::rect m_rectDragVert;
   ::rect m_rectFrameDragHorz;
   ::rect m_rectFrameDragVert;

   ::user::control_bar* m_pBar;        // the toolbar that created this action_context
   __pointer(::user::frame_window) m_pDockSite;     // the controlling frame of the ::user::control_bar
   u32 m_dwDockStyle;        // allowable dock styles for bar
   u32 m_dwOverDockStyle;    // style of dock that rect is over
   u32 m_dwStyle;            // style of control bar
   bool m_bFlip;               // if shift key is down
   bool m_bForceFrame;         // if ctrl key is down

   ::draw2d::graphics * m_pDC;                 // where to draw during drag
   bool m_bDragging;
   i32 m_nHitTest;
   bool m_bTracking;

   UINT m_uMRUDockID;
   ::rect m_rectMRUDockPos;

   u32 m_dwMRUFloatStyle;
   point m_pointMRUFloatPos;

// Drag Operations
   virtual void StartDrag(const ::point & point);
   void Move(const ::point & point);       // called when mouse has moved
   void EndDrag();             // drop
   void OnKey(i32 nChar, bool bDown);

// Resize Operations
   virtual void StartResize(i32 nHitTest, const ::point & point);
   void Stretch(const ::point & point);
   void EndResize();

// Double Click Operations
   virtual void ToggleDocking();

// Operations
   void InitLoop();
   void CancelLoop();

// Implementation
public:
   ~BaseDockContext();
   bool Track();
   void DrawFocusRect(bool bRemoveRect = FALSE);
      // draws the correct outline
   void UpdateState(bool* pFlag, bool bNewValue);
   u32 CanDock();
   BaseDockBar* GetDockBar(u32 dwOverDockStyle);


   void OnBarMouseMove(UINT uiFlags, const ::point & point);
   void OnBarLButtonUp(UINT uiFlags, const ::point & point);
   void DragMoveFeedback();
};

