#include "framework.h"
//#include "core/user/user/_component.h"
#include "list_data.h"
#include "mesh.h"
#include "list.h"
#include "list_column.h"
#include "list_column_array.h"


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

      return pmesh->m_plist->m_pcolumna->get_visible_count();

   }


} // namespace user



