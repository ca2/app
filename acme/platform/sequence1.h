#pragma once


template < typename SEQUENCE >
using sequence_step = ::function < void(SEQUENCE *) >;


template < typename SEQUENCE >
class sequence :
   virtual public ::element
{
public:


   pointer< sequencer < SEQUENCE > >   m_psequencer;
   ::payload                              m_payloadResult;


   virtual ::payload do_synchronously(const class ::wait & wait = ::wait::infinite())
   {

      return {};

   }


   virtual void do_asynchronously()
   {


   }


   //inline SEQUENCE * get() { return this; }
   //inline const SEQUENCE * get() const { return this; }

   //sequence * then(const sequence_step < SEQUENCE > & function);

   //sequence * then(const ::duration & duration, const sequence_step < SEQUENCE > & function);



};




template < typename SEQUENCE >
sequencer < SEQUENCE > ::sequencer()
{

   //m_ptask = ::get_task();

   m_pevent = nullptr;

}


//template < typename TYPE >
//void future < RESULT > ::set_object(const RESULT& result, const ::e_status & estatus)
//{
//
//   critical_section_lock lock(get_sequence_critical_section());
//
//   if (m_p.m_estatus == error_not_initialized)
//   {
//
//      m_p.m_estatus = estatus;
//
//      m_p.m_result = result;
//
//      if (m_pevent)
//      {
//
//         m_pevent->SetEvent();
//
//      }
//
//      if (m_preceptor)
//      {
//
//         m_preceptor->get(this);
//
//      }
//
//   }
//
//}


template < typename SEQUENCE >
void sequencer < SEQUENCE > ::fork()
{

   ::get_system()->fork(__routine([this]()
      {

         on_sequence();

      }));

}


template < typename SEQUENCE >
void sequencer < SEQUENCE > ::on_sequence()
{

   critical_section_lock lock(get_sequence_critical_section());

   if (m_pevent)
   {

      m_pevent->SetEvent();

   }

   while (m_stepa.has_element())
   {

      auto step = m_stepa.pop_first();

      lock.unlock();

      step(m_psequence);

      lock.lock();

   }

}


//template < typename SEQUENCE >
//void sequencer < SEQUENCE > ::set_status(const ::e_status & estatus)
//{
//
//   critical_section_lock lock(get_sequence_critical_section());
//
//   m_p.m_estatus = estatus;
//
//   if (m_pevent)
//   {
//
//      m_pevent->SetEvent();
//
//   }
//
//   increment_reference_count();
//
//   m_psystem->fork(__routine([this]()
//      {
//
//         auto pHold = ::move_transfer(this);
//
//         critical_section_lock lock(get_sequence_critical_section());
//
//         while (m_stepa.has_element())
//         {
//
//            auto pfunction = m_stepa.pop_first();
//
//            lock.unlock();
//
//            pfunction->process(*this);
//
//            lock.lock();
//
//         }
//
//      }));
//
//}

template < typename SEQUENCE >
sequence < SEQUENCE > * sequencer < SEQUENCE > ::topic(const ::duration & duration)
{

   critical_section_lock lock(get_sequence_critical_section());

   if (m_psequence.m_estatus == error_not_initialized)
   {

      m_pevent = memory_new manual_reset_event();

      if (!m_pevent->wait(duration))
      {

         lock.lock();

         if (m_psequence.m_estatus == error_not_initialized)
         {

            m_psequence.m_estatus = error_timeout;

         }

         lock.unlock();

      }

   }

   return this->m_p;

}


template < typename SEQUENCE >
::e_status sequencer < SEQUENCE > ::wait(const class ::wait & wait)
{

   critical_section_lock lock(get_sequence_critical_section());

   if (m_psequence.m_estatus == error_not_initialized)
   {

      m_pevent = __new(manual_reset_event);

      lock.unlock();

      if (!m_pevent->wait(wait))
      {

         lock.lock();

         if (m_psequence.m_estatus == error_not_initialized)
         {

            m_psequence.m_estatus = error_wait_timeout;

         }

         lock.unlock();

      }

   }

   return m_psequence.m_estatus;

}


template < typename SEQUENCE >
sequence < SEQUENCE > * sequencer < SEQUENCE > ::then(const sequence_step < SEQUENCE > & step)
{

   critical_section_lock lock(get_sequence_critical_section());

   if (m_psequence.is_set())
   {

      m_stepa.add(step);

   }
   else
   {

      lock.unlock();

      step(m_psequence);

   }

   return m_psequence;

}


template < typename SEQUENCE >
sequence < SEQUENCE > * sequencer < SEQUENCE > ::then(const ::duration & duration, const sequence_step < SEQUENCE > & step)
{

   critical_section_lock lock(get_sequence_critical_section());

   if (m_psequence.m_estatus == error_not_initialized)
   {

      m_stepa.add(step);

      m_pevent = memory_new manual_reset_event();

      lock.unlock();

      if (!m_pevent->wait(duration))
      {

         lock.lock();

         if (m_psequence.m_estatus == error_not_initialized)
         {

            m_psequence.m_estatus = error_timeout;

         }

         lock.unlock();

         if (m_psequence.m_estatus == error_timeout)
         {

            step(m_psequence);

         }

      }

   }
   else
   {

      lock.unlock();

      step(m_psequence);

   }

   return m_psequence;

}



//template < typename OBJECT, typename TRANSPORT , typename SEQUENCE >
//SEQUENCE * asynchronous < OBJECT, TRANSPORT, SEQUENCE >::sequence()
//{
//
//   if (!m_pfuture)
//   {
//
//      m_psystem->__construct_new(m_pfuture);
//       
//      m_pfuture->m_psystem = m_psystem;
//
//      m_pfuture->m_p = this;
//
//   }
//
//   return m_pfuture;
//
//}




//template < typename TYPE >
//inline ::pointer<TYPE>property_object::__create_new()
//{
//
//   auto p = __new(TYPE);
//
//   p->initialize_matter(this);
//
//   return p;
//
//}


//#endif // __cplusplus_winrt
