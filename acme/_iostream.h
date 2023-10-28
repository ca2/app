#pragma once


#if defined(__STD_FORMAT__)


// Created by speccylad(twitch)/turd(discord) 2023-10-27 ~09:00 BRT

#include <format>
#include <iostream>
#include <string>
#include <utility>

#include "framework.h"

#define _FMT_DEF inline
//
//// Simple specialization for strings in the Ca2 framework.
//// This just uses ::string::c_str() to format.
//template<>
//struct std::formatter<::string> : std::formatter<std::string> {
//    template<class FormatContext>
//    auto format(const ::string& value, FormatContext& fc) const
//    {
//        return std::formatter<std::string>::format(value.c_str(), fc);
//    }
//};

// NOTE: "fmt" is marked as const in all of these function declarations 
// because std::format() also does this. I'm just following what they've 
// done as I assume there's good reason.

//template<typename... Ts>
//inline ::string format(const std::format_string<Ts...> fmt, Ts&&... args) {
//    return ::string(std::format(fmt, std::forward<Ts>(args)...));
//}


// print formatted output to std::cout without a newline
template<typename... Ts>
inline void print(const std::format_string<Ts...> fmt, Ts&&... args) {
    const auto _Fmtd = std::format(fmt, std::forward<Ts>(args)...);
    std::cout << _Fmtd;
}


// print formatted output to std::cout with a newline
template<typename... Ts>
inline void println(const std::format_string<Ts...> fmt, Ts&&... args) {
    const auto _Fmtd = std::format(fmt, std::forward<Ts>(args)...);
    std::cout << _Fmtd << '\n';
}


// print formatted output to std::cerr without a newline
template<typename... Ts>
inline void eprint(const std::format_string<Ts...> fmt, Ts&&... args) {
    const auto _Fmtd = std::format(fmt, std::forward<Ts>(args)...);
    std::cerr << _Fmtd;
}

// print formatted output to std::cerr with a newline
template<typename... Ts>
inline void eprintln(const std::format_string<Ts...> fmt, Ts&&... args) {
    const auto _Fmtd = std::format(fmt, std::forward<Ts>(args)...);
    std::cerr << _Fmtd << '\n';
}


#endif // __STD_FORMAT__



