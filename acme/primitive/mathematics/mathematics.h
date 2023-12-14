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


      double         m_dPi;
      float          m_fPi;
      u32            dwMode;
      ::u8           pbData[16];

   public:


      ::pointer < math_os_data >  m_posdata;


      mathematics();
      virtual ~mathematics();


      virtual void initialize(::particle * pparticle) override;
      virtual void destroy() override;


      i32 LinearMap(i32 iMin, i32 iMax, i32 iValue, i32 iValueMin, i32 iValueMax);

      double LinearMap(double dMin, double dMax, double dValue, double dValueMin, double dValueMax);
      inline double get_pi() const { return m_dPi; }
      inline float get_pi_f() const { return m_fPi; }

      static bool IsPowerOfTwo(u64 uiValue);
      static u32 ReverseBits(u32 index, u32 NumBits);
      static inline void MaxClip(double * pnClipValue, double nMaxValue);
      static inline void MinClip(double * pnClipValue, double nMinValue);

      i32 RangeRate(i32 iMin, i32 iMax, double dRate);




      template < typename T1, typename T2 >
      inline bool clip_convert(T1 & t1, const T2 & t2)
      {

         if (::comparison::gt(t2, ::numeric_info < T1 >::get_maximum_value()))
         {

            t1 = ::numeric_info < T1 >::get_maximum_value();

            informationf("\nclip::assign maximum clipped");

            return false;

         }

         if (::comparison::lt(t2, ::numeric_info < T1 >::get_minimum_value()))
         {

            t1 = ::numeric_info < T1 >::get_minimum_value();

            informationf("\nclip::assign minimum clipped");

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

            informationf("\nclip::convert maximum clipped");

            return ::numeric_info < T1 >::get_maximum_value();

         }

         if (::comparison::lt(t2, ::numeric_info < T1 >::get_minimum_value()))
         {

            informationf("\nclip::convert minimum clipped");

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
      //i64 random(i64 i1, i64 i2);
      //i32 random(i32 i1, i32 i2);
      //template < typename ::i32 >
      //::i32 __random_int(::i32 i1, ::i32 i2);


      //#include "acme/primitive/primitive/matter.h"
      void random(const block & block);
      //u64 gen_rand();
//void random_bytes(void * buf, memsize dwLen);
//void RandomBytes(void * buf, memsize dwLen);
//void gen_rand(void * buf, memsize dwLen);

      void random_alphanumeric(char * buf, memsize dwLen);
      //string gen_rand_alnum(strsize s);
      string random_alphanumeric(strsize s);

      char random_char();
      u8 random_u8();
      u32 random_u32();
      u64 random_u64();

      i32 rand_max();


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

         ::u64 u = 0;

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

         auto u = random_u64();

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


