#pragma once


////#include "acme/primitive/primitive/object.h"
#include "acme/primitive/geometry2d/_geometry2d.h"


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
      virtual void on_open_directory(const ::string & pszPath) = 0;

      virtual void overlay(const ::string & pszPath, ::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle) = 0;

   };


} // namespace filemanager
