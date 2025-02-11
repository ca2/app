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

      unsigned int m_uSeed;
      std::default_random_engine m_generator;
      std::uniform_int_distribution<unsigned int> m_distributionU32;
      std::uniform_int_distribution<unsigned int> m_distributionU8;


      void seed(int iTwistLen, unsigned int seed);
      unsigned int get_unsigned_int();
      unsigned char get_unsigned_char();

   private:
      unsigned int _get();
      int m_value;
      unsigned_int_array m_uinta;
      long long m_iAccess = 0;
   };

   // http://www.alhem.net/
   /** from C++ Sockets Library \file Utility.h
   **   \date  2004-02-13
   **   \author grymse@alhem.net
   **/
   // }


} //namespace mathematics




