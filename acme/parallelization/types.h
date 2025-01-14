// Created by camilo on 2025-01-14 04:46 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/prototype/prototype/hash32.h"



class message_queue;


//using htask_t = void *;

// insight by listening lastmiles (Dennis Clarke) talk about pthread_equal (it may end up not to be an int but a pointer in some implementations ?, so should use pthread_equal...)
class CLASS_DECL_ACME htask_t
{
public:

#ifdef PARALLELIZATION_PTHREAD

	pthread_t	m_h;
	
	htask_t(pthread_t h):m_h(h) {}
	
#elif defined(WINDOWS)

	HANDLE	m_h;
	
	htask_t(HANDLE h):m_h(h) {}
	
#else

	void * m_h;
	
	htask_t(void * h):m_h(h) {}
	
#endif

	htask_t():m_h{} {}
	
	htask_t(nullptr_t):m_h{} {}

	htask_t(const htask_t & h):m_h(h.m_h) {}	
	
	htask_t & operator = (const htask_t & h) {m_h = h.m_h; return *this;}

	bool operator == (const htask_t & h) const;
	
	bool is_null() const  { return operator==(nullptr); }
	
	bool is_set() const { return !is_null(); }
	
	bool operator !() const { return is_null(); }
	
	
};

//using itask_t = iptr;

// insight by listening lastmiles (Dennis Clarke) talk about pthread_equal (it may end up not to be an int but a pointer in some implementations ?, so should use pthread_equal...)
class CLASS_DECL_ACME itask_t
{
public:

#ifdef PARALLELIZATION_PTHREAD

	pthread_t	m_i;
	
	itask_t(pthread_t i):m_i(i) {}
	
#else

	iptr		m_i;
	
	itask_t(iptr i):m_i(i) {}
	
#endif

	itask_t():m_i{} {}
	
	itask_t(nullptr_t):m_i{} {}

	itask_t(const itask_t & i):m_i(i.m_i) {}	
	
	itask_t & operator = (const itask_t & i) {m_i = i.m_i; return *this;}

	bool operator == (const itask_t & i) const;
	
	bool is_null() const  { return operator==(nullptr); }
	
	bool is_set() const { return !is_null(); }
	
	bool operator !() const { return is_null(); }

	
};



// insight by listening lastmiles (Dennis Clarke) talk about pthread_equal (it may end up not to be an int but a pointer in some implementations ?, so should use pthread_equal...)
class CLASS_DECL_ACME task_index
{
public:


	iptr	m_i;
	
	
	task_index(iptr i):m_i(i) {}

	task_index():m_i{} {}
	
	task_index(nullptr_t):m_i{} {}

	task_index(const task_index & i):m_i(i.m_i) {}	
	
	task_index & operator = (const task_index & i) {m_i = i.m_i; return *this;}

	bool operator == (const task_index & i) const { return m_i == i.m_i; }
	
	bool is_null() const  { return operator==(nullptr); }
	
	bool is_set() const { return !is_null(); }
	
	bool operator !() const { return is_null(); }
	
	
	operator hash32() const { return (hash32)m_i; }

	
};





class CLASS_DECL_ACME thread_storage
{
public:
  
  task_index  	                  m_taskindex;
  htask_t     	                  m_htask;
  itask_t     	                  m_itask;
  ::task *		                  m_ptask;
  ::pointer < ::message_queue >  m_pmessagequeue;
  
};




