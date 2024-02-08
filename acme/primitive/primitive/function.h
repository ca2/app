// Created by camilo on 2022-03-20 11:35 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/primitive/primitive/transfer.h"

#include "acme/primitive/primitive/ptr.h"

#include "acme/primitive/primitive/referenceable.h"

#include "acme/primitive/time/_time.h"


enum enum_use
{

   e_use,

}; // enum enum_use


enum enum_as_lparam
{

   e_as_lparam,

}; // enum enum_as_lparam


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


   void timeout(const class time & timeWait)  { m_timeTimeout = timeWait; }


   class ::time timeout() const {return m_timeTimeout;}


};


template < typename PRIMITIVE_FUNCTION >
concept primitive_function = ::std::is_base_of < ::function_common, PRIMITIVE_FUNCTION >::value;


template < typename FUNCTION >
class function :
   public function_common
{

};

//template < typename FUNCTION >
//class function_receptor :
//   public function < FUNCTION >
//{
//
//};


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


   using base = ::referenceable;


   template < typename ELEMENT >
   class implementation :
      virtual public base
   {
   public:


      ELEMENT m_element;


      implementation(ELEMENT && element) :
         m_element(::transfer(element))
      {

      }


      void operator()()
      {

         m_element();

      }


      void run() override
      {

         this->operator()();

      }


   };


   ::ptr < base > m_pbase;


   
   function(nullptr_t = nullptr)
   {

   }


   function(const ptr < ::particle > & p) :
      m_pbase(p)
   {

   }


   function(ptr < ::particle > && p) :
      m_pbase(p)
   {
      

   }


   function(enum_as_lparam, iptr iptr) :
      m_pbase((::particle *)iptr)
   {

   }


   function(use_t, base * p) :
      m_pbase(p)
   {

   }


   //function(transfer_t, base * p) :
   //   m_pbase(transfer_t{}, p)
   //{

   //}


   //template < typename PREDICATE >
   //function(function_t, PREDICATE predicateParam) :
   //   m_pbase(transfer_t{}, __allocate< class implementation <PREDICATE > >(predicateParam))
   //{

   //}

   template < typename PREDICATE >
   function(PREDICATE predicateParam) :
      m_pbase(__allocate< class implementation <PREDICATE > >(::transfer(predicateParam)))
   {

   }


   template < typename PREDICATE >
   function(enum_timeout, const class time & wait, PREDICATE predicateParam) :
      function(predicateParam)
   {

      m_timeTimeout = wait;
   
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


   function & operator = (function && function)
   {

      m_pbase = ::transfer(function.m_pbase);

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

   explicit operator bool() const { return ::is_set(this) && __pointer_is_set(m_pbase); }

   bool operator !() const { return !this->operator bool(); }

   operator ::referenceable *() const { return ::is_null(this) ? nullptr : m_pbase; }

   const ::referenceable * operator -> () const { return m_pbase; }

   ::referenceable * operator -> () { return m_pbase; }
   

};
//
//template < >
//class function_receptor < void() > :
//   public function < void() >
//{
//public:
//
//   template < typename FUNCTION >
//   function_receptor(FUNCTION function) :
//      function < void() >(transfer_t{}, function)
//   {
//   }
//
//
//};


template < typename RETURN_TYPE >
class function < RETURN_TYPE() > :
   public function_common
{
public:


   class base :
      virtual public ::referenceable
   {
   public:

      virtual RETURN_TYPE operator()() = 0;

   };


   template < typename PREDICATE >
   class implementation :
      public base
   {
   public:


      PREDICATE m_predicate;


      implementation(PREDICATE && implementation) :
         m_predicate(::transfer(implementation))
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


   function(use_t, base * p) :
      m_pbase(p)
   {

   }


   //function(transfer_t, base * p) :
   //   m_pbase(transfer_t{}, p)
   //{

   //}


   //template < typename PREDICATE >
   //function(function_t, PREDICATE predicateParam) :
   //   m_pbase(transfer_t{}, __allocate< class implementation <PREDICATE > >(predicateParam))
   //{

   //}

   template < typename PREDICATE >
   function(PREDICATE predicateParam) :
      m_pbase(__allocate< class implementation <PREDICATE > >(::transfer(predicateParam)))
   {

   }

   function(function && function) :
      m_pbase(::transfer(function.m_pbase))
   {

   }


   function(const function & function) :
      m_pbase(function.m_pbase)
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

      m_pbase = ::transfer(__allocate< class implementation <PREDICATE > >(::transfer(predicateParam)));

      return *this;

   }


   function & operator = (const function & function)
   {

      m_pbase = function.m_pbase;

      return *this;

   }


   function & operator = (function && function)
   {

      m_pbase = ::transfer(function.m_pbase);

      return *this;

   }


   function & operator = (nullptr_t)
   {

      clear();

      return *this;

   }

   explicit operator bool() const { return __pointer_is_set(m_pbase); }

   bool operator !() const { return __pointer_is_null(m_pbase); }


   operator ::u32hash() const 
   {

      return { (::u32)(::uptr)m_pbase.m_p };

   };


};

//
//template < typename RETURN_TYPE >
//class function_receptor < RETURN_TYPE() > :
//   public function < RETURN_TYPE() >
//{
//public:
//
//   template < typename FUNCTION >
//   function_receptor(FUNCTION function) :
//      function < RETURN_TYPE() >(transfer_t{}, function)
//   {
//   }
//
//
//};



template < typename RETURN_TYPE, typename... TYPES >
class function < RETURN_TYPE(TYPES...) > :
   public function_common
{
public:


   class base :
      virtual public ::referenceable
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

      implementation(PREDICATE && implementation) :
         m_predicate(::transfer(implementation))
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


   function(use_t, base * p) :
      m_pbase(p)
   {

   }


   //function(transfer_t, base * p) :
   //   m_pbase(transfer_t{}, p)
   //{

   //}


   template < typename FUNCTION >
   function(FUNCTION functionParam) :
      m_pbase(__allocate< class implementation < FUNCTION > >(::transfer(functionParam)))
   {

   }

   //template < typename FUNCTION >
   //function(function_t, FUNCTION functionParam) :
   //   m_pbase(transfer_t{}, __allocate< class implementation < FUNCTION > >(functionParam))
   //{

   //}

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

      m_pbase = ::transfer( __allocate< class implementation <FUNCTION > >(::transfer(functionParam)));

      return *this;

   }


   function & operator = (const function & function)
   { 
      
      m_pbase = function.m_pbase; 
      
      return *this; 
   
   }


   function & operator = (function && function)
   {

      m_pbase = ::transfer(function.m_pbase);

      return *this;

   }


   function & operator = (nullptr_t)
   {

      clear();

      return *this;

   }

   explicit operator bool() const { return __pointer_is_set(m_pbase); }

   bool operator !() const { return __pointer_is_null(m_pbase); }

   bool operator == (const function & function) const { return m_pbase == function.m_pbase; }

   operator ::u32hash() const 
   {

      return { (::u32)(::uptr)m_pbase.m_p };

   }


};

//
//template < typename RETURN_TYPE, typename... TYPES >
//class function_receptor < RETURN_TYPE(TYPES...) > :
//   public function <  RETURN_TYPE(TYPES...) >
//{
//public:
//
//   template < typename FUNCTION >
//   function_receptor(FUNCTION function) :
//      function <  RETURN_TYPE(TYPES...) >(transfer_t{}, function)
//   {
//   }
//
//
//};



template < typename... TYPES >
class function < void(TYPES...) > :
   public function_common
{
public:


   class base :
      virtual public ::referenceable
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

      implementation(PREDICATE && implementation) :
         m_predicate(::transfer(implementation))
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


   function(use_t, base * p) :
      m_pbase(p)
   {

   }


   //function(transfer_t, base * p) :
   //   m_pbase(transfer_t{}, p)
   //{

   //}


   //template < typename FUNCTION >
   //function(function_t, FUNCTION functionParam) :
   //   m_pbase(transfer_t{}, __allocate< class implementation < FUNCTION > >(functionParam))
   //{

   //}

   template < typename FUNCTION >
   function(FUNCTION functionParam) :
      m_pbase(__allocate< class implementation < FUNCTION > >(::transfer(functionParam)))
   {

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

      m_pbase = ::transfer(__allocate< class implementation <FUNCTION > >(::transfer(functionParam)));

      return *this;

   }
   

   function& operator = (base * pbase)
   {

      m_pbase = pbase;

      return *this;

   }


   function & operator = (const function & function)
   {
      
      m_pbase = function.m_pbase; 
      
      return *this; 
   
   }


   function & operator = (function && function)
   {
      
      m_pbase = ::transfer(function.m_pbase); 
      
      return *this; 
   
   }


   function & operator = (nullptr_t)
   {

      clear();

      return *this;

   }

   explicit operator bool() const { return __pointer_is_set(m_pbase.m_p); }

   bool operator !() const { return __pointer_is_null(m_pbase.m_p); }

   bool operator == (const function & function) const { return m_pbase == function.m_pbase; }

   operator ::u32hash() const { return { (::u32)(::uptr)m_pbase.m_p }; }

};

//
//template < typename... types >
//class function_receptor < void(types...) > :
//   public function <  void(types...) >
//{
//public:
//
//   template < typename function >
//   function_receptor(function function) :
//      function <  void(types...) >(transfer_t{}, function)
//   {
//   }
//
//
//};



