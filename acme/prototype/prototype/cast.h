//
// Created by camilo on 2024-10-25 00:28 <3ThomasBorregaardSorensen!!
//
#pragma once



template < typename TYPE >
class cast
{
public:

   
   TYPE * m_p;

   
   cast()
   {

      m_p = nullptr;

   }


   template < typename TYPE2 >
   cast(const TYPE2 * p2)
   {

      m_p = dynamic_cast < TYPE  *>((TYPE2 *)(p2));

   }


   template < typename TYPE2 >
   cast(const ::pointer < TYPE2 > & p2)
   {

      m_p = dynamic_cast < TYPE  *>((::subparticle *)(p2.m_psubparticle));

   }


   template < typename TYPE2 >
   cast(const ::cast < TYPE2 > & p2)
   {

      m_p = dynamic_cast <TYPE *>((::subparticle *)(p2.m_p));

   }


   operator TYPE *()
   {

      return m_p;

   }


   operator const TYPE * () const
   {

      return m_p;

   }


   TYPE * operator ->()
   {

      return m_p;

   }


   TYPE * operator ->() const
   {

      return m_p;

   }


   TYPE & operator *()
   {

      return *m_p;

   }


   const TYPE & operator *() const
   {

      return *m_p;

   }


   cast& operator  = (nullptr_t)
   {

      m_p = nullptr;

      return *this;

   }



   template < typename TYPE2 >
   cast & operator  = (const TYPE2 * p2)
   {

      m_p = dynamic_cast <TYPE *>((TYPE2 *)(p2));

      return *this;

   }


   template < typename TYPE2 >
   cast& operator = (const ::pointer < TYPE2 >& p2);


   template < typename TYPE2 >
   cast & operator = (const ::cast < TYPE2 > & p2)
   {

      m_p = dynamic_cast <TYPE *>((::subparticle *)(p2.m_p));

      return *this;

   }


};

