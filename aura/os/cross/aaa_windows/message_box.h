#pragma once


#define e_message_box_ok                       0x00000000L
#define MB_OKCANCEL                 0x00000001L
#define MB_ABORTRETRYIGNORE         0x00000002L
#define MB_YESNOCANCEL              0x00000003L
#define MB_YESNO                    0x00000004L
#define MB_RETRYCANCEL              0x00000005L
//#if(WINVER >= 0x0500)
#define MB_CANCELTRYCONTINUE        0x00000006L
//#endif /* WINVER >= 0x0500 */


#define MB_ICONHAND                 0x00000010L
#define MB_ICONQUESTION             0x00000020L
#define e_message_box_icon_exclamation          0x00000030L
#define MB_ICONASTERISK             0x00000040L

//#if(WINVER >= 0x0400)
#define MB_USERICON                 0x00000080L
#define e_message_box_icon_warning              e_message_box_icon_exclamation
#define MB_ICONERROR                MB_ICONHAND
//#endif /* WINVER >= 0x0400 */

#define e_message_box_icon_information          MB_ICONASTERISK
#define e_message_box_icon_stop                 MB_ICONHAND



