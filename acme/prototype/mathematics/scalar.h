// From template to class by camilo on 2022-11-17 04:35 ILoveYouThomasBorregaardSorensen!!
#pragma once


#include "acme/constant/scalar.h"



//using real = double;
//using integer = long long;

namespace number
{
   class CLASS_DECL_ACME number
   {
   public:

      union
      {

         char        m_ch;
         unsigned char        m_uch;
         short       m_sh;
         unsigned short       m_ush;
         int       m_i;
         unsigned int       m_ui;
         long long       m_hi;
         unsigned long long       m_hn;

         float       m_f;
         double       m_d;

      };

      enum_number    m_enumber;

      number(enum_number enumber = e_number_none) { m_hi = 0; m_enumber = enumber; }
      number(char i) { m_ch = i; m_enumber = e_number_char; }
      number(unsigned char u) { m_uch = u; m_enumber = e_number_unsigned_char; }
      number(short i) { m_sh = i; m_enumber = e_number_short; }
      number(unsigned short u) { m_ush = u; m_enumber = e_number_unsigned_short; }
      number(int i) { m_i = i; m_enumber = e_number_int; }
      number(unsigned int u) { m_ui = u; m_enumber = e_number_unsigned_int; }
      number(long long i) { m_hi = i; m_enumber = e_number_long_long; }
      number(unsigned long long u) { m_hn = u; m_enumber = e_number_unsigned_long_long; }
      number(float f) { m_f = f; m_enumber = e_number_float; }
      number(double d) { m_d = d; m_enumber = e_number_double; }
      //#ifdef __clang__
      //   number(long l) { m_hi = l; m_enumber = e_number_long_long; }
      //#endif


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
            case e_number_char:
               return (T)m_ch;
            case e_number_unsigned_char:
               return(T)m_uch;
            case e_number_short:
               return(T)m_sh;
            case e_number_unsigned_short:
               return (T)m_ush;
            case e_number_int:
               return(T)m_i;
            case e_number_unsigned_int:
               return (T)m_ui;
            case e_number_long_long:
               return(T)m_hi;
            case e_number_unsigned_long_long:
               return (T)m_hn;
            case e_number_float:
               return (T)m_f;
            case e_number_double:
               return(T)m_d;
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
               m_ch = (char) t;
               break;
            case e_number_unsigned_char:
               m_uch = (unsigned char) t;
               break;
            case e_number_short:
               m_sh = (short) t;
               break;
            case e_number_unsigned_short:
               m_ush = (unsigned short)t;
               break;
            case e_number_int:
               m_i = (int)t;
               break;
            case e_number_unsigned_int:
               m_ui = (unsigned int)t;
               break;
            case e_number_long_long:
               m_hi = (long long)t;
               break;
            case e_number_unsigned_long_long:
               m_hn = (unsigned long long)t;
               break;
            case e_number_float:
               m_f = (float)t;
               break;
            case e_number_double:
               m_d = (double)t;
               break;
         };

      }

      char get_char() const { return get < char>(); }
      unsigned char get_unsigned_char() const { return get < unsigned char>(); }
      short get_short() const { return get < short>(); }
      unsigned short get_unsigned_short() const { return get < unsigned short>(); }
      int get_int() const { return get < int>(); }
      unsigned int get_unsigned_int() const { return get < unsigned int>(); }
      long long get_long_long() const { return get < long long>(); }
      unsigned long long get_unsigned_long_long() const { return get < unsigned long long>(); }
      float get_float() const { return get < float>(); }
      double get_double() const { return get < double>(); }


      ::number::number operator + (const number& number) const
      {

         ::number::number numberResult;

         numberResult.m_enumber = maximum(m_enumber, number.m_enumber);

         if (numberResult.is_float())
         {

            numberResult.set(get_double() + number.get_double());

         }
         else if (numberResult.is_integer())
         {

            numberResult.set(get_long_long() + number.get_long_long());

         }

         return numberResult;

      }


      ::number::number operator - (const number& number) const
      {

         ::number::number numberResult;

         numberResult.m_enumber = maximum(m_enumber, number.m_enumber);

         if (numberResult.is_float())
         {

            numberResult.set(get_double() - number.get_double());

         }
         else if (numberResult.is_integer())
         {

            numberResult.set(get_long_long() - number.get_long_long());

         }

         return numberResult;

      }

      ::number::number operator * (const number& number) const
      {

         ::number::number numberResult;

         numberResult.m_enumber = maximum(m_enumber, number.m_enumber);

         if (numberResult.is_float())
         {

            numberResult.set(get_double() * number.get_double());

         }
         else if (numberResult.is_integer())
         {

            numberResult.set(get_long_long() * number.get_long_long());

         }

         return numberResult;

      }


      ::number::number operator / (const number& number) const
      {

         ::number::number numberResult;

         numberResult.m_enumber = maximum(m_enumber, number.m_enumber);

         if (numberResult.is_float())
         {

            numberResult.set(get_double() / number.get_double());

         }
         else if (numberResult.is_integer())
         {

            numberResult.set(get_long_long() / number.get_long_long());

         }

         return numberResult;

      }


      bool operator == (const number& number) const
      {

         auto enumber = maximum(m_enumber, number.m_enumber);

         if (enumber & 64) // float
         {

            return get_double() == number.get_double();

         }
         else if (enumber & 6) // integer
         {

            return get_long_long() == number.get_long_long();

         }

         return false;

      }

      bool operator != (const number& number) const
      {

         auto enumber = maximum(m_enumber, number.m_enumber);

         if (enumber & 64) // float
         {

            return get_double() != number.get_double();

         }
         else if (enumber & 6) // integer
         {

            return get_long_long() != number.get_long_long();

         }

         return false;

      }


      bool operator < (const number& number) const
      {

         auto enumber = maximum(m_enumber, number.m_enumber);

         if (enumber & 64) // float
         {

            return get_double() < number.get_double();

         }
         else if (enumber & 6) // integer
         {

            return get_long_long() < number.get_long_long();

         }

         return false;

      }


      bool operator <= (const number& number) const
      {

         auto enumber = maximum(m_enumber, number.m_enumber);

         if (enumber & 64) // float
         {

            return get_double() <= number.get_double();

         }
         else if (enumber & 6) // integer
         {

            return get_long_long() <= number.get_long_long();

         }

         return false;

      }


      bool operator > (const number& number) const
      {

         auto enumber = maximum(m_enumber, number.m_enumber);

         if (enumber & 64) // float
         {

            return get_double() > number.get_double();

         }
         else if (enumber & 6) // integer
         {

            return get_long_long() > number.get_long_long();

         }

         return false;

      }



      bool operator >= (const number& number) const
      {

         auto enumber = maximum(m_enumber, number.m_enumber);

         if (enumber & 64) // float
         {

            return get_double() >= number.get_double();

         }
         else if (enumber & 6) // integer
         {

            return get_long_long() >= number.get_long_long();

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


//inline string get_default_scalar_format < double >()
//{
//   return "%d";
//}
//
//template <  >
//inline string get_default_scalar_format < long long >()
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


         virtual bool on_set_scalar(scalar_source * pscalar, enum_scalar escalar, ::number::number n, int iFlags);
         // virtual bool on_set_integer_scalar(scalar_source* pscalar, enum_scalar escalar, ::integer i, int iFlags);


      };



      ::pointer_array < listener >     m_scalarlistenera;
      ::atom                           m_atomScalarSource;


      scalar_source();


      bool set_scalar(enum_scalar escalar,::number::number real,bool bForce = false,int iFlags = e_scalar_none);
      bool constrain_scalar(enum_scalar escalar, ::number::number& real);
      void increment_scalar(enum_scalar  escalar, ::number::number real);
      double get_scalar_rate(enum_scalar escalar,double dDefault = 0.0);
      bool set_scalar_rate(enum_scalar escalar,double dValue,int iFlags);
      bool contains_scalar(enum_scalar escalar, ::number::number real);

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


      virtual bool on_set_scalar(enum_scalar escalar, ::number::number integer, int iFlags);
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

      virtual double get_rate(double dDefault = 0.0);

      virtual bool set_rate(double dRate, int iFlags);

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

      scalar& operator ++(int) { increment(); return *this; }
      scalar& operator --(int) { decrement(); return *this; }

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
//   double get_rate(double dDefault = 0.0) override;
//   bool set_rate(double dRate,int iFlags) override;
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
//   real_scalar & operator ++(int) { increment(); return *this; }
//   real_scalar & operator --(int) { decrement(); return *this; }
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
//   virtual string printf(const ::scoped_string & scopedstrFormat);
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
////using double_scalar_manager = scalar_manager < double >;
////using int_scalar_manager  = scalar_manager < long long >;
//
////using double_scalar_listener = scalar_manager < double >::listener;
////using int_scalar_listener  = scalar_manager < long long >::listener;
//
//
////using double_scalar = scalar < double >;
////using int_scalar  = scalar < long long >;
//
//
//
