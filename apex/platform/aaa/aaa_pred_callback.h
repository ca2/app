#pragma once



template < typename PRED >
class __λcallback :
   virtual public ::matter
{
public:


   PRED                             m_predicate;
   __pointer(::matter)      m_pobjectHold;


   __λcallback(PRED pred, ::matter* pobjectHold = nullptr) :
      m_predicate(pred),
      m_pobjectHold(pobjectHold)
   {

   }

   virtual ~__λcallback()
   {


   }


   virtual ::e_status run() override
   {

      throw ::interface_only_exception();

      return ::error_interface_only;

   }


   void receive_response(const ::payload & payload) override
   {

      m_predicate(payload);

   }


};




template < typename PRED >
inline auto __task_callback(PRED pred, ::matter* pobjectHold)
{

   return __new(__λcallback < PRED >(pred, pobjectHold));

}
