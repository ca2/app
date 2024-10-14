// Created by camilo on 2024-02-07 22:52 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "acme/exception/exit.h"
#include "acme/exception/interface_only.h"
#include "acme/memory/memory_allocate.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/referencing_debugging.h"
#include "acme/platform/system.h"


CLASS_DECL_ACME void do_tasks();


#if REFERENCING_DEBUGGING


namespace allocator
{


   CLASS_DECL_ACME void __on_after_construct_subparticle(::subparticle* psubparticle);


} // namespace allocator


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


#if REFERENCING_DEBUGGING


void subparticle::on_after_construct(::reference_referer* preferer)
{


   ::allocator::__on_after_construct_subparticle(this);


}


#endif


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


::acme::system* subparticle::system() const
{

   return ::system();

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


//#if REFERENCING_DEBUGGING
//
//
//void subparticle::set_creation_referer(::reference_referer* preferer)
//{
//
//
//}
//
//
//#endif


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


#ifdef WINDOWS


hsynchronization subparticle::get_synchronization_handle()
{

   return nullptr;

}


#endif


::e_status subparticle::lock()
{

   return wait();

}


::e_status subparticle::lock(const class time& timeWait)
{

   return this->wait(timeWait);

}


void subparticle::_lock()
{

   _wait();

}


bool subparticle::_lock(const class time& timeWait)
{

   return this->_wait(timeWait);

}


void subparticle::_wait()
{

   _wait(::time::infinity());

}


::e_status subparticle::wait()
{

   auto ptask = ::get_task();

   if (::is_null(ptask))
   {

      ptask = system();

   }

   if (::is_null(ptask))
   {

      //try { throw "errorABC1"; } catch(...){}

      printf_line("particle::wait ptask is NULL, going to do NOT transacted wait");

      _wait();

      return ::success;

   }

   //printf_line("particle::wait ptask is SET, going to DO transacted wait");

   while (true)
   {

      do_tasks();

      //try { throw "errorABC2"; } catch(...){}

      auto bOk = _wait(100_ms);

      if (bOk)
      {

         return ::success;

      }

      if (!ptask->task_get_run())
      {

         return error_failed;

      }

   }

}


::e_status subparticle::wait(const class time& timeWait)
{

   if (timeWait < 200_ms)
   {

      auto bOk = this->_wait(timeWait);

      if (!bOk)
      {

         return error_wait_timeout;

      }

      return ::success;

   }

   if (timeWait.is_infinite())
   {

      return this->wait();

   }

   auto ptask = ::get_task();

   if (::is_null(ptask))
   {

      ptask = system();

   }

   if (::is_null(ptask))
   {

      auto bOk = this->_wait(timeWait);

      if (!bOk)
      {

         return error_wait_timeout;

      }

      return ::success;

   }

   auto waitStart = ::time::now();

   while (true)
   {

      ::do_tasks();

      auto waitElapsed = waitStart.elapsed();

      if (waitElapsed > timeWait)
      {

         return error_wait_timeout;

      }

      auto waitNow = ::minimum(waitElapsed, 100_ms);

      bool bOk = _wait(waitNow);

      if (bOk)
      {

         return ::success;

      }

      if (!ptask->task_get_run())
      {

         return error_failed;

      }

   }

}


bool subparticle::is_locked() const
{

   // CRITICAL SECTIONS does *NOT* support is locked and timed locks
   ASSERT(dynamic_cast <critical_section*> (const_cast <subparticle*> (this)) == nullptr);

   single_lock synchronouslock(const_cast <subparticle*> (this));

   bool bWasLocked = false;

   try
   {

      synchronouslock.wait(0_s);

   }
   catch (...)
   {

      bWasLocked = true;

   }

   if (!bWasLocked)
   {

      synchronouslock.unlock();

   }

   return bWasLocked;

}



void subparticle::unlock()
{

   ///return false;

}


void subparticle::unlock(::i32 /* lCount */, ::i32* /* pPrevCount=nullptr */)
{

   //return false;

}


void subparticle::init_wait()
{


}


void subparticle::exit_wait()
{


}






bool subparticle::_wait(const class time& timeWait)
{

   //#ifdef WINDOWS
   //
   //   if (!m_hsynchronization)
   //   {
   //
   //      return true;
   //
   //   }
   //
   //   //auto milliseconds = wait.operator u32();
   //   //unsigned int ui;
   //   //if (wait.m_d <= 0.)
   //   //{
   //   //   ui = 0;
   //
   //   //}
   //   //else if (wait.m_d >= 0xffffffffu)
   //   //{
   //
   //   //   ui = 0xffffffffu;
   //   //}
   //   //else
   //   //{
   //
   //   //   ui = (::u32) (wait.m_d * 1'000.0);
   //
   //   //}
   //
   //   ////return (::u32)m_d <= 0. ? 0 : (m_d >= 0xffffffffu ? 0xffffffffu : (::u32)(m_d * 1'000.0));
   //   //if (milliseconds < 1'000'000'000)
   //   //{
   //
   //   //   informationf("milliseconds < 1'000'000'000");
   //
   //   //}
   //
   //   auto windowsWaitResult = ::WaitForSingleObjectEx(m_hsync, wait, false);
   //
   //   auto estatus = windows_wait_result_to_status(windowsWaitResult);
   //
   //   if (estatus == error_wait_timeout)
   //   {
   //
   //      return false;
   //
   //   }
   //   else if (estatus == signaled_base)
   //   {
   //
   //#ifdef _DEBUG
   //
   //      auto pmutex = dynamic_cast < ::pointer< ::mutex >> (this);
   //
   //      if (::is_set(pmutex))
   //      {
   //
   //         pmutex->m_strThread = ::task_get_name();
   //         pmutex->m_itask = ::current_itask();
   //         informationf("");
   //
   //      }
   //
   //#endif
   //
   //      return true;
   //
   //   }
   //   else
   //   {
   //
   //      throw ::exception(estatus);
   //
   //      return false;
   //
   //   }
   //
   //#endif
   //
   //   throw ::exception(error_interface_only);
   //
   return true;

}


void subparticle::acquire_ownership()
{

   //m_bOwner = true;

   set_own_synchronization_flag();

}


[[maybe_unused]] void subparticle::release_ownership()
{

   //m_bOwner = false;
   clear_own_synchronization_flag();

}






