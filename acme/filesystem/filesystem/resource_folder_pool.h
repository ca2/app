#pragma once


#include "acme/filesystem/file/folder.h"
#include "acme/parallelization/parallelization.h"
#include "acme/prototype/prototype/memory_base.h"
#include <memory>
#include <vector>


class resource_folder_pool;
struct resource_folder_pool_entry;


class CLASS_DECL_ACME resource_folder_lease
{
public:


   resource_folder_pool *       m_ppool = nullptr;
   resource_folder_pool_entry * m_pentry = nullptr;
   ::pointer < ::folder >       m_pfolder;


   resource_folder_lease() = default;
   resource_folder_lease(
      resource_folder_pool * ppool,
      resource_folder_pool_entry * pentry,
      const ::pointer < ::folder > & pfolder);
   resource_folder_lease(const resource_folder_lease &) = delete;
   resource_folder_lease & operator=(const resource_folder_lease &) = delete;
   resource_folder_lease(resource_folder_lease && lease) noexcept;
   resource_folder_lease & operator=(resource_folder_lease && lease) noexcept;
   ~resource_folder_lease();


   ::folder * get() const;
   ::folder * operator->() const;
   explicit operator bool() const;
   void release();


};


struct resource_folder_pool_entry
{


   ::pointer < memory_base > m_pmemory;
   ::pointer < ::folder >    m_pfolder;
   bool                      m_bInUse = false;


};


class CLASS_DECL_ACME resource_folder_pool
{
public:


   ::parallelization::mutex m_mutex;
   ::parallelization::condition_payload m_conditionpayload;
   ::std::vector < ::std::unique_ptr < resource_folder_pool_entry > > m_entrya;
   ::collection::count m_countActive = 0;
   ::collection::count m_countDesiredMaximum = 8;


   resource_folder_lease acquire(
      memory_base * pmemory,
      const ::function < ::pointer < ::folder >() > & functionCreateFolder);
   void return_to_pool(resource_folder_pool_entry * pentry);
   void reconcile(::collection::count maximum);
   ::collection::count folder_count();
   ::collection::count active_count();


protected:


   void trim_idle_entries_while_locked();
   resource_folder_pool_entry * find_idle_matching_memory_while_locked(memory_base * pmemory);
   resource_folder_pool_entry * find_any_idle_entry_while_locked();
   resource_folder_lease lease_entry_while_locked(resource_folder_pool_entry * pentry);


};
