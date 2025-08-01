#pragma once


////#include "acme/prototype/prototype/object.h"
//#include "acme/prototype/geometry2d/_geometry2d.h"


namespace filemanager
{


   class CLASS_DECL_CORE iconoverlayer :
      virtual public ::object
   {
   public:


      iconoverlayer();
      ~iconoverlayer() override;

      void initialize(::particle * pparticle) override = 0;
      void destroy() override = 0;


      // give a chance to cache and optimize
      virtual void on_open_directory(const ::scoped_string & scopedstrPath) = 0;

      virtual void overlay(const ::scoped_string & scopedstrPath, ::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangle) = 0;

   };


} // namespace filemanager
