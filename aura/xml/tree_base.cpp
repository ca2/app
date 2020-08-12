#include "framework.h"
#include "aura/xml/_.h"


namespace xml
{


   tree_base::tree_base(::object * pobjectContext) :
      ::object(pobjectContext),
      m_varexchange(pobjectContext)
   {
      
      m_pschema = nullptr;

   }


   tree_base::tree_base(::object * pobjectContext, tree_schema * pschema) :
      ::object(pobjectContext),
      m_varexchange(pobjectContext)
   {

      m_pschema = pschema;

   }


   tree_base::~tree_base()
   {

   }

   string tree_base::get_node_name(i32 iNameIndex)
   {
      return m_pschema->get_node_name(iNameIndex);
   }

   tree_schema & tree_base::get_schema()
   {
      return *m_pschema;
   }

   void tree_base::set_schema(tree_schema * pschema)
   {
      m_pschema = pschema;
   }

} // namespace xml
