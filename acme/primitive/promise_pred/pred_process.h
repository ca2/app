#pragma once


//template < typename PRED >
//class pred_future :
//   virtual public ::matter
//{
//public:
//
//
//   PRED     m_pred;
//
//
//   pred_future(PRED pred) :
//      m_pred(pred)
//   {
//
//   }
//
//
//   virtual ~pred_future()
//   {
//
//
//   }
//
//
//   virtual ::e_status run() override
//   {
//
//      __throw(interface_only_exception());
//
//      return ::error_interface_only;
//
//   }
//
//
//   void receive_response(const ::payload& payload) override
//   {
//
//      m_pred(payload);
//
//   }
//
//
//};
//


template < typename PRED >
class pred_process :
   virtual public matter
{
public:

   PRED m_pred;
   //future() {}

   //future(const ::future& future) : function((const ::function &) future) { }
   //future(::future * pfuture) : function((const ::function &) *pfuture) { }
   pred_process(PRED pred) : m_pred(pred) { }


   virtual void operator()(const payload & payload)  override
   {

      m_pred(payload);

   }


   //template < typename PRED >
   //void pred(PRED pred);


   //inline future& operator = (const ::future& future) { m_pmatter = future.m_pmatter; return *this; }
   //future& operator = (const ::payload& payload);

};


template < typename PRED >
::promise::process __process(PRED pred)
{

    return __new(pred_process< PRED >(pred));

}



