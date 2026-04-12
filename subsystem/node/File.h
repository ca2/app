// Created by camilo on 2026-04-05 18:22 <3ThomasBorregaardSørensen!!
#pragma once


#include "subsystem/_common_header.h"


namespace subsystem
{

   class CLASS_DECL_ACME FileInterface :
      virtual public ::subsystem::particle_interface<FileInterface>
   {
   public:

      //File();
      //virtual ~FileInterface() =0 ;

      virtual void * _HANDLE() = 0;

   };


   class CLASS_DECL_ACME File :
   virtual public ::subsystem::composite<FileInterface >
   {
   public:
      File();
      ~File() override;

      void * _HANDLE() override;

   };

} // namespace subsystem



