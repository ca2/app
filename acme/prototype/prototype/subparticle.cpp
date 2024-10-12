// Created by camilo on 2024-02-07 22:52 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "acme/exception/exit.h"
#include "acme/exception/interface_only.h"
#include "acme/memory/memory_allocate.h"
#include "acme/platform/referencing_debugging.h"


#if REFERENCING_DEBUGGING


bool g_bDefaultEnableObjectReferenceCountDebug = false;


//CLASS_DECL_ACME void on_construct_particle(::particle * pparticle);


subparticle::subparticle() :
   m_countReference(1)
{

#if REFERENCING_DEBUGGING

   if (!g_bDefaultEnableObjectReferenceCountDebug)
   {

      disable_referencing_debugging();

   }

   ::allocator::on_construct_subparticle(this);

#endif

}


//particle::particle(disable_referencing_debugging_t) :
//   m_countReference(1)
//{
//
//#if REFERENCING_DEBUGGING
//
//   disable_referencing_debugging();
//
//#endif
//
//   ::allocator::on_construct_particle(this);
//
//}


#endif



subparticle::~subparticle()
{

#if REFERENCING_DEBUGGING
   {

      //auto p = ::transfer(m_preferenceitema);

      //m_preferenceitema.release();

      ::allocator::on_destruct_subparticle(this);

      //      ::acme::del(m_preferenceitema);

   }
#endif
}

void subparticle::initialize(::particle* pparticle)
{


}
void subparticle::finalize()
{

}


#ifdef _DEBUG


i64 subparticle::increment_reference_count()
{

#if REFERENCING_DEBUGGING

   critical_section_lock synchronouslock(&::acme::get()->m_preferencingdebugging->m_criticalsection);

#endif

   auto c = ++m_countReference;

#if REFERENCING_DEBUGGING

   add_reference_item();

#endif

   return c;

}


i64 subparticle::decrement_reference_count()
{

#if REFERENCING_DEBUGGING

   critical_section_lock synchronouslock(&::acme::get()->m_preferencingdebugging->m_criticalsection);

#endif

   auto c = --m_countReference;

#if REFERENCING_DEBUGGING

   if (c >= 0)
   {

      erase_reference_item();

   }

#endif

   return c;

}


::string subparticle::get_debug_title() const
{

   auto psubparticle = (::subparticle*)this;

   return ::type(*psubparticle).name();

}


i64 subparticle::replace_reference()
{

   auto c = m_countReference;

#if REFERENCING_DEBUGGING

   if (c > 0)
   {

      throw ::exception(::error_failed);

      //m_preferenceitema->replace_item();

   }

#endif

   return c;

}


i64 subparticle::release()
{

   i64 i = decrement_reference_count();

   if (i == 0)
   {

      delete_this();

   }

   return i;

}


#endif

void subparticle::init_task()
{


}


void subparticle::call()
{

   //m_eflagElement += e_flag_running;

   try
   {

      run();

   }
   catch (const ::exit_exception& exception)
   {

      throw exception;

   }
   catch (...)
   {

   }

   //m_eflagElement -= e_flag_running;

}



bool subparticle::defer_consume_main_arguments(int argc, char ** argv, int & iArgument)
{

   return false;
   
}


enum_type subparticle::get_payload_type() const
{

   return e_type_element;

}



bool subparticle::_is_set() const
{

   return true;

}


bool subparticle::_is_ok() const
{

   //return has_ok_flag();

   return true;

}


//void matter::finish(::property_object * pcontextobjectFinish)
void subparticle::destroy()
{

   //auto estatus = set_finish();

   //if (estatus == error_pending)
   //{

   //   //system()->add_pending_finish(this);

   //   return estatus;

   //}

   ////estatus = on_finish();

   ////if (estatus == error_pending)
   ////{

   ////   //system()->add_pending_finish(this);

   ////   return estatus;

   ////}

   //return estatus;

   //return ::success;


}


void subparticle::destroy_impl_data()
{


}


void subparticle::destroy_os_data()
{


}


void subparticle::delete_this()
{

   delete this;

}



void subparticle::write_to_stream(::binary_stream & stream)
{

   throw interface_only();

}


void subparticle::read_from_stream(::binary_stream & stream)
{

   throw interface_only();

}


//void subparticle::operator delete(void* p)
//{
//
//   ::memory_free(p);
//
//}


void subparticle::run()
{

   while (true)
   {

      if (!subparticle_step())
      {

         break;

      }

   }

}


//void subparticle::aggregate(::subparticle * psubparticle)
//{
//
//   run();
//
//   psubparticle->aggregate(this);
//
//}


class ::time subparticle::get_run_timeout()
{

#ifdef DEBUG
   return 5_min;
#else
   return 5_s;
#endif


}

bool subparticle::subparticle_step()
{

   return false;

}


class ::time subparticle::timeout() const
{

   return 1_min;

}


void subparticle::set_timeout(const class time & timeTimeout)
{

   throw interface_only();

}



