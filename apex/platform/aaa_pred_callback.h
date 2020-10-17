#pragma once



template < typename PRED >
class __pred_callback :
   virtual public ::matter
{
public:


   PRED                             m_pred;
   __pointer(::matter)      m_pobjectHold;


   __pred_callback(PRED pred, ::matter* pobjectHold = nullptr) :
      m_pred(pred),
      m_pobjectHold(pobjectHold)
   {

   }

   virtual ~__pred_callback()
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
inline auto __task_callback(PRED pred, ::matter* pobjectHold)
{

   return __new(__pred_callback < PRED >(pred, pobjectHold));

}
