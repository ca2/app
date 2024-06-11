// Created by camilo on 2022-03-20 11:35 <3ThomasBorregaardSorensen!!
#pragma once


//#define __pointer_is_null(p) (((uptr)(void *) p) < 4096)
//
//#define __pointer_is_set(p) (!__pointer_is_null(p))

//#include <ios>
//#include <ratio>

#include "acme/primitive/primitive/transfer.h"

#include "acme/primitive/primitive/pointer.h"

#include "acme/primitive/primitive/subparticle.h"

#include "acme/primitive/time/_time.h"

template < typename ENTITY, typename... TYPES >
concept callable = ::std::is_invocable< ENTITY, TYPES... >::type;

template < typename ENTITY, typename RESULT, typename... TYPES >
concept callable_with_result = ::std::is_invocable_r< RESULT, ENTITY, TYPES... >::type;

template <typename T>
constexpr bool is_lvalue_helper = std::is_lvalue_reference<T>::value;

template <typename T>
constexpr bool is_xvalue_helper = std::is_rvalue_reference<T>::value;

template <typename T>
constexpr bool is_prvalue_helper = !(is_lvalue_helper<T> || is_xvalue_helper<T>);

template <typename T>
constexpr bool is_rvalue_helper = is_xvalue_helper<T> || is_prvalue_helper<T>;

template <typename T>
constexpr bool is_glvalue_helper = is_xvalue_helper<T> || is_lvalue_helper<T>;

#define is_left_instance(type_instance) is_lvalue_helper<decltype((type_instance))>
#define is_xvalue(type_instance) is_xvalue_helper<decltype((type_instance))>
#define is_prvalue(type_instance)is_prvalue_helper<decltype((type_instance))>
#define is_right_instance(type_instance) is_rvalue_helper<decltype((type_instance))>
#define is_glvalue(type_instance)is_glvalue_helper<decltype((type_instance))>


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


template < primitive_function FUNCTION >
class signal;


template < typename PAYLOAD >
class function :
   public function_common
{

};

//template < typename PAYLOAD >
//class function_receptor :
//   public function < PAYLOAD >
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


   using base = ::subparticle;


   template < typename ELEMENT >
   class implementation :
      virtual public base
   {
   public:


      ELEMENT m_element;


      implementation(ELEMENT element) :
         m_element(element)
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


   ::pointer < base > m_pbase;


   
   function()
   {

   }


   function(const pointer < ::subparticle > & p) :
      m_pbase(p)
   {

   }


   function(pointer < ::subparticle > && p) :
      m_pbase(p)
   {
      

   }


   function(enum_as_lparam, iptr iptr) :
      m_pbase((::subparticle *)iptr)
   {

   }


   function(use_t, base * p) :
      m_pbase(p)
   {

   }


   function(transfer_t, base * p) :
      m_pbase(transfer_t{}, p)
   {

   }


   //template < typename PREDICATE >
   //function(function_t, PREDICATE predicateParam) :
   //   m_pbase(transfer_t{}, __new< class implementation <PREDICATE > >(predicateParam))
   //{

   //}



   template < typename PREDICATE >
   function(const PREDICATE & predicate) :
      function()
   {

      if constexpr(::std::is_same_v<PREDICATE, nullptr_t>)
      {


      }
      else if constexpr(::std::is_same_v<::std::decay_t<PREDICATE>, payload >
         || ::std::is_same_v<::std::decay_t <PREDICATE> , property>)
      {

         m_pbase = as_subparticle(predicate);

      }
      else if constexpr(::std::is_same_v<PREDICATE, const function & >)
      {

         m_pbase = predicate.m_pbase;

      }
      else
      {

         m_pbase.transfer(__new< class implementation < PREDICATE > >(predicate));

      }

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

   void clear()
   {

      m_pbase.release();

   }


   function & operator = (const function & function)
   {

      m_pbase = function.m_pbase;

      return *this;

   }

   explicit operator bool() const { return ::is_set(this) && ::is_set(m_pbase); }

   bool operator !() const { return !this->operator bool(); }

   operator ::subparticle *() const { return ::is_null(this) ? nullptr : m_pbase; }

   const ::subparticle * operator -> () const { return m_pbase; }

   ::subparticle * operator -> () { return m_pbase; }
   

};
//
//template < >
//class function_receptor < void() > :
//   public function < void() >
//{
//public:
//
//   template < typename PAYLOAD >
//   function_receptor(PAYLOAD function) :
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
      virtual public ::subparticle
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


      implementation(PREDICATE implementation) :
           m_predicate(implementation)
      {


      }


      RETURN_TYPE operator()()
      {

         return m_predicate();

      }

   };

   pointer<base >     m_pbase;


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
   //   m_pbase(transfer_t{}, __new< class implementation <PREDICATE > >(predicateParam))
   //{

   //}


   template < typename PREDICATE >
   function(const PREDICATE & predicate) :
      function()
   {

      if constexpr(::std::is_same_v<PREDICATE, nullptr_t>)
      {


      }
      else if constexpr(::std::is_same_v<::std::decay_t<PREDICATE>, payload >
         || ::std::is_same_v<::std::decay_t <PREDICATE> , property>)
      {

         m_pbase = as_subparticle(predicate);

      }
      else if constexpr(::std::is_same_v<PREDICATE, const function & >)
      {

         m_pbase = predicate.m_pbase;

      }
      else
      {

         m_pbase.transfer(__new< class implementation < PREDICATE > >(predicate));

      }

   }


   
   function(transfer_t, base * pbase) :
      m_pbase(transfer_t{}, pbase)
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

   function & operator = (const function & function)
   {

      m_pbase = function.m_pbase;

      return *this;

   }


   explicit operator bool() const { return ::is_set(m_pbase); }

   bool operator !() const { return ::is_null(m_pbase); }


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
//   template < typename PAYLOAD >
//   function_receptor(PAYLOAD function) :
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
      virtual public ::subparticle
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


      implementation(PREDICATE implementation) :
           m_predicate(implementation)
      {


      }



      RETURN_TYPE operator()(TYPES... args) override
      {

         return m_predicate(args...);

      }

   };

   
   pointer < base >     m_pbase;


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


   template < typename PREDICATE >
   function(const PREDICATE & predicate) :
      function()
   {

      if constexpr(::std::is_same_v<PREDICATE, nullptr_t>)
      {


      }
      else if constexpr(::std::is_same_v<::std::decay_t<PREDICATE>, payload >
         || ::std::is_same_v<::std::decay_t <PREDICATE> , property>)
      {

         m_pbase = as_subparticle(predicate);

      }
      else if constexpr(::std::is_same_v<PREDICATE, const function & >)
      {

         m_pbase = predicate.m_pbase;

      }
      else
      {

         m_pbase.transfer(__new< class implementation < PREDICATE > >(predicate));

      }

   }

   
   
   function(transfer_t, base * pbase) :
      m_pbase(transfer_t{}, pbase)
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


   function & operator = (const function & function)
   {

      m_pbase = function.m_pbase;

      return *this;

   }


   explicit operator bool() const { return ::is_set(m_pbase); }

   bool operator !() const { return ::is_null(m_pbase); }

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
//   template < typename PAYLOAD >
//   function_receptor(PAYLOAD function) :
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
      virtual public ::subparticle
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


      implementation(PREDICATE implementation) :
         m_predicate(implementation)
      {


      }


      void operator()(TYPES... args) override
      {

         m_predicate(args...);

      }

   };

   
   pointer < base >     m_pbase;


   function()
   {

   }


   function(use_t, base * p) :
      m_pbase(p)
   {

   }


   function(transfer_t, base * p) :
      m_pbase(transfer_t{}, p)
   {

   }


   template < typename PREDICATE >
   function(const PREDICATE & predicate) :
      function()
   {

      if constexpr(::std::is_same_v<PREDICATE, nullptr_t>)
      {


      }
      else if constexpr(::std::is_same_v<::std::decay_t<PREDICATE>, payload >
         || ::std::is_same_v<::std::decay_t <PREDICATE> , property>)
      {

         m_pbase = as_subparticle(predicate);

      }
      else if constexpr(::std::is_same_v<PREDICATE, const function & >)
      {

         m_pbase = predicate.m_pbase;

      }
      else
      {

         m_pbase.transfer(__new< class implementation < PREDICATE > >(predicate));

      }

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


   function & operator = (const function & function)
   {

      m_pbase = function.m_pbase;

      return *this;

   }


   explicit operator bool() const { return ::is_set(m_pbase.m_p); }

   bool operator !() const { return ::is_null(m_pbase.m_p); }

   bool operator == (const function & function) const { return m_pbase == function.m_pbase; }

   operator ::u32hash() const { return { (::u32)(::uptr)m_pbase.m_p }; }
   

};







