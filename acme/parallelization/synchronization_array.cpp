#include "framework.h"
#include "acme/operating_system.h"


#ifdef PARALLELIZATION_PTHREAD


#include "acme/node/operating_system/ansi/_pthread.h"


#endif


synchronization_array::synchronization_array()
{

}


synchronization_array::synchronization_array(const ::synchronization_array & array) :
   matter(array),
#ifdef WINDOWS
   m_hsyncaCache(array.m_hsyncaCache),
#endif
   m_synchronizationa(array.m_synchronizationa)
{

#ifdef WINDOWS
   memcpy(m_byteaSyncIndex, array.m_byteaSyncIndex, sizeof(m_byteaSyncIndex));
#endif

}


synchronization_array::~synchronization_array()
{

}


synchronization_array & synchronization_array::operator = (const synchronization_array & synca)
{

   if(this != &synca)
   {

#ifdef WINDOWS
      m_hsyncaCache = synca.m_hsyncaCache;
      memcpy(&m_byteaSyncIndex, synca.m_byteaSyncIndex, sizeof(m_byteaSyncIndex));
#endif
      m_synchronizationa = synca.m_synchronizationa;

   }

   return *this;

}


void	synchronization_array::clear()
{

   m_synchronizationa.clear();
#ifdef WINDOWS
   m_hsyncaCache.clear();
#endif

}


::count synchronization_array::size() const
{

   return m_synchronizationa.get_size();

}


bool synchronization_array::is_empty() const
{

   return m_synchronizationa.is_empty();

}


bool synchronization_array::add_item(synchronization_object * psync)
{

   if (m_synchronizationa.size() >= MAXIMUM_WAIT_OBJECTS)
   {

      return false;

   }

#ifdef WINDOWS

   auto hsync = psync->hsync();

   if (hsync != nullptr)
   {

      m_byteaSyncIndex[m_hsyncaCache.get_size()] = (byte) m_synchronizationa.get_size();

      m_hsyncaCache.add(hsync);

   }

#endif

   m_synchronizationa.add(psync);

   return true;

}




bool synchronization_array::add(const synchronization_array& synca)
{

#ifdef WINDOWS

   if (m_hsyncaCache.size() + synca.m_hsyncaCache.get_size() > MAXIMUM_WAIT_OBJECTS)
   {

      return false;

   }

#endif

   for (auto& psync : synca.m_synchronizationa)
   {

      add_item(psync);

   }

   return true;

}


void synchronization_array::erase(class synchronization_object * psync)
{

   m_synchronizationa.erase(psync);

#ifdef WINDOWS

   auto hsync = psync->hsync();

   if (hsync != nullptr)
   {

      m_hsyncaCache.erase(hsync);

   }

#endif

}


void synchronization_array::erase(index index)
{

   if (index >= m_synchronizationa.size())
   {

      __throw(error_range, "synchronization_array::erase: index out of bounds");

   }

   synchronization_object* psync = m_synchronizationa[index];

   erase(psync);

}


::e_status synchronization_array::wait()
{

   return wait(duration::infinite());

}


::e_status synchronization_array::wait(const class ::wait & wait, bool bWaitForAll, ::u32 uWakeMask)
{

   if (is_empty())
   {

      return error_failed;

   }

#ifdef WINDOWS

   u32 windowsWaitResult;

#if !defined(_UWP)

   if (uWakeMask)
   {

      windowsWaitResult = ::MsgWaitForMultipleObjectsEx((u32)m_hsyncaCache.size(), m_hsyncaCache.get_data(), wait, uWakeMask, bWaitForAll ? MWMO_WAITALL : 0);

   }
   else

#endif

   {

      ::u32 uCount = (u32)m_hsyncaCache.size();

      auto psynca = m_hsyncaCache.get_data();

      windowsWaitResult = ::WaitForMultipleObjects(uCount, psynca, bWaitForAll, wait);

   }

   return windows_wait_result_to_status(windowsWaitResult);
   
#else

   for(auto & psync : m_synchronizationa)
   {

      psync->init_wait();

   }

//   auto start = ::duration::now();

   bool FoundExternal=false;

   ::e_status estatus;

//   ::duration durationWaitNow;

//   do
//   {

//      if(duration.is_infinite())
//      {
//
//         durationWaitNow.Infinite();
//
//      }
//      else
//      {
//
//         durationWaitNow = start.elapsed() - duration;
//
//         if (durationWaitNow <= ::duration(0))
//         {
//
//            result = e_synchronization_result_timed_out;
//
//            break;
//
//         }
//
//      }

//      do
      {


#if !defined(_UWP)
         if (uWakeMask)
         {

            estatus = ::MsgWaitForMultipleObjectsEx((::u32) synchronization_object_count(), synchronization_object_data(), wait, QS_ALLEVENTS, bWaitForAll ? MWMO_WAITALL : 0);

         }
         else
#endif
         {

            estatus = ::WaitForMultipleObjectsEx((::u32) synchronization_object_count(), synchronization_object_data(), bWaitForAll, wait, true);

         }

      }
//      while (result == e_synchronization_result_io_completion);

//   }
//   while (result == e_synchronization_result_timed_out);

   return estatus;

#endif

}


::e_status synchronization_array::contains(const ::e_status & result) const
{

   __throw(todo);

   //if ( !result.abandoned() && !result.signaled() )
   //   __throw(range_error("no matter signaled"));

   //index position = result.abandoned() ? result.abandoned_index() : result.signaled_index();

   //position = maximum(0)
   //for ( ++position; position<m_synchronizationa.get_size(); ++position )
   //{
   //   if(!m_waitableelementa[position].m_psynccallback)
   //   {
   //      i32 res = ::WaitForSingleObjectEx(m_synchronizationa[position], 0, false);
   //      if ( res == WAIT_TIMEOUT )
   //         continue;
   //      return synchronization_result( static_cast<i32>(position), m_synchronizationa.get_size() );
   //   }
   //}

   //return synchronization_result( e_synchronization_result_error );

   return error_failed;

}



