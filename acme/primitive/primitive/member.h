//
//  member.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 28/02/20.
//
#pragma once

////
////namespace primitive
////{
//
//
//   template < typename TYPE >
//   class member// :
//      //virtual public matter
//   {
//   public:
//
//
//      member() : m_p(nullptr) {}
//
//      TYPE* get() { return m_p; }
//      TYPE* get() const { return m_p; }
//
//      operator TYPE* () const { return m_p; }
//      operator TYPE* () { return m_p; }
//
//      TYPE* operator ->() const { return m_p; }
//      TYPE* operator ->() { return m_p; }
//
//      bool is_null() const { return __pointer_is_null(m_p); }
//      bool is_set() const { return __pointer_is_set(m_p); }
//      bool operator !() const { return is_null(); }
//
//      template < typename OBJECT >
//      ::pointer<OBJECT>cast() const;
//
//
//   protected:
//
//      friend class ::object;
//
//      TYPE* m_p;
//      void clear_member() { m_p = nullptr; }
//
//
//   public:
//
//      member& operator = (const ::primitive::member < TYPE >& member) { m_p = member.m_p; return *this; }
//
//      template < typename OBJECT >
//      member& operator = (const ::pointer<OBJECT>& p) { m_p = dynamic_cast <TYPE*> ((OBJECT*)p.m_p); return *this; }
//
//      template < typename OBJECT >
//      member& operator = (const ::ptr< OBJECT >& p) { m_p = dynamic_cast <TYPE*> ((OBJECT*)p.m_p); return *this; }
//
//      template < typename OBJECT >
//      member& operator = (const OBJECT* p) { m_p = dynamic_cast <TYPE*> ((OBJECT*)p); return *this; }
//
//      //virtual void clear_member() override { m_p = nullptr; }
//
//      //bool is_composite()const 
//      //{
//      //   return is_set() && m_p->m_eobject & e_object_composite;
//      //}
//
//   };
//
//
//   template < typename TYPE >
//   class composite :
//      public member < TYPE >
//      //virtual public member < TYPE >
//   {
//   public:
//
//
//      //composite() : matter(e_object_acquire) { }
//
//
//
//   protected:
//     friend class ::object;
//      using member < TYPE > ::operator =;
//
//      bool is_composite()const { return true; }
//
//   };
//
//
//   template < typename TYPE >
//   class reference :
//      public member < TYPE >
//      //virtual public member < TYPE >
//   {
//   public:
//
//
//      reference() { }
//
//   protected:
//      friend class ::object;
//      using member < TYPE > ::operator =;
//
//
//   };
//
////
////} // namespace primitive

//
//#define __member(TYPE) ::primitive::member < TYPE >
//#define ::pointer<TYPE>::primitive::composite < TYPE >
//#define ::pointer<TYPE>::primitive::reference < TYPE >


template<typename TYPE>
inline bool is_null(const ::pointer<TYPE>& p)
{

   return p.is_null();

}


template<typename TYPE>
inline bool is_set(const ::pointer<TYPE>& p)
{

   return p.is_set();

}



