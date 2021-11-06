// iMonitorMyFiles
#include "framework.h"
#include "_ios.h"
#include <sys/time.h>


namespace file
{


   os_watch::os_watch()
   {
      
      m_bKeepMonitoringFile = false;
      
   }

   
   os_watch::~os_watch()
   {
      
      if(m_source)
      {
 
         dispatch_source_cancel(m_source);
         
      }
      
      if(m_iFile)
      {

         close(m_iFile);
         
      }
      
      m_iFile = 0;
      
      m_source = nullptr;

   }


   bool os_watch::open(const ::file::path & pathFolder, bool bRecursive)
   {
      
      // Add a file descriptor for our test file
      m_iFile = ::open(pathFolder, O_EVTONLY);
      
      // Get a reference to the default queue so our file notifications can go out on it
      dispatch_queue_t defaultQueue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
      
      // Create a dispatch source
      m_source = dispatch_source_create(DISPATCH_SOURCE_TYPE_VNODE,
                                       m_iFile,
                                       DISPATCH_VNODE_ATTRIB | DISPATCH_VNODE_DELETE | DISPATCH_VNODE_EXTEND | DISPATCH_VNODE_LINK | DISPATCH_VNODE_RENAME | DISPATCH_VNODE_REVOKE | DISPATCH_VNODE_WRITE,
                                       defaultQueue);
      
      // Log one or more messages to the screen when there's a file change event
      dispatch_source_set_event_handler(m_source, ^ { on_event(dispatch_source_get_data(m_source)); });
      
      dispatch_source_set_cancel_handler(m_source, ^ { on_dispatch_source_cancellation(); });
      
      // Start monitoring the test file
      dispatch_resume(m_source);
      
      if(!watch::open(pathFolder, m_bRecursive))
      {
         
         return false;
         
      }

      return true;

   }
   

   void os_watch::on_dispatch_source_cancellation()
   {
   
       close(m_iFile);
      
       m_iFile = 0;
      
       m_source = nullptr;
       
       // If this dispatch source was canceled because of a rename or delete notification, recreate it
       if (m_bKeepMonitoringFile)
       {
          
          m_bKeepMonitoringFile = false;
          
          open(m_pathFolder, m_bRecursive);
          
       }
      
   }

   
//   bool os_watch::step()
//   {
//      
//      return true;
//      
//   }


   void os_watch::on_event(unsigned long uEventType)
   {
      
      ::file::action action;

      psubject->m_pathFile = m_pathFolder;

      if (uEventType & DISPATCH_VNODE_ATTRIB)
      {
          //[eventSet addObject:@(TABFileMonitorChangeTypeMetadata)];
      }
      if (uEventType & DISPATCH_VNODE_DELETE)
      {
          psubject->m_eaction = ::file::action_delete;
          m_bKeepMonitoringFile = true;
      }
      if (uEventType & DISPATCH_VNODE_EXTEND)
      {
          //[eventSet addObject:@(TABFileMonitorChangeTypeSize)];
      }
      if (uEventType & DISPATCH_VNODE_LINK)
      {
          //[eventSet addObject:@(TABFileMonitorChangeTypeObjectLink)];
      }
      if (uEventType & DISPATCH_VNODE_RENAME)
      {
          psubject->m_eaction = ::file::action_modify;
          m_bKeepMonitoringFile = true;
      }
      if (uEventType & DISPATCH_VNODE_REVOKE)
      {
          //[eventSet addObject:@(TABFileMonitorChangeTypeRevoked)];
      }
      if (uEventType & DISPATCH_VNODE_WRITE)
      {
          psubject->m_eaction = ::file::action_modify;
      }
      

         
//         if(eventFlags[i] & kFSEventStreamEventFlagItemCreated)
//         {
//
//            psubject->m_eaction = ::file::action_add;
//
//         }

         handle_action(&action);

     
   }



//   void os_watch::eraseFile(const ::string & file)
//   {
//
//
//
//   }
   

   bool os_watcher::step()
   {
      
      bool done = false;
      
      // Start the run loop but return after each source is handled.
      //SInt32 result = CFRunLoopRunInMode(kCFRunLoopDefaultMode, 2, true);
      
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










