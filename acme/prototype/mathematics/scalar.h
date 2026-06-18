// From template to class by camilo on 2022-11-17 04:35 ILoveYouThomasBorregaardSorensen!!
#pragma once


#include "acme/constant/scalar.h"



//using real = ::f64;
//using integer = ::i64;

namespace number
{
   class CLASS_DECL_ACME number
   {
   public:

      union
      {

         ::i8        m_i8;
         ::u8        m_u8;
         ::i16       m_i16;
         ::u16       m_u16;
         ::i32       m_i32;
         ::u32       m_u32;
         ::i64       m_hi;
         ::u64       m_hn;

         ::f32       m_f32;
         ::f64       m_f64;

      };

      enum_number    m_enumber;

      number(enum_number enumber = e_number_none) { m_hi = 0; m_enumber = enumber; }
      number(::i8 i) { m_i8 = i; m_enumber = e_number_char; }
      number(::u8 u) { m_u8 = u; m_enumber = e_number_unsigned_char; }
      number(::i16 i) { m_i16 = i; m_enumber = e_number_short; }
      number(::u16 u) { m_u16 = u; m_enumber = e_number_unsigned_short; }
      number(::i32 i) { m_i32 = i; m_enumber = e_number_int; }
      number(::u32 u) { m_u32 = u; m_enumber = e_number_u32; }
      number(::i64 i) { m_hi = i; m_enumber = e_number_i64; }
      number(::u64 u) { m_hn = u; m_enumber = e_number_u64; }
      number(::f32 f) { m_f32 = f; m_enumber = e_number_f32; }
      number(::f64 d) { m_f64 = d; m_enumber = e_number_f64; }
      //#ifdef __clang__
      //   number(long l) { m_hi = l; m_enumber = e_number_i64; }
      //#endif


      bool ok() const { return m_enumber != e_number_none; }
      bool nok() const { return !ok(); }
      bool is_f32() const { return m_enumber & 16; }
      bool is_integer() const { return m_enumber & 6; }
      bool is_signed() const { return m_enumber & 2; }
      bool is_unsigned() const { return m_enumber & 4; }

      template < typename T >
      T get() const
      {
         switch (m_enumber)
         {
            case e_number_none:
               return (T)0;
            case e_number_char:
               return (T)m_i8;
            case e_number_unsigned_char:
               return(T)m_u8;
            case e_number_short:
               return(T)m_i16;
            case e_number_unsigned_short:
               return (T)m_u16;
            case e_number_int:
               return(T)m_i32;
            case e_number_u32:
               return (T)m_u32;
            case e_number_i64:
               return(T)m_hi;
            case e_number_u64:
               return (T)m_hn;
            case e_number_f32:
               return (T)m_f32;
            case e_number_f64:
               return(T)m_f64;
         };
         return (T)0;
      }


      template < typename T >
      void set(T t)
      {
         switch (m_enumber)
         {
            case e_number_none:
               break;
            case e_number_char:
               m_i8 = (::i8) t;
               break;
            case e_number_unsigned_char:
               m_u8 = (::u8) t;
               break;
            case e_number_short:
               m_i16 = (::i16) t;
               break;
            case e_number_unsigned_short:
               m_u16 = (::u16)t;
               break;
            case e_number_int:
               m_i32 = (::i32)t;
               break;
            case e_number_u32:
               m_u32 = (::u32)t;
               break;
            case e_number_i64:
               m_hi = (::i64)t;
               break;
            case e_number_u64:
               m_hn = (::u64)t;
               break;
            case e_number_f32:
               m_f32 = (::f32)t;
               break;
            case e_number_f64:
               m_f64 = (::f64)t;
               break;
         };

      }

      ::i8 get_char() const { return get < ::i8>(); }
      ::u8 get_unsigned_char() const { return get < ::u8>(); }
      ::i16 get_short() const { return get < ::i16>(); }
      ::u16 get_unsigned_short() const { return get < ::u16>(); }
      ::i32 get_int() const { return get < ::i32>(); }
      ::u32 get_u32() const { return get < ::u32>(); }
      ::i64 get_i64() const { return get < ::i64>(); }
      ::u64 get_u64() const { return get < ::u64>(); }
      ::f32 get_f32() const { return get < ::f32>(); }
      ::f64 get_f64() const { return get < ::f64>(); }


      ::number::number operator + (const number& number) const
      {

         ::number::number numberResult;

         numberResult.m_enumber = maximum(m_enumber, number.m_enumber);

         if (numberResult.is_f32())
         {

            numberResult.set(get_f64() + number.get_f64());

         }
         else if (numberResult.is_integer())
         {

            numberResult.set(get_i64() + number.get_i64());

         }

         return numberResult;

      }


      ::number::number operator - (const number& number) const
      {

         ::number::number numberResult;

         numberResult.m_enumber = maximum(m_enumber, number.m_enumber);

         if (numberResult.is_f32())
         {

            numberResult.set(get_f64() - number.get_f64());

         }
         else if (numberResult.is_integer())
         {

            numberResult.set(get_i64() - number.get_i64());

         }

         return numberResult;

      }

      ::number::number operator * (const number& number) const
      {

         ::number::number numberResult;

         numberResult.m_enumber = maximum(m_enumber, number.m_enumber);

         if (numberResult.is_f32())
         {

            numberResult.set(get_f64() * number.get_f64());

         }
         else if (numberResult.is_integer())
         {

            numberResult.set(get_i64() * number.get_i64());

         }

         return numberResult;

      }


      ::number::number operator / (const number& number) const
      {

         ::number::number numberResult;

         numberResult.m_enumber = maximum(m_enumber, number.m_enumber);

         if (numberResult.is_f32())
         {

            numberResult.set(get_f64() / number.get_f64());

         }
         else if (numberResult.is_integer())
         {

            numberResult.set(get_i64() / number.get_i64());

         }

         return numberResult;

      }


      bool operator == (const number& number) const
      {

         auto enumber = maximum(m_enumber, number.m_enumber);

         if (enumber & 64) // ::f32
         {

            return get_f64() == number.get_f64();

         }
         else if (enumber & 6) // integer
         {

            return get_i64() == number.get_i64();

         }

         return false;

      }

      bool operator != (const number& number) const
      {

         auto enumber = maximum(m_enumber, number.m_enumber);

         if (enumber & 64) // ::f32
         {

            return get_f64() != number.get_f64();

         }
         else if (enumber & 6) // integer
         {

            return get_i64() != number.get_i64();

         }

         return false;

      }


      bool operator < (const number& number) const
      {

         auto enumber = maximum(m_enumber, number.m_enumber);

         if (enumber & 64) // ::f32
         {

            return get_f64() < number.get_f64();

         }
         else if (enumber & 6) // integer
         {

            return get_i64() < number.get_i64();

         }

         return false;

      }


      bool operator <= (const number& number) const
      {

         auto enumber = maximum(m_enumber, number.m_enumber);

         if (enumber & 64) // ::f32
         {

            return get_f64() <= number.get_f64();

         }
         else if (enumber & 6) // integer
         {

            return get_i64() <= number.get_i64();

         }

         return false;

      }


      bool operator > (const number& number) const
      {

         auto enumber = maximum(m_enumber, number.m_enumber);

         if (enumber & 64) // ::f32
         {

            return get_f64() > number.get_f64();

         }
         else if (enumber & 6) // integer
         {

            return get_i64() > number.get_i64();

         }

         return false;

      }



      bool operator >= (const number& number) const
      {

         auto enumber = maximum(m_enumber, number.m_enumber);

         if (enumber & 64) // ::f32
         {

            return get_f64() >= number.get_f64();

         }
         else if (enumber & 6) // integer
         {

            return get_i64() >= number.get_i64();

         }

         return false;

      }

   };

} // namespace number



inline string get_default_real_scalar_format()
{
   return "%f";
}

inline string get_default_integer_scalar_format()
{
   return "%lld";
}


//inline string get_default_scalar_format < ::f64 >()
//{
//   return "%d";
//}
//
//template <  >
//inline string get_default_scalar_format < ::i64 >()
//{
//   return "%lli";
//}
//
//namespace str
//{
//
//   template < typename FORMATABLE >
//   inline string printf(const ::scoped_string & scopedstrFormat, const FORMATABLE & f)
//   {
//
//      string str;
//
//      str.formatf(strFormat,f);
//
//      return str;
//
//   }
//
//
//} // namespace str



#include "acme/prototype/prototype/atom.h"

namespace  number
{
   class CLASS_DECL_ACME scalar_source :
      virtual public particle
   {
   public:


      class CLASS_DECL_ACME listener :
         virtual public particle
      {
      public:


         virtual bool on_set_scalar(scalar_source * pscalar, enum_scalar escalar, ::number::number n, ::i32 iFlags);
         // virtual bool on_set_integer_scalar(scalar_source* pscalar, enum_scalar escalar, ::integer i, ::i32 iFlags);


      };



      ::pointer_array < listener >     m_scalarlistenera;
      ::atom                           m_atomScalarSource;


      scalar_source();


      bool set_scalar(enum_scalar escalar,::number::number real,bool bForce = false,::i32 iFlags = e_scalar_none);
      bool constrain_scalar(enum_scalar escalar, ::number::number& real);
      void increment_scalar(enum_scalar  escalar, ::number::number real);
      ::f64 get_scalar_rate(enum_scalar escalar,::f64 dDefault = 0.0);
      bool set_scalar_rate(enum_scalar escalar,::f64 dValue,::i32 iFlags);
      bool contains_scalar(enum_scalar escalar, ::number::number real);

      //bool set_integer_scalar(enum_scalar escalar, ::integer integer, bool bForce = false, ::i32 iFlags = e_scalar_none);
      //bool constrain_integer_scalar(enum_scalar escalar, ::integer& integer);
      //void increment_integer_scalar(enum_scalar  escalar, ::integer iIncintegerrement);
      //::f64 get_integer_scalar_rate(enum_scalar escalar, ::f64 dDefault = 0.0);
      //bool set_integer_scalar_rate(enum_scalar escalar, ::f64 dValue, ::i32 iFlags);
      //bool contains_integer_scalar(enum_scalar escalar, ::integer integer);


      //virtual bool on_set_real_scalar(enum_scalar escalar, ::real real, ::i32 iFlags);
      //virtual bool get_real_scalar_minimum(enum_scalar escalar, ::real& real);
      //virtual bool get_real_scalar(enum_scalar escalar, ::real& real);
      //virtual bool get_real_scalar_maximum(enum_scalar escalar, ::real& real);


      virtual bool on_set_scalar(enum_scalar escalar, ::number::number integer, ::i32 iFlags);
      virtual ::number::number get_scalar_minimum(enum_scalar escalar);
      virtual ::number::number get_scalar(enum_scalar escalar);
      virtual ::number::number get_scalar_maximum(enum_scalar escalar);



   };





   class CLASS_DECL_ACME scalar :
      virtual public ::particle
   {
   public:



      ::pointer < scalar_source >         m_psource;
      //string                              m_strFormat;
      enum_scalar                         m_escalar;
      //enum_number                         m_enumber;

      scalar(scalar_source* psource = nullptr, enum_scalar ereal_scalar = e_scalar_none);

      virtual ::f64 get_rate(::f64 dDefault = 0.0);

      virtual bool set_rate(::f64 dRate, ::i32 iFlags);

      //string Format(const ::scoped_string & scopedstrFormat);

      //string to_string() { return Format(m_strFormat); }
      bool is_null() const { return m_psource == nullptr || m_escalar == e_scalar_none; }
      bool is_set() const { return !is_null(); }

      void set(::number::number dValue);
      ::number::number get() const;


      scalar& operator = (::number::number dValue) { set(dValue); return *this; }
      scalar & operator = (const ::number::scalar & scalar) { set(scalar.get()); return *this; }

      number maximum();
      number minimum();

      //virtual string printf(const ::scoped_string & scopedstrFormat);

      void increment(number number = 1) { set(get() + number); }
      void decrement(number number = 1) { set(get() - number); }

      scalar& operator ++(::i32) { increment(); return *this; }
      scalar& operator --(::i32) { decrement(); return *this; }

   };
} // namespace number


//class CLASS_DECL_ACME real_scalar :
//   virtual public scalar_base
//{
//public:
//
//
//   real_scalar(scalar_source * psource = nullptr,enum_scalar ereal_scalar = e_scalar_none,const ::scoped_string & scopedstrFormat = ::get_default_real_scalar_format());
//
//
//   void set(::real dValue);
//   ::real get();
//
//   
//   ::f64 get_rate(::f64 dDefault = 0.0) override;
//   bool set_rate(::f64 dRate,::i32 iFlags) override;
//
//
//   ::real maximum();
//   ::real minimum();
//   operator ::real () { return get(); }
//
//   real_scalar & operator = (::real dValue) { set(dValue); return *this; }
//
//   virtual string printf(const ::scoped_string & scopedstrFormat);
//
//   void increment(::real iValue = ::numeric_info<::real>::unitary()) { set(get() + iValue); }
//   void decrement(::real iValue = ::numeric_info<::real>::unitary()) { set(get() - iValue); }
//
//   real_scalar & operator ++(::i32) { increment(); return *this; }
//   real_scalar & operator --(::i32) { decrement(); return *this; }
//
//
//};
//class CLASS_DECL_ACME integer_scalar :
//   virtual public scalar_base
//{
//public:
//
//
//   integer_scalar(scalar_source* psource = nullptr, enum_scalar einteger_scalar = e_scalar_none, const ::scoped_string & scopedstrFormat = ::get_default_integer_scalar_format());
//
//
//   void set(::integer dValue);
//   ::integer get();
//
//   ::f64 get_rate(::f64 dDefault = 0.0) override;
//   bool set_rate(::f64 dRate, ::i32 iFlags) override;
//
//
//   ::integer maximum();
//   ::integer minimum();
//
//
//
//   operator ::integer () { return get(); }
//
//   integer_scalar& operator = (::integer dValue) { set(dValue); return *this; }
//
//   virtual string printf(const ::scoped_string & scopedstrFormat);
//
//   void increment(::integer iValue = ::numeric_info<::integer>::unitary()) { set(get() + iValue); }
//   void decrement(::integer iValue = ::numeric_info<::integer>::unitary()) { set(get() - iValue); }
//
//   integer_scalar& operator ++(::i32) { increment(); return *this; }
//   integer_scalar& operator --(::i32) { decrement(); return *this; }
//
//
//};
//
//
//
////using f64_scalar_manager = scalar_manager < ::f64 >;
////using i32_scalar_manager  = scalar_manager < ::i64 >;
//
////using f64_scalar_listener = scalar_manager < ::f64 >::listener;
////using i32_scalar_listener  = scalar_manager < ::i64 >::listener;
//
//
////using f64_scalar = scalar < ::f64 >;
////using i32_scalar  = scalar < ::i64 >;
//
//
//
