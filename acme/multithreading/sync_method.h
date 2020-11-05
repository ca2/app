#pragma once


class sync_method;


inline __pointer(sync_method) ___sync_method(const method& method);


class CLASS_DECL_ACME sync_method :
   public ::sync
{
protected:

   friend __pointer(sync_method) ___sync_method(const method& method);


   sync_method(const method& method) :
      m_method(method)
   {

      __defer_construct(m_peventCompletion);

   }


public:


   method                                 m_method;
   __pointer(manual_reset_event)          m_peventCompletion;
   ::duration                             m_duration;
   ::estatus                              m_estatus;


   virtual ~sync_method() {}
   

   inline virtual ::estatus operator()() override
   {

      m_estatus = m_method();

      m_peventCompletion->SetEvent();

      return m_estatus;

   }


   virtual sync_result wait(const duration& durationTimeout)
   {

      return m_peventCompletion->wait(durationTimeout);

   }


};



inline __pointer(sync_method) ___sync_method(const method& method)
{

   return __new(sync_method(method));

}