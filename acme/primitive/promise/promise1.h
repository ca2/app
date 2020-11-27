#pragma once



//template < typename TYPE, typename PRED >
//class future_pred :
//   virtual public ::t_runnable
//{
//public:
//
//   /// result ahead of the promisse?
//   /// Oh!!
//   /// Why not an allocated pointer of unitialized matter,
//   /// that will hold the final built matter as result?
//   /// (a pointer is smart and safe solution)
//   TYPE        m_result;
//   PRED        m_pred;
//
//   future_pred(const TYPE & t, PRED pred) : m_result(t), m_pred(pred) { }
//
//   virtual ::estatus     run() override
//   {
//
//      return m_pred(m_result);
//
//   }
//
//};

//template < typename TYPE, typename PRED >
//inline __pointer(::count_runnable) __process(const TYPE & t, PRED pred)
//{
//
//   return __new(future_pred < TYPE, PRED >(t, pred));
//
//}
