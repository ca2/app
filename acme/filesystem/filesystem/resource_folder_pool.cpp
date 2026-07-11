#include "framework.h"
#include "resource_folder_pool.h"


resource_folder_lease::resource_folder_lease(
   resource_folder_pool * ppool,
   resource_folder_pool_entry * pentry,
   const ::pointer < ::folder > & pfolder) :
   m_ppool(ppool),
   m_pentry(pentry),
   m_pfolder(pfolder)
{

}


resource_folder_lease::resource_folder_lease(resource_folder_lease && lease) noexcept :
   m_ppool(lease.m_ppool),
   m_pentry(lease.m_pentry),
   m_pfolder(::transfer(lease.m_pfolder))
{

   lease.m_ppool = nullptr;
   lease.m_pentry = nullptr;

}


resource_folder_lease & resource_folder_lease::operator=(resource_folder_lease && lease) noexcept
{

   if (this != &lease)
   {

      release();

      m_ppool = lease.m_ppool;
      m_pentry = lease.m_pentry;
      m_pfolder = ::transfer(lease.m_pfolder);

      lease.m_ppool = nullptr;
      lease.m_pentry = nullptr;

   }

   return *this;

}


resource_folder_lease::~resource_folder_lease()
{

   release();

}


::folder * resource_folder_lease::get() const
{

   return m_pfolder.m_p;

}


::folder * resource_folder_lease::operator->() const
{

   return get();

}


resource_folder_lease::operator bool() const
{

   return get() != nullptr;

}


void resource_folder_lease::release()
{

   auto ppool = m_ppool;
   auto pentry = m_pentry;

   m_ppool = nullptr;
   m_pentry = nullptr;
   m_pfolder.release();

   if (ppool && pentry)
   {

      ppool->return_to_pool(pentry);

   }

}


resource_folder_lease resource_folder_pool::acquire(
   memory_base * pmemory,
   const ::function < ::pointer < ::folder >() > & functionCreateFolder)
{

   if (!pmemory || !functionCreateFolder)
   {

      return {};

   }

   ::parallelization::unique_lock lock(m_mutex);

   for (;;)
   {

      trim_idle_entries_while_locked();

      if (auto pentry = find_idle_matching_memory_while_locked(pmemory))
      {

         return lease_entry_while_locked(pentry);

      }

      if ((::collection::count) m_entrya.size() < m_countDesiredMaximum)
      {

         auto pfolder = functionCreateFolder();

         if (!pfolder)
         {

            return {};

         }

         auto pentry = ::std::make_unique < resource_folder_pool_entry >();

         pentry->m_pmemory = pmemory;
         pentry->m_pfolder = pfolder;

         auto prawentry = pentry.get();

         m_entrya.push_back(::std::move(pentry));

         return lease_entry_while_locked(prawentry);

      }

      if (auto pentry = find_any_idle_entry_while_locked())
      {

         auto pfolder = functionCreateFolder();

         if (!pfolder)
         {

            return {};

         }

         pentry->m_pmemory = pmemory;
         pentry->m_pfolder = pfolder;

         return lease_entry_while_locked(pentry);

      }

      m_conditionpayload.wait(lock);

   }

}


void resource_folder_pool::return_to_pool(resource_folder_pool_entry * pentry)
{

   ::parallelization::unique_lock lock(m_mutex);

   if (!pentry || !pentry->m_bInUse)
   {

      return;

   }

   pentry->m_bInUse = false;
   m_countActive--;

   trim_idle_entries_while_locked();

   lock.unlock();
   m_conditionpayload.notify_one();

}


void resource_folder_pool::reconcile(::collection::count maximum)
{

   maximum = ::maximum((::collection::count) 1, maximum);

   ::parallelization::unique_lock lock(m_mutex);

   auto bIncreased = maximum > m_countDesiredMaximum;

   m_countDesiredMaximum = maximum;

   trim_idle_entries_while_locked();

   lock.unlock();

   if (bIncreased)
   {

      m_conditionpayload.notify_all();

   }

}


void resource_folder_pool::trim_idle_entries_while_locked()
{

   for (auto iterator = m_entrya.end();
      iterator != m_entrya.begin() && (::collection::count) m_entrya.size() > m_countDesiredMaximum;)
   {

      --iterator;

      if (!(*iterator)->m_bInUse)
      {

         iterator = m_entrya.erase(iterator);

      }

   }

}


resource_folder_pool_entry * resource_folder_pool::find_idle_matching_memory_while_locked(memory_base * pmemory)
{

   for (auto & pentry : m_entrya)
   {

      if (!pentry->m_bInUse && pentry->m_pmemory.m_p == pmemory)
      {

         return pentry.get();

      }

   }

   return nullptr;

}


resource_folder_pool_entry * resource_folder_pool::find_any_idle_entry_while_locked()
{

   for (auto & pentry : m_entrya)
   {

      if (!pentry->m_bInUse)
      {

         return pentry.get();

      }

   }

   return nullptr;

}


resource_folder_lease resource_folder_pool::lease_entry_while_locked(resource_folder_pool_entry * pentry)
{

   pentry->m_bInUse = true;
   m_countActive++;

   return {this, pentry, pentry->m_pfolder};

}


::collection::count resource_folder_pool::folder_count()
{

   ::parallelization::unique_lock lock(m_mutex);

   return (::collection::count) m_entrya.size();

}


::collection::count resource_folder_pool::active_count()
{

   ::parallelization::unique_lock lock(m_mutex);

   return m_countActive;

}
