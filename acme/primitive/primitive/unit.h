// Created by camilo on 2023-02-07 20:55 BRT <3ThomasBorregaardSorensen!!
#pragma once

#pragma warning( disable : 4455) // literal suffix identifiers that do not start with an underscore are reserved


constexpr long double operator "" η(long double d)
{

   return d / (1'000.0 * 1'000.0 * 1'000.0);

}


constexpr unsigned long long int operator "" η(unsigned long long int i)
{

   return i / (1'000 * 1'000 * 1'000);

}


constexpr long double operator "" μ(long double d)
{

   return d / (1'000.0 * 1'000.0);

}


constexpr unsigned long long int operator "" μ(unsigned long long int i)
{

   return i / (1'000 * 1'000);

}


constexpr long double operator ""m(long double d)
{

   return d / 1'000.0;

}


constexpr unsigned long long operator "" m(unsigned long long i)
{

   return i / 1'000;

}


class integral_byte
{
public:


   memsize m_memsize;


   constexpr integral_byte(memsize memsize = 1) :
      m_memsize(memsize)
   {


   }

   operator memsize() const { return m_memsize; }


};


constexpr integral_byte operator ""KiB(long double d)
{

   return (memsize) (1024.0 * d);

}


constexpr integral_byte operator ""KiB(unsigned long long i)
{

   return (memsize) (i << 10);

}


constexpr long double operator ""k(long double d)
{

   return 1000.0 * d;

}


constexpr unsigned long long operator ""k(unsigned long long i)
{

   return 1'000 * i;

}


constexpr integral_byte operator ""MiB(long double d)
{

   return (memsize)(1024.0 * 1024.0 * d);

}


constexpr integral_byte operator ""MiB(unsigned long long i)
{

   return (memsize)(i << 20);

}


constexpr long double operator ""M(long double d)
{

   return 1'000.0 * 1'000.0 * d;

}


constexpr unsigned long long operator ""M(unsigned long long i)
{

   return 1'000 * 1'000 * i;

}


constexpr integral_byte operator ""GiB(long double d)
{

   return (memsize) (1'024.0 * 1'024.0 * 1'024.0 * d);

}


constexpr integral_byte operator ""GiB(unsigned long long i)
{

   return (memsize) (i << 30);

}


constexpr long double operator ""G(long double d)
{

   return 1'000.0 * 1'000.0 * 1'000.0 * d;

}


constexpr unsigned long long operator ""G(unsigned long long i)
{

   return 1'000 * 1'000 * 1'000 * i;

}


template < typename ENUM >
class unit_base
{
public:

   union
   {

      ::f64 m_f64;

      ::i64 m_i64;

   };


   ENUM        m_eunit;
   bool        m_bFloating : 1;

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
      m_f64 = (::f64)f; 
      m_eunit = eunit; 
      set_floating(); 
   }

   template < primitive_floating FLOATING >
   constexpr unit_base(FLOATING f) 
   {
      m_f64 = (::f64)f;
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

   constexpr operator ::i64() const { return is_floating() ? (::i64) m_f64 : m_i64; }
   constexpr operator ::f64() const { return is_floating() ? m_f64 : (::f64) m_i64; }

   //template < primitive_integral INTEGRAL >
   //constexpr unit_base & operator = (INTEGRAL i) { m_i64 = (::i64)i; clear_floating(); return *this; }

   template < primitive_floating FLOATING >
   constexpr unit_base & operator = (FLOATING f)
   { 
      
      m_f64 = (::f64)f; 
      
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

      m_f64 = operator ::f64() * f;

      set_floating();

      return *this;

   }

};


template < typename ENUM, ENUM t_unitaAllow[] >
class targeted_unit :
   public unit_base < ENUM >
{
public:


   constexpr targeted_unit() :
      unit_base<ENUM>(0, t_unitaAllow[0]) 
   {
   
   }

   template < primitive_integral INTEGRAL >
   constexpr targeted_unit(INTEGRAL i, ENUM eunit) : 
      unit_base<ENUM>(i, eunit) 
   {
      assert_allowed(eunit); 
   }

   template < primitive_floating FLOATING >
   constexpr targeted_unit(FLOATING f, ENUM eunit) : 
      unit_base<ENUM>(f, eunit)
   {
      assert_allowed(eunit); 
   }

   constexpr targeted_unit(const unit_base <ENUM > & unit) : 
      unit_base<ENUM>(unit)
   { 
      assert_allowed(this->m_eunit); 
   }


   constexpr static void assert_allowed(ENUM eunit) 
   {
      if (!is_allowed(eunit)) 
         throw eunit; 
   }

   constexpr static bool is_allowed(ENUM eunit)
   {

      eunit = (ENUM) (eunit & ~INT_MIN);
      
      auto pallow = t_unitaAllow; 
      
      while (*pallow != e_unit_none)
      {
         
         if (*pallow == eunit)
         {

            return true;

         }

         pallow++;

      } 
      
      return false;

   }


   template < primitive_floating FLOATING >
   constexpr targeted_unit & operator = (FLOATING f)
   {
      
      unit_base <ENUM >::operator = (f);
      
      assert_allowed(this->m_eunit); 
      
      return *this;

   }


   constexpr targeted_unit & operator = (const unit_base <ENUM> & unit) 
   {
      
      unit_base <ENUM >::operator =(unit);  
      
      assert_allowed(this->m_eunit); 
      
      return *this; 
   
   }

   constexpr void set_unit(ENUM eunit)
   { 
      
      assert_allowed(eunit); 
      
      this->m_eunit = eunit; 
   
   }

};


using unit = unit_base < enum_unit >;



constexpr auto operator ""px(unsigned long long i)
{

   return unit(i, e_unit_pixel);

}



constexpr auto operator ""px(long double d)
{

   return unit(d, e_unit_pixel);

}


constexpr auto operator ""pt(unsigned long long i)
{

   return unit(i, e_unit_point);

}



constexpr auto operator ""pt(long double d)
{

   return unit(d, e_unit_point);

}