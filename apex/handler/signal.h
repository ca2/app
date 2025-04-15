// Extrapolation from merge with control_"topic" by camilo on day after ThomasBirthday2021 10:16!!
#pragma once



#include "acme/handler/extended_topic.h"
#include "acme/prototype/collection/map.h"
//#include "acmee/handler/context.h"


class handler_context;

using signal_handler_context = ::map < ::signal_handler, ::pointer < ::handler_context > >;

using object_handler_context = ::map < ::object *, ::pointer < ::handler_context > >;


namespace handler
{


   class CLASS_DECL_APEX signal :
      virtual public ::extended_topic
//      , virtual public ::object
   {
   public:


      ::manager *                      m_pmanager;
      ::signal_handler_context         m_signalhandlercontext;
      ::object_handler_context         m_objecthandlercontext;


      signal(const ::atom & atom, ::manager * pmanager = nullptr);
      ~signal() override;


#ifdef _DEBUG


      virtual long long increment_reference_count() override;
      virtual long long decrement_reference_count() override;
      virtual long long release() override;


#endif


      virtual void run() override;


      virtual void notify();

      void on_notify(::particle * pparticle, enum_id eid) override;

      virtual void add_handler(::object * pobject);

      virtual void erase_handler(::object * pobject);

      virtual void add_signal_handler(const signal_handler & signalhandler);

      virtual void erase_signal_handler(const signal_handler & signalhandler);

      //virtual void erase_signal_handlers(::particle * pparticle);

      virtual void set_modified();

      virtual void clear_modified();

      virtual bool is_modified() const;

      virtual ::handler_context * listener_context(const signal_handler & signalhandler);

      void post_destroy_all();


      class ::time poll_time();


      static inline bool should_poll(const class time & time)
      {

         return time >= 100_ms;

      }


      ::topic & operator=(const ::atom & atom)
      {

         id() = atom;

         return *this;

      }


      inline bool operator==(const ::atom & atom) const { return id() == atom || id() == id_full; }

      void subject_common_construct();

      virtual void start_task();

      virtual bool is_up_to_date(const ::handler_context * pcontext) const;

      virtual void set_up_to_date(::handler_context * pcontext);



   };


} // namespace handler




