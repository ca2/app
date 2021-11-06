#pragma once


//CLASS_DECL_ACME void generate_random_bytes(void* p, memsize s);
CLASS_DECL_ACME void transform_alphanumeric(void* p, memsize s);
CLASS_DECL_ACME void generate_random_alphanumeric(void * p, memsize s);

template < typename TYPE >
inline TYPE* __random_bytes(TYPE* p, memsize s);

template < typename TYPE >
TYPE& __random(TYPE& t);

template < typename TYPE >
TYPE __random();


//float __random(float f1, float f2);
//double __random(double d1, double d2);
//i64 __random(i64 i1, i64 i2);
//i32 __random(i32 i1, i32 i2);
//template < typename ::i32 >
//::i32 __random_int(::i32 i1, ::i32 i2);


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
      byte           pbData[16];

   public:


      math_os_data *  m_posdata;


      mathematics();
      virtual ~mathematics();


      virtual ::e_status initialize(::object * pobject) override;
      virtual ::e_status destroy() override;


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
      inline double get_pi() const { return m_dPi; }
      inline float get_pi_f() const { return m_fPi; }

      static bool IsPowerOfTwo(u64 uiValue);
      static u32 ReverseBits(u32 index, u32 NumBits);
      static inline void MaxClip(double * pnClipValue, double nMaxValue);
      static inline void MinClip(double * pnClipValue, double nMinValue);

      i32 RangeRate(i32 iMin, i32 iMax, double dRate);


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


   CLASS_DECL_ACME class mathematics * mathematics();


} // namespace mathematics


