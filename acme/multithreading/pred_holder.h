#pragma once


class CLASS_DECL_ACME pred_holder_base :
   virtual public elemental
{
public:

   
   ::tool_thread *         m_ptoolthread;


   pred_holder_base()
   {

      m_ptoolthread = nullptr;

   }

   
   virtual ::estatus run() { return ::success; }


};


template < typename PRED >
class pred_holder :
   virtual public pred_holder_base
{
public:

   
   PRED m_pred;

   
   pred_holder(PRED pred) :
      m_pred(pred)
   {

   }

   
   virtual ::estatus run() override
   {

      m_pred();

      return ::success;

   }


};



class CLASS_DECL_ACME pred_array :
   virtual public array < __pointer(pred_holder_base) >
{
public:


   pred_array();
   virtual ~pred_array();


   template < typename PRED >
   void pred_add(PRED pred)
   {

      add(__new(pred_holder < PRED >(pred)));

   }

   void run_all();

};


