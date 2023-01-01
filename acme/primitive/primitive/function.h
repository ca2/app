// Created by camilo on 2022-03-20 11:35 <3ThomasBorregaardS�rensen!!
#pragma once


#include "acme/primitive/primitive/transfer.h"

#include "acme/primitive/primitive/ptr.h"

#include "acme/primitive/primitive/particle.h"

//#include "acme/parallelization/wait.h"

enum enum_use
{

   e_use,

}; // enum enum_base


enum enum_as_lparam
{

   e_as_lparam,

}; // enum enum_base


enum enum_timeout
{

   e_timeout,

}; // enum enum_timeout


#define _as(p) { e_use, p }


class function_common
{
public:


   class ::time      m_timeTimeout;


   function_common() {}
   function_common(enum_timeout, const class time& wait): m_timeTimeout(wait) {}

   void timeout(const class time & timeWait)  { m_timeTimeout = timeWait;}
   class ::time timeout() const {return m_timeTimeout;}


};


template < typename FUNCTION >
class function :
   public function_common
{

};

//template <  typename RETURN_TYPE, typename... TYPES>
//class function_type < RETURN_TYPE(TYPES...) >
//{
//public:
//
//   using return_type = RETURN_TYPE;
//
//};
//
//template <class RETURN_TYPE, class... TYPES>
//struct get_function_implementation
//{
//   using type = function_implementation<RETURN_TYPE, TYPES...>;
//};


template < >
class function < void() > :
   public ptr < ::particle >,
   public function_common
{
public:


   template < typename ELEMENT >
   class predicate :
      virtual public particle
   {
   public:


      ELEMENT m_element;


      predicate(ELEMENT element) :
         m_element(element)
      {

      }


      void operator()()
      {

         m_element();

      }


      virtual void run()
      {

         this->operator()();

      }


   };

   
   function(nullptr_t = nullptr)
   {

   }


   function(const ptr < ::particle > & p) :
      ptr < ::particle >(p)
   {

   }


   function(ptr < ::particle > && p) :
      ptr < ::particle >(::transfer(p))
   {

   }


   function(enum_as_lparam, iptr iptr)
   {

      m_p = (::particle *) iptr;

   }


   template < typename TYPE >
   function(TYPE * p)
   {

      m_p = p;

      p->increment_reference_count();

   }


   template < typename PREDICATE >
   function(PREDICATE predicateParam)
   {

      m_p = memory_new class predicate <PREDICATE >(predicateParam);

   }


   template < typename PREDICATE >
   function(enum_timeout, const class time & wait, PREDICATE predicateParam) :
      function(predicateParam)
   {

      m_timeTimeout = wait;
   
   }


   function(const function & function) :
      ptr < ::particle > (function)
   {

   }


   function(function && function) :
      ptr < ::particle >(::transfer(function))
   {

   }


   ~function()
   {

   }


   void operator()() const
   {

      m_p->call_run();

   }


   function & operator = (const function & function)
   {

      ptr < ::particle >::operator=(function.m_p);

      return *this;

   }

//
//   function & operator = (function && function)
//   {
//
//      ptr < ::element >::operator=(::transfer(function));
//
//      return *this;
//
//   }

   operator bool() const { return __pointer_is_set(m_p); }

   bool operator !() const { return __pointer_is_null(m_p); }

   operator ::particle *() const { return m_p; }

   const ::particle * operator -> () const { return m_p; }

   ::particle * operator -> () { return m_p; }
   

};


template < typename RETURN_TYPE >
class function < RETURN_TYPE() > :
   public function_common
{
public:


   class predicate_base :
      virtual public ::particle
   {
   public:

      virtual RETURN_TYPE operator()() = 0;

   };


   template < typename PREDICATE >
   class predicate :
      public predicate_base
   {
   public:

      PREDICATE m_predicate;

      predicate(PREDICATE predicate) :
         m_predicate(predicate)
      {

      }


      RETURN_TYPE operator()()
      {

         return m_predicate();

      }

   };

   ptr<predicate_base >     m_ppredicate;


   function(nullptr_t = nullptr)
   {

   }

   template < typename PREDICATE >
   function(PREDICATE predicateParam)
   {

      m_ppredicate.transfer(memory_new class predicate <PREDICATE >(predicateParam));

   }


   function(const function & function) :
      m_ppredicate(function.m_ppredicate)
   {

   }


   function(function && function) :
      m_ppredicate(::transfer(function.m_ppredicate))
   {

   }


   ~function()
   {

   }


   RETURN_TYPE operator()() const
   {

      ASSERT(m_ppredicate);

      return m_ppredicate->operator()();

   }


   void clear() { m_ppredicate.release(); }

   template < typename PREDICATE >
   function & operator = (PREDICATE predicateParam)
   {

      m_ppredicate.transfer(memory_new class predicate <PREDICATE >(predicateParam));

      return *this;

   }

   function & operator = (const function & function)
   {

      m_ppredicate = function.m_ppredicate;

      return *this;

   }


   function & operator = (nullptr_t)
   {

      clear();

      return *this;

   }

   operator bool() const { return __pointer_is_set(m_ppredicate); }

   bool operator !() const { return __pointer_is_null(m_ppredicate); }


   operator u32hash() const {
      return { (::u32)(::uptr)m_ppredicate.m_p };
   };
   


};



template < typename RETURN_TYPE, typename... TYPES >
class function < RETURN_TYPE(TYPES...) > :
   public function_common
{
public:


   class base :
      virtual public ::particle
   {
   public:

      virtual RETURN_TYPE operator()(TYPES... args) = 0;

   };


   template < typename PREDICATE >
   class implementation :
      public base
   {
   public:

      PREDICATE m_predicate;

      implementation(PREDICATE predicate) :
         m_predicate(predicate)
      {

      }


      RETURN_TYPE operator()(TYPES... args) override
      {

         return m_predicate(args...);

      }

   };

   
   ptr < base >     m_pfunctionbase;


   function(nullptr_t = nullptr)
   {

   }


   function(enum_use, base * pbase)
   {

      m_pfunctionbase = pbase;

   }


   template < typename FUNCTION >
   function(FUNCTION functionParam)
   {

      m_pfunctionbase.transfer(memory_new class implementation < FUNCTION >(functionParam));

   }


   function(const function & function) :
      m_pfunctionbase(function.m_pfunctionbase)
   {

   }


   function(function && function) :
      m_pfunctionbase(::transfer(function.m_pfunctionbase))
   {

   }


   ~function()
   {

   }


   RETURN_TYPE operator()(TYPES... args) const
   {

      //ASSERT(m_pfunctionbase);

      return ((base *)m_pfunctionbase.m_p)->operator()(args...);

   }


   void clear() { m_pfunctionbase.release(); }


   template < typename FUNCTION >
   function & operator = (FUNCTION functionParam)
   {

      m_pfunctionbase.transfer ( memory_new class implementation <FUNCTION >(functionParam));

      return *this;

   }


   function & operator = (nullptr_t)
   {

      clear();

      return *this;

   }

   operator bool() const { return __pointer_is_set(m_pfunctionbase); }

   bool operator !() const { return __pointer_is_null(m_pfunctionbase); }

   function & operator = (const function & function) { m_pfunctionbase = function.m_pfunctionbase; return *this; }
   bool operator == (const function & function) const { return m_pfunctionbase == function.m_pfunctionbase; }
   bool operator != (const function & function) const { return !operator==(function); }

   operator u32hash() const {
      return { (::u32)(::uptr)m_pfunctionbase.m_p };
   }

};




template < typename... TYPES >
class function < void(TYPES...) > :
   public function_common
{
public:


   class base :
      virtual public ::particle
   {
   public:

      virtual void operator()(TYPES... args) = 0;

   };


   template < typename PREDICATE >
   class implementation :
      public base
   {
   public:

      PREDICATE m_predicate;

      implementation(PREDICATE predicate) :
         m_predicate(predicate)
      {

      }


      void operator()(TYPES... args) override
      {

         m_predicate(args...);

      }

   };

   
   ptr < base >     m_pfunctionbase;


   function(nullptr_t = nullptr)
   {

   }


   function(enum_use, base * pbase)
   {

      m_pfunctionbase = pbase;

   }


   template < typename FUNCTION >
   function(FUNCTION functionParam)
   {

      m_pfunctionbase.transfer(memory_new class implementation < FUNCTION >(functionParam));

   }


   function(const function & function) :
      m_pfunctionbase(function.m_pfunctionbase)
   {

   }


   function(function && function) :
      m_pfunctionbase(::transfer(function.m_pfunctionbase))
   {

   }


   ~function()
   {

   }


   void operator()(TYPES... args) const
   {

      //ASSERT(m_pfunctionbase);

      ((base *)m_pfunctionbase.m_p)->operator()(args...);

   }


   void clear() { m_pfunctionbase.release(); }


   template < typename FUNCTION >
   function & operator = (FUNCTION functionParam)
   {

      m_pfunctionbase.transfer ( memory_new class implementation <FUNCTION >(functionParam));

      return *this;

   }


   function & operator = (nullptr_t)
   {

      clear();

      return *this;

   }

   operator bool() const { return __pointer_is_set(m_pfunctionbase.m_p); }

   bool operator !() const { return __pointer_is_null(m_pfunctionbase.m_p); }

   function & operator = (const function & function) { m_pfunctionbase = function.m_pfunctionbase.m_p; return *this; }
   bool operator == (const function & function) const { return m_pfunctionbase == function.m_pfunctionbase; }
   bool operator != (const function & function) const { return !operator==(function); }


   operator u32hash() const { return { (::u32)(::uptr)m_pfunctionbase.m_p }; }

};






