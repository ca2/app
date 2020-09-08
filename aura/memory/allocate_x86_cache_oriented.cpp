#include "framework.h"


CLASS_DECL_AURA void * x86_memory_pool_alloc(memsize s);
CLASS_DECL_AURA void x86_memory_pool_freec(void * p);


class CLASS_DECL_AURA x86_oriented_memory_allocator
{
public:

   void * alloc(int iSize)
   {

      return memory_alloc(iSize);

   }

   void free(void * p)
   {

      ::memory_free(p);

   }

};

#undef new

class x86_cache_oriented_memory_pool
{
private:

   void * operator new(size_t);
   void * operator new(size_t,const char *,i32);

   void operator delete(void * p)
   {

   }

   void operator delete(void * p,const char *,i32)
   {

   }


public:

   void *      m_p;
   iptr     m_iMaxSize;
   iptr     m_iSize;
   int         m_iCurPos;
   byte        m_ba[1];





   static int calc_cache_size()
   {

      return 1024 * 1024;

   }


   static x86_cache_oriented_memory_pool * new_pool()
   {

      int iSize = calc_cache_size();

      void * p = memory_alloc(iSize * 2);

      // TODO : better dynamically memory align

      byte * pb;

      if(((iptr)p) % iSize == 0)
      {
         pb = (byte *)p;
      }
      else
      {
         pb = (byte *)(((iptr)p) % iSize + (((iptr)p) / iSize) * iSize);
      }

      x86_cache_oriented_memory_pool * ppool = (x86_cache_oriented_memory_pool *) pb;

      ppool->m_p = p;
      ppool->m_iMaxSize = iSize * 2;
      ppool->m_iSize = iSize - sizeof(x86_cache_oriented_memory_pool);
      ppool->m_iCurPos = 0;

      return ppool;

   }

   static void del_pool(x86_cache_oriented_memory_pool * p)
   {
      ::memory_free(p->m_p);
   }

   void * alloc(::count c)
   {
      byte * pb;

      if(m_iCurPos + c < m_iSize)
      {
         pb =  &m_ba[m_iCurPos];

         m_iCurPos += (int) c;
      }
      else
      {
         pb = (byte *) memory_alloc(c);

         // can use string because messed all with cache out hot hit !!/^`}{{ **!
         ::aura::application * papp = get_context_application();
         TRACE("handler oriented cache: memory out of cache palace garden (size=%d)", c);
      }
      return pb;


   }
   void free(void * p)
   {
      if((p >= m_p && p < m_ba) || (p >= &m_ba[m_iCurPos] && p < ((byte *)m_p) + m_iMaxSize))
      {
         // freeing memory in palace garden (not supposed to allocated memory in these places as they would cause a cache fault)
         __throw(invalid_argument_exception());
      }
      else if(p < m_ba || p > &m_ba[m_iCurPos])
      {
         // disregard
      }
      else
      {
         memory_free(p);
      }
   }

   void reset()
   {

      m_iCurPos = 0;

   }

};

static x86_cache_oriented_memory_pool * s_processororientedmemorypoola[MAX_PROC_CACHE_ORIENTED_MEM_POOL];
//thread_int_ptr < iptr > t_iProcessorOrientedMemoryPool;

//void thread_set_process



CLASS_DECL_AURA x86_cache_oriented_memory_pool * x86_cache_oriented_get_thread_memory_pool()
{

   return s_processororientedmemorypoola[thread_value("x86_cache_oriented_get_thread_memory_pool").i32()];

}


CLASS_DECL_AURA int_bool x86_cache_oriented_set_thread_memory_pool(int iPoolIndex)
{

   if(iPoolIndex < 0)
   {

      __throw(invalid_argument_exception());

      return false;

   }

   if(iPoolIndex >= MAX_PROC_CACHE_ORIENTED_MEM_POOL)
   {

      __throw(invalid_argument_exception());

      return false;
   }

   if(s_processororientedmemorypoola[iPoolIndex] == nullptr)
   {

      s_processororientedmemorypoola[iPoolIndex] = x86_cache_oriented_memory_pool::new_pool();

   }

   thread_value("x86_cache_oriented_get_thread_memory_pool") = iPoolIndex;

   return true;

}


CLASS_DECL_AURA void x86_cache_oriented_destroy_all_memory_pools()
{

   for(int iPoolIndex = 0; iPoolIndex < MAX_PROC_CACHE_ORIENTED_MEM_POOL; iPoolIndex++)
   {

      if(s_processororientedmemorypoola[iPoolIndex] != nullptr)
      {

         x86_cache_oriented_memory_pool::del_pool(s_processororientedmemorypoola[iPoolIndex]);

         s_processororientedmemorypoola[iPoolIndex] = nullptr;

      }

   }

}


CLASS_DECL_AURA void * x86_cache_oriented_memory_alloc(memsize s)
{

   return x86_cache_oriented_get_thread_memory_pool()->alloc(s);

}


CLASS_DECL_AURA void x86_cache_oriented_memory_free(void * p)
{

   return x86_cache_oriented_get_thread_memory_pool()->free(p);

}

CLASS_DECL_AURA void x86_cache_oriented_memory_reset()
{

   return x86_cache_oriented_get_thread_memory_pool()->reset();

}

#define new ACME_NEW


