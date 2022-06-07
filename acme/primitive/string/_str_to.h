

      iptr         to_iptr(const ::string & psz);
      i32          to_i32(const ::string & psz);
      u32          to_u32(const ::string & psz);


    i64           to_i64(const ::string & psz);
    u64           to_u64(const ::string & psz);



    inline    i32 to_with_fallback(const ::string & psz, i32 iDefault);
    inline   i64 to_with_fallback(const ::string & psz, i64 iDefault);
    inline   i32 to_with_fallback(const ::string & psz, i32 iDefault, i32 iBase);
    inline   i64 to_with_fallback(const ::string & psz, i64 iDefault, i32 iBase);


