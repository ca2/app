#pragma once


class thread_tool;

// item of *thread_tool* associated with each *tool_thread*
// of a *thread_group*
class thread_tool_item;


// group of *tool_thread*(s) that work together
// to perform a *thread_tool* operation/task
class thread_group;

// a group of *tool_thread*s on a *thread_group*(s)
// acts on single *thread_tool_item* of a *thread_tool*
// to perform a operation/task.
class CLASS_DECL_AURA tool_thread :
   virtual public ::thread
{
public:


   index                            m_iThread;
   thread_group *                   m_pgroup;
   thread_tool *                    m_ptool;
   thread_tool_item *               m_pitem;
   __pointer(manual_reset_event)    m_pevStart;
   __pointer(manual_reset_event)    m_pevReady;
   void *                           m_pdata;
   index                            m_cCount;
   index                            m_iIndex;
   ::count                          m_iScan;
   ::count                          m_iCount;
   __pointer(::pred_holder_base)    m_ppred;
   __pointer(object)                m_pholdref;


   tool_thread();


   virtual ::estatus initialize_tool_thread(::thread_group* pgroup);


   virtual ::estatus     run() override;


   bool set_pred(::pred_holder_base * ppred);

   void reset();
   void start() override;

};


class CLASS_DECL_AURA thread_tool_item :
   virtual public ::object
{
public:


   thread_tool *        m_ptool;
   tool_thread *        m_pthread;


   thread_tool_item();
   virtual ~thread_tool_item();


   virtual ::estatus     run() override;


};


class CLASS_DECL_AURA thread_tool :
   virtual public ::object
{
public:


   enum_thread_tool     m_ethreadtool;
   thread_group *       m_pthreadgroup;


   HAVE_ARRAY_OF(item, m_itema, thread_tool_item);

   thread_tool();
   virtual ~thread_tool();

};


class CLASS_DECL_AURA thread_group :
   virtual public ::object
{
public:


   HAVE_ARRAY_OF(thread, m_threada, tool_thread);

   sync_array                             m_synca;
   ::count                                m_cCount;
   ::count                                m_cIteration;
   ::count                                m_cSpan;
   ::enum_thread_op                       m_ethreadop;
   __pointer(::thread_tool)               m_ptool;
   ::e_priority                           m_epriority;


   thread_group(::object * pobject, ::e_priority epriority);
   virtual ~thread_group();




   ::count get_count() const { return m_threada.get_count(); }
   bool is_empty() const { return get_count() <= 0; }
   bool is_full() const { return m_cCount >= m_threada.get_count(); }
   bool fillable() const { return !is_full(); }
   ::count get_span() const { return m_cSpan; }
   bool nok() const { return is_empty(); };

   bool prepare(::enum_thread_op eop, ::count cIteration = 0);
   bool start();
   bool wait();
   bool operator()();

   bool add_pred(::pred_holder_base * ppred);


   void select_tool(thread_tool* ptool);



};





template < typename PRED >
inline ::count fork_count_end(::object* pobject, ::count iCount, PRED pred, index iStart = 0, ::e_priority epriority = ::priority_none);




//::count thread_toolset::get_span() const
//{
//   return m_pthreadtools->get_span();
//}

//bool thread_toolset::operator()()
//{
//   return m_pthreadtools->operator()();
//
//}



using thread_group_map = isomap < e_priority, __pointer_array(::thread_group) >;
using thread_tool_map = isomap < enum_thread_tool, __pointer_array(::thread_tool) >;




