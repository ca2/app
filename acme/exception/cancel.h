#pragma once


#include "acme/exception/exception.h"


template < typename CONTEXT_TYPE >
class cancel_exception :
   public ::exception
{
public:

   using CONTEXT = CONTEXT_TYPE;

   ::string m_strContext = typeid(CONTEXT).name();

   cancel_exception(const ::scoped_string & scopedstrMessage = nullptr);
   virtual ~cancel_exception();


   //virtual bool get_error_message(string & str,P::u32 pnHelpContext = nullptr);


};



template < typename CONTEXT_TYPE >
cancel_exception<CONTEXT_TYPE>::cancel_exception(const ::scoped_string & scopedstrMessage) :
   exception(error_cancelled, scopedstrMessage)
{

}
template < typename CONTEXT_TYPE >
cancel_exception<CONTEXT_TYPE>::~cancel_exception()
{

}

//bool cancel_exception::get_error_message(string & str,P::u32 pnHelpContext)
//{
//
//   str = what();
//
//   return true;
//
//}


template < typename CONTEXT_TYPE >
[[noreturn]]inline void throw_cancel_exception(const ::scoped_string & scopedstrMessage = {})
{

   throw cancel_exception<CONTEXT_TYPE>(scopedstrMessage);

}


[[noreturn]] inline void cancel_continuation(const ::scoped_string & scopedstrMessage = nullptr)
{

   throw_cancel_exception<continuation_t>(scopedstrMessage);

}

