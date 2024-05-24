// Created by camilo on 2022-04-30 02:47 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "acid/filesystem/filesystem/ace_directory.h"
#include "acid/platform/acid.h"
#include "acid/platform/system.h"


::file::path dir_ca2_module()
{

   auto psystem = this->platform()->system();

   return psystem->m_pacedirectory->module();

}



