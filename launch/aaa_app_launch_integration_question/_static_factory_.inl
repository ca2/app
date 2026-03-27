#ifdef CONSOLE_INTEGRATION_NO_AUDIO
#define DO_FACTORY(do) \
do(apex_node); \
do(networking_bsd); \
do(folder_zip);\

#else
#define DO_FACTORY(do) \
do(default_text_to_speech);\
do(apex_node); \
do(networking_bsd); \
do(audio);\
do(default_audio);\
do(folder_zip);\
do(audio_resample_swresample);\



#endif
