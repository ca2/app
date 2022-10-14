// Created by camilo on 2022-05-08 20:20 <3ThomasBorregaardSørensen!!
#include "framework.h"


particle::~particle()
{


}



#ifdef _DEBUG


i64 particle::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

   auto c = ++m_countReference;

#if OBJECT_REFERENCE_COUNT_DEBUG

   add_ref_history(pReferer, pszObjRefDbg);

#endif

   return c;

}


i64 particle::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

   auto c = --m_countReference;

#if OBJECT_REFERENCE_COUNT_DEBUG

   if (c > 0)
   {

      dec_ref_history(pReferer, pszObjRefDbg);

   }

#endif

   return c;

}


i64 particle::release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

   i64 i = decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   if (i == 0)
   {

      delete_this();

   }

   return i;

}


#endif



enum_type particle::get_payload_type() const
{

   return e_type_element;

}


void particle::destroy()
{


}


void particle::delete_this()
{

   if (!m_eflagElement & e_flag_statically_allocated)
   {

      delete this;

   }

}




void particle::initialize(::object * pobject)
{

   ///initialize_matter(pobject);

   on_initialize_object();

}


void particle::on_initialize_object()
{


}

//void particle::initialize_matter(::matter * pmatter)
//{
//
//   //return ::success;
//
//}


//void particle::run()
//{
//
//
//}



void particle::init_task()
{


}


void particle::call_run()
{

   //::e_status estatus;

   //try
   //{

   /*estatus =*/ run();

   //}
   //catch (...)
   //{

   //   estatus = ::error_exception;

   //}

   //return estatus;

}


void particle::run()
{

   while (true)
   {

      /*auto estatus =*/ step();

      //if(!estatus)
      //{

      //   break;

      //}

   }

   //return ::success;

}


bool particle::step()
{

   //return ::error_failed;
   return false;

}


void particle::on_sequence()
{


}


strsize particle::sz_len() const
{

   return strlen(__type_name(this)) + 1;

}


void particle::to_sz(char * sz, strsize len) const
{

   strncpy(sz, __type_name(this), len);

}



