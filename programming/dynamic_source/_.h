#pragma once


#include "apex/filesystem/fs/fs.h"


#include "apex/networking/netserver/_.h"


#include "apex/networking/netserver/_netserver.h"


namespace dynamic_source
{


   class script_instance;
   class script_manager;
   class script;
   class script_instance;
   class httpd_socket;
   class script_main;


   typedef script_instance* (*NET_NODE_CREATE_INSTANCE_PROC)();


} // namespace dynamic_source


namespace webserver
{

   class simage_accepta;
   typedef __pointer_array(simage_accepta) simage_accepta_ptr_array;
   class match_host;
   typedef __pointer_array(match_host) match_host_array;
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


#include "exit_exception.h"

#include "session.h"


#include "apex/filesystem/file/html_file.h"


#include "library.h"


#include "script_interface.h"
#include "script_composite.h"
#include "script_instance.h"
#include "script_main.h"


#include "script.h"
#include "script_cache.h"
#include "script_compiler.h"


#include "httpd_socket.h"


#include "script_manager.h"


#include "_impl.h"



