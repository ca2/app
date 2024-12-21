// Created by camilo on 2022-03-20 11:35 <3ThomasBorregaardSorensen!!
#pragma once



//#define __pointer_is_null(p) (((uptr)(void *) p) < 4096)
//
//#define __pointer_is_set(p) (!__pointer_is_null(p))

//#include <ios>
//#include <ratio>

#include "acme/prototype/prototype/transfer.h"

#include "acme/prototype/prototype/pointer.h"

#include "acme/prototype/prototype/subparticle.h"

#include "acme/prototype/time/_time.h"

CLASS_DECL_ACME class ::time default_run_timeout();

template < typename BASE_TYPE >
class add_particle_timeout :
   virtual public BASE_TYPE
{
public:

   class ::time m_timeTimeout;

   add_particle_timeout() :
      m_timeTimeout(default_run_timeout())
   {



   }
   add_particle_timeout(const class ::time & timeTimeout)
   {

      if (timeTimeout.is_null())
      {

         m_timeTimeout = default_run_timeout();

      }
      else
      {

         m_timeTimeout = timeTimeout;

      }

   }

   void set_timeout(const class ::time & timeTimeout) override
   {

      m_timeTimeout = timeTimeout;
   }

   [[nodiscard]] class ::time timeout() const override
   {

      return m_timeTimeout;

   }
};


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

template < typename BASE_TYPE >
class function_composite_base :
   public add_particle_timeout < BASE_TYPE > 
{
public:

   using base = BASE_TYPE;

   ::pointer < base > m_pbase;

   function_composite_base(base * pbase, const class ::time & timeTimeout) :
      m_pbase(pbase),
      add_particle_timeout < BASE_TYPE >(timeTimeout)
   {

   }

};
#define FUNCTION_DEBUGGING 1
class function_common_base
{
public:
#if FUNCTION_DEBUGGING
   const char * m_pszDebug;
   ::huge_integer m_iDebug;
#endif
};

template < typename BASE_TYPE, typename COMPOSITE_TYPE >
class function_common :
   public function_common_base
{
public:

   using base = BASE_TYPE;
   using composite = COMPOSITE_TYPE;

   using base_implementation = add_particle_timeout < base >;

   pointer<base >     m_pbase;

   function_common() { }
   template < typename T2 >
   inline function_common(transfer_t, T2 * p) :m_pbase(place_t{}, p) {}
   template < typename T2 >
   inline function_common(place_t, T2 * p) : m_pbase(place_t{}, p) {}
   template < typename T2 >
   function_common(pointer < T2 > && p) : m_pbase(::transfer(p)) { }
   function_common(enum_as_lparam, iptr iptr) : m_pbase((::subparticle *)iptr) { }
   function_common(const function_common & function) : m_pbase(function.m_pbase) { }
   function_common(function_common && function) : m_pbase(::transfer(function.m_pbase)) {}
   ~function_common() { }


   void clear()
   {

      m_pbase.release();

   }


   function_common & operator = (const function_common & function)
   {

      m_pbase = function.m_pbase;

      return *this;

   }

   explicit operator bool() const { return ::is_set(this) && ::is_set(m_pbase); }

   bool operator !() const { return !this->operator bool(); }

   bool operator == (const function_common & function) const { return m_pbase == function.m_pbase; }

   operator ::subparticle * () const { return ::is_null(this) ? nullptr : m_pbase; }

   const ::subparticle * operator -> () const { return m_pbase; }

   ::subparticle * operator -> () { return m_pbase; }

   operator ::hash32() const
   {

      return { (unsigned int)(::uptr)m_pbase.m_p };

   };


   void construct(base * p, const class ::time & timeTimeout)
   {

      if (timeTimeout.is_null())
      {

         m_pbase = p;

         return;

      }

      auto paddparticletimeout = dynamic_cast <add_particle_timeout < base >*>(p);

      if (is_set(paddparticletimeout))
      {

         paddparticletimeout->set_timeout(timeTimeout);

         m_pbase = p;

         return;

      }

      m_pbase = __allocate composite(p, timeTimeout);

   }


   void set_timeout(const class time & timeTimeout)
   {

      ::pointer<add_particle_timeout<base>> pbase = m_pbase;

      if (!pbase)
      {

         m_pbase = __allocate composite(m_pbase, timeTimeout);

      }
      else
      {

         pbase->set_timeout(timeTimeout);

      }

   }

   class ::time timeout() const
   {

      return ::is_set(m_pbase) ? m_pbase->timeout() : default_run_timeout();

   }



};

//class function_base :
//   virtual public ::subparticle
//{
//public:
//
//
//   class ::time      m_timeTimeout;
//
//
//   function_base(const class ::time & timeTimeout = {})
//   {
//
//      if (timeTimeout.m_iSecond <= 0)
//      {
//
//         m_timeTimeout = default_run_timeout();
//
//      }
//      else
//      {
//
//         m_timeTimeout = timeTimeout;
//
//      }
//
//   }
//
//
//   void set_run_timeout(const class time & timeTimeout)  { m_timeTimeout = timeTimeout; }
//
//
//   class ::time get_run_timeout() const {return m_timeTimeout;}
//
//
//};
//

template < typename PRIMITIVE_FUNCTION >
concept primitive_function = ::std::is_base_of < ::function_common_base, PRIMITIVE_FUNCTION >::value;

namespace data
{
   template < primitive_function FUNCTION >
   class signal;
} // namespace data



template < typename PAYLOAD >
class function :
   public function_common_base
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


class function_composite_1 :
   public function_composite_base < ::subparticle >
{
public:

   function_composite_1(base * pbase, const class ::time & timeTimeout) :
      function_composite_base < ::subparticle >(pbase, timeTimeout)
   {

   }


   void operator()()
   {

      this->m_pbase->call();

   }


   void run() override
   {

      this->m_pbase->call();

   }


};


template < >
class function < void() > :
   public function_common < ::subparticle, ::function_composite_1 >
{
public:

   using base_function = function_common < ::subparticle, ::function_composite_1 >;

   template < typename ELEMENT >
   class implementation :
      public base_implementation
   {
   public:


      ELEMENT m_element;


      implementation(ELEMENT element, const class ::time & timeTimeout) :
         m_element(element),
         base_implementation(timeTimeout)
      {

         set_flag(e_flag_automatic_result_just_after_running);
         
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

   



   //::pointer < base > m_pbase;

   function() { }
   template < typename T2 >
   function(transfer_t, T2 * p) :base_function(place_t{}, p) {}
   template < typename T2 >
   function(place_t, T2 * p) : base_function(place_t{}, p) {}
   template < typename T2 >
   function(pointer < T2 > && p) : base_function(::transfer(p)) { }
   function(enum_as_lparam, iptr iptr) : base_function(e_as_lparam, iptr) { }
   function(const function & function) : base_function(function) { }
   function(function && function) : base_function(::transfer(function)) {}


   template < typename PREDICATE >
   function(const PREDICATE & predicate, const class time & timeTimeout = 0_s)
   {

      if constexpr(::std::is_same_v<PREDICATE, nullptr_t>)
      {


      }
      else if constexpr (::std::is_convertible_v<PREDICATE, ::uptr>
         && ::std::is_convertible_v<PREDICATE, lparam>)
      {

         this->construct((::subparticle*)(::uptr) predicate, timeTimeout);

      }
      else if constexpr (::primitive_subparticle_pointer<PREDICATE> )
      {

         this->construct(predicate, timeTimeout);

      }
      else if constexpr (::std::is_base_of_v<::subparticle, decay<PREDICATE> >)
      {

         this->construct(as_subparticle(predicate), timeTimeout);

      }
      else if constexpr(::std::is_same_v<::std::decay_t<PREDICATE>, payload >
         || ::std::is_same_v<::std::decay_t <PREDICATE> , property>)
      {

         this->construct(as_subparticle(predicate), timeTimeout);

      }
      else if constexpr(::std::is_same_v<PREDICATE, const function & >)
      {

         this->construct(predicate.m_pbase, timeTimeout);

      }
      else
      {

         this->m_pbase = __allocate implementation < PREDICATE > (predicate, timeTimeout);

      }

   }


   template < typename PREDICATE >
   function(enum_timeout, const class time & timeTimeout, PREDICATE predicateParam) :
      function(predicateParam, timeTimeout)
   {
   
   }


   ~function()
   {

   }


   void operator()()
   {

      m_pbase->call();

   }


   void operator()() const
   {

      m_pbase->call();

   }

   function & operator = (const function & function)
   {
      
      base_function::operator=(function);
      
      return *this;

   }

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
class function_base_2 :
   virtual public ::subparticle
{
public:

   virtual RETURN_TYPE operator()() = 0;

};

template < typename RETURN_TYPE >
class function_composite_2 :
   public function_composite_base < ::function_base_2 < RETURN_TYPE > >
{
public:

   using base = ::function_base_2 < RETURN_TYPE >;

   function_composite_2(base * pbase, const class ::time & timeTimeout) :
      function_composite_base < ::function_base_2 < RETURN_TYPE > >(pbase, timeTimeout)
   {

   }


   RETURN_TYPE operator()() override
   {

      return ::transfer(this->m_pbase->operator()());

   }

};


template < typename RETURN_TYPE >
class function < RETURN_TYPE() > :
   public function_common <
      ::function_base_2 < RETURN_TYPE >,
      ::function_composite_2 < RETURN_TYPE > 
   >
{
public:

   using base_function = function_common <
      ::function_base_2 < RETURN_TYPE >,
      ::function_composite_2 < RETURN_TYPE >
   >;

   using base_implementation = base_function::base_implementation;


   template < typename PREDICATE >
   class implementation :
      public base_implementation
   {
   public:


      PREDICATE m_predicate;


      implementation(PREDICATE implementation, const class ::time & timeTimeout = 0_s) :
           m_predicate(implementation),
         base_implementation(timeTimeout)
      {


      }


      RETURN_TYPE operator()()
      {

         return m_predicate();

      }

   };



   function() { }
   template < typename T2 >
   function(transfer_t, T2 * p) :base_function(place_t{}, p) {}
   template < typename T2 >
   function(place_t, T2 * p) : base_function(place_t{}, p) {}
   template < typename T2 >
   function(pointer < T2 > && p) : base_function(::transfer(p)) { }
   function(enum_as_lparam, iptr iptr) : base_function(e_as_lparam, iptr) { }
   function(const function & function) : base_function(function) { }
   function(function && function) : base_function(::transfer(function)) {}


   template < typename PREDICATE >
   function(const PREDICATE & predicate, const class ::time & timeTimeout = 0_s)
   {

      if constexpr(::std::is_same_v<PREDICATE, nullptr_t>)
      {


      }
      else if constexpr(::std::is_same_v<::std::decay_t<PREDICATE>, payload >
         || ::std::is_same_v<::std::decay_t <PREDICATE> , property>)
      {

         this->construct(as_subparticle(predicate), timeTimeout);

      }
      else if constexpr(::std::is_same_v<PREDICATE, const function & >)
      {

         this->construct(predicate.m_pbase, timeTimeout);

      }
      else
      {

         this->m_pbase = __allocate implementation < PREDICATE > (predicate, timeTimeout);

      }

   }


   template < typename PREDICATE >
   function(enum_timeout, const class time & timeTimeout, PREDICATE predicateParam) :
      function(predicateParam, timeTimeout)
   {

   }


   ~function()
   {

   }


   RETURN_TYPE operator()() const
   {

      return this->m_pbase->operator()();

   }


   //void clear() { m_pbase.release(); }

   //function & operator = (const function & function)
   //{

   //   m_pbase = function.m_pbase;

   //   return *this;

   //}


   /*explicit operator bool() const { return ::is_set(m_pbase); }

   bool operator !() const { return ::is_null(m_pbase); }*/


   //operator ::hash32() const 
   //{

   //   return { (unsigned int)(::uptr)m_pbase.m_p };

   //};

   //void set_run_timeout(const class time & timeTimeout)
   //{

   //   m_pbase->set_run_timeout(timeTimeout);
   //}

   //class ::time get_run_timeout() const { return ::is_set(m_pbase) ? m_pbase->get_run_timeout() : default_run_timeout(); }

   function & operator = (const function & function)
   {

      base_function::operator=(function);

      return *this;

   }


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
class function_base_3 :
   virtual public ::subparticle
{
public:

   virtual RETURN_TYPE operator()(TYPES... args) = 0;

};



template < typename RETURN_TYPE, typename... TYPES >
class function_composite_3 :
   virtual public ::function_composite_base < ::function_base_3 < RETURN_TYPE, TYPES... > >
{
public:


   using base = ::function_base_3 < RETURN_TYPE, TYPES... >;


   function_composite_3(base * pbase, const class ::time & timeTimeout) :
      function_composite_base < ::function_base_3 < RETURN_TYPE, TYPES... > >(pbase, timeTimeout)
   {

   }


   RETURN_TYPE operator()(TYPES... args) override
   {

      return m_predicate(args...);

   }

};


template < typename RETURN_TYPE, typename... TYPES >
class function < RETURN_TYPE(TYPES...) > :
   public function_common <
   function_base_3 < RETURN_TYPE, TYPES... > ,
   function_composite_3 < RETURN_TYPE, TYPES... >
   >
{
public:


   using base_function = function_common <
      function_base_3 < RETURN_TYPE, TYPES... >,
      function_composite_3 < RETURN_TYPE, TYPES... >
   >;

   using base_implementation = base_function::base_implementation;

   using base = base_function::base;


   template < typename PREDICATE >
   class implementation :
      public base_implementation
   {
   public:

      PREDICATE m_predicate;


      implementation(PREDICATE implementation, const class ::time & timeTimeout = 0_s) :
           m_predicate(implementation),
         base_implementation(timeTimeout)
      {


      }


      void get_debug_title(char * sz, character_count c) const override
      {

         ::strncpy(sz, "function with argument(s) and return type", c);

      }



      RETURN_TYPE operator()(TYPES... args) override
      {

         return m_predicate(args...);

      }

   };

   
   //pointer < base >     m_pbase;

   function() { }
   template < typename T2 >
   function(transfer_t, T2 * p) :base_function(place_t{}, p) {}
   template < typename T2 >
   function(place_t, T2 * p) : base_function(place_t{}, p) {}
   template < typename T2 >
   function(pointer < T2 > && p) : base_function(::transfer(p)) { }
   function(enum_as_lparam, iptr iptr) : base_function(e_as_lparam, iptr) { }
   function(const function & function) : base_function(function) { }
   function(function && function) : base_function(::transfer(function)) {}



   template < typename PREDICATE >
   function(const PREDICATE & predicate, const class ::time & timeTimeout = 0_s)
   {

      if constexpr(::std::is_same_v<PREDICATE, nullptr_t>)
      {


      }
      else if constexpr(::std::is_same_v<::std::decay_t<PREDICATE>, payload >
         || ::std::is_same_v<::std::decay_t <PREDICATE> , property>)
      {

         this->construct(as_subparticle(predicate), timeTimeout);

      }
      else if constexpr(::std::is_same_v<PREDICATE, const function & >)
      {

         this->construct(predicate.m_pbase, timeTimeout);

      }
      else
      {

         this->m_pbase = __allocate implementation < PREDICATE > (predicate, timeTimeout);

      }

   }

   template < typename PREDICATE >
   function(enum_timeout, const class time & timeTimeout, PREDICATE predicateParam) :
      function(predicateParam, timeTimeout)
   {

   }

   
   ~function()
   {

   }


   RETURN_TYPE operator()(TYPES... args) const
   {

      //ASSERT(m_pbase);

      return ((base *)this->m_pbase.m_p)->operator()(args...);

   }


   //void clear() { m_pbase.release(); }


   //function & operator = (const function & function)
   //{

   //   m_pbase = function.m_pbase;

   //   return *this;

   //}


   //explicit operator bool() const { return ::is_set(m_pbase); }

   //bool operator !() const { return ::is_null(m_pbase); }

   //bool operator == (const function & function) const { return m_pbase == function.m_pbase; }

   //operator ::hash32() const 
   //{

   //   return { (unsigned int)(::uptr)m_pbase.m_p };

   //}

   //void set_run_timeout(const class time & timeTimeout)
   //{

   //   m_pbase->set_run_timeout(timeTimeout);
   //}

   //class ::time get_run_timeout() const { return ::is_set(m_pbase) ? m_pbase->get_run_timeout() : default_run_timeout(); }

   function & operator = (const function & function)
   {

      base_function::operator=(function);

      return *this;

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
class function_base_4 :
   virtual public ::subparticle
{
public:

   virtual void operator()(TYPES... args) = 0;

};



template < typename... TYPES >
class function_composite_4 :
   virtual public ::function_composite_base < function_base_4 < TYPES... > >
{
public:

   using base_composite = ::function_composite_base < function_base_4 < TYPES... > >;

   using base = base_composite::base;

   function_composite_4(base * pbase, const class ::time & timeTimeout) :
      function_composite_base < ::function_base_4 < TYPES... > >(pbase, timeTimeout)
   {

   }

   void operator()(TYPES... args) override
   {

      this->m_pbase->operator()(args...);

   }

};


template < typename... TYPES >
class function < void(TYPES...) > :
   public function_common < 
   function_base_4 < TYPES... > ,
   function_composite_4 < TYPES... >
   >
{
public:


   using base_function = function_common <
      function_base_4 < TYPES... >,
      function_composite_4 < TYPES... >
   >;

   using base_implementation = base_function::base_implementation;

   using base = base_function::base;


   template < typename PREDICATE >
   class implementation :
      public base_implementation
   {
   public:


      PREDICATE m_predicate;


      implementation(PREDICATE implementation, const class ::time & timeTimeout = 0_s) :
         m_predicate(implementation),
         base_implementation(timeTimeout)
      {


      }

      
      ~implementation() override
      {

      
      }


      void operator()(TYPES... args) override
      {

         m_predicate(args...);

      }

   };

   
   //pointer < base >     m_pbase;

   function() { }
   template < typename T2 >
   function(transfer_t, T2 * p) :base_function(place_t{}, p) {}
   template < typename T2 >
   function(place_t, T2 * p) : base_function(place_t{}, p) {}
   template < typename T2 >
   function(pointer < T2 > && p) : base_function(::transfer(p)) { }
   function(enum_as_lparam, iptr iptr) : base_function(e_as_lparam, iptr) { }
   function(const function & function) : base_function(function) { }
   function(function && function) : base_function(::transfer(function)) {}


   template < typename PREDICATE >
   function(const PREDICATE & predicate, const class ::time & timeTimeout = 0_s) 
   {

      if constexpr(::std::is_same_v<PREDICATE, nullptr_t>)
      {


      }
      else if constexpr (::std::is_convertible_v<PREDICATE, base * >)
      {

         this->construct(predicate, timeTimeout);

      }
      else if constexpr(::std::is_same_v<::std::decay_t<PREDICATE>, payload >
         || ::std::is_same_v<::std::decay_t <PREDICATE> , property>)
      {

         this->construct(dynamic_cast < base * >(as_subparticle(predicate)), timeTimeout);

      }
      else if constexpr(::std::is_same_v<PREDICATE, const function & >)
      {

         this->construct(predicate.m_pbase, timeTimeout);

      }
      else
      {

         this->m_pbase = __allocate implementation < PREDICATE > (predicate);

      }

   }


   template < typename PREDICATE >
   function(enum_timeout, const class time & timeTimeout, PREDICATE predicateParam) :
      function(predicateParam, timeTimeout)
   {

   }



   ~function()
   {

   }


   void operator()(TYPES... args) const
   {

      //ASSERT(m_pbase);

      ((base *)this->m_pbase.m_p)->operator()(args...);

   }


   //void clear() { m_pbase.release(); }


   //function & operator = (const function & function)
   //{

   //   m_pbase = function.m_pbase;

   //   return *this;

   //}


   //explicit operator bool() const { return ::is_set(m_pbase.m_p); }

   //bool operator !() const { return ::is_null(m_pbase.m_p); }

   //bool operator == (const function & function) const { return m_pbase == function.m_pbase; }

   //operator ::hash32() const { return { (unsigned int)(::uptr)m_pbase.m_p }; }
   //
   //void set_run_timeout(const class time & timeTimeout)
   //{

   //   m_pbase->set_run_timeout(timeTimeout);
   //}

   //class ::time get_run_timeout() const { return ::is_set(m_pbase) ? m_pbase->get_run_timeout() : default_run_timeout(); }

   function & operator = (const function & function)
   {

      base_function::operator=(function);

      return *this;

   }



};







