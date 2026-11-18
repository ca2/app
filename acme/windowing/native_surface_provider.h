#pragma once

namespace acme::windowing
{
   // Generic exclusive buffer-presentation ownership. A renderer borrows the
   // native surface, claims it before submitting buffers, then releases it
   // after its native presentation objects have been destroyed.
   class CLASS_DECL_ACME native_surface_provider
   {
   public:
      virtual ~native_surface_provider() = default;
      virtual void acquire_external_presentation() = 0;
      virtual void release_external_presentation() = 0;
   };
}
