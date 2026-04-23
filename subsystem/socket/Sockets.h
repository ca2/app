// Created by camilo on 2026-04-22 23:33 <3ThomasBorregaardSørensen!!
#pragma once


#include "subsystem/_common_header.h"


namespace subsystem
{
   //
   // Class that startup and cleanup Windows Sockets subsystem.
   //
   class CLASS_DECL_SUBSYSTEM Sockets :
   virtual public ::particle
   {
   public:

      Sockets();

      ~Sockets() override;
      // Initializes Windows sockets subsystem.
      // Throws exception if winsock already initialized or
      // if was error during winsock startup.

      virtual void startup(int loVer, int hiVer);

      virtual void _startup(int loVer, int hiVer);

      //  Deinitializes Windows sockets subsystem.
      // Throws exception if winsock does not initialized or
      // if was error during winsock cleanup.
      virtual void cleanup();
      virtual void _cleanup();

   ///protected:
      bool m_bIsStarted;
   };


} // namespace subsystem