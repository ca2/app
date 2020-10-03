#pragma once




//namespace file
//{


   class string_file;


   typedef __pointer(string_file) string_file_pointer;


   class CLASS_DECL_ACME string_file :
      virtual public ::file::file
   {
   public:


      string         m_str;
      strsize        m_iPos;


      string_file();
      string_file(const string & str);
      string_file(const string_file & str);
      virtual ~string_file();


      //using ::file::file::read;
      virtual memsize read(void *pdata, memsize nCount) override;

      //virtual stream & read(stream & istream) override;


      //using ::file::file::write;
      virtual void write(const void *pdata, memsize nCount) override;

      //virtual stream & write(stream & ostream) const override;

      ::string str() const;

      virtual void flush() override;

      virtual void close() override;

      bool is_empty() const
      {

         return m_str.is_empty();

      }




      filesize get_length() const
      {
         return m_str.get_length();
      }


      virtual filesize get_position() const override;

      void destroy();
      //void alloc(strsize iSize);

      //void alloc_up(strsize iAtLeast);

      void set(const char * psz,strsize len);

      void set(const string & str)
      {
         set(str, str.length());
      }


      void append(const char * psz,strsize len);

      void append(const string & str)
      {
         append(str, str.length());
      }



      //operator const char *() const
      //{

      //   return m_str;

      //}


      operator const string & () const
      {

         return m_str;

      }


      virtual void to_string(const string_exchange & str) const override;


      string_file & operator += (const string & str)
      {
         append(str);
         return *this;
      }

      string_file & operator = (const string & str)
      {
         set(str);
         return *this;
      }

   };


//} // namespace file



