#pragma once


//CLASS_DECL_APEX void generate_random_bytes(void* p, memsize s);
CLASS_DECL_APEX void transform_alphanumeric(void* p, memsize s);
CLASS_DECL_APEX void generate_random_alphanumeric(void * p, memsize s);

template < typename TYPE >
inline TYPE* __random_bytes(TYPE* p, memsize s);

template < typename TYPE >
TYPE& __random(TYPE& t);

template < typename TYPE >
TYPE __random();


float __random(float f1, float f2);
double __random(double d1, double d2);
i64 __random(i64 i1, i64 i2);
i32 __random(i32 i1, i32 i2);
template < typename ::i32 >
::i32 __random_int(::i32 i1, ::i32 i2);


namespace math
{

   struct math_os_data;

   class CLASS_DECL_APEX math :
      virtual public ::apex::department
   {
   private:


      double         dPi;
      float          fPi;
      u32            dwMode;
      byte           pbData[16];

   public:


      __composite(math_os_data)  m_posdata;


      math();
      virtual ~math();


      virtual ::estatus initialize(::layered * pobjectContext) override;
      virtual void finalize() override;


      i32 LinearMap(i32 iMin, i32 iMax, i32 iValue, i32 iValueMin, i32 iValueMax);
      u64 gen_rand();
      void random_bytes(void * buf, memsize dwLen);
      void RandomBytes(void * buf, memsize dwLen);
      void gen_rand(void * buf, memsize dwLen);

      void gen_rand_alnum(char * buf, memsize dwLen);
      string gen_rand_alnum(strsize s);
      string random_string(strsize s);

      u32 rnd();
      i32 rand_max();

      double LinearMap(double dMin, double dMax, double dValue, double dValueMin, double dValueMax);
      double GetPi();
      float get_pi_f();

      static bool IsPowerOfTwo(u64 uiValue);
      static u32 ReverseBits(u32 index, u32 NumBits);
      static inline void MaxClip(double * pnClipValue, double nMaxValue);
      static inline void MinClip(double * pnClipValue, double nMinValue);

      i32 RangeRate(i32 iMin, i32 iMax, double dRate);


   };


   inline void math::MaxClip(double * pnClipValue, double nMaxValue)
   {

      if (*pnClipValue > nMaxValue)
      {

         *pnClipValue = nMaxValue;

      }

   }


   inline void math::MinClip(double * pnClipValue, double nMinValue)
   {
   
      if (*pnClipValue < nMinValue)
      {

         *pnClipValue = nMinValue;

      }

   }


} // namespace math


