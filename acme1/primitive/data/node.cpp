#include "framework.h"


namespace data
{


   node::node()
   {

      m_pxmlnode = nullptr;

      m_pnodeParent = nullptr;

      m_enode = e_node_none;

   }


   node::~node()
   {


   }


   ::xml::document* node::get_xml_document() const
   {

      return nullptr;

   }


} // namespace data



