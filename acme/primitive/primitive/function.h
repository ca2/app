// Created by camilo on 2022-03-20 11:35 <3ThomasBorregaardS�rensen!!
#pragma once


enum enum_as
{

   e_as,

}; // enum enum_base


#define __as(p) { e_as, p }

//
//struct function_common
//{
//
//
//#ifdef DEBUG
//
//   class ::wait m_waitTimeout = 30_min;
//
//#else
//
//   class ::wait m_waitTimeout = 5_s;
//
//#endif
//
//   void timeout(const class ::wait & wait)  { m_waitTimeout = wait;}
//   class ::wait timeout() const {return m_waitTimeout;}
//
//};


template < typename FUNCTION >
struct function //:
   //public function_common
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
   public ___pointer < ::element >
//,
  // public function_common
{
public:


   template < typename ELEMENT >
   class predicate :
      virtual public element
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


   //function(enum_as, ::element * pelement)
   //{

   //   m_p = pelement;

   //   m_pelement = m_p;

   //}


   function(::lparam & lparam)
   {

      m_p = (::element *) lparam.m_lparam;

      m_pelement = m_p;

   }


   template < typename TYPE >
   function(TYPE * p)
   {

      m_p = p;

      m_pelement = m_p;

      p->increment_reference_count();

   }


   template < typename TYPE >
   function(const __pointer(TYPE) & p)
   {

      m_p = p;

      m_pelement = m_p;

      p->increment_reference_count();

   }



   template < typename PREDICATE >
   function(PREDICATE predicateParam)
   {

      m_p = new class predicate <PREDICATE >(predicateParam);

      m_pelement = m_p;

   }


   function(const function & function) :
      ___pointer < ::element > (function)
   {

   }


   function(function && function) :
      ___pointer < ::element >(::move(function))
   {

   }


   ~function()
   {

   }


   void operator()() const
   {

      ASSERT(m_p);

      m_p->call_run();

   }


   function & operator = (const function & function)
   {

      ___pointer < ::element >::operator=(function.m_p);

      return *this;

   }


   function & operator = (function && function)
   {

      ___pointer < ::element >::operator=(::move(function));

      return *this;

   }

   operator bool() const { return ::is_set(m_p); }

   bool operator !() const { return ::is_null(m_p); }

   operator ::element *() const { return m_p; }

   const ::element * operator -> () const { return m_p; }

   ::element * operator -> () { return m_p; }
   

};


template < typename RETURN_TYPE >
class function < RETURN_TYPE() > // :
   //public function_common
{
public:


   class predicate_base :
      virtual public ::element
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

   __pointer(predicate_base)     m_ppredicate;


   function(nullptr_t = nullptr)
   {

   }

   template < typename PREDICATE >
   function(PREDICATE predicateParam)
   {

      m_ppredicate = __new(class predicate <PREDICATE >(predicateParam));

   }


   function(const function & function) :
      m_ppredicate(function.m_ppredicate)
   {

   }


   function(function && function) :
      m_ppredicate(::move(function.m_ppredicate))
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

      m_ppredicate = __new(class predicate <PREDICATE >(predicateParam));

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

   operator bool() const { return ::is_set(m_ppredicate); }

   bool operator !() const { return ::is_null(m_ppredicate); }


};



template < typename RETURN_TYPE, typename... TYPES >
class function < RETURN_TYPE(TYPES...) > //:
   //public function_common
{
public:


   class base :
      virtual public ::element
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


      RETURN_TYPE operator()(TYPES... args)
      {

         return m_predicate(args...);

      }

   };

   
   __pointer(base)     m_pbase;


   function(nullptr_t = nullptr)
   {

   }


   function(enum_as, base * pbase)
   {

      m_pbase = pbase;

   }


   template < typename FUNCTION >
   function(FUNCTION functionParam)
   {

      m_pbase = __new(class implementation < FUNCTION >(functionParam));

   }


   function(const function & function) :
      m_pbase(function.m_pbase)
   {

   }


   function(function && function) :
      m_pbase(::move(function.m_pbase))
   {

   }


   ~function()
   {

   }


   RETURN_TYPE operator()(TYPES... args) const
   {

      ASSERT(m_pbase);

      return m_pbase->operator()(args...);

   }


   void clear() { m_pbase.release(); }


   template < typename FUNCTION >
   function & operator = (FUNCTION functionParam)
   {

      m_pbase = __new(class implementation <FUNCTION >(functionParam));

      return *this;

   }


   function & operator = (nullptr_t)
   {

      clear();

      return *this;

   }

   operator bool() const { return ::is_set(m_pbase); }

   bool operator !() const { return ::is_null(m_pbase); }

   function & operator = (const function & function) { m_pbase = function.m_pbase; return *this; }
   bool operator == (const function & function) const { return m_pbase == function.m_pbase; }
   bool operator != (const function & function) const { return !operator==(function); }


};



