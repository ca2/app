//
//  _unit_operator.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 15/10/21 09:27 BRT.
//  Copyright (c) 2021 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#pragma once
//template < a_enum ENUM >
//inline int operator -(UniChar ush, ENUM e) { return ush - (int) e; }

//template < primitive_integral INTEGRAL >
//inline integral_nanosecond operator %(const integral_nanosecond & time, INTEGRAL integral) { return integral_nanosecond((huge_integer)(time.m_i % integral)); }
template < primitive_integral INTEGRAL >
inline integral_nanosecond operator /(const integral_nanosecond & time, INTEGRAL integral) { return integral_nanosecond((huge_integer)(time.m_i / integral)); }
template < primitive_integral INTEGRAL >
inline integral_nanosecond operator *(const integral_nanosecond & time, INTEGRAL integral) { return integral_nanosecond((huge_integer)(time.m_i * integral)); }
//template < primitive_integral INTEGRAL >
//inline integral_nanosecond operator +(const integral_nanosecond & time, INTEGRAL integral) { return integral_nanosecond((huge_integer)(time.m_i + integral)); }
//template < primitive_integral INTEGRAL >
//inline integral_nanosecond operator -(const integral_nanosecond & time, INTEGRAL integral) { return integral_nanosecond((huge_integer)(time.m_i - integral)); }


//template < primitive_integral INTEGRAL >
//inline integral_microsecond operator %(const integral_microsecond & time, INTEGRAL integral) { return integral_microsecond((huge_integer)(time.m_i % integral)); }
template < primitive_integral INTEGRAL >
inline integral_microsecond operator /(const integral_microsecond & time, INTEGRAL integral) { return integral_microsecond((huge_integer)(time.m_i / integral)); }
template < primitive_integral INTEGRAL >
inline integral_microsecond operator *(const integral_microsecond & time, INTEGRAL integral) { return integral_microsecond((huge_integer)(time.m_i * integral)); }
//template < primitive_integral INTEGRAL >
//inline integral_microsecond operator +(const integral_microsecond & time, INTEGRAL integral) { return integral_microsecond((huge_integer)(time.m_i + integral)); }
//template < primitive_integral INTEGRAL >
//inline integral_microsecond operator -(const integral_microsecond & time, INTEGRAL integral) { return integral_microsecond((huge_integer)(time.m_i - integral)); }


//template < primitive_integral INTEGRAL >
//inline integral_millisecond operator %(const integral_millisecond & time, INTEGRAL integral) { return integral_millisecond((huge_integer)(time.m_i % integral)); }
template < primitive_integral INTEGRAL >
inline integral_millisecond operator /(const integral_millisecond & time, INTEGRAL integral) { return integral_millisecond((huge_integer)(time.m_i / integral)); }
template < primitive_integral INTEGRAL >
inline integral_millisecond operator *(const integral_millisecond & time, INTEGRAL integral) { return integral_millisecond((huge_integer)(time.m_i * integral)); }
//template < primitive_integral INTEGRAL >
//inline integral_millisecond operator +(const integral_millisecond & time, INTEGRAL integral) { return integral_millisecond((huge_integer)(time.m_i + integral)); }
//template < primitive_integral INTEGRAL >
//inline integral_millisecond operator -(const integral_millisecond & time, INTEGRAL integral) { return integral_millisecond((huge_integer)(time.m_i - integral)); }


//template < primitive_integral INTEGRAL >
//inline integral_second operator %(const integral_second & time, INTEGRAL integral) { return integral_second((huge_integer)(time.m_i % integral)); }
template < primitive_integral INTEGRAL >
inline integral_second operator /(const integral_second & time, INTEGRAL integral) { return integral_second((huge_integer)(time.m_i / integral)); }
template < primitive_integral INTEGRAL >
inline integral_second operator *(const integral_second & time, INTEGRAL integral) { return integral_second((huge_integer)(time.m_i * integral)); }
//template < primitive_integral INTEGRAL >
//inline integral_second operator +(const integral_second & time, INTEGRAL integral) { return integral_second((huge_integer)(time.m_i + integral)); }
//template < primitive_integral INTEGRAL >
//inline integral_second operator -(const integral_second & time, INTEGRAL integral) { return integral_second((huge_integer)(time.m_i - integral)); }


//template < primitive_integral INTEGRAL >
//inline integral_minute operator %(const integral_minute & time, INTEGRAL integral) { return integral_minute((huge_integer)(time.m_i % integral)); }
template < primitive_integral INTEGRAL >
inline integral_minute operator /(const integral_minute & time, INTEGRAL integral) { return integral_minute((huge_integer)(time.m_i / integral)); }
template < primitive_integral INTEGRAL >
inline integral_minute operator *(const integral_minute & time, INTEGRAL integral) { return integral_minute((huge_integer)(time.m_i * integral)); }
//template < primitive_integral INTEGRAL >
//inline integral_minute operator +(const integral_minute & time, INTEGRAL integral) { return integral_minute((huge_integer)(time.m_i + integral)); }
//template < primitive_integral INTEGRAL >
//inline integral_minute operator -(const integral_minute & time, INTEGRAL integral) { return integral_minute((huge_integer)(time.m_i - integral)); }


//template < primitive_integral INTEGRAL >
//inline integral_hour operator %(const integral_hour & time, INTEGRAL integral) { return integral_hour((huge_integer)(time.m_i % integral)); }
template < primitive_integral INTEGRAL >
inline integral_hour operator /(const integral_hour & time, INTEGRAL integral) { return integral_hour((huge_integer)(time.m_i / integral)); }
template < primitive_integral INTEGRAL >
inline integral_hour operator *(const integral_hour & time, INTEGRAL integral) { return integral_hour((huge_integer)(time.m_i * integral)); }
//template < primitive_integral INTEGRAL >
//inline integral_hour operator +(const integral_hour & time, INTEGRAL integral) { return integral_hour((huge_integer)(time.m_i + integral)); }
//template < primitive_integral INTEGRAL >
//inline integral_hour operator -(const integral_hour & time, INTEGRAL integral) { return integral_hour((huge_integer)(time.m_i - integral)); }


//template < primitive_integral INTEGRAL >
//inline integral_day operator %(const integral_day & time, INTEGRAL integral) { return integral_day(time.m_i % integral); }
template < primitive_integral INTEGRAL >
inline integral_day operator /(const integral_day & time, INTEGRAL integral) { return integral_day(time.m_i / integral); }
template < primitive_integral INTEGRAL >
inline integral_day operator *(const integral_day & time, INTEGRAL integral) { return integral_day(time.m_i * integral); }
//template < primitive_integral INTEGRAL >
//inline integral_day operator +(const integral_day & time, INTEGRAL integral) { return integral_day(time.m_i + integral); }
//template < primitive_integral INTEGRAL >
//inline integral_day operator -(const integral_day & time, INTEGRAL integral) { return integral_day(time.m_i - integral); }


//template < primitive_floating FLOATING >
//inline integral_nanosecond operator %(const integral_nanosecond & time, FLOATING floating) { return integral_nanosecond((huge_integer)(time.m_i % floating)); }
template < primitive_floating FLOATING >
inline integral_nanosecond operator /(const integral_nanosecond & time, FLOATING floating) { return integral_nanosecond((huge_integer)(time.m_i / floating)); }
template < primitive_floating FLOATING >
inline integral_nanosecond operator *(const integral_nanosecond & time, FLOATING floating) { return integral_nanosecond((huge_integer)(time.m_i * floating)); }
//template < primitive_floating FLOATING >
//inline integral_nanosecond operator +(const integral_nanosecond & time, FLOATING floating) { return integral_nanosecond((huge_integer)(time.m_i + floating)); }
//template < primitive_floating FLOATING >
//inline integral_nanosecond operator -(const integral_nanosecond & time, FLOATING floating) { return integral_nanosecond((huge_integer)(time.m_i - floating)); }


//template < primitive_floating FLOATING >
//inline integral_microsecond operator %(const integral_microsecond & time, FLOATING floating) { return integral_microsecond((huge_integer)(time.m_i % floating)); }
template < primitive_floating FLOATING >
inline integral_microsecond operator /(const integral_microsecond & time, FLOATING floating) { return integral_microsecond((huge_integer)(time.m_i / floating)); }
template < primitive_floating FLOATING >
inline integral_microsecond operator *(const integral_microsecond & time, FLOATING floating) { return integral_microsecond((huge_integer)(time.m_i * floating)); }
//template < primitive_floating FLOATING >
//inline integral_microsecond operator +(const integral_microsecond & time, FLOATING floating) { return integral_microsecond((huge_integer)(time.m_i + floating)); }
//template < primitive_floating FLOATING >
//inline integral_microsecond operator -(const integral_microsecond & time, FLOATING floating) { return integral_microsecond((huge_integer)(time.m_i - floating)); }


//template < primitive_floating FLOATING >
//inline integral_millisecond operator %(const integral_millisecond & time, FLOATING floating) { return integral_millisecond((huge_integer)(time.m_i % floating)); }
template < primitive_floating FLOATING >
inline integral_millisecond operator /(const integral_millisecond & time, FLOATING floating) { return integral_millisecond((huge_integer)(time.m_i / floating)); }
template < primitive_floating FLOATING >
inline integral_millisecond operator *(const integral_millisecond & time, FLOATING floating) { return integral_millisecond((huge_integer)(time.m_i * floating)); }
//template < primitive_floating FLOATING >
//inline integral_millisecond operator +(const integral_millisecond & time, FLOATING floating) { return integral_millisecond((huge_integer)(time.m_i + floating)); }
//template < primitive_floating FLOATING >
//inline integral_millisecond operator -(const integral_millisecond & time, FLOATING floating) { return integral_millisecond((huge_integer)(time.m_i - floating)); }


//template < primitive_floating FLOATING >
//inline integral_second operator %(const integral_second & time, FLOATING floating) { return integral_second((huge_integer)(time.m_i % floating)); }
template < primitive_floating FLOATING >
inline integral_second operator /(const integral_second & time, FLOATING floating) { return integral_second((huge_integer)(time.m_i / floating)); }
template < primitive_floating FLOATING >
inline integral_second operator *(const integral_second & time, FLOATING floating) { return integral_second((huge_integer)(time.m_i * floating)); }
//template < primitive_floating FLOATING >
//inline integral_second operator +(const integral_second & time, FLOATING floating) { return integral_second((huge_integer)(time.m_i + floating)); }
//template < primitive_floating FLOATING >
//inline integral_second operator -(const integral_second & time, FLOATING floating) { return integral_second((huge_integer)(time.m_i - floating)); }


//template < primitive_floating FLOATING >
//inline integral_minute operator %(const integral_minute & time, FLOATING floating) { return integral_minute((huge_integer)(time.m_i % floating)); }
template < primitive_floating FLOATING >
inline integral_minute operator /(const integral_minute & time, FLOATING floating) { return integral_minute((huge_integer)(time.m_i / floating)); }
template < primitive_floating FLOATING >
inline integral_minute operator *(const integral_minute & time, FLOATING floating) { return integral_minute((huge_integer)(time.m_i * floating)); }
//template < primitive_floating FLOATING >
//inline integral_minute operator +(const integral_minute & time, FLOATING floating) { return integral_minute((huge_integer)(time.m_i + floating)); }
//template < primitive_floating FLOATING >
//inline integral_minute operator -(const integral_minute & time, FLOATING floating) { return integral_minute((huge_integer)(time.m_i - floating)); }


//template < primitive_floating FLOATING >
//inline integral_hour operator %(const integral_hour & time, FLOATING floating) { return integral_hour((huge_integer)(time.m_i % floating)); }
template < primitive_floating FLOATING >
inline integral_hour operator /(const integral_hour & time, FLOATING floating) { return integral_hour((huge_integer)(time.m_i / floating)); }
template < primitive_floating FLOATING >
inline integral_hour operator *(const integral_hour & time, FLOATING floating) { return integral_hour((huge_integer)(time.m_i * floating)); }
//template < primitive_floating FLOATING >
//inline integral_hour operator +(const integral_hour & time, FLOATING floating) { return integral_hour((huge_integer)(time.m_i + floating)); }
//template < primitive_floating FLOATING >
//inline integral_hour operator -(const integral_hour & time, FLOATING floating) { return integral_hour((huge_integer)(time.m_i - floating)); }


//template < primitive_floating FLOATING >
//inline integral_day operator %(const integral_day & time, FLOATING floating) { return integral_day(time.m_i % floating); }
template < primitive_floating FLOATING >
inline integral_day operator /(const integral_day & time, FLOATING floating) { return integral_day(time.m_i / floating); }
template < primitive_floating FLOATING >
inline integral_day operator *(const integral_day & time, FLOATING floating) { return integral_day(time.m_i * floating); }
//template < primitive_floating FLOATING >
//inline integral_day operator +(const integral_day & time, FLOATING floating) { return integral_day(time.m_i + floating); }
//template < primitive_floating FLOATING >
//inline integral_day operator -(const integral_day & time, FLOATING floating) { return integral_day(time.m_i - floating); }


//template < primitive_integral INTEGRAL >
//inline floating_nanosecond operator %(const floating_nanosecond & time, INTEGRAL integral) { return floating_nanosecond((double)(time.m_d % integral)); }
template < primitive_integral INTEGRAL >
inline floating_nanosecond operator /(const floating_nanosecond & time, INTEGRAL integral) { return floating_nanosecond((double)(time.m_d / integral)); }
template < primitive_integral INTEGRAL >
inline floating_nanosecond operator *(const floating_nanosecond & time, INTEGRAL integral) { return floating_nanosecond((double)(time.m_d * integral)); }
//template < primitive_integral INTEGRAL >
//inline floating_nanosecond operator +(const floating_nanosecond & time, INTEGRAL integral) { return floating_nanosecond((double)(time.m_d + integral)); }
//template < primitive_integral INTEGRAL >
//inline floating_nanosecond operator -(const floating_nanosecond & time, INTEGRAL integral) { return floating_nanosecond((double)(time.m_d - integral)); }


//template < primitive_integral INTEGRAL >
//inline floating_microsecond operator %(const floating_microsecond & time, INTEGRAL integral) { return floating_microsecond((double)(time.m_d % integral)); }
template < primitive_integral INTEGRAL >
inline floating_microsecond operator /(const floating_microsecond & time, INTEGRAL integral) { return floating_microsecond((double)(time.m_d / integral)); }
template < primitive_integral INTEGRAL >
inline floating_microsecond operator *(const floating_microsecond & time, INTEGRAL integral) { return floating_microsecond((double)(time.m_d * integral)); }
//template < primitive_integral INTEGRAL >
//inline floating_microsecond operator +(const floating_microsecond & time, INTEGRAL integral) { return floating_microsecond((double)(time.m_d + integral)); }
//template < primitive_integral INTEGRAL >
//inline floating_microsecond operator -(const floating_microsecond & time, INTEGRAL integral) { return floating_microsecond((double)(time.m_d - integral)); }


//template < primitive_integral INTEGRAL >
//inline floating_millisecond operator %(const floating_millisecond & time, INTEGRAL integral) { return floating_millisecond((double)(time.m_d % integral)); }
template < primitive_integral INTEGRAL >
inline floating_millisecond operator /(const floating_millisecond & time, INTEGRAL integral) { return floating_millisecond((double)(time.m_d / integral)); }
template < primitive_integral INTEGRAL >
inline floating_millisecond operator *(const floating_millisecond & time, INTEGRAL integral) { return floating_millisecond((double)(time.m_d * integral)); }
//template < primitive_integral INTEGRAL >
//inline floating_millisecond operator +(const floating_millisecond & time, INTEGRAL integral) { return floating_millisecond((double)(time.m_d + integral)); }
//template < primitive_integral INTEGRAL >
//inline floating_millisecond operator -(const floating_millisecond & time, INTEGRAL integral) { return floating_millisecond((double)(time.m_d - integral)); }


//template < primitive_integral INTEGRAL >
//inline floating_second operator %(const floating_second & time, INTEGRAL integral) { return floating_second((double)(time.m_d % integral)); }
template < primitive_integral INTEGRAL >
inline floating_second operator /(const floating_second & time, INTEGRAL integral) { return floating_second((double)(time.m_d / integral)); }
template < primitive_integral INTEGRAL >
inline floating_second operator *(const floating_second & time, INTEGRAL integral) { return floating_second((double)(time.m_d * integral)); }
//template < primitive_integral INTEGRAL >
//inline floating_second operator +(const floating_second & time, INTEGRAL integral) { return floating_second((double)(time.m_d + integral)); }
//template < primitive_integral INTEGRAL >
//inline floating_second operator -(const floating_second & time, INTEGRAL integral) { return floating_second((double)(time.m_d - integral)); }


//template < primitive_integral INTEGRAL >
//inline floating_minute operator %(const floating_minute & time, INTEGRAL integral) { return floating_minute((double)(time.m_d % integral)); }
template < primitive_integral INTEGRAL >
inline floating_minute operator /(const floating_minute & time, INTEGRAL integral) { return floating_minute((double)(time.m_d / integral)); }
template < primitive_integral INTEGRAL >
inline floating_minute operator *(const floating_minute & time, INTEGRAL integral) { return floating_minute((double)(time.m_d * integral)); }
//template < primitive_integral INTEGRAL >
//inline floating_minute operator +(const floating_minute & time, INTEGRAL integral) { return floating_minute((double)(time.m_d + integral)); }
//template < primitive_integral INTEGRAL >
//inline floating_minute operator -(const floating_minute & time, INTEGRAL integral) { return floating_minute((double)(time.m_d - integral)); }


//template < primitive_integral INTEGRAL >
//inline floating_hour operator %(const floating_hour & time, INTEGRAL integral) { return floating_hour((double)(time.m_d % integral)); }
template < primitive_integral INTEGRAL >
inline floating_hour operator /(const floating_hour & time, INTEGRAL integral) { return floating_hour((double)(time.m_d / integral)); }
template < primitive_integral INTEGRAL >
inline floating_hour operator *(const floating_hour & time, INTEGRAL integral) { return floating_hour((double)(time.m_d * integral)); }
//template < primitive_integral INTEGRAL >
//inline floating_hour operator +(const floating_hour & time, INTEGRAL integral) { return floating_hour((double)(time.m_d + integral)); }
//template < primitive_integral INTEGRAL >
//inline floating_hour operator -(const floating_hour & time, INTEGRAL integral) { return floating_hour((double)(time.m_d - integral)); }


//template < primitive_integral INTEGRAL >
//inline floating_day operator %(const floating_day & time, INTEGRAL integral) { return floating_day(time.m_d % integral); }
template < primitive_integral INTEGRAL >
inline floating_day operator /(const floating_day & time, INTEGRAL integral) { return floating_day(time.m_d / integral); }
template < primitive_integral INTEGRAL >
inline floating_day operator *(const floating_day & time, INTEGRAL integral) { return floating_day(time.m_d * integral); }
//template < primitive_integral INTEGRAL >
//inline floating_day operator +(const floating_day & time, INTEGRAL integral) { return floating_day(time.m_d + integral); }
//template < primitive_integral INTEGRAL >
//inline floating_day operator -(const floating_day & time, INTEGRAL integral) { return floating_day(time.m_d - integral); }


//template < primitive_floating FLOATING >
//inline floating_nanosecond operator %(const floating_nanosecond & time, FLOATING floating) { return floating_nanosecond((double)(time.m_d % floating)); }
template < primitive_floating FLOATING >
inline floating_nanosecond operator /(const floating_nanosecond & time, FLOATING floating) { return floating_nanosecond((double)(time.m_d / floating)); }
template < primitive_floating FLOATING >
inline floating_nanosecond operator *(const floating_nanosecond & time, FLOATING floating) { return floating_nanosecond((double)(time.m_d * floating)); }
//template < primitive_floating FLOATING >
//inline floating_nanosecond operator +(const floating_nanosecond & time, FLOATING floating) { return floating_nanosecond((double)(time.m_d + floating)); }
//template < primitive_floating FLOATING >
//inline floating_nanosecond operator -(const floating_nanosecond & time, FLOATING floating) { return floating_nanosecond((double)(time.m_d - floating)); }


//template < primitive_floating FLOATING >
//inline floating_microsecond operator %(const floating_microsecond & time, FLOATING floating) { return floating_microsecond((double)(time.m_d % floating)); }
template < primitive_floating FLOATING >
inline floating_microsecond operator /(const floating_microsecond & time, FLOATING floating) { return floating_microsecond((double)(time.m_d / floating)); }
template < primitive_floating FLOATING >
inline floating_microsecond operator *(const floating_microsecond & time, FLOATING floating) { return floating_microsecond((double)(time.m_d * floating)); }
//template < primitive_floating FLOATING >
//inline floating_microsecond operator +(const floating_microsecond & time, FLOATING floating) { return floating_microsecond((double)(time.m_d + floating)); }
//template < primitive_floating FLOATING >
//inline floating_microsecond operator -(const floating_microsecond & time, FLOATING floating) { return floating_microsecond((double)(time.m_d - floating)); }


//template < primitive_floating FLOATING >
//inline floating_millisecond operator %(const floating_millisecond & time, FLOATING floating) { return floating_millisecond((double)(time.m_d % floating)); }
template < primitive_floating FLOATING >
inline floating_millisecond operator /(const floating_millisecond & time, FLOATING floating) { return floating_millisecond((double)(time.m_d / floating)); }
template < primitive_floating FLOATING >
inline floating_millisecond operator *(const floating_millisecond & time, FLOATING floating) { return floating_millisecond((double)(time.m_d * floating)); }
//template < primitive_floating FLOATING >
//inline floating_millisecond operator +(const floating_millisecond & time, FLOATING floating) { return floating_millisecond((double)(time.m_d + floating)); }
//template < primitive_floating FLOATING >
//inline floating_millisecond operator -(const floating_millisecond & time, FLOATING floating) { return floating_millisecond((double)(time.m_d - floating)); }


//template < primitive_floating FLOATING >
//inline floating_second operator %(const floating_second & time, FLOATING floating) { return floating_second((double)(time.m_d % floating)); }
template < primitive_floating FLOATING >
inline floating_second operator /(const floating_second & time, FLOATING floating) { return floating_second((double)(time.m_d / floating)); }
template < primitive_floating FLOATING >
inline floating_second operator *(const floating_second & time, FLOATING floating) { return floating_second((double)(time.m_d * floating)); }
//template < primitive_floating FLOATING >
//inline floating_second operator +(const floating_second & time, FLOATING floating) { return floating_second((double)(time.m_d + floating)); }
//template < primitive_floating FLOATING >
//inline floating_second operator -(const floating_second & time, FLOATING floating) { return floating_second((double)(time.m_d - floating)); }


//template < primitive_floating FLOATING >
//inline floating_minute operator %(const floating_minute & time, FLOATING floating) { return floating_minute((double)(time.m_d % floating)); }
template < primitive_floating FLOATING >
inline floating_minute operator /(const floating_minute & time, FLOATING floating) { return floating_minute((double)(time.m_d / floating)); }
template < primitive_floating FLOATING >
inline floating_minute operator *(const floating_minute & time, FLOATING floating) { return floating_minute((double)(time.m_d * floating)); }
//template < primitive_floating FLOATING >
//inline floating_minute operator +(const floating_minute & time, FLOATING floating) { return floating_minute((double)(time.m_d + floating)); }
//template < primitive_floating FLOATING >
//inline floating_minute operator -(const floating_minute & time, FLOATING floating) { return floating_minute((double)(time.m_d - floating)); }


//template < primitive_floating FLOATING >
//inline floating_hour operator %(const floating_hour & time, FLOATING floating) { return floating_hour((double)(time.m_d % floating)); }
template < primitive_floating FLOATING >
inline floating_hour operator /(const floating_hour & time, FLOATING floating) { return floating_hour((double)(time.m_d / floating)); }
template < primitive_floating FLOATING >
inline floating_hour operator *(const floating_hour & time, FLOATING floating) { return floating_hour((double)(time.m_d * floating)); }
//template < primitive_floating FLOATING >
//inline floating_hour operator +(const floating_hour & time, FLOATING floating) { return floating_hour((double)(time.m_d + floating)); }
//template < primitive_floating FLOATING >
//inline floating_hour operator -(const floating_hour & time, FLOATING floating) { return floating_hour((double)(time.m_d - floating)); }


//template < primitive_floating FLOATING >
//inline floating_day operator %(const floating_day & time, FLOATING floating) { return floating_day(time.m_d % floating); }
template < primitive_floating FLOATING >
inline floating_day operator /(const floating_day & time, FLOATING floating) { return floating_day(time.m_d / floating); }
template < primitive_floating FLOATING >
inline floating_day operator *(const floating_day & time, FLOATING floating) { return floating_day(time.m_d * floating); }
//template < primitive_floating FLOATING >
//inline floating_day operator +(const floating_day & time, FLOATING floating) { return floating_day(time.m_d + floating); }
//template < primitive_floating FLOATING >
//inline floating_day operator -(const floating_day & time, FLOATING floating) { return floating_day(time.m_d - floating); }

