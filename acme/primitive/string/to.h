#pragma once


namespace str
{


   CLASS_DECL_ACME  iptr         to_iptr(const ::string & psz);
   CLASS_DECL_ACME  i32          to_i32(const ::string & psz);
   CLASS_DECL_ACME  u32          to_u32(const ::string & psz);


   CLASS_DECL_ACME i64           to_i64(const ::string & str);
   CLASS_DECL_ACME i64           to_i64(const ::string & psz);
   CLASS_DECL_ACME u64           to_u64(const ::string & str);
   CLASS_DECL_ACME u64           to_u64(const ::string & psz);



   inline CLASS_DECL_ACME i32 to_with_fallback(const ::string & psz, i32 iDefault) { from_string(iDefault, psz); return iDefault; }
   inline CLASS_DECL_ACME i64 to_with_fallback(const ::string & psz, i64 iDefault) { from_string(iDefault, psz); return iDefault; }
   inline CLASS_DECL_ACME i32 to_with_fallback(const ::string & psz, i32 iDefault, i32 iBase) { from_string(iDefault, iBase, psz); return iDefault; }
   inline CLASS_DECL_ACME i64 to_with_fallback(const ::string & psz, i64 iDefault, i32 iBase) { from_string(iDefault, iBase, psz); return iDefault; }



} // namespace str



