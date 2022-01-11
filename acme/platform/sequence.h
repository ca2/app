#pragma once


template < typename OBJECT /*, typename TRANSPORT = transport < OBJECT > */ >
class transport :
   virtual public ::matter
{
public:


   class route :
      virtual public matter
   {
   public:


      virtual void transport(class transport & transport) {}


   };


   template < typename OPERATION >
   class route_operation :
      virtual public route
   {
   public:


      OPERATION   m_operation;


      route_operation(OPERATION operation) :
         m_operation(operation)
      {

      }


      virtual void process(class transport& transport) override
      {

         m_operation(transport);

      }

   };


   __pointer(::object)                    m_pobject;
   __pointer(manual_reset_event)          m_pevent;
   __pointer_array(route)                 m_routea;

   
   transport();


   ///void set_object(const OBJECT & result, const void & estatus = ::success);
   void set_status(const ::e_status3 & estatus = ::success);


   OBJECT & get_object(const ::duration & duration = ::duration::infinite());


   void wait(const ::duration& duration = ::duration::infinite());


   template < typename OPERATION >
   transport & then(OPERATION predicate);

   template < typename OPERATION >
   transport& then(const ::duration& duration, OPERATION predicate);

   auto operator ->() { return m_pobject.operator ->(); }
   auto operator ->() const { return m_pobject.operator ->(); }

};


CLASS_DECL_ACME critical_section* get_sequence_critical_section();

CLASS_DECL_ACME void initialize_sequence_critical_section();

CLASS_DECL_ACME void finalize_sequence_critical_section();


template < typename OBJECT /*, typename TRANSPORT = ::transport < OBJECT >, typename SEQUENCE = ::sequence < OBJECT, TRANSPORT >*/ >
class asynchronous :
   virtual public matter
{
public:


   __pointer(OBJECT)          m_pobject;


   //OBJECT * ();


};



