#pragma once


namespace draw2d
{


   class graphics_call_base :
      virtual public matter
   {
   public:

      
      virtual void call(::draw2d::graphics_pointer & pdraw2dgraphics) = 0;


   };


   class graphics_call :
      virtual public graphics_call_base
   {
   public:
      
      
      ::function<void(::draw2d::graphics_pointer &)> m_function;

      graphics_call(const ::function<void(::draw2d::graphics_pointer&)> & function) : m_function(function) {}

      void call(::draw2d::graphics_pointer & pdraw2dgraphics)
      {

         this->m_function(pdraw2dgraphics);

      }

   };


} // namespace draw2d



