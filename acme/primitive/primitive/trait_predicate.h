////
////  trait_predicate.h
////  acme
////
////  Created by Camilo Sasuke Tsumanuma on 02/06/19.
////
//
//
//template <  typename PRED >
//class trait_predicate :
//virtual public ::matter
//{
//public:
//   
//   
//   PRED                 m_predicate;
//   
//   
//   trait_predicate(PRED pred) :
//   m_predicate(pred)
//   {
//      
//   }
//   
//   
//   virtual ::e_status     run(::trait & trait) override
//   {
//      
//      return m_predicate(trait);
//      
//   }
//   
//   
//};
//
//
//template < typename PRED >
//auto __trait_predicate(PRED pred)
//{
//   
//   return __new(trait_predicate < PRED >(pred));
//   
//}
//
//
//
