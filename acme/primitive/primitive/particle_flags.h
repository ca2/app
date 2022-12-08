// Created by camilo on 2022-11-30 02:50 <3ThomasBorregaardSorensen!!
#pragma once


struct PARTICLE_FLAGS
{
public:


   ::e_flag                            m_eflagElement;
   ::e_status                          m_estatus;


   [[nodiscard]] inline bool has_flag(enum_flag eflag) const { return (m_eflagElement & eflag) == eflag; }
   inline void set_flag(enum_flag eflag) { m_eflagElement = (enum_flag)((::u64)(m_eflagElement) | (::u64)(eflag)); }
   inline void set_flag(enum_flag eflag, bool bSet) { if (bSet) set_flag(eflag); else clear_flag(eflag); }
   inline void clear_flag(enum_flag eflag) { m_eflagElement = (enum_flag)((::u64)(m_eflagElement) & (~(::u64)(eflag))); }


   inline void set_ok_flag() { set_flag(e_flag_success); clear_flag(e_flag_timeout); clear_flag(e_flag_failure); }
   inline void set_nok(enum_flag estatusFailure = e_flag_failure) { clear_flag(e_flag_success); set_flag(estatusFailure); }
   inline void set_modified_flag(bool bModified = true) { set_flag(e_flag_changed, bModified); }


   inline void set_fail_flag() { set_flag(e_flag_failure); clear_flag(e_flag_success); }
   inline void set_timed_out_flag() { set_flag(e_flag_timeout); }
   inline void set_persistent_flag(bool bSet = true) { set_flag(e_flag_persist, bSet); }


   [[nodiscard]] inline bool has_ok_flag() const { return has_flag(e_flag_success); }
   [[nodiscard]] inline bool nok() const { return has_flag(e_flag_failure) || has_flag(e_flag_timeout); }
   [[nodiscard]] inline bool has_timed_out_flag() { return has_flag(e_flag_timeout); }
   [[nodiscard]] inline bool has_modified_flag() const { return has_flag(e_flag_changed); }
   [[nodiscard]] inline bool has_persistent_flag() const { return has_flag(e_flag_persist); }

   [[nodiscard]] inline bool has_shared_flag() const { return has_flag(e_flag_shared); }
   inline void set_shared_flag(bool bSet = true) { set_flag(e_flag_shared, bSet); }


   [[nodiscard]] inline bool has_finishing_flag() const { return has_flag(e_flag_finishing); }
   inline void set_finishing_flag() { set_flag(e_flag_finishing); }
   inline void clear_finishing_flag() { clear_flag(e_flag_finishing); }


   [[nodiscard]] inline bool has_acquired_flag() const { return has_flag(e_flag_acquired); }
   inline void set_acquired_flag() { set_flag(e_flag_acquired); }
   inline void clear_acquired_flag() { clear_flag(e_flag_acquired); }

   [[nodiscard]] inline bool has_own_synchronization_flag() const { return has_flag(e_flag_own_synchronization); }
   inline void set_own_synchronization_flag(bool bSet = true) { set_flag(e_flag_own_synchronization, bSet); }
   inline void clear_own_synchronization_flag() { clear_flag(e_flag_own_synchronization); }


   [[nodiscard]] inline bool has_already_exists_flag() const { return has_flag(e_flag_already_exists); }
   inline void set_already_exists_flag(bool bSet = true) { set_flag(e_flag_already_exists, bSet); }
   inline void clear_already_exists_flag() { clear_flag(e_flag_already_exists); }


   // [[nodiscard]] inline bool is_heap_allocated() const { return has_flag(e_flag_heap_allocated); }
   // inline void set_heap_allocated() { set_flag(e_flag_heap_allocated); }
   // inline void clear_heap_allocated() { clear_flag(e_flag_heap_allocated); }


   [[nodiscard]] inline bool has_destroying_flag() const { return has_flag(e_flag_destroying); }
   inline void set_destroying_flag() { set_flag(e_flag_destroying); }
   inline void clear_destroying_flag() { clear_flag(e_flag_destroying); }


   [[nodiscard]] inline bool has_storing_flag() const { return has_flag(e_flag_storing); }
   [[nodiscard]] inline bool has_loading_flag() const { return !has_storing_flag(); }


   inline void set_storing_flag() { set_flag(e_flag_storing); }
   inline void set_loading_flag() { clear_flag(e_flag_storing); }


   inline void defer_set_storing_flag() { if (!has_storing_flag()) set_storing_flag(); }
   inline void defer_set_loading_flag() { if (!has_loading_flag()) set_loading_flag(); }


   inline void set_statically_allocated_flag() { set_flag(e_flag_statically_allocated); }
   inline void set_verbose_flag(bool bVerbose = true) { set_flag(e_flag_verbose, bVerbose); }
   [[nodiscard]] inline bool has_verbose_flag() const { return has_flag(e_flag_verbose); }



   [[nodiscard]] inline bool has_read_only_flag() const { return has_flag(e_flag_read_only); }
   inline void set_read_only_flag() { set_flag(e_flag_read_only); }
   inline void clear_read_only_flag() { clear_flag(e_flag_read_only); }

   [[nodiscard]] inline bool has_owner_flag() const { return has_flag(e_flag_owner); }
   inline void set_owner_flag() { set_flag(e_flag_owner); }
   inline void clear_owner_flag() { clear_flag(e_flag_owner); }


   inline bool is_status_ok() const { return m_estatus; }
   inline bool has_failed_status() const { return !is_status_ok(); }


};



