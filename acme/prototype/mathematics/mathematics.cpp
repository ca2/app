#include "framework.h"
#include "acme/platform/system.h"
#include "acme/_operating_system.h"
#include <time.h>
//#include "apex/prototype/mathematics/prime100k.h"
#ifdef LINUX

#endif
#ifdef WINDOWS
#include <wincrypt.h>
#endif
#include "mathematics.h"
//#undef constructø
//#undef createø
#include "random_number_generator.h"

namespace mathematics
{


   ::f64 mathematics::s_π = atan(1.0) * 4.0;

   ::f32 mathematics::s_fπ = atanf(1.0f) * 4.0f;


   struct math_os_data :
      virtual public ::matter
   {


      ::i32                              m_i32;
      ::i32                              m_iRngReSeedCountDown;
      ::critical_section               m_criticalsection;
      random_number_generator          m_randomnumbergenerator;

//#ifdef WINDOWS_DESKTOP
//
//      HCRYPTPROV           m_hCryptProv;
//      HCRYPTKEY            m_hOriginalKey;
//      HCRYPTKEY            m_hDuplicateKey;
//
//#endif


      math_os_data()
      {

         construct();

      }


      virtual ~math_os_data() 
      {
      
      }


      void construct()
      {

//#ifdef WINDOWS_DESKTOP
//
//         m_hCryptProv = NULL;
//
//         m_hOriginalKey = NULL;
//
//         m_hDuplicateKey = NULL;
//
//         if (!CryptAcquireContext(
//            &m_hCryptProv,
//            nullptr,
//            nullptr,
//            PROV_RSA_FULL,
//            0))
//         {
//            if (CryptAcquireContext(
//               &m_hCryptProv,
//               nullptr,
//               nullptr,
//               PROV_RSA_FULL,
//               CRYPT_NEWKEYSET))
//            {
//               //debug_print("CryptAcquireContext succeeded. \n");
//            }
//            else
//            {
//               //           TRACELASTERROR();
//               //debug_print("Error during CryptAcquireContext!\n");
//
//            }
//
//         }
//         else
//         {
//            //debug_print("CryptAcquireContext succeeded. \n");
//         }
//         //-------------------------------------------------------------------
//         // Generate a key.
//         if (CryptGenKey(
//            m_hCryptProv,
//            CALG_RC4,
//            0,
//            &m_hOriginalKey))
//         {
//            //debug_print("Original session key is created. \n");
//         }
//         else
//         {
//            //debug_print("ERROR - CryptGenKey.");
//         }
//         //-------------------------------------------------------------------
//         // Duplicate the key.
//
//         if (CryptDuplicateKey(
//            m_hOriginalKey,
//            nullptr,
//            0,
//            &m_hDuplicateKey))
//         {
//            //debug_print("The session key has been duplicated. \n");
//         }
//         else
//         {
//            //debug_print("ERROR - CryptDuplicateKey");
//         }
//         //-------------------------------------------------------------------
//         // set additional parameters on the original key.
//         // First, set the cipher mode.
//
//         ::u32 dwMode = CRYPT_MODE_ECB;
//         if (CryptSetKeyParam(
//            m_hOriginalKey,
//            KP_MODE,
//            (::u8*)& dwMode,
//            0))
//         {
//            //debug_print("Key Parameters set. \n");
//         }
//         else
//         {
//            //debug_print("Error during CryptSetKeyParam.");
//         }
//
//         memory m;
//
//         m.set_size(256);
//
//
//
//         // Generate a random initialization vector.
//         if (CryptGenRandom(
//            m_hCryptProv,
//            (::u32)m.get_size(),
//            m.get_data()))
//         {
//            //debug_print("Random sequence generated. \n");
//         }
//         else
//         {
//            //debug_print("Error during CryptGenRandom.");
//         }
//         //-------------------------------------------------------------------
//         // set the initialization vector.
//         if (CryptSetKeyParam(
//            m_hOriginalKey,
//            KP_IV,
//            m.get_data(),
//            0))
//         {
//            //debug_print("Parameter set with random sequence as initialization vector. \n");
//         }
//         else
//         {
//            //debug_print("Error during CryptSetKeyParam.");
//         }
//
//#endif

         //{

         //   //::i32 c = prime100k_count();

         //   ::earth::time time = ::earth::time::now();

         //   ::i32 l = get_nanos() % c;

         //   ::i32 m = (l + time.GetDay()) % c;

         //   ::i32 n = (m + time.GetMonth()) % c;

         //   ::i32 o = (n + time.GetMinute()) % c;

         //   ::i32 p = (o + time.GetSecond()) % c;

         //   m_iRngReSeedCountDown = random_context_entropy(3);

         //   m_rng.seed(n, random_context_entropy(3));

         //}


      }


//#if defined(LINUX) || defined(__APPLE__) || defined(__ANDROID__)

      void random(const ::block & block)
      {

         critical_section_lock lock(&m_criticalsection);

         ::u32 * pu = (::u32 *) block.data();

         auto s = block.size();

         while(s > 4)
         {

            *pu = m_randomnumbergenerator.get_u32();

            s-=4;

            pu++;

         }

         char_pointer pc = (char_pointer )pu;

         while(s > 0)
         {

            s--;

            pc[s] = m_randomnumbergenerator.get_unsigned_char();

         }

      }

//#elif defined(WINDOWS_DESKTOP)
//
//      void generate_random_bytes(void* p, memsize s)
//      {
//
//         critical_section_lock lock(&m_criticalsection);
//
//
//         ::CryptGenRandom(m_hCryptProv, (::u32)s, (::u8*)p);
//
//      }
//
//#elif defined(UNIVERSAL_WINDOWS)
//
//      void generate_random_bytes(void* p, memsize s)
//      {
//
//         ::winrt::Windows::Storage::Streams::IBuffer^ buffer = ::winrt::Windows::Security::Cryptography::CryptographicBuffer::GenerateRandom(s);
//
//         memory mem;
//
//         mem.set_os_buffer(buffer);
//
//         ::memory_copy(p, mem.get_data(), mem.get_size());
//
//      }
//
//
//#endif


   };


   mathematics::mathematics()
   {

      //task_on_after_new_particle(m_posdata);

      // initial rng seed

   }


   mathematics::~mathematics()
   {

      m_posdata.release();

   }


   void mathematics::initialize(::particle * pparticle)
   {

      /*auto estatus =*/ ::matter::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      construct_newø(m_posdata);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void mathematics::destroy()
   {

      //::platform::department::destroy();

      //return ::success;

   }


   ::u64 mathematics::random_u64()
   {
//#if defined(UNIVERSAL_WINDOWS)
//      ::u64 uiLo = ::winrt::Windows::Security::Cryptography::CryptographicBuffer::GenerateRandomNumber();
//      ::u64 uiHi = ::winrt::Windows::Security::Cryptography::CryptographicBuffer::GenerateRandomNumber();
//      return uiLo | (uiHi << 32);
//#else
      ::u64 u = 0;
         random({ e_as_block,u });
         
      return u;
//#endif
//
   }

   ::i8 mathematics::random_char()
   {
      //#if defined(UNIVERSAL_WINDOWS)
      //      ::u64 uiLo = ::winrt::Windows::Security::Cryptography::CryptographicBuffer::GenerateRandomNumber();
      //      ::u64 uiHi = ::winrt::Windows::Security::Cryptography::CryptographicBuffer::GenerateRandomNumber();
      //      return uiLo | (uiHi << 32);
      //#else
//      ::i8 ch = 0;
//      random({ e_as_block,ch });
//
      return random_u8();
      //#endif
      //
   }


   ::u8 mathematics::random_u8()
   {
      //#if defined(UNIVERSAL_WINDOWS)
      //      ::u64 uiLo = ::winrt::Windows::Security::Cryptography::CryptographicBuffer::GenerateRandomNumber();
      //      ::u64 uiHi = ::winrt::Windows::Security::Cryptography::CryptographicBuffer::GenerateRandomNumber();
      //      return uiLo | (uiHi << 32);
      //#else
      //::u8 u = 0;
      //random({ e_as_block,u });

      return m_posdata->m_randomnumbergenerator.get_unsigned_char();
      //#endif
      //
   }


   ::u32 mathematics::random_ui()
   {
      //#if defined(UNIVERSAL_WINDOWS)
      //      ::u64 uiLo = ::winrt::Windows::Security::Cryptography::CryptographicBuffer::GenerateRandomNumber();
      //      ::u64 uiHi = ::winrt::Windows::Security::Cryptography::CryptographicBuffer::GenerateRandomNumber();
      //      return uiLo | (uiHi << 32);
      //#else
      //::u32 u = 0;
      //random({ e_as_block,u });

      return m_posdata->m_randomnumbergenerator.get_u32();
      //#endif
      //
   }

//   ::u64 mathematics::gen_rand()
//   {
////#if defined(UNIVERSAL_WINDOWS)
////      ::u64 uiLo = ::winrt::Windows::Security::Cryptography::CryptographicBuffer::GenerateRandomNumber();
////      ::u64 uiHi = ::winrt::Windows::Security::Cryptography::CryptographicBuffer::GenerateRandomNumber();
////      return uiLo | (uiHi << 32);
////#else
//      ::u64 u = 0;
//      gen_rand(&u, sizeof(u));
//      return u;
////#endif
////
//   }

   //void mathematics::random_bytes(void * buf, memsize dwLen)
   //{

   //   gen_rand(buf, dwLen);

   //}

   //void mathematics::RandomBytes(void * buf, memsize dwLen)
   //{

   //   random_bytes(buf, dwLen);

   //}


   //void mathematics::gen_rand(void * buf, memsize dwLen)
   //{

   //   random({ buf, dwLen });

   //}


   string mathematics::random_alphanumeric(character_count s)
   {

      ::string str;

      auto p = str.get_buffer(s);

      random_alphanumeric( p,s );

      str.release_buffer();

      return str;

   }


   //string mathematics::gen_rand_alnum(character_count s)
   //{

   //   string str;

   //   char_pointer psz = str.get_buffer(s);

   //   gen_rand_alnum(scopedstr, s);

   //   str.release_buffer(s);

   //   return str;

   //}


   //void mathematics::gen_rand_alnum(char_pointer buf, memsize dwLen)
   //{

   //   generate_random_alphanumeric(buf, dwLen);

   //}




   ::i32 mathematics::rand_max()
   {

      return 0xffffff;

   }






   //::f64 mathematics::get_pi()
   //{
   //   return dPi;
   //}


   //::f32 mathematics::get_pi_f()
   //{
   //   return fPi;
   //}


   bool mathematics::IsPowerOfTwo(::u64 uiValue)
   {

      if (uiValue == 0)
      {

         return false;

      }

      if (uiValue & (uiValue - 1)) // Thanks to 'byang' for this cute trick!
      {

         return false;

      }

      return true;

   }

   ::u32 mathematics::ReverseBits(::u32 index, ::u32 NumBits)
   {
      ::u32 i, rev;

      for (i = rev = 0; i < NumBits; i++)
      {
         rev = (rev << 1) | (index & 1);
         index >>= 1;
      }

      return rev;
   }

   /*      ::i32 mathematics::RandRange(::i32 i1, ::i32 i2)
   {
   // dRandRange == 0.0 is impossible happening due this next statement;
   if(i1 == i2)
   return i1;
   ::i32 iMin = minimum(i1, i2);
   ::i32 iMax = maximum(i1, i2);
   ::f64 dRand = 0.0;
   ::f64 dRange = (::f64) (iMax - iMin);
   ::f64 dRandRange = 1.0;
   ::i32 i = 1;
   while((dRandRange - 1.0) < dRange)
   {
   dRand += dRandRange * gen_rand();
   dRandRange = pow((::f64) rand_max() + 1, (::f64) i);
   i++;
   }
   dRandRange -= 1.0;
   dRand *= (dRange) / (::f64) dRandRange;
   dRand += (::f64) iMin;
   dRand += 0.5;
   return (::i32) dRand;
   }

   ::u32 mathematics::RandRange(::u32 ui1, ::u32 ui2)
   {
   // dRandRange == 0.0 is impossible happening due this next statement;
   if(ui1 == ui2)
   return ui1;
   ::i32 iMin = minimum(ui1, ui2);
   ::i32 iMax = maximum(ui1, ui2);
   ::f64 dRand = 0.0;
   ::f64 dRange = (::f64) (iMax - iMin);
   ::f64 dRandRange = 1.0;
   ::i32 i = 1;
   while((dRandRange - 1.0) < dRange)
   {
   dRand += dRandRange * gen_rand();
   dRandRange = pow((::f64) rand_max() + 1, (::f64) i);
   i++;
   }
   dRandRange -= 1.0;
   dRand *= (dRange) / (::f64) dRandRange;
   dRand += (::f64) iMin;
   dRand += 0.5;
   return (::i32) dRand;
   }*/


   //::f64 mathematics::frand_range(::f64 d1, ::f64 d2)
   //{
   //   // dRandRange == 0.0 is impossible happening due this next statement;
   //   if (d1 == d2)
   //      return d1;
   //   ::f64 dMin = minimum(d1, d2);
   //   ::f64 dMax = maximum(d1, d2);
   //   ::f64 dRange = dMax - dMin;
   //   return (((::f64)(gen_rand() % (1000000000 + 1)) / 1000000000.0) * dRange) + dMin;
   //}

   /*

   ::u64 mathematics::RandRange(::u64 ui1, ::u64 ui2)
   {
   // dRandRange == 0.0 is impossible happening due this next statement;
   if(ui1 == ui2)
   return ui1;
   ::u64 uiMin = minimum(ui1, ui2);
   ::u64 uiMax = maximum(ui1, ui2);
   ::f64 dRand = 0.0;
   ::f64 dRange = (::f64) (uiMax - uiMin);
   ::f64 dRandRange = 1.0;
   ::i32 i = 1;
   while((dRandRange - 1.0) < dRange)
   {
   dRand += dRandRange * gen_rand();
   dRandRange = pow((::f64) rand_max() + 1, (::f64) i);
   i++;
   }
   dRandRange -= 1.0;
   dRand *= (dRange) / (::f64) dRandRange;
   dRand += (::f64) uiMin;
   dRand += 0.5;
   return (::i32) dRand;
   }


   */

   ::i32 mathematics::LinearMap(::i32 iMin, ::i32 iMax, ::i32 iValue, ::i32 iValueMin, ::i32 iValueMax)
   {
      ::f64 d = iValue - iValueMin;
      d *= (iMax - iMin) / (::f64)(iValueMax - iValueMin);
      d += iMin;
      d += 0.5;
      return (::i32)d;
   }

   ::f64 mathematics::LinearMap(::f64 dMin, ::f64 dMax, ::f64 dValue, ::f64 dValueMin, ::f64 dValueMax)
   {
      
      ::f64 d = dValue - dValueMin;

      d *= (dMax - dMin) / (::f64)(dValueMax - dValueMin);

      d += dMin;

      return d;

   }


   ::i32 mathematics::RangeRate(::i32 iMin, ::i32 iMax, ::f64 dRate)
   {
      
      return (::i32)((iMax - iMin) * dRate) + iMin;

   }


   // class mathematics* g_pmathematics = nullptr;


   //CLASS_DECL_ACME class mathematics* mathematics()
   //{

   //   return g_pmathematics;

   //}


   //void initialize_mathematics()
   //{

   //   if (!g_pmathematics)
   //   {

   //      g_pmathematics = ___new class mathematics ();

   //      //task_untrack_allocateø(g_pmathematics);

   //   }

   //}


   //void finalize_mathematics()
   //{

   //   ::acme::del(g_pmathematics);

   //}


   void mathematics::random(const ::block & block)
   {

      m_posdata->random(block);

   }



   void mathematics::random_alphanumeric(char_pointer p, memsize s)
   {

      random({ p, s });

      transform_alphanumeric(p, s);

   }


   void mathematics::transform_alphanumeric(void * p, memsize s)
   {

      ::u8 * pchar = (::u8 *)p;

      while (s > 0)
      {

         ::i8 ch = *pchar % 62;

         if (ch <= 9)
         {

            *pchar = ch + '0';

         }
         else if (ch <= 35)
         {

            *pchar = ch - 10 + 'a';

         }
         else
         {

            *pchar = ch - 36 + 'A';

         }

         pchar++;

         s--;

      }

   }



} // namespace mathematics


namespace apex
{


   namespace acme
   {

      ::i32 CLASS_DECL_ACME time_seed();

      void CLASS_DECL_ACME srand();

      ::i32 CLASS_DECL_ACME time_seed()
      {

         return (time(nullptr) % 5000 + (::i64_millisecond() / 100) % 5000) % 1000;

      }


      void CLASS_DECL_ACME srand()
      {
         ::i32 iSeed = time_seed();
         ::srand(iSeed);
         iSeed %= 64;
         for (::i32 i = 0; i < iSeed; i++)
         {
            ::srand(rand());
         }
         for (::i32 i = 0; i < iSeed; i++)
         {
            rand();
         }
      }


   } // acme





} // namespace mathematics


