// Extrapolation from merge with control_"topic" by camilo on day after ThomasBirthday2021 10:16!!
#pragma once



#include "acme/handler/extended_topic.h"
#include "acme/primitive/collection/map.h"
#include "context.h"


class context;

using signal_handle_context = map < signal_handler, ::pointer < ::context > >;



class CLASS_DECL_APEX signal :
   virtual public ::extended_topic
{
public:


   ::manager *                            m_pmanager;
   ::signal_handle_context                m_signalhandlercontext;


   signal(const ::atom & atom, ::manager * pmanager = nullptr);
   ~signal() override;


#ifdef _DEBUG

   
   virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
   virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
   virtual i64 release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;


#endif


   virtual void run() override;


   virtual void notify();

   virtual void add_handler(::matter * pmatter);

   virtual void add_signal_handler(const signal_handler& signalhandler);

   virtual void erase_handler(const signal_handler& signalhandler);

   virtual void set_modified();

   virtual void clear_modified();

   virtual bool is_modified() const;

   virtual ::context * listener_context(const signal_handler & signalhandler);

   void post_destroy_all();


   ::duration poll_time();


   static inline bool should_poll(const ::duration & duration)
   {

      return duration >= 100_ms;

   }


   ::topic & operator=(const ::atom & atom)
   {

      m_atom = atom;

      return *this;

   }


   inline bool operator==(const ::atom & atom) const { return m_atom == atom || m_atom == ID_FULL; }

   void subject_common_construct();

   virtual void start_task();

   virtual bool is_up_to_date(const ::context * pcontext) const;

   virtual void set_up_to_date(::context * pcontext);



};


using signal_map = ::atom_map < ::pointer<class ::signal>>;



