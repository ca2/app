// From template to class by camilo on 2022-11-17 04:35 ILoveYouThomasBorregaardSorensen!!
#pragma once


#include "acme/constant/scalar.h"
#include "acme/primitive/string/string.h"


//using real = ::f64;
//using integer = ::i64;

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
      ::i64       m_i64;
      ::u64       m_u64;

      ::f32       m_f32;
      ::f64       m_f64;

   };

   enum_number    m_enumber;

   number(enum_number enumber = e_number_none) { m_i64 = 0; m_enumber = enumber; }
   number(i8 i) { m_i8 = i; m_enumber = e_number_i8; }
   number(u8 u) { m_u8 = u; m_enumber = e_number_u8; }
   number(i16 i) { m_i16 = i; m_enumber = e_number_i16; }
   number(u16 u) { m_u16 = u; m_enumber = e_number_u16; }
   number(i32 i) { m_i32 = i; m_enumber = e_number_i32; }
   number(u32 u) { m_u32 = u; m_enumber = e_number_u32; }
   number(i64 i) { m_i64 = i; m_enumber = e_number_i64; }
   number(u64 u) { m_u64 = u; m_enumber = e_number_u64; }
   number(f32 f) { m_f32 = f; m_enumber = e_number_f32; }
   number(f64 d) { m_f64 = d; m_enumber = e_number_f64; }


   bool ok() const { return m_enumber != e_number_none; }
   bool nok() const { return !ok(); }
   bool is_float() const { return m_enumber & 16; }
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
      case e_number_i8:
         return (T)m_i8;
      case e_number_u8:
         return(T)m_u8;
      case e_number_i16:
         return(T)m_i16;
      case e_number_u16:
         return (T)m_u16;
      case e_number_i32:
         return(T)m_i32;
      case e_number_u32:
         return (T)m_u32;
      case e_number_i64:
         return(T)m_i64;
      case e_number_u64:
         return (T)m_u64;
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
      case e_number_i8:
         m_i8 = (::i8) t;
         break;
      case e_number_u8:
         m_u8 = (::u8) t;
         break;
      case e_number_i16:
         m_i16 = (::i16) t;
         break;
      case e_number_u16:
         m_u16 = (::u16)t;
         break;
      case e_number_i32:
         m_i32 = (::i32)t;
         break;
      case e_number_u32:
         m_u32 = (::u32)t;
         break;
      case e_number_i64:
         m_i64 = (::i64)t;
         break;
      case e_number_u64:
         m_u64 = (::u64)t;
         break;
      case e_number_f32:
         m_f32 = (::f32)t;
         break;
      case e_number_f64:
         m_f64 = (::f64)t;
         break;
      };

   }

   ::i8 get_i8() const { return get < ::i8>(); }
   ::u8 get_u8() const { return get < ::u8>(); }
   ::i16 get_i16() const { return get < ::i16>(); }
   ::u16 get_u16() const { return get < ::u16>(); }
   ::i32 get_i32() const { return get < ::i32>(); }
   ::u32 get_u32() const { return get < ::u32>(); }
   ::i64 get_i64() const { return get < ::i64>(); }
   ::u64 get_u64() const { return get < ::u64>(); }
   ::f32 get_f32() const { return get < ::f32>(); }
   ::f64 get_f64() const { return get < ::f64>(); }


   ::number operator + (const number& number) const
   {

      ::number numberResult;

      numberResult.m_enumber = maximum(m_enumber, number.m_enumber);

      if (numberResult.is_float())
      {

         numberResult.set(get_f64() + number.get_f64());

      }
      else if (numberResult.is_integer())
      {

         numberResult.set(get_i64() + number.get_i64());

      }

      return numberResult;

   }


   ::number operator - (const number& number) const
   {

      ::number numberResult;

      numberResult.m_enumber = maximum(m_enumber, number.m_enumber);

      if (numberResult.is_float())
      {

         numberResult.set(get_f64() - number.get_f64());

      }
      else if (numberResult.is_integer())
      {

         numberResult.set(get_i64() - number.get_i64());

      }

      return numberResult;

   }

   ::number operator * (const number& number) const
   {

      ::number numberResult;

      numberResult.m_enumber = maximum(m_enumber, number.m_enumber);

      if (numberResult.is_float())
      {

         numberResult.set(get_f64() * number.get_f64());

      }
      else if (numberResult.is_integer())
      {

         numberResult.set(get_i64() * number.get_i64());

      }

      return numberResult;

   }


   ::number operator / (const number& number) const
   {

      ::number numberResult;

      numberResult.m_enumber = maximum(m_enumber, number.m_enumber);

      if (numberResult.is_float())
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

      if (enumber & 64) // float
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

      if (enumber & 64) // float
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

      if (enumber & 64) // float
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

      if (enumber & 64) // float
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

      if (enumber & 64) // float
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

      if (enumber & 64) // float
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


inline string get_default_real_scalar_format()
{
   return "%f";
}

inline string get_default_integer_scalar_format()
{
   return "%lld";
}


//inline string get_default_scalar_format < double >()
//{
//   return "%d";
//}
//
//template <  >
//inline string get_default_scalar_format < i64 >()
//{
//   return "%lli";
//}
//
//namespace str
//{
//
//   template < typename FORMATABLE >
//   inline string printf(const ::string & strFormat, const FORMATABLE & f)
//   {
//
//      string str;
//
//      str.format(strFormat,f);
//
//      return str;
//
//   }
//
//
//} // namespace str


#include "acme/primitive/primitive/particle.h"
#include "acme/primitive/primitive/atom.h"


class CLASS_DECL_ACME scalar_source :
   virtual public particle
{
public:


   class CLASS_DECL_ACME listener :
      virtual public particle
   {
   public:


      virtual bool on_set_scalar(scalar_source * pscalar, enum_scalar escalar, ::number n, int iFlags);
      // virtual bool on_set_integer_scalar(scalar_source* pscalar, enum_scalar escalar, ::integer i, int iFlags);


   };



   ::pointer_array < listener >     m_scalarlistenera;
   ::atom                           m_atomScalarSource;


   scalar_source();


   bool set_scalar(enum_scalar escalar,::number real,bool bForce = false,int iFlags = e_scalar_none);
   bool constrain_scalar(enum_scalar escalar, ::number& real);
   void increment_scalar(enum_scalar  escalar, ::number real);
   double get_scalar_rate(enum_scalar escalar,double dDefault = 0.0);
   bool set_scalar_rate(enum_scalar escalar,double dValue,int iFlags);
   bool contains_scalar(enum_scalar escalar, ::number real);

   //bool set_integer_scalar(enum_scalar escalar, ::integer integer, bool bForce = false, int iFlags = e_scalar_none);
   //bool constrain_integer_scalar(enum_scalar escalar, ::integer& integer);
   //void increment_integer_scalar(enum_scalar  escalar, ::integer iIncintegerrement);
   //double get_integer_scalar_rate(enum_scalar escalar, double dDefault = 0.0);
   //bool set_integer_scalar_rate(enum_scalar escalar, double dValue, int iFlags);
   //bool contains_integer_scalar(enum_scalar escalar, ::integer integer);


   //virtual bool on_set_real_scalar(enum_scalar escalar, ::real real, int iFlags);
   //virtual bool get_real_scalar_minimum(enum_scalar escalar, ::real& real);
   //virtual bool get_real_scalar(enum_scalar escalar, ::real& real);
   //virtual bool get_real_scalar_maximum(enum_scalar escalar, ::real& real);

   
   virtual bool on_set_scalar(enum_scalar escalar, ::number integer, int iFlags);
   virtual ::number get_scalar_minimum(enum_scalar escalar);
   virtual ::number get_scalar(enum_scalar escalar);
   virtual ::number get_scalar_maximum(enum_scalar escalar);



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

   virtual double get_rate(double dDefault = 0.0);

   virtual bool set_rate(double dRate, int iFlags);

   //string Format(const ::string & strFormat);

   //string to_string() { return Format(m_strFormat); }
   bool is_null() const { return m_psource == nullptr || m_escalar == e_scalar_none; }
   bool is_set() const { return !is_null(); }

   void set(::number dValue);
   ::number get();


   scalar& operator = (::number dValue) { set(dValue); return *this; }

   number maximum();
   number minimum();

   //virtual string printf(const ::string& strFormat);

   void increment(number number = 1) { set(get() + number); }
   void decrement(number number = 1) { set(get() - number); }

   scalar& operator ++(int) { increment(); return *this; }
   scalar& operator --(int) { decrement(); return *this; }

};


//class CLASS_DECL_ACME real_scalar :
//   virtual public scalar_base
//{
//public:
//
//
//   real_scalar(scalar_source * psource = nullptr,enum_scalar ereal_scalar = e_scalar_none,const ::string & strFormat = ::get_default_real_scalar_format());
//
//
//   void set(::real dValue);
//   ::real get();
//
//   
//   double get_rate(double dDefault = 0.0) override;
//   bool set_rate(double dRate,int iFlags) override;
//
//
//   ::real maximum();
//   ::real minimum();
//
//
//
//
//   operator ::real () { return get(); }
//
//   real_scalar & operator = (::real dValue) { set(dValue); return *this; }
//
//   virtual string printf(const ::string & strFormat);
//
//   void increment(::real iValue = ::numeric_info<::real>::unitary()) { set(get() + iValue); }
//   void decrement(::real iValue = ::numeric_info<::real>::unitary()) { set(get() - iValue); }
//
//   real_scalar & operator ++(int) { increment(); return *this; }
//   real_scalar & operator --(int) { decrement(); return *this; }
//
//
//};
//
//
//
//
//class CLASS_DECL_ACME integer_scalar :
//   virtual public scalar_base
//{
//public:
//
//
//   integer_scalar(scalar_source* psource = nullptr, enum_scalar einteger_scalar = e_scalar_none, const ::string& strFormat = ::get_default_integer_scalar_format());
//
//
//   void set(::integer dValue);
//   ::integer get();
//
//   double get_rate(double dDefault = 0.0) override;
//   bool set_rate(double dRate, int iFlags) override;
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
//   virtual string printf(const ::string& strFormat);
//
//   void increment(::integer iValue = ::numeric_info<::integer>::unitary()) { set(get() + iValue); }
//   void decrement(::integer iValue = ::numeric_info<::integer>::unitary()) { set(get() - iValue); }
//
//   integer_scalar& operator ++(int) { increment(); return *this; }
//   integer_scalar& operator --(int) { decrement(); return *this; }
//
//
//};
//
//
//
//
//
//
//
////using double_scalar_manager = scalar_manager < double >;
////using int_scalar_manager  = scalar_manager < i64 >;
//
////using double_scalar_listener = scalar_manager < double >::listener;
////using int_scalar_listener  = scalar_manager < i64 >::listener;
//
//
////using double_scalar = scalar < double >;
////using int_scalar  = scalar < i64 >;
//
//
//
