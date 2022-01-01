#pragma once


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


   index                            m_iThread;
   task_group *                   m_pgroup;
   task_tool *                    m_ptool;
   task_tool_item *               m_pitem;
   __pointer(manual_reset_event)    m_pevStart;
   __pointer(manual_reset_event)    m_pevReady;
   void *                           m_pdata;
   index                            m_cCount;
   index                            m_iIndex;
   ::count                          m_iScan;
   ::count                          m_iCount;
   __pointer(::predicate_holder_base)    m_ppred;
   __pointer(matter)                m_pholdref;


   tool_task();


   virtual ::e_status initialize_tool_task(::task_group* pgroup);


   virtual ::e_status run() override;


   bool set_predicate(::predicate_holder_base * ppred);

   void reset();
   ::e_status set_ready_to_start();


};


class CLASS_DECL_ACME task_tool_item :
   virtual public ::matter
{
public:


   task_tool *        m_ptool;
   tool_task *        m_ptask;


   task_tool_item();
   virtual ~task_tool_item();


   virtual ::e_status     run() override;


};


class CLASS_DECL_ACME task_tool :
   virtual public ::material_object
{
public:


   enum_task_tool     m_etasktool;
   task_group *       m_ptaskgroup;


   HAVE_ARRAY_OF(item, m_itema, task_tool_item);

   task_tool();
   virtual ~task_tool();

};


class CLASS_DECL_ACME task_group :
   virtual public ::matter
{
public:


   HAVE_ARRAY_OF(task, m_taska, tool_task);

   synchronization_array                             m_synchronizationa;
   ::count                                m_cCount;
   ::count                                m_cIteration;
   ::count                                m_cSpan;
   ::enum_task_op                       m_etaskop;
   __pointer(::task_tool)               m_ptool;
   ::enum_priority                           m_epriority;


   task_group(::matter * pmatter, ::enum_priority epriority);
   virtual ~task_group();




   ::count get_count() const { return m_taska.get_count(); }
   bool is_empty() const { return get_count() <= 0; }
   bool is_full() const { return m_cCount >= m_taska.get_count(); }
   bool fillable() const { return !is_full(); }
   ::count get_span() const { return m_cSpan; }
   bool nok() const { return is_empty(); };

   ::e_status prepare(::enum_task_op eop, ::count cIteration = 0);
   virtual ::e_status set_ready_to_start();
   ::e_status wait() override;
   virtual ::e_status process();

   bool add_predicate(::predicate_holder_base * ppred);


   void select_tool(task_tool* ptool);

   template < typename PRED >
   inline ::count fork_count_end(::property_object* pobject, ::count iCount, PRED pred, index iStart)
   {

      if (iCount <= 0)
      {

         return -1;

      }

      //auto psystem = ::apex::get_system();

      synchronous_lock slGroup(m_psystem->mutex());

      ///   auto ptool = ::apex::get_system()->task_tool(op_fork_count);

      if (get_count() <= 1)
      {

         for (index i = iStart; i < iCount; i++)
         {

            pred(i);

         }

         return 1;

      }

      if (!prepare(::e_task_op_fork_count, iCount - iStart))
      {

         return -1;

      }

      synchronization_array ptra;

      ::count iScan = maximum(1, minimum(iCount - iStart, task_count()));

      for (index iOrder = 0; iOrder < iScan; iOrder++)
      {

         __pointer(predicate_holder_base) pusermessage = __new(forking_count_predicate < PRED >(pobject, iOrder, iOrder + iStart, iScan, iCount, pred));

         if (!add_predicate(pusermessage))
         {

            return -1;

         }

      }

      if (!this->operator()())
      {

         return -1;

      }

      return iScan;

   }


};





template < typename PRED >
inline ::count fork_count_end(::matter* pobject, ::count iCount, PRED pred, index iStart = 0, ::enum_priority epriority = ::e_priority_none);




//::count task_toolset::get_span() const
//{
//   return m_ptasktools->get_span();
//}

//bool task_toolset::operator()()
//{
//   return m_ptasktools->operator()();
//
//}



using task_group_map = map < enum_priority, __pointer_array(::task_group) >;
using task_tool_map = map < enum_task_tool, __pointer_array(::task_tool) >;




