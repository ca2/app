// Created by camilo on 2022-04-30 02:47 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/platform/acme.h"
#include "acme/platform/system.h"


::file::path dir_ca2_module()
{

   auto psystem = this->platform()->system();

   return psystem->m_pdirectorysystem->module();

}



