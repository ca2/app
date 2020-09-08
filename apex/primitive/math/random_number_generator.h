#pragma once


CLASS_DECL_APEX i32 random_context_entropy(i32 iLevel= 3);


namespace math
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
   class CLASS_DECL_APEX rng
   {
   public:
      rng();

      void seed(i32 iTwistLen, u32 seed);
      u32 get();

   private:
      i32 m_value;
      u32_array m_uinta;
   };

   // http://www.alhem.net/
   /** from C++ Sockets Library \file Utility.h
   **   \date  2004-02-13
   **   \author grymse@alhem.net
   **/
   // }


} //namespace math




