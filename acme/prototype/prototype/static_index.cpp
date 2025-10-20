// Created by camilo on 2025-10-20 01:01 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "static_index.h"


::interlocked_count static_index::s_count;


static_index::static_index()
{

   m_iStaticIndex = s_count++;

}




