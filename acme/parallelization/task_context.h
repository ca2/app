// Deeply refactored by camilo on 2024-10-07 07:24 <3ThomasBorregaardSorensen!!
// More deep refactoring merging post_procedure_continuation by
//   camilo on 2024-10-09 11:31 <3ThomasBorregaardSorensen!!
// post_procedure_continuation
//  camilo on 2024-10-08 08:45 <3ThomasBorregaardSorensen!!
#pragma once


class task_context_base;


inline static thread_local ::pointer <task_context_base> t_ptaskcontextbaseRoot;

class CLASS_DECL_ACME task_context_base :
   virtual public ::particle
{
public:

   ::pointer <task_context_base> m_pParent;

   
   static task_context_base * current() { return t_ptaskcontextbaseRoot; }
   void push()
   {

      auto pNewParent = t_ptaskcontextbaseRoot;

      t_ptaskcontextbaseRoot = this;

      t_ptaskcontextbaseRoot->m_pParent = pNewParent;

   }


   void pop()
   {

      auto pParent = t_ptaskcontextbaseRoot->m_pParent;

      t_ptaskcontextbaseRoot = pParent;

   }

};

class stack_task_context_base
{
public:
   task_context_base * m_p;

   stack_task_context_base(task_context_base * p) :
      m_p(p)
   {
      m_p->push();

   }

   ~stack_task_context_base()
   {

      m_p->pop();

      m_p = nullptr;
   }

};


template < typename CONTEXT_TYPE >
class task_context :
   virtual public ::task_context_base
{
public:

   task_context()
   {

   }
   ~task_context() override
   {

   }

};



