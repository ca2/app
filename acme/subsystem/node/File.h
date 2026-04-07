// Created by camilo on 2026-04-05 18:22 <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/subsystem/_common_header.h"


namespace subsystem
{

   class CLASS_DECL_ACME FileInterface :
      virtual public ::subsystem::particle_interface
   {
   public:

      //File();
      virtual ~FileInterface() =0 ;

   };


   class CLASS_DECL_ACME File :
   virtual public ::subsystem::composite<FileInterface >
   {
   public:
      File();
      ~File() override;

   };

//// __WINCURSOR_H__
///
} // namespace subsystem
