#pragma once


class CLASS_DECL_ACME stringl :
   public string_list
{
public:


   stringl();
   virtual ~stringl();


   void explode(const char * pcszSeparator, const char * psz);

   void implode(string & rwstr, const char * pcszSeparator = nullptr, index iStart = 0, ::count iCount = -1) const;

   string implode(const char * pcszSeparator = nullptr, index iStart = 0, ::count iCount = -1) const;

   void reverse_implode(string & rwstr, const char * pcszSeparator = nullptr, index iStart = 0, ::count iCount = -1) const;

   string reverse_implode(const char * pcszSeparator = nullptr, index iStart = 0, ::count iCount = -1) const;


   void add_tail_tokens(const char * pcsz, const char * pcszSeparator, bool bAddEmpty);


   //virtual ::stream & read(::stream & stream) override;
   //virtual ::stream & write(::stream & stream) const override;


};



template < typename TYPE >
inline stream& operator <<(stream& stream, const stringl& list);


template < typename TYPE >
inline stream& operator >>(stream& stream, stringl& list);




