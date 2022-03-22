#pragma once


namespace user
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

         m_predicate(pgraphics);

      }

   };


   using graphics_call_array = __pointer_array(graphics_call_base);


} // namespace user



