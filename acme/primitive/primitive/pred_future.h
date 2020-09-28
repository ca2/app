#pragma once


template < typename PRED >
class ___pred_future :
   virtual public ::elemental
{
public:


   PRED                             m_pred;
   __pointer(::elemental)      m_pobjectHold;


   ___pred_future(PRED pred, ::elemental* pobjectHold = nullptr) :
      m_pred(pred),
      m_pobjectHold(pobjectHold)
   {

   }


   virtual ~___pred_future()
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
inline auto __pred_future(PRED pred, ::elemental* pobjectHold = nullptr)
{

   return __new(___pred_future < PRED >(pred, pobjectHold));

}
