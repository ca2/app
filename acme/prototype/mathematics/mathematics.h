#pragma once



template < typename UNIT_TYPE, primitive_number NUMBER >
inline UNIT_TYPE linear_rate(const UNIT_TYPE & t1, const UNIT_TYPE & t2, NUMBER numerator, NUMBER denominator)
{

   if (t2 == t1)
   {

      return t1;

   }

   return (UNIT_TYPE)(((double)(t2 - t1) * (double)numerator / (double)denominator) + (double)t1);

}



namespace mathematics
{

   struct math_os_data;

   class CLASS_DECL_ACME mathematics :
      virtual public ::matter
   {
   private:


      static double           s_π;
      static float            s_fπ;
      unsigned int            dwMode;
      unsigned char           pbData[16];

   public:


      ::pointer < math_os_data >  m_posdata;


      mathematics();
      virtual ~mathematics();


      virtual void initialize(::particle * pparticle) override;
      virtual void destroy() override;


      int LinearMap(int iMin, int iMax, int iValue, int iValueMin, int iValueMax);

      double LinearMap(double dMin, double dMax, double dValue, double dValueMin, double dValueMax);
      static inline double π() { return s_π; }
      static inline float πf() { return s_fπ; }

      static bool IsPowerOfTwo(unsigned long long uiValue);
      static unsigned int ReverseBits(unsigned int index, unsigned int NumBits);
      static inline void MaxClip(double * pnClipValue, double nMaxValue);
      static inline void MinClip(double * pnClipValue, double nMinValue);

      int RangeRate(int iMin, int iMax, double dRate);




      template < typename T1, typename T2 >
      inline bool clip_convert(T1 & t1, const T2 & t2)
      {

         if (::comparison::gt(t2, ::numeric_info < T1 >::get_maximum_value()))
         {

            t1 = ::numeric_info < T1 >::get_maximum_value();

            informationf("----> clip::assign maximum clipped");

            return false;

         }

         if (::comparison::lt(t2, ::numeric_info < T1 >::get_minimum_value()))
         {

            t1 = ::numeric_info < T1 >::get_minimum_value();

            informationf("----> clip::assign minimum clipped");

            return false;

         }

         t1 = (T1)t2;

         return true;

      }


      template < typename T1, typename T2 >
      inline T1 clip_convert(const T2 & t2)
      {

         if (::comparison::gt(t2, ::numeric_info < T1 >::get_maximum_value()))
         {

            informationf("----> clip::convert maximum clipped");

            return ::numeric_info < T1 >::get_maximum_value();

         }

         if (::comparison::lt(t2, ::numeric_info < T1 >::get_minimum_value()))
         {

            informationf("----> clip::convert minimum clipped");

            return ::numeric_info < T1 >::get_minimum_value();

         }

         return (T1)t2;

      }


      template < typename T1, typename T2 >
      inline bool clip_convert_add(T1 & t1, const T2 & t2)
      {

         auto t = t1 + t2;

         if (!convert(t1, t))
         {

            informationf(" (convert_add)");

         }

         return true;

      }


      template < typename T1, typename T2 >
      inline bool clip_convert_difference(T1 & t1, const T2 & t2)
      {

         auto t = t1 - t2;

         return clip_convert(t1, t);

      }


      template < typename T1, typename T2 >
      inline bool clip_convert_multiply(T1 & t1, const T2 & t2)
      {

         auto t = t2 * t1;

         if (!clip_convert(t1, t))
         {

            informationf(" (convert_multiply)");

         }

         return true;

      }


      // division by zero protection isn't this function's current responsability and maybe never should be
      template < typename T1, typename T2 >
      inline bool clip_convert_divide(T1 & t1, const T2 & t2)
      {

         auto t = t1 / t2;

         if (!clip_convert(t1, t))
         {

            informationf(" (convert_divide)");

         }

         return true;

      }



      //CLASS_DECL_ACME void generate_random_bytes(void* p, memsize s);
      void transform_alphanumeric(void * p, memsize s);
      //void generate_random_alphanumeric(void * p, memsize s);

      //template < typename TYPE >
      //inline TYPE * __random_bytes(TYPE * p, memsize s);

      //template < typename TYPE >
      //TYPE & random(TYPE & t);

      //template < typename TYPE >
      //TYPE random();


      //float random(float f1, float f2);
      //double random(double d1, double d2);
      //long long random(long long i1, long long i2);
      //int random(int i1, int i2);
      //template < typename int >
      //int __random_int(int i1, int i2);


      //#include "acme/prototype/prototype/matter.h"
      void random(const block & block);
      //unsigned long long gen_rand();
//void random_bytes(void * buf, memsize dwLen);
//void RandomBytes(void * buf, memsize dwLen);
//void gen_rand(void * buf, memsize dwLen);

      void random_alphanumeric(char * buf, memsize dwLen);
      //string gen_rand_alnum(character_count s);
      string random_alphanumeric(character_count s);

      char random_char();
      unsigned char random_uch();
      unsigned int random_ui();
      unsigned long long random_unsigned_long_long();

      int rand_max();


      //template < typename TYPE >
      //inline TYPE * __random_bytes(TYPE * p, memsize s)
      //{
      //   generate_random_bytes(p, s);
      //   return p;
      //}


      //template < typename TYPE >
      //inline TYPE & random(TYPE & t)
      //{

      //   return *__random_bytes(&t, sizeof(TYPE));

      //}


      template < typename TYPE >
      inline TYPE random()
      {

         TYPE t;

         random({ e_as_block, t });

         return t;

      }



      template < typename UNIT_TYPE >
      inline UNIT_TYPE minimum_maximum_rand(const UNIT_TYPE & t1, const UNIT_TYPE & t2)
      {

         return linear_rate(t1, t2, ::rand(), RAND_MAX);

      }




      template < primitive_floating FLOATING1, primitive_floating FLOATING2 >
      inline ::largest_type < FLOATING1, FLOATING2 > random(const FLOATING1 & f1, const FLOATING2 & f2)
      {

         if (f1 == f2) return f1;

         ::largest_type < FLOATING1, FLOATING2 > fMin = minimum(f1, f2);

         ::largest_type < FLOATING1, FLOATING2 > fMax = maximum(f1, f2);

         ::largest_type < FLOATING1, FLOATING2 > fRange = fMax - fMin;

         unsigned long long u = 0;

         random(u);

         return (::largest_type < FLOATING1, FLOATING2 >) (((u * fRange) / (::largest_type < FLOATING1, FLOATING2 >)U64_MAXIMUM) + fMin);

      }




      template < primitive_integral INTEGRAL1, primitive_integral INTEGRAL2 >
      inline ::largest_type < INTEGRAL1, INTEGRAL2 > random(const INTEGRAL1 & i1, const INTEGRAL2 & i2)
      {

         if (i1 == i2) return i1;

         ::largest_type < INTEGRAL1, INTEGRAL2 > iMin = minimum(i1, i2);

         ::largest_type < INTEGRAL1, INTEGRAL2 > iMax = maximum(i1, i2);

         ::largest_type < INTEGRAL1, INTEGRAL2 > iRange = iMax - iMin;

         auto u = random_unsigned_long_long();

         return(::largest_type < INTEGRAL1, INTEGRAL2 >) ((u % (iRange + 1)) + iMin);

      }





   };


   inline void mathematics::MaxClip(double * pnClipValue, double nMaxValue)
   {

      if (*pnClipValue > nMaxValue)
      {

         *pnClipValue = nMaxValue;

      }

   }


   inline void mathematics::MinClip(double * pnClipValue, double nMinValue)
   {
   
      if (*pnClipValue < nMinValue)
      {

         *pnClipValue = nMinValue;

      }

   }


   //CLASS_DECL_ACME class mathematics * mathematics();


} // namespace mathematics


