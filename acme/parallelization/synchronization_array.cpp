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
////::e_status MsgWaitForMultipleObjectsEx(unsigned int dwSize, hsynchronization * synca, unsigned int tickTimeout, unsigned int dwWakeMask, unsigned int dwFlags);
//
////::e_status WaitForMultipleObjectsEx(unsigned int dwSize, hsynchronization * synca, int_bool bWaitForAll, unsigned int tickTimeout, int_bool bAlertable);
//
//
//#endif


synchronization_array::synchronization_array()
{

}


synchronization_array::synchronization_array(const ::synchronization_array & array) :
   m_subparticlea(array.m_subparticlea),
   m_hsynchronizationa(array.m_hsynchronizationa),
   m_uaIndexes(array.m_uaIndexes)
{

}


synchronization_array::~synchronization_array()
{

}


synchronization_array & synchronization_array::operator = (const synchronization_array & synca)
{

   if(this != &synca)
   {

      m_subparticlea = synca.m_subparticlea;
      m_hsynchronizationa = synca.m_hsynchronizationa;
      m_uaIndexes =  synca.m_uaIndexes;

   }

   return *this;

}


void	synchronization_array::clear()
{

   m_subparticlea.clear();
   m_hsynchronizationa.clear();

}


//::collection::count synchronization_array::size() const
//{
//
//   return m_subparticlea.get_size();
//
//}


//bool synchronization_array::is_empty() const
//{
//
//   return m_subparticlea.is_empty();
//
//}
//

bool synchronization_array::add_item(::subparticle * psubparticle)
{

   if (m_subparticlea.size() >= MAXIMUM_WAIT_OBJECTS)
   {

      return false;

   }

   if (!m_subparticlea.add_unique(psubparticle))
   {

      return false;

   }

   auto handle = psubparticle->get_synchronization_handle();

   if (handle != nullptr)
   {

      m_uaIndexes[m_hsynchronizationa.get_size()] = (unsigned char) m_subparticlea.get_size();

      m_hsynchronizationa.add(handle);

   }

   return true;

}


bool synchronization_array::add(const synchronization_array& synca)
{

#ifdef WINDOWS

   if (m_hsynchronizationa.size() + synca.m_hsynchronizationa.get_size() > MAXIMUM_WAIT_OBJECTS)
   {

      return false;

   }

#endif

   for (auto& psync : synca.m_subparticlea)
   {

      add_item(psync);

   }

   return true;

}


void synchronization_array::erase(::subparticle * psubparticle)
{

   m_subparticlea.erase(psubparticle);

   auto handle = psubparticle->get_synchronization_handle();

   if (handle != nullptr)
   {

      auto iIndex = m_hsynchronizationa.erase(handle);

      ::memory_transfer(&m_uaIndexes[iIndex], &m_uaIndexes[iIndex + 1], m_hsynchronizationa.get_count() - 1);

   }

}


void synchronization_array::erase(::collection::index index)
{

   if (index >= m_subparticlea.size())
   {

      throw ::exception(error_range, "synchronization_array::erase: index out of bounds");

   }

   auto sizeOld = (int) this->size();

   m_subparticlea.erase_at(index);
   m_hsynchronizationa.erase_at(index);
   m_uaIndexes.erase_at(index, sizeOld);

}


::e_status synchronization_array::wait()
{

   return wait(time::infinity()) >= 0 ? ::success : ::error_failed;

}


::e_status synchronization_array::wait(const class time & timeWait, bool bWaitForAll, unsigned int uWakeMask)
{

   if (is_empty() && !uWakeMask)
   {

      throw ::exception(error_failed);

   }

#ifdef WINDOWS

   unsigned int windowsWaitResult;

   unsigned int uCount = (unsigned int)m_hsynchronizationa.size();

#if !defined(UNIVERSAL_WINDOWS)

   if (uWakeMask)
   {

      windowsWaitResult = ::MsgWaitForMultipleObjectsEx((unsigned int)uCount, m_hsynchronizationa.get_data(), ::windows::wait(timeWait), uWakeMask, bWaitForAll ? MWMO_WAITALL : 0);

   }
   else

#endif

   {

      auto psynca = m_hsynchronizationa.get_data();

      windowsWaitResult = ::WaitForMultipleObjects(uCount, psynca, bWaitForAll, ::windows::wait(timeWait));

   }

   auto estatus = ::windows::wait_result_status(windowsWaitResult, (int) uCount);

#else

   for(auto & psync : m_subparticlea)
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


#if !defined(UNIVERSAL_WINDOWS)
         
         if (uWakeMask)
         {
            
//#if !defined(WINDOWS)
//#define QS_ALLEVENTS 0xffffffffu
//#endif

            estatus = ::MsgWaitForMultipleObjectsEx((unsigned int) size(), m_hsynchronizationa.data(), timeWait, QS_ALLEVENTS, bWaitForAll ? MWMO_WAITALL : 0);

         }
         else
#endif
         {

            estatus = ::WaitForMultipleObjectsEx((unsigned int) m_hsynchronizationa.size(), m_hsynchronizationa.data(), bWaitForAll, timeWait, true);

         }

      }


//      while (result == e_synchronization_result_io_completion);

//   }
//   while (result == e_synchronization_result_timed_out);

   //return estatus;

#endif

   //if (estatus == error_wait_timeout)
   //{

   //   return -1;

   //}
   //else if (estatus.failed())
   //{

   //   throw ::exception(estatus);

   //}

   //return (::collection::index) (estatus.m_eenum - signaled_base);

   return estatus;

}


void synchronization_array::unlock_item(::collection::index index)
{

   m_subparticlea[index]->unlock();

}


void synchronization_array::unlock_item(::collection::index index, int lCount, int * pPrevCount)
{

   m_subparticlea[index]->unlock(lCount, pPrevCount);

}


void synchronization_array::contains(const ::e_status & result) const
{

   throw ::exception(todo);

   //if ( !result.abandoned() && !result.signaled() )
   //   throw ::exception(range_error("no matter signaled"));

   //index position = result.abandoned() ? result.abandoned_index() : result.signaled_index();

   //position = maximum(0)
   //for ( ++position; position<m_subparticlea.get_size(); ++position )
   //{
   //   if(!m_waitableelementa[position].m_psynccallback)
   //   {
   //      int res = ::WaitForSingleObjectEx(m_subparticlea[position], 0, false);
   //      if ( res == WAIT_TIMEOUT )
   //         continue;
   //      return synchronization_result( static_cast<int>(position), m_subparticlea.get_size() );
   //   }
   //}

   //return synchronization_result( e_synchronization_result_error );

   //return error_failed;

}



