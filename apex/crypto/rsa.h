#pragma once


#include "acme/primitive/primitive/particle.h"


namespace crypto
{


   class CLASS_DECL_APEX rsa :
      virtual public particle
   {
   public:


      string n;
      string e;
      string d;
      string p;
      string q;
      string dmp1;
      string dmq1;
      string iqmp;

      rsa();
      rsa(const string& n);
      rsa(
         const string& n,
         const string& e,
         const string& d,
         const string& point,
         const string& q,
         const string& dmp1,
         const string& dmq1,
         const string& iqmp);
      ~rsa() override;


      virtual int public_encrypt(memory& out, const memory& in, string& strError);
      virtual int private_decrypt(memory& out, const memory& in, string& strError);
      virtual int public_decrypt(memory& out, const memory& in, string& strError);
      virtual int private_encrypt(memory& out, const memory& in, string& strError);

   };


   typedef pointer_array < rsa > rsa_pointer_array;


} // namespace crypto



//::pointer<::crypto::rsa>__create_rsa(const string& str);


