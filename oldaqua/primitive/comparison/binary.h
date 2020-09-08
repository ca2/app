#pragma once


namespace comparison
{


   template < typename TYPE, typename ARG_TYPE = const TYPE & >
   class binary
   {
   public:


      int operator ()(ARG_TYPE a, ARG_TYPE b)
      {
         if(a < b)
            return -1;
         else if(b < a)
            return 1;
         else
            return 0;
      }


   };

   template < >
   class CLASS_DECL_AQUA binary < i32 >
   {
   public:


      inline static iptr CompareElements(const i32 * pElement1, const i32 * pElement2)
      {
         return *pElement1 - *pElement2;
      }


   };



} // namespace comparison


