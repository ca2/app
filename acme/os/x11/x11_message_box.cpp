#include "framework.h"
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>
#include <locale.h>
#include <wchar.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "_x11.h"

#if !defined(RASPBIAN)
bool x11_message_box_process_event(Display * pdisplay, XEvent & e, XGenericEventCookie * cookie);
#else
bool x11_message_box_process_event(Display * pdisplay, XEvent & e);
#endif


struct Dimensions{
    //window
    unsigned int winMinWidth;
    unsigned int winMinHeight;
    //vertical space between lines
    unsigned int lineSpacing;
    unsigned int barHeight;
    //padding
    unsigned int pad_up;
    unsigned int pad_down;
    unsigned int pad_left;
    unsigned int pad_right;
    //button
    unsigned int btSpacing;
    unsigned int btMinWidth;
    unsigned int btMinHeight;
    unsigned int btLateralPad;

};


//these values can be changed to whatever you prefer
struct Dimensions dim = {400, 0, 5, 50, 30, 10, 30, 30, 20, 75, 25, 8};


void setWindowTitle(const char* title, const Window *win, Display *dpy){
    Atom wm_Name = XInternAtom(dpy, "_NET_WM_NAME", False);
    Atom utf8Str = XInternAtom(dpy, "UTF8_STRING", False);

    Atom winType = XInternAtom(dpy, "_NET_WM_WINDOW_TYPE", False );
    Atom typeDialog = XInternAtom(dpy, "_NET_WM_WINDOW_TYPE_DIALOG", False );

    XChangeProperty(dpy, *win, wm_Name, utf8Str, 8, PropModeReplace, (const unsigned char*)title, (int)strlen(title));

    XChangeProperty( dpy,*win, winType, XA_ATOM,
                     32, PropModeReplace, (unsigned char *)&typeDialog,
                     1);
}

//void split(const wchar_t* text, const wchar_t* seps, wchar_t ***str, int *count){
//    wchar_t *last, *tok, *data;
//    int i;
//    *count = 0;
//    data = wcsdup(text);
//
//    for (tok = wcstok(data, seps, &last); tok != NULL; tok = wcstok(NULL, seps, &last))
//        (*count)++;
//
//    free(data);
//    fflush(stdout);
//    data = wcsdup(text);
//    *str = (wchar_t **)malloc((size_t)(*count)*sizeof(wchar_t*));
//
//
//    for (i = 0, tok = wcstok(data, seps, &last); tok != NULL; tok = wcstok(NULL, seps, &last), i++)
//        (*str)[i] = wcsdup(tok);
//    free(data);
//}

// void x11_text_extents(XFontSet* fs, wchar_t** texts, int size, unsigned int spaceBetweenLines,
//                      unsigned int *w,  unsigned  int *h)
// {
//     int i;
//     XRectangle rect  = {0,0,0,0};
//     *h = 0;
//     *w = 0;
//     for(i = 0; i < size; i++){
//         XwcTextExtents(*fs, texts[i], (int)wcslen(texts[i]), &rect, NULL);
//         *w = (rect.width > *w) ? (rect.width): *w;
//         *h += rect.height + spaceBetweenLines;
//         fflush(stdin);
//     }
// }

//::e_status x11MessageBoxA(const char* title, const char * text, const Button* buttons, int numButtons);



// void createGC(GC* gc, const Colormap* cmap, Display* dpy, const  Window* win,
//               unsigned char red, unsigned char green, unsigned char blue){
//     float coloratio = (float) 65535 / 255;
//     XColor color;
//     *gc = XCreateGC (dpy, *win, 0,0);
//     memset(&color, 0, sizeof(color));
//     color.red   = (unsigned short)(coloratio * red  );
//     color.green = (unsigned short)(coloratio * green);
//     color.blue  = (unsigned short)(coloratio * blue );
//     color.flags = DoRed | DoGreen | DoBlue;
//     XAllocColor (dpy, *cmap, &color);
//     XSetForeground (dpy, *gc, color.pixel);
// }



//::e_status x11MessageBoxA(const char* title, const char * text, const Button* btsData, int numButtons)
//{
//    //setlocale(LC_ALL,"");
//
////    //---- convert the text in list (to draw in multiply lines)---------------------------------------------------------
////    wchar_t** text_splitted = NULL;
////    int textLines = 0;
////    split(text, L"\n" , &text_splitted, &textLines);
////    //------------------------------------------------------------------------------------------------------------------
//
//   string_array stra;
//
//   stra.add_lines(text);
//
//   sync_lock sl(x11_mutex());
//
//    xdisplay d(x11_get_display());
//    if(!d.display()){
//
//        return ::error_failed;
//    }
//
//    int ds = DefaultScreen(d.display());
//    Window win = 0;
//
//        if(::user::is_app_dark_mode())
//        {
//
//        win= XCreateSimpleWindow(d.display(), RootWindow(d.display(), ds), 0, 0, 800, 100, 1,
//                                     WhitePixel(d.display(), ds), BlackPixel(d.display(), ds));
//
//                                     }
//                                     else
//                                     {
//    win = XCreateSimpleWindow(d.display(), RootWindow(d.display(), ds), 0, 0, 800, 100, 1,
//                                     BlackPixel(d.display(), ds), WhitePixel(d.display(), ds));
//
//}
//    XSelectInput(dpy, win, ExposureMask | PointerMotionMask | ButtonPressMask | ButtonReleaseMask);
//    //XMapWindow(dpy, win);
//
//    //allow windows to be closed by pressing cross button (but it wont close - see ClientMessage on switch)
//    Atom WM_DELETE_WINDOW = XInternAtom(dpy, "WM_DELETE_WINDOW", False);
//    XSetWMProtocols(dpy, win, &WM_DELETE_WINDOW, 1);
//
//    //--create the gc for drawing text----------------------------------------------------------------------------------
//    XGCValues gcValues;
//    gcValues.font = XLoadFont(dpy, "7x13");
//    if(::user::is_dark_mode())
//    {
//      gcValues.foreground = BlackPixel(dpy, 0);
//   }
//   else
//   {
//      gcValues.foreground = WhitePixel(dpy, 0);
//   }
//    GC textGC = XCreateGC(dpy, win, GCFont + GCForeground, &gcValues);
//    //XUnmapWindow( dpy, win );
//    //------------------------------------------------------------------------------------------------------------------
//
//    //----create fontset-----------------------------------------------------------------------------------------------
//    char **missingCharset_list = NULL;
//    int missingCharset_count = 0;
//    XFontSet fs;
//    fs = XCreateFontSet(dpy,
//                        "-*-*-medium-r-*-*-*-140-75-75-*-*-*-*" ,
//                        &missingCharset_list, &missingCharset_count, NULL);
//
//    if (missingCharset_count) {
//        fprintf(stderr, "Missing charsets :\n");
//        for(int i = 0; i < missingCharset_count; i++){
//            fprintf(stderr, "%s\n", missingCharset_list[i]);
//        }
//        XFreeStringList(missingCharset_list);
//    }
//    //------------------------------------------------------------------------------------------------------------------
//
//    Colormap cmap = DefaultColormap (dpy, ds);
//
//    //resize the window according to the text size-----------------------------------------------------------------------
//    unsigned int winW, winH;
//    unsigned int textW, textH;
//
//    //calculate the ideal window's size
//    x11_text_extents(&fs, text_splitted, textLines, dim.lineSpacing, &textW, &textH);
//    unsigned int newWidth = textW + dim.pad_left + dim.pad_right;
//    unsigned int newHeight = textH + dim.pad_up + dim.pad_down + dim.barHeight;
//    winW = (newWidth > dim.winMinWidth)? newWidth: dim.winMinWidth;
//    winH = (newHeight > dim.winMinHeight)? newHeight: dim.winMinHeight;
//
//
//
//    //set windows hints
//    XSizeHints hints;
//    hints.flags      = PSize | PMinSize | PMaxSize;
//    hints.min_width  = hints.max_width  = hints.base_width  = winW;
//    hints.min_height = hints.max_height = hints.base_height = winH;
//
//    XSetWMNormalHints( dpy, win, &hints );
//    XMapRaised( dpy, win );
//    //------------------------------------------------------------------------------------------------------------------
//
//    GC barGC;
//    GC buttonGC;
//    GC buttonGC_underPointer;
//    GC buttonGC_onClick;                               // GC colors
//    createGC(&barGC, &cmap, dpy, &win,                 242, 242, 242);
//    createGC(&buttonGC, &cmap, dpy, &win,              202, 202, 202);
//    createGC(&buttonGC_underPointer, &cmap, dpy, &win, 192, 192, 192);
//    createGC(&buttonGC_onClick, &cmap, dpy, &win,      182, 182, 182);
//
//    //---setup the buttons data-----------------------------------------------------------------------------------------
//
//    int pass = 0;
//    for(int i = 0; i < numButtons; i++){
//        btsData[i].button = &buttons[i];
//        btsData[i].gc = &buttonGC;
//        XRectangle btTextDim;
//        XwcTextExtents(fs, btsData[i].button->label, (int)wcslen(btsData[i].button->label),
//                       &btTextDim, NULL);
//        btsData[i].rect.width = (btTextDim.width < dim.btMinWidth) ? dim.btMinWidth:
//                                   (btTextDim.width + 2 * dim.btLateralPad);
//        btsData[i].rect.height = dim.btMinHeight;
//        btsData[i].rect.x = winW - dim.pad_left - btsData[i].rect.width - pass;
//        btsData[i].rect.y = textH + dim.pad_up + dim.pad_down + ((dim.barHeight - dim.btMinHeight)/ 2) ;
//        pass += btsData[i].rect.width + dim.btSpacing;
//    }
//    //------------------------------------------------------------------------------------------------------------------
//
//    setWindowTitle(title, &win, dpy);
//
//    XFlush( dpy );
//
//
//    bool quit = false;
//    int res = -1;
//
//    while( !quit ) {
//        XEvent e;
//        XNextEvent( dpy, &e );
//
//        switch (e.type){
//
//            case MotionNotify:
//            case ButtonPress:
//            case ButtonRelease:
//                for(int i = 0; i < numButtons; i++) {
//                    btsData[i].gc = &buttonGC;
//                    if (isInside(e.xmotion.x, e.xmotion.y, btsData[i].rect)) {
//                        btsData[i].gc = &buttonGC_underPointer;
//                        if(e.type == ButtonPress && e.xbutton.button == Button1) {
//                            btsData[i].gc = &buttonGC_onClick;
//                            res = btsData[i].button->result;
//                            quit = true;
//                        }
//                    }
//                }
//
//            case Expose:
//                //draw the text in multiply lines----------------------------------------------------------------------
//                for(int i = 0; i < textLines; i++){
//
//                    XwcDrawString( dpy, win, fs, textGC, dim.pad_left, dim.pad_up + i * (dim.lineSpacing + 18),
//                                   text_splitted[i], (int)wcslen(text_splitted[i]));
//                }
//                //------------------------------------------------------------------------------------------------------
//                XFillRectangle(dpy, win, barGC, 0, textH + dim.pad_up + dim.pad_down, winW, dim.barHeight);
//
//                for(int i = 0; i < numButtons; i++){
//                    XFillRectangle(dpy, win, *btsData[i].gc, btsData[i].rect.x, btsData[i].rect.y,
//                                   btsData[i].rect.width, btsData[i].rect.height);
//
//                    XRectangle btTextDim;
//                    XwcTextExtents(fs, btsData[i].button->label, (int)wcslen(btsData[i].button->label),
//                                   &btTextDim, NULL);
//                    XwcDrawString( dpy, win, fs, textGC,
//                                   btsData[i].rect.x + (btsData[i].rect.width  - btTextDim.width ) / 2,
//                                   btsData[i].rect.y + (btsData[i].rect.height + btTextDim.height) / 2,
//                                   btsData[i].button->label, (int)wcslen(btsData[i].button->label));
//                }
//                XFlush(dpy);
//
//                break;
//
//            case ClientMessage:
//                //if window's cross button pressed does nothing
//                //if((unsigned int)(e.xclient.data.l[0]) == WM_DELETE_WINDOW)
//                    //quit = true;
//                break;
//            default:
//                break;
//        }
//    }
//
//    for(int i = 0; i < textLines; i++){
//        free(text_splitted[i]);
//    }
//    free(text_splitted);
//    free(btsData);
//    XFreeStringList(missingCharset_list);
//    XDestroyWindow(dpy, win);
//    XFreeFontSet(dpy, fs);
//    XFreeGC(dpy, textGC);
//    XFreeGC(dpy, barGC);
//    XFreeGC(dpy, buttonGC);
//    XFreeGC(dpy, buttonGC_underPointer);
//    XFreeGC(dpy, buttonGC_onClick);
//    XFreeColormap(dpy, cmap);
//    XCloseDisplay(dpy);
//
//    return res;
//}
//
//#if !defined(RASPBIAN)
//bool x11_message_box_process_event(osdisplay_data * pdisplaydata, XEvent & e, XGenericEventCookie * cookie)
//#else
//bool x11_message_box_process_event(osdisplay_data * pdisplaydata, XEvent & e)
//#endif
//{
//
//
//}
