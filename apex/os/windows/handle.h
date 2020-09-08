// This is apex API library.
//
//
//
//
//
//
//
//

/////////////////////////////////////////////////////////////////////////////
// CHandleMap
//
//  Note: Do not access the members of this class directly.
//      Use ::windows::window::from_handle, ::windows::graphics::from_handle, etc.
//      The actual definition is only included because it is
//      necessary for the definition of WindowsThread.
//
//  Most Windows objects are represented with a HANDLE, including
//      the most important ones, oswindow, HDC, HPEN, HFONT etc.
//  We want C++ objects to wrap these handle based objects whenever we can.
//  Since Windows objects can be created outside of C++ (eg: calling
//      ::CreateWindow will return an oswindow with no C++ wrapper) we must
//      support a reasonably uniform mapping from permanent handles
//      (i.e. the ones allocated in C++) and temporary handles (i.e.
//      the ones allocated in C, but passed through a C++ interface.
//  We keep two dictionaries for this purpose.  The permanent dictionary
//      stores those C++ objects that have been explicitly created by
//      the developer.  The C++ constructor for the wrapper class will
//      insert the mapping into the permanent dictionary and the C++
//      destructor will remove it and possibly free up the associated
//      Windows object.
//  When a handle passes through a C++ interface that doesn't exist in
//      the permanent dictionary, we allocate a temporary wrapping object
//      and store that mapping into the temporary dictionary.
//  At idle time the temporary wrapping objects are flushed (since you better
//      not be holding onto something you didn't create).
//

#pragma once

template <>
inline UINT HashKey < oswindow >(oswindow key)
{
   // default identity hash - works for most primitive values
   return (DWORD)((uptr)key);
}

template <>
inline UINT HashKey < HMENU >(HMENU key)
{
   // default identity hash - works for most primitive values
   return (DWORD)((uptr)key);
}

template <>
inline UINT HashKey < HDC >(HDC key)
{
   // default identity hash - works for most primitive values
   return (DWORD)((uptr)key);
}

template <>
inline UINT HashKey < HGDIOBJ >(HGDIOBJ key)
{
   // default identity hash - works for most primitive values
   return (DWORD)((uptr)key);
}

template <>
inline UINT HashKey < HIMAGELIST >(HIMAGELIST key)
{
   // default identity hash - works for most primitive values
   return (DWORD)((uptr)key);
}


namespace windows
{

   class window;
   class graphics;
   class object;

   template < i32 t_iHandleCount >
   class handle_base
   {
   public:
      HANDLE m_handlea[t_iHandleCount];
      static const i32 s_iHandleCount = t_iHandleCount;
   };

   template < class H >
   class handle1 : public handle_base < 1 >
   {
   public:
      handle1() { m_handlea[0] = nullptr; }
      typedef handle_base < 1 > HANDLE_BASE_TYPE;
      inline H get_handle() const { return static_cast < H > (m_handlea[0]); }
      inline operator H () const { return get_handle(); }
      inline H set_handle(H h) { return static_cast < H > (m_handlea[0] = static_cast < HANDLE > (h)); }
   };

   template < class H1, class H2 >
   class handle2 : public handle_base < 2 >
   {
   public:
      handle2() { m_handlea[0] = nullptr; m_handlea[1] = nullptr; }
      typedef handle_base < 2 > HANDLE_BASE_TYPE;
      inline H1 get_os_data() const { return static_cast < H1 > (m_handlea[0]); }
      inline H2 get_handle2() const { return static_cast < H2 > (m_handlea[0]); }
      inline H1 set_handle1(H1 h) { return static_cast < H1 > (m_handlea[0] = static_cast < HANDLE > (h)); }
      inline H2 set_handle2(H2 h) { return static_cast < H2 > (m_handlea[1] = static_cast < HANDLE > (h)); }
   };

   typedef handle1 < oswindow > oswindow_handle;
   typedef handle1 < HMENU > hmenu_handle;
   typedef handle2 < HDC, HDC > hdc_handle;
   typedef handle1 < HGDIOBJ > hgdiobj_handle;
   typedef handle1 < HIMAGELIST > himagelist_handle;

} // namespace windows


template<class TYPE>
struct ConstructDestruct
{
   static void Construct(object* pObject)
   {
      new (pObject) TYPE;
   }
   static void Destruct(object* pObject)
   {
      TYPE* p = dynamic_cast < TYPE * > (pObject);
      p->~TYPE();
   }
   static void Construct(TYPE * pObject)
   {
#undef new
      new (pObject) TYPE;
#define new ACME_NEW
   }
   static void Destruct(TYPE * pObject)
   {
      TYPE* p = dynamic_cast < TYPE * > (pObject);
      p->~TYPE();
   }
};

class WindowsThread;       // forward context_object for friend declaration


template < class HT, class CT >
class handle_map :
   virtual public ::object
{
public:


   fixed_alloc_no_sync     m_alloc;
   ::mutex                   m_mutex;
   void (* m_pfnConstructObject)(CT* pObject);
   void (* m_pfnDestructObject)(CT* pObject);
   map < HANDLE, HANDLE, CT *, CT *> m_permanentMap;
   map < HANDLE, HANDLE, CT *, CT *> m_temporaryMap;

   handle_map(::object * pobject);
   virtual ~handle_map()
   {
      delete_temp();
   }

// Operations
public:
   CT * from_handle(HANDLE h, CT * (* pfnAllocator) (__pointer(::apex::application), HANDLE) = nullptr, __pointer(::apex::application) papp = nullptr);
   void delete_temp();

   void set_permanent(HANDLE h, CT * permOb);
   void remove_handle(HANDLE h);

   CT * lookup_permanent(HANDLE h);
   CT * lookup_temporary(HANDLE h);

   friend class thread;
};

class CLASS_DECL_APEX oswindow_map :
   public handle_map < ::windows::oswindow_handle, ::windows::window >
{
public:
   oswindow_map(::object * pobject) : handle_map < ::windows::oswindow_handle, ::windows::window >(pobject) {}
};

/*class CLASS_DECL_APEX hdc_map :
   public handle_map < ::windows::hdc_handle, ::windows::graphics >
{
public:
};*/

/*class hgdiobj_map :
   public handle_map < ::windows::hgdiobj_handle, ::windows::object >
{
public:
};*/

/*
class CLASS_DECL_APEX hdc_map :
   public handle_map < ::windows::hmenu_handle, ::windows::menu >
{
public:
};
*/


template < class HT, class CT >
handle_map < HT, CT > ::handle_map(::object * pobject) :
   ::object(pobject),
   m_permanentMap(papp, 1024),
   m_temporaryMap(papp, 1024),
   m_alloc(sizeof(CT), 1024),
   m_mutex(pobject)
{

   ASSERT(HT::s_iHandleCount == 1 || HT::s_iHandleCount == 2);

   m_permanentMap.InitHashTable(1024, TRUE);
   m_temporaryMap.InitHashTable(1024, TRUE);

   m_pfnConstructObject    = ConstructDestruct<CT>::Construct;
   m_pfnDestructObject     = ConstructDestruct<CT>::Destruct;

}

template < class HT, class CT >
CT* handle_map < HT, CT >::from_handle(HANDLE h, CT * (*pfnAllocator) (__pointer(::apex::application), HANDLE), __pointer(::apex::application) papp)
{

   single_lock sl(&m_mutex, TRUE);

   ASSERT(HT::s_iHandleCount == 1 || HT::s_iHandleCount == 2);

   if (h == nullptr)
      return nullptr;

   CT* pObject = lookup_permanent(h);
   if (pObject != nullptr && pObject->get_os_data() == (void *) h)
      return pObject;   // return permanent one
   else if ((pObject = lookup_temporary(h)) != nullptr && pObject->get_os_data() == (void *) h)
   {
      HANDLE* ph = pObject->m_handlea;
      ASSERT(ph[0] == h || ph[0] == nullptr);
      ph[0] = h;
      if (HT::s_iHandleCount == 2)
      {
         ASSERT(ph[1] == h || ph[1] == nullptr);
         ph[1] = h;
      }
      return pObject;   // return current temporary one
   }

   // This handle wasn't created by us, so we must create a temporary
   // C++ object to wrap it.  We don't want the ::account::user to see this memory
   // allocation, so we turn tracing off.

   //bool bEnable = __enable_memory_tracking(FALSE);
#ifndef ___PORTABLE
//   _PNH pnhOldHandler = __set_new_handler(&__critical_new_handler);
#endif

   CT* pTemp = nullptr;
   try
   {
      if(pfnAllocator != nullptr)
      {
         pTemp = pfnAllocator(papp, h);
         if (pTemp == nullptr)
            __throw(memory_exception());
      }
      else
      {
         // get memory for the object from the fixed allocator
   //      ASSERT((UINT)m_pClass->m_nObjectSize == m_alloc.GetAllocSize());
         pTemp = (CT*)m_alloc.Alloc();
         if (pTemp == nullptr)
            __throw(memory_exception());

         // now construct the object in place
         ASSERT(m_pfnConstructObject != nullptr);
         (*m_pfnConstructObject)(pTemp);
      }

      // set it in the map
      m_temporaryMap.set_at(h, pTemp);
   }
   catch(::exception::apex * pe)
   {
#ifndef ___PORTABLE
//      __set_new_handler(pnhOldHandler);
#endif
      //__enable_memory_tracking(bEnable);
      ::exception::rethrow(pe);
   }


#ifndef ___PORTABLE
   //__set_new_handler(pnhOldHandler);
#endif
   //__enable_memory_tracking(bEnable);

   // now set the handle in the object
   HANDLE* ph = pTemp->m_handlea;  // after object
   ph[0] = h;
   if (HT::s_iHandleCount == 2)
      ph[1] = h;

   return pTemp;
}

#ifdef __DEBUG   // out-of-line version for memory tracking
template < class HT, class CT >
void handle_map < HT, CT >::set_permanent(HANDLE h, CT * permOb)
{

   single_lock sl(&m_mutex, TRUE);

   //bool bEnable = __enable_memory_tracking(FALSE);
   m_permanentMap[(LPVOID)h] = permOb;
   //__enable_memory_tracking(bEnable);

}
#endif //__DEBUG

#ifdef __DEBUG
template < class HT, class CT >
void handle_map < HT, CT > ::remove_handle(HANDLE h)
{

   single_lock sl(&m_mutex, TRUE);

   // make sure the handle entry is consistent before deleting
   CT* pTemp = lookup_temporary(h);
   if (pTemp != nullptr)
   {
      // temporary objects must have correct handle values
      HANDLE* ph = pTemp->m_handlea;
      ASSERT(ph[0] == h || ph[0] == nullptr);
      if (HT::s_iHandleCount == 2)
      {
         ASSERT(ph[1] == h || ph[1] == nullptr);
      }
   }
   pTemp = lookup_permanent(h);
   if (pTemp != nullptr)
   {
      HANDLE* ph = pTemp->m_handlea;
      ASSERT(ph[0] == h);
      // permanent object may have secondary handles that are different
   }
   // remove only from permanent map -- temporary objects are removed
   //  at idle in CHandleMap::delete_temp, always!
   m_permanentMap.remove_key((LPVOID)h);
}
#endif //__DEBUG

template < class HT, class CT >
void handle_map < HT, CT >::delete_temp()
{

   single_lock sl(&m_mutex, TRUE);

   if (::is_null(this))
      return;

   POSITION pos = m_temporaryMap.get_start_position();
   while (pos != nullptr)
   {
      HANDLE h; // just used for asserts
      CT * pTemp;
      m_temporaryMap.get_next_assoc(pos, h, pTemp);

      // zero out the handles
      ASSERT(HT::s_iHandleCount == 1 || HT::s_iHandleCount == 2);
      HANDLE* ph = pTemp->m_handlea;  // after object
      ASSERT(ph[0] == h || ph[0] == nullptr);
      ph[0] = nullptr;
      if (HT::s_iHandleCount == 2)
      {
         ASSERT(ph[1] == h || ph[1] == nullptr);
         ph[1] = nullptr;
      }

      ASSERT(m_pfnDestructObject != nullptr);
      //pTemp->get_context_application() = nullptr;
      (*m_pfnDestructObject)(pTemp);   // destruct the object
   }

   m_temporaryMap.remove_all();       // free up dictionary links etc
   m_alloc.FreeAll();   // free all the memory used for these temp objects
}


// Note: out-of-line __DEBUG version is in winhand.cpp
#ifndef __DEBUG
template < class HT, class CT >
inline void handle_map < HT, CT >::set_permanent(HANDLE h, CT * permOb)
   { m_permanentMap[(HANDLE)h] = permOb; }

template < class HT, class CT >
inline void handle_map < HT, CT >::remove_handle(HANDLE h)
{
   // remove only from permanent map -- temporary objects are removed
   //  at idle in CHandleMap::delete_temp, always!
   m_permanentMap.remove_key((HANDLE)h);
}
#endif //__DEBUG

template < class HT, class CT >
inline CT* handle_map <HT, CT>::lookup_permanent(HANDLE h)
{

   single_lock sl(&m_mutex, TRUE);

   CT * pt = m_permanentMap.get(h, (CT*) nullptr);
   if(pt != nullptr && pt->get_os_data() == (void *) h)
      return pt;
   else
      return nullptr;

}

template < class HT, class CT >
inline CT* handle_map <HT, CT>::lookup_temporary(HANDLE h)
{

   single_lock sl(&m_mutex, TRUE);

   CT * pt = m_temporaryMap.get(h, (CT*) nullptr);
   if(pt != nullptr && pt->get_os_data() == (void *) h)
      return pt;
   else
      return nullptr;

}


CLASS_DECL_APEX oswindow_map * get_oswindow_map(bool bCreate = FALSE);
CLASS_DECL_APEX himagelist_map * afxMapHIMAGELIST(bool bCreate = FALSE);
//CLASS_DECL_APEX hdc_map * afxMapHDC(bool bCreate = FALSE);
//CLASS_DECL_APEX hgdiobj_map * afxMapHGDIOBJ(bool bCreate = FALSE);
//CLASS_DECL_APEX hmenu_map * afx_map_HMENU(bool bCreate = FALSE);
