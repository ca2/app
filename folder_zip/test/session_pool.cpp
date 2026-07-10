#include "folder_zip/framework.h"
#include "folder_zip/session.h"
#include "acme/prototype/prototype/read_only_memory.h"
#include <atomic>
#include <chrono>
#include <future>
#include <thread>


namespace
{


   constexpr ::u8 g_zip[] =
   {
      0x50, 0x4b, 0x03, 0x04, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x45, 0x33, 0xea, 0x5c, 0xf1, 0x86,
      0x6c, 0x7a, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x6f, 0x6e,
      0x65, 0x2e, 0x74, 0x78, 0x74, 0x6f, 0x6e, 0x65, 0x50, 0x4b, 0x01, 0x02, 0x14, 0x00, 0x14, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x45, 0x33, 0xea, 0x5c, 0xf1, 0x86, 0x6c, 0x7a, 0x03, 0x00, 0x00, 0x00,
      0x03, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x6f, 0x6e, 0x65, 0x2e, 0x74, 0x78, 0x74, 0x50, 0x4b, 0x05,
      0x06, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x35, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00,
      0x00, 0x00, 0x00,
   };


} // namespace


int main()
{

   ::pointer < read_only_memory > pmemory1;
   ::pointer < read_only_memory > pmemory2;

   pmemory1 = ___new read_only_memory(g_zip, sizeof(g_zip));
   pmemory2 = ___new read_only_memory(g_zip, sizeof(g_zip));

   ::folder_zip::session_pool pool;

   pool.reconcile(2);

   auto please1 = pool.acquire(pmemory1);
   auto please2 = pool.acquire(pmemory1);

   if (pool.session_count() != 2 || pool.active_count() != 2)
   {

      return 1;

   }

   ::std::promise < void > promiseStarted;
   auto futureStarted = promiseStarted.get_future();
   ::std::promise < void > promiseAcquired;
   auto futureAcquired = promiseAcquired.get_future();

   ::std::thread waiter([&]
      {

         promiseStarted.set_value();

         auto please3 = pool.acquire(pmemory2);

         promiseAcquired.set_value();

      });

   futureStarted.wait();

   if (futureAcquired.wait_for(::std::chrono::milliseconds(100)) != ::std::future_status::timeout)
   {

      waiter.join();

      return 2;

   }

   please1.release();

   if (futureAcquired.wait_for(::std::chrono::seconds(2)) != ::std::future_status::ready)
   {

      waiter.detach();

      return 3;

   }

   waiter.join();
   please2.release();

   pool.reconcile(1);

   if (pool.session_count() != 1 || pool.active_count() != 0)
   {

      return 4;

   }

   return 0;

}
