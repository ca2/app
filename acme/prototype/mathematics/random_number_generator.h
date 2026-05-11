#pragma once


CLASS_DECL_ACME int random_context_entropy(int iLevel= 3);

#include <random>
//#include "acme/prototype/collection/numeric_array.h"


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
   class CLASS_DECL_ACME random_number_generator
   {
   public:
      random_number_generator();

      ::u32 m_uSeed;
      std::default_random_engine m_generator;
      std::uniform_int_distribution<::u32> m_distributionU32;
      std::uniform_int_distribution<::u32> m_distributionU8;


      void seed(int iTwistLen, ::u32 seed);
      ::u32 get_unsigned_int();
      unsigned char get_unsigned_char();

   private:
      ::u32 _get();
      int m_value;
      unsigned_int_array m_uinta;
      ::i64 m_iAccess = 0;
   };

   // http://www.alhem.net/
   /** from C++ Sockets Library \file Utility.h
   **   \date  2004-02-13
   **   \author grymse@alhem.net
   **/
   // }


} //namespace mathematics




