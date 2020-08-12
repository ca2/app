#pragma once


namespace user
{

   class impact_data;
   class frame_window;


} // namespace user

//#include "user_windowing.h"


// Note: afxData.cxBorder and afxData.cyBorder aren't used anymore
// #define CX_BORDER   1
// #define CY_BORDER   1




// Implementation structures
struct __SIZEPARENTPARAMS;    // control bar implementationproperca2_property.h

// Classes declared in this file

//::draw2d::graphics_pointer
class preview_dc;               // Virtual DC for print preview

class mini_dock_frame_window;

/////////////////////////////////////////////////////////////////////////////
// Global ID ranges (see Technical note TN020 for more details)

// 8000 -> FFFF command IDs (used for menu items, accelerators and controls)
#define IS_COMMAND_ID(nID)  ((nID) & 0x8000)

// 8000 -> DFFF : ::account::user commands
// E000 -> EFFF : _ commands and other things
// F000 -> FFFF : standard windows commands and other things etc
// E000 -> E7FF standard commands
// E800 -> E8FF control bars (first 32 are special)
// E900 -> EEFF standard interaction_impl controls/components
// EF00 -> EFFF SC_ menu help
// F000 -> FFFF standard strings
#define ID_COMMAND_FROM_SC(sc)  (((sc - 0xF000) >> 4) + __IDS_SCFIRST)

// 0000 -> 7FFF IDR range
// 0000 -> 6FFF : ::account::user resources
// 7000 -> 7FFF : _ (and standard windows) resources
// IDR ranges (NOTE: IDR_ values must be <32768)
#define ASSERT_VALID_IDR(nIDR) ASSERT((nIDR) != 0 && (nIDR) < 0x8000)

/////////////////////////////////////////////////////////////////////////////
// Context sensitive help support (see Technical note TN028 for more details)

// Help ID bases
#define HID_BASE_COMMAND    0x00010000UL        // ID and IDM
#define HID_BASE_RESOURCE   0x00020000UL        // IDR and IDD
#define HID_BASE_PROMPT     0x00030000UL        // IDP
#define HID_BASE_NCAREAS    0x00040000UL
#define HID_BASE_CONTROL    0x00050000UL        // IDC
#define HID_BASE_DISPATCH   0x00060000UL        // IDispatch help codes





// flags for wParam in the WM_FLOATSTATUS message
enum
{
   FS_SHOW = 0x01, FS_HIDE = 0x02,
   FS_ACTIVATE = 0x04, FS_DEACTIVATE = 0x08,
   FS_ENABLE = 0x10, FS_DISABLE = 0x20,
   FS_SYNCACTIVE = 0x40
};





#ifndef LAYOUT_LTR
#define LAYOUT_LTR                         0x00000000
#endif



//#include "user_job.h"


//#include "user_message.h"

//#include "axis/axis/axis_print_job.h"
//#include "user_print_job.h"


//#include "user_menu_item.h"
//#include "user_menu_command.h"
//#include "user_menu.h"

namespace user
{
   //class interaction_impl;
   class frame_window;
   class mdi_child_window;
   class control_bar;


   struct PrintPreviewState;  // forward context_object (see afxext.h)

   class mini_dock_frame_window;    // forward context_object (see afxpriv.h)


}

//#include "user_copydesk.h"


#include "user_inline.h"


//
//
//namespace user
//{
//
//   class CLASS_DECL_BASE map_form_window :
//      virtual public strsp(::user::form_control)
//   {
//   public:
//
//   };
//
//} // namespace user
//









