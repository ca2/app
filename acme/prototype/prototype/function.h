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

// template < typename BASE_TYPE >
// class add_particle_timeout :
//    virtual public BASE_TYPE
// {
// public:
//
//    class ::time m_timeTimeout;
//
//    add_particle_timeout() :
//       m_timeTimeout(default_run_timeout())
//    {
//
//
//
//    }
//    add_particle_timeout(const class ::time & timeTimeout)
//    {
//
//       if (timeTimeout.is_null())
//       {
//
//          m_timeTimeout = default_run_timeout();
//
//       }
//       else
//       {
//
//          m_timeTimeout = timeTimeout;
//
//       }
//
//    }
//
//    void set_timeout(const class ::time & timeTimeout) override
//    {
//
//       m_timeTimeout = timeTimeout;
//    }
//
//    [[nodiscard]] class ::time timeout() const override
//    {
//
//       return m_timeTimeout;
//
//    }
// };


template < typename ENTITY, typename... ARGUMENTS >
concept callable = ::std::is_invocable< ENTITY, ARGUMENTS... >::type;

template < typename ENTITY, typename RESULT, typename... ARGUMENTS >
concept callable_with_result = ::std::is_invocable_r< RESULT, ENTITY, ARGUMENTS... >::type;

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



///#define _as(p) { e_use, p }
//
// template < typename BASE_TYPE >
// class function_composite_base :
//    //public add_particle_timeout < BASE_TYPE >
// public  BASE_TYPE
// {
// public:
//
//    using base = BASE_TYPE;
//
//    ::pointer < base > m_pbase;
//
//    function_composite_base(base * pbase, const class ::time & timeTimeout) :
//       m_pbase(pbase)
//    //,      add_particle_timeout < BASE_TYPE >(timeTimeout)
//    {
//
//    }
//
// };
#define FUNCTION_DEBUGGING 1
class function_common_base
{
public:
#if FUNCTION_DEBUGGING
   const_char_pointer m_pszDebug;
   long long m_iDebug;
#endif
   class ::time m_timeTimeout;


   function_common_base(const class ::time &timeTimeout = default_run_timeout()) :
      m_timeTimeout(timeTimeout)
   {

   }


   class ::time timeout() const
   {
   
      return m_timeTimeout; 
   
   } 


   void set_timeout(const class ::time & timeTimeout)
   {
      m_timeTimeout = timeTimeout; 
   
   }


};


// template < typename BASE_TYPE, typename COMPOSITE_TYPE >
// class function_common :
//    public function_common_base
// {
// public:
//
//    using base = BASE_TYPE;
//    using composite = COMPOSITE_TYPE;
//
//    //using base_implementation = add_particle_timeout < base >;
//    using  base_implementation = base;
//
//    pointer<base >     m_pbase;
//
//    function_common() { }
//    template < typename T2 >
//    inline function_common(transfer_t, T2 * p) :m_pbase(place_t{}, p) {}
//    template < typename T2 >
//    inline function_common(place_t, T2 * p) : m_pbase(place_t{}, p) {}
//    template < typename T2 >
//    function_common(pointer < T2 > && p) : m_pbase(::transfer(p)) { }
//    function_common(enum_as_lparam, iptr iptr) : m_pbase((::subparticle *)iptr) { }
//    function_common(const function_common & function) : m_pbase(function.m_pbase) { }
//    function_common(function_common && function) : m_pbase(::transfer(function.m_pbase)) {}
//    ~function_common() { }
//
//
//    void clear()
//    {
//
//       m_pbase.release();
//
//    }
//
//
//    function_common & operator = (const function_common & function)
//    {
//
//       m_pbase = function.m_pbase;
//
//       return *this;
//
//    }
//
//    explicit operator bool() const { return ::is_set(this) && ::is_set(m_pbase); }
//
//    bool operator !() const { return !this->operator bool(); }
//
//    bool operator == (const function_common & function) const { return m_pbase == function.m_pbase; }
//
//    operator ::subparticle * () const { return ::is_null(this) ? nullptr : m_pbase; }
//
//    const ::subparticle * operator -> () const { return m_pbase; }
//
//    ::subparticle * operator -> () { return m_pbase; }
//
//    operator ::hash32() const
//    {
//
//       return { (unsigned int)(::uptr)m_pbase.m_p };
//
//    };
//
//
//    void construct(base * p, const class ::time & timeTimeout)
//    {
//
//       m_pbase = p;
//
//       m_timeTimeout = timeTimeout;
//
//       // if (timeTimeout.is_null())
//       // {
//       //
//       //    m_pbase = p;
//       //
//       //    return;
//       //
//       // }
//       //
//       // auto paddparticletimeout = dynamic_cast <add_particle_timeout < base >*>(p);
//       //
//       // if (is_set(paddparticletimeout))
//       // {
//       //
//       //    paddparticletimeout->set_timeout(timeTimeout);
//       //
//       //    m_pbase = p;
//       //
//       //    return;
//       //
//       // }
//       //
//       // m_pbase = øallocate composite(p, timeTimeout);
//
//    }
//
//
//    void set_timeout(const class time & timeTimeout)
//    {
//
//       ::pointer<add_particle_timeout<base>> pbase = m_pbase;
//
//       if (!pbase)
//       {
//
//          m_pbase = øallocate composite(m_pbase, timeTimeout);
//
//       }
//       else
//       {
//
//          pbase->set_timeout(timeTimeout);
//
//       }
//
//    }
//
//    class ::time timeout() const
//    {
//
//       return ::is_set(m_pbase) ? m_pbase->timeout() : default_run_timeout();
//
//    }
//
//
//
// };

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
concept prototype_function = ::std::is_base_of < ::function_common_base, PRIMITIVE_FUNCTION >::value;

namespace data
{
   template < prototype_function FUNCTION >
   class signal;
} // namespace data


template <typename PROCEDURE >
concept prototype_pure_procedure =
   requires(PROCEDURE procedure)
{

   { procedure() } -> std::same_as<void>;

};


template < typename PROCEDURE >
requires(prototype_pure_procedure<PROCEDURE>)
class pure_procedure :
   virtual public ::subparticle
{
public:


   PROCEDURE m_procedure;

   pure_procedure(PROCEDURE procedure) :
   m_procedure(procedure)
   {


   }


   void operator()() override
   {

      this->m_procedure();

   }


   void run() override
   {

      this->m_procedure(); 
   
   }


};


// class function_composite_1 :
//    public function_composite_base < ::subparticle >
// {
// public:
//
//
//    function_composite_1(base * pbase, const class ::time & timeTimeout) :
//       function_composite_base < ::subparticle >(pbase, timeTimeout)
//    {
//
//
//    }
//
//
//    void operator()() override
//    {
//
//       this->m_pbase->call();
//
//    }
//
//
// };


template < >
class function < void() > :
   public ::function_common_base,
   public ::pointer < ::subparticle >
{
public:

   
   using base = ::subparticle;

   using base_pointer = ::pointer < ::subparticle >;

   
   // template < typename ELEMENT >
   // class implementation :
   //    public base_implementation
   // {
   // public:
   //
   //
   //    ELEMENT m_element;
   //
   //
   //    implementation(ELEMENT element, const class ::time & timeTimeout) :
   //       m_element(element),
   //       base_implementation(timeTimeout)
   //    {
   //
   //       set_flag(e_flag_automatic_result_just_after_running);
   //
   //    }
   //
   //
   //    void run() override
   //    {
   //
   //       m_element();
   //
   //    }
   //
   //
   // };

   



   //::pointer < base > m_pbase;

   function() { }
   // template < typename T2 >
   // function(transfer_t, T2 * p) :base_function(place_t{}, p) {}
   // template < typename T2 >
   // function(place_t, T2 * p) : base_function(place_t{}, p) {}
   // template < typename T2 >
   // function(pointer < T2 > && p) : base_function(::transfer(p)) { }
   // function(enum_as_lparam, iptr iptr) : base_function(e_as_lparam, iptr) { }
   // function(const function & function) : base_function(function) { }
   // function(function && function) : base_function(::transfer(function)) {}

   function(::subparticle * psubparticle, const class ::time & timeTimeout = 0_s) :
   function_common_base(timeTimeout),
   base_pointer(psubparticle)
   {

   }


   function(::lparam & lparam, const class ::time &timeTimeout = 0_s) :
       function_common_base(timeTimeout), base_pointer(lparam)
   {
   }



   template < typename PROCEDURE >
   requires(prototype_pure_procedure<PROCEDURE>)
   function(PROCEDURE procedure, const class time & timeTimeout = 0_s) :
      function_common_base(timeTimeout), base_pointer(øallocate pure_procedure(procedure))
   {

      // if constexpr(::std::is_same_v<PROCEDURE, nullptr_t>)
      // {
      //
      //
      // }
      // else if constexpr (::std::is_convertible_v<PROCEDURE, ::uptr>
      //    && ::std::is_convertible_v<PROCEDURE, lparam>)
      // {
      //
      //    this->construct((::subparticle*)(::uptr) procedure, timeTimeout);
      //
      // }
      // else if constexpr (::prototype_subparticle_pointer<PROCEDURE> )
      // {
      //
      //    this->construct(procedure, timeTimeout);
      //
      // }
      // else if constexpr (::std::is_base_of_v<::subparticle, decay<PROCEDURE> >)
      // {
      //
      //    this->construct(as_subparticle(procedure), timeTimeout);
      //
      // }
      // else if constexpr(::std::is_same_v<::std::decay_t<PROCEDURE>, payload >
      //    || ::std::is_same_v<::std::decay_t <PROCEDURE> , property>)
      // {
      //
      //    this->construct(as_subparticle(procedure), timeTimeout);
      //
      // }
      // else if constexpr(::std::is_same_v<const PROCEDURE &, const function & >)
      // {
      //
      //    this->m_pbase = procedure.m_pbase;
      //
      //    this->m_pbase->set_timeout(timeTimeout);
      //
      //    //this->construct(procedure.m_pbase, timeTimeout);
      //
      // }
      // else
      // {
      //
      //    this->m_pbase = øallocate implementation (procedure, timeTimeout);
      //
      // }

   }


   template < typename PROCEDURE >
   function(enum_timeout, const class time & timeTimeout, PROCEDURE procedureParam) :
      function(procedureParam, timeTimeout)
   {
   
   }


   ~function()
   {

   }


   void operator()() const
   {

      this->m_p->operator()();

   }


   function & operator = (const function & function)
   {
      
      base_pointer::operator=(function);
      
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


// template < typename RETURN_TYPE >
// class function_base_2 :
//    virtual public ::subparticle
// {
// public:
//
//
//    virtual RETURN_TYPE get() = 0;
//
//
// };
//
//
// template < typename RETURN_TYPE >
// class function_composite_2 :
//    public function_composite_base < ::function_base_2 < RETURN_TYPE > >
// {
// public:
//
//    using base = ::function_base_2 < RETURN_TYPE >;
//
//    function_composite_2(base * pbase, const class ::time & timeTimeout) :
//       function_composite_base < ::function_base_2 < RETURN_TYPE > >(pbase, timeTimeout)
//    {
//
//    }
//
//
//    RETURN_TYPE get() override
//    {
//
//       return ::transfer(this->m_pbase->operator()());
//
//    }
//
// };


template <typename FUNCTION, typename RETURN_TYPE>
concept prototype_return_function =
   requires(FUNCTION function)
{

   { function() } -> std::same_as<RETURN_TYPE>;

};


template < typename RETURN_TYPE >
class return_function_base :
   virtual public ::subparticle
{
public:


   virtual RETURN_TYPE function_get() = 0;


};



template < typename FUNCTION, typename RETURN_TYPE >
class return_function :
   public return_function_base<RETURN_TYPE>
{
public:


   FUNCTION m_function;


   return_function(FUNCTION function) :
        m_function(function)
   {


   }
   //
   //
   // void get_debug_title(char * sz, character_count c) override
   // {
   //
   //    ::string_count_copy(sz, "a procedure", c);
   //
   // }

   RETURN_TYPE function_get()
   {
      
      return this->m_function(); 
   
   }


};



template < typename RETURN_TYPE >
class function < RETURN_TYPE() > : 
   public function_common_base,
   public ::pointer<::return_function_base <RETURN_TYPE >>
{
public:

   using base = ::return_function_base <RETURN_TYPE >;

   using base_pointer = ::pointer<::return_function_base <RETURN_TYPE >>;




   function() { }
   function(nullptr_t)   {}
   // template < typename T2 >
   // function(transfer_t, T2 * p) :base_function(place_t{}, p) {}
   // template < typename T2 >
   // function(place_t, T2 * p) : base_function(place_t{}, p) {}
   // template < typename T2 >
   // function(pointer < T2 > && p) : base_function(::transfer(p)) { }
   // function(enum_as_lparam, iptr iptr) : base_function(e_as_lparam, iptr) { }
   // function(const function & function) : base_function(function) { }
   // function(function && function) : base_function(::transfer(function)) {}


   template < typename FUNCTION >
   requires(prototype_return_function<FUNCTION, RETURN_TYPE > )
   function(FUNCTION functionParam, const class ::time & timeTimeout = 0_s) :
   function_common_base(timeTimeout),
   base_pointer(øallocate return_function<FUNCTION, RETURN_TYPE>(functionParam))
   {

      // if constexpr(::std::is_same_v<FUNCTION, nullptr_t>)
      // {
      //
      //
      // }
      // else if constexpr(::std::is_same_v<::std::decay_t<FUNCTION>, payload >
      //    || ::std::is_same_v<::std::decay_t <FUNCTION> , property>)
      // {
      //
      //    this->construct(as_subparticle(function), timeTimeout);
      //
      // }
      // else if constexpr(::std::is_same_v<FUNCTION, const function & >)
      // {
      //
      //    this->construct(function.m_pbase, timeTimeout);
      //
      // }
      // else
      // {
      //
      //    this->m_pbase = øallocate implementation<FUNCTION >(function, timeTimeout);
      //
      // }

   }


   template < typename FUNCTION >
   function(enum_timeout, const class time & timeTimeout, FUNCTION functionParam) :
      function(functionParam, timeTimeout)
   {

   }


   ~function()
   {

   }


   RETURN_TYPE operator()() const
   {

      return this->m_p->function_get();

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

      base_pointer::operator=(function);

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


template <typename FUNCTION, typename RETURN_TYPE, typename... ARGUMENTS>
concept prototype_arguments_function =
   requires(FUNCTION function, ARGUMENTS... arguments)
{

   { function(arguments...) } -> std::same_as<RETURN_TYPE>;

};


template < typename RETURN_TYPE, typename... ARGUMENTS >
class arguments_function_base :
   virtual public ::subparticle
{
public:


   virtual RETURN_TYPE operator()(ARGUMENTS... arguments) = 0;


};



template < typename FUNCTION, typename RETURN_TYPE, typename... ARGUMENTS >
   requires(prototype_arguments_function<FUNCTION, RETURN_TYPE, ARGUMENTS...>)
class arguments_function :
   virtual public ::arguments_function_base < RETURN_TYPE, ARGUMENTS... >
{
public:


   FUNCTION m_function;


   //using base = ::function_base_3 < RETURN_TYPE, ARGUMENTS... >;


   arguments_function(FUNCTION function) :
      m_function(function)
   {

   }


   RETURN_TYPE operator()(ARGUMENTS... arguments) override
   {

      return m_function(arguments...);

   }

};


template < typename RETURN_TYPE, typename... ARGUMENTS >
class function < RETURN_TYPE(ARGUMENTS...) > :
   public function_common_base,
   public ::pointer <arguments_function_base< RETURN_TYPE, ARGUMENTS...>>
{
public:


   using base = arguments_function_base< RETURN_TYPE, ARGUMENTS...>;

   using base_pointer = ::pointer < arguments_function_base< RETURN_TYPE, ARGUMENTS...> >;

   // template < typename FUNCTION >
   // class implementation :
   //    public base_implementation
   // {
   // public:
   //
   //    FUNCTION m_function;
   //
   //
   //    implementation(FUNCTION implementation, const class ::time & timeTimeout = 0_s) :
   //         m_function(implementation),
   //       base_implementation(timeTimeout)
   //    {
   //
   //
   //    }
   //
   //
   //    void get_debug_title(char * sz, character_count c) const override
   //    {
   //
   //       ::string_count_copy(sz, "function with argument(s) and return type", c);
   //
   //    }
   //
   //
   //    RETURN_TYPE operator()(ARGUMENTS... arguments) override
   //    {
   //
   //       return m_function(arguments...);
   //
   //    }
   //
   //
   // };

   
   //pointer < base >     m_pbase;

   function() { }
   function(nullptr_t) {}
   // template < typename T2 >
   // function(transfer_t, T2 * p) :base_function(place_t{}, p) {}
   // template < typename T2 >
   // function(place_t, T2 * p) : base_function(place_t{}, p) {}
   // template < typename T2 >
   // function(pointer < T2 > && p) : base_function(::transfer(p)) { }
   // function(enum_as_lparam, iptr iptr) : base_function(e_as_lparam, iptr) { }
   // function(const function & function) : base_function(function) { }
   // function(function && function) : base_function(::transfer(function)) {}



   template < typename FUNCTION >
   requires(prototype_arguments_function<FUNCTION, RETURN_TYPE, ARGUMENTS...>)
   function(FUNCTION functionParam, const class ::time & timeTimeout = 0_s) :
   function_common_base(timeTimeout),
   base_pointer(øallocate arguments_function<FUNCTION, RETURN_TYPE, ARGUMENTS...>(functionParam))
   {

      // if constexpr(::std::is_same_v<FUNCTION, nullptr_t>)
      // {
      //
      //
      // }
      // else if constexpr(::std::is_same_v<::std::decay_t<FUNCTION>, payload >
      //    || ::std::is_same_v<::std::decay_t <FUNCTION> , property>)
      // {
      //
      //    this->construct(as_subparticle(function), timeTimeout);
      //
      // }
      // else if constexpr(::std::is_same_v<FUNCTION, const function & >)
      // {
      //
      //    this->construct(function.m_pbase, timeTimeout);
      //
      // }
      // else
      // {
      //
      //    this->m_pbase = øallocate implementation <FUNCTION > (function, timeTimeout);
      //
      // }

   }

   template < typename FUNCTION >
   requires(prototype_arguments_function<FUNCTION, RETURN_TYPE, ARGUMENTS...>)
   function(enum_timeout, const class time & timeTimeout, FUNCTION functionParam) :
      function(functionParam, timeTimeout)
   {

   }

   function(base * pbase, const class ::time & timeTimeout) :
   function_common_base(timeTimeout),
   base_pointer(pbase)
   {



   }

   
   ~function()
   {

   }


   RETURN_TYPE operator()(ARGUMENTS... arguments) const
   {

      //ASSERT(m_pbase);

      return this->m_p->operator()(arguments...);

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

      base_pointer::operator=(function);

      return *this;

   }


};

//
//template < typename RETURN_TYPE, typename... ARGUMENTS >
//class function_receptor < RETURN_TYPE(ARGUMENTS...) > :
//   public function <  RETURN_TYPE(ARGUMENTS...) >
//{
//public:
//
//   template < typename PAYLOAD >
//   function_receptor(PAYLOAD function) :
//      function <  RETURN_TYPE(ARGUMENTS...) >(transfer_t{}, function)
//   {
//   }
//
//
//};


template <typename PROCEDURE, typename... ARGUMENTS>
concept prototype_arguments_procedure =
   requires(PROCEDURE procedure, ARGUMENTS... arguments)
{

   { procedure(arguments...) } -> std::same_as<void>;

};


template < typename ... ARGUMENTS>
class arguments_procedure_base :
   virtual public ::subparticle
{
public:

   virtual void operator()(ARGUMENTS... arguments)= 0;

};


template < typename PROCEDURE, typename ... ARGUMENTS >
class arguments_procedure :
   virtual public ::arguments_procedure_base<ARGUMENTS...>
{
public:

   PROCEDURE m_procedure;

   arguments_procedure(PROCEDURE procedure) :
   m_procedure(procedure)
   {


   }

   //function_base_4(const ::e_flag & eflag, const ::e_status & estatus = undefined) :
   //   ::quantum(eflag, estatus),
   //   ::subparticle(eflag, estatus)
   //{


   //}
   //
   //
   // function_base_4(const function_base_4 & functionbase4) :
   //    ::quantum(functionbase4),
   //    ::subparticle(functionbase4)
   // {
   //
   //
   // }
   //
   // function_base_4(function_base_4&& functionbase4) :
   //    ::quantum(::transfer(functionbase4)),
   //    ::subparticle(::transfer(functionbase4))
   // {
   //
   //
   // }
   //
   //
   // ~function_base_4() override
   // {
   //
   //
   // }
   //
   //
   // virtual void operator()(ARGUMENTS... arguments)
   // {
   //
   //
   // }

   virtual void operator()(ARGUMENTS... arguments)
   {

      this->m_procedure(arguments...);

   }


};


//
// template < typename... ARGUMENTS >
// class function_composite_4 :
//    virtual public ::function_composite_base < function_base_4 < ARGUMENTS... > >
// {
// public:
//
//    using base_composite = ::function_composite_base < function_base_4 < ARGUMENTS... > >;
//
//    using base = base_composite::base;
//
//    function_composite_4(base * pbase, const class ::time & timeTimeout) :
//       function_composite_base < ::function_base_4 < ARGUMENTS... > >(pbase, timeTimeout)
//    {
//
//    }
//
//    void operator()(ARGUMENTS... arguments) override
//    {
//
//       this->m_pbase->operator()(arguments...);
//
//    }
//
// };
//
//
// template < typename... ARGUMENTS >
// using base_function_4 = function_common <
//    function_base_4 < ARGUMENTS... >,
//    function_composite_4 < ARGUMENTS... >
// >;
//
//
// template < typename PROCEDURE, typename... ARGUMENTS >
// class function_4_implementation :
//    //virtual public add_particle_timeout < function_base_4 < ARGUMENTS... > >
//    public function_base_4 < ARGUMENTS...>
// {
// public:
//
//
//    PROCEDURE m_function;
//
//
//    function_4_implementation(PROCEDURE implementation, const class ::time & timeTimeout = 0_s) :
//       m_function(implementation),
//       //add_particle_timeout < function_base_4 < ARGUMENTS... > >(timeTimeout)
//    function_base_4 < ARGUMENTS... >(timeTimeout)
//    //function_common_base
//    {
//
//
//    }
//
//
//    ~function_4_implementation() override
//    {
//
//
//    }
//
//
//    void get_debug_title(char * sz, character_count c) const override
//    {
//
//       ::string_count_copy(sz, "function with argument(s) and no return type", c);
//
//    }
//
//
//    void operator()(ARGUMENTS... arguments) override
//    {
//
//       m_function(arguments...);
//
//    }
//
//
// };



template < typename... ARGUMENTS >
class function < void(ARGUMENTS...) > :
   public function_common_base,
   public ::pointer < arguments_procedure_base <ARGUMENTS...> >
{
public:


   using base = arguments_procedure_base <ARGUMENTS...>;
   using base_pointer = ::pointer < arguments_procedure_base <ARGUMENTS...> >;

   //using base_implementation = base_function::base_implementation;

   //using base = base_function_4 < ARGUMENTS... > ::base;




   //pointer < base >     m_pbase;

   function() { }
   function(nullptr_t) {}
   //template < typename T2 >
   //function(transfer_t, T2 * p) :base_function_4 < ARGUMENTS... > (place_t{}, p) {}
   //template < typename T2 >
   //function(place_t, T2 * p) : base_function_4 < ARGUMENTS... > (place_t{}, p) {}
   //template < typename T2 >
   //function(pointer < T2 > && p) : base_function_4 < ARGUMENTS... > (::transfer(p)) { }
   //function(enum_as_lparam, iptr iptr) : base_function_4 < ARGUMENTS... > (e_as_lparam, iptr) { }
   //function(const function & function) : base_function_4 < ARGUMENTS... > (function) { }
   //function(function && function) : base_function_4 < ARGUMENTS... > (::transfer(function)) {}


   template < typename PROCEDURE >
   requires(prototype_arguments_procedure<PROCEDURE, ARGUMENTS ...>)
   function(PROCEDURE procedure, const class ::time & timeTimeout = 0_s) :
   function_common_base(timeTimeout),
   base_pointer(øallocate arguments_procedure<PROCEDURE, ARGUMENTS...>(procedure))
   //
   //      requires (::std::is_convertible_v<PROCEDURE, :: >)
   {

      //this->construct(procedure, timeTimeout);

   }


   function(base * pbase, const class ::time & timeTimeout = 0_s) :
      function_common_base(timeTimeout),
      base_pointer(pbase)
   {

      //this->construct(procedure, timeTimeout);

   }


   template < typename PAYLOAD_WITH_PROCEDURE >
   requires (::is_same<::std::decay_t<PAYLOAD_WITH_PROCEDURE>, payload >
|| ::is_same<::std::decay_t <PAYLOAD_WITH_PROCEDURE>, property>)
   function(PAYLOAD_WITH_PROCEDURE payloadWithProcedure, const class ::time& timeTimeout = 0_s) :
   function_common_base(timeTimeout),
   base_pointer(dynamic_cast <base*>(as_subparticle(payloadWithProcedure)))
   {

      //this->construct(dynamic_cast <base*>(as_subparticle(payloadWithProcedure)), timeTimeout);

   }


   // template < typename PROCEDURE >
   // function(PROCEDURE procedure, const class ::time& timeTimeout = 0_s)
   //    requires (LambdaWithVoidAndarguments< PROCEDURE, ARGUMENTS... >)
   // {
   //
   //    this->m_pbase = øallocate function_4_implementation< PROCEDURE, ARGUMENTS... >(procedure, timeTimeout);
   //
   // }


   template < typename PROCEDURE >
   requires(prototype_arguments_procedure<PROCEDURE, ARGUMENTS ...>)
   function(enum_timeout, const class time & timeTimeout, PROCEDURE procedure) :
      function(procedure, timeTimeout)
   {

   }



   ~function()
   {

   }


   void operator()(ARGUMENTS... arguments) const
   {

      this->m_p->operator()(arguments...);

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

      base_pointer::operator=(function);

      return *this;

   }



};


class topic;

class handler_context;

using signal_handler = ::function < void(::topic *, ::handler_context *) >;





