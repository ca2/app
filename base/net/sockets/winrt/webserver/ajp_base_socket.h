#pragma once


namespace sockets
{


   class CLASS_DECL_BASE AjpBaseSocket : public tcp_socket
   {
   public:

      class Initializer
      {
      public:
         Initializer();
         virtual ~Initializer() {}

         ::int_to_string Method;
         ::int_to_string header;
         ::int_to_string Attribute;
         ::string_map < int > ResponseHeader;

      };

      AjpBaseSocket(base_socket_handler& h);

      void OnRawData(char *buf, memsize sz);

      virtual void OnHeader( short id, short len ) = 0;
      virtual void OnPacket( const char *buf, memsize sz ) = 0;

   protected:
      unsigned char get_byte(const char *buf, int& ptr);
      bool get_boolean(const char *buf, int& ptr);
      short get_integer(const char *buf, int& ptr);
      string get_string(const char *buf, int& ptr);

      void put_byte(char *buf, int& ptr, unsigned char zz);
      void put_boolean(char *buf, int& ptr, bool zz);
      void put_integer(char *buf, int& ptr, short zz);
      void put_string(char *buf, int& ptr, const char * psz);

   private:
      int m_state;
      int m_length;
      int m_ptr;
      char m_message[8192];
   };


} // namespace sockets



