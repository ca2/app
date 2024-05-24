// Created by camilo on 2024-04-17 00:58 <3ThomasBorregaardSorensen!!
#pragma once


CLASS_DECL_ACID void safe_memory_copy_bytes(void* ptarget, strsize sizeTargetMax, const void* psource, strsize size);
CLASS_DECL_ACID void safe_wide_memory_copy(::wide_character* ptarget, strsize sizeTargetMax, const ::wide_character* psource, strsize size);
CLASS_DECL_ACID void safe_memory_transfer_bytes(void* ptarget, strsize sizeTargetMax, const void* psource, strsize size);


template < typename TYPE >
inline void safe_memory_copy2(TYPE* ptarget, strsize countTargetMax, const TYPE* psource, strsize count)
{

   ::safe_memory_copy_bytes(ptarget, countTargetMax * sizeof(TYPE), psource, count * sizeof(TYPE));

}


template < typename TYPE >
inline void safe_memory_transfer2(TYPE* ptarget, strsize countTargetMax, const TYPE* psource, strsize count)
{
   
   ::safe_memory_transfer_bytes(ptarget, countTargetMax * sizeof(TYPE), psource, count * sizeof(TYPE));

}



