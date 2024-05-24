//
//  memory/_.h
//  acid
//
//  Create by camilo on 2023-11-23 06:34 <3ThomasBorregaardSoerensen!!
//
#pragma once


namespace heap
{

//
//   enum enum_allocator
//   {
//
//      e_allocator_system,
//      e_allocator_default,
//      e_allocator_memory,
//      e_allocator_c,
//      e_allocator_a2,
//
//      e_allocator_count,
//
//   };
//
//
//   enum enum_memory
//   {
//
//      e_memory_main,
//      e_memory_secondary,
//      e_memory_array,
//      e_memory_property,
//      e_memory_string,
//
//      e_memory_count,
//
//   };
//
//


   class heap;
   class allocator;
   class memory;
   
   
   class management;


   template < typename TYPE >
   class counter;


} // namespace heap
//
//
//



CLASS_DECL_ACID void increment_particle_counter(::particle * pparticle);


CLASS_DECL_ACID void decrement_particle_counter(::particle * pparticle);

