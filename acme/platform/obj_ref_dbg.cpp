#include "framework.h"
#include "acme/platform/static_start.h"
#include "obj_ref_dbg_impl.h"


extern lparam_dbg g_lparamdbg;

bool g_bEnableObjRefDbg = true;

//critical_section * g_pcsRefDbg = nullptr;


obj_ref_dbg::obj_ref_dbg()
{

}

obj_ref_dbg::~obj_ref_dbg()
{


}


void defer_delete(obj_ref_dbg* p)
{

   if (::is_null(p))
   {

      return;

   }

   delete p;

};


string object_name(matter* p)
{

   iptr i = (iptr)p;

   if (i < 16)
   {

      return __str(i);

   }

   return typeid(*p).name();

}

#if OBJ_REF_DBG

void matter::add_ref_history(matter* p, const char* pszObjRefDbg)
{

   if (!::acme::g_bAcme)
   {

      return;

   }

   critical_section_lock synchronizationlock(&::acme::g_csRefDbg);

   if (g_bEnableObjRefDbg)
   {

      g_bEnableObjRefDbg = false;

      try
      {

         string strType = type_name();

         if (strType == "pacman::game")
         {

            output_debug_string("pacman::game");

         }


         if (m_pobjrefdbg == nullptr)
         {

            m_pobjrefdbg = new obj_ref_dbg;

         }

         string strNote = ::object_name(p);

         if (::is_set(pszObjRefDbg))
         {

            strNote += " - " + string(pszObjRefDbg);

         }

         if (strType == "pacman::game")
         {

            output_debug_string("pacman::game");

         }
         else if (strType.contains_ci("session"))
         {

            if (m_pobjrefdbg->m_iStep == 39)
            {

               output_debug_string("session");

            }

         }

         m_pobjrefdbg->m_itema.add_item({ m_pobjrefdbg->m_iStep++, p, strNote });

      }
      catch (...)
      {

      }

      g_bEnableObjRefDbg = true;

   }

}


void matter::dec_ref_history(matter* p, const char* /*pszObjRefDbgNotUsedCurrently*/)
{

   critical_section_lock synchronizationlock(&::acme::g_csRefDbg);

   if (::is_null(m_pobjrefdbg) || m_countReference <= 0 || m_pobjrefdbg->m_itema.isEmpty())
   {

      return;

   }

   ::index iFind = m_pobjrefdbg->m_itema.predicate_find_last([p](auto& item) {return item.m_p == p; });

   if (iFind >= 0)
   {

      m_pobjrefdbg->m_itema.remove_at(iFind);

   }

}


void matter::check_pending_releases()
{

   critical_section_lock synchronizationlock(&::acme::g_csRefDbg);

   if (m_pobjrefdbg == nullptr)
   {

      return;

   }

   if (m_pobjrefdbg->m_itema.has_element())
   {

      ::output_debug_string("\nThere are pending releases (m_countReference=" + __str(m_countReference) + "):\n");

      try
      {

         ::output_debug_string("For " + __str(typeid(*this).name()) + "(" + string(debug_note()) + ")\n");

      }
      catch (...)
      {

      }

      for (index iIndex = 0; iIndex < m_pobjrefdbg->m_itema.get_count(); iIndex++)
      {

         auto& item = m_pobjrefdbg->m_itema[iIndex];

         ::index iStep = item.m_iStep;

         ::matter* pobj = item.m_p;

         string str = item.m_strNote;

         try
         {

            ::output_debug_string(::str::pad(__str(iIndex), 4, " ", ::str::pad_left) + ": " + ::str::pad(__str(iStep), 4, " ", ::str::pad_left) + ": " + str + "\n");

         }
         catch (...)
         {


         }

      }

      ::output_debug_string("-------------------\n\n");

   }


}

#endif


lparam_dbg g_lparamdbg;


CLASS_DECL_ACME lparam_dbg & lparam_debug()
{

    return g_lparamdbg;

}



