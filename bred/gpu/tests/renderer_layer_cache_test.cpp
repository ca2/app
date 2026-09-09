#include "../renderer_layer_cache.h"
#include <memory>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iterator>
#include <string>

static void require(bool condition, const char * message)
{
   if (!condition) { std::fprintf(stderr, "%s\n", message); std::exit(1); }
}

struct renderer { int id; };
struct layer
{
   renderer * owner;
   // Models the context permanently captured when native command buffers are created.
   renderer * commandBufferOwner;
};

int main()
{
   renderer continuum{1}, switcher{2}, skybox{5}, ui{0};
   gpu::renderer_layer_cache<renderer *, std::shared_ptr<layer>> cache;
   auto acquire = [&](renderer * owner, int occurrence = 0)
   {
      return cache.acquire(owner, occurrence, [&]()
      { return std::make_shared<layer>(layer{owner, owner}); });
   };
   const auto mainLayer = acquire(&continuum);
   const auto switchLayer = acquire(&switcher);
   const auto skyLayer = acquire(&skybox);
   const auto uiFirst = acquire(&ui);
   const auto uiSecond = acquire(&ui, 1);
   require(mainLayer != switchLayer && mainLayer != skyLayer, "Tabs must not share a native layer");
   require(uiFirst != uiSecond, "Two layers from one renderer must stay distinct");

   for (int frame = 0; frame < 1000; ++frame)
   {
      renderer * order[] = {&continuum, &switcher, &skybox};
      for (int slot = 0; slot < 3; ++slot)
      {
         auto owner = order[(slot + frame) % 3];
         const auto selected = acquire(owner);
         require(selected->commandBufferOwner == owner, "Command buffer belongs to a previous tab");
      }
      require(acquire(&continuum) == mainLayer && acquire(&skybox) == skyLayer,
         "Returning to a tab must reuse its own layer");
   }
   require(cache.size() == 5, "Tab switching must not grow the cache per frame/global slot");
   auto heldInFlight = mainLayer;
   require(heldInFlight->commandBufferOwner == &continuum, "Switching must not mutate in-flight owners");

   std::ifstream source("source/app/bred/gpu/window_attachment.cpp");
   require(source.good(), "Run from SceneFoundry main workspace");
   const std::string text{std::istreambuf_iterator<char>(source), {}};
   require(text.find("m_rendererlayercache.acquire(pgpurenderer, occurrence,") != std::string::npos,
      "Production layer allocation must use the owner-aware cache");
   require(text.find("previous->m_pgpurenderer == pgpurenderer") != std::string::npos,
      "Layer occurrence must be counted per renderer");
   std::ifstream layerSource("source/app/bred/gpu/layer.cpp");
   require(layerSource.good(), "Layer source missing");
   const std::string layerText{std::istreambuf_iterator<char>(layerSource), {}};
   require(layerText.find("GPU layer cannot be reassigned to a different renderer") != std::string::npos,
      "Cross-renderer layer reinitialization must be rejected");
   require(layerText.find("GPU layer command buffer belongs to a different renderer") != std::string::npos,
      "Stale command-buffer ownership must not silently submit");
   std::puts("Renderer-owned layer cache passed: tab reordering, multiple UI layers, stable reuse and in-flight ownership.");
}
