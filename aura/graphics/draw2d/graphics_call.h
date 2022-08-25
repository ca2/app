#pragma once


namespace draw2d
{


   class graphics_call_base :
      virtual public matter
   {
   public:

      
      virtual void call(::draw2d::graphics_pointer & pgraphics) = 0;


   };


   template < typename PRED >
   class graphics_call :
      virtual public graphics_call_base
   {
   public:
      
      
      PRED m_predicate;

      graphics_call(PRED pred) : m_predicate(pred) {}

      void call(::draw2d::graphics_pointer & pgraphics)
      {

         this->m_predicate(pgraphics);

      }

   };


} // namespace draw2d



