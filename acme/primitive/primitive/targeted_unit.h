// Created by camilo on 2023-06-28 BRT <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/exception/bad_unit_exception.h"

/// struct some_allowed_units { static ENUM * allowed_units() {...} }


template < typename ENUM, typename allowed_units >
class targeted_unit :
   public unit_base < ENUM >
{
public:


   constexpr targeted_unit() :
      unit_base<ENUM>(0, allowed_units::allowed_units()[0])
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
      {

         throw ::bad_unit_exception < ENUM >(eunit);

      }

   }

   constexpr static bool is_allowed(ENUM eunit)
   {

      //::index i = 0;

      auto pallowed = allowed_units::allowed_units();

      ENUM eallowed;

      while ((eallowed = *pallowed) != e_unit_none)
      {

         if (eallowed == eunit)
         {

            return true;

         }

         pallowed++;

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
   
   
   template < primitive_floating FLOATING >
   targeted_unit & operator *= (FLOATING f)
   {

      unit_base < ENUM >::operator *=(f);

      return *this;

   }
   
   
   template < primitive_floating FLOATING >
   targeted_unit & operator /= (FLOATING f)
   {

      unit_base < ENUM >::operator /=(f);

      return *this;

   }
   

   template < primitive_floating FLOATING >
   targeted_unit operator * (FLOATING f) const
   {
      
      auto unit = *this;

      unit *= f;

      return unit;

   }
   
   
   template < primitive_floating FLOATING >
   targeted_unit operator / (FLOATING f) const
   {

      auto unit = *this;

      unit /= f;

      return *this;

   }
   

};



