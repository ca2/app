#include "framework.h"
#include "aqua/xml.h"


namespace xml
{


   data::data(::xml::parse_info * pparseinfo) :
      ::xml::document(pparseinfo)
   {


   }


   data::~data()
   {



   }


   void data::edit(::xml::edit * pedit)
   {

      auto estatus = validate_edit(pedit);

      if (!estatus)
      {

         throw ::exception::exception(estatus);

      }

      __pointer(::xml::node) pnode;

      for (index iEdit = pedit->m_iEdit; iEdit < pedit->m_edititema.get_count(); iEdit++)
      {

         ::xml::edit_item * pitem = pedit->m_edititema.element_at(iEdit);

         try
         {

            switch (pitem->m_eaction)
            {

            case ::xml::action_set_name:
            {
               pnode = get_node_from_indexed_path(pitem->m_iaPath);
               if (!pnode)
                  return;
               pnode->set_name(pitem->m_strValue);
            }
            break;

            case ::xml::action_set_value:
            {
               pnode = get_node_from_indexed_path(pitem->m_iaPath);
               if (!pnode)
                  return;
               pnode->set_value(pitem->m_strValue);
            }
            break;

            case ::xml::action_set_attribute:
            {
               pnode = get_node_from_indexed_path(pitem->m_iaPath);
               if (!pnode)
                  return;
               pnode->set_attribute(pitem->m_strName, pitem->m_strValue);
            }
            break;

            //case ::xml::action_add_attr:
            //{
            //   pnode = get_node_from_indexed_path(pitem->m_iaPath);
            //   if(!pnode)
            //      return;
            //   pnode->add_attr(pitem->m_strName, pitem->m_strValue);
            //}
            //break;

            default:
               ASSERT(false);
               break;

            }

         }
         catch (...)
         {
            break;
         }

         pedit->m_iEdit = iEdit;
      }



   }

   
   ::e_status data::validate_edit(::xml::edit* pedit)
   {

      return ::success;

   }

   
   ::stream & data::write(::stream & stream) const
   {

      return ::xml::document::write(stream);

   }
   

   ::stream & data::read(::stream & stream)
   {

      return ::xml::document::read(stream);

   }



} // namespace aura



