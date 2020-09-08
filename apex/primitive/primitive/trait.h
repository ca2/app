////
////  promisse.h
////  apex
////
////  Created by Camilo Sasuke Tsumanuma on 02/06/19.
////
//
//
//#pragma once
//
//
//
//
////class create;
////
////namespace papaya
////{
////
////   namespace function
////   {
////
////
////template<typename Ret, typename Arg, typename... Rest>
////Arg first_argument_helper(Ret(*) (Arg, Rest...));
////
////template<typename Ret, typename F, typename Arg, typename... Rest>
////Arg first_argument_helper(Ret(F::*) (Arg, Rest...));
////
////template<typename Ret, typename F, typename Arg, typename... Rest>
////Arg first_argument_helper(Ret(F::*) (Arg, Rest...) const);
////
////template <typename F>
////decltype(first_argument_helper(&F::operator())) first_argument_helper(F);
////
////template <typename T>
////using first_argument = decltype(first_argument_helper(std::declval<T>()));
////
////   } //   namespace function
////
////
////   namespace lambda
////   {
////
////
////template<typename F, typename Ret, typename A, typename... Rest>
////A
////helper(Ret (F::*)(A, Rest...));
////
////template<typename F, typename Ret, typename A, typename... Rest>
////A
////helper(Ret (F::*)(A, Rest...) const);
////
////// volatile or lvalue/rvalue *this not required for lambdas (phew)
//////that accept a pointer to member function taking at least one argument. And now:
////
////template<typename F>
////struct first_argument {
////   typedef decltype( helper(&F::operator()) ) type;
////};
////
////
////   } // namespace lambda
////
////} // namespace papaya
//
//typedef CLASS_DECL_APEX __pointer(::context_object) context_object_pointer;
//
//typedef CLASS_DECL_APEX __pointer_array(::context_object) context_object_pointera;
//
//enum e_notify
//{
//  
//   notify_none,
//   notify_call,
//   notify_fork,
//   notify_fork_each,
//   
//};
//
//
////class CLASS_DECL_APEX trait //:
////   //virtual public context_object
////{
////public:
////   
////   
////   //::object *        m_pobjectHandler;
////   ::i64             m_iTrait;
////   ::estatus         m_estatus;
////   //::u64                                     m_uTrait;
////   //__pointer(::context_object)                    m_preference;
////   //__pointer(::object)               m_pobjectTaskTransport;
////   //__pointer(::object)               m_pobjectTask;
////
////
////   //e_notify                                  m_enotify;
////   //__pointer(::context_object_pointera)      m_pobjectTaskaNotify;
////   trait(::i64 iTrait = 0) : m_iTrait(iTrait){ m_estatus = error_not_ready; }
////   
//////   trait()
//////   {
//////      
//////      construct();
//////      
//////   }
//////   
//////
//////   void construct(::u64 uId = 0, ::u64 uTrait = 0)
//////   {
//////      
//////      m_uId = uId;
//////      m_uTrait = uTrait;
//////      m_enotify = notify_none;
//////      
//////   }
//////
//////   
//////   template < typename PRED >
//////   trait(::u64 uId, PRED pred);
//////
//////   
//////   template < typename PRED >
//////   trait(::u64 uId, ::u64 uTrait, PRED pred);
//////
//////#if _MSC_VER && !__INTEL_COMPILER
//////
//////   template < typename PRED > trait(int iId, PRED pred) : trait((::u64) iId, pred) {}
//////   template < typename PRED > trait(int iId, int iTrait, PRED pred) : trait((::u64) iId, (::u64) iTrait, pred) {}
//////   template < typename PRED > trait(::u64 uId, int iTrait, PRED pred) : trait(uId, (::u64) iTrait, pred) {}
//////   template < typename PRED > trait(int iId, ::u64 uTrait, PRED pred) : trait((::u64) iId, uTrait, pred) {}
//////
//////#endif
//////
//////   template < typename TYPE >
//////   __pointer(TYPE) result()
//////   {
//////      
//////      return m_preference.cast <TYPE>();
//////      
//////   }
//////   
//////   
//////
//////   void set_action(const ::trait & traitPayload);
//////   
//////   void add_notification(const ::trait & traitPayload);
//////   
//////
//////   void fork(::object * pobject);
//////   
//////   ::context_object_pointera * notifya();
//////   
//////
//////   void _notify(::object * pobjectForker);
//////   
//////   
//////   void _call_notify(::object * pobjectForker);
//////   thread_pointer _fork_notify(::object * pobjectForker);
//////   thread_spa _fork_notify_each(::object * pobjectForker);
////   
////   
////};
////
////
////
