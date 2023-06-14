#include "framework.h"


CLASS_DECL_ACME void * x86_memory_pool_alloc(memsize s);
CLASS_DECL_ACME void x86_memory_pool_freec(void * p);


class CLASS_DECL_ACME x86_oriented_memory_allocator
{
public:

   void * alloc(int iSize)
   {

      return memory_allocate(iSize);

   }

   void free(void * p)
   {

      ::memory_free(p);

   }

};



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

      void * p = memory_allocate(iSize * 2);

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
         pb = (byte *) memory_allocate(c);

         // can use string because messed all with cache out hot hit !!/^`}{{ **!
         //::acme::application * papp = get_app();
         //information("handler oriented cache: memory out of cache palace garden (size=%d)", c);
      }
      return pb;


   }
   void free(void * p)
   {
      if((p >= m_p && p < m_ba) || (p >= &m_ba[m_iCurPos] && p < ((byte *)m_p) + m_iMaxSize))
      {
         // freeing memory in palace garden (not supposed to allocated memory in these places as they would cause a cache fault)
         throw_exception(error_bad_argument);
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
thread_local iptr t_iProcessorOrientedMemoryPool;

//void thread_set_process



CLASS_DECL_ACME x86_cache_oriented_memory_pool * x86_cache_oriented_get_thread_memory_pool()
{

   return s_processororientedmemorypoola[t_iProcessorOrientedMemoryPool];

}


CLASS_DECL_ACME int_bool x86_cache_oriented_set_thread_memory_pool(int iPoolIndex)
{

   if(iPoolIndex < 0)
   {

      throw_exception(error_bad_argument);

      return false;

   }

   if(iPoolIndex >= MAX_PROC_CACHE_ORIENTED_MEM_POOL)
   {

      throw_exception(error_bad_argument);

      return false;
   }

   if(s_processororientedmemorypoola[iPoolIndex] == nullptr)
   {

      s_processororientedmemorypoola[iPoolIndex] = x86_cache_oriented_memory_pool::new_pool();

   }

   t_iProcessorOrientedMemoryPool = iPoolIndex;

   return true;

}


CLASS_DECL_ACME void x86_cache_oriented_destroy_all_memory_pools()
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


CLASS_DECL_ACME void * x86_cache_oriented_memory_alloc(memsize s)
{

   return x86_cache_oriented_get_thread_memory_pool()->alloc(s);

}


CLASS_DECL_ACME void x86_cache_oriented_memory_free(void * p)
{

   return x86_cache_oriented_get_thread_memory_pool()->free(p);

}

CLASS_DECL_ACME void x86_cache_oriented_memory_reset()
{

   return x86_cache_oriented_get_thread_memory_pool()->reset();

}

//#define memory_new ACME_NEW


