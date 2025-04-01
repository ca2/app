// Created by camilo on 2025-01-14 04:46 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/prototype/prototype/hash32.h"

struct hthread_t
{
	unsigned int ui0;
	unsigned int ui1;
	unsigned int ui2;
	unsigned int ui3;
	unsigned int ui4;
	unsigned int ui5;
	unsigned int ui6;
	unsigned int ui7;
};


//#ifdef _TIME_H_
//#error "time.h already included WHAT!!!!!!"
//#endif

//#include <pthread.h>

//#ifdef _TIME_H_
//#error "time.h already included WHAT!!!!!!"
//#endif


#ifdef WINDOWS


#include "acme/operating_system/windows_common/handle.h"


#endif


class message_queue;


//using htask = void *;

// insight by listening lastmiles (Dennis Clarke) talk about pthread_equal (it may end up not to be an int but a pointer in some implementations ?, so should use pthread_equal...)
class CLASS_DECL_ACME htask
{
public:

#ifdef PARALLELIZATION_PTHREAD

	hthread_t	m_h;
	
	htask(hthread_t h):m_h(h) {}
	
#elif defined(WINDOWS)

   ::uptr      m_h;
	
	htask(const ::uptr & h):m_h(h) {}
	
#else

	void * m_h;
	
	htask(void * h):m_h(h) {}
	
#endif

	htask():m_h{} {}
	
	htask(nullptr_t):m_h{} {}

	htask(const htask & h):m_h(h.m_h) {}	
	
	htask & operator = (const htask & h) {m_h = h.m_h; return *this;}

	bool operator == (const htask & h) const;
	
	bool is_null() const;
	
	bool is_set() const { return !is_null(); }
	
	bool operator !() const { return is_null(); }
	
	
};

//using itask = iptr;

// insight by listening lastmiles (Dennis Clarke) talk about pthread_equal (it may end up not to be an int but a pointer in some implementations ?, so should use pthread_equal...)
class CLASS_DECL_ACME itask
{
public:

#ifdef PARALLELIZATION_PTHREAD

	hthread_t	m_i;
	
	itask(hthread_t i):m_i(i) {}
	
#else

	iptr		m_i;
	
	itask(iptr i):m_i(i) {}
	
#endif

	itask():m_i{} {}
	
	itask(nullptr_t):m_i{} {}

	itask(const itask & i):m_i(i.m_i) {}	
	
	itask & operator = (const itask & i) {m_i = i.m_i; return *this;}

	bool operator == (const itask & i) const;
	
	bool is_null() const;
	
	bool is_set() const { return !is_null(); }
	
	bool operator !() const { return is_null(); }

	
};



//class CLASS_DECL_ACME task_index
//{
//public:
//
//
//	iptr	m_i;
//	
//	
//	task_index(iptr i):m_i(i) {}
//
//	task_index():m_i{} {}
//	
//	task_index(nullptr_t):m_i{} {}
//
//	task_index(const task_index & i):m_i(i.m_i) {}	
//	
//	task_index & operator = (const task_index & i) {m_i = i.m_i; return *this;}
//
//	bool operator == (const task_index & i) const { return m_i == i.m_i; }
//	
//	bool is_null() const  { return operator==(nullptr); }
//	
//	bool is_set() const { return !is_null(); }
//	
//	bool operator !() const { return is_null(); }
//	
//	
//	operator hash32() const { return (hash32)m_i; }
//
//	
//};
//




class CLASS_DECL_ACME thread_storage
{
public:
  
   ::task_index                     m_taskindex;
   htask     	                     m_htask;
   itask     	                     m_itask;
   ::pointer < ::task >             m_ptask;
   ::pointer < ::message_queue >    m_pmessagequeue;
  
};




