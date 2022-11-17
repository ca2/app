// Created by camilo on 2021-09-30 08:05 <3ThomasBorregaardS�rensen!!
#pragma once


enum enum_flag : u64
{


   e_flag_none,
   e_flag_success = 1 << 0,
   e_flag_timeout = 1 << 1,
   e_flag_failure = 1 << 2,
   e_flag_persist = 1 << 3,
   e_flag_factory = 1 << 4,
   e_flag_acquire = 1 << 6,
   e_flag_default = 1 << 7,
   e_flag_changed = 1 << 9,
   e_flag_heap_allocated = 1 << 10,
   e_flag_statically_allocated = 1 << 11,
   e_flag_finishing = 1 << 12,
   e_flag_destroying = 1 << 13,
   e_flag_processed = 1 << 14,
   e_flag_task_started = 1 << 15,
   e_flag_task_terminated = 1 << 16,
   e_flag_checking_children_task = 1 << 17,
   e_flag_check_children_task_post_quit = 1 << 18,
   e_flag_task_ready = 1 << 19,
   e_flag_data_struct = 1 << 20,
   e_flag_exited = 1 << 21,
   e_flag_storing = 1 << 22,
   e_flag_alertable_wait = 1 << 23,
   e_flag_verbose = 1 << 24,
   e_flag_acquired = 1 << 25,
   e_flag_own_synchronization = 1 << 26,
   e_flag_already_exists = 1 << 27,

   //e_object_none,
   //aaa_want_to_erase_object_locked = 1 << 10,
   //aaa_want_to_erase_object_shared = 1 << 11,
   //aaa_want_to_erase_object_read_only_link = 1 << 12,
   e_flag_log_disable = 1 << 28,
   e_flag_property_set_modified = 1 << 29,
   e_flag_default_io_exchange = 1 << 30,
   //e_object_alertable_wait = 1 << 16,
   e_flag_any_hook = 1ll << 31,
   //e_object_any_hook = 1 << 17,
   //e_object_any_update = (1 << 18) | e_object_any_hook,
   //e_object_composite = 1 << 19,
#if OBJECT_TYPE_COUNTER
   e_flag_object_type_counter = 1ll << 32,
#endif
   e_flag_synchronous = 1ll << 33,
   e_flag_shared = 1ll << 34,
   e_flag_read_only = 1ll << 35,
   e_flag_owner = 1ll << 35,

};



