#pragma once

namespace parallelization
{

   class fast_critical_section_impl;

   /// Base semantics: in-process, non-recursive, exclusive locking.
   class CLASS_DECL_ACME fast_critical_section
   {
   public:

      fast_critical_section_impl *m_pimpl;

      fast_critical_section() noexcept;
      fast_critical_section(const fast_critical_section &) = delete;
      fast_critical_section &operator=(const fast_critical_section &) = delete;
      ~fast_critical_section() noexcept;

      void lock() noexcept;
      bool try_lock() noexcept;
      void unlock() noexcept;
   };

} // namespace parallelization
