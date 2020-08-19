#pragma once


class form_document;


namespace user
{

   
   class user;
   class control;
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
   //class tree;
   class plain_edit;
   class message_queue;
   template < class VIEW >  class show;
   using scroll_view = show < control >;
   using plain_edit_view = show < plain_edit >;

   //class mesh_cache_interface;
   //class mesh_data;
   //class mesh;
   //class list;
   //class list_item;
   //class list_column;

   CLASS_DECL_AURA COLORREF get_system_app_background_color();

   CLASS_DECL_AURA bool is_system_dark_mode();

   CLASS_DECL_AURA bool is_app_dark_mode();

   class plain_text_set_sel_command;
   class plain_text_tree;
   class plain_text_command;
   class tree_draw_item;

   class shell;




} // namespace user


namespace user
{

#if !defined(WINDOWS_DESKTOP) && !defined(MACOS)
   CLASS_DECL_AURA void set_system_dark_mode(bool bDark);
   CLASS_DECL_AURA void set_app_dark_mode(bool bDark);
#endif
   CLASS_DECL_AURA bool is_system_dark_mode();
   CLASS_DECL_AURA bool is_app_dark_mode();
   CLASS_DECL_AURA void os_update_dark_mode();


} // namespace user


inline ::user::primitive* __user_primitive(oswindow oswindow);



#include "language.h"
#include "language_map.h"


#include "create_struct.h"


#include "windowing.h"
#include "key.h"
#include "mouse.h"





#include "form_callback.h"
#include "impact_creator.h"



#include "document_manager_container.h"


#include "range.h"


//#include "mesh_item.h"
//#include "list_item.h"


//#include "mesh_data.h"
//#include "list_data.h"


#include "aura/filesystem/file/html_file.h"


#include "message_queue_listener.h"






