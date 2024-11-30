//
// Created by camilo on 23/12/2022 16:26 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "_impl_generic_map.h"
#include "_impl_numeric_array.h"


template<typename ITERATOR_TYPE>
inline auto & range < ITERATOR_TYPE >::first() { return ::get(this->begin()); }
template<typename ITERATOR_TYPE>
inline auto & range < ITERATOR_TYPE >::first() const { return (CONST_ITEM &) ::get(this->begin()); }






#include "acme/handler/sequence_continuation.h"


inline sequence_continuation particle::user_send(const ::procedure & procedure)
{
   return { this, e_dispatch_user_send, procedure };
}
inline sequence_continuation particle::user_send()
{
   return { this, e_dispatch_user_send };
}
inline sequence_continuation particle::user_sync()
{
   return { this, e_dispatch_user_send, this };
}




inline sequence_continuation particle::user_post(const ::procedure & procedure)
{
   return { this, e_dispatch_user_post, procedure };
}
inline sequence_continuation particle::user_post()
{
   return { this, e_dispatch_user_post };
}
inline sequence_continuation particle::user_async()
{
   return { this, e_dispatch_user_post, this };
}


inline sequence_continuation particle::main_send(const ::procedure & procedure)
{
   return { this, e_dispatch_main_send, procedure };
}
inline sequence_continuation particle::main_send()
{
   return { this, e_dispatch_main_send };
}
inline sequence_continuation particle::main_sync()
{
   return { this, e_dispatch_main_send, this };
}

inline sequence_continuation particle::main_post(const ::procedure & procedure)
{
   return { this, e_dispatch_main_post, procedure };
}
inline sequence_continuation particle::main_post()
{
   return { this, e_dispatch_main_post };
}
inline sequence_continuation particle::main_async()
{
   return { this, e_dispatch_main_post, this };
}


inline sequence_continuation particle::send(const ::procedure & procedure)
{
   return { this, e_dispatch_send, procedure };
}
inline sequence_continuation particle::send()
{
   return { this, e_dispatch_send };
}


inline sequence_continuation particle::sync(const class ::time & timeTimeout)
{
   
   ::procedure procedure;

   procedure.m_pbase = this;
   
   if (!timeTimeout.is_null())
   {

      procedure.set_timeout(timeTimeout);

   }

   return { this, e_dispatch_send, procedure, should_create_sequence_on_synchronicity()};

}


inline sequence_continuation particle::post(const ::procedure & procedure)
{
   return { this, e_dispatch_post, procedure };
}
inline sequence_continuation particle::post()
{

   return { this, e_dispatch_post };
}
inline sequence_continuation particle::async()
{

   return { this, e_dispatch_post, this };
}

#include "acme/exception/cancel.h"




   template < typename CONTEXT_TYPE >
   void procedure_array_with_context<CONTEXT_TYPE>::run()
   {

      try
      {

         ::procedure_array::run();

      }
      catch (const ::cancel_exception<CONTEXT_TYPE> & cancelexception)
      {

         informationf("procedure_array : cancel_exception(%s) : %s", cancelexception.m_strContext.c_str(), cancelexception.m_strMessage.c_str());

      }


   }



