#pragma once

#include <vector>
#include <utility>

namespace gpu
{

   // Layer command buffers and native container objects belong to a renderer.
   // Draw-order indices are not stable owners when tabs/visibility change.
   template <typename RENDERER_POINTER, typename LAYER_POINTER>
   class renderer_layer_cache
   {
   public:
      template <typename FACTORY>
      LAYER_POINTER acquire(RENDERER_POINTER renderer, int occurrence, FACTORY && factory)
      {
         for (const auto & entry : m_entries)
            if (entry.renderer == renderer && entry.occurrence == occurrence)
               return entry.layer;

         auto layer = factory();
         m_entries.push_back({renderer, occurrence, layer});
         return layer;
      }

      size_t size() const { return m_entries.size(); }

   private:
      struct entry
      {
         RENDERER_POINTER renderer;
         int occurrence;
         LAYER_POINTER layer;
      };
      std::vector<entry> m_entries;
   };

}
