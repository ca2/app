#include "framework.h"
#include "file_os_watcher.h"



namespace file
{


   os_watch::os_watch()
   {
      
   }

   
   os_watch::~os_watch()
   {
      
      removeAll();

   }


   bool os_watch::open(const ::file::path & pathFolder, bool bRecursive)
   {
      
      m_stream = nullptr;
      
      m_pwatcher->m_pthread->send_pred([&]()
      {

         CFStringRef mypath = CFStringCreateWithCString(kCFAllocatorDefault, pathFolder, kCFStringEncodingUTF8);
         
         CFArrayRef pathsToWatch = CFArrayCreate(nullptr, (const void **)&mypath, 1, nullptr);
         
         void * callbackInfo = this; // put stream-specific data here.
         
         CFAbsoluteTime latency = 0.3; /* Latency in seconds */
         
         FSEventStreamContext context;
         
         context.version = 0;
         
         context.info = (void*) this;
         
         context.retain = nullptr;
         
         context.release = nullptr;
         
         context.copyDescription = nullptr;
         
         /* Create the stream, passing in a callback */
         
         m_stream = FSEventStreamCreate(nullptr,
                                       &myCallbackFunction,
                                       &context,
                                       pathsToWatch,
                                       kFSEventStreamEventIdSinceNow, /* Or a previous event ID */
                                       latency,
                                       kFSEventStreamCreateFlagFileEvents /* Flags explained in generic */
                                       );
         
         FSEventStreamScheduleWithRunLoop(m_stream, CFRunLoopGetCurrent(), kCFRunLoopCommonModes);
         
         FSEventStreamStart(m_stream);

         CFRelease(mypath);
         
         CFRelease(pathsToWatch);
         
      });
      
      if(!m_stream)
      {
         
         return false;
         
      }
      
      if(!watch::open(pathFolder, bRecursive))
      {
         
         return false;
         
      }

      return true;

   }
   
   
   bool os_watch::step()
   {
      
      return true;
      
   }


   void os_watch::myCallbackFunction(
   ConstFSEventStreamRef streamRef,
   void *clientCallBackInfo,
   size_t numEvents,
   void *eventPaths,
   const FSEventStreamEventFlags eventFlags[],
   const FSEventStreamEventId eventIds[])
   {

      int i;

      char **paths = (char **) eventPaths;

      auto pwatch = (os_watch *) clientCallBackInfo;

      ::file::action action;

      action.m_pwatch = pwatch;

      action.m_id = pwatch->m_id;

      action.m_pathFolder = pwatch->m_pathFolder;

      for (i = 0; i < numEvents; i++)
      {

         ::file::path path = paths[i];

         if(!pwatch->m_bRecursive)
         {

            if(path.folder().get_length() > action.m_pathFolder.get_length())
            {

               continue;

            }

         }

         ::str::begins_eat(path, action.m_pathFolder);

         action.m_pathFile = path;

         if(eventFlags[i] & kFSEventStreamEventFlagItemRemoved)
         {

            action.m_eaction = ::file::action_delete;

         }

         if(eventFlags[i] & kFSEventStreamEventFlagItemRenamed)
         {

            action.m_eaction = ::file::action_modify;

         }

         if(eventFlags[i] & kFSEventStreamEventFlagItemModified)
         {

            action.m_eaction = ::file::action_modify;

         }

         if(eventFlags[i] & kFSEventStreamEventFlagItemCreated)
         {

            action.m_eaction = ::file::action_add;

         }

         pwatch->handle_action(&action);

      }

   }



   void os_watch::removeAll()
   {

      FSEventStreamStop(m_stream);
      
      FSEventStreamInvalidate(m_stream);
      
      FSEventStreamRelease(m_stream);

      m_stream = nullptr;

   }
   

   bool os_watcher::step()
   {
      
      bool done = false;
      
      // Start the run loop but return after each source is handled.
      SInt32 result = CFRunLoopRunInMode(kCFRunLoopDefaultMode, 2, TRUE);
      
      // If a source explicitly stopped the run loop, or if there are no
      // sources or timers, go ahead and exit.
      //if ((result == kCFRunLoopRunStopped) || (result == kCFRunLoopRunFinished))
      //if (result == kCFRunLoopRunFinished)
      //{
         
      //   done = true;
         
      //}
      
      // Check for any other exit conditions here and set the
      // done variable as needed.
      
      //if(done)
      //{
         
      //   return false;
         
      //}
      
      if(!watcher::step())
      {
       
         return false;
         
      }
      
      return true;

   }
   

   os_watcher::os_watcher()
   {

   }


   os_watcher::~os_watcher()
   {

   }


} // namespace file_watcher



