#pragma once


#include "base/user/_.h"


#include "_constant.h"


class form_document;


class xfplayer_impact_line;
class xfplayer_impact_line_selection;
class xfplayer_impact_linea;


namespace user
{


   class user;
   class document_manager;
   class interaction_pointer_array;
   class split_impact;
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
   using scroll_impact = show < scroll_base >;
   using plain_edit_impact = show < plain_edit >;

   class mesh_cache_interface;
   class mesh_data;
   class mesh;
   class mesh_item;
   class mesh_subitem;
   class mesh_group;
   class draw_mesh_item;
   class draw_mesh_subitem;
   class draw_mesh_group;
   class list;
   class list_data;
   class list_cache;
   class list_header;
   class list_item;
   class list_column;
   class list_column_array;
   class draw_list_item;
   class draw_list_subitem;
   class draw_list_group;


   class plain_text_set_sel_command;
   class plain_text_tree;
   class plain_text_command;
   class tree_draw_item;

   class shell;

   class font_list;

   class image_manager;

   typedef ::user::show < ::user::font_list > font_list_impact;


   class primitive_pointer_array;

   class control_bar;

   class scroll_info;



} // namespace user



class xfplayer_impact_linea;
class xfplayer_impact_line;

CLASS_DECL_CORE void DDX_Control(::user::data_exchange * pdx, atom idControl, ::user::interaction & control);
CLASS_DECL_CORE void DDX_Text(::user::data_exchange * pdx, atom idControl, string & str);
CLASS_DECL_CORE void DDV_MaxChars(::user::data_exchange * pdx, string & str, i32 iMax);
CLASS_DECL_CORE void DDX_Check(::user::data_exchange * pdx, atom idControl, i32 & iBool);
CLASS_DECL_CORE void DDX_Check(::user::data_exchange * pdx, atom idControl, bool & b);



inline ::user::primitive* __user_primitive(oswindow oswindow);


//#include "mesh_item.h"
//#include "list_item.h"
//
//
//#include "mesh_data.h"
//#include "list_data.h"
//




