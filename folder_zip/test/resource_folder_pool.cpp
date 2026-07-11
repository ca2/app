#include "acme/framework.h"
#include "acme/filesystem/filesystem/resource_folder_pool.h"
#include "acme/filesystem/file/folder.h"
#include "acme/prototype/prototype/read_only_memory.h"
#include <chrono>
#include <future>
#include <thread>


int main()
{

   constexpr ::u8 data1[]{1};
   constexpr ::u8 data2[]{2};

   ::pointer < read_only_memory > pmemory1(allocate_t{}, data1, sizeof(data1));
   ::pointer < read_only_memory > pmemory2(allocate_t{}, data2, sizeof(data2));

   ::resource_folder_pool pool;

   pool.reconcile(2);

   ::function < ::pointer < ::folder >() > functionCreateFolder = []
      {

         return ::pointer < ::folder >(allocate_t{});

      };

   auto please1 = pool.acquire(pmemory1, functionCreateFolder);
   auto please2 = pool.acquire(pmemory1, functionCreateFolder);

   if (!please1 || !please2 || pool.folder_count() != 2 || pool.active_count() != 2)
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

         auto please3 = pool.acquire(pmemory2, functionCreateFolder);

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

   pool.reconcile(3);

   auto please4 = pool.acquire(pmemory1, functionCreateFolder);
   auto please5 = pool.acquire(pmemory1, functionCreateFolder);
   auto please6 = pool.acquire(pmemory2, functionCreateFolder);

   pool.reconcile(1);

   please4.release();
   please5.release();

   if (pool.folder_count() != 1 || pool.active_count() != 1)
   {

      return 4;

   }

   please6.release();

   if (pool.folder_count() != 1 || pool.active_count() != 0)
   {

      return 5;

   }

   return 0;

}
