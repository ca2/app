// Into tightvnc sources by Camilo on 2026-02-10 <3ThomasBorregaardSorensen!!
#pragma once



//#include "remoting/_.h"


//#if defined(_remoting_win_system_project)
//#define CLASS_DECL_REMOTING_WIN_SYSTEM  CLASS_DECL_EXPORT
//#else
//#define CLASS_DECL_REMOTING_WIN_SYSTEM  CLASS_DECL_IMPORT
//#endif
//


namespace subsystem
{


   class Registry;

   class string_table;

   class resource_loader;

   class subsystem;

   class PixelFormat;

   class Shell;

   using LogWriter = ::particle;


} // namespace subsystem


#include "acme/subsystem/io/_.h"
#include "acme/subsystem/thread/_.h"
