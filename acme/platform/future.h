#pragma once


template < typename OBJECT, typename TRANSPORT = transport < OBJECT > >
class future :
   virtual public ::matter
{
public:

   class receptor :
      virtual public matter
   {
   public:


      virtual void get(future & future) {}


   };

   template < typename PREDICATE >
   class predicate_receptor :
      virtual public receptor
   {
   public:


      PREDICATE   m_predicate;


      predicate_receptor(PREDICATE predicate) :
         m_predicate(predicate)
      {

      }


      virtual void get(future & pfuture) override
      {

         m_predicate(pfuture);

      }


   };



   TRANSPORT                              m_transport;
   __pointer(manual_reset_event)          m_pevent;
   __pointer(receptor)                    m_preceptor;



   future();


   ///void set_object(const OBJECT & result, const ::e_status & estatus = ::success);
   void set_status(const ::e_status & estatus = ::success);


   TRANSPORT & get_object(const ::duration & duration = ::duration::infinite());


   ::e_status wait(const ::duration& duration = ::duration::infinite());


   template < typename PREDICATE >
   future& then(PREDICATE predicate);

   template < typename PREDICATE >
   future& then(const ::duration& duration, PREDICATE predicate);

   auto operator ->() { return m_transport.operator ->(); }
   auto operator ->() const { return m_transport.operator ->(); }

};


CLASS_DECL_ACME critical_section* get_future_critical_section();

CLASS_DECL_ACME void initialize_future_critical_section();

CLASS_DECL_ACME void finalize_future_critical_section();




template < typename OBJECT, typename TRANSPORT = ::transport < OBJECT >, typename FUTURE = ::future < OBJECT > >
class asynchronous :
   virtual public matter
{
public:


   __pointer(FUTURE)          m_pfuture;


   FUTURE* future();

};
