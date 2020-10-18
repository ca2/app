#include "framework.h"
#include "acme/library.h"
#include "acme/platform/static_start.h"


extern lparam_dbg g_lparamdbg;

bool g_bEnableObjRefDbg = true;

//critical_section * g_pcsRefDbg = nullptr;

class obj_ref_dbg
{
public:

   class item
   {
   public:

      ::index                 m_iStep;
      matter *        m_p;
      string                  m_strNote;

   };

   ::index           m_iStep;
   array < item >    m_itema;

   obj_ref_dbg();
   virtual ~obj_ref_dbg();

};

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

   cslock sl(&::acme::g_csRefDbg);

   if (g_bEnableObjRefDbg)
   {

      g_bEnableObjRefDbg = false;

      try
      {

         if (m_pobjrefdbg == nullptr)
         {

            m_pobjrefdbg = new obj_ref_dbg;

         }

         string strNote = ::object_name(p);

         if (::is_set(pszObjRefDbg))
         {

            strNote += " - " + string(pszObjRefDbg);

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

   cslock sl(&::acme::g_csRefDbg);

   if (m_pobjrefdbg == nullptr || m_countReference <= 0 || m_pobjrefdbg->m_itema.isEmpty())
   {

      return;

   }

   ::index iFind = m_pobjrefdbg->m_itema.pred_find_last([p](auto& item) {return item.m_p == p; });

   if (iFind >= 0)
   {

      m_pobjrefdbg->m_itema.remove_at(iFind);

   }

}


void matter::check_pending_releases()
{

   cslock sl(&::acme::g_csRefDbg);

   if (m_pobjrefdbg == nullptr)
   {

      return;

   }

   if (m_pobjrefdbg->m_itema.has_element())
   {

      ::output_debug_string("\nThere are pending releases (m_countReference=" + __str(m_countReference) + "):\n");

      try
      {

         ::output_debug_string("For "+__str(typeid(*this).name())+"("+string(debug_note())+")\n");

      }
      catch (...)
      {

      }

      for (index i = 0; i < m_pobjrefdbg->m_itema.get_count(); i++)
      {

         auto& item = m_pobjrefdbg->m_itema[i];

         ::index iStep = item.m_iStep;

         ::matter* pobj = item.m_p;

         string str = item.m_strNote;

         try
         {

            ::output_debug_string(__str(iStep) + ": " + str + "\n");

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

