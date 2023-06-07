// Created by camilo on 2022-04-30 02:47 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/platform/acme.h"
#include "acme/platform/system.h"


::file::path dir_ca2_module()
{

   auto psystem = ::acme::acme::g_pacme->m_psubsystem->acmesystem();

   return psystem->m_pacmedirectory->module();

}



