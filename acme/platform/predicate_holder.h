#pragma once


//class CLASS_DECL_ACME predicate_holder_base :
//   virtual public matter
//{
//public:
//
//
//   ::tool_task *         m_ptooltask;
//
//
//   predicate_holder_base()
//   {
//
//      m_ptooltask = nullptr;
//
//   }
//
//
//   virtual void run() {}
//
//
//};
//
//
//template < typename PRED >
//class predicate_holder :
//   virtual public predicate_holder_base
//{
//public:
//
//
//   PRED m_predicate;
//
//
//   predicate_holder(PRED pred) :
//      m_predicate(pred)
//   {
//
//   }
//
//
//   virtual void run() override
//   {
//
//      m_predicate();
//
//      //return ::success;
//
//   }
//
//
//};
//
//
//
//class CLASS_DECL_ACME predicate_array :
//   virtual public array < ::pointer<predicate_holder_base >>
//{
//public:
//
//
//   predicate_array();
//   ~predicate_array() override;
//
//
//   template < typename PRED >
//   void predicate_add(PRED pred)
//   {
//
//      add(__allocate predicate_holder < PRED > (pred));
//
//   }
//
//   void run_all();
//
//};
//
//
