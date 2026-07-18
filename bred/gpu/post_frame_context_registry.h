#pragma once


#include <exception>
#include <utility>
#include <vector>


namespace gpu
{


   template < typename CONTEXT_POINTER, typename LAYER_POINTER >
   class post_frame_context_registry
   {
   public:


      struct entry
      {

         CONTEXT_POINTER m_pcontext;
         LAYER_POINTER m_player;

      };


      using entry_array = std::vector<entry>;

      entry_array m_entrya;


      void clear()
      {

         m_entrya.clear();

      }


      void register_context(CONTEXT_POINTER pcontext, LAYER_POINTER player)
      {

         if (!pcontext)
         {

            return;

         }

         for (auto &entry : m_entrya)
         {

            if (entry.m_pcontext == pcontext)
            {

               entry.m_player = std::move(player);

               return;

            }

         }

         m_entrya.push_back({std::move(pcontext), std::move(player)});

      }


      entry_array take_entries()
      {

         return std::exchange(m_entrya, {});

      }


      static LAYER_POINTER find_layer(
         const entry_array &entrya,
         const CONTEXT_POINTER &pcontext)
      {

         for (const auto &entry : entrya)
         {

            if (entry.m_pcontext == pcontext)
            {

               return entry.m_player;

            }

         }

         return {};

      }


      template < typename GET_CURRENT_LAYER, typename SET_CURRENT_LAYER, typename END_CONTEXT >
      static void dispatch(
         entry_array entrya,
         const CONTEXT_POINTER &pcontextMain,
         GET_CURRENT_LAYER getCurrentLayer,
         SET_CURRENT_LAYER setCurrentLayer,
         END_CONTEXT endContext)
      {

         auto playerPrevious = getCurrentLayer();
         std::exception_ptr pexceptionFirst;

         auto invoke =
            [&](const CONTEXT_POINTER &pcontext, const LAYER_POINTER &player)
            {

               try
               {

                  setCurrentLayer(player);
                  endContext(pcontext);

               }
               catch (...)
               {

                  if (!pexceptionFirst)
                  {

                     pexceptionFirst = std::current_exception();

                  }

               }

            };

         for (const auto &entry : entrya)
         {

            if (entry.m_pcontext != pcontextMain)
            {

               invoke(entry.m_pcontext, entry.m_player);

            }

         }

         if (pcontextMain)
         {

            invoke(pcontextMain, find_layer(entrya, pcontextMain));

         }

         try
         {

            setCurrentLayer(playerPrevious);

         }
         catch (...)
         {

            if (!pexceptionFirst)
            {

               pexceptionFirst = std::current_exception();

            }

         }

         if (pexceptionFirst)
         {

            std::rethrow_exception(pexceptionFirst);

         }

      }


   };


   template < typename SAMPLE >
   void dispatch_cpu_sampling(bool bCpuBuffer, SAMPLE &&sample)
   {

      if (bCpuBuffer)
      {

         std::forward<SAMPLE>(sample)();

      }

   }


} // namespace gpu
