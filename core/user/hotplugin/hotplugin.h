#pragma once



// hotplugin
// interface for a hot plugin
// hot plugin - a plugin that can easily change underlying plugin implementation
//
// hot plugin plugin - represents plugin interface
// hot plugin host - is a plugin - also - that can host a plugin by forwarding calls



namespace hotplugin
{

   
   class composer;


} // namespace hotplugin


#include "hotplugin_plugin.h"
#include "hotplugin_host.h"
#include "hotplugin_container_launcher.h"
#include "hotplugin_composer.h"

typedef ::hotplugin::plugin * (* FN_NEW_HOTPLUGIN)();


namespace hotplugin
{


   enum e_message
   {
      
      message_alive = 2000,
      message_init = 2000,
      message_set_window,
      message_paint,
      message_message,
      message_set_ready,
      message_set_installing,
      message_open_url,
      message_set_plugin_url

   };



   CLASS_DECL_BASE ::aura::system * get_aura_system();

   CLASS_DECL_BASE bool defer_start_base_system();
   CLASS_DECL_BASE void defer_stop_base_system();


#ifdef WINDOWS

   // hotplugin plugin dll HINSTANCE
   CLASS_DECL_BASE HINSTANCE get_hinstance();
   CLASS_DECL_BASE void set_hinstance(HINSTANCE hinstance);
   //CLASS_DECL_BASE void entry_hall_windows_on_paint(HDC hdc,const ::rectangle_i32 & rectangle,const string & strEntryHallText);



#endif

      CLASS_DECL_BASE void entry_hall_windows_on_paint(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle, const string & strEntryHallText);

} // namespace ca2plugin_container


