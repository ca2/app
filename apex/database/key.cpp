#include "framework.h"


namespace database
{


   key::key()
   {

      m_bLocalData = false;

   }


   key::key(const std::initializer_list < payload > & list)
   {

      m_bLocalData = false;

      for (auto & payload : list)
      {

         if (payload.get_type() == type_bool)
         {

            m_bLocalData = (bool)(payload);

         }
         else
         {

            m_strDataKey = payload.get_string();

         }

      }

   }


} // namespace database



