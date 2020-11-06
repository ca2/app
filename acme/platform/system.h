#pragma once


namespace acme
{


   class CLASS_DECL_ACME system :
      virtual public ::source,
      virtual public ::task
   {
   public:


      ::mutex                                            m_mutexTask;
      task_map                                           m_taskmap;
      task_id_map                                        m_taskidmap;
      ::mutex                                            m_mutexTaskOn;
      isomap < ITHREAD, ITHREAD >                        m_mapTaskOn;


      ::apex::system *                                   m_papexsystem;
      ::aqua::system *                                   m_paquasystem;
      ::aura::system *                                   m_paurasystem;
      ::axis::system *                                   m_paxissystem;
      ::base::system *                                   m_pbasesystem;
      ::bred::system *                                   m_pbredsystem;
      ::core::system *                                   m_pcoresystem;


      system();
      virtual ~system();


      virtual void defer_calc_os_dark_mode();


      virtual void on_apply(::action * paction) override;


      virtual ::estatus main_user_async(const ::procedure & procedure, ::e_priority epriority = priority_normal);

      virtual ::estatus main_user_sync(const procedure & procedure, const ::duration & duration = one_minute(), e_priority epriority = priority_normal);


      ::task * get_task(ITHREAD ithread);
      ITHREAD get_task_id(::task * ptask);
      void set_task(ITHREAD ithread, ::task * ptask);
      void unset_task(ITHREAD ithread, ::task * ptask);


   };

} // namespace acme
