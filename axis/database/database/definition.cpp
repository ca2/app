#include "framework.h"
#include "exception.h"
#include "parameter_list.h"
#include "field.h"
#include "result_set.h"


namespace database
{


   exception::exception()
   {

      string str;

      str = "Unknown CDatabase Error";

      m_strMessage = str;

   }


   exception::exception(const char * pszFormat, ...)
   {

      string str;

      va_list args;

      va_start(args, pszFormat);

      try
      {

         str.format_arguments(pszFormat, args);

      }
      catch (...)
      {

      }

      va_end(args);

      str = "CDatabase Error: " + str;

      m_strMessage = str;

   }


   parameter_list & parameter_list::operator = (const parameter_list & paramlist)
   {
      
      m_stra = paramlist.m_stra;
      
      m_row = paramlist.m_row;
      
      return *this;

   }


   field::field()
   {

   }


   //stream & field::write(::stream & stream) const
   //{

   //   stream.write(m_iIndex);
   //   stream.write((::i32 &)m_edatatype);
   //   stream.write(m_strName);
   //   stream.write(m_strDisplayMame);
   //   stream.write(m_strFieldTable);
   //   stream.write(m_bReadOnly);
   //   stream.write(m_iLength);
   //   stream.write(m_ulFlag);

   //   return stream;

   //}


   //stream & field::read(::stream & stream) 
   //{

   //   stream.read(m_iIndex);
   //   stream.read((::i32 &)m_edatatype);
   //   stream.read(m_strName);
   //   stream.read(m_strDisplayMame);
   //   stream.read(m_strFieldTable);
   //   stream.read(m_bReadOnly);
   //   stream.read(m_iLength);
   //   stream.read(m_ulFlag);

   //   return stream;

   //}


   bool parameter_list::is_empty()
   {

      return this->get_size() <= 0;

   }


   ::count parameter_list::get_size()
   {

      return m_stra.get_size();

   }


   const char * parameter_list::get_key(index i)
   {

      return m_stra[i];

   }


   ::payload & parameter_list::get_value(index i)
   {

      return m_row[i];

   }



   result_set::result_set()
   {

      m_iMaxRowCount = -1;
      m_iMaxColumnCount = -1;

   }




   //stream & result_set::write(::stream & stream) const
   //{

   //   stream << *m_pfielda;
   //   stream << *m_prowa;

   //   return stream;

   //}


   //stream & result_set::read(::stream & stream)
   //{

   //   stream >> *m_pfielda;
   //   stream >> *m_prowa;

   //   return stream;

   //}





} // namespace sqlite



