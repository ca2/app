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
#undef __construct
#undef __create
#include "random_number_generator.h"

namespace mathematics
{


   struct math_os_data :
      virtual public ::matter
   {


      int                              m_i;
      int                              m_iRngReSeedCountDown;
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
//         unsigned int dwMode = CRYPT_MODE_ECB;
//         if (CryptSetKeyParam(
//            m_hOriginalKey,
//            KP_MODE,
//            (unsigned char*)& dwMode,
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
//            (unsigned int)m.get_size(),
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

      void random(const ::block & block)
      {

         critical_section_lock lock(&m_criticalsection);

         unsigned int * pu = (unsigned int *) block.data();

         auto s = block.size();

         while(s > 4)
         {

            *pu = m_randomnumbergenerator.get_u32();

            s-=4;

            pu++;

         }

         char * pc = (char *)pu;

         while(s > 0)
         {

            s--;

            pc[s] = m_randomnumbergenerator.get_u8();

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
//         ::CryptGenRandom(m_hCryptProv, (unsigned int)s, (unsigned char*)p);
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
      m_dPi = atan(1.0) * 4.0;

      m_fPi = atanf(1.0f) * 4.0f;

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

      __construct_new(m_posdata);

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


   u64 mathematics::random_u64()
   {
//#if defined(UNIVERSAL_WINDOWS)
//      u64 uiLo = ::winrt::Windows::Security::Cryptography::CryptographicBuffer::GenerateRandomNumber();
//      u64 uiHi = ::winrt::Windows::Security::Cryptography::CryptographicBuffer::GenerateRandomNumber();
//      return uiLo | (uiHi << 32);
//#else
      u64 u = 0;
         random({ e_as_block,u });
         
      return u;
//#endif
//
   }

   char mathematics::random_char()
   {
      //#if defined(UNIVERSAL_WINDOWS)
      //      u64 uiLo = ::winrt::Windows::Security::Cryptography::CryptographicBuffer::GenerateRandomNumber();
      //      u64 uiHi = ::winrt::Windows::Security::Cryptography::CryptographicBuffer::GenerateRandomNumber();
      //      return uiLo | (uiHi << 32);
      //#else
//      char ch = 0;
//      random({ e_as_block,ch });
//
      return random_u8();
      //#endif
      //
   }


   unsigned char mathematics::random_u8()
   {
      //#if defined(UNIVERSAL_WINDOWS)
      //      u64 uiLo = ::winrt::Windows::Security::Cryptography::CryptographicBuffer::GenerateRandomNumber();
      //      u64 uiHi = ::winrt::Windows::Security::Cryptography::CryptographicBuffer::GenerateRandomNumber();
      //      return uiLo | (uiHi << 32);
      //#else
      //unsigned char u = 0;
      //random({ e_as_block,u });

      return m_posdata->m_randomnumbergenerator.get_u8();
      //#endif
      //
   }


   unsigned int mathematics::random_u32()
   {
      //#if defined(UNIVERSAL_WINDOWS)
      //      u64 uiLo = ::winrt::Windows::Security::Cryptography::CryptographicBuffer::GenerateRandomNumber();
      //      u64 uiHi = ::winrt::Windows::Security::Cryptography::CryptographicBuffer::GenerateRandomNumber();
      //      return uiLo | (uiHi << 32);
      //#else
      //unsigned int u = 0;
      //random({ e_as_block,u });

      return m_posdata->m_randomnumbergenerator.get_u32();
      //#endif
      //
   }

//   u64 mathematics::gen_rand()
//   {
////#if defined(UNIVERSAL_WINDOWS)
////      u64 uiLo = ::winrt::Windows::Security::Cryptography::CryptographicBuffer::GenerateRandomNumber();
////      u64 uiHi = ::winrt::Windows::Security::Cryptography::CryptographicBuffer::GenerateRandomNumber();
////      return uiLo | (uiHi << 32);
////#else
//      u64 u = 0;
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


   string mathematics::random_alphanumeric(strsize s)
   {

      ::string str;

      auto p = str.get_buffer(s);

      random_alphanumeric( p,s );

      str.release_buffer();

      return str;

   }


   //string mathematics::gen_rand_alnum(strsize s)
   //{

   //   string str;

   //   char * psz = str.get_buffer(s);

   //   gen_rand_alnum(psz, s);

   //   str.release_buffer(s);

   //   return str;

   //}


   //void mathematics::gen_rand_alnum(char * buf, memsize dwLen)
   //{

   //   generate_random_alphanumeric(buf, dwLen);

   //}




   int mathematics::rand_max()
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

   unsigned int mathematics::ReverseBits(unsigned int index, unsigned int NumBits)
   {
      unsigned int i, rev;

      for (i = rev = 0; i < NumBits; i++)
      {
         rev = (rev << 1) | (index & 1);
         index >>= 1;
      }

      return rev;
   }

   /*      int mathematics::RandRange(int i1, int i2)
   {
   // dRandRange == 0.0 is impossible event due this next statement;
   if(i1 == i2)
   return i1;
   int iMin = minimum(i1, i2);
   int iMax = maximum(i1, i2);
   double dRand = 0.0;
   double dRange = (double) (iMax - iMin);
   double dRandRange = 1.0;
   int i = 1;
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
   return (int) dRand;
   }

   unsigned int mathematics::RandRange(unsigned int ui1, unsigned int ui2)
   {
   // dRandRange == 0.0 is impossible event due this next statement;
   if(ui1 == ui2)
   return ui1;
   int iMin = minimum(ui1, ui2);
   int iMax = maximum(ui1, ui2);
   double dRand = 0.0;
   double dRange = (double) (iMax - iMin);
   double dRandRange = 1.0;
   int i = 1;
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
   return (int) dRand;
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
   int i = 1;
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
   return (int) dRand;
   }


   */

   int mathematics::LinearMap(int iMin, int iMax, int iValue, int iValueMin, int iValueMax)
   {
      double d = iValue - iValueMin;
      d *= (iMax - iMin) / (double)(iValueMax - iValueMin);
      d += iMin;
      d += 0.5;
      return (int)d;
   }

   double mathematics::LinearMap(double dMin, double dMax, double dValue, double dValueMin, double dValueMax)
   {
      
      double d = dValue - dValueMin;

      d *= (dMax - dMin) / (double)(dValueMax - dValueMin);

      d += dMin;

      return d;

   }


   int mathematics::RangeRate(int iMin, int iMax, double dRate)
   {
      
      return (int)((iMax - iMin) * dRate) + iMin;

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

   //      //task_untrack___allocate(g_pmathematics);

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



   void mathematics::random_alphanumeric(char * p, memsize s)
   {

      random({ p, s });

      transform_alphanumeric(p, s);

   }


   void mathematics::transform_alphanumeric(void * p, memsize s)
   {

      unsigned char * pchar = (unsigned char *)p;

      while (s > 0)
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



} // namespace mathematics


namespace apex
{


   namespace acme
   {

      int CLASS_DECL_ACME time_seed();

      void CLASS_DECL_ACME srand();

      int CLASS_DECL_ACME time_seed()
      {

         return (time(nullptr) % 5000 + (::i64_millisecond() / 100) % 5000) % 1000;

      }


      void CLASS_DECL_ACME srand()
      {
         int iSeed = time_seed();
         ::srand(iSeed);
         iSeed %= 64;
         for (int i = 0; i < iSeed; i++)
         {
            ::srand(rand());
         }
         for (int i = 0; i < iSeed; i++)
         {
            rand();
         }
      }


   } // acme





} // namespace mathematics


