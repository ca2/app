#pragma once



template < typename PRED >
class __λcallback :
   virtual public ::matter
{
public:


   PRED                             m_pred;
   __pointer(::matter)      m_pobjectHold;


   __λcallback(PRED pred, ::matter* pobjectHold = nullptr) :
      m_pred(pred),
      m_pobjectHold(pobjectHold)
   {

   }

   virtual ~__λcallback()
   {


   }


   virtual ::estatus run() override
   {

      __throw(interface_only_exception());

      return ::error_interface_only;

   }


   void receive_response(const ::payload& payload) override
   {

      m_pred(payload);

   }


};




template < typename PRED >
inline auto __task_callback(PRED pred, ::matter* pobjectHold)
{

   return __new(__λcallback < PRED >(pred, pobjectHold));

}
