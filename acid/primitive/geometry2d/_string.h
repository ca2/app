// From nanoui/vector.h by camilo on 2023-05-18 22:33 <3ThomasBorregaardSorensen
#pragma once


template < typename COORDINATE, size_t SIZE >
::string as_string(const vector_base<COORDINATE, SIZE>& m_coordinatea)
{

   ::string str;
   
   str += '[';

   for (size_t i = 0; i < SIZE; ++i) 
   {

      str += as_string(m_coordinatea.m_coordinatea[i]);
      
      if (i + 1 < SIZE)
      {

         str += ", ";

      }

   }
   
   str+= ']';
   
   return ::transfer(str);

}


template < typename COORDINATE, size_t SIZE>
::string as_string(const Matrix<COORDINATE, SIZE>& m) 
{

   ::string str;

   str += '[';

   for (size_t i = 0; i < SIZE; ++i) 
   {
      
      if (i != 0)
      {

         str += ' ';

      }

      str += '[';

      for (size_t j = 0; j < SIZE; ++j) 
      {
         
         str +=::as_string( m.m[j][i]);

         if (j + 1 < SIZE)
         {

            str += ", ";

         }

      }

      str += ']';

      if (i != SIZE - 1)
      {

         str += ",\n";

      }

   }

   str += ']';

   return ::transfer(str);

}



