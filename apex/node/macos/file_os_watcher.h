#pragma once


namespace file
{
   
   
   class CLASS_DECL_APEX os_watch :
      virtual public watch
   {
   public:


      FSEventStreamRef m_stream;


      os_watch();
      virtual ~os_watch();


      virtual bool open(const ::file::path & pathFolder, bool bRecursive) override;

      //void handle_action(::file::action * paction) override;


      static void myCallbackFunction(
      ConstFSEventStreamRef streamRef,
      void *clientCallBackInfo,
      size_t numEvents,
      void *eventPaths,
      const FSEventStreamEventFlags eventFlags[],
      const FSEventStreamEventId eventIds[]);
      void addAll();
      void removeAll();

      bool step()override;

   };
   

   class CLASS_DECL_APEX os_watcher :
   virtual public watcher
   {
   public:


      os_watcher();
      virtual ~os_watcher();

      
      virtual bool step() override;
      

   };


} // namespace file_watcher




