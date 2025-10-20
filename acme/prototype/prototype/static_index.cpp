// Created by camilo on 2025-10-20 01:01 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "static_index.h"


static_index static_index_source::create_static_index()
{

   return this;

}


static_index::static_index(static_index_source* pstaticindexsource)
{

   m_iStaticIndex = pstaticindexsource->m_count++;

}




