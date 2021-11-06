#pragma once

/////////////////////////////////////////////////////////////////////////////
//
//   probe_::message::command - used to check for command status
//
//   It can be used before dispatching a command
//   It can be used to update a command button with updated status
//   ...
//

// class probe_::message::command: public ::message::command
// {
// public:


//    bool                    m_bEnabled;
//    enum_check          m_echeck;
//    string                  m_strText;
//    bool                    m_bRadio;
//    bool                    m_bRadioChanged;


//    probe_::message::command(::object * pobject);


//    virtual void enable(bool bOn, const ::action_context & action_context = ::e_source_system);
//    virtual void _001SetCheck(bool bCheck, const ::action_context & action_context = ::e_source_system);   // 0, 1 or 2 (indeterminate)
//    virtual void _001SetCheck(enum_check echeck, const ::action_context & action_context = ::e_source_system);   // 0, 1 or 2 (indeterminate)
//    virtual void SetRadio(bool bOn = true, const ::action_context & action_context = ::e_source_system);
//    virtual void SetText(const char * pszText, const ::action_context & action_context = ::e_source_system);



// };


// special ::message::command derived classes are used for other UI paradigms
// like toolbar buttons and status indicators

//// pointer to member function
//#ifndef __MSG_CALL
//#define __MSG_CALL
//#endif
////typedef void (__MSG_CALL channel::*__PMSG)();
////
////enum __DISPMAP_FLAGS
////{
////   afxDispCustom = 0,
////   afxDispStock = 1
////};
//
////IA64: __DISPMAP_ENTRY could be ordered more efficiently to reduce size_i32
//// bloat from alignment
//#pragma warning( disable: 4121 )
//struct CLASS_DECL_APEX __DISPMAP_ENTRY
//{
//   const char * lpszName;       // member/property name

//   long lDispID;           // DISPID (may be DISPID_UNKNOWN)
//   const char * pszParams;      // member parameter description

//   ::u16 vt;                // return value type / or type of property
//   __PMSG pfn;           // normal member On<membercall> or, OnGet<property>
//   __PMSG pfnSet;        // special member for OnSet<property>
//   size_t nPropOffset;     // property offset
//   __DISPMAP_FLAGS flags;// flags (e.g. stock/custom)
//};
//#pragma warning( default: 4121 )
//
//struct CLASS_DECL_APEX __EVENTSINKMAP_ENTRY
//{
//   __DISPMAP_ENTRY dispEntry;
//   ::u32 nCtrlIDFirst;
//   ::u32 nCtrlIDLast;
//};
//
//// DSC Sink state/reason codes passed to apex API ::account::user event handlers
//enum DSCSTATE
//{
//   dscNoState = 0,
//   dscOKToDo,
//   dscCancelled,
//   dscSyncBefore,
//   dscAboutToDo,
//   dscFailedToDo,
//   dscSyncAfter,
//   dscDidEvent
//};
//
//enum DSCREASON
//{
//   dscNoReason = 0,
//   dscClose,
//   dscCommit,
//   dscDelete,
//   dscEdit,
//   dscInsert,
//   dscModify,
//   dscMove
//};

/////////////////////////////////////////////////////////////////////////////
// interaction_impl implementation
namespace apex
{
   class create_context;      // action_context for creating user interface things
}
namespace apex
{
   class create_context;      // action_context for creating things
}
struct CPrintInfo;          // print preview customization info

/////////////////////////////////////////////////////////////////////////////
// interaction_impl - a Microsoft Windows application interaction_impl


// interaction_impl::m_nFlags (matter to interaction_impl)
#define WF_TOOLTIPS         0x0001  // interaction_impl is enabled for tooltips
#define WF_TEMPHIDE         0x0002  // interaction_impl is temporarily hidden
#define WF_STAYDISABLED     0x0004  // interaction_impl should stay disabled
#define WF_OLECTLCONTAINER  0x0100  // some descendant is an OLE control
#define WF_TRACKINGTOOLTIPS 0x0400  // interaction_impl is enabled for tracking tooltips

// interaction_impl::m_nFlags (specific to frame_window)
#define WF_STAYACTIVE       0x0020  // look active even though not active
#define WF_NOPOPMSG         0x0040  // ignore WM_POPMESSAGESTRING calls
#define WF_MODALDISABLE     0x0080  // interaction_impl is disabled
#define WF_KEEPMINIACTIVE   0x0200  // stay activate even though you are deactivated


#define WF_NOWIN32ISDIALOGMSG   0x0800
#define WF_ISWINFORMSVIEWWND    0x1000

// flags for interaction_impl::RunModalLoop
#define MLF_NOIDLEMSG       0x0001  // don't send WM_ENTERIDLE messages
#define MLF_NOKICKIDLE      0x0002  // don't send WM_KICKIDLE messages
#define MLF_SHOWONIDLE      0x0004  // show interaction_impl if not visible at idle time

// extra apex API defined TTF_ flags for TOOLINFO::uFlags
#define TTF_NOTBUTTON       0x80000000L // no status help on buttondown
#define TTF_ALWAYSTIP       0x40000000L // always show the tip even if not active







