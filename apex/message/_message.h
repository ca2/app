#pragma once


//namespace user
//{
//
//
//   class command;
//
//
//} // namespace user


namespace message
{

   
   class message;
   //class id_route;
   //template < typename MESSAGE > class typed_route;
   //class atom;
   class route;


} // namespace status


namespace draw2d
{


   class graphics;

   class path;


} // namespace draw2d


#include "predicate_handler.h"


#include "const.h"
#include "receiver.h"
#include "dispatcher.h"
#include "message.h"
//#include "definition.h"


#include "channel.h"
#include "base.h"
#include "_impl.h"
#include "listener_smart_pointer_array.h"

//#ifdef WINDOWS_DESKTOP
//
//#define MESSAGE MSG
//#define MESSAGE * LPMSG
//
//#endif

//namespace message
//{
//
//
//   CLASS_DECL_APEX bool is_idle_message(::message::message * pmessage);
//
//
//   CLASS_DECL_APEX bool is_idle_message(MESSAGE* pMsg);
//
//
//} // namespace message


//#include "timer.h"


