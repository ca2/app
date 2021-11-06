#pragma once


//template < typename PRED >
//class predicate_future :
//   virtual public ::matter
//{
//public:
//
//
//   PRED     m_predicate;
//
//
//   predicate_future(PRED pred) :
//      m_predicate(pred)
//   {
//
//   }
//
//
//   virtual ~predicate_future()
//   {
//
//
//   }
//
//
//   virtual ::e_status run() override
//   {
//
//      throw ::interface_only_exception();
//
//      return ::error_interface_only;
//
//   }
//
//
//   void receive_response(const ::payload & payload) override
//   {
//
//      m_predicate(payload);
//
//   }
//
//
//};
//


template < typename PRED >
class predicate_process :
   virtual public matter
{
public:

   PRED m_predicate;
   //future() {}

   //future(const ::future& future) : function((const ::function &) future) { }
   //future(::future * pfuture) : function((const ::function &) *pfuture) { }
   predicate_process(PRED pred) : m_predicate(pred) { }


   virtual void operator()(const ::payload & payload)  override
   {

      m_predicate(payload);

   }


   //template < typename PRED >
   //void pred(PRED pred);


   //inline future& operator = (const ::future& future) { m_pmatter = future.m_pmatter; return *this; }
   //future& operator = (const ::payload & payload);

};


//template < typename PRED >
//::future __process(PRED pred)
//{
//
//    return __new(predicate_process< PRED >(pred));
//
//}



