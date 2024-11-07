#include "framework.h"
#include <time.h>
#undef __construct
#undef __create
#include "random_number_generator.h"
#include <chrono>
// defines for the random number generator
#define TWIST_LEN       (m_uinta.get_count())
#define TWIST_IA        397
#define TWIST_IB        (TWIST_LEN - TWIST_IA)
#define UMASK           I32_MINIMUM
#define LMASK           0x7FFFFFFF
#define MATRIX_A        0x9908B0DF
#define TWIST(b,i,j)   ((b)[i] & UMASK) | ((b)[j] & LMASK)
#define MAGIC_TWIST(s) (((s) & 1) * MATRIX_A)

namespace mathematics
{
   random_number_generator::random_number_generator() : 
      m_uSeed((unsigned int) ::std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count()),
      m_generator(m_uSeed),
      m_distributionU32(0, U32_MAXIMUM),
      m_distributionU8(0, U8_MAXIMUM)
   {
      seed(624, 0);
   }

   
   void random_number_generator::seed(int iTwistLen, unsigned int seed)
   {
      
      iTwistLen = maximum(TWIST_IA + 10, iTwistLen);
      
      m_uinta.set_size(iTwistLen);
      
      m_uinta[0]= seed & 0xffffffffUL;
      
      for (int i = 1; i < m_uinta.get_count(); i++)
      {
         
         m_uinta[i] = (1812433253UL * (m_uinta[i - 1] ^ (m_uinta[i - 1] >> 30)) + i);
         
      }
      
   }


/* generates a random number on [0,0xffffffff]-interval */

   unsigned int random_number_generator::get_unsigned_int()
   {
      return m_distributionU32(m_generator);
   }

   unsigned char random_number_generator::get_unsigned_char()
   {
      return m_distributionU8(m_generator);
   }

   unsigned int random_number_generator::_get()
   {
      if(m_uinta.get_size() == 0)
         return 0;
      m_iAccess++;
      unsigned int val = m_uinta[m_value % m_uinta.get_size()];
      ++m_value;
      if (m_value == TWIST_LEN)
      {
         int i = 0;
         for (i = 0; i < TWIST_IB; ++i)
         {
            unsigned int s = TWIST(m_uinta, i, i + 1);
            m_uinta[i] = m_uinta[i + TWIST_IA] ^ (s >> 1) ^ MAGIC_TWIST(s);
         }
         for (; i < TWIST_LEN - 1; ++i)
         {
            unsigned int s = TWIST(m_uinta, i, i + 1);
            m_uinta[i] = m_uinta[i - TWIST_IB] ^ (s >> 1) ^ MAGIC_TWIST(s);
         }
         unsigned int s = TWIST(m_uinta, TWIST_LEN - 1, 0);
         m_uinta[TWIST_LEN - 1] = m_uinta[TWIST_IA - 1] ^ (s >> 1) ^ MAGIC_TWIST(s);

         m_value = 0;
      }
      return val;
   }

} // namespace random_number_generator


   huge_integer random_context_entropy64(unsigned char bLevel)
   {

      bLevel = minimum(bLevel, 3);

      if (bLevel <= 0)
      {

         bLevel = 3;

      }

      huge_integer i0 = ::huge_integer_nanosecond();

      preempt(microsecond_time(bLevel));

      huge_integer i1 = ::huge_integer_nanosecond();

      huge_integer i2 = time(nullptr);

      huge_integer i3 = ::huge_integer_nanosecond();

      huge_integer i4 = abs(i0 + i1 + i2 + i3);

      return i4;

   }


   int random_context_entropy(int iLevel)
   {

      if (iLevel <= 0)
      {

         iLevel = 3;

      }

      huge_integer iValue = 0;

      iValue %= I32_MAXIMUM;

      while (iLevel > 0)
      {

         iValue += random_context_entropy64(iLevel);

         iValue %= I32_MAXIMUM;

         iLevel--;

      }

      return (int) iValue;

   }
