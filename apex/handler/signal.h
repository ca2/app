// Extrapolation from merge with control_"topic" by camilo on day after ThomasBirthday2021 10:16!!
#pragma once



#include "acme/handler/extended_topic.h"
#include "acme/primitive/collection/map.h"
#include "context.h"


class context;

using particle_context = map < ::pointer < ::particle >, ::pointer < ::context > >;



class CLASS_DECL_APEX signal :
   virtual public ::extended_topic
{
public:


   ::manager *                            m_pmanager;
   ::particle_context                     m_particlecontext;


   signal(const ::atom & atom, ::manager * pmanager = nullptr);
   ~signal() override;


#ifdef _DEBUG

   
   virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
   virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
   virtual i64 release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;


#endif


   virtual void run() override;


   virtual void notify();

   virtual void add_handler(::particle* pparticle);

   virtual void erase_handler(::particle * pparticle);

   virtual void set_modified();

   virtual void clear_modified();

   virtual bool is_modified() const;

   virtual ::context * listener_context(::particle * pparticle);

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


   inline bool operator==(const ::atom & atom) const { return m_atom == atom || m_atom == FULL_ID; }

   void subject_common_construct();

   virtual void start_task();

   virtual bool is_up_to_date(const ::context * pcontext) const;

   virtual void set_up_to_date(::context * pcontext);



};


using signal_map = ::atom_map < ::pointer<class ::signal>>;



