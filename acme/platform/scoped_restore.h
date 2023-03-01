#pragma once


template <class TYPE>
struct scoped_restore_struct
{


   TYPE *  m_pKept;
   TYPE    m_valueRestore;

   scoped_restore_struct(TYPE * pKept);
   scoped_restore_struct(TYPE * pKept,const TYPE & set);
   ~scoped_restore_struct();

   void Restore();

};


template <class TYPE>
scoped_restore_struct<TYPE>::scoped_restore_struct(TYPE * pKept):
   m_pKept(pKept),
   m_valueRestore(*m_pKept)
{

}


template <class TYPE>
scoped_restore_struct<TYPE>::scoped_restore_struct(TYPE * pKept, const TYPE & set) :
   m_pKept(pKept),
   m_valueRestore(*m_pKept)
{

   *m_pKept = set;
}



template <class TYPE>
scoped_restore_struct<TYPE>::~scoped_restore_struct()
{

   Restore();

}


template <class TYPE>
void scoped_restore_struct<TYPE>::Restore()
{

   *m_pKept = m_valueRestore;

}


template < typename TYPE >
inline ::scoped_restore_struct < TYPE > create_scoped_restore(TYPE & t)
{
   
   return {&t};
   
}


#define scoped_restore(payload) auto η = create_scoped_restore(payload)


//#define __set_restore(payload, set) ::scoped_restore < decltype(payload) > TOKEN_CONCATENATE(scopedrestore, __COUNTER__) (&payload); ::payload = set


#define __counter_name__ TOKEN_CONCATENATE(η_, __COUNTER__)


#define η __counter_name__


#define λ η = [&]()


template <class PREDICATE>
struct run_at_destructor_struct
{

   PREDICATE m_predicate;

   run_at_destructor_struct(PREDICATE predicate) : m_predicate(predicate) {}
   ~run_at_destructor_struct() { m_predicate(); }

};


#define at_end_of_scope run_at_destructor_struct λ



