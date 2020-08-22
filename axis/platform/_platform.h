#pragma once




#undef SYSTEM_TYPE
#undef SESSION_TYPE
#undef APP_TYPE

#define SYSTEM_TYPE ::axis::system
#define SESSION_TYPE ::axis::session
#define APP_TYPE ::axis::application
//
//#undef Sys
//#define Sys(pobject) (*(::get_context_system(pobject))->cast < SYSTEM_TYPE >())
//
//#undef Sess
//#define Sess(pobject) (*(::get_context_session(pobject))->cast < SESSION_TYPE >())
//
//#undef App
//#define App(pobject) (*(::get_context_application(pobject))->cast < APP_TYPE >())
//



namespace axis
{

   //class run_start_installer;

   CLASS_DECL_AXIS bool init_core();

   CLASS_DECL_AXIS bool term_core();


} // namespace axis


CLASS_DECL_AXIS int get_core_init();
//extern "C"
//CLASS_DECL_AXIS int_bool defer_aura_init();
//extern "C"
//CLASS_DECL_AXIS int_bool defer_aura_term();


namespace axis
{


   //static_start g_staticstart;
   //{


   //   CLASS_DECL_AXIS void init(void);

   //   CLASS_DECL_AXIS void term(void);


   //} // namespace static_start


} // namespace axis







class task;




#pragma warning(disable: 4250)


class stdio_file;
struct memory_state;


//#include "const.h"


//#include "core/user/userex/const.h"


//#include "strn.h"


//#include "less.h"


//#include "smart_pointer_query.h"


//#define ASSERT_KINDOF(class_name, object) ASSERT(base_class < class_name > ::bases(object))
//#define DYNAMIC_CAST(class_name, object) (dynamic_cast < class_name * > (object))
//#define ZERO_INIT_JUST_THIS(base_class) __memset(((base_class*)this)+1, 0, sizeof(*this) - sizeof(class base_class));


//#include "constraint.h"

//
//class resource_exception;
//class user_exception;
//namespace axis
//{
//   class menu;                 // a menu
//
//}
//
//namespace draw2d
//{
//   class graphics;                   // a Display Context / HDC wrapper
//   class object;            // ::draw2d::graphics_pointer drawing tool
//   class bitmap;           // a bitmap
//   class palette;          // a palette
//   class region;
//   class font;
//   class pen;
//   class brush;
//   class memory_graphics;         // ::draw2d::graphics_pointer for client of window
//   class window_graphics;         // ::draw2d::graphics_pointer for entire window
//   class paint_graphics;          // embeddable BeginPaint struct helper
//}
//
//namespace axis
//{
//   class job;
//}
//
//class channel;            // a target for ::account::user commands
//
//namespace user
//{
//   class plain_edit;            // Edit control
//   class document_manager;      // impact_system manager object
//   class frame_window;        // standard SDI frame
//   class interaction_child;
//   class combo_box;        // ComboBox control
//} // namespace user
//
//
//namespace math
//{
//
//
//   class math;
//
//
//} // namespace math
//
//namespace geometry
//{
//
//   class geometry;
//
//} // namespace geometry
//class dialog;          // a dialog
//
////// standard windows controls
////class CStatic;          // Static control
////class CListBox;         // ListBox control
////class CCheckListBox;// special listbox with checks
////class CScrollBar;       // ScrollBar control
////
////// frame windows
////class CMDIFrameWnd; // standard MDI frame
////class CMDIChildWnd; // standard MDI child
////class CMiniFrameWnd;// half-height caption frame wnd
////
////// views on a document
////class CScrollView;  // a scrolling ::user::impact
//
///*class single_document_template;
//class multiple_document_template;
//*/
//
////namespace user
////{
////
////   class user;
////
////
////} // namespace user
////

//#include "aura/user/user/control_property.h"

//#include "history.h"

//#include "os_history.h"

//
//namespace axis
//{
//
//
//   CLASS_DECL_AXIS void format_strings(string& rString, const char* pszFormat, const char* const* rgpsz, i32 nString);
//
//   CLASS_DECL_AXIS bool extract_sub_string(string& rString, const char* pszFullString, i32 iSubString, char chSep = '\n');
//
//
//}


//#include "process_data.h"
//
//#include "types.h"
//
//#include "progress_interface.h"
//
//#include "debug.h"

//#include "aura/primitive/collection/std_iterator.h"
//#include "aura/primitive/collection/insert_iterator.h"
//#include "aura/primitive/collection/back_insert_iterator.h"
//#include "aura/primitive/collection/std_pair.h"


//#include "muldiv32.h"
//
//
//#include "logic.h"
//
//#include "util1.h"

//#include "app/aura/math/math_math.h"

//#include "theme.h"
//
////#include "app/aura/user/user/_.h"
//
//#include "debug.h"

//#include "aura/filesystem/filehandler/filehandler.h"

//#include "patch.h"

//#include "filesystem/filemanager/callback.h"
//
//#include "filesystem/filemanager/item_action.h"
//

//#include "aura/math/math_math.h"



//#endif





//#include "str_context.h"



