#include "framework.h"
#include "acme/platform/system.h"
#include "acme/_operating_system.h"
#include <time.h>
//#include "apex/primitive/mathematics/prime100k.h"
#ifdef LINUX

#endif
#ifdef WINDOWS
#include <wincrypt.h>
#endif
#include "mathematics.h"
#include "random_number_generator.h"

namespace mathematics
{


   struct math_os_data :
      virtual public ::matter
   {


      int                              m_i;
      i32                              m_iRngReSeedCountDown;
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
//            (byte*)& dwMode,
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

         //   //int c = prime100k_count();

         //   ::earth::time time = ::earth::time::now();

         //   int l = get_nanos() % c;

         //   int m = (l + time.GetDay()) % c;

         //   int n = (m + time.GetMonth()) % c;

         //   int o = (n + time.GetMinute()) % c;

         //   int p = (o + time.GetSecond()) % c;

         //   m_iRngReSeedCountDown = random_context_entropy(3);

         //   m_rng.seed(n, random_context_entropy(3));

         //}


      }


//#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID)

      void generate_random_bytes(void * p, memsize s)
      {

         critical_section_lock lock(&m_criticalsection);

         u32 * pu = (u32 *) p;

         while(s > 4)
         {

            *pu = m_randomnumbergenerator.get();

            s-=4;

            pu++;

         }

         char * pc = (char *)pu;

         u32 uSrc = m_randomnumbergenerator.get();

         char * pcSrc = (char *)&uSrc;

         while(s > 0)
         {

            s--;

            pc[s] = pcSrc[s];

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
//         ::CryptGenRandom(m_hCryptProv, (::u32)s, (byte*)p);
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

      m_posdata = memory_new math_os_data();

      // initial rng seed
      m_dPi = atan(1.0) * 4.0;

      m_fPi = atanf(1.0f) * 4.0f;

   }


   mathematics::~mathematics()
   {

      ::acme::del(m_posdata);

   }


   void mathematics::initialize(::particle * pparticle)
   {

      /*auto estatus =*/ ::matter::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_posdata = m_pcontext->__create_new < math_os_data>();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void mathematics::destroy()
   {

      //::acme::department::destroy();

      //return ::success;

   }


   u64 mathematics::gen_rand()
   {
//#if defined(UNIVERSAL_WINDOWS)
//      u64 uiLo = ::winrt::Windows::Security::Cryptography::CryptographicBuffer::GenerateRandomNumber();
//      u64 uiHi = ::winrt::Windows::Security::Cryptography::CryptographicBuffer::GenerateRandomNumber();
//      return uiLo | (uiHi << 32);
//#else
      u64 u = 0;
      gen_rand(&u, sizeof(u));
      return u;
//#endif
//
   }

   void mathematics::random_bytes(void * buf, memsize dwLen)
   {

      gen_rand(buf, dwLen);

   }

   void mathematics::RandomBytes(void * buf, memsize dwLen)
   {

      random_bytes(buf, dwLen);

   }


   void mathematics::gen_rand(void * buf, memsize dwLen)
   {

      generate_random_bytes(buf, dwLen);

   }


   string mathematics::random_string(strsize s)
   {

      return gen_rand_alnum(s);

   }


   string mathematics::gen_rand_alnum(strsize s)
   {

      string str;

      char * psz = str.get_buffer(s);

      gen_rand_alnum(psz, s);

      str.release_buffer(s);

      return str;

   }


   void mathematics::gen_rand_alnum(char * buf, memsize dwLen)
   {

      generate_random_alphanumeric(buf, dwLen);

   }




   i32 mathematics::rand_max()
   {

      return 0xffffff;

   }






   //double mathematics::get_pi()
   //{
   //   return dPi;
   //}


   //float mathematics::get_pi_f()
   //{
   //   return fPi;
   //}


   bool mathematics::IsPowerOfTwo(u64 uiValue)
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

   u32 mathematics::ReverseBits(u32 index, u32 NumBits)
   {
      u32 i, rev;

      for (i = rev = 0; i < NumBits; i++)
      {
         rev = (rev << 1) | (index & 1);
         index >>= 1;
      }

      return rev;
   }

   /*      i32 mathematics::RandRange(i32 i1, i32 i2)
   {
   // dRandRange == 0.0 is impossible event due this next statement;
   if(i1 == i2)
   return i1;
   i32 iMin = minimum(i1, i2);
   i32 iMax = maximum(i1, i2);
   double dRand = 0.0;
   double dRange = (double) (iMax - iMin);
   double dRandRange = 1.0;
   i32 i = 1;
   while((dRandRange - 1.0) < dRange)
   {
   dRand += dRandRange * gen_rand();
   dRandRange = pow((double) rand_max() + 1, (double) i);
   i++;
   }
   dRandRange -= 1.0;
   dRand *= (dRange) / (double) dRandRange;
   dRand += (double) iMin;
   dRand += 0.5;
   return (i32) dRand;
   }

   u32 mathematics::RandRange(u32 ui1, u32 ui2)
   {
   // dRandRange == 0.0 is impossible event due this next statement;
   if(ui1 == ui2)
   return ui1;
   i32 iMin = minimum(ui1, ui2);
   i32 iMax = maximum(ui1, ui2);
   double dRand = 0.0;
   double dRange = (double) (iMax - iMin);
   double dRandRange = 1.0;
   i32 i = 1;
   while((dRandRange - 1.0) < dRange)
   {
   dRand += dRandRange * gen_rand();
   dRandRange = pow((double) rand_max() + 1, (double) i);
   i++;
   }
   dRandRange -= 1.0;
   dRand *= (dRange) / (double) dRandRange;
   dRand += (double) iMin;
   dRand += 0.5;
   return (i32) dRand;
   }*/


   //double mathematics::frand_range(double d1, double d2)
   //{
   //   // dRandRange == 0.0 is impossible event due this next statement;
   //   if (d1 == d2)
   //      return d1;
   //   double dMin = minimum(d1, d2);
   //   double dMax = maximum(d1, d2);
   //   double dRange = dMax - dMin;
   //   return (((double)(gen_rand() % (1000000000 + 1)) / 1000000000.0) * dRange) + dMin;
   //}

   /*

   u64 mathematics::RandRange(u64 ui1, u64 ui2)
   {
   // dRandRange == 0.0 is impossible event due this next statement;
   if(ui1 == ui2)
   return ui1;
   u64 uiMin = minimum(ui1, ui2);
   u64 uiMax = maximum(ui1, ui2);
   double dRand = 0.0;
   double dRange = (double) (uiMax - uiMin);
   double dRandRange = 1.0;
   i32 i = 1;
   while((dRandRange - 1.0) < dRange)
   {
   dRand += dRandRange * gen_rand();
   dRandRange = pow((double) rand_max() + 1, (double) i);
   i++;
   }
   dRandRange -= 1.0;
   dRand *= (dRange) / (double) dRandRange;
   dRand += (double) uiMin;
   dRand += 0.5;
   return (i32) dRand;
   }


   */

   i32 mathematics::LinearMap(i32 iMin, i32 iMax, i32 iValue, i32 iValueMin, i32 iValueMax)
   {
      double d = iValue - iValueMin;
      d *= (iMax - iMin) / (double)(iValueMax - iValueMin);
      d += iMin;
      d += 0.5;
      return (i32)d;
   }

   double mathematics::LinearMap(double dMin, double dMax, double dValue, double dValueMin, double dValueMax)
   {
      
      double d = dValue - dValueMin;

      d *= (dMax - dMin) / (double)(dValueMax - dValueMin);

      d += dMin;

      return d;

   }


   i32 mathematics::RangeRate(i32 iMin, i32 iMax, double dRate)
   {
      
      return (i32)((iMax - iMin) * dRate) + iMin;

   }


   class mathematics* g_pmathematics = nullptr;


   CLASS_DECL_ACME class mathematics* mathematics()
   {

      return g_pmathematics;

   }


   void initialize_mathematics()
   {

      if (!g_pmathematics)
      {

         g_pmathematics = memory_new class mathematics;

      }

   }


   void finalize_mathematics()
   {

      ::acme::del(g_pmathematics);

   }


} // namespace mathematics


namespace apex
{


   namespace acme
   {

      i32 CLASS_DECL_ACME time_seed();

      void CLASS_DECL_ACME srand();

      i32 CLASS_DECL_ACME time_seed()
      {

         return (time(nullptr) % 5000 + (::integral_millisecond() / 100) % 5000) % 1000;

      }


      void CLASS_DECL_ACME srand()
      {
         i32 iSeed = time_seed();
         ::srand(iSeed);
         iSeed %= 64;
         for (i32 i = 0; i < iSeed; i++)
         {
            ::srand(rand());
         }
         for (i32 i = 0; i < iSeed; i++)
         {
            rand();
         }
      }


   } // acme




} // namespace mathematics




CLASS_DECL_ACME void generate_random_bytes(void * p, memsize s)
{

   ::mathematics::g_pmathematics->m_posdata->generate_random_bytes(p, s);

}



CLASS_DECL_ACME void generate_random_alphanumeric(void * p, memsize s)
{

   generate_random_bytes(p, s);

   transform_alphanumeric(p, s);

}


CLASS_DECL_ACME void transform_alphanumeric(void * p, memsize s)
{

   u8 * pchar = (u8 *) p;

   while(s > 0)
   {

      char ch = *pchar % 62;

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


