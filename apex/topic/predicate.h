// From subject_listener from apex_database by camilo on day after ThomasBirthday2021 07:26 BRT
#pragma once


template < typename PREDICATE >
class __predicate :
   virtual public ::matter
{
public:


   PREDICATE m_predicate;


   __predicate(PREDICATE predicate) : m_predicate(predicate) { }
   virtual ~__predicate() {}
   //method(const ::matter_pointer & pmatter) : matter_pointer(pmatter) { }
   //method(const ::method & method) : matter_pointer(method) { }


   //inline void operator()() const;

   void handle(::topic * ptopic, ::context * pcontext) override
   {

      m_predicate(ptopic, pcontext);

   }

   //template < typename PRED >
   //void pred(PRED pred);

   //inline method & operator = (const ::method & method) { m_pmatter = method.m_pmatter; return *this; }
   //method & operator = (const ::payload & payload);


};


template < typename PREDICATE >
::matter_pointer predicate(PREDICATE predicate)
{

   return __new(__predicate<PREDICATE>(predicate));

}



