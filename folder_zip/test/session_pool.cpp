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

   pool.reconcile(3);

   auto please4 = pool.acquire(pmemory1);
   auto please5 = pool.acquire(pmemory1);
   auto please6 = pool.acquire(pmemory2);

   pool.reconcile(1);

   please4.release();
   please5.release();

   if (pool.session_count() != 1 || pool.active_count() != 1)
   {

      return 5;

   }

   ::std::promise < void > promiseResizeStarted;
   auto futureResizeStarted = promiseResizeStarted.get_future();
   ::std::promise < void > promiseResizeAcquired;
   auto futureResizeAcquired = promiseResizeAcquired.get_future();

   ::std::thread resizeWaiter([&]
      {

         promiseResizeStarted.set_value();

         auto please7 = pool.acquire(pmemory1);

         promiseResizeAcquired.set_value();

      });

   futureResizeStarted.wait();

   if (futureResizeAcquired.wait_for(::std::chrono::milliseconds(100)) != ::std::future_status::timeout)
   {

      resizeWaiter.join();

      return 6;

   }

   please6.release();

   if (futureResizeAcquired.wait_for(::std::chrono::seconds(2)) != ::std::future_status::ready)
   {

      resizeWaiter.detach();

      return 7;

   }

   resizeWaiter.join();

   pool.reconcile(4);

   auto please8 = pool.acquire(pmemory1);
   auto please9 = pool.acquire(pmemory1);
   auto please10 = pool.acquire(pmemory2);
   auto please11 = pool.acquire(pmemory2);

   if (pool.session_count() != 4 || pool.active_count() != 4)
   {

      return 8;

   }

   return 0;

}
