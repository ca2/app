// Created by camilo on 2025-10-20 01:01 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "unique_index.h"



unique_index unique_index_domain::unique_index()
{

   return this;

}



unique_index::unique_index(unique_index_domain * puniqueindexdomain)
{

   m_iUniqueIndex = puniqueindexdomain->m_count++;

}


