#pragma once


//template < typename PRED >
//class λfuture :
//   virtual public ::matter
//{
//public:
//
//
//   PRED     m_pred;
//
//
//   λfuture(PRED pred) :
//      m_pred(pred)
//   {
//
//   }
//
//
//   virtual ~λfuture()
//   {
//
//
//   }
//
//
//   virtual ::estatus run() override
//   {
//
//      ＿＿throw(interface_only_exception());
//
//      return ::error_interface_only;
//
//   }
//
//
//   void receive_response(const ::var& var) override
//   {
//
//      m_pred(var);
//
//   }
//
//
//};
//


template < typename PRED, typename FUTURE >
class λfuture :
   virtual public matter
{
public:

   PRED m_pred;
   //future() {}

   //future(const ::future& future) : function((const ::function &) future) { }
   //future(::future * pfuture) : function((const ::function &) *pfuture) { }
   λfuture(PRED pred) : m_pred(pred) { }


   virtual void operator()(const FUTURE & var)  override

   //virtual void send(const var& var)
   {

      m_pred(var);

   }


   //template < typename PRED >
   //void pred(PRED pred);


   //inline future& operator = (const ::future& future) { m_pmatter = future.m_pmatter; return *this; }
   //future& operator = (const ::var& var);

};



template < typename PRED, typename FUTURE >
::future < FUTURE > ＿＿future(PRED pred)
{

   return ＿＿new(λfuture<PRED, FUTURE>(pred));

}


template < typename PRED >
::futurevar ＿＿futurevar(PRED pred)
{

    return ＿＿new(λfuture<PRED, var>(pred));

}




