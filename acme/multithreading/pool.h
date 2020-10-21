#pragma once


template < typename THREAD_POINTER >
class ___task_pool :
   virtual public ::context_object
{
protected:


   THREAD_POINTER& thread(const ::id& id) { return m_map[id]; }


public:


   id_map < THREAD_POINTER >   m_map;


   ___task_pool();
   virtual ~___task_pool();


   virtual THREAD_POINTER& start(const ::id& id, const matter_pointer& pmatter);


   virtual void start_clock(enum_clock eclock, duration duration);
   virtual void _task_clock(enum_clock eclock, duration duration);
   virtual void on_clock(enum_clock eclock);



};



template < typename THREAD_POINTER >
___task_pool < THREAD_POINTER >::___task_pool()
{

   defer_create_mutex();

}


template < typename THREAD_POINTER >
___task_pool < THREAD_POINTER >::~___task_pool()
{


}


template < typename THREAD_POINTER >
THREAD_POINTER& ___task_pool < THREAD_POINTER >::start(const ::id& id, const matter_pointer& pmatter)
{

   auto& pthread = thread(id);

   auto estatus = __construct(pthread);

   if (!estatus)
   {

      pthread = __create_new < ::task >();

   }

   pthread->_start(pmatter);

   return pthread;

}


//::thread_pointer & thread_pool::thread(const ::id& id)
//{
//
//   auto& pthread = 
//
//   return pthread;
//
//}


template < typename THREAD_POINTER >
void ___task_pool < THREAD_POINTER >::start_clock(enum_clock eclock, duration duration)
{

   //string eclock;

   //switch (eclock)
   //{
   //case clock_none:
   //   throw invalid_argument_exception();
   //   return;
   //case clock_slow:
   //   strName = "clock_slow";
   //   break;
   //case clock_fast:
   //   strName = "clock_fast";
   //   break;
   //default:
   //   throw invalid_argument_exception();
   //   return;

   //}

   start(eclock, __pred_method([&, eclock, duration]()
      {

         _task_clock(eclock, duration);

      }));

}


//template < typename THREAD_POINTER >
//void ___task_pool < THREAD_POINTER >::_task_clock(enum_clock eclock, duration duration)


template < typename THREAD_POINTER >
void ___task_pool < THREAD_POINTER >::on_clock(enum_clock eclock)
{

}



