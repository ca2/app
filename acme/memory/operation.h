// Created by camilo on 2024-04-17 00:58 <3ThomasBorregaardSorensen!!
#pragma once


CLASS_DECL_ACME void safe_memory_copy(void* ptarget, strsize sizeTargetMax, const void* psource, strsize size);
CLASS_DECL_ACME void safe_wide_memory_copy(::wide_character* ptarget, strsize sizeTargetMax, const ::wide_character* psource, strsize size);
CLASS_DECL_ACME void safe_memory_transfer(void* ptarget, strsize sizeTargetMax, const void* psource, strsize size);



