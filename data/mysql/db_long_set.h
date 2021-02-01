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
//    inline bool load(const char * lpKey, T & rvalue)
//    {
      
//       i64 i;

//       if(!load(lpKey, &i))
//          return false;

//       rvalue = (T &) i;

//       return true;

//    }

//    bool load(const char * lpKey, i64 * lValue);
//    bool load(const char * lpKey, LPRECT32 lpRect);
// #ifdef WINDOWS_DESKTOP
//    bool load(const char * lpKey, WINDOWPLACEMENT & wp);
// #endif
//    bool load(const char * lpKey, POINT_I32 * lpPoint);

//    // save Functions
//    template < typename T >
//    inline bool save(const char * lpKey, T value)
//    {
      
//       return save(lpKey, (i64) value);

//    }

//    bool save(const char * lpKey, i64 lValue);
//    bool save(const char * lpKey, const RECTANGLE_I32 * lpRect);
// #ifdef WINDOWS_DESKTOP
//    bool save(const char * lpKey, WINDOWPLACEMENT & wp);
// #endif
//    bool save(const char * lpKey, POINT_I32 * lpPoint);

//    // Search Functions
//    bool find(const char * lpKey);


//    bool MoveWindow_(const char * lpKey, ::user::interaction_impl * pwindow);
//    bool SaveWindowRect_(const char * lpKey, ::user::interaction_impl * pwindow);
//    bool SetWindowPlacement(const char * lpKey, ::user::interaction_impl * pwindow);
//    bool SaveWindowPlacement(const char * lpKey, ::user::interaction_impl * pwindow);

// };

