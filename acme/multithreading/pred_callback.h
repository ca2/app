#pragma once


template < typename PRED >
class ___pred_callback :
   virtual public ::generic
{
public:


   PRED                             m_pred;
   __pointer(::generic)      m_pobjectHold;


   ___pred_callback(PRED pred, ::generic* pobjectHold = nullptr) :
      m_pred(pred),
      m_pobjectHold(pobjectHold)
   {

   }


   virtual ~___pred_callback()
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
inline auto __pred_callback(PRED pred, ::generic* pobjectHold = nullptr)
{

   return __new(___pred_callback < PRED >(pred, pobjectHold));

}
