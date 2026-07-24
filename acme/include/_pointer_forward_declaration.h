// Created by camilo on 2027-06-06 10:06 BRT <3ThomasBorregaardSørensen!!
#pragma once



template<typename T>
class pointer;


// template < typename TYPE, ::enum_flag t_eflag = e_flag_none, ::enum_status t_estatus = undefined >
template<typename TYPE>
class make_particle1;


template<typename TYPE>
class array_particle;


template<class TYPE, class ARG_TYPE = const TYPE &, class TYPED = ::typed::def<TYPE>,
         class MEMORY = ::heap::typed_memory<TYPE, ::heap::e_memory_array>,
         ::enum_type t_etypeContainer = e_type_element>
using array = array_particle<array_base<TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer>>;

template<class TYPE, class ARG_TYPE = const TYPE &, class TYPED = ::typed::def_with_zero_init<TYPE>,
         class MEMORY = ::heap::typed_memory<TYPE, ::heap::e_memory_array>,
         ::enum_type t_etypeContainer = e_type_element>
using array_with_zero_init = array<TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer>;


template<class TYPE, class ARG_TYPE = const TYPE &, class TYPED = ::typed::def<TYPE>,
         class MEMORY = ::heap::typed_memory<TYPE, ::heap::e_memory_array>,
         ::enum_type t_etypeContainer = e_type_element>
using raw_array = array_particle<raw_array_base<TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer>>;


using exception_array = ::array_particle<::exception_array_base>;

using const_char_ptra = ::array_particle<const_char_ptra_base>;
using void_ptra = ::array_particle<void_ptra_base>;
using particle_address_array = ::array_particle<particle_address_array_base>;


using char_array = ::array_particle<char_array_base>;
using short_array = ::array_particle<short_array_base>;
using i32_array = ::array_particle<i32_array_base>;
using i64_array = ::array_particle<i64_array_base>;

using u8_array = ::array_particle<u8_array_base>;
using u16_array = ::array_particle<u16_array_base>;
using u32_array = ::array_particle<unsigned_i32_array_base>;
using u64_array = ::array_particle<u64_array_base>;

using f32_array = ::array_particle<f32_array_base>;
using f64_array = ::array_particle<f64_array_base>;

using index_array = ::array_particle<index_array_base>;
using count_array = ::array_particle<count_array_base>;
using u32_array = ::array_particle<unsigned_i32_array_base>;

#ifdef OS64BIT


using iptr_array = i64_array;
using uptr_array = u64_array;


#else

using iptr_array = i32_array;
using uptr_array = u32_array;


#endif


using strsize_array = iptr_array;

using process_identifier_array = ::array_particle<process_identifier_array_base>;

using byte_array = u8_array;

using payload_array = ::array_particle<payload_array_base>;

using arguments = payload_array;


using pixmap_pointer = ::pointer < ::pixmap >;

namespace image
{


   using image_pointer = ::pointer<::image::image>;


} // namespace image


using mutex_pointer = ::pointer<::mutex>;


namespace write_text
{


   class font;

   using font_pointer = ::pointer<font>;


} // namespace write_text


using item_pointer = ::pointer<::item>;

using memory_pointer = ::pointer<::make_particle1<::memory>>;


template<class T, typename ARG_T = const T *, typename ARRAY_BASE = array_base<::pointer<T>, ARG_T>>
class pointer_array_base;

template<class T, typename ARG_T = const T *, typename ARRAY_BASE = array_base<::pointer<T>, ARG_T>>
class pointer_array; // = ::array_particle < pointer_array_base < T, ARG_T, ARRAY_BASE > >;


template<class T, ::i32 t_preallocated_array_size, typename ARG_T = const T *>
using preallocated_pointer_array_base =
   pointer_array_base<T, ARG_T, ::block_array<::pointer<T>, t_preallocated_array_size, e_array_none, ARG_T>>;


using particle_array_base = pointer_array_base<particle>;
using subparticle_array_base = pointer_array_base<subparticle>;


using particle_array = ::array_particle<particle_array_base>;
using subparticle_array = ::array_particle<subparticle_array_base>;


using regular_expression_pointer = ::pointer<::regular_expression::regular_expression>;


using file_pointer = ::pointer<::file::file>;


using memory_file_pointer = ::pointer<::memory_file>;


using folder_pointer = ::pointer<::folder>;

template<typename T>
inline ::pointer<T> pointer_transfer(T *p);


template<typename T, typename... Args>
inline ::pointer<T> __call_allocate(Args &&...args);


using manager_pointer = ::pointer<manager>;
using context_pointer = ::pointer<context>;


using topic_pointer = ::pointer<topic>;
using extended_topic_pointer = ::pointer<extended_topic>;


using task_pointer = ::pointer<task>;


using task_pointer = ::pointer<task>;


CLASS_DECL_ACME task_pointer fork(::particle *pparticle, const ::procedure &procedure);


// #include "acme/prototype/prototype/_u32hash.h"


CLASS_DECL_ACME task_pointer fork(::particle *pparticle, const ::procedure &procedure);


namespace draw2d
{


   class graphics_pointer;


} // namespace draw2d


using particle_array_base = pointer_array_base<::particle>;


using particle_array = ::array_particle<::particle_array_base>;


namespace write_text
{


   using font_enumeration_item_array = pointer_array<font_enumeration_item>;


} // namespace write_text


using object_ptra = pointer_array<::matter>; // Please use just for keeping non-member-based references.

using matter_array = pointer_array<::matter>; // Please use just for keeping non-member-based references.

using task_array = pointer_array<::task>; // Please use just for keeping non-member-based references.


namespace platform
{


   using session_map = ::index_map_base<::pointer<::platform::session>>;


} // namespace platform


namespace file
{

   using listing = ::array_particle<listing_base>;

} // namespace file
