#include "framework.h"


namespace database
{


   key::key()
   {

      m_bLocalData = false;

   }


   key::key(const std::initializer_list < var > & list)
   {

      m_bLocalData = false;

      for (auto & var : list)
      {

         if (var.get_type() == type_bool)
         {

            m_bLocalData = (bool)(var);

         }
         else
         {

            m_strDataKey = var.get_string();

         }

      }

   }


} // namespace database



