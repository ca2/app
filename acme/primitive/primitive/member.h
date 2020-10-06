//
//  member.h
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 28/02/20.
//
#pragma once


namespace primitive
{


   template < typename TYPE >
   class member// :
      //virtual public elemental
   {
   public:


      member() : m_p(nullptr) {}

      TYPE* get() { return m_p; }
      TYPE* get() const { return m_p; }

      operator TYPE* () const { return m_p; }
      operator TYPE* () { return m_p; }

      TYPE* operator ->() const { return m_p; }
      TYPE* operator ->() { return m_p; }

      bool is_null() const { return ::is_null(m_p); }
      bool is_set() const { return ::is_set(m_p); }
      bool operator !() const { return is_null(); }

      template < typename OBJECT >
      __pointer(OBJECT) cast() const;


   protected:

      friend class ::object;

      TYPE* m_p;

      member& operator = (const ::primitive::member < TYPE >& member) { m_p = member.m_p; return *this; }

      template < typename OBJECT >
      member& operator = (const ::___pointer < OBJECT >& p) { m_p = dynamic_cast <TYPE*> ((OBJECT*)p.m_p); return *this; }

      template < typename OBJECT >
      member& operator = (const OBJECT* p) { m_p = dynamic_cast <TYPE*> ((OBJECT*)p); return *this; }

      //virtual void clear_member() override { m_p = nullptr; }
      void clear_member() { m_p = nullptr; }

      bool is_composite()const { return false; }

   };


   template < typename TYPE >
   class composite :
      public member < TYPE >
      //virtual public member < TYPE >
   {
   public:


      //composite() : elemental(e_object_acquire) { }

      bool is_composite()const { return true; }


   protected:
      friend class ::object;
      using member < TYPE > ::operator =;


   };


   template < typename TYPE >
   class reference :
      public member < TYPE >
      //virtual public member < TYPE >
   {
   public:


      reference() { }

   protected:
      friend class ::object;
      using member < TYPE > ::operator =;


   };


} // namespace primitive



