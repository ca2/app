// Created by camilo on 2022-04-30 02:47 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "acme/filesystem/filesystem/acme_directory.h"


::file::path dir_ca2_module()
{

   auto psystem = ::get_system();

   return psystem->m_pacmedirectory->module();

}



