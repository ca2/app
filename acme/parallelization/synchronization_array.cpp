#include "framework.h"
#include "synchronization_array.h"
////#include "acme/exception/exception.h"
#include "acme/_operating_system.h"


#ifdef PARALLELIZATION_PTHREAD


#define MWMO_WAITALL        0x0001


#include "acme/operating_system/ansi/_pthread.h"
#include "acme/operating_system/posix/parallelization_pthread.h"


#endif


//#if defined(WINDOWS)
//
//
//
//
////::e_status MsgWaitForMultipleObjectsEx(::u32 dwSize, hsynchronization * synca, ::u32 tickTimeout, ::u32 dwWakeMask, ::u32 dwFlags);
//
////::e_status WaitForMultipleObjectsEx(::u32 dwSize, hsynchronization * synca, int_bool bWaitForAll, ::u32 tickTimeout, int_bool bAlertable);
//
//
//#endif


synchronization_array::synchronization_array()
{

}


synchronization_array::synchronization_array(const ::synchronization_array & array) :
   //matter(array),
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


bool synchronization_array::add_item(::particle * pparticle)
{

   if (m_synchronizationa.size() >= MAXIMUM_WAIT_OBJECTS)
   {

      return false;

   }

#ifdef WINDOWS

   auto hsynchronization = pparticle->m_hsynchronization;

   if (hsynchronization != nullptr)
   {

      m_byteaSyncIndex[m_hsyncaCache.get_size()] = (byte) m_synchronizationa.get_size();

      m_hsyncaCache.add(hsynchronization);

   }

#endif

   m_synchronizationa.add(pparticle);

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


void synchronization_array::erase(::particle * pparticle)
{

   m_synchronizationa.erase(pparticle);

#ifdef WINDOWS

   auto hsynchronization = pparticle->m_hsynchronization;

   if (hsynchronization != nullptr)
   {

      auto iIndex = m_hsyncaCache.erase(hsynchronization);

      ::memmove(&m_byteaSyncIndex[iIndex], &m_byteaSyncIndex[iIndex + 1], m_hsyncaCache.get_count() - 1);

   }

#endif

}


void synchronization_array::erase(index index)
{

   if (index >= m_synchronizationa.size())
   {

      throw ::exception(error_range, "synchronization_array::erase: index out of bounds");

   }

   auto pparticle = m_synchronizationa[index];

   erase_synchronization(pparticle);

}


::e_status synchronization_array::wait()
{

   return wait(time::infinite()) >= 0 ? ::success : ::error_failed;

}


::index synchronization_array::wait(const class time & timeWait, bool bWaitForAll, ::u32 uWakeMask)
{

   if (is_empty())
   {

      throw ::exception(error_failed);

   }

#ifdef WINDOWS

   u32 windowsWaitResult;

#if !defined(_UWP)

   if (uWakeMask)
   {

      windowsWaitResult = ::MsgWaitForMultipleObjectsEx((u32)m_hsyncaCache.size(), m_hsyncaCache.get_data(), ::windows::wait(timeWait), uWakeMask, bWaitForAll ? MWMO_WAITALL : 0);

   }
   else

#endif

   {

      ::u32 uCount = (u32)m_hsyncaCache.size();

      auto psynca = m_hsyncaCache.get_data();

      windowsWaitResult = ::WaitForMultipleObjects(uCount, psynca, bWaitForAll, ::windows::wait(timeWait));

   }

   auto estatus = ::windows::wait_result_status(windowsWaitResult);

#else

   for(auto & psync : m_synchronizationa)
   {

      psync->init_wait();

   }

//   auto start = ::time::now();

   bool FoundExternal=false;

   ::e_status estatus;

//   ::time timeWaitNow;

//   do
//   {

//      if(time.is_infinite())
//      {
//
//         timeWaitNow.Infinite();
//
//      }
//      else
//      {
//
//         timeWaitNow = start.elapsed() - time;
//
//         if (timeWaitNow <= ::time(0))
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
            
#if !defined(WINDOWS)
#define QS_ALLEVENTS 0xffffffffu
#endif

            estatus = ::MsgWaitForMultipleObjectsEx((::u32) synchronization_count(), synchronization_data(), timeWait, QS_ALLEVENTS, bWaitForAll ? MWMO_WAITALL : 0);

         }
         else
#endif
         {

            estatus = ::WaitForMultipleObjectsEx((::u32) synchronization_count(), synchronization_data(), bWaitForAll, timeWait, true);

         }

      }


//      while (result == e_synchronization_result_io_completion);

//   }
//   while (result == e_synchronization_result_timed_out);

   //return estatus;

#endif

   if (estatus == error_wait_timeout)
   {

      return -1;

   }
   else if (failed(estatus))
   {

      throw ::exception(estatus);

   }

   return (::index) (estatus.m_eenum - signaled_base);

}


void synchronization_array::contains(const ::e_status & result) const
{

   throw ::exception(todo);

   //if ( !result.abandoned() && !result.signaled() )
   //   throw ::exception(range_error("no matter signaled"));

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

   //return error_failed;

}



