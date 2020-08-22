#pragma once


#ifdef WINDOWS_DESKTOP


/// This class represents events for file changes
class CLASS_DECL_AURA file_change_event :
   virtual public sync
{
public:

   /// enum describing the possible filters
   enum filter
   {
      change_file_name = FILE_NOTIFY_CHANGE_FILE_NAME,
      change_dir_name = FILE_NOTIFY_CHANGE_DIR_NAME,
      change_attributes = FILE_NOTIFY_CHANGE_ATTRIBUTES,
      change_size = FILE_NOTIFY_CHANGE_SIZE,
      change_last_write = FILE_NOTIFY_CHANGE_LAST_WRITE,
      change_security = FILE_NOTIFY_CHANGE_SECURITY
   };

   ///  \brief		constructor with passed path to file
   ///  \lparam		path the file to watch
   ///  \lparam		watchsubtree if true, the function monitors the directory tree
   ///				rooted at the specified directory, if it is false,
   ///				it monitors only the specified directory
   ///  \lparam		filter filter conditions that satisfy a change notification wait
   ///				can take values described by enum filter
   file_change_event (::object * pobject, const char * path, bool watchsubtree, u32 filter);

   ///  \brief		destructor
   ~file_change_event();


   virtual bool lock(const duration & durationTimeout = duration::infinite());

   using sync::unlock;
   virtual bool unlock();


   ///  \brief		waits for an file notification forever
   virtual sync_result wait ();

   ///  \brief		waits for an file notification for a specified time
   ///  \lparam		duration time period to wait for an file notification
   ///  \return	waiting action result as sync_result
   virtual sync_result wait (const duration& duration);

   ///  \brief		requests that the operating system signal a change
   ///				notification handle the next time it detects an appropriate
   ///				change
   bool next ();

   ///  \brief		stops change notification handle monitoring
   void close ();

};



#endif


