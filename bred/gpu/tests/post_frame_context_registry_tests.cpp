#include "../post_frame_context_registry.h"

#include <cassert>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>


namespace
{


   struct fake_context
   {

      std::string m_strName;
      bool m_bThrow = false;

   };


   struct fake_layer
   {

      int m_iIdentifier = 0;

   };


   using context_pointer = std::shared_ptr<fake_context>;
   using layer_pointer = std::shared_ptr<fake_layer>;
   using registry = ::gpu::post_frame_context_registry<context_pointer, layer_pointer>;


   void test_registration_deduplicates_and_updates_latest_layer()
   {

      registry contextregistry;
      auto pcontextFirst = std::make_shared<fake_context>(fake_context{"first"});
      auto pcontextSecond = std::make_shared<fake_context>(fake_context{"second"});
      auto playerFirst = std::make_shared<fake_layer>(fake_layer{1});
      auto playerFirstLatest = std::make_shared<fake_layer>(fake_layer{2});
      auto playerSecond = std::make_shared<fake_layer>(fake_layer{3});

      contextregistry.register_context(pcontextFirst, playerFirst);
      contextregistry.register_context(pcontextSecond, playerSecond);
      contextregistry.register_context(pcontextFirst, playerFirstLatest);

      auto entrya = contextregistry.take_entries();

      assert(entrya.size() == 2);
      assert(entrya[0].m_pcontext == pcontextFirst);
      assert(entrya[0].m_player == playerFirstLatest);
      assert(entrya[1].m_pcontext == pcontextSecond);
      assert(contextregistry.take_entries().empty());

   }


   void test_dispatch_uses_first_use_order_and_calls_main_last()
   {

      registry contextregistry;
      auto pcontextFirst = std::make_shared<fake_context>(fake_context{"first"});
      auto pcontextMain = std::make_shared<fake_context>(fake_context{"main"});
      auto pcontextSecond = std::make_shared<fake_context>(fake_context{"second"});
      auto playerFirst = std::make_shared<fake_layer>(fake_layer{1});
      auto playerFirstLatest = std::make_shared<fake_layer>(fake_layer{4});
      auto playerMain = std::make_shared<fake_layer>(fake_layer{2});
      auto playerSecond = std::make_shared<fake_layer>(fake_layer{3});
      auto playerPrevious = std::make_shared<fake_layer>(fake_layer{99});
      auto playerCurrent = playerPrevious;
      std::vector<std::string> straCall;

      contextregistry.register_context(pcontextFirst, playerFirst);
      contextregistry.register_context(pcontextMain, playerMain);
      contextregistry.register_context(pcontextSecond, playerSecond);
      contextregistry.register_context(pcontextFirst, playerFirstLatest);

      registry::dispatch(
         contextregistry.take_entries(),
         pcontextMain,
         [&]() { return playerCurrent; },
         [&](const layer_pointer &player) { playerCurrent = player; },
         [&](const context_pointer &pcontext)
         {

            straCall.push_back(
               pcontext->m_strName + ":" + std::to_string(playerCurrent->m_iIdentifier));

         });

      assert((straCall == std::vector<std::string>{"first:4", "second:3", "main:2"}));
      assert(playerCurrent == playerPrevious);

   }


   void test_dispatch_attempts_all_contexts_and_rethrows_first_exception()
   {

      registry contextregistry;
      auto pcontextFirst = std::make_shared<fake_context>(fake_context{"first", true});
      auto pcontextSecond = std::make_shared<fake_context>(fake_context{"second", true});
      auto pcontextMain = std::make_shared<fake_context>(fake_context{"main", false});
      auto player = std::make_shared<fake_layer>(fake_layer{1});
      auto playerPrevious = std::make_shared<fake_layer>(fake_layer{99});
      auto playerCurrent = playerPrevious;
      std::vector<std::string> straCall;

      contextregistry.register_context(pcontextFirst, player);
      contextregistry.register_context(pcontextSecond, player);
      contextregistry.register_context(pcontextMain, player);

      try
      {

         registry::dispatch(
            contextregistry.take_entries(),
            pcontextMain,
            [&]() { return playerCurrent; },
            [&](const layer_pointer &playerSet) { playerCurrent = playerSet; },
            [&](const context_pointer &pcontext)
            {

               straCall.push_back(pcontext->m_strName);

               if (pcontext->m_bThrow)
               {

                  throw std::runtime_error(pcontext->m_strName);

               }

            });

         assert(false);

      }
      catch (const std::runtime_error &error)
      {

         assert(std::string(error.what()) == "first");

      }

      assert((straCall == std::vector<std::string>{"first", "second", "main"}));
      assert(playerCurrent == playerPrevious);

   }


   void test_unregistered_main_is_still_called_last()
   {

      registry contextregistry;
      auto pcontextFirst = std::make_shared<fake_context>(fake_context{"first"});
      auto pcontextMain = std::make_shared<fake_context>(fake_context{"main"});
      auto playerFirst = std::make_shared<fake_layer>(fake_layer{1});
      auto playerPrevious = std::make_shared<fake_layer>(fake_layer{99});
      auto playerCurrent = playerPrevious;
      std::vector<std::string> straCall;

      contextregistry.register_context(pcontextFirst, playerFirst);

      registry::dispatch(
         contextregistry.take_entries(),
         pcontextMain,
         [&]() { return playerCurrent; },
         [&](const layer_pointer &player) { playerCurrent = player; },
         [&](const context_pointer &pcontext)
         {

            straCall.push_back(pcontext->m_strName);

            if (pcontext == pcontextMain)
            {

               assert(!playerCurrent);

            }

         });

      assert((straCall == std::vector<std::string>{"first", "main"}));
      assert(playerCurrent == playerPrevious);

   }


   void test_cpu_sampling_policy()
   {

      int iSampleCount = 0;

      ::gpu::dispatch_cpu_sampling(false, [&]() { ++iSampleCount; });
      assert(iSampleCount == 0);

      ::gpu::dispatch_cpu_sampling(true, [&]() { ++iSampleCount; });
      assert(iSampleCount == 1);

   }


} // namespace


int main()
{

   test_registration_deduplicates_and_updates_latest_layer();
   test_dispatch_uses_first_use_order_and_calls_main_last();
   test_dispatch_attempts_all_contexts_and_rethrows_first_exception();
   test_unregistered_main_is_still_called_last();
   test_cpu_sampling_policy();

   return 0;

}
