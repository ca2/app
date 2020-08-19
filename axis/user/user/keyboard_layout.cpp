#include "framework.h" 
//#include "aura/xml/_.h"


namespace user
{



   keyboard_layout_id::keyboard_layout_id()
   {

   }


   keyboard_layout_id::keyboard_layout_id(const keyboard_layout_id & id)
   {

      operator = (id);

   }

   keyboard_layout_id::~keyboard_layout_id()
   {


   }


   keyboard_layout_id & keyboard_layout_id::operator = (const keyboard_layout_id & id)
   {

      if(this != &id)
      {

         m_strName      = id.m_strName;
         m_strPath      = id.m_strPath;
         m_countrycode  = id.m_countrycode;
         m_hkla         = id.m_hkla;
         m_keylayout    = id.m_keylayout;

      }

      return *this;

   }


   bool keyboard_layout_id::operator <= (const keyboard_layout_id & on_layout) const
   {
      i32 iCompare = m_strName.compare_ci(on_layout.m_strName);
      if(iCompare <= 0)
         return true;
      else if(iCompare == 0)
      {
         iCompare = m_strPath.compare_ci(on_layout.m_strPath);
         return iCompare <= 0;
      }
      else
         return false;
   }


   bool keyboard_layout_id::operator < (const keyboard_layout_id & on_layout) const
   {
      i32 iCompare = m_strName.compare_ci(on_layout.m_strName);
      if(iCompare < 0)
         return true;
      else if(iCompare == 0)
      {
         iCompare = m_strPath.compare_ci(on_layout.m_strPath);
         return iCompare < 0;
      }
      else
         return false;
   }

   bool keyboard_layout_id::operator == (const keyboard_layout_id & on_layout) const
   {
      i32 iCompare = m_strName.compare_ci(on_layout.m_strName);
      if(iCompare != 0)
         return false;
      iCompare = m_strPath.compare_ci(on_layout.m_strPath);
      if(iCompare != 0)
         return false;
      return true;
   }

   keyboard_layout::keyboard_layout()
   {

   }

   keyboard_layout::~keyboard_layout()
   {



   }

   //void keyboard_layout::process_escape(__pointer(::xml::node) pnode, property_set & set)
   //{
   //   for(i32 i = 0; i < pnode->get_children_count(); i++)
   //   {
   //      __pointer(::xml::node) pchild = pnode->child_at(i);
   //      if(pchild->get_name().compare_ci("item") == 0)
   //      {
   //         string str = pchild->attribute("char");
   //         if(str.has_char())
   //         {
   //            set[str] = pchild->attribute("value");
   //         }
   //      }
   //      else if(pchild->get_name().compare_ci("escape") == 0)
   //      {
   //         process_escape(pchild, set[pnode->attribute("value").get_string()].propset());
   //      }
   //   }
   //}


   // load keyboard_layout/<language>.xml
   bool keyboard_layout::load(const char * pszPath)
   {

      //i32 iMap;
      
      string str = Context.file().as_string(pszPath);

      if (str.is_empty())
      {

         return false;

      }

      __throw(todo("xml"));
      
      /*::xml::document doc;
      
      if (!doc.load(str))
      {

         return false;

      }

      for(i32 i = 0; i < doc.root()->get_children_count(); i++)
      {
         
         auto  pnode = doc.root()->child_at(i);

         if(pnode->get_name().compare_ci("item") == 0)
         {

            string strCode = pnode->attribute("code");

            string strValue = pnode->attribute("value");

            string strEscape = pnode->attribute("escape");

            iMap = 0;

            if(pnode->attribute("shift") == 1)
            {

               iMap |= 0x80000000;

            }

            if(pnode->attribute("ralt") == 1)
            {

               iMap |= 0x40000000;

            }

            if(strCode.has_char())
            {

               ::user::e_key ekey;

               text_enum(ekey, strCode);

               i32 iCode = iMap | (i32)(ekey);

               if(strValue.has_char())
               {

                  m_mapCode[iCode] = strValue;

               }
               else
               {

                  m_mapCode[iCode] = "escape=" + strEscape;

               }

            }

         }
         else if(pnode->get_name().compare_ci("escape") == 0)
         {

            process_escape(pnode, m_setEscape[pnode->attribute("value").get_string()].propset());

         }

      }*/

      return true;

   }


   string keyboard_layout::process_key(key * pkey)
   {

      string str;

      if(!m_mapCode.lookup((int) pkey->m_iCode,str))
      {

         str = (char)(pkey->m_nChar & 0xff);

      }

      if(::str::begins_eat(str,"escape="))
      {

         return process_escape(str);

      }
      else
      {

         return process_char(str);

      }

   }


   string keyboard_layout::process_key(i32 iCode)
   {

      string str;

      // load keyboard_layout/<language>.xml
      if(!m_mapCode.lookup(iCode, str))
      {

         str = (char) (iCode & 0xff);

      }

      if(::str::begins_eat(str, "escape="))
      {

         return process_escape(str);

      }
      else
      {

         return process_char(str);

      }

   }


   string keyboard_layout::process_char(const char * pszKey)
   {

      string strChar;

      if(m_strEscape.has_char())
      {

         string_array stra;

         stra.explode(";", m_strEscape);

         property_set * pset = &m_setEscape;

         for(i32 i = 0; i < stra.get_size(); i++)
         {

            if(pset->has_property(stra[i]))
            {

               if((*pset)[stra[i]].get_type() == ::type_propset)
               {

                  pset = &(*pset)[stra[i]].propset();

               }
               else if(i == stra.get_upper_bound())
               {

                  m_strEscape.Empty();

                  return stra.implode("") + pszKey;

               }

            }
            else
            {

               m_strEscape.Empty();

               return stra.implode("") + pszKey;

            }

         }

         if(pset->has_property(pszKey))
         {

            m_strEscape.Empty();

            return (*pset)[pszKey];

         }
         else
         {

            m_strEscape.Empty();

            return stra.implode("") + pszKey;

         }

      }
      else
      {

         return pszKey;

      }

   }


   string keyboard_layout::process_escape(const char * pszEscape)
   {

      if(m_strEscape.has_char())
      {

         m_strEscape += ";";

         m_strEscape += pszEscape;

      }
      else
      {

         m_strEscape = pszEscape;

      }

      return "";

   }


} // namespace user




