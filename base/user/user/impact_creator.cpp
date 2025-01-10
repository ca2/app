#include "framework.h"
#include "impact_creator.h"
#include "impact_data.h"
#include "place_holder.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/user/user/interaction_array.h"


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


   bool impact_creator::impact_creator_create_impact(::user::impact_data * pimpactdata)
   {

      __check_refdbg

      on_create_impact(pimpactdata);

      __check_refdbg

      if(pimpactdata->m_bOk)
      {

         return true;

      }

      if(::is_set(pimpactdata->m_puserinteraction) || ::is_set(pimpactdata->m_pdocument))
      {

         pimpactdata->m_bOk = true;

         return true;

      }

      {

         _synchronous_lock synchronouslock(this->synchronization());

         if (::is_set(pimpactdata->m_pplaceholder)
            && ::is_set(pimpactdata->m_pplaceholder->m_pacmeuserinteractionaChildren)
            && pimpactdata->m_pplaceholder->m_pacmeuserinteractionaChildren->has_element())
         {

            pimpactdata->m_bOk = true;

            return true;

         }

      }

      return false;

   }


} // namespace user



