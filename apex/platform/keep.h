#pragma once


inline var & thread_value(const ::id & id);
inline void thread_set(const ::id & id) { thread_value(id) = true; }
inline void thread_unset(const ::id & id) { thread_value(id) = false; }
inline bool thread_is_set(const ::id & id);

//
//template  < typename TYPE >
//inline TYPE default_keep_value()
//{
//
//   return (TYPE) nullptr;
//
//}
//
//
//template  < >
//inline bool default_keep_value < bool >()
//{
//
//   return true;
//
//}

template  < >
inline ::thread * default_keep_value < ::thread * >()
{

   return ::get_task();

}
//
//
//template < typename TYPE >
//class ___keep
//{
//public:
//
//
//   TYPE    m_keepValue;
//   TYPE    m_keepAwayValue;
//   TYPE *  m_pKept;
//   bool    m_bKept;
//
//
//   ___keep(___keep && keep);
//
//   template < typename TYPE_KEEP, typename TYPE_KEEP_AWAY >
//   ___keep(TYPE & kept, const TYPE_KEEP & keepValue, const TYPE_KEEP_AWAY & keepAwayValue, bool bStartKept = true);
//
//   template < typename TYPE_KEEP >
//   ___keep(TYPE & kept, const TYPE_KEEP & keepValue = ::default_keep_value < TYPE >());
//
//   virtual ~___keep();
//
//   void Keep();
//   void KeepAway();
//
//
//};


//template < typename TYPE >
//class ___keep_pointer
//{
//public:
//
//
//   TYPE *            m_keepValue;
//   TYPE *            m_keepAwayValue;
//   __pointer(TYPE) * m_pKept;
//   bool              m_bKept;
//
//
//   template < typename TYPE_KEEP, typename TYPE_KEEP_AWAY >
//   ___keep_pointer(__pointer(TYPE)* pKept, TYPE_KEEP * keepValue, TYPE_KEEP_AWAY * keepAwayValue, bool bStartKept = true);
//
//   template < typename TYPE_KEEP >
//   ___keep_pointer(__pointer(TYPE)* pKept, TYPE_KEEP * keepValue = ::default_keep_value < TYPE * >());
//
//   ___keep_pointer(___keep_pointer&& keep);
//
//   virtual ~___keep_pointer();
//
//   void Keep();
//   void KeepAway();
//
//
//};
//
//

//template < typename TYPE >
//template < typename TYPE_KEEP, typename TYPE_KEEP_AWAY >
//___keep < TYPE > ::___keep(TYPE & kept, const TYPE_KEEP & keepValue, const TYPE_KEEP_AWAY & keepAwayValue,bool bStartKept):
//   m_keepValue(keepValue),
//   m_keepAwayValue(keepAwayValue),
//   m_pKept(&kept)
//{
//   if(bStartKept)
//   {
//      m_bKept = false;
//      Keep();
//   }
//   else
//   {
//      m_bKept = true;
//      KeepAway();
//   }
//
//}

//template < typename TYPE >
//template < typename TYPE_KEEP >
//___keep < TYPE > ::___keep(TYPE & kept, const TYPE_KEEP & keepValue) :
//   m_keepValue(keepValue),
//   m_keepAwayValue(kept),
//   m_pKept(&kept)
//{
//   m_bKept = false;
//   Keep();
//}
//
//
//template < typename TYPE >
//___keep < TYPE > ::___keep(___keep && keep) :
//   m_keepValue(keep.m_keepValue),
//   m_keepAwayValue(keep.m_keepAwayValue),
//   m_pKept(keep.m_pKept),
//   m_bKept(keep.m_bKept)
//{
//   keep.m_pKept = nullptr;
//}


//template < typename TYPE >
//___keep<TYPE>::~___keep()
//{
//   if(m_bKept)
//   {
//      KeepAway();
//   }
//}
//
//template < typename TYPE >
//void ___keep<TYPE>::Keep()
//{
//   if(m_pKept)
//   {
//      *m_pKept = m_keepValue;
//      m_bKept = true;
//   }
//}
//
//template <class TYPE>
//void ___keep<TYPE>::KeepAway()
//{
//   if(m_pKept)
//   {
//      *m_pKept = m_keepAwayValue;
//      m_bKept = false;
//   }
//}

//template < typename TYPE >
//template < typename TYPE_KEEP, typename TYPE_KEEP_AWAY >
//___keep_pointer < TYPE > ::___keep_pointer(__pointer(TYPE)* pKept, TYPE_KEEP * keepValue, TYPE_KEEP_AWAY * keepAwayValue, bool bStartKept) :
//   m_keepValue(keepValue),
//   m_keepAwayValue(keepAwayValue),
//   m_pKept(pKept)
//{
//   if (bStartKept)
//   {
//      m_bKept = false;
//      Keep();
//   }
//   else
//   {
//      m_bKept = true;
//      KeepAway();
//   }
//
//}
//
//template < typename TYPE >
//template < typename TYPE_KEEP >
//___keep_pointer < TYPE > ::___keep_pointer(__pointer(TYPE)* pKept, TYPE_KEEP * keepValue) :
//   m_keepValue(keepValue),
//   m_keepAwayValue(*pKept),
//   m_pKept(pKept)
//{
//   m_bKept = false;
//   Keep();
//}
//
//
//template < typename TYPE >
//___keep_pointer < TYPE > ::___keep_pointer(___keep_pointer&& keep) :
//   m_keepValue(keep.m_keepValue),
//   m_keepAwayValue(keep.m_keepAwayValue),
//   m_pKept(keep.m_pKept),
//   m_bKept(keep.m_bKept)
//{
//   keep.m_pKept = nullptr;
//}
//
//
//template < typename TYPE >
//___keep_pointer<TYPE>::~___keep_pointer()
//{
//   if (m_bKept)
//   {
//      KeepAway();
//   }
//}
//
//template < typename TYPE >
//void ___keep_pointer<TYPE>::Keep()
//{
//   if (m_pKept)
//   {
//      *m_pKept = m_keepValue;
//      m_bKept = true;
//   }
//}
//
//template <class TYPE>
//void ___keep_pointer<TYPE>::KeepAway()
//{
//   if (m_pKept)
//   {
//      *m_pKept = m_keepAwayValue;
//      m_bKept = false;
//   }
//}
//

//template < typename TYPE >
//___keep < TYPE > keep(TYPE * pKept)
//{
//
//   return ___keep < TYPE >(pKept, ::default_keep_value < TYPE >());
//
//}


//template < typename TYPE, typename TYPE_KEEP >
//___keep < TYPE > keep(TYPE * pKept, TYPE_KEEP * keepValue)
//{
//
//   return ___keep < TYPE >(pKept, keepValue);
//
//}


//template < typename TYPE, typename TYPE_KEEP, typename TYPE_KEEP_AWAY >
//___keep < TYPE > keep(TYPE * pKept, TYPE_KEEP * keepValue, TYPE_KEEP_AWAY * keepAwayValue,  bool bStartKept = true)
//{
//
//   return ___keep < TYPE >(pKept, keepValue, keepAwayValue, bStartKept);
//
//}
//

//template < typename TYPE >
//___keep < TYPE > keep(TYPE & kept)
//{
//
//   return ___keep < TYPE >(kept, ::default_keep_value < TYPE >());
//
//}

//template < typename TYPE, typename TYPE_KEEP >
//___keep_pointer < TYPE > keep(__pointer(TYPE)* pKept, TYPE_KEEP * keepValue)
//{
//
//   return ___keep_pointer < TYPE >(pKept, keepValue);
//
//}


//template < typename TYPE >
//___keep_pointer < TYPE > keep(__pointer(TYPE)& kept)
//{
//
//   return ___keep_pointer < TYPE >(&kept, ::default_keep_value < TYPE >());
//
//}


//template < typename TYPE, typename TYPE_KEEP >
//___keep < TYPE > keep(TYPE & kept, const TYPE_KEEP & keepValue)
//{
//
//   return ___keep < TYPE >(kept, keepValue);
//
//}


//template < typename TYPE, typename TYPE_KEEP, typename TYPE_KEEP_AWAY >
//___keep < TYPE > keep(TYPE & kept, const TYPE_KEEP & keepValue, const TYPE_KEEP_AWAY & keepAwayValue, bool bStartKept = true)
//{
//
//   return ___keep < TYPE >(kept, keepValue, keepAwayValue, bStartKept);
//
//}
/// _<3tbs special singular macro start with underscore and all lower case

#define __keep(...) auto TOKEN_AT_LINE(__keep) = keep(__VA_ARGS__)
#define __keep_true(...) auto TOKEN_AT_LINE(__keep_true) = keep(__VA_ARGS__, true)
#define __keep_false(...) auto TOKEN_AT_LINE(__keep_false) = keep(__VA_ARGS__, false)
#define __keep_thread_flag(...) auto TOKEN_AT_LINE(__keep_thread_flag) = keep_thread_flag(__VA_ARGS__)
#define __keep_current_thread(...) auto TOKEN_AT_LINE(__keep_current_thread) = keep(__VA_ARGS__, ::get_task())


#define __task_guard_ret(flag, ret) \
 \
sync_lock sl(mutex()); \
 \
if (flag) \
{ \
\
   ret; \
\
} \
\
auto TOKEN_AT_LINE(__task_guard_task_ret) = keep(flag); \
\
sl.unlock()

#define __task_guard(flag) __task_guard_ret(flag, return)


#define __guard_wait_ret(flag, ret) \
 \
sync_lock sl(mutex()); \
 \
while (flag) \
{ \
\
   \
   sl.unlock(); \
   \
   if (!thread_sleep(100)) \
   {\
   \
      ret; \
   \
   } \
   \
   sl.lock(); \
   \
   \
} \
\
auto TOKEN_AT_LINE(__guard_wait_ret) = keep(&flag); \
\
sl.unlock()

#define __guard_wait(flag) __task_guard_ret(flag, return)



//template <class TYPE>
//class ___keep_on
//{
//public:
//
//
//   TYPE     m_keepValue;
//   bool     m_bWasSet;
//   TYPE *   m_pKept;
//   bool     m_bKept;
//
//   template < typename TYPE_KEEP>
//   ___keep_on(TYPE * pKept, TYPE_KEEP keep, bool bStartKept = true);
//   ___keep_on(___keep_on && on):
//      m_keepValue(on.m_keepValue),
//      m_bWasSet(on.m_bWasSet),
//      m_pKept(on.m_pKept),
//      m_bKept(on.m_bKept)
//   {
//      on.m_pKept = nullptr;
//   }
//   virtual ~___keep_on();
//
//   void Keep();
//   void KeepAway();
//
//
//};



//template < typename TYPE >
//template < typename TYPE_KEEP >
//___keep_on<TYPE>::___keep_on(TYPE * pKept, TYPE_KEEP keepValue, bool bStartKept) :
//   m_keepValue(keepValue),
//   m_pKept(pKept)
//{
//   if (bStartKept)
//   {
//      m_bKept = false;
//      Keep();
//   }
//   else
//   {
//      m_bKept = true;
//      KeepAway();
//   }
//
//}
//template <class TYPE>
//___keep_on<TYPE>::~___keep_on()
//{
//   if (m_bKept)
//   {
//      KeepAway();
//   }
//}

//#pragma once


//inline var & thread_value(const ::id & id);
//inline void thread_set(const ::id & id) { thread_value(id) = true; }
//inline void thread_unset(const ::id & id) { thread_value(id) = false; }
//inline bool thread_is_set(const ::id & id);


//template  < typename TYPE >
//inline TYPE default_keep_value()
//{
//
//   return (TYPE) nullptr;
//
//}


//template  < >
//inline bool default_keep_value < bool >()
//{
//
//   return true;
//
//}

//template  < >
//inline ::thread * default_keep_value < ::thread * >()
//{
//
//   return ::get_task();
//
//}

//
//template < typename TYPE >
//class ___keep
//{
//public:
//
//
//   TYPE    m_keepValue;
//   TYPE    m_keepAwayValue;
//   TYPE* m_pKept;
//   bool    m_bKept;
//
//
//   ___keep(___keep&& keep);
//
//   template < typename TYPE_KEEP, typename TYPE_KEEP_AWAY >
//   ___keep(TYPE& kept, const TYPE_KEEP& keepValue, const TYPE_KEEP_AWAY& keepAwayValue, bool bStartKept = true);
//
//   template < typename TYPE_KEEP >
//   ___keep(TYPE& kept, const TYPE_KEEP& keepValue = ::default_keep_value < TYPE >());
//
//   virtual ~___keep();
//
//   void Keep();
//   void KeepAway();
//
//
//};


//template < typename TYPE >
//class ___keep_pointer
//{
//public:
//
//
//   TYPE *            m_keepValue;
//   TYPE *            m_keepAwayValue;
//   __pointer(TYPE) * m_pKept;
//   bool              m_bKept;
//
//
//   template < typename TYPE_KEEP, typename TYPE_KEEP_AWAY >
//   ___keep_pointer(__pointer(TYPE)* pKept, TYPE_KEEP * keepValue, TYPE_KEEP_AWAY * keepAwayValue, bool bStartKept = true);
//
//   template < typename TYPE_KEEP >
//   ___keep_pointer(__pointer(TYPE)* pKept, TYPE_KEEP * keepValue = ::default_keep_value < TYPE * >());
//
//   ___keep_pointer(___keep_pointer&& keep);
//
//   virtual ~___keep_pointer();
//
//   void Keep();
//   void KeepAway();
//
//
//};
//
//

//template < typename TYPE >
//template < typename TYPE_KEEP, typename TYPE_KEEP_AWAY >
//___keep < TYPE > ::___keep(TYPE & kept, const TYPE_KEEP & keepValue, const TYPE_KEEP_AWAY & keepAwayValue, bool bStartKept) :
//   m_keepValue(keepValue),
//   m_keepAwayValue(keepAwayValue),
//   m_pKept(&kept)
//{
//   if (bStartKept)
//   {
//      m_bKept = false;
//      Keep();
//   }
//   else
//   {
//      m_bKept = true;
//      KeepAway();
//   }
//
//}
//
//template < typename TYPE >
//template < typename TYPE_KEEP >
//___keep < TYPE > ::___keep(TYPE & kept, const TYPE_KEEP & keepValue) :
//   m_keepValue(keepValue),
//   m_keepAwayValue(kept),
//   m_pKept(&kept)
//{
//   m_bKept = false;
//   Keep();
//}
//
//
//template < typename TYPE >
//___keep < TYPE > ::___keep(___keep && keep) :
//   m_keepValue(keep.m_keepValue),
//   m_keepAwayValue(keep.m_keepAwayValue),
//   m_pKept(keep.m_pKept),
//   m_bKept(keep.m_bKept)
//{
//   keep.m_pKept = nullptr;
//}
//
//
//template < typename TYPE >
//___keep<TYPE>::~___keep()
//{
//   if (m_bKept)
//   {
//      KeepAway();
//   }
//}
//
//template < typename TYPE >
//void ___keep<TYPE>::Keep()
//{
//   if (m_pKept)
//   {
//      *m_pKept = m_keepValue;
//      m_bKept = true;
//   }
//}
//
//template <class TYPE>
//void ___keep<TYPE>::KeepAway()
//{
//   if (m_pKept)
//   {
//      *m_pKept = m_keepAwayValue;
//      m_bKept = false;
//   }
//}

//template < typename TYPE >
//template < typename TYPE_KEEP, typename TYPE_KEEP_AWAY >
//___keep_pointer < TYPE > ::___keep_pointer(__pointer(TYPE)* pKept, TYPE_KEEP * keepValue, TYPE_KEEP_AWAY * keepAwayValue, bool bStartKept) :
//   m_keepValue(keepValue),
//   m_keepAwayValue(keepAwayValue),
//   m_pKept(pKept)
//{
//   if (bStartKept)
//   {
//      m_bKept = false;
//      Keep();
//   }
//   else
//   {
//      m_bKept = true;
//      KeepAway();
//   }
//
//}
//
//template < typename TYPE >
//template < typename TYPE_KEEP >
//___keep_pointer < TYPE > ::___keep_pointer(__pointer(TYPE)* pKept, TYPE_KEEP * keepValue) :
//   m_keepValue(keepValue),
//   m_keepAwayValue(*pKept),
//   m_pKept(pKept)
//{
//   m_bKept = false;
//   Keep();
//}
//
//
//template < typename TYPE >
//___keep_pointer < TYPE > ::___keep_pointer(___keep_pointer&& keep) :
//   m_keepValue(keep.m_keepValue),
//   m_keepAwayValue(keep.m_keepAwayValue),
//   m_pKept(keep.m_pKept),
//   m_bKept(keep.m_bKept)
//{
//   keep.m_pKept = nullptr;
//}
//
//
//template < typename TYPE >
//___keep_pointer<TYPE>::~___keep_pointer()
//{
//   if (m_bKept)
//   {
//      KeepAway();
//   }
//}
//
//template < typename TYPE >
//void ___keep_pointer<TYPE>::Keep()
//{
//   if (m_pKept)
//   {
//      *m_pKept = m_keepValue;
//      m_bKept = true;
//   }
//}
//
//template <class TYPE>
//void ___keep_pointer<TYPE>::KeepAway()
//{
//   if (m_pKept)
//   {
//      *m_pKept = m_keepAwayValue;
//      m_bKept = false;
//   }
//}
//

//template < typename TYPE >
//___keep < TYPE > keep(TYPE * pKept)
//{
//
//   return ___keep < TYPE >(pKept, ::default_keep_value < TYPE >());
//
//}


//template < typename TYPE, typename TYPE_KEEP >
//___keep < TYPE > keep(TYPE * pKept, TYPE_KEEP * keepValue)
//{
//
//   return ___keep < TYPE >(pKept, keepValue);
//
//}


//template < typename TYPE, typename TYPE_KEEP, typename TYPE_KEEP_AWAY >
//___keep < TYPE > keep(TYPE * pKept, TYPE_KEEP * keepValue, TYPE_KEEP_AWAY * keepAwayValue,  bool bStartKept = true)
//{
//
//   return ___keep < TYPE >(pKept, keepValue, keepAwayValue, bStartKept);
//
//}
//

//template < typename TYPE >
//___keep < TYPE > keep(TYPE & kept)
//{
//
//   return ___keep < TYPE >(kept, ::default_keep_value < TYPE >());
//
//}

//template < typename TYPE, typename TYPE_KEEP >
//___keep_pointer < TYPE > keep(__pointer(TYPE)* pKept, TYPE_KEEP * keepValue)
//{
//
//   return ___keep_pointer < TYPE >(pKept, keepValue);
//
//}


//template < typename TYPE >
//___keep_pointer < TYPE > keep(__pointer(TYPE)& kept)
//{
//
//   return ___keep_pointer < TYPE >(&kept, ::default_keep_value < TYPE >());
//
//}


//template < typename TYPE, typename TYPE_KEEP >
//___keep < TYPE > keep(TYPE & kept, const TYPE_KEEP & keepValue)
//{
//
//   return ___keep < TYPE >(kept, keepValue);
//
//}


//template < typename TYPE, typename TYPE_KEEP, typename TYPE_KEEP_AWAY >
//___keep < TYPE > keep(TYPE & kept, const TYPE_KEEP & keepValue, const TYPE_KEEP_AWAY & keepAwayValue, bool bStartKept = true)
//{
//
//   return ___keep < TYPE >(kept, keepValue, keepAwayValue, bStartKept);
//
//}
/// _<3tbs special singular macro start with underscore and all lower case

//#define __keep(...) auto TOKEN_AT_LINE(__keep) = keep(__VA_ARGS__)
//#define __keep_true(...) auto TOKEN_AT_LINE(__keep_true) = keep(__VA_ARGS__, true)
//#define __keep_false(...) auto TOKEN_AT_LINE(__keep_false) = keep(__VA_ARGS__, false)
#define __keep_thread_flag(...) auto TOKEN_AT_LINE(__keep_thread_flag) = keep_thread_flag(__VA_ARGS__)
#define __keep_current_thread(...) auto TOKEN_AT_LINE(__keep_current_thread) = keep(__VA_ARGS__, ::get_task())


#define __task_guard_ret(flag, ret) \
 \
sync_lock sl(mutex()); \
 \
if (flag) \
{ \
\
   ret; \
\
} \
\
auto TOKEN_AT_LINE(__task_guard_task_ret) = keep(flag); \
\
sl.unlock()

#define __task_guard(flag) __task_guard_ret(flag, return)


#define __guard_wait_ret(flag, ret) \
 \
sync_lock sl(mutex()); \
 \
while (flag) \
{ \
\
   \
   sl.unlock(); \
   \
   if (!thread_sleep(100)) \
   {\
   \
      ret; \
   \
   } \
   \
   sl.lock(); \
   \
   \
} \
\
auto TOKEN_AT_LINE(__guard_wait_ret) = keep(&flag); \
\
sl.unlock()

#define __guard_wait(flag) __task_guard_ret(flag, return)



//template <class TYPE>
//class ___keep_on
//{
//public:
//
//
//   TYPE     m_keepValue;
//   bool     m_bWasSet;
//   TYPE* m_pKept;
//   bool     m_bKept;
//
//   template < typename TYPE_KEEP>
//   ___keep_on(TYPE* pKept, TYPE_KEEP keep, bool bStartKept = true);
//   ___keep_on(___keep_on&& on) :
//      m_keepValue(on.m_keepValue),
//      m_bWasSet(on.m_bWasSet),
//      m_pKept(on.m_pKept),
//      m_bKept(on.m_bKept)
//   {
//      on.m_pKept = nullptr;
//   }
//   virtual ~___keep_on();
//
//   void Keep();
//   void KeepAway();
//
//
//};
//
//
//
//template < typename TYPE >
//template < typename TYPE_KEEP >
//___keep_on<TYPE>::___keep_on(TYPE * pKept, TYPE_KEEP keepValue, bool bStartKept) :
//   m_keepValue(keepValue),
//   m_pKept(pKept)
//{
//   if (bStartKept)
//   {
//      m_bKept = false;
//      Keep();
//   }
//   else
//   {
//      m_bKept = true;
//      KeepAway();
//   }
//
//}
//template <class TYPE>
//___keep_on<TYPE>::~___keep_on()
//{
//   if (m_bKept)
//   {
//      KeepAway();
//   }
//}
//
//template <class TYPE>
//void ___keep_on<TYPE>::Keep()
//{
//   if (m_pKept)
//   {
//      *m_pKept |= m_keepValue;
//      m_bKept = true;
//   }
//}
//
//template <class TYPE>
//void ___keep_on<TYPE>::KeepAway()
//{
//   if (m_pKept && !m_bWasSet)
//   {
//      *m_pKept &= ~m_keepValue;
//      m_bKept = false;
//   }
//}
//
//
//template < typename TYPE, typename TYPE_KEEP >
//___keep_on < TYPE > keep_on(TYPE & kept, TYPE_KEEP keepValue, bool bStartKept = true)
//{
//
//   return ___keep_on < TYPE >(&kept, keepValue, bStartKept);
//
//}
//
//
//template < typename TYPE, typename TYPE_KEEP >
//___keep_on < TYPE > keep_on(TYPE * pKept, TYPE_KEEP keepValue, bool bStartKept = true)
//{
//
//   return ___keep_on < TYPE >(pKept, keepValue, bStartKept);
//
//}
//
///// special singular macro start with two underscores and all lower case
//
//#define __keep_on(...) auto TOKEN_AT_LINE(__keep_on) = keep_on(__VA_ARGS__)
//

//
//class CLASS_DECL_APEX ___keep_thread_flag
//{
//public:
//
//
//   bool m_bChanged;
//
//
//   ::var &      m_varThread;
//
//
//   ___keep_thread_flag(const ::id & id) :
//      m_varThread(thread_value(id))
//   {
//
//      if ((bool) m_varThread)
//      {
//
//         m_bChanged = false;
//
//      }
//      else
//      {
//
//         m_varThread = true;
//
//         m_bChanged = true;
//
//      }
//
//   }
//
//
//   ~___keep_thread_flag()
//   {
//
//      if (m_bChanged)
//      {
//
//         m_varThread = false;
//
//      }
//
//   }
//
//
//};
//
//
//
//inline ___keep_thread_flag keep_thread_flag(const ::id & id)
//{
//
//   return id;
//
//}

//#define __keep(...) auto TOKEN_AT_LINE(__keep_thread_flag) = keep_thread_flag(__VA_ARGS__)



//template < typename FLAG >
//class ___keep_flag_on
//{
//public:
//
//
//   cflag < FLAG >& m_eflagVariable;
//   cflag < FLAG >          m_eflag;
//
//
//   ___keep_flag_on(cflag < FLAG >& eflagVariable, i64 iFlag) :
//      m_eflagVariable(eflagVariable),
//      m_eflag(iFlag)
//   {
//
//      m_eflagVariable |= m_eflag;
//
//   }
//
//   ___keep_flag_on(const ___keep_flag_on& on) :
//      m_eflagVariable(on.m_eflagVariable),
//      m_eflag(on.m_eflag)
//   {
//
//   }
//
//
//   ~___keep_flag_on()
//   {
//
//      m_eflagVariable -= m_eflag;
//
//   }
//
//
//};
//
//template < typename FLAG >
//inline ___keep_flag_on < FLAG > keep_flag_on(cflag < FLAG > & eflagVariable, i64 iFlag)
//{
//
//   return ___keep_flag_on < FLAG >(eflagVariable, iFlag);
//
//}
//
//
//#define __keep_flag_on(...) auto TOKEN_AT_LINE(__keep_flag_on) = keep_flag_on(__VA_ARGS__)


//template <class TYPE>
//void ___keep_on<TYPE>::KeepAway()
//{
//   if (m_pKept && !m_bWasSet)
//   {
//      *m_pKept &= ~m_keepValue;
//      m_bKept = false;
//   }
//}
//
//
//template < typename TYPE, typename TYPE_KEEP >
//___keep_on < TYPE > keep_on(TYPE & kept, TYPE_KEEP keepValue, bool bStartKept = true)
//{
//
//   return ___keep_on < TYPE >(&kept, keepValue, bStartKept);
//
//}


//template < typename TYPE, typename TYPE_KEEP >
//___keep_on < TYPE > keep_on(TYPE * pKept, TYPE_KEEP keepValue, bool bStartKept = true)
//{
//
//   return ___keep_on < TYPE >(pKept, keepValue, bStartKept);
//
//}
//
///// special singular macro start with two underscores and all lower case
//
//#define __keep_on(...) auto TOKEN_AT_LINE(__keep_on) = keep_on(__VA_ARGS__)
//


class CLASS_DECL_APEX ___keep_thread_flag
{
public:


   bool m_bChanged;


   ::var &      m_varThread;


   ___keep_thread_flag(const ::id & id) :
      m_varThread(thread_value(id))
   {

      if ((bool) m_varThread)
      {

         m_bChanged = false;

      }
      else
      {

         m_varThread = true;

         m_bChanged = true;

      }

   }


   ~___keep_thread_flag()
   {

      if (m_bChanged)
      {

         m_varThread = false;

      }

   }


};



inline ___keep_thread_flag keep_thread_flag(const ::id & id)
{

   return id;

}

//#define __keep(...) auto TOKEN_AT_LINE(__keep_thread_flag) = keep_thread_flag(__VA_ARGS__)


//
//template < typename FLAG >
//class ___keep_flag_on
//{
//public:
//
//
//   cflag < FLAG > &        m_eflagVariable;
//   cflag < FLAG >          m_eflag;
//
//
//   ___keep_flag_on(cflag < FLAG > & eflagVariable, i64 iFlag) :
//      m_eflagVariable(eflagVariable),
//      m_eflag(iFlag)
//   {
//
//      m_eflagVariable |= m_eflag;
//
//   }
//
//   ___keep_flag_on(const ___keep_flag_on & on) :
//      m_eflagVariable(on.m_eflagVariable),
//      m_eflag(on.m_eflag)
//   {
//
//   }
//
//
//   ~___keep_flag_on()
//   {
//
//      m_eflagVariable -= m_eflag;
//
//   }
//
//
//};
//
//template < typename FLAG >
//inline ___keep_flag_on < FLAG > keep_flag_on(cflag < FLAG > & eflagVariable, i64 iFlag)
//{
//
//   return ___keep_flag_on < FLAG >(eflagVariable, iFlag);
//
//}
//
//
//#define __keep_flag_on(...) auto TOKEN_AT_LINE(__keep_flag_on) = keep_flag_on(__VA_ARGS__)
