#pragma once


#include "acme/parallelization/task.h"
#include "synchronization_array.h"
#include "synchronous_lock.h"
////#include "acme/exception/exception.h"
#include "acme/platform/system.h"


class task_tool;

// item of *task_tool* associated with each *tool_task*
// of a *task_group*
class task_tool_item;


// group of *tool_task*(s) that work together
// to perform a *task_tool* operation/task
class task_group;

// a group of *tool_task*s on a *task_group*(s)
// acts on single *task_tool_item* of a *task_tool*
// to perform a operation/task.
class CLASS_DECL_ACME tool_task :
   virtual public ::task
{
public:


   ::raw::index                            m_iThread;
   task_group *                     m_pgroup;
   task_tool *                      m_ptool;
   task_tool_item *                 m_pitem;
   ::pointer<manual_reset_event>    m_pevStart;
   ::pointer<manual_reset_event>    m_pevReady;
   void *                           m_pdata;
   ::raw::index                            m_cCount;
   ::raw::index                            m_iIndex;
   ::raw::count                          m_iScan;
   ::raw::count                          m_iCount;
   ::procedure                      m_procedure;
   ::pointer<matter>                m_pholdref;


   tool_task();


   virtual void initialize_tool_task(::task_group* pgroup);


   virtual void run() override;


   bool set_procedure(const ::procedure & procedure);

   void reset();
   void set_ready_to_start();


};


class CLASS_DECL_ACME task_tool_item :
   virtual public ::matter
{
public:


   task_tool *        m_ptool;
   tool_task *        m_ptask;


   task_tool_item();
   virtual ~task_tool_item();


   virtual void     run() override;


};


class CLASS_DECL_ACME task_tool :
   virtual public ::matter
{
public:


   enum_task_tool     m_etasktool;
   task_group *       m_ptaskgroup;


   HAVE_ARRAY_OF(item, m_itema, task_tool_item);

   task_tool();
   ~task_tool() override;

};


class CLASS_DECL_ACME task_group :
   virtual public ::matter
{
public:


   HAVE_ARRAY_OF(task, m_taska, tool_task);

   synchronization_array                             m_synchronizationa;
   ::raw::count                                m_cCount;
   ::raw::count                                m_cIteration;
   ::raw::count                                m_cSpan;
   ::enum_task_op                       m_etaskop;
   ::pointer<::task_tool>              m_ptool;
   ::enum_priority                           m_epriority;


   task_group(::matter * pmatter, ::enum_priority epriority);
   ~task_group() override;




   ::raw::count get_count() const { return m_taska.get_count(); }
   bool is_empty() const { return get_count() <= 0; }
   bool is_full() const { return m_cCount >= m_taska.get_count(); }
   bool fillable() const { return !is_full(); }
   ::raw::count get_span() const { return m_cSpan; }
   bool nok() const { return is_empty(); };

   void prepare(::enum_task_op eop, ::raw::count cIteration = 0);
   virtual void set_ready_to_start();
   ::e_status wait() override;
   virtual void process();

   bool add_procedure(const ::procedure & procedure);


   void select_tool(task_tool* ptool);

   template < typename PRED >
   inline ::raw::count fork_count_end(::property_object* pparticle, ::raw::count iCount, PRED pred, ::raw::index iStart)
   {

      if (iCount <= 0)
      {

         return -1;

      }

      //auto psystem = ::apexacmesystem();

      synchronous_lock slGroup(system()->synchronization());

      ///   auto ptool = ::apexacmesystem()->task_tool(op_fork_count);

      if (get_count() <= 1)
      {

         for (::raw::index i = iStart; i < iCount; i++)
         {

            pred(i);

         }

         return 1;

      }

      prepare(::e_task_op_fork_count, iCount - iStart);
//      {
//
//         return -1;
//
//      }

      synchronization_array ptra;

      ::raw::count iScan = maximum(1, minimum(iCount - iStart, task_count()));

      for (::raw::index iOrder = 0; iOrder < iScan; iOrder++)
      {

         throw ::exception(todo);

//         ::pointer<predicate_holder_base>pusermessage = __allocate< forking_count_predicate < PRED > >(pparticle, iOrder, iOrder + iStart, iScan, iCount, pred);
//
//         if (!add_predicate(pusermessage))
//         {
//
//            return -1;
//
//         }

      }

      call_run();
//      {
//
//         return -1;
//
//      }

      return iScan;

   }


};





template < typename PRED >
inline ::raw::count fork_count_end(::particle * pparticle, ::raw::count iCount, PRED pred, ::raw::index iStart = 0, ::enum_priority epriority = ::e_priority_none);




//::raw::count task_toolset::get_span() const
//{
//   return m_ptasktools->get_span();
//}

//bool task_toolset::operator()()
//{
//   return m_ptasktools->operator()();
//
//}



using task_group_map = map < enum_priority, pointer_array < ::task_group > >;
using task_tool_map = map < enum_task_tool, pointer_array < ::task_tool > >;




