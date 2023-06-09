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

#define __counter_name__(name) TOKEN_CONCATENATE(name, TOKEN_CONCATENATE(_, __COUNTER__))




#define scoped_restore(payload) auto __counter_name__(scoped_restore) = create_scoped_restore(payload)


//#define __set_restore(payload, set) ::scoped_restore < decltype(payload) > TOKEN_CONCATENATE(scopedrestore, __COUNTER__) (&payload); ::payload = set




//#define η __counter_name__
//
//
//#define λ η = [&]()


template <class PREDICATE>
struct run_at_destructor_struct
{

   PREDICATE m_predicate;

   run_at_destructor_struct(PREDICATE predicate) : m_predicate(predicate) {}
   ~run_at_destructor_struct() { m_predicate(); }

};


#define at_end_of_scope run_at_destructor_struct __counter_name__(run_at_destructor) = [&]()



