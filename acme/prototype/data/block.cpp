//
// Created by camilo on 2025-08-30 02:11 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "block.h"

namespace data
{
block::block()
{

}
block::~block()
{


}

void block::initialize_set_operation(const ::scoped_string & scopedstrPath, const ::scoped_string & scopedstrMime, const ::block & block)
{

   m_bWrite = true;
   m_strPath = scopedstrPath;
   m_strMime = scopedstrMime;
   m_memory = block;

}


void block::initialize_get_operation(const ::scoped_string & scopedstrPath,
                                     const ::scoped_string & scopedstrMime)
{

   m_bWrite = false;
   m_strPath = scopedstrPath;
   m_strMime = scopedstrMime;

}


} // namespace data