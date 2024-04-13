// Created by camilo on 2023-07-05 09:47 BRT Thomas Month Coming!! <3ThomasBS_!!
#define __BSD_VISIBLE 1
#include <link.h>
#include <dlfcn.h>


char * freebsd_acme_path()
{

   void * handle = dlopen("libacme.so", RTLD_NOW);

   if (handle == nullptr)
   {

      return nullptr;

   }

   link_map * plm;

   dlinfo(handle, RTLD_DI_LINKMAP, &plm);

   auto p = strdup(plm->l_name);

   dlclose(handle);

   return p;

}



