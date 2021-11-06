#pragma once
// transposed 2011-04-08
// originally from C++ sockets library tcp_socket::circular_file


namespace file
{

   /** buffer class containing one read/write circular buffer.
   \ingroup internal */

   class CLASS_DECL_ACME circular_file :
      virtual public file
   {
   protected:


      memory m_memory;
      memsize m_max;
      memsize m_q;
      memsize m_b;
      memsize m_t;
      memsize m_count;


   public:


      circular_file(memsize size);
      circular_file(const circular_file& buffer);
      circular_file& operator=(const circular_file& buffer);
      ~circular_file();

      /** append l bytes from point_i32 to buffer */
      using ::file::file::write;
      void write(const void * pdata, memsize l);
      /** copy l bytes from buffer to dest */
      using ::file::file::read;
      memsize read(void * pbuffer, memsize l);
      /** skip l bytes from buffer */
      bool erase(memsize l);
      /** read l bytes from buffer, returns as string. */
      using ::file::file::read_string;
      string read_string(memsize l);

      /** total buffer length */
      filesize get_length() const;
      /** pointer to circular buffer beginning */
      const char *GetStart();
      /** return number of bytes from circular buffer beginning to buffer physical end */
      memsize GetL();
      /** return free space in buffer, number of bytes until buffer overrun */
      memsize Space();

      /** return total number of bytes written to this buffer, ever */
      memsize ByteCounter(bool clear = false);

   };


} // namespace file




