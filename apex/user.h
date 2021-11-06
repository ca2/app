#pragma once



namespace graphics
{

   
   class graphics;


} // namespace graphics



//#define e_message_size_parent       0x0361  // lParam = &__SIZEPARENTPARAMS



/////////////////////////////////////////////////////////////////////////////
// Internal _ Windows messages (see Technical note TN024 for more details)
// (0x0360 - 0x037F are reserved for apex API)

#define WM_SETMESSAGESTRING 0x0362  // wParam = nIDS (or 0),
// lParam = pszOther (or nullptr)

#define WM_IDLEUPDATECMDUI  0x0363  // wParam == bDisableIfNoHandler
#define WM_COMMANDHELP      0x0365  // lResult = true/false,
// lParam = dwContext
#define WM_HELPHITTEST      0x0366  // lResult = dwContext,
// lParam = __MAKE_LONG(x,y)
#define WM_EXITHELPMODE     0x0367  // (params unused)
#define WM_RECALCPARENT     0x0368  // force on_layout on frame interaction_impl
//  (only for inplace frame windows)
#define WM_SIZECHILD        0x0369  // special notify from COleResizeBar
// wParam = ID of child interaction_impl
// lParam = pRectNew (new position/size_i32)

#define WM_KICKIDLE         0x036A  // (params unused) causes idles to kick in
#define WM_QUERYCENTERWND   0x036B  // lParam = oswindow to use as centering parent
#define WM_DISABLEMODAL     0x036C  // lResult = 0, disable during modal state
// lResult = 1, don't disable
#define WM_FLOATSTATUS      0x036D  // wParam combination of FS_* flags below

// WM_ACTIVATETOPLEVEL is like WM_ACTIVATEAPP but works with hierarchies
//   of mixed processes (as is the case with OLE in-place activation)
#define WM_ACTIVATETOPLEVEL 0x036E  // wParam = nState (like e_message_activate)
// lParam = pointer to oswindow[2]
//  lParam[0] = oswindow getting e_message_activate
//  lParam[1] = oswindow_Other

#define WM_RESERVED_036F   0x036F  // was WM_QUERY3DCONTROLS (now not used)

// Note: Messages 0x0370, 0x0371, and 0x372 were incorrectly used by
//  some versions of Windows.  To remain compatible, apex API does not
//  use messages in that range.
#define WM_RESERVED_0370    0x0370
#define WM_RESERVED_0371    0x0371
#define WM_RESERVED_0372    0x0372

// WM_SOCKET_NOTIFY and WM_SOCKET_DEAD are used internally by apex API's
// Windows sockets implementation.  For more information, see sockcore.cpp
#define WM_SOCKET_NOTIFY    0x0373
#define WM_SOCKET_DEAD      0x0374

// same as WM_SETMESSAGESTRING except not popped if IsTracking()
#define WM_POPMESSAGESTRING 0x0375

// WM_HELPPROMPTADDR is used internally to get the address of
//   m_dwPromptContext from the associated frame interaction_impl. This is used
//   during message boxes to setup for F1 help while that msg box is
//   displayed. lResult is the address of m_dwPromptContext.
#define WM_HELPPROMPTADDR   0x0376

// Constants used in DLGINIT resources for OLE control containers
// NOTE: These are NOT real Windows messages they are simply tags
// used in the control resource and are never used as 'messages'
#define WM_OCC_LOADFROMSTREAM           0x0376
#define WM_OCC_LOADFROMSTORAGE          0x0377
#define WM_OCC_INITNEW                  0x0378
#define WM_OCC_LOADFROMSTREAM_EX        0x037A
#define WM_OCC_LOADFROMSTORAGE_EX       0x037B

// Marker used while rearranging the message queue
#define WM_QUEUE_SENTINEL   0x0379

// Note: Messages 0x037C - 0x37E reserved for future apex API use.
#define WM_RESERVED_037C    0x037C
#define WM_RESERVED_037D    0x037D
#define WM_RESERVED_037E    0x037E

// WM_FORWARDMSG - used by apex to forward a message to another interaction_impl for processing
//   WPARAM - u32 dwUserData - defined by ::account::user
//   LPARAM - MESSAGE * pMsg - a pointer to the MESSAGE structure
//   return value - 0 if the message was not processed, nonzero if it was
#define WM_FORWARDMSG      0x037F
#define WM_APPEXIT         WM_APP + 1444




// like ON_MESSAGE but no return value
#define ON_MESSAGE_VOID(message, memberFxn) \
{ message,0,0,0,::apex::Sig_vv,\
   (__PMSG)(__PMSGW)(void (__MSG_CALLwindow::*)())&memberFxn },


//#include "platform/drawable.h"
//#include "apex/user/check.h"
//#include "apex/user/text.h"
//#include "apex/user/window_state.h"
//#include "apex/user/callback.h"
//#include "apex/user/primitive.h"

//#include "apex/user/style_base.h"
//#include "apex/user/style.h"


