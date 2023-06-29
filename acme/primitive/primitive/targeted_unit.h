// Created by camilo on 2023-06-28 BRT <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/exception/bad_unit_exception.h"


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
      {

         throw ::bad_unit_exception < ENUM >(eunit);

      }

   }

   constexpr static bool is_allowed(ENUM eunit)
   {

      eunit = (ENUM)(eunit & ~INT_MIN);

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



