// Created by camilo on 2023-02-07 20:55 BRT <3ThomasBorregaardSorensen!!
#pragma once


template < typename ENUM >
class unit_base
{
protected:


   union
   {

      double m_d;

      long long m_hi;

   };


   ENUM        m_eunit;
   bool        m_bFloating : 1;


public:


   constexpr unit_base() 
   {
      m_hi = 0; 
      m_eunit = (ENUM)0; 
      m_bFloating = false; 
   }

   template < prototype_integral INTEGRAL >
   constexpr unit_base(INTEGRAL i, ENUM eunit)
   {
      m_hi = (long long)i;
      m_eunit = eunit; 
      clear_floating();
   }

   template < prototype_floating FLOATING >
   constexpr unit_base(FLOATING f, ENUM eunit)
   {
      m_d = (double)f; 
      m_eunit = eunit; 
      set_floating(); 
   }

   template < prototype_floating FLOATING >
   constexpr unit_base(FLOATING f) 
   {
      m_d = (double)f;
      m_eunit = rate_unit(); 
      set_floating();
   }

   constexpr unit_base(const unit_base & unit): 
      m_hi(unit.m_hi),
      m_eunit(unit.m_eunit),
      m_bFloating(unit.m_bFloating)
   { }


   constexpr bool is_rate()const { return m_eunit == rate_unit(); }
   constexpr bool is_floating()const { return m_bFloating; }
   constexpr void set_floating() {  m_bFloating = true; }
   constexpr void clear_floating() { m_bFloating = false; }

   constexpr long long as_long_long() const { return is_floating() ? (long long)m_d : m_hi; }
   constexpr double as_double() const { return is_floating() ? m_d : (double)m_hi; }
   constexpr int as_int() const { return (int) this->as_long_long(); }
   constexpr float as_float() const { return (float) this->as_double(); }
   constexpr ENUM eunit() const { return m_eunit; }

   constexpr bool is_null_or_negative() { return is_floating() ? m_d <= 0.0 : m_hi <= 0; }
   constexpr bool is_negative() { return is_floating() ? m_d < 0.0 : m_hi < 0; }
   constexpr bool is_null_or_positive() { return is_floating() ? m_d >= 0.0 : m_hi >= 0; }
   constexpr bool is_positive() { return is_floating() ? m_d > 0.0 : m_hi > 0; }

//   constexpr operator long long()const { return long_long; }
//   constexpr operator double() const { return double(); }
//   constexpr operator ENUM() const { return eunit(); }

   //template < prototype_integral INTEGRAL >
   //constexpr unit_base & operator = (INTEGRAL i) { m_hi = (long long)i; clear_floating(); return *this; }

   
   bool operator ==(const unit_base & unit) const
   {
      
      return m_hi == unit.m_hi && m_eunit == unit.m_eunit;
      
   }
   
   template < prototype_floating FLOATING >
   constexpr unit_base & operator = (FLOATING f)
   { 
      
      m_d = (double)f; 
      
      m_eunit = rate_unit(); 

      set_floating();

      return *this;
   
   }

   
   constexpr unit_base & operator = (const unit_base & unit) 
   {
      
      m_hi = unit.m_hi; 

      m_eunit = unit.m_eunit; 

      m_bFloating = unit.m_bFloating;

      return *this;
   
   }

   
   //constexpr ENUM raw_unit() const { return (ENUM) (m_eunit & ~INT_MIN); }
   //constexpr ENUM floating_unit() const { return (ENUM)(m_eunit & INT_MIN); }
   
   
   constexpr static ENUM rate_unit() { return (ENUM)-1; }

   
   constexpr void set_unit(ENUM eunit) { m_eunit = eunit; }
   

   template < prototype_floating FLOATING >
   unit_base & operator *= (FLOATING f)
   {

      m_d = this->as_double() * f;

      set_floating();

      return *this;

   }
   
   
   template < prototype_floating FLOATING >
   unit_base & operator /= (FLOATING f)
   {

      m_d = this->as_double() / f;

      set_floating();

      return *this;

   }
   

   template < prototype_floating FLOATING >
   unit_base operator * (FLOATING f) const
   {

      unit_base < ENUM > unitResult(this->as_double() * f, this->eunit());

      return unitResult;

   }
   
   
   template < prototype_floating FLOATING >
   unit_base operator / (FLOATING f) const
   {

      unit_base < ENUM > unitResult(this->as_double() / f, this->eunit());

      return *this;

   }


};


template < prototype_floating FLOATING, typename ENUM >
inline unit_base < ENUM > operator * (FLOATING f, const unit_base < ENUM > & unit)
{

   unit_base < ENUM > unitResult(unit.as_double() * f, unit.eunit());

   return unitResult;

}

using unit = unit_base < enum_unit >;

template < prototype_number NUMBER >
constexpr auto pixel_unit(NUMBER n)
{

   return unit(n, e_unit_pixel);

}


constexpr auto operator ""_px(unsigned long long i)
{

   return pixel_unit(i);

}


constexpr auto operator ""_px(long double d)
{

   return pixel_unit(d);

}


//struct point_unit_t {};

//template < prototype_number NUMBER >
//constexpr auto operator *(NUMBER n, point_unit_t) { return unit(n, e_unit_point); }


template < prototype_number NUMBER >
constexpr auto point_unit(NUMBER n)
{
 
   return unit(n, e_unit_point);

}


constexpr auto operator ""_pt(unsigned long long i)
{

   return point_unit(i);

}


constexpr auto operator ""_pt(long double d)
{

   return point_unit(d);

}



