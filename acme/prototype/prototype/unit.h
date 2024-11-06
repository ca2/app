// Created by camilo on 2023-02-07 20:55 BRT <3ThomasBorregaardSorensen!!
#pragma once


template < typename ENUM >
class unit_base
{
protected:


   union
   {

      double m_d;

      ::i64 m_i64;

   };


   ENUM        m_eunit;
   bool        m_bFloating : 1;


public:


   constexpr unit_base() 
   {
      m_i64 = 0; 
      m_eunit = (ENUM)0; 
      m_bFloating = false; 
   }

   template < primitive_integral INTEGRAL >
   constexpr unit_base(INTEGRAL i, ENUM eunit)
   {
      m_i64 = (::i64)i;
      m_eunit = eunit; 
      clear_floating();
   }

   template < primitive_floating FLOATING >
   constexpr unit_base(FLOATING f, ENUM eunit)
   {
      m_d = (double)f; 
      m_eunit = eunit; 
      set_floating(); 
   }

   template < primitive_floating FLOATING >
   constexpr unit_base(FLOATING f) 
   {
      m_d = (double)f;
      m_eunit = rate_unit(); 
      set_floating();
   }

   constexpr unit_base(const unit_base & unit): 
      m_i64(unit.m_i64),
      m_eunit(unit.m_eunit),
      m_bFloating(unit.m_bFloating)
   { }


   constexpr bool is_rate()const { return m_eunit == rate_unit(); }
   constexpr bool is_floating()const { return m_bFloating; }
   constexpr void set_floating() {  m_bFloating = true; }
   constexpr void clear_floating() { m_bFloating = false; }

   constexpr ::i64 as_i64() const { return is_floating() ? (::i64)m_d : m_i64; }
   constexpr double as_double() const { return is_floating() ? m_d : (double)m_i64; }
   constexpr int as_int() const { return (int) this->as_i64(); }
   constexpr float as_float() const { return (float) this->as_double(); }
   constexpr ENUM eunit() const { return m_eunit; }

   constexpr bool is_null_or_negative() { return is_floating() ? m_d <= 0.0 : m_i64 <= 0; }
   constexpr bool is_negative() { return is_floating() ? m_d < 0.0 : m_i64 < 0; }
   constexpr bool is_null_or_positive() { return is_floating() ? m_d >= 0.0 : m_i64 >= 0; }
   constexpr bool is_positive() { return is_floating() ? m_d > 0.0 : m_i64 > 0; }

//   constexpr operator ::i64() const { return i64(); }
//   constexpr operator double() const { return double(); }
//   constexpr operator ENUM() const { return eunit(); }

   //template < primitive_integral INTEGRAL >
   //constexpr unit_base & operator = (INTEGRAL i) { m_i64 = (::i64)i; clear_floating(); return *this; }

   
   bool operator ==(const unit_base & unit) const
   {
      
      return m_i64 == unit.m_i64 && m_eunit == unit.m_eunit;
      
   }
   
   template < primitive_floating FLOATING >
   constexpr unit_base & operator = (FLOATING f)
   { 
      
      m_d = (double)f; 
      
      m_eunit = rate_unit(); 

      set_floating();

      return *this;
   
   }

   
   constexpr unit_base & operator = (const unit_base & unit) 
   {
      
      m_i64 = unit.m_i64; 

      m_eunit = unit.m_eunit; 

      m_bFloating = unit.m_bFloating;

      return *this;
   
   }

   
   //constexpr ENUM raw_unit() const { return (ENUM) (m_eunit & ~INT_MIN); }
   //constexpr ENUM floating_unit() const { return (ENUM)(m_eunit & INT_MIN); }
   
   
   constexpr static ENUM rate_unit() { return (ENUM)-1; }

   
   constexpr void set_unit(ENUM eunit) { m_eunit = eunit; }
   

   template < primitive_floating FLOATING >
   unit_base & operator *= (FLOATING f)
   {

      m_d = this->double() * f;

      set_floating();

      return *this;

   }
   
   
   template < primitive_floating FLOATING >
   unit_base & operator /= (FLOATING f)
   {

      m_d = this->as_double() / f;

      set_floating();

      return *this;

   }
   

   template < primitive_floating FLOATING >
   unit_base operator * (FLOATING f) const
   {

      unit_base < ENUM > unitResult(this->as_double() * f, this->eunit());

      return unitResult;

   }
   
   
   template < primitive_floating FLOATING >
   unit_base operator / (FLOATING f) const
   {

      unit_base < ENUM > unitResult(this->as_double() / f, this->eunit());

      return *this;

   }


};


template < primitive_floating FLOATING, typename ENUM >
inline unit_base < ENUM > operator * (FLOATING f, const unit_base < ENUM > & unit)
{

   unit_base < ENUM > unitResult(unit.as_double() * f, unit.eunit());

   return unitResult;

}

struct pixel_t {};

template < primitive_number NUMBER >
constexpr auto operator *(NUMBER n, pixel_t) { return unit(n, e_unit_pixel); }

using unit = unit_base < enum_unit >;

constexpr auto operator ""_px(unsigned long long i)
{

   return unit(i, e_unit_pixel);

}


constexpr auto operator ""_px(long double d)
{

   return unit(d, e_unit_pixel);

}


struct point_t {};

template < primitive_number NUMBER >
constexpr auto operator *(NUMBER n, point_t) { return unit(n, e_unit_point); }


constexpr auto operator ""_pt(unsigned long long i)
{

   return unit(i, e_unit_point);

}


constexpr auto operator ""_pt(long double d)
{

   return unit(d, e_unit_point);

}



