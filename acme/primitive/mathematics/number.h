#pragma once


//#include "math_value.h"


namespace mathematics
{


   class binary_operation;


   class number :
      virtual public value_impl
   {
   public:


      binary_operation * m_pbinop;


      number();
      virtual ~number();



   };


} // namespace mathematics



