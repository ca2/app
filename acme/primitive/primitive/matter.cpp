#include "framework.h"
#include "acme/id.h"
#include "acme/primitive/primitive/layered.h"


#if OBJ_REF_DBG


void defer_delete(obj_ref_dbg* p);


#endif


matter::~matter()
{

#if OBJ_REF_DBG

   ::defer_delete(m_pobjrefdbg);

#endif

   if (m_eobject & e_object_any_hook)
   {

      ::release(m_pmutex);

      if (m_eobject & e_object_any_update)
      {

         remove_from_any_source();

      }

   }

}


void matter::assert_valid() const
{

}


void matter::dump(dump_context & dumpcontext) const
{

}


::estatus matter::initialize(::layered * pobjectContext)
{

   return ::success;

}


void matter::finalize()
{

}


const char* matter::debug_note() const
{

   return nullptr;

}


#ifdef _DEBUG

i64 matter::add_ref(OBJ_REF_DBG_PARAMS_DEF)
{

   auto c = atomic_increment(&m_countReference);

#if OBJ_REF_DBG

   add_ref_history(pReferer, pszObjRefDbg);

#endif

   return c;

}


i64 matter::dec_ref(OBJ_REF_DBG_PARAMS_DEF)
{

   auto c = atomic_decrement(&m_countReference);

#if OBJ_REF_DBG

   if (c > 0)
   {

      dec_ref_history(pReferer, pszObjRefDbg);

   }

#endif

   return c;

}


i64 matter::release(OBJ_REF_DBG_PARAMS_DEF)
{

   i64 i = dec_ref(OBJ_REF_DBG_ARGS);

   if (i == 0)
   {

      delete_this();

   }

   return i;

}


#endif


::matter * matter::clone() const
{

   __throw(interface_only_exception());

   return nullptr;

}


void matter::set_mutex(sync* psync)
{

   ::release(m_pmutex);

   m_pmutex = psync;

}


void matter::remove_from_any_source()
{

   ::source::__remove(this);

}


void matter::defer_create_mutex()
{

   if (!m_pmutex)
   {

      m_pmutex = new ::mutex;

   }

   set(e_object_any_hook);

}


::estatus matter::on_task()
{

   return  run();
   
}


void matter::thread_remove(::thread* pthread)
{


}


void matter::thread_on_term(::thread* pthread)
{


}


void matter::set_finish()
{

}


::estatus matter::call()
{

   ::estatus estatus;

   try
   {

      estatus = run();

   }
   catch (...)
   {

      estatus = ::error_exception;

   }

   return estatus;

}


void matter::call(const ::var & var)
{

}


void matter::receive_response(const ::var& var)
{

}


::estatus matter::run()
{

   return ::success;

}


::var matter::realize()
{

   return ::success;

}


::estatus matter::add_composite(::matter* pobject OBJ_REF_DBG_ADD_PARAMS_DEF)
{

   return ::success_none;

}


//::estatus matter::fork(
//   ::e_priority epriority,
//   u32 nStackSize,
//   u32 dwCreateFlags,
//   ITHREAD* pithread,
//   HTHREAD* phthread)
//{
//
//   auto estatus = __fork(
//      this,
//      epriority,
//      nStackSize,
//      dwCreateFlags,
//      pithread,
//      phthread
//   );
//
//   return estatus;
//
//}


::estatus matter::add_reference(::matter* pobject OBJ_REF_DBG_ADD_PARAMS_DEF)
{

   return ::success_none;

}


::estatus matter::release_composite(::matter* pobject OBJ_REF_DBG_ADD_PARAMS_DEF)
{

   return ::success_none;

}


::estatus matter::release_reference(::matter* pobject OBJ_REF_DBG_ADD_PARAMS_DEF)
{

   return ::success_none;

}


::matter* matter::get_taskpool_container()
{

   return nullptr;

}


::layered* matter::taskpool()
{

   auto pcontainer = get_taskpool_container();

   if (pcontainer)
   {

      auto ptaskpool = pcontainer->taskpool();

      if (ptaskpool)
      {

         return ptaskpool;

      }

   }

   return nullptr;

}


::task* matter::defer_fork(const ::id& id, const matter* pmatter)
{

   auto ptasktool = __task_pool(taskpool());

   if (ptasktool)
   {

      return ptasktool->start(id, pmatter);

   }

   return nullptr;

}


::estatus matter::set_generic_object_name(const char* pszName)
{

   return ::success_none;

}


void matter::delete_this()
{

   try
   {

      delete this;

   }
   catch (...)
   {

   }

}


void matter::__tracea(::matter * pobject, e_trace_level elevel, const char * pszFunction, const char * pszFile, int iLine, const char * psz)
{


}


void matter::__tracef(::matter * pobject, e_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * pszFormat, ...)
{

   va_list valist;

   va_start(valist, pszFormat);

   __tracev(pobject, elevel, pszFunction, pszFile, iLine, pszFormat, valist);

   va_end(valist);

}


void matter::__tracev(::matter * pobject, e_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * pszFormat, va_list valist)
{

   string str;

   str.FormatV(pszFormat, valist);

   __tracea(pobject, elevel, pszFunction, pszFile, iLine, str);

}


e_trace_category matter::trace_category()
{

   return trace_category_general;

}


e_trace_category matter::trace_category(::matter * pobject)
{

   return pobject->trace_category();

}


const char * matter::topic_text() const
{

   return typeid(*this).name();

}


void matter::apply(::action * paction)
{

   if (!paction->is_up_to_date())
   {

      on_apply(paction);

   }

}


void matter::on_apply(::action * paction)
{


}


strsize matter::sz_len() const
{

   return strlen(typeid(*this).name());

}


void matter::to_sz(char * sz, strsize len) const
{

   strncpy(sz, typeid(*this).name(), len);

}


::estatus matter::__thread_main()
{

   ::estatus estatus = call();

   return estatus;

}


::index matter::thread_add(::thread* pthread)
{

   return -1;

}


//::estatus matter::__thread_procedure()
//{
//
//   ::u32 u = -1;
//
//   ::estatus estatus = error_failed;
//
//   ::estatus estatusOs = error_failed;
//
//   ::estatus estatusStart = error_failed;
//
//   {
//
//      estatusOs = osthread_init();
//
//      if (::succeeded(estatusOs))
//      {
//
//         estatusStart = __thread_init();
//
//      }
//
//   }
//
//   if (::succeeded(estatusStart))
//   {
//
//      estatus = __thread_main();
//
//   }
//
//   if (::succeeded(estatusOs))
//   {
//
//      __thread_term();
//
//      osthread_term();
//
//   }
//
//#if OBJ_REF_DBG
//
//   //release(OBJ_REF_DBG_P_NOTE(this, nullptr));
//
//   try
//   {
//
//      if (m_countReference > 1)
//      {
//
//         __check_pending_releases(this);
//
//      }
//
//   }
//   catch (...)
//   {
//
//   }
//
//#endif
//
//   return estatus;
//
//}


::estatus matter::osthread_init()
{

   return ::success;

}


::estatus matter::__thread_init()
{

   return ::success;

}


::estatus matter::__thread_term()
{

   return ::success;

}


::estatus matter::osthread_term()
{

   return ::success;

}


void matter::exchange(stream& s)
{

}


stream & matter::write(stream& s) const
{

   return s;

}


stream& matter::read(stream& s)
{

   return s;

}


void matter::to_string(const class string_exchange & str) const
{

   str = type_c_str();

}


CLASS_DECL_ACME ::estatus __call(::matter* pobjectTask)
{

   return pobjectTask->call();

}



