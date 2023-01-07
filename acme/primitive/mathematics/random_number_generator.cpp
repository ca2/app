#include "framework.h"
#include <time.h>
#include "random_number_generator.h"

// defines for the random number generator
#define TWIST_LEN       (m_uinta.get_count())
#define TWIST_IA        397
#define TWIST_IB        (TWIST_LEN - TWIST_IA)
#define UMASK           0x80000000
#define LMASK           0x7FFFFFFF
#define MATRIX_A        0x9908B0DF
#define TWIST(b,i,j)   ((b)[i] & UMASK) | ((b)[j] & LMASK)
#define MAGIC_TWIST(s) (((s) & 1) * MATRIX_A)

namespace mathematics
{
   random_number_generator::random_number_generator() : m_value( 0 )
   {
      seed(624, 0);
   }

   void random_number_generator::seed(i32 iTwistLen, u32 seed)
   {
      iTwistLen = maximum(TWIST_IA + 10, iTwistLen);
      m_uinta.allocate(iTwistLen);
      m_uinta[0]= seed & 0xffffffffUL;
      for (i32 i = 1; i < m_uinta.get_count(); i++)
      {
         m_uinta[i] = (1812433253UL * (m_uinta[i - 1] ^ (m_uinta[i - 1] >> 30)) + i);
      }
   }

/* generates a random number on [0,0xffffffff]-interval */
   u32 random_number_generator::get()
   {
      if(m_uinta.get_size() == 0)
         return 0;
      u32 val = m_uinta[m_value % m_uinta.get_size()];
      ++m_value;
      if (m_value == TWIST_LEN)
      {
         i32 i = 0;
         for (i = 0; i < TWIST_IB; ++i)
         {
            u32 s = TWIST(m_uinta, i, i + 1);
            m_uinta[i] = m_uinta[i + TWIST_IA] ^ (s >> 1) ^ MAGIC_TWIST(s);
         }
         for (; i < TWIST_LEN - 1; ++i)
         {
            u32 s = TWIST(m_uinta, i, i + 1);
            m_uinta[i] = m_uinta[i - TWIST_IB] ^ (s >> 1) ^ MAGIC_TWIST(s);
         }
         u32 s = TWIST(m_uinta, TWIST_LEN - 1, 0);
         m_uinta[TWIST_LEN - 1] = m_uinta[TWIST_IA - 1] ^ (s >> 1) ^ MAGIC_TWIST(s);

         m_value = 0;
      }
      return val;
   }

} // namespace random_number_generator


   i64 random_context_entropy64(byte bLevel)
   {

      bLevel = minimum(bLevel, 3);

      if (bLevel <= 0)
      {

         bLevel = 3;

      }

      i64 i0 = ::integral_nanosecond();

      preempt(integral_millisecond(bLevel));

      i64 i1 = ::integral_nanosecond();

      i64 i2 = time(nullptr);

      i64 i3 = ::integral_nanosecond();

      i64 i4 = abs(i0 + i1 + i2 + i3);

      return i4;

   }


   i32 random_context_entropy(i32 iLevel)
   {

      if (iLevel <= 0)
      {

         iLevel = 3;

      }

      ::i64 iValue = 0;

      iValue %= MAXI32;

      while (iLevel > 0)
      {

         iValue += random_context_entropy64(iLevel);

         iValue %= MAXI32;

         iLevel--;

      }

      return (::i32) iValue;

   }
