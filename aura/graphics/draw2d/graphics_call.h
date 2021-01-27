#pragma once


namespace draw2d
{


   class graphics_call_base :
      virtual public matter
   {
   public:

      virtual void call(::draw2d::graphics * pgraphics) = 0;


   };

   template < typename PRED >
   class graphics_call :
      virtual public graphics_call_base
   {

      PRED m_pred;

      graphics_call(PRED pred) : m_pred(pred) {}

      void call(::draw2d::graphics * pgraphics)
      {

         m_pred(pgraphics);

      }

   };


   using graphics_call_array = __pointer_array(graphics_call_base);


} // namespace draw2d



