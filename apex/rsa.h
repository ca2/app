#pragma once


namespace crypto
{


   class CLASS_DECL_APEX rsa :
      virtual public object
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

      rsa(::layered* pobjectContext);
      rsa(::layered* pobjectContext, const string& n);
      rsa(::layered* pobjectContext,
         const string& n,
         const string& e,
         const string& d,
         const string& point,
         const string& q,
         const string& dmp1,
         const string& dmq1,
         const string& iqmp);
      virtual ~rsa();

      
      virtual int public_encrypt(memory& out, const memory& in, string& strError);
      virtual int private_decrypt(memory& out, const memory& in, string& strError);
      virtual int public_decrypt(memory& out, const memory& in, string& strError);
      virtual int private_encrypt(memory& out, const memory& in, string& strError);


   };


} // namespace crypto


