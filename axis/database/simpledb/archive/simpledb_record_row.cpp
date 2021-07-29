#include "framework.h"


namespace simpledb
{


//      table *     m_ptable;
   //    string_array     m_straFields;
   //  ::payload         m_var;

   void record_row::io(stream & stream)
   {
      if (stream.is_storing())
      {

         if (m_straFields.get_size() <= 0)
         {
            payload_array payloada = m_var.payloada();
            if (payloada.get_count() != m_ptable->m_fielddefinition.get_count())
            {
               __throw(::exception::exception("no fields specified and values ::count is different from table '" + m_ptable->m_strName + "' field count"));
            }
            else
            {
               for (i32 i = 0; i < m_ptable->m_fielddefinition.get_count(); i++)
               {
                  ::database::field_definition_item & item = m_ptable->m_fielddefinition[i];
                  ::payload payload = payloada[i];
                  if (item.m_etype == ::database::field_definition_item::type_text)
                  {
                     if (item.m_iSize > 0)
                     {
                        strsize iLen = minimum(255, payload.get_string().get_length());
                        stream << (char)iLen;
                        stream.write(payload.get_string().Left(iLen), iLen);
                        if (iLen < item.m_iSize)
                        {
                           string str(' ', item.m_iSize - iLen);
                           stream.write(str, item.m_iSize - iLen);
                        }
                     }
                  }
               }
            }

         }
      }
      else
      {
         if (m_straFields.get_size() <= 0 || (m_straFields.get_size() == 1 && m_straFields[0] == "*"))
         {
            for (i32 i = 0; i < m_ptable->m_fielddefinition.get_count(); i++)
            {
               ::database::field_definition_item & item = m_ptable->m_fielddefinition[i];
               ::payload payload;
               if (item.m_etype == ::database::field_definition_item::type_text)
               {
                  if (item.m_iSize > 0)
                  {
                     byte uchLen;
                     stream >> uchLen;
                     string str;
                     stream.read(str.get_string_buffer(uchLen), uchLen);
                     payload = str;
                     str.ReleaseBuffer(uchLen);
                     if (uchLen < item.m_iSize)
                     {
                        char sz[255];
                        stream.read(sz, item.m_iSize - uchLen);
                     }
                  }
               }
               m_var.payloada().add(payload);
            }
         }


      }
   }


} // namespace simpledb


