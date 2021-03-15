#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE iconoverlayer :
      virtual public ::object
   {
   public:


      iconoverlayer();
      virtual ~iconoverlayer();

      virtual ::e_status initialize(::context_object * pcontextobject) = 0;
      virtual void finalize() = 0;


      // give a chance to cache and optimize
      virtual void on_open_directory(const char * pszPath) = 0;

      virtual void overlay(const char * pszPath, ::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle) = 0;

   };


} // namespace filemanager