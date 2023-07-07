// Detemplatized refactored by camilo on 2023-07-06 07:28 <3ThomasBorregaardSorensen!!
#pragma once


class string_buffer;


class string_buffer_base :
   virtual public ::file::file
{
public:


   string_buffer_base();
   ~string_buffer_base() override;

   virtual void write(const ::block & block);

   void flush() override;

   void close() override;

   virtual bool is_empty() const;

   virtual filesize length() const;

   filesize get_position() const override;

   bool unget_if(::ansi_character ch) override;

};


class string_reference_buffer :
   virtual public ::string_buffer_base
{
public:


   string & m_str;


   string_reference_buffer(::string & str);
   string_reference_buffer(const string_reference_buffer & buffer) = default;
   string_reference_buffer(string_reference_buffer & buffer) = default;
   ~string_reference_buffer() override;

   void write(const ::block & block) override;

   void flush() override;

   void close() override;

   bool is_empty() const override;

   filesize length() const override;

   filesize get_position() const override;

   bool unget_if(::ansi_character ch) override;

};




class CLASS_DECL_ACME string_buffer :
   public string_reference_buffer
{
public:


   ::string                         m_strOwnStorage;

   string_buffer();
   string_buffer(string_buffer && buffer);
   ~string_buffer() override;


};

