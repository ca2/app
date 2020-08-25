#pragma once


namespace file
{


   class os_watcher;


   class os_watch :
      virtual public watch
   {
   public:


      //bool                 m_bOwn;


      os_watch();
      virtual ~os_watch();

      //virtual bool open(const ::file::path & pathFolder, bool bRecursive);


   };




   class os_watcher :
      virtual public watcher
   {
   public:


      i32 mFD;
      struct timeval mTimeOut;
      fd_set mDescriptorSet;


      os_watcher();
      virtual ~os_watcher();


     virtual watch_id add_watch(const ::file::path & pathFolder, listener * plistenerParam, bool bRecursive) override;


      virtual bool step() override;

      //virtual ::estatus     run() override;


   };


} // namespace file_watcher

