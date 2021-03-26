#include "framework.h"



/////////////////////////////////////////////////////////////////////////////
// no_track_object

#if defined(_DEBUG) && !defined(___NO_DEBUG_CRT)
#undef new
void * PASCAL no_track_object::operator new(size_t nSize, const char *, i32)
{
   return no_track_object::operator new(nSize);
}
#define new DEBUG_NEW
void PASCAL no_track_object::operator delete(void * pObject, const char *, i32)
{
   if (pObject != nullptr)
      ::free(pObject);
}
#endif

#undef new
void * PASCAL no_track_object::operator new(size_t nSize)
{
   void * p = ::malloc(nSize);
   if (p == nullptr)
      throw memory_exception(::get_thread_app());
   return p;
}
#define new DEBUG_NEW

void PASCAL no_track_object::operator delete(void * p)
{
   if (p != nullptr)
      ::free(p);
}


struct thread_data : public no_track_object
{
   thread_data* pNext; // required to be member of simple_list
   i32 nCount;         // current size of pData
   LPVOID* pData;      // actual thread local data (indexed by nSlot)
};

struct slot_data
{
   ::u32 dwFlags;      // slot flags (allocated/not allocated)
   HINSTANCE hInst;    // module which owns this slot
};

// flags used for slot_data::dwFlags above
#define SLOT_USED   0x01    // slot is allocated

//static
//static pthread_once_t key_once = PTHREAD_ONCE_INIT;

//static void
//make_key()
//{
//  (void)
///}

/*func()
{
    void *ptr;

    if ((ptr = pthread_getspecific(key)) == nullptr) {
        ptr = malloc(OBJECT_SIZE);
        ...
        (void) pthread_setspecific(key, ptr);
    }
    ...
}*/

#undef new


thread_local_storage::thread_local_storage()
{

   m_pthreadslotdata = new thread_slot_data();

}


thread_local_storage::~thread_local_storage()
{

   delete_data();

   __thread_data = nullptr;

}

void thread_local_storage::delete_data()
{

   if(m_pthreadslotdata != nullptr)
   {

      delete m_pthreadslotdata;

      m_pthreadslotdata = nullptr;

   }

}


thread_slot_data * thread_local_storage::get_slot_data()
{

   return m_pthreadslotdata;

}
#define new DEBUG_NEW


thread_slot_data::thread_slot_data()
{
   __memset(m_pa, 0, sizeof(m_pa));
}

void thread_slot_data::delete_data()
{
   for(i32 i = 0; i < 1024; i++)
   {
      if(m_pa[i] != nullptr)
      {
         delete m_pa[i];
      }
   }
   free(this);
}


/////////////////////////////////////////////////////////////////////////////
// thread_local_object


/////////////////////////////////////////////////////////////////////////////
// CProcessLocalData

no_track_object* process_local_object::get_data(
no_track_object* ( * pfnCreateObject)())
{
   if (m_pObject == nullptr)
   {
      single_lock synchronizationlock(&m_mutex, true);
      try
      {
         if (m_pObject == nullptr)
            m_pObject = (*pfnCreateObject)();
      }
      catch(::exception::aura * pe)
      {
         ::ca2::rethrow(pe);
      }

   }
   return m_pObject;
}

process_local_object::~process_local_object()
{
   if (m_pObject != nullptr)
      delete m_pObject;
}

/////////////////////////////////////////////////////////////////////////////
// Init/Term for thread/process local data

/*void CLASS_DECL_CORE ::ca2::InitLocalData(HINSTANCE hInst)
{
   if (__thread_data != nullptr)
      __thread_data->AssignInstance(hInst);
}

void CLASS_DECL_CORE __term_local_data(HINSTANCE hInst, bool bAll)
{
   if (__thread_data != nullptr)
      __thread_data->DeleteValues(hInst, bAll);
}*/

// This object count is needed to support Win32s, such that the
// thread-local and process-local data is not destroyed prematurely.
// It is basically a object count of the number of processes that
// have attached to the ca2 API DLL.

long gen_TlsRef = 0;

void CLASS_DECL_CORE __tls_add_ref()
{
   ++gen_TlsRef;
}

void CLASS_DECL_CORE __tls_release()
{
   if (gen_TlsRef == 0 || --gen_TlsRef == 0)
   {
      if (__thread_data != nullptr)
      {
         __thread_data->~thread_local_storage();
         __thread_data = nullptr;
      }
   }
}

thread_object < thread_local_storage > g_threaddata;


