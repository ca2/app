// Created by camilo on 2022-03-20 11:35 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/primitive/primitive/transfer.h"

#include "acme/primitive/primitive/ptr.h"

#include  "acme/primitive/primitive/particle.h"


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


   function_common()
   {

#ifdef DEBUG

       m_timeTimeout = 5_min;

#else

       m_timeTimeout = 15_s;

#endif

   }


   function_common(enum_timeout, const class time& wait): m_timeTimeout(wait) {}


   void timeout(const class time & timeWait)  { m_timeTimeout = timeWait;}
   class ::time timeout() const {return m_timeTimeout;}


};


template < typename PRIMITIVE_FUNCTION >
concept primitive_function = ::std::is_base_of < ::function_common, PRIMITIVE_FUNCTION >::value;


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
   public function_common
{
public:


   using base = ::particle;


   template < typename ELEMENT >
   class predicate :
      virtual public base
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


   ::ptr < base > m_pbase;


   
   function(nullptr_t = nullptr)
   {

   }


   function(const ptr < ::particle > & p) 
   {
      m_pbase = p;
   }


   function(ptr < ::particle > && p)
   {
      m_pbase = ::transfer(p);
   }


   function(enum_as_lparam, iptr iptr)
   {

      m_pbase = (::particle *) iptr;

   }


   template < typename TYPE >
   function(TYPE * p)
   {

      m_pbase = p;

      p->increment_reference_count();

   }


   template < typename PREDICATE >
   function(PREDICATE predicateParam)
   {

      m_pbase = memory_new class predicate <PREDICATE >(predicateParam);

   }


   template < typename PREDICATE >
   function(enum_timeout, const class time & wait, PREDICATE predicateParam) :
      function(predicateParam)
   {

      m_timeTimeout = wait;
   
   }


   function(const function & function)
   {
      m_pbase = function.m_pbase;
   }


   function(function && function)
   {

      m_pbase = ::transfer(function.m_pbase);

   }


   ~function()
   {

   }

   void operator()()
   {

      m_pbase->call_run();

   }

   void operator()() const
   {

      m_pbase->call_run();

   }


   function & operator = (const function & function)
   {

      m_pbase = function.m_pbase;

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

   operator bool() const { return ::is_set(this) && __pointer_is_set(m_pbase); }

   bool operator !() const { return !this->operator bool(); }

   operator ::particle *() const { return ::is_null(this) ? nullptr : m_pbase; }

   const ::particle * operator -> () const { return m_pbase; }

   ::particle * operator -> () { return m_pbase; }
   

};


template < typename RETURN_TYPE >
class function < RETURN_TYPE() > :
   public function_common
{
public:


   class base :
      virtual public ::particle
   {
   public:

      virtual RETURN_TYPE operator()() = 0;

   };


   template < typename PREDICATE >
   class predicate :
      public base
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

   ptr<base >     m_pbase;


   function(nullptr_t = nullptr)
   {

   }

   template < typename PREDICATE >
   function(PREDICATE predicateParam)
   {

      m_pbase.transfer(memory_new class predicate <PREDICATE >(predicateParam));

   }


   function(const function & function) :
      m_pbase(function.m_pbase)
   {

   }


   function(function && function) :
      m_pbase(::transfer(function.m_pbase))
   {

   }


   ~function()
   {

   }


   RETURN_TYPE operator()() const
   {

      ASSERT(m_pbase);

      return m_pbase->operator()();

   }


   void clear() { m_pbase.release(); }

   template < typename PREDICATE >
   function & operator = (PREDICATE predicateParam)
   {

      m_pbase.transfer(memory_new class predicate <PREDICATE >(predicateParam));

      return *this;

   }

   function & operator = (const function & function)
   {

      m_pbase = function.m_pbase;

      return *this;

   }


   function & operator = (nullptr_t)
   {

      clear();

      return *this;

   }

   operator bool() const { return __pointer_is_set(m_pbase); }

   bool operator !() const { return __pointer_is_null(m_pbase); }


   
   operator ::u32hash() const {
      return { (::u32)(::uptr)m_pbase.m_p };
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

   
   ptr < base >     m_pbase;


   function(nullptr_t = nullptr)
   {

   }


   function(enum_use, base * pbase)
   {

      m_pbase = pbase;

   }


   template < typename FUNCTION >
   function(FUNCTION functionParam)
   {

      m_pbase.transfer(memory_new class implementation < FUNCTION >(functionParam));

   }


   function(const function & function) :
      m_pbase(function.m_pbase)
   {

   }


   function(function && function) :
      m_pbase(::transfer(function.m_pbase))
   {

   }


   ~function()
   {

   }


   RETURN_TYPE operator()(TYPES... args) const
   {

      //ASSERT(m_pbase);

      return ((base *)m_pbase.m_p)->operator()(args...);

   }


   void clear() { m_pbase.release(); }


   template < typename FUNCTION >
   function & operator = (FUNCTION functionParam)
   {

      m_pbase.transfer ( memory_new class implementation <FUNCTION >(functionParam));

      return *this;

   }


   function & operator = (nullptr_t)
   {

      clear();

      return *this;

   }

   operator bool() const { return __pointer_is_set(m_pbase); }

   bool operator !() const { return __pointer_is_null(m_pbase); }

   function & operator = (const function & function) { m_pbase = function.m_pbase; return *this; }
   bool operator == (const function & function) const { return m_pbase == function.m_pbase; }
   bool operator != (const function & function) const { return !operator==(function); }

   operator ::u32hash() const {
      return { (::u32)(::uptr)m_pbase.m_p };
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

   
   ptr < base >     m_pbase;


   function(nullptr_t = nullptr)
   {

   }


   function(enum_use, base * pbase)
   {

      m_pbase = pbase;

   }


   template < typename FUNCTION >
   function(FUNCTION functionParam)
   {

      m_pbase.transfer(memory_new class implementation < FUNCTION >(functionParam));

   }


   function(const function & function) :
      m_pbase(function.m_pbase)
   {

   }


   function(function && function) :
      m_pbase(::transfer(function.m_pbase))
   {

   }


   ~function()
   {

   }


   void operator()(TYPES... args) const
   {

      //ASSERT(m_pbase);

      ((base *)m_pbase.m_p)->operator()(args...);

   }


   void clear() { m_pbase.release(); }


   template < typename FUNCTION >
   function & operator = (FUNCTION functionParam)
   {

      m_pbase.transfer ( memory_new class implementation <FUNCTION >(functionParam));

      return *this;

   }
   

   function& operator = (base * pbase)
   {

      m_pbase = pbase;

      return *this;

   }


   function & operator = (nullptr_t)
   {

      clear();

      return *this;

   }

   operator bool() const { return __pointer_is_set(m_pbase.m_p); }

   bool operator !() const { return __pointer_is_null(m_pbase.m_p); }

   function & operator = (const function & function) { m_pbase = function.m_pbase.m_p; return *this; }
   bool operator == (const function & function) const { return m_pbase == function.m_pbase; }
   bool operator != (const function & function) const { return !operator==(function); }


   operator ::u32hash() const { return { (::u32)(::uptr)m_pbase.m_p }; }

};



using trace_function = ::function < void(enum_trace_level, const ::scoped_string&) >;






