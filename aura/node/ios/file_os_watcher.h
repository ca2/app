#pragma once


namespace file
{
   
   
   class CLASS_DECL_AURA os_watch :
      virtual public watch
   {
   public:


      int                  m_iFile;
      dispatch_source_t    m_source;
      bool                 m_bKeepMonitoringFile;

      os_watch();
      virtual ~os_watch();


      virtual bool open(const ::file::path & pathFolder, bool bRecursive) override;
      
      
      virtual void on_dispatch_source_cancellation();

      //void handle_action(::file::action * paction) override;


      void on_event(unsigned long uEventTypes);
      

   };
   

   class CLASS_DECL_AURA os_watcher :
   virtual public watcher
   {
   public:


      os_watcher();
      virtual ~os_watcher();

      
      virtual bool step() override;
      

   };


} // namespace file_watcher




