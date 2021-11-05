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

   class frame_window;


} // namespace user


#include "control_event_listener.h"


#include "aura/graphics/user/close_button.h"
#include "aura/graphics/user/close_icon.h"


#include "aura/platform/drawable.h"
#include "aura/user/window_state.h"
//#include "aura/user/callback.h"


#include "aura/user/style_control.h"


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
   class plain_edit;


#ifdef WINDOWS_DESKTOP

   class message_window;

#endif


   class plain_text_set_sel_command;
   class plain_text_tree;
   class plain_text_command;
   class tree_draw_item;


} // namespace user


CLASS_DECL_AURA ::user::primitive* __user_primitive(::windowing::window * pwindow);


#include "system.h"

#include "acme/constant/button_state.h"

#include "mouse.h"

#include "aura/user/message.h"

#include "windowing.h"

#include "key.h"

#include "acme/constant/activate.h"

#include "aura/message/user.h"


#include "range.h"


#include "message_window_listener.h"



