#pragma once


CLASS_DECL_ACID i32 random_context_entropy(i32 iLevel= 3);

#include <random>
//#include "acid/primitive/collection/numeric_array.h"


namespace mathematics
{

   // {
   // http://www.alhem.net/
   /** from C++ Sockets Library \file Utility.h
   **   \date  2004-02-13
   **   \author grymse@alhem.net
   **/
   /** Conversion utilities.
   \ingroup util */
   /**
   The Mersenne Twister
   http://www.math.keio.ac.jp/~matumoto/emt.html
   */
   class CLASS_DECL_ACID random_number_generator
   {
   public:
      random_number_generator();

      ::u32 m_uSeed;
      std::default_random_engine m_generator;
      std::uniform_int_distribution<u32> m_distributionU32;
      std::uniform_int_distribution<u32> m_distributionU8;


      void seed(i32 iTwistLen, u32 seed);
      u32 get_u32();
      u8 get_u8();

   private:
      u32 _get();
      i32 m_value;
      u32_array m_uinta;
      ::i64 m_iAccess = 0;
   };

   // http://www.alhem.net/
   /** from C++ Sockets Library \file Utility.h
   **   \date  2004-02-13
   **   \author grymse@alhem.net
   **/
   // }


} //namespace mathematics




