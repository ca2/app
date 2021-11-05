#include "framework.h"


namespace database
{


   key::key()
   {

      m_bLocalData = false;

   }


   key::key(const std::initializer_list < ::payload > & list)
   {

      m_bLocalData = false;

      for (auto & payload : list)
      {

         if (payload.get_type() == e_type_bool)
         {

            m_bLocalData = payload.get_bool();

         }
         else
         {

            m_strDataKey = payload.string();

         }

      }

   }


} // namespace database



