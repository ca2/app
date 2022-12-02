#pragma once


#include "aura/user/user/_.h"


#include "_constant.h"


class application_menu;


namespace user
{


   class impact;
   class impact_data;
   class impact_system;
   class form;
   class form_impact;
   class document_manager;
   class tab;
   class impact_kit;
   class tab_data;
   class tab_pane;
   class tab_impact;
   class tab_callback;
   class place_holder;
   class split_bar;

   class picture;
   class picture_impl;

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
   class plain_edit;
#ifdef WINDOWS_DESKTOP
   class message_window;
#endif
   class scroll_base;
   template < class VIEW >  class show;
   using scroll_impact = show < scroll_base >;
   using plain_edit_impact = show < plain_edit >;

   class plain_text_set_sel_command;
   class plain_text_tree;
   class plain_text_command;
   class tree_draw_item;
   class impact_creator;


   class data_exchange;

   
   class shell;


   CLASS_DECL_BASE ::pointer<::user::document>__document(::request * prequest);




   typedef ::user::show < ::user::button > button_impact;




} // namespace user


class form_data;
class form_document;



