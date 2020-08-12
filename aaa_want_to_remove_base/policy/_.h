#pragma once

#pragma warning(disable: 4251)



namespace user
{



   class message_queue_listener;


   class scroll_info;


   class primitive_impl;
   class interaction;
   class user;
   class button;
   class window_draw;
   class control_event;
   class interaction_impl;
   class frame_window;
   class place_holder;
   class form_view;
   class impact_data;
   class message;
   //class map_form_window;
   class document_manager;
   class mouse;

   class interaction_pointer_array;




} // namespace user


namespace experience
{


   class experience;
   class frame_window;
   class updown;


} // namespace experience


namespace base
{

   class application;
   class system;
//   class system_interaction_impl;

   //typedef pointer < copydesk > copydesk_pointer;



} // namespace base


namespace database
{


   class server;


} // namespace database


namespace draw2d
{


   class icon;


} // namespace draw2d




namespace plane
{

   class session;
   class system;
   //class cube;


} // namespace plane



namespace draw2d
{


   class graphics;


} // namespace draw2d

class stream;

namespace file
{


   class file;
   class object;


} // namespace file

class machine_event_data;
namespace html
{
   class html;
} // namespace html


namespace message
{

   class mouse;

}


namespace base
{

   template < typename T >
   inline void del(T * & point)
   {
      if(point != nullptr)
      {
         delete point;
         point = nullptr;
      }
   }

} // namespace base



class image_list;





namespace data
{


   class item;


} // namespace data







namespace str
{


   namespace international
   {


      class locale_schema;


   } // namespace international


} // namespace str




namespace draw2d
{


   class graphics;


} // namespace draw2d





class event;


class thread;




class thread;


typedef pointer < thread > thread_pointer;


class thread_impl;


typedef pointer < thread_impl > thread_impl_pointer;



#define SYSTEM_TYPE ::base::system
#define SESSION_TYPE ::base::session
#define APP_TYPE ::base::application

#undef Sys
#define Sys(pobject) (*(::get_context_system(pobject))->cast < SYSTEM_TYPE >())

#undef Sess
#define Sess(pobject) (*(::get_context_session(pobject))->cast < SESSION_TYPE >())

#undef App
#define App(pobject) (*(::get_context_application(pobject))->cast < APP_TYPE >())







CLASS_DECL_BASE bool base_init();
CLASS_DECL_BASE bool base_term();

// CLASS_DECL_BASE bool __node_base_pre_init();
// CLASS_DECL_BASE bool __node_base_pos_init();

// CLASS_DECL_BASE bool __node_base_pre_term();
// CLASS_DECL_BASE bool __node_base_pos_term();

//#include "base/os/_.h"

CLASS_DECL_BASE ::user::interaction_impl * window_from_handle(oswindow oswindow);

#include "base/base/static_start.h"

#include "base/database/database.h"

#include "base/user/prelude.h"

#include "base/user/_.h"

#include "base/base/application.h"

#include "base/base/session.h"

#include "base/base/system.h"

#include "base/user/hotplugin/hotplugin.h"

#include "base/user/account/account.h"

//#include "base/base/node/_.h"

#include "base/user/_impl.h"

#include "base/base/_impl.h"









