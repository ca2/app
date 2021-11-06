#pragma once


namespace database
{


   template < typename TYPE >
   inline bool client::binary_set(const key & key, const TYPE & t)
   {

      if (!::is_set(m_pdataserver))
      {

         return false;

      }

      memory_stream stream;

      stream << t;

      if (stream.fail())
      {

         return false;

      }

      if (!m_pdataserver->_data_server_save(this, key, stream->memory()))
      {

         return false;

      }

      return true;

   }


   template < typename TYPE >
   inline bool client::binary_get(const key & key, TYPE & t)
   {

      if (::is_null(m_pdataserver))
      {

         return false;

      }

      memory_stream stream;

      if (!m_pdataserver->_data_server_load(this, key, stream->memory()))
      {

         return false;

      }

      stream >> t;

      if (stream.fail())
      {

         return false;

      }

      return true;

   }


} // namespace database



