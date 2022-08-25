#include "framework.h"
#include "core/user/user/_component.h"


namespace user
{

 
   list_data::list_data()
   {
    
   }

   
   list_data::~list_data()
   {

   }


   count list_data::_001GetColumnCount(mesh * pmesh)
   {

      return pmesh->m_plist->m_columna.get_visible_count();

   }



} // namespace user






