#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE iconoverlayer :
      virtual public ::object
   {
   public:


      iconoverlayer();
      virtual ~iconoverlayer();

      virtual void initialize(::particle * pparticle) = 0;
      virtual void destroy() = 0;


      // give a chance to cache and optimize
      virtual void on_open_directory(const ::string & pszPath) = 0;

      virtual void overlay(const ::string & pszPath, ::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle) = 0;

   };


} // namespace filemanager
