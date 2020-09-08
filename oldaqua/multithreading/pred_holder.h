#pragma once


class CLASS_DECL_AQUA pred_holder_base :
   virtual public object
{
public:

   
   ::tool_thread *         m_ptoolthread;
   __pointer(object)       m_pholdref;


   pred_holder_base(__pointer(object) pholdref = nullptr) :
      m_pholdref(pholdref)
   {

      m_ptoolthread = nullptr;

   }

   
   virtual ::estatus     run() { return ::success; }


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

   pred_holder(__pointer(object) pholdref, PRED pred) :
      pred_holder_base(pholdref),
      m_pred(pred)
   {

   }

   virtual ::estatus     run() override
   {

      m_pred();

      return ::success;

   }

};




class CLASS_DECL_AQUA pred_array :
   virtual public array < __pointer(pred_holder_base) >
{
public:


   pred_array(::object * pobject);
   virtual ~pred_array();


   template < typename PRED >
   void pred_add(PRED pred)
   {

      add(__new(pred_holder < PRED >(get_context_application(), pred)));

   }

   void run_all();

};


