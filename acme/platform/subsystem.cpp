// Created by camilo on 2022-10-09 21:01 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "subsystem.h"
#include "acme/platform/library.h"
#include "acme/exception/exception.h"
#include "acme/parallelization/task.h"


static subsystem * g_psubsystem = nullptr;


subsystem::subsystem()
{

   if (g_psubsystem)
   {

      throw ::exception(error_wrong_state);

   }

   g_psubsystem = this;

}


subsystem::~subsystem()
{

   task_release();

   {

      array<void *> librarya;

      for (auto & plibrary : m_mapLibrary.values())
      {

         if (plibrary)
         {

            librarya.add(plibrary->m_plibrary);

            plibrary->m_plibrary = nullptr;

            plibrary->destroy();

         }

      }

      m_mapLibrary.clear();

      for (auto & p : librarya)
      {


         __node_library_close(p);

      }

   }

   g_psubsystem = nullptr;

}


::subsystem * subsystem::get()
{

   return g_psubsystem;

}



