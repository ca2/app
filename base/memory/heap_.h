#pragma once


template < typename TYPE_CHAR >
class string_base;


using string = string_base < ansichar >;


namespace heap
{


   class CLASS_DECL_AURA system_memory_allocator
   {
   public:

#if MEMDLEAK  || defined(__MCRTDBG)
      inline static void * alloc(memsize iSize,  const char * pszFile, int iLine)
      {

         return system_heap_alloc_dbg(iSize, 725, pszFile, iLine);

      }
#else
      inline static void * alloc(memsize iSize)
      {

         return system_heap_alloc(iSize);

      }
#endif


      inline static void _free(void * p)
      {

         system_heap_free(p);

      }


   };


   class CLASS_DECL_AURA default_memory_allocator
   {
   public:


#if MEMDLEAK || defined(__MCRTDBG)
      inline static void * alloc(memsize iSize, const char * pszFile, int iLine)
      {

         return memory_alloc_dbg(iSize, 724, pszFile, iLine);

      }
#else
      inline static void * alloc(memsize iSize)
      {

         return memory_alloc(iSize);

      }
#endif


      inline static void _free(void * p)
      {

         ::memory_free(p);

      }


   };


//   class CLASS_DECL_AURA heap_base
//   {
//   public:
//
//
//      void *         m_p;
//      memsize       m_uiSize;
//
//
//      heap_base()
//      {
//
//         m_p         = nullptr;
//         m_uiSize    = 0;
//
//      }
//
//      heap_base(memsize uiSize)
//      {
//
//         m_p         = nullptr;
//         m_uiSize    = 0;
//
//         size(uiSize);
//
//      }
//
//      virtual ~heap_base()
//      {
//
//         _free();
//
//      }
//
//      memsize size()
//      {
//
//         return m_uiSize;
//
//      }
//
//
//      void zero();
//
//
//      virtual memsize size(memsize uiSize)
//      {
//
//         if(m_p == nullptr)
//         {
//
//            m_p = memory_alloc(uiSize);
//
//         }
//         else
//         {
//
//            m_p = memory_realloc(m_p,uiSize);
//
//         }
//
//         if(m_p != nullptr)
//         {
//
//            m_uiSize = uiSize;
//
//         }
//
//         return m_uiSize;
//
//      }
//
//
//      void _free()
//      {
//
//         if(m_p != nullptr)
//         {
//
//            ::memory_free(m_p);
//
//            m_p = nullptr;
//
//         }
//
//      }
//
//
//   };
//

//   template < typename T >
//   class heap:
//      public heap_base
//   {
//   public:
//
//
//      heap() {   }
//
//      heap(memsize iCount): heap_base(iCount * sizeof(T)) {   }
//
//      operator T * () { return (T *)m_p; }
//      operator const T * () const { return (T *)m_p; }
//
//      memsize count() { return size() / sizeof(T); }
//
//      void stralloc(::count cChar) { size((cChar + 1) * sizeof(T)); }
//
//      string & to_string(string & str) const;
//
//   };
//

} // namespace heap



//typedef ::heap::heap < char > hstring_base;
//
//class CLASS_DECL_AURA hstring:
//   public hstring_base
//{
//public:
//
//   hstring() {}
//   hstring(memsize uiSize): hstring_base(uiSize) {}
//
//};


//typedef ::heap::heap < unichar > hwstring_base;
//
//class CLASS_DECL_AURA wstring:
//   public hwstring_base
//{
//public:
//
//   wstring() {}
//   wstring(memsize uiSize): hwstring_base(uiSize) {}
//
//};

