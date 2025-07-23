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
      
//       long long i;

//       if(!load(lpKey, &i))
//          return false;

//       rvalue = (T &) i;

//       return true;

//    }

//    bool load(const ::string & lpKey, long long * lValue);
//    bool load(const ::string & lpKey, ::int_rectangle * lpRect);
// #ifdef WINDOWS_DESKTOP
//    bool load(const ::string & lpKey, WINDOWPLACEMENT & wp);
// #endif
//    bool load(const ::string & lpKey, ::int_point * lpPoint);

//    // save Functions
//    template < typename T >
//    inline bool save(const ::string & lpKey, T value)
//    {
      
//       return save(lpKey, (long long) value);

//    }

//    bool save(const ::string & lpKey, long long lValue);
//    bool save(const ::string & lpKey, const ::int_rectangle * lpRect);
// #ifdef WINDOWS_DESKTOP
//    bool save(const ::string & lpKey, WINDOWPLACEMENT & wp);
// #endif
//    bool save(const ::string & lpKey, ::int_point * lpPoint);

//    // Search Functions
//    bool find(const ::string & lpKey);


//    bool MoveWindow_(const ::string & lpKey, ::windowing::window * pwindow);
//    bool SaveWindowRectangle(const ::string & lpKey, ::windowing::window * pwindow);
//    bool SetWindowPlacement(const ::string & lpKey, ::windowing::window * pwindow);
//    bool SaveWindowPlacement(const ::string & lpKey, ::windowing::window * pwindow);

// };

