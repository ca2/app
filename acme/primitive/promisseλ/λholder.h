#pragma once


class CLASS_DECL_ACME λholder_base :
   virtual public matter
{
public:

   
   ::tool_thread *         m_ptoolthread;


   λholder_base()
   {

      m_ptoolthread = nullptr;

   }

   
   virtual ::estatus run() { return ::success; }


};


template < typename PRED >
class λholder :
   virtual public λholder_base
{
public:

   
   PRED m_pred;

   
   λholder(PRED pred) :
      m_pred(pred)
   {

   }

   
   virtual ::estatus run() override
   {

      m_pred();

      return ::success;

   }


};



class CLASS_DECL_ACME λarray :
   virtual public array < ＿＿pointer(λholder_base) >
{
public:


   λarray();
   virtual ~λarray();


   template < typename PRED >
   void λadd(PRED pred)
   {

      add(＿＿new(λholder < PRED >(pred)));

   }

   void run_all();

};


