#include "framework.h"
#include "base/user/user/_user.h"


#ifdef LINUX
#include <unistd.h>
#endif

namespace user
{


   //impact_creator::impact_creator()
   //{


   //}


   //impact_creator::~impact_creator()
   //{


   //}


   //void impact_creator::set_impact_creator(impact_creator* pimpactcreator)
   //{

   //   m_pimpactcreator = pimpactcreator;

   //}


   void impact_creator::on_create_impact(::user::impact_data * pimpactdata)
   {

      //if (m_pimpactcreator)
      //{

      //   m_pimpactcreator->create_impact(pimpactdata);

      //}

   }


   bool impact_creator::create_impact(::user::impact_data * pimpactdata)
   {

      on_create_impact(pimpactdata);

      if(pimpactdata->m_bOk)
      {

         return true;

      }

      if(::is_set(pimpactdata->m_puserinteraction) || ::is_set(pimpactdata->m_pdocument))
      {

         pimpactdata->m_bOk = true;

         return true;

      }

      if (::is_set(pimpactdata->m_pplaceholder) 
         && ::is_set(pimpactdata->m_pplaceholder->m_puserinteractionpointeraChild)
         && pimpactdata->m_pplaceholder->m_puserinteractionpointeraChild->has_interaction())
      {

         pimpactdata->m_bOk = true;

         return true;

      }

      return false;

   }


} // namespace user



