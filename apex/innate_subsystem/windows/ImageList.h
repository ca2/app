//
// Created by camilo on 2026-04-06 14:22 <3ThomasBorregaardSørensen!!
//
#pragma once
#include "acme/subsystem/particle.h"


namespace innate_subsystem
{


   class CLASS_DECL_APEX ImageListInterface :
   virtual public ::subsystem::particle_interface
   {
   public:


      virtual ~ImageListInterface() = 0;

      virtual void initialize_image_list() = 0;



   };



   class CLASS_DECL_APEX ImageList :
   virtual public ::subsystem::composite<ImageListInterface>
   {
   public:

      ImageList();

       ~ImageList()override;

      void initialize_image_list() override;



   };

} // namespace innate_subsystem
