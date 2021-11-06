#pragma once


#include "base/user/_.h"


#include "_const.h"


class form_document;


namespace user
{


   class user;
   class document_manager;
   class interaction_pointer_array;
   class split_view;
   class single_document_template;
   class multiple_document_template;
   class document;
   class keyboard;
   class theme;
   class copydesk;
   class main_frame;
   class window_map;
   class tree;
   class plain_edit;
#ifdef WINDOWS_DESKTOP
   class message_window;
#endif
   class scroll_base;
   template < class VIEW >  class show;
   using scroll_view = show < scroll_base >;
   using plain_edit_view = show < plain_edit >;

   class mesh_cache_interface;
   class mesh_data;
   class mesh;
   class list;
   class list_item;
   class list_column;

   class plain_text_set_sel_command;
   class plain_text_tree;
   class plain_text_command;
   class tree_draw_item;

   class shell;


} // namespace user



inline ::user::primitive* __user_primitive(oswindow oswindow);


#include "mesh_item.h"
#include "list_item.h"


#include "mesh_data.h"
#include "list_data.h"


//#include "aura/filesystem/file/html_file.h"


//#include "message_queue_listener.h"








