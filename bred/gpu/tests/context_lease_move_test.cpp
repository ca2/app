#include "bred/platform.h"
#include "bred/gpu/context_lease.h"
#include "bred/gpu/device.h"

// Exercise the production lease with a pool stand-in; no native GPU is needed.
class lease_test_device : public ::gpu::device
{
public:
   int m_returns = 0;
   bool m_lastDamaged = false;
   ::gpu::context * m_lastContext = nullptr;

   void return_gpu_context(::pointer<::gpu::context> context, bool damaged) override
   {
      ++m_returns;
      m_lastContext = context;
      m_lastDamaged = damaged;
   }
};

int main()
{
   auto device = allocateø lease_test_device;
   auto first = allocateø ::gpu::context;
   auto second = allocateø ::gpu::context;

   {
      ::gpu::context_lease source(device, first, false);
      source.mark_damaged();
      ::gpu::context_lease moved(::transfer(source));
      if (moved.m_pdevice != device || source.m_pdevice) return 1;
      source.close();
      if (device->m_returns != 0) return 2;
      moved.close();
      moved.close();
      if (device->m_returns != 1 || device->m_lastContext != first || !device->m_lastDamaged) return 3;
   }

   {
      ::gpu::context_lease destination(device, first, false);
      ::gpu::context_lease owned(device, second, true);
      destination = ::transfer(owned);
      if (device->m_returns != 2 || !destination.m_bOwned) return 4;
      destination.close();
      owned.close();
      if (device->m_returns != 2) return 5;
   }

   {
      ::gpu::context_lease destination(device, first, true);
      ::gpu::context_lease borrowed(device, second, false);
      destination = ::transfer(borrowed);
      if (destination.m_bOwned || device->m_returns != 2) return 6;
      destination.close();
      borrowed.close();
      if (device->m_returns != 3 || device->m_lastContext != second || device->m_lastDamaged) return 7;
   }

   return 0;
}
