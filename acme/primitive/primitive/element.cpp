#include "framework.h"
//#if !BROAD_PRECOMPILED_HEADER
//#include "acme/user/_user.h"
//#endif


#if OBJ_REF_DBG
void defer_delete(obj_ref_dbg* p);
#endif

element::~element()
{

#if OBJ_REF_DBG

   ::defer_delete(m_pobjrefdbg);

#endif

   ::release(m_pobjectContext);

   ::release(m_pmutex);

}


void element::assert_valid() const
{


}


void element::dump(dump_context & dumpcontext) const
{


}


::estatus element::initialize(::layered * pobjectContext)
{

   set_context_object(pobjectContext);

   return ::success;

}



void element::finalize()
{


}

const char* element::debug_note() const
{

   return nullptr;

}

//bool element::is_ok() const
//{
//
//   return has_id(OK);
//
//}


#ifdef _DEBUG

i64 element::add_ref(OBJ_REF_DBG_PARAMS_DEF)
{

   auto c = atomic_increment(&m_countReference);

#if OBJ_REF_DBG

   add_ref_history(p, pszObjRefDbg);

#endif

   return c;

}


i64 element::dec_ref(OBJ_REF_DBG_PARAMS_DEF)
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


i64 element::release(OBJ_REF_DBG_PARAMS_DEF)
{

   i64 i = dec_ref(OBJ_REF_DBG_ARGS);

   if (i == 0)
   {

      delete_this();

   }

   return i;

}


#endif


::element * element::clone() const
{

   __throw(interface_only_exception());

   return nullptr;

}


void element::set_mutex(sync* psync)
{

   ::release(m_pmutex);

   m_pmutex = psync;

}


void element::defer_create_mutex()
{

   if (!m_pmutex)
   {

      m_pmutex = new ::mutex;

   }

}


void element::set_context_object(::layered * pobjectContext)
{

   auto pold = m_pobjectContext;

   if(::is_set(pobjectContext))
   {

      pobjectContext->add_ref();

   }

   m_pobjectContext = pobjectContext;

   ::release(pold);

}




void element::set_finish()
{

}


::estatus element::call()
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


void element::call(const ::var & var)
{

}


void element::receive_response(const ::var& var)
{

}


::estatus element::run()
{

   return ::success;

}


::var element::realize()
{

   return ::success;

}


#ifdef WINDOWS


DWORD WINAPI element::s_os_thread_proc(void* p)
{

   ::element* pobject = (::element *) p;

   return pobject->__thread_proc();

}


#else


void * element::s_os_thread_proc(void* p)
{

   ::element* pobject = (::element*) p;

   return (void*)(iptr)pobject->__thread_proc();

}


#endif



::estatus element::add_composite(::element* pobject)
{

   return ::success_none;

}


::estatus element::os_fork(::e_priority epriority, UINT nStackSize, u32 uiCreateFlags, ITHREAD * pithread, HTHREAD * phthread)
{

   add_ref(OBJ_REF_DBG_P_NOTE(this, "os_fork"));

   ::element* p = this;

   HTHREAD hthread = NULL_HTHREAD;

   ITHREAD ithread = NULL_ITHREAD;

#ifdef WINDOWS

   DWORD dwThread = 0;

   hthread = ::CreateThread(nullptr, nStackSize, &::element::s_os_thread_proc, (LPVOID)p, uiCreateFlags, &dwThread);

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
      &element::s_os_thread_proc,
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






::estatus element::add_reference(::element* pobject)
{

   return ::success_none;

}


::estatus element::release_composite(::element* pobject)
{

   return ::success_none;

}


::estatus element::release_reference(::element* pobject)
{

   return ::success_none;

}


::estatus element::set_generic_object_name(const char* pszName)
{

   return ::success_none;

}


void element::delete_this()
{

   try
   {

      delete this;

   }
   catch (...)
   {

   }

}








void element::__tracea(::element * pobject, e_trace_level elevel, const char * pszFunction, const char * pszFile, int iLine, const char * psz)
{

   // acme commented
   //::__tracea(pobject, elevel, pszFunction, pszFile, iLine, psz);

}


void element::__tracef(::element * pobject, e_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * pszFormat, ...)
{

   va_list valist;

   va_start(valist, pszFormat);

   __tracev(pobject, elevel, pszFunction, pszFile, iLine, pszFormat, valist);

   va_end(valist);

}


void element::__tracev(::element * pobject, e_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * pszFormat, va_list valist)
{

   string str;

   str.FormatV(pszFormat, valist);

   __tracea(pobject, elevel, pszFunction, pszFile, iLine, str);

}

e_trace_category element::trace_category()
{

   return trace_category_general;

}


e_trace_category element::trace_category(::element * pobject)
{

   return pobject->trace_category();

}


const char * element::topic_text() const
{

   return typeid(*this).name();

}


void element::call_update(const ::__id& id)
{

   auto pupdate = new_update();

   pupdate->m_id = id;

   call_update(pupdate);

}


void element::call_update(const ::__id& id, const ::action_context& context)
{

   auto pupdate = new_update();

   pupdate->m_id = id;

   pupdate->m_actioncontext = context;

   call_update(pupdate);

}


void element::call_update(::update* pupdate)
{

   if (!pupdate->handled_by(this))
   {

      pupdate->set_handled_by(this);

      this->update(pupdate);

   }

}


void element::update(::update * pupdate)
{


}


bool element::already_handled(::update * pupdate) const
{

  if (::is_set(pupdate))
  {

      if (pupdate->handled_by(this))
      {

         return true;

      }

  }

  return false;

}


strsize element::sz_len() const
{

   return strlen(typeid(*this).name());

}


void element::to_sz(char * sz, strsize len) const
{

   strncpy(sz, typeid(*this).name(), len);

}


::estatus element::__thread_main()
{

   ::estatus estatus = call();

   return estatus;

}


::estatus element::__thread_proc()
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



::estatus element::osthread_init()
{

   return ::success;

}


::estatus element::__thread_init()
{

   return ::success;

}


::estatus element::__thread_term()
{

   return ::success;

}


::estatus element::osthread_term()
{

   return ::success;

}


void element::exchange(stream& s)
{

}


stream & element::write(stream& s) const
{

   return s;

}


stream& element::read(stream& s)
{

   return s;

}


void element::to_string(const class string_exchange & str) const
{

   str = type_c_str();

}




CLASS_DECL_ACME ::estatus __call(::element* pobjectTask)
{

   return pobjectTask->call();

}



