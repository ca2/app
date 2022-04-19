// Created by camilo on 2022-03-20 11:35 <3ThomasBorregaardSørensen!!
#pragma once


enum enum_as
{

   e_as,

}; // enum enum_base


#define __as(p) { e_as, p }


template < typename FUNCTION >
struct function {

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
class function < void() >
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

   
   __pointer(::element)    m_pelement;


   function(nullptr_t = nullptr)
   {

   }


   function(enum_as, ::element * pelement)
   {

      m_pelement = pelement;

   }


   function(enum_as, ::lparam & lparam)
   {

      m_pelement = ::move(lparam.detach_element());

   }


   template < typename PREDICATE >
   function(PREDICATE predicateParam)
   {

      m_pelement = __new(class predicate <PREDICATE >(predicateParam));

   }


   function(const function & function) :
      m_pelement(function.m_pelement)
   {

   }


   function(function && function) :
      m_pelement(::move(function.m_pelement))
   {

   }


   ~function()
   {

   }


   void operator()() const
   {

      ASSERT(m_pelement);

      m_pelement->call_run();

   }


   void clear() { m_pelement.release(); }


   function & operator = (const function & function)
   {

      if (&function != this)
      {

         m_pelement = function.m_pelement;

      }

      return *this;

   }


   function & operator = (function && function)
   {

      if (&function != this)
      {

         m_pelement = ::move(function.m_pelement);

      }

      return *this;

   }

   function & operator = (nullptr_t)
   {

      clear();

      return *this;

   }

   operator bool() const { return ::is_set(m_pelement); }

   bool operator !() const { return ::is_null(m_pelement); }

   operator ::element *() const { return m_pelement.m_p; }

   const ::element * operator -> () const { return m_pelement.m_p; }

   ::element * operator -> () { return m_pelement.m_p; }
   

};


template < typename RETURN_TYPE >
class function < RETURN_TYPE() >
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


   function & operator = (nullptr_t)
   {

      clear();

      return *this;

   }

   operator bool() const { return ::is_set(m_ppredicate); }

   bool operator !() const { return ::is_null(m_ppredicate); }


};



template < typename RETURN_TYPE, typename... TYPES >
class function < RETURN_TYPE(TYPES...) >
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



