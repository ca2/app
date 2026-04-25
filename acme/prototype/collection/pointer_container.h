//
// Created by camilo on 2026-04-23 <3ThomasBorregaardSørensen!! and Mummi!!
//
#pragma once



// 1. Define a helper type trait
template<typename T, template<typename...> class Template>
struct is_specialization_of_t : ::false_type
{
};

template<template<typename...> class Template, typename... Args>
struct is_specialization_of_t<Template<Args...>, Template> : ::true_type
{
};

// 2. Wrap the trait in a concept
template<typename T, template<typename...> class Template>
concept is_specialization_of = is_specialization_of_t<std::decay_t<T>, Template>::payload;

// Example Usage:
//static_assert(is_specialization_of<array_base<int>, array_base>); // Passes
//static_assert(!is_specialization_of<int, array_base); // Fails

//// 1. Helper type trait to detect instantiation
//template<typename T, template<typename...> class Template>
//struct is_instantiation_of : std::false_type
//{
//};
//
//
//template<template<typename...> class Template, typename... Args>
//struct is_instantiation_of<Template<Args...>, Template> : std::true_type
//{
//};
//
//
//// 2. C++20 Concept using the trait
//template<typename T, template<typename...> class Template>
//concept InstantiationOf = is_instantiation_of<T, Template>::value;


//// Example Usage:
//void process_vector(InstantiationOf<std::vector> auto const &vec)
//{
//   // This function only accepts std::vector instantiations
//}


template < typename POINTER_CONTAINER >
concept prototype_pointer_container = is_specialization_of<typename POINTER_CONTAINER::BASE_PAYLOAD, ::pointer>;


template<prototype_pointer_container POINTER_CONTAINER>
void defer_destroy_and_release_each_pointer_payload_in_container(POINTER_CONTAINER &container)
{

   for (auto &p: container.payloads())
   {

      p.defer_destroy_and_release();

   }

}


template<prototype_pointer_container POINTER_CONTAINER>
void defer_destroy_and_release_each_payload_pointer_in_container_and_then_clear_it(POINTER_CONTAINER &container)
{

   defer_destroy_and_release_each_pointer_payload_in_container(container);

   container.clear();

}


template<typename TYPE>
class ø
{
public:

};


template < typename TYPE1, typename TYPE2, class PAIR = pair < TYPE1, ::pointer < TYPE2 > >, enum_allocate t_eallocate = e_allocate_normal >
using map_to_pointer_base = ::ø < pair_map_base < PAIR, t_eallocate > >;


template < typename TYPE1, typename TYPE2, class PAIR = pair < TYPE1, TYPE2 >, enum_allocate t_eallocate = e_allocate_normal >
using map_to_pointer = map_particle < map_to_pointer_base < TYPE1, TYPE2, PAIR, t_eallocate > >;






template<prototype_pointer_container POINTER_CONTAINER>
class ø<POINTER_CONTAINER> : virtual public POINTER_CONTAINER
{
public:


   using BASE_CONTAINER = POINTER_CONTAINER;


   using BASE_CONTAINER::BASE_CONTAINER;
   using BASE_CONTAINER::operator=;


   void _defer_destroy_and_release() { ::defer_destroy_and_release_each_pointer_payload_in_container(*this); }


   void defer_destroy_and_release()
   {

      ::defer_destroy_and_release_each_payload_pointer_in_container_and_then_clear_it(*this);
   }
};


