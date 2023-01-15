// Created by camilo on 2022-11-02 06:00 <3ThomasBorregaardSørensen!!


#if defined(WINDOWS) && !PREFER_MALLOC  && !(defined(__VLD) || defined(__MCRTDBG))


#include "WindowsHeapAlloc.cpp"


#else


#include "malloc.cpp"


#endif



