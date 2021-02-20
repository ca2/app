#pragma once


typedef u32 THREAD_PROC(void * p);

typedef THREAD_PROC * thread_proc;

//
//// very close to the operating system
//CLASS_DECL_APEX hthread_t create_thread(
//thread_proc proc,
//void * p,
//::e_priority epriority = ::priority_normal,
//::u32 nStackSize = 0,
//u32 uiCreateFlags = 0,
//LPSECURITY_ATTRIBUTES psa = nullptr,
//
//ithread_t * puiId = nullptr);
//
//




//CLASS_DECL_APEX ithread_t get_current_ithread();

//CLASS_DECL_APEX hthread_t get_current_hthread();





CLASS_DECL_APEX bool on_init_thread();
CLASS_DECL_APEX bool on_term_thread();


CLASS_DECL_APEX void __init_thread();
CLASS_DECL_APEX void __term_thread();


CLASS_DECL_APEX bool __os_init_thread();
CLASS_DECL_APEX bool __os_term_thread();


CLASS_DECL_APEX bool __node_init_thread(::thread * pthread);
CLASS_DECL_APEX bool __node_term_thread(::thread * pthread);


CLASS_DECL_APEX void __init_threading_count();
CLASS_DECL_APEX void __term_threading_count();


CLASS_DECL_APEX void __inc_threading_count();
CLASS_DECL_APEX void __dec_threading_count();




#define __prevent_bad_status_exception __keep_thread_flag(id_thread_prevent_bad_status_exception)

//CLASS_DECL_APEX enumeration < e_thread_flag > & thread_flags();
//CLASS_DECL_APEX void thread_set_flag(const enumeration < e_thread_flag > & eflag, bool bSet = true);
//CLASS_DECL_APEX void thread_set_fast_path(bool bFastPath = true);
//CLASS_DECL_APEX bool thread_is_fast_path();
//CLASS_DECL_APEX void thread_set_zip_is_dir(bool bZipIsDir = true);
//CLASS_DECL_APEX bool thread_set(id_thread_zip_is_dir);
//CLASS_DECL_APEX void thread_set_is_timer(bool bIsTimer = true);
//CLASS_DECL_APEX bool thread_is_timer();
//CLASS_DECL_APEX void thread_set_resolve_alias(bool bResolveAlias = true);
//CLASS_DECL_APEX bool thread_resolve_alias();


//CLASS_DECL_APEX bool __wait_threading_count(::duration dur);
//CLASS_DECL_APEX bool __wait_threading_count_except(::thread * pthread,::duration dur);


//CLASS_DECL_APEX ::thread * get_task();
//CLASS_DECL_APEX void set_thread(thread * pthread);
//CLASS_DECL_APEX void thread_release();


//CLASS_DECL_APEX bool thread_get_run();


CLASS_DECL_APEX void __node_init_multithreading();
CLASS_DECL_APEX void __node_term_multithreading();


//thread_local __pointer(property_set) t_ppropertyset;




namespace parallelization
{


   CLASS_DECL_APEX void init_multithreading();
   CLASS_DECL_APEX void term_multithreading();

   //CLASS_DECL_APEX bool thread_registered(::thread * pthread);
   //CLASS_DECL_APEX bool thread_id_registered(ithread_t id);

   //CLASS_DECL_APEX void thread_register(ithread_t ithread, ::thread * pthread);

   //CLASS_DECL_APEX void thread_unregister(ithread_t ithread, ::thread * pthread);

   CLASS_DECL_APEX bool is_child(::task * ptask);

   CLASS_DECL_APEX void post_quit_to_all_threads();

   CLASS_DECL_APEX void post_to_all_threads(const ::id & id, wparam wparam, lparam lparam);

   //CLASS_DECL_APEX bool wait_threads(::duration duration, __pointer_array(::thread) threadaExcept = __pointer_array(::thread)());

   CLASS_DECL_APEX __pointer(::thread) calc_parent(::thread * pthread);

   //CLASS_DECL_APEX void __node_on_init_thread(thread * pthread);
   //CLASS_DECL_APEX void __node_on_term_thread(thread * pthread);

   //CLASS_DECL_APEX extern comparable_eq_array <ithread_t> * s_piaThread;
   //CLASS_DECL_APEX extern address_array < ::thread * > * s_pthreadptra;
   //CLASS_DECL_APEX extern ::mutex * s_pmutex;


} // namespace parallelization



//CLASS_DECL_APEX void __end_thread(::layered * pobjectContext);

//CLASS_DECL_APEX void __term_thread(::layered * pobjectContext);





//
//#ifdef WINDOWS
//
/////  \brief    global function to wait on a object item for a specified time
/////  \lparam    waitableItem item to wait for (can be event, socket, file, semaphore, ...)
/////  \lparam    duration time period to wait for item (default: infinite)
/////  \return   result of waiting action as defined in synchronization_result
//inline synchronization_result wait(synchronization_object * psync,const duration & duration = duration::infinite())
//{
//   return psync->wait(duration);
//}
//
/////  \brief    global function to wait on a object item for a specified time
/////  \lparam    waitableItem item to wait for (item can be thread, event, socket, file, semaphore, ...)
/////  \lparam    duration time period to wait for item (default: infinite)
/////  \return   result of waiting action as defined in synchronization_result
//synchronization_result wait(i32 numberOfItems, synchronization_object * psync, const duration & duration = duration::infinite(),bool waitForAll = false);
//
//#else
//
/////  \brief    global function to wait on a object item for a specified time
/////  \lparam    waitableItem item to wait for (can be event, socket, file, semaphore, ...)
/////  \lparam    duration time period to wait for item (default: infinite)
/////  \return   result of waiting action as defined in synchronization_result
//synchronization_result wait(synchronization_object * psync,const duration & duration = duration::infinite());
//
/////  \brief    global function to wait on a object item for a specified time
/////  \lparam    waitableItem item to wait for (item can be thread, event, socket, file, semaphore, ...)
/////  \lparam    duration time period to wait for item (default: infinite)
/////  \return   result of waiting action as defined in synchronization_result
//synchronization_result wait(size_t numberOfItems, synchronization_object ** psync, const duration& duration = duration::infinite(),bool waitForAll = false);
//
//#endif




CLASS_DECL_APEX void thread_alloc_ready(bool bReady);









//CLASS_DECL_APEX ::mutex & user_mutex();
//CLASS_DECL_APEX ::mutex & message_dispatch_mutex();




typedef void SIMPLE_ROUTINE(void);
typedef SIMPLE_ROUTINE * PPROC_SIMPLE;

//CLASS_DECL_APEX extern PPROC_SIMPLE g_axisoninitthread;
//CLASS_DECL_APEX extern PPROC_SIMPLE g_axisontermthread;



