#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif


#if OBJ_REF_DBG
void defer_delete(obj_ref_dbg* p);
#endif

generic_object::~generic_object()
{

#if OBJ_REF_DBG

   ::defer_delete(m_pobjrefdbg);

#endif

   if(::is_set(m_pobjectContext))
   {

      ::release(m_pobjectContext);

   }


}


::estatus generic_object::initialize(::object* pobjectContext)
{

   set_context_object(pobjectContext);

   return ::success;

}



void generic_object::finalize()
{


}

const char* generic_object::debug_note() const
{

   return nullptr;

}

//bool generic_object::is_ok() const
//{
//
//   return has_id(OK);
//
//}


#ifdef _DEBUG

i64 generic_object::add_ref(OBJ_REF_DBG_PARAMS_DEF)
{

   auto c = atomic_increment(&m_countReference);

#if OBJ_REF_DBG

   add_ref_history(p, pszObjRefDbg);

#endif

   return c;

}


i64 generic_object::dec_ref(OBJ_REF_DBG_PARAMS_DEF)
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


i64 generic_object::release(OBJ_REF_DBG_PARAMS_DEF)
{

   i64 i = dec_ref(OBJ_REF_DBG_ARGS);

   if (i == 0)
   {

      delete_this();

   }

   return i;

}


#endif


::generic_object * generic_object::clone() const
{

   __throw(interface_only_exception());

   return nullptr;

}


void generic_object::set_context_object(::object * pobjectContext)
{

   auto pold = m_pobjectContext;

   if(::is_set(pobjectContext))
   {

      pobjectContext->add_ref();

   }

   m_pobjectContext = pobjectContext;

   ::release(pold);

}




void generic_object::set_finish()
{

}


::estatus generic_object::call()
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


void generic_object::call(const ::var & var)
{

}


void generic_object::receive_response(const ::var& var)
{

}


::estatus generic_object::run()
{

   return ::success;

}


#ifdef WINDOWS


DWORD WINAPI generic_object::s_os_thread_proc(void* p)
{

   ::generic_object* pobject = (::generic_object *) p;

   return pobject->__thread_proc();

}


#else


void * generic_object::s_os_thread_proc(void* p)
{

   ::generic_object* pobject = (::generic_object*) p;

   return (void*)(iptr)pobject->__thread_proc();

}


#endif



::estatus generic_object::add_composite(::generic_object* pobject)
{

   return ::success_none;

}


::estatus generic_object::os_fork(::e_priority epriority, UINT nStackSize, u32 uiCreateFlags, LPSECURITY_ATTRIBUTES psa, ITHREAD * pithread, HTHREAD * phthread)
{

   add_ref(OBJ_REF_DBG_P_NOTE(this, "os_fork"));

   ::generic_object* p = this;

   HTHREAD hthread = NULL_HTHREAD;

   ITHREAD ithread = NULL_ITHREAD;

#ifdef WINDOWS

   DWORD dwThread = 0;

   hthread = ::CreateThread(psa, nStackSize, &::generic_object::s_os_thread_proc, (LPVOID)p, uiCreateFlags, &dwThread);

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
      &generic_object::s_os_thread_proc,
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






::estatus generic_object::add_reference(::generic_object* pobject)
{

   return ::success_none;

}


::estatus generic_object::release_composite(::generic_object* pobject)
{

   return ::success_none;

}


::estatus generic_object::release_reference(::generic_object* pobject)
{

   return ::success_none;

}


::estatus generic_object::set_generic_object_name(const char* pszName)
{

   return ::success_none;

}


void generic_object::delete_this()
{

   try
   {

      delete this;

   }
   catch (...)
   {

   }

}








void generic_object::__tracea(::generic_object * pobject, e_trace_level elevel, const char * pszFunction, const char * pszFile, int iLine, const char * psz)
{

   ::__tracea(pobject, elevel, pszFunction, pszFile, iLine, psz);

}


void generic_object::__tracef(::generic_object * pobject, e_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * pszFormat, ...)
{

   va_list valist;

   va_start(valist, pszFormat);

   __tracev(pobject, elevel, pszFunction, pszFile, iLine, pszFormat, valist);

   va_end(valist);

}


void generic_object::__tracev(::generic_object * pobject, e_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * pszFormat, va_list valist)
{

   string str;

   str.FormatV(pszFormat, valist);

   __tracea(pobject, elevel, pszFunction, pszFile, iLine, str);

}

e_trace_category generic_object::trace_category()
{

   return trace_category_general;

}


e_trace_category generic_object::trace_category(::generic_object * pobject)
{

   return pobject->trace_category();

}


const char * generic_object::topic_text() const
{

   return typeid(*this).name();

}


void generic_object::call_update(const ::id & id, const ::action_context & context)
{

   auto pupdate = new_update();

   pupdate->m_id = id;

   pupdate->m_actioncontext = context;

   call_update(pupdate);

}





void generic_object::call_update(const ::id & id)
{

   auto pupdate = new_update();

   pupdate->m_id = id;

   call_update(pupdate);

}


void generic_object::update(::update * pupdate)
{


}


bool generic_object::already_handled(::update * pupdate) const
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


void generic_object::call_update(::update * pupdate)
{

   if (!pupdate->handled_by(this))
   {

      pupdate->set_handled_by(this);

      this->update(pupdate);

   }

}


strsize generic_object::sz_len() const
{

   return strlen(typeid(*this).name());

}


void generic_object::to_sz(char * sz, strsize len) const
{

   strncpy(sz, typeid(*this).name(), len);

}


::estatus generic_object::__thread_main()
{

   ::estatus estatus = call();

   return estatus;

}


::estatus generic_object::__thread_proc()
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



::estatus generic_object::osthread_init()
{

   return ::success;

}


::estatus generic_object::__thread_init()
{

   return ::success;

}


::estatus generic_object::__thread_term()
{

   return ::success;

}


::estatus generic_object::osthread_term()
{

   return ::success;

}


void generic_object::exchange(stream& s)
{

}


stream & generic_object::write(stream& s) const
{

   return s;

}


stream& generic_object::read(stream& s)
{

   return s;

}


void generic_object::to_string(string& str) const
{

   str = type_c_str();

}



