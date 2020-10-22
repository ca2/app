#pragma once


template < typename PRED >
class ___future :
   virtual public ::matter
{
public:


   PRED                             m_pred;
   __pointer(::matter)      m_pobjectHold;


   ___future(PRED pred, ::matter* pobjectHold = nullptr) :
      m_pred(pred),
      m_pobjectHold(pobjectHold)
   {

   }


   virtual ~___future()
   {


   }


   virtual ::estatus run() override
   {

      __throw(interface_only_exception());

      return ::error_interface_only;

   }


   void receive_response(const ::var& var) override
   {

      m_pred(var);

   }


};


template < typename PRED >
inline __pointer(::matter) __future(PRED pred)
{

   return __new(___future < PRED >(pred));

}



template < typename PRED >
inline __pointer(::matter) __future(PRED pred, ::matter* pobjectHold)
{

   return __new(___future < PRED >(pred, pobjectHold));

}
