//
// Created by camilo on 2026-04-08 17:33 <3ThomasBorregaardSørensen!!
//
#pragma once


namespace innate_subsystem
{

   class CLASS_DECL_INNATE_SUBSYSTEM GraphicsObject :
      virtual public ::particle_base
   {
   public:


      //virtual void * _HGDIOBJ();

      //virtual bool is_temporary_graphics_object() const;


      virtual void destroyGraphicsObject();


   };


}//namespace innate_subsystem