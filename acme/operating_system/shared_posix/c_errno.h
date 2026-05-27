// From acme/platform/error.h by camilo on 2023-07-06 08:41 <3ThomasBorregaardSorense!!
#pragma once


CLASS_DECL_ACME ::e_status get_last_status();
CLASS_DECL_ACME void set_last_status(const ::e_status & estatus);


struct c_errno_t {};


/// Class with static functions to get information about an error.
class CLASS_DECL_ACME c_errno
{
public:


   ::i32          m_iErrNo;


   c_errno();
#ifdef WINDOWS
   c_errno(c_errno_t, errno_t iErrNo);
#else
   c_errno(c_errno_t, ::i32 iErrNo);
#endif
   c_errno(const c_errno & cerrno);


   ::i32 as_i32() const {return m_iErrNo;}


   ::string get_error_description() const;

   ::string name() const;


   class ::error_code error_code() const;

   ::e_status estatus() const;

   ::e_status failed_estatus() const;


   ::e_status set_last_errno_status();

   static c_errno s_errno();

   static string s_get_error_description(c_errno cerrno = s_errno());

   static void s_throw_exception(c_errno cerrno);


   bool operator == (::i32 iErrNo) const {return m_iErrNo == iErrNo; }


};


