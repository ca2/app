// Created by camilo on 2022-03-20 11:35 <3ThomasBorregaardSørensen!!
#pragma once


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


template < typename RETURN_TYPE, typename... TYPES >
class function < RETURN_TYPE(TYPES...) >
{
public:


   class predicate_base :
      virtual public ::element
   {
   public:

      virtual RETURN_TYPE operator()(TYPES... args) = 0;

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

      RETURN_TYPE operator()(TYPES... args)
      {

         return m_predicate(args...);

      }

   };


   __pointer(predicate_base)     m_ppredicate;

   function()
   {

   }

   template < typename PREDICATE >
   function(PREDICATE predicateParam)
   {

      m_ppredicate = __new(class predicate <PREDICATE >(predicateParam));

   }

   ~function()
   {

   }


   RETURN_TYPE operator()(TYPES... args) const
   {

      ASSERT(m_ppredicate);

      return m_ppredicate->operator()(args...);

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
