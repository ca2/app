#include "framework.h"
#include "acme/id.h"
//#if !BROAD_PRECOMPILED_HEADER
//#include "acme/user/_user.h"
//#endif


#if OBJ_REF_DBG
void defer_delete(obj_ref_dbg* p);
#endif

matter::~matter()
{

#if OBJ_REF_DBG

   ::defer_delete(m_pobjrefdbg);

#endif

   //::release(m_pobjectContext);

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

//bool matter::is_ok() const
//{
//
//   return has_id(OK);
//
//}


#ifdef _DEBUG

i64 matter::add_ref(OBJ_REF_DBG_PARAMS_DEF)
{

   auto c = atomic_increment(&m_countReference);

#if OBJ_REF_DBG

   add_ref_history(p, pszObjRefDbg);

#endif

   return c;

}


i64 matter::dec_ref(OBJ_REF_DBG_PARAMS_DEF)
{

   auto c = atomic_decrement(&m_countReference);

#if OBJ_REF_DBG

   if (c > 0)
   {

      dec_ref_history(p, pszObjRefDbg);

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


//::estatus matter::add_update(const ::id& id)
//{
//
//   ::update::_add(id, this);
//   
//   set(e_object_any_update);
//
//   return ::success;
//
//}
//
//
//::estatus matter::remove_update(const ::id& id)
//{
//
//   ::update::_remove(id, this);
//
//   return ::success;
//
//}


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


#ifdef WINDOWS


DWORD WINAPI matter::s_os_thread_proc(void* p)
{

   __pointer(::action) paction((::action *) p);

   try
   {

      paction->__thread_proc();

   }
   catch (...)
   {

   }

   return 0;

}


#else


void * matter::s_os_thread_proc(void* p)
{

   __pointer(::action) paction((::action*) p);

   try
   {

      paction->__thread_proc();

   }
   catch (...)
   {

   }

   return NULL;

}


#endif



::estatus matter::add_composite(::matter* pobject)
{

   return ::success_none;

}


//::estatus matter::fork_update(
//   ::i64 iUpdate,
//   ::e_priority epriority,
//   u32 nStackSize,
//   u32 dwCreateFlags,
//   ITHREAD* pithread,
//   HTHREAD* phthread)
//{
//
//   return start_change(
//      __new(change(iUpdate, this)),
//      epriority,
//      nStackSize,
//      dwCreateFlags,
//      pithread,
//      phthread);
//
//}


::estatus matter::fork_run(
   ::e_priority epriority,
   u32 nStackSize,
   u32 dwCreateFlags,
   ITHREAD* pithread,
   HTHREAD* phthread)
{

   return start_action(
      __new(action(nullptr, this)),
      epriority,
      nStackSize,
      dwCreateFlags,
      pithread,
      phthread);

}


::estatus matter::start_action(const __pointer(action) & paction, ::e_priority epriority, UINT nStackSize, u32 uiCreateFlags, ITHREAD * pithread, HTHREAD * phthread)
{

   add_ref(OBJ_REF_DBG_P_NOTE(this, "os_fork"));

   //auto p = new __os_fork{ iUpdate, this };

   paction->add_ref();

   HTHREAD hthread = NULL_HTHREAD;

   ITHREAD ithread = NULL_ITHREAD;

#ifdef WINDOWS

   DWORD dwThread = 0;

   hthread = ::CreateThread(nullptr, nStackSize, &::matter::s_os_thread_proc, (LPVOID)(action*)paction, uiCreateFlags, &dwThread);

   ithread = dwThread;

#else

   pthread_attr_t threadAttr;

   pthread_attr_init(&threadAttr);

   if (nStackSize > 0)
   {

      pthread_attr_setstacksize(&threadAttr, nStackSize); // Set the stack size of the thread

   }

   pthread_attr_setdetachstate(&threadAttr, PTHREAD_CREATE_DETACHED); // Set thread to detached state. No need for pthread_join

   pthread_create(
      &hthread,
      &threadAttr,
      &matter::s_os_thread_proc,
      (LPVOID)p);

#endif

   if (phthread)
   {

      *phthread = hthread;

   }

   if (pithread)
   {

      *pithread = ithread;

   }

   if(!hthread)
   {

      return ::error_failed;

   }

   return ::success;


}






::estatus matter::add_reference(::matter* pobject)
{

   return ::success_none;

}


::estatus matter::release_composite(::matter* pobject)
{

   return ::success_none;

}


::estatus matter::release_reference(::matter* pobject)
{

   return ::success_none;

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

   // acme commented
   //::__tracea(pobject, elevel, pszFunction, pszFile, iLine, psz);

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


//bool matter::already_handled(::task* pupdate) const
//{
//
//  if (::is_set(pupdate))
//  {
//
//      if (pupdate->handled_by(this))
//      {
//
//         return true;
//
//      }
//
//  }
//
//  return false;
//
//}
//

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


::estatus matter::__thread_proc()
{

   ::u32 u = -1;

   ::estatus estatus = error_failed;

   ::estatus estatusOs = error_failed;

   ::estatus estatusStart = error_failed;

   {

      estatusOs = osthread_init();

      if (::succeeded(estatusOs))
      {

         estatusStart = __thread_init();

      }

   }

   if (::succeeded(estatusStart))
   {

      estatus = __thread_main();

   }

   if (::succeeded(estatusOs))
   {

      __thread_term();

      osthread_term();

   }

#if OBJ_REF_DBG

   release(OBJ_REF_DBG_P_NOTE(this, nullptr));

   try
   {

      if (m_countReference > 1)
      {

         __check_pending_releases(this);

      }

   }
   catch (...)
   {

   }

#endif

   return estatus;

}



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



