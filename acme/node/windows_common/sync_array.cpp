#include "framework.h"
#include "acme/os/_os.h"


sync_array::sync_array()
{

}


sync_array::sync_array(const ::sync_array & array) :
   matter(array),
   m_hsyncaCache(array.m_hsyncaCache),
   m_synca(array.m_synca)
{

   memcpy(m_byteaSyncIndex, array.m_byteaSyncIndex, sizeof(m_byteaSyncIndex));

}


sync_array::~sync_array()
{

}


sync_array & sync_array::operator = (const sync_array & synca)
{

   if(this != &synca)
   {

      m_hsyncaCache = synca.m_hsyncaCache;
      memcpy(&m_byteaSyncIndex, synca.m_byteaSyncIndex, sizeof(m_byteaSyncIndex));
      m_synca = synca.m_synca;

   }

   return *this;

}


void	sync_array::clear()
{

   m_synca.clear();

   m_hsyncaCache.clear();

}


::count sync_array::size() const
{

   return m_synca.get_size();

}


bool sync_array::is_empty() const
{

   return m_synca.is_empty();

}


bool sync_array::add_item(sync * psync)
{

   if (m_synca.size() >= MAXIMUM_WAIT_OBJECTS)
   {

      return false;

   }

   HSYNC hsync = psync->hsync();

   if (hsync != nullptr && hsync != INVALID_HSYNC_VALUE)
   {

      m_byteaSyncIndex[m_hsyncaCache.get_size()] = (byte) m_synca.get_size();

      m_hsyncaCache.add(hsync);

   }

   m_synca.add(psync);


   return true;

}




bool sync_array::add(const sync_array& synca)
{

   if (m_hsyncaCache.size() + synca.m_hsyncaCache.get_size() > MAXIMUM_WAIT_OBJECTS)
   {

      return false;

   }

   for (auto& psync : synca.m_synca)
   {

      add_item(psync);

   }

   return true;

}


void sync_array::remove(class sync * psync)
{

   m_synca.remove(psync);

   HSYNC hsync = psync->hsync();

   if (hsync != nullptr && hsync != INVALID_HSYNC_VALUE)
   {

      m_hsyncaCache.remove(hsync);

   }

}


void sync_array::remove(index index)
{

   if (index >= m_synca.size())
   {

      __throw(range_error("sync_array::remove: index out of bounds"));

   }

   sync* psync = m_synca[index];

   remove(psync);

}


void sync_array::wait()
{

   wait(true, duration::infinite());

}


sync_result sync_array::wait(const duration & duration)
{

   return wait(false, duration);

}


sync_result sync_array::wait(bool waitForAll, const duration & duration, bool bWaitMessageQueue)
{

   if (is_empty())
   {

      return sync_result(sync_result::result_error);

   }

   u32 winResult;

   if (m_synca.size() == m_hsyncaCache.size())
   {

#ifdef WINDOWS_DESKTOP

      if (bWaitMessageQueue)
      {

         auto millis = duration.u32_millis();

         winResult = ::MsgWaitForMultipleObjectsEx((u32)m_hsyncaCache.size(), m_hsyncaCache.get_data(), millis, QS_ALLEVENTS, waitForAll ? MWMO_WAITALL : 0);

      }
      else
#endif
      {

         auto millis = duration.u32_millis();

         ::u32 uCount = (u32)m_hsyncaCache.size();

         auto psynca = m_hsyncaCache.get_data();

         winResult = ::WaitForMultipleObjectsEx(uCount, psynca, waitForAll, millis, bWaitMessageQueue);

      }

      return sync_result(winResult, m_hsyncaCache.size());

   }


   for(auto & psync : m_synca)
   {

      psync->init_wait();

   }

   auto start = ::millis::now();

   bool FoundExternal=false;

   do
   {

      if (start.elapsed() > duration)
      {

         winResult = WAIT_TIMEOUT;

      }

      do
      {

#ifdef WINDOWS_DESKTOP
         if (bWaitMessageQueue)
         {

            winResult = ::MsgWaitForMultipleObjectsEx((u32)m_hsyncaCache.size(), m_hsyncaCache.get_data(),  __os(duration - start.elapsed()), QS_ALLEVENTS, waitForAll ? MWMO_WAITALL : 0);

         }
         else
#endif
         {

            winResult = ::WaitForMultipleObjectsEx((u32)m_hsyncaCache.size(), m_hsyncaCache.get_data(), waitForAll, __os(duration - start.elapsed()), true);

         }

      }
      while (winResult == WAIT_IO_COMPLETION);

      // TODO

      //if(m_synca.has_element() && winResult!=WAIT_TIMEOUT && winResult!=WAIT_FAILED)
      //{

      //   sync_result result=sync_result(winResult,m_synca.size());

      //   if(waitForAll)
      //   {
      //
      //      for (auto& psync : m_synca)
      //      {

      //         psync->wait();

      //      }

      //   }
      //   else
      //   {

      //      index position = result.abandoned() ? result.abandoned_index() : result.signaled_index();

      //      position = maximum(0, position- m_hsynca.get_size());

      //      m_synca[position]->wait();

      //      for ( ++position; position<m_synca.size(); ++position )
      //      {
      //         if(m_waitableelementa[position].m_psynccallback)
      //         {
      //            i32 res = ::WaitForSingleObjectEx(m_synca[position], 0, false);

      //            if ( res != WAIT_TIMEOUT )
      //               m_waitableelementa[position].m_psynccallback->on_sync(m_waitableelementa[position].m_psync);
      //         }
      //         else if(!FoundExternal)
      //         {
      //            i32 res = ::WaitForSingleObjectEx(m_synca[position], 0, false);

      //            if ( res != WAIT_TIMEOUT )
      //            {
      //               winResult= (u32) (res + position);
      //               FoundExternal=true;
      //            }
      //         }
      //      }
      //   }
      //}
      //else if(m_countCallback==0)
      //   FoundExternal=true;

   }
   while (winResult != WAIT_TIMEOUT && winResult != WAIT_FAILED);
   //while (winResult!=WAIT_TIMEOUT && winResult!= WAIT_FAILED && FoundExternal==false);

   ////MBO: remove events to avoid double signalization
   //comparable_array < waitable_element >::iterator it;
   //for (it = m_waitableelementa.begin(); it != m_waitableelementa.end(); ++it)
   //   (*it).m_psync->exit_wait();

   return sync_result(winResult,m_hsyncaCache.size());

}


sync_result sync_array::contains( const sync_result& result ) const
{

   throw todo();

   //if ( !result.abandoned() && !result.signaled() )
   //   __throw(range_error("no matter signaled"));

   //index position = result.abandoned() ? result.abandoned_index() : result.signaled_index();

   //position = maximum(0)
   //for ( ++position; position<m_synca.get_size(); ++position )
   //{
   //   if(!m_waitableelementa[position].m_psynccallback)
   //   {
   //      i32 res = ::WaitForSingleObjectEx(m_synca[position], 0, false);
   //      if ( res == WAIT_TIMEOUT )
   //         continue;
   //      return sync_result( static_cast<i32>(position), m_synca.get_size() );
   //   }
   //}

   //return sync_result( sync_result::result_error );

}


