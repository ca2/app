#include "framework.h"
#include "aqua/xml.h"


namespace xml
{


tree_schema::tree_schema()
{

}

tree_schema::~tree_schema()
{

}

string tree_schema::get_node_name(i32 iNameIndex)
{
   return m_stra[iNameIndex];
}

void tree_schema::set_node_name(i32 iNameIndex, const char * pcszName)

{
   m_stra.set_at_grow(iNameIndex, pcszName);

}

} // namespace xml
