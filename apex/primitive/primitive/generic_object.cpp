#include "framework.h"

#if OBJ_REF_DBG
void defer_delete(obj_ref_dbg* p);
#endif

generic::~generic()
{

#if OBJ_REF_DBG

   ::defer_delete(m_pobjrefdbg);

#endif

   if(::is_set(m_pobjectContext))
   {

      ::release(m_pobjectContext);

   }


}


::estatus generic::initialize(::layered * pobjectContext)
{

   set_context_object(pobjectContext);

   return ::success;

}



void generic::finalize()
{


}

const char* generic::debug_note() const
{

   return nullptr;

}

//bool generic::is_ok() const
//{
//
//   return has_id(OK);
//
//}


#ifdef _DEBUG

i64 generic::add_ref(OBJ_REF_DBG_PARAMS_DEF)
{

   auto c = atomic_increment(&m_countReference);

#if OBJ_REF_DBG

   add_ref_history(p, pszObjRefDbg);

#endif

   return c;

}


i64 generic::dec_ref(OBJ_REF_DBG_PARAMS_DEF)
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


i64 generic::release(OBJ_REF_DBG_PARAMS_DEF)
{

   i64 i = dec_ref(OBJ_REF_DBG_ARGS);

   if (i == 0)
   {

      delete_this();

   }

   return i;

}


#endif


::generic * generic::clone() const
{

   __throw(interface_only_exception());

   return nullptr;

}


void generic::set_context_object(::layered * pobjectContext)
{

   auto pold = m_pobjectContext;

   if(::is_set(pobjectContext))
   {

      pobjectContext->add_ref();

   }

   m_pobjectContext = pobjectContext;

   ::release(pold);

}




void generic::set_finish()
{

}


::estatus generic::call()
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


void generic::call(const ::var & var)
{

}


void generic::receive_response(const ::var& var)
{

}


::estatus generic::run()
{

   return ::success;

}


#ifdef WINDOWS


DWORD WINAPI generic::s_os_thread_proc(void* p)
{

   ::generic* pobject = (::generic *) p;

   return pobject->__thread_proc();

}


#else


void * generic::s_os_thread_proc(void* p)
{

   ::generic* pobject = (::generic*) p;

   return (void*)(iptr)pobject->__thread_proc();

}


#endif



::estatus generic::add_composite(::generic* pobject)
{

   return ::success_none;

}


::estatus generic::os_fork(::e_priority epriority, UINT nStackSize, u32 uiCreateFlags, ITHREAD * pithread, HTHREAD * phthread)
{

   add_ref(OBJ_REF_DBG_P_NOTE(this, "os_fork"));

   ::generic* p = this;

   HTHREAD hthread = NULL_HTHREAD;

   ITHREAD ithread = NULL_ITHREAD;

#ifdef WINDOWS

   DWORD dwThread = 0;

   hthread = ::CreateThread(psa, nStackSize, &::generic::s_os_thread_proc, (LPVOID)p, uiCreateFlags, &dwThread);

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
      &generic::s_os_thread_proc,
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






::estatus generic::add_reference(::generic* pobject)
{

   return ::success_none;

}


::estatus generic::release_composite(::generic* pobject)
{

   return ::success_none;

}


::estatus generic::release_reference(::generic* pobject)
{

   return ::success_none;

}


::estatus generic::set_generic_object_name(const char* pszName)
{

   return ::success_none;

}


void generic::delete_this()
{

   try
   {

      delete this;

   }
   catch (...)
   {

   }

}








void generic::__tracea(::generic * pobject, e_trace_level elevel, const char * pszFunction, const char * pszFile, int iLine, const char * psz)
{

   ::__tracea(pobject, elevel, pszFunction, pszFile, iLine, psz);

}


void generic::__tracef(::generic * pobject, e_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * pszFormat, ...)
{

   va_list valist;

   va_start(valist, pszFormat);

   __tracev(pobject, elevel, pszFunction, pszFile, iLine, pszFormat, valist);

   va_end(valist);

}


void generic::__tracev(::generic * pobject, e_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * pszFormat, va_list valist)
{

   string str;

   str.FormatV(pszFormat, valist);

   __tracea(pobject, elevel, pszFunction, pszFile, iLine, str);

}

e_trace_category generic::trace_category()
{

   return trace_category_general;

}


e_trace_category generic::trace_category(::generic * pobject)
{

   return pobject->trace_category();

}


const char * generic::topic_text() const
{

   return typeid(*this).name();

}


void generic::call_update(const ::id & id, const ::action_context & context)
{

   auto pupdate = new_update();

   pupdate->m_id = id;

   pupdate->m_actioncontext = context;

   call_update(pupdate);

}





void generic::call_update(const ::id & id)
{

   auto pupdate = new_update();

   pupdate->m_id = id;

   call_update(pupdate);

}


void generic::update(::update * pupdate)
{


}


bool generic::already_handled(::update * pupdate) const
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


void generic::call_update(::update * pupdate)
{

   if (!pupdate->handled_by(this))
   {

      pupdate->set_handled_by(this);

      this->update(pupdate);

   }

}


strsize generic::sz_len() const
{

   return strlen(typeid(*this).name());

}


void generic::to_sz(char * sz, strsize len) const
{

   strncpy(sz, typeid(*this).name(), len);

}


::estatus generic::__thread_main()
{

   ::estatus estatus = call();

   return estatus;

}


::estatus generic::__thread_proc()
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



::estatus generic::osthread_init()
{

   return ::success;

}


::estatus generic::__thread_init()
{

   return ::success;

}


::estatus generic::__thread_term()
{

   return ::success;

}


::estatus generic::osthread_term()
{

   return ::success;

}


void generic::exchange(stream& s)
{

}


stream & generic::write(stream& s) const
{

   return s;

}


stream& generic::read(stream& s)
{

   return s;

}


void generic::to_string(string& str) const
{

   str = type_c_str();

}



