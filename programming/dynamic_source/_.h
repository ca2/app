#pragma once

//
//#include "apex/filesystem/fs/fs.h"
//
//
//#include "apex/networking/netserver/_.h"
//
//
//#include "apex/networking/netserver/_netserver.h"


namespace dynamic_source
{


   class script_instance;
   class script_manager;
   class script;
   class script_instance;
   class httpd_socket;
   class httpd_listen_socket;
   class script_main;


   typedef script_instance* (*NET_NODE_CREATE_INSTANCE_PROC)();

   class ds_script;
   class script;


   class library;


   class script_cache;
   class script_compiler;

   class session;



} // namespace dynamic_source


namespace webserver
{

   class simage_accepta;
   typedef pointer_array < simage_accepta > simage_accepta_ptr_array;
   class match_host;
   typedef pointer_array < match_host > match_host_array;
   class ui_redir;
   class account_database;
   class way_database;


} // namespace netnode


namespace netnode
{


   class script_manager;
   class script_interface;
   class script_main;
   class script_impl;

} // namespace netnode



