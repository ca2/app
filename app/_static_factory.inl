#ifdef ANDROID
#define default_node node_android
#define default_windowing windowing_android
#define default_draw2d draw2d_cairo
#endif

#define DO_FACTORY(do) \
do(default_draw2d); \
do(default_node); \
do(default_windowing); \
do(crypto_openssl);

