// Created by camilo on 2024-04-17 00:58 <3ThomasBorregaardSorensen!!
#pragma once


CLASS_DECL_ACME void safe_memory_copy_bytes(void* ptarget, character_count sizeTargetMax, const void* psource, character_count size);
CLASS_DECL_ACME void safe_wide_memory_copy(::wide_character* ptarget, character_count sizeTargetMax, const ::wide_character* psource, character_count size);
CLASS_DECL_ACME void safe_memory_transfer_bytes(void* ptarget, character_count sizeTargetMax, const void* psource, character_count size);


template < typename TYPE >
inline void safe_memory_copy2(TYPE* ptarget, character_count countTargetMax, const TYPE* psource, character_count count)
{

   ::safe_memory_copy_bytes(ptarget, countTargetMax * sizeof(TYPE), psource, count * sizeof(TYPE));

}


template < typename TYPE >
inline void safe_memory_transfer2(TYPE* ptarget, character_count countTargetMax, const TYPE* psource, character_count count)
{
   
   ::safe_memory_transfer_bytes(ptarget, countTargetMax * sizeof(TYPE), psource, count * sizeof(TYPE));

}



