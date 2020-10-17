/**
* \brief	Session independent waitables
*/
#pragma once




//namespace multithreading
//{

/// constant representing infinite time
//const boost::posix_time::time_duration InfiniteTime = boost::posix_time::time_duration(boost::date_time::pos_infin);
// use INFINITE

/// constant representing zero time
//const boost::posix_time::time_duration ZeroTime = boost::posix_time::time_duration();
// use 0

/// This class represents results of waiting actions.
class CLASS_DECL_ACME sync_result
{
public:
   enum e_result : ::index
   {
      result_abandon0 = -10,		/// waiting abandoned because thread stopped
      // place additional failure codes here
      result_error = -3,		/// waiting error
      result_bad_thread = -2,		/// thread not found?
      result_timeout = -1,		/// timeout occured
      result_event0 = 0,		/// signaled

   };
   /// Internal member holding the result of the last waiting action
   union
   {

      e_result                 m_eresult;
      ::index                  m_iEvent;

   };


public:
//#if defined(WIN32) || defined(WIN64)
   ///  \brief		constructor with result value and matter ::count passed (Windows only)
   ///  \lparam		value waiting result value as passed by Windows API function
   ///  \lparam		objectCount number of items in event_collection
   explicit sync_result(u32 value, ::count objectCount = 1);
//#endif
   ///  \brief		constructor with result value passed
   ///  \lparam		value waiting result value as passed by Windows API function
   explicit sync_result(i32 iEvent)
      : m_iEvent(iEvent)
   {}

   sync_result(e_result eresult)
      : m_eresult(eresult)
   {}

   ///  \brief		default constructor
   sync_result()
      : m_eresult(result_error)
   {}

   ///  \brief		checks if last result == Abandon0
   ///  \return	true if last result == Abandon0
   inline bool abandoned() const;

   ///  \brief		returns index of abandoned thread
   ///  \return	abandoned thread index
   inline ::index abandoned_index() const;

   ///  \brief		checks if last result == Failure
   ///  \return	true if last result == Failure
   inline bool error() const;

   ///  \brief		checks if last result == BadThread
   ///  \return	true if last result == BadThread
   inline bool bad_thread() const;

   ///  \brief		checks if last result == Timeout
   ///  \return	true if last result == Timeout
   inline bool timeout() const;

   ///  \brief		checks if last result == Event0
   ///  \return	true if last result == Event0
   inline bool signaled() const;

   inline bool succeeded() const;

   inline bool failed() const { return !succeeded(); }

   operator bool() const { return succeeded(); }

   bool operator !() const { return failed(); }


   ///  \brief		returns index of signaled thread
   ///  \return	signaled thread index
   inline ::index signaled_index() const;

};

