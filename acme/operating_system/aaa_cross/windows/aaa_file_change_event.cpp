#include "framework.h"
#include "acme/operating_system.h"


namespace windows
{


   ///  \brief		constructor with passed path to file
   ///  \lparam		path the file to watch
   ///  \lparam		watchsubtree if true, the function monitors the directory tree
   ///				rooted at the specified directory, if it is false,
   ///				it monitors only the specified directory
   ///  \lparam		filter filter conditions that satisfy a machine notification wait
   ///				can take values described by enum filter
   file_change_event::file_change_event(::matter * pobject, const char * path, bool watchsubtree, u32 filter) :
      synchronization_object(::FindFirstChangeNotificationW(utf8_to_unicode(path), watchsubtree, filter))
   {
      if (hsync() == nullptr)
         throw ::exception(runtime_error("file_change_event: failed to create event"));
   }

   ///  \brief		destructor
   file_change_event::~file_change_event()
   {
   }


   bool file_change_event::lock(const duration & durationTimeout)
   {

      u32 dwRet = ::WaitForSingleObject(hsync(), durationTimeout.u32_millis());

      if (dwRet == WAIT_OBJECT_0 || dwRet == WAIT_ABANDONED)
      {

         return true;

      }
      else
      {

         return false;

      }

   }

   bool file_change_event::unlock()
   {
      next();
      return true;
   }

   ///  \brief		waits for an file notification forever
   synchronization_result file_change_event::wait()
   {

      if (::WaitForSingleObject(hsync(), U32_INFINITE_TIMEOUT) != WAIT_OBJECT_0)
      {

         return synchronization_result(e_synchronization_result_error);

      }

      return synchronization_result(e_synchronization_result_signaled_base);

   }


   ///  \brief		waits for an file notification for a specified time
   ///  \lparam		duration time period to wait for an file notification
   ///  \return	waiting action result as synchronization_result
   synchronization_result file_change_event::wait(const duration & duration)
   {

      return synchronization_result((u32) ::WaitForSingleObject(hsync(), duration.u32_millis()));

   }


   ///  \brief		requests that the operating system signal a machine
   ///				notification handle the next time it detects an appropriate
   ///				machine
   bool file_change_event::next()
   {
      return ::FindNextChangeNotification(hsync()) != false;

   }

   ///  \brief		stops machine notification handle monitoring
   void file_change_event::close()
   {
      ::FindCloseChangeNotification(hsync());
   }


} // namespace windows



