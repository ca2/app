// Created by camilo on 2023-11-24 00:10 <3ThomasBorregaardSorensen!!
#pragma once


namespace heap
{


   enum enum_memory
   {

      e_memory_main,
      e_memory_secondary,
      e_memory_array,
      e_memory_property,
      e_memory_string,

      e_memory_count,

   };

   enum enum_allocator
   {

      e_allocator_system,
      e_allocator_default,
      e_allocator_memory,
      e_allocator_malloc,
      e_allocator_a2,

      e_allocator_count,

   };

   enum enum_heap
   {

      e_heap_default,

      e_heap_count,

   };


} // namespace heap



struct default_t {};


