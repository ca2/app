#pragma once


namespace userpresence
{


   class CLASS_DECL_CORE presence :
      virtual public ::object
   {
   public:

      
      enum e_predicateefined_status
      {
         
         status_online     = 1000000006,
         status_offline    = 1000000025
            
      };


      class ::time m_timeLastActivity;
      class ::time m_timeLastPulse;
      long long        m_iShortStatusWayTag;
      string         m_strLongStatus;


      presence(::particle * pparticle);
      virtual ~presence();

      virtual void report_activity();


      virtual void defer_pulse_user_presence();
      virtual void pulse_user_presence();

      virtual bool on_ui_mouse_message(::user::mouse * pmouse);


   };


} // namespace userpresence



