#pragma once


#include  "apex/_.h"


namespace graphics
{


   class graphics;


} // namespace graphics



namespace user
{

   class button;

   class check_box;

   class still;

   class plain_edit;

   class message;


} // namespace user


//// like ON_MESSAGE but no return value
//#define ON_MESSAGE_VOID(message, memberFxn) \
//{ message,0,0,0,::aura::Sig_vv,\
//   (__PMSG)(__PMSGW)(void (__MSG_CALLwindow::*)())&memberFxn },


#include "aura/platform/drawable.h"
//#include "aura/user/check.h"
//#include "aura/user/text.h"
#include "aura/user/window_state.h"
#include "aura/user/callback.h"
#include "aura/user/primitive.h"



#include "aura/user/style_control.h"
//#include "aura/user/plain_edit_style.h"


#include "aura/user/style_base.h"
#include "aura/user/style.h"


class form_document;


namespace user
{


   class user;
   class interaction_array;
   class keyboard;
   class copydesk;
   class main_frame;
   //class window_map;
   class plain_edit;


#ifdef WINDOWS_DESKTOP

   class message_window;

#endif



   class plain_text_set_sel_command;
   class plain_text_tree;
   class plain_text_command;
   class tree_draw_item;

   //class shell;




} // namespace user




CLASS_DECL_AURA ::user::primitive* __user_primitive(::windowing::window * pwindow);



//#include "language.h"
//#include "language_map.h"


#include "system.h"

#include "mouse.h"

#include "aura/user/message.h"

#include "windowing.h"

#include "key.h"

#include "aura/message/user.h"





//#include "form_callback.h"
//#include "impact_creator.h"



//#include "document_manager_container.h"


#include "range.h"


//#include "mesh_item.h"
//#include "list_item.h"


//#include "mesh_data.h"
//#include "list_data.h"


//#include "aura/filesystem/file/html_file.h"


#include "message_window_listener.h"



//#include "aura/platform/message_box.h"



//#include "controller.h"

