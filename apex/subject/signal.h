﻿// Extrapolation from merge with control_"subject" by camilo on day after ThomasBirthday2021 10:16!!
#pragma once


class CLASS_DECL_APEX signal :
   virtual public ::subject
{
public:


   ::manager *                            m_pmanager;
   ::matter_context                       m_mattercontext;


   signal(const ::id & id, ::manager * pmanager = nullptr);
   ~signal() override;


#ifdef _DEBUG

   
   virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
   virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
   virtual i64 release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;


#endif


   virtual ::e_status run() override;


   virtual void notify();

   virtual void add_handler(::matter * pmatter, bool bForkWhenNotify = false);

   virtual void erase_handler(::matter * pmatter);

   virtual void set_modified();

   virtual void clear_modified();

   virtual bool is_modified() const;

   virtual ::context * listener_context(::matter * pmatter);

   void post_destroy_all();


   inline ::duration poll_time() { return m_psystem->get_update_poll_time(m_id); };


   static inline bool should_poll(const ::duration & duration)
   {

      return duration >= 100_ms;

   }


   ::subject & operator=(const ::id & id)
   {

      m_id = id;

      return *this;

   }


   inline bool operator==(const ::id & id) const { return m_id == id || m_id == FULL_ID; }

   void subject_common_construct();

   virtual ::e_status start_task();

   virtual bool is_up_to_date(const ::context * pcontext) const;

   virtual void set_up_to_date(::context * pcontext);



};


using signal_map = ::id_map < __pointer(class ::signal) >;



