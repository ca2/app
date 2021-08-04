#pragma once



// class CLASS_DECL_AURA db_long_set :
//    virtual public ::object
// {
// public:


//    class db_long_set_core *            m_pcore;


//    db_long_set(db_server * pdatacentral);
//    ~db_long_set();



//    // load Functions
//    template < typename T >
//    inline bool load(const ::string & lpKey, T & rvalue)
//    {
      
//       i64 i;

//       if(!load(lpKey, &i))
//          return false;

//       rvalue = (T &) i;

//       return true;

//    }

//    bool load(const ::string & lpKey, i64 * lValue);
//    bool load(const ::string & lpKey, RECTANGLE_I32 * lpRect);
// #ifdef WINDOWS_DESKTOP
//    bool load(const ::string & lpKey, WINDOWPLACEMENT & wp);
// #endif
//    bool load(const ::string & lpKey, POINT_I32 * lpPoint);

//    // save Functions
//    template < typename T >
//    inline bool save(const ::string & lpKey, T value)
//    {
      
//       return save(lpKey, (i64) value);

//    }

//    bool save(const ::string & lpKey, i64 lValue);
//    bool save(const ::string & lpKey, const RECTANGLE_I32 * lpRect);
// #ifdef WINDOWS_DESKTOP
//    bool save(const ::string & lpKey, WINDOWPLACEMENT & wp);
// #endif
//    bool save(const ::string & lpKey, POINT_I32 * lpPoint);

//    // Search Functions
//    bool find(const ::string & lpKey);


//    bool MoveWindow_(const ::string & lpKey, ::user::interaction_impl * pwindow);
//    bool SaveWindowRect_(const ::string & lpKey, ::user::interaction_impl * pwindow);
//    bool SetWindowPlacement(const ::string & lpKey, ::user::interaction_impl * pwindow);
//    bool SaveWindowPlacement(const ::string & lpKey, ::user::interaction_impl * pwindow);

// };

