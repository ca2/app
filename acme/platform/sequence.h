#pragma once


template < typename OBJECT, typename TRANSPORT = transport < OBJECT > >
class sequence :
   virtual public ::matter
{
public:


   class function :
      virtual public matter
   {
   public:


      virtual void process(sequence & sequence) {}


   };


   template < typename PREDICATE >
   class function_predicate :
      virtual public function
   {
   public:


      PREDICATE   m_predicate;


      function_predicate(PREDICATE predicate) :
         m_predicate(predicate)
      {

      }


      virtual void process(sequence & sequence) override
      {

         m_predicate(sequence);

      }

   };


   TRANSPORT                              m_transport;
   __pointer(manual_reset_event)          m_pevent;
   __pointer_array(function)              m_functiona;
   ::task_pointer                         m_ptask;


   sequence();


   ///void set_object(const OBJECT & result, const ::e_status & estatus = ::success);
   void set_status(const ::e_status & estatus = ::success);


   TRANSPORT & get_object(const ::duration & duration = ::duration::infinite());


   ::e_status wait(const ::duration& duration = ::duration::infinite());


   template < typename PREDICATE >
   sequence & then(PREDICATE predicate);

   template < typename PREDICATE >
   sequence & then(const ::duration& duration, PREDICATE predicate);

   auto operator ->() { return m_transport.operator ->(); }
   auto operator ->() const { return m_transport.operator ->(); }

};


CLASS_DECL_ACME critical_section* get_sequence_critical_section();

CLASS_DECL_ACME void initialize_sequence_critical_section();

CLASS_DECL_ACME void finalize_sequence_critical_section();


template < typename OBJECT, typename TRANSPORT = ::transport < OBJECT >, typename SEQUENCE = ::sequence < OBJECT > >
class asynchronous :
   virtual public matter
{
public:


   __pointer(SEQUENCE)          m_pfuture;


   SEQUENCE * sequence();


};



