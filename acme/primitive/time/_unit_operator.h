//
//  _unit_operator.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 15/10/21 09:27 BRT.
//  Copyright © 2021 Camilo Sasuke Thomas Borregaard Sørensen. All rights reserved.
//
#pragma once
//template < a_enum ENUM >
//inline int operator -(UniChar ush, ENUM e) { return ush - (int) e; }

//template < primitive_integral INTEGRAL >
//inline INTEGRAL_NANOSECOND operator %(const INTEGRAL_NANOSECOND & time, INTEGRAL integral) { return INTEGRAL_NANOSECOND((::i64)(time.m_i % integral)); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_NANOSECOND operator /(const INTEGRAL_NANOSECOND & time, INTEGRAL integral) { return INTEGRAL_NANOSECOND((::i64)(time.m_i / integral)); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_NANOSECOND operator *(const INTEGRAL_NANOSECOND & time, INTEGRAL integral) { return INTEGRAL_NANOSECOND((::i64)(time.m_i * integral)); }
//template < primitive_integral INTEGRAL >
//inline INTEGRAL_NANOSECOND operator +(const INTEGRAL_NANOSECOND & time, INTEGRAL integral) { return INTEGRAL_NANOSECOND((::i64)(time.m_i + integral)); }
//template < primitive_integral INTEGRAL >
//inline INTEGRAL_NANOSECOND operator -(const INTEGRAL_NANOSECOND & time, INTEGRAL integral) { return INTEGRAL_NANOSECOND((::i64)(time.m_i - integral)); }


//template < primitive_integral INTEGRAL >
//inline INTEGRAL_MICROSECOND operator %(const INTEGRAL_MICROSECOND & time, INTEGRAL integral) { return INTEGRAL_MICROSECOND((::i64)(time.m_i % integral)); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_MICROSECOND operator /(const INTEGRAL_MICROSECOND & time, INTEGRAL integral) { return INTEGRAL_MICROSECOND((::i64)(time.m_i / integral)); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_MICROSECOND operator *(const INTEGRAL_MICROSECOND & time, INTEGRAL integral) { return INTEGRAL_MICROSECOND((::i64)(time.m_i * integral)); }
//template < primitive_integral INTEGRAL >
//inline INTEGRAL_MICROSECOND operator +(const INTEGRAL_MICROSECOND & time, INTEGRAL integral) { return INTEGRAL_MICROSECOND((::i64)(time.m_i + integral)); }
//template < primitive_integral INTEGRAL >
//inline INTEGRAL_MICROSECOND operator -(const INTEGRAL_MICROSECOND & time, INTEGRAL integral) { return INTEGRAL_MICROSECOND((::i64)(time.m_i - integral)); }


//template < primitive_integral INTEGRAL >
//inline INTEGRAL_MILLISECOND operator %(const INTEGRAL_MILLISECOND & time, INTEGRAL integral) { return INTEGRAL_MILLISECOND((::i64)(time.m_i % integral)); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_MILLISECOND operator /(const INTEGRAL_MILLISECOND & time, INTEGRAL integral) { return INTEGRAL_MILLISECOND((::i64)(time.m_i / integral)); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_MILLISECOND operator *(const INTEGRAL_MILLISECOND & time, INTEGRAL integral) { return INTEGRAL_MILLISECOND((::i64)(time.m_i * integral)); }
//template < primitive_integral INTEGRAL >
//inline INTEGRAL_MILLISECOND operator +(const INTEGRAL_MILLISECOND & time, INTEGRAL integral) { return INTEGRAL_MILLISECOND((::i64)(time.m_i + integral)); }
//template < primitive_integral INTEGRAL >
//inline INTEGRAL_MILLISECOND operator -(const INTEGRAL_MILLISECOND & time, INTEGRAL integral) { return INTEGRAL_MILLISECOND((::i64)(time.m_i - integral)); }


//template < primitive_integral INTEGRAL >
//inline INTEGRAL_SECOND operator %(const INTEGRAL_SECOND & time, INTEGRAL integral) { return INTEGRAL_SECOND((::i64)(time.m_i % integral)); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_SECOND operator /(const INTEGRAL_SECOND & time, INTEGRAL integral) { return INTEGRAL_SECOND((::i64)(time.m_i / integral)); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_SECOND operator *(const INTEGRAL_SECOND & time, INTEGRAL integral) { return INTEGRAL_SECOND((::i64)(time.m_i * integral)); }
//template < primitive_integral INTEGRAL >
//inline INTEGRAL_SECOND operator +(const INTEGRAL_SECOND & time, INTEGRAL integral) { return INTEGRAL_SECOND((::i64)(time.m_i + integral)); }
//template < primitive_integral INTEGRAL >
//inline INTEGRAL_SECOND operator -(const INTEGRAL_SECOND & time, INTEGRAL integral) { return INTEGRAL_SECOND((::i64)(time.m_i - integral)); }


//template < primitive_integral INTEGRAL >
//inline INTEGRAL_MINUTE operator %(const INTEGRAL_MINUTE & time, INTEGRAL integral) { return INTEGRAL_MINUTE((::i64)(time.m_i % integral)); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_MINUTE operator /(const INTEGRAL_MINUTE & time, INTEGRAL integral) { return INTEGRAL_MINUTE((::i64)(time.m_i / integral)); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_MINUTE operator *(const INTEGRAL_MINUTE & time, INTEGRAL integral) { return INTEGRAL_MINUTE((::i64)(time.m_i * integral)); }
//template < primitive_integral INTEGRAL >
//inline INTEGRAL_MINUTE operator +(const INTEGRAL_MINUTE & time, INTEGRAL integral) { return INTEGRAL_MINUTE((::i64)(time.m_i + integral)); }
//template < primitive_integral INTEGRAL >
//inline INTEGRAL_MINUTE operator -(const INTEGRAL_MINUTE & time, INTEGRAL integral) { return INTEGRAL_MINUTE((::i64)(time.m_i - integral)); }


//template < primitive_integral INTEGRAL >
//inline INTEGRAL_HOUR operator %(const INTEGRAL_HOUR & time, INTEGRAL integral) { return INTEGRAL_HOUR((::i64)(time.m_i % integral)); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_HOUR operator /(const INTEGRAL_HOUR & time, INTEGRAL integral) { return INTEGRAL_HOUR((::i64)(time.m_i / integral)); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_HOUR operator *(const INTEGRAL_HOUR & time, INTEGRAL integral) { return INTEGRAL_HOUR((::i64)(time.m_i * integral)); }
//template < primitive_integral INTEGRAL >
//inline INTEGRAL_HOUR operator +(const INTEGRAL_HOUR & time, INTEGRAL integral) { return INTEGRAL_HOUR((::i64)(time.m_i + integral)); }
//template < primitive_integral INTEGRAL >
//inline INTEGRAL_HOUR operator -(const INTEGRAL_HOUR & time, INTEGRAL integral) { return INTEGRAL_HOUR((::i64)(time.m_i - integral)); }


//template < primitive_integral INTEGRAL >
//inline INTEGRAL_DAY operator %(const INTEGRAL_DAY & time, INTEGRAL integral) { return INTEGRAL_DAY(time.m_i % integral); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_DAY operator /(const INTEGRAL_DAY & time, INTEGRAL integral) { return INTEGRAL_DAY(time.m_i / integral); }
template < primitive_integral INTEGRAL >
inline INTEGRAL_DAY operator *(const INTEGRAL_DAY & time, INTEGRAL integral) { return INTEGRAL_DAY(time.m_i * integral); }
//template < primitive_integral INTEGRAL >
//inline INTEGRAL_DAY operator +(const INTEGRAL_DAY & time, INTEGRAL integral) { return INTEGRAL_DAY(time.m_i + integral); }
//template < primitive_integral INTEGRAL >
//inline INTEGRAL_DAY operator -(const INTEGRAL_DAY & time, INTEGRAL integral) { return INTEGRAL_DAY(time.m_i - integral); }


//template < primitive_floating FLOATING >
//inline INTEGRAL_NANOSECOND operator %(const INTEGRAL_NANOSECOND & time, FLOATING floating) { return INTEGRAL_NANOSECOND((::i64)(time.m_i % floating)); }
template < primitive_floating FLOATING >
inline INTEGRAL_NANOSECOND operator /(const INTEGRAL_NANOSECOND & time, FLOATING floating) { return INTEGRAL_NANOSECOND((::i64)(time.m_i / floating)); }
template < primitive_floating FLOATING >
inline INTEGRAL_NANOSECOND operator *(const INTEGRAL_NANOSECOND & time, FLOATING floating) { return INTEGRAL_NANOSECOND((::i64)(time.m_i * floating)); }
//template < primitive_floating FLOATING >
//inline INTEGRAL_NANOSECOND operator +(const INTEGRAL_NANOSECOND & time, FLOATING floating) { return INTEGRAL_NANOSECOND((::i64)(time.m_i + floating)); }
//template < primitive_floating FLOATING >
//inline INTEGRAL_NANOSECOND operator -(const INTEGRAL_NANOSECOND & time, FLOATING floating) { return INTEGRAL_NANOSECOND((::i64)(time.m_i - floating)); }


//template < primitive_floating FLOATING >
//inline INTEGRAL_MICROSECOND operator %(const INTEGRAL_MICROSECOND & time, FLOATING floating) { return INTEGRAL_MICROSECOND((::i64)(time.m_i % floating)); }
template < primitive_floating FLOATING >
inline INTEGRAL_MICROSECOND operator /(const INTEGRAL_MICROSECOND & time, FLOATING floating) { return INTEGRAL_MICROSECOND((::i64)(time.m_i / floating)); }
template < primitive_floating FLOATING >
inline INTEGRAL_MICROSECOND operator *(const INTEGRAL_MICROSECOND & time, FLOATING floating) { return INTEGRAL_MICROSECOND((::i64)(time.m_i * floating)); }
//template < primitive_floating FLOATING >
//inline INTEGRAL_MICROSECOND operator +(const INTEGRAL_MICROSECOND & time, FLOATING floating) { return INTEGRAL_MICROSECOND((::i64)(time.m_i + floating)); }
//template < primitive_floating FLOATING >
//inline INTEGRAL_MICROSECOND operator -(const INTEGRAL_MICROSECOND & time, FLOATING floating) { return INTEGRAL_MICROSECOND((::i64)(time.m_i - floating)); }


//template < primitive_floating FLOATING >
//inline INTEGRAL_MILLISECOND operator %(const INTEGRAL_MILLISECOND & time, FLOATING floating) { return INTEGRAL_MILLISECOND((::i64)(time.m_i % floating)); }
template < primitive_floating FLOATING >
inline INTEGRAL_MILLISECOND operator /(const INTEGRAL_MILLISECOND & time, FLOATING floating) { return INTEGRAL_MILLISECOND((::i64)(time.m_i / floating)); }
template < primitive_floating FLOATING >
inline INTEGRAL_MILLISECOND operator *(const INTEGRAL_MILLISECOND & time, FLOATING floating) { return INTEGRAL_MILLISECOND((::i64)(time.m_i * floating)); }
//template < primitive_floating FLOATING >
//inline INTEGRAL_MILLISECOND operator +(const INTEGRAL_MILLISECOND & time, FLOATING floating) { return INTEGRAL_MILLISECOND((::i64)(time.m_i + floating)); }
//template < primitive_floating FLOATING >
//inline INTEGRAL_MILLISECOND operator -(const INTEGRAL_MILLISECOND & time, FLOATING floating) { return INTEGRAL_MILLISECOND((::i64)(time.m_i - floating)); }


//template < primitive_floating FLOATING >
//inline INTEGRAL_SECOND operator %(const INTEGRAL_SECOND & time, FLOATING floating) { return INTEGRAL_SECOND((::i64)(time.m_i % floating)); }
template < primitive_floating FLOATING >
inline INTEGRAL_SECOND operator /(const INTEGRAL_SECOND & time, FLOATING floating) { return INTEGRAL_SECOND((::i64)(time.m_i / floating)); }
template < primitive_floating FLOATING >
inline INTEGRAL_SECOND operator *(const INTEGRAL_SECOND & time, FLOATING floating) { return INTEGRAL_SECOND((::i64)(time.m_i * floating)); }
//template < primitive_floating FLOATING >
//inline INTEGRAL_SECOND operator +(const INTEGRAL_SECOND & time, FLOATING floating) { return INTEGRAL_SECOND((::i64)(time.m_i + floating)); }
//template < primitive_floating FLOATING >
//inline INTEGRAL_SECOND operator -(const INTEGRAL_SECOND & time, FLOATING floating) { return INTEGRAL_SECOND((::i64)(time.m_i - floating)); }


//template < primitive_floating FLOATING >
//inline INTEGRAL_MINUTE operator %(const INTEGRAL_MINUTE & time, FLOATING floating) { return INTEGRAL_MINUTE((::i64)(time.m_i % floating)); }
template < primitive_floating FLOATING >
inline INTEGRAL_MINUTE operator /(const INTEGRAL_MINUTE & time, FLOATING floating) { return INTEGRAL_MINUTE((::i64)(time.m_i / floating)); }
template < primitive_floating FLOATING >
inline INTEGRAL_MINUTE operator *(const INTEGRAL_MINUTE & time, FLOATING floating) { return INTEGRAL_MINUTE((::i64)(time.m_i * floating)); }
//template < primitive_floating FLOATING >
//inline INTEGRAL_MINUTE operator +(const INTEGRAL_MINUTE & time, FLOATING floating) { return INTEGRAL_MINUTE((::i64)(time.m_i + floating)); }
//template < primitive_floating FLOATING >
//inline INTEGRAL_MINUTE operator -(const INTEGRAL_MINUTE & time, FLOATING floating) { return INTEGRAL_MINUTE((::i64)(time.m_i - floating)); }


//template < primitive_floating FLOATING >
//inline INTEGRAL_HOUR operator %(const INTEGRAL_HOUR & time, FLOATING floating) { return INTEGRAL_HOUR((::i64)(time.m_i % floating)); }
template < primitive_floating FLOATING >
inline INTEGRAL_HOUR operator /(const INTEGRAL_HOUR & time, FLOATING floating) { return INTEGRAL_HOUR((::i64)(time.m_i / floating)); }
template < primitive_floating FLOATING >
inline INTEGRAL_HOUR operator *(const INTEGRAL_HOUR & time, FLOATING floating) { return INTEGRAL_HOUR((::i64)(time.m_i * floating)); }
//template < primitive_floating FLOATING >
//inline INTEGRAL_HOUR operator +(const INTEGRAL_HOUR & time, FLOATING floating) { return INTEGRAL_HOUR((::i64)(time.m_i + floating)); }
//template < primitive_floating FLOATING >
//inline INTEGRAL_HOUR operator -(const INTEGRAL_HOUR & time, FLOATING floating) { return INTEGRAL_HOUR((::i64)(time.m_i - floating)); }


//template < primitive_floating FLOATING >
//inline INTEGRAL_DAY operator %(const INTEGRAL_DAY & time, FLOATING floating) { return INTEGRAL_DAY(time.m_i % floating); }
template < primitive_floating FLOATING >
inline INTEGRAL_DAY operator /(const INTEGRAL_DAY & time, FLOATING floating) { return INTEGRAL_DAY(time.m_i / floating); }
template < primitive_floating FLOATING >
inline INTEGRAL_DAY operator *(const INTEGRAL_DAY & time, FLOATING floating) { return INTEGRAL_DAY(time.m_i * floating); }
//template < primitive_floating FLOATING >
//inline INTEGRAL_DAY operator +(const INTEGRAL_DAY & time, FLOATING floating) { return INTEGRAL_DAY(time.m_i + floating); }
//template < primitive_floating FLOATING >
//inline INTEGRAL_DAY operator -(const INTEGRAL_DAY & time, FLOATING floating) { return INTEGRAL_DAY(time.m_i - floating); }


//template < primitive_integral INTEGRAL >
//inline FLOATING_NANOSECOND operator %(const FLOATING_NANOSECOND & time, INTEGRAL integral) { return FLOATING_NANOSECOND((::f64)(time.m_d % integral)); }
template < primitive_integral INTEGRAL >
inline FLOATING_NANOSECOND operator /(const FLOATING_NANOSECOND & time, INTEGRAL integral) { return FLOATING_NANOSECOND((::f64)(time.m_d / integral)); }
template < primitive_integral INTEGRAL >
inline FLOATING_NANOSECOND operator *(const FLOATING_NANOSECOND & time, INTEGRAL integral) { return FLOATING_NANOSECOND((::f64)(time.m_d * integral)); }
//template < primitive_integral INTEGRAL >
//inline FLOATING_NANOSECOND operator +(const FLOATING_NANOSECOND & time, INTEGRAL integral) { return FLOATING_NANOSECOND((::f64)(time.m_d + integral)); }
//template < primitive_integral INTEGRAL >
//inline FLOATING_NANOSECOND operator -(const FLOATING_NANOSECOND & time, INTEGRAL integral) { return FLOATING_NANOSECOND((::f64)(time.m_d - integral)); }


//template < primitive_integral INTEGRAL >
//inline FLOATING_MICROSECOND operator %(const FLOATING_MICROSECOND & time, INTEGRAL integral) { return FLOATING_MICROSECOND((::f64)(time.m_d % integral)); }
template < primitive_integral INTEGRAL >
inline FLOATING_MICROSECOND operator /(const FLOATING_MICROSECOND & time, INTEGRAL integral) { return FLOATING_MICROSECOND((::f64)(time.m_d / integral)); }
template < primitive_integral INTEGRAL >
inline FLOATING_MICROSECOND operator *(const FLOATING_MICROSECOND & time, INTEGRAL integral) { return FLOATING_MICROSECOND((::f64)(time.m_d * integral)); }
//template < primitive_integral INTEGRAL >
//inline FLOATING_MICROSECOND operator +(const FLOATING_MICROSECOND & time, INTEGRAL integral) { return FLOATING_MICROSECOND((::f64)(time.m_d + integral)); }
//template < primitive_integral INTEGRAL >
//inline FLOATING_MICROSECOND operator -(const FLOATING_MICROSECOND & time, INTEGRAL integral) { return FLOATING_MICROSECOND((::f64)(time.m_d - integral)); }


//template < primitive_integral INTEGRAL >
//inline FLOATING_MILLISECOND operator %(const FLOATING_MILLISECOND & time, INTEGRAL integral) { return FLOATING_MILLISECOND((::f64)(time.m_d % integral)); }
template < primitive_integral INTEGRAL >
inline FLOATING_MILLISECOND operator /(const FLOATING_MILLISECOND & time, INTEGRAL integral) { return FLOATING_MILLISECOND((::f64)(time.m_d / integral)); }
template < primitive_integral INTEGRAL >
inline FLOATING_MILLISECOND operator *(const FLOATING_MILLISECOND & time, INTEGRAL integral) { return FLOATING_MILLISECOND((::f64)(time.m_d * integral)); }
//template < primitive_integral INTEGRAL >
//inline FLOATING_MILLISECOND operator +(const FLOATING_MILLISECOND & time, INTEGRAL integral) { return FLOATING_MILLISECOND((::f64)(time.m_d + integral)); }
//template < primitive_integral INTEGRAL >
//inline FLOATING_MILLISECOND operator -(const FLOATING_MILLISECOND & time, INTEGRAL integral) { return FLOATING_MILLISECOND((::f64)(time.m_d - integral)); }


//template < primitive_integral INTEGRAL >
//inline FLOATING_SECOND operator %(const FLOATING_SECOND & time, INTEGRAL integral) { return FLOATING_SECOND((::f64)(time.m_d % integral)); }
template < primitive_integral INTEGRAL >
inline FLOATING_SECOND operator /(const FLOATING_SECOND & time, INTEGRAL integral) { return FLOATING_SECOND((::f64)(time.m_d / integral)); }
template < primitive_integral INTEGRAL >
inline FLOATING_SECOND operator *(const FLOATING_SECOND & time, INTEGRAL integral) { return FLOATING_SECOND((::f64)(time.m_d * integral)); }
//template < primitive_integral INTEGRAL >
//inline FLOATING_SECOND operator +(const FLOATING_SECOND & time, INTEGRAL integral) { return FLOATING_SECOND((::f64)(time.m_d + integral)); }
//template < primitive_integral INTEGRAL >
//inline FLOATING_SECOND operator -(const FLOATING_SECOND & time, INTEGRAL integral) { return FLOATING_SECOND((::f64)(time.m_d - integral)); }


//template < primitive_integral INTEGRAL >
//inline FLOATING_MINUTE operator %(const FLOATING_MINUTE & time, INTEGRAL integral) { return FLOATING_MINUTE((::f64)(time.m_d % integral)); }
template < primitive_integral INTEGRAL >
inline FLOATING_MINUTE operator /(const FLOATING_MINUTE & time, INTEGRAL integral) { return FLOATING_MINUTE((::f64)(time.m_d / integral)); }
template < primitive_integral INTEGRAL >
inline FLOATING_MINUTE operator *(const FLOATING_MINUTE & time, INTEGRAL integral) { return FLOATING_MINUTE((::f64)(time.m_d * integral)); }
//template < primitive_integral INTEGRAL >
//inline FLOATING_MINUTE operator +(const FLOATING_MINUTE & time, INTEGRAL integral) { return FLOATING_MINUTE((::f64)(time.m_d + integral)); }
//template < primitive_integral INTEGRAL >
//inline FLOATING_MINUTE operator -(const FLOATING_MINUTE & time, INTEGRAL integral) { return FLOATING_MINUTE((::f64)(time.m_d - integral)); }


//template < primitive_integral INTEGRAL >
//inline FLOATING_HOUR operator %(const FLOATING_HOUR & time, INTEGRAL integral) { return FLOATING_HOUR((::f64)(time.m_d % integral)); }
template < primitive_integral INTEGRAL >
inline FLOATING_HOUR operator /(const FLOATING_HOUR & time, INTEGRAL integral) { return FLOATING_HOUR((::f64)(time.m_d / integral)); }
template < primitive_integral INTEGRAL >
inline FLOATING_HOUR operator *(const FLOATING_HOUR & time, INTEGRAL integral) { return FLOATING_HOUR((::f64)(time.m_d * integral)); }
//template < primitive_integral INTEGRAL >
//inline FLOATING_HOUR operator +(const FLOATING_HOUR & time, INTEGRAL integral) { return FLOATING_HOUR((::f64)(time.m_d + integral)); }
//template < primitive_integral INTEGRAL >
//inline FLOATING_HOUR operator -(const FLOATING_HOUR & time, INTEGRAL integral) { return FLOATING_HOUR((::f64)(time.m_d - integral)); }


//template < primitive_integral INTEGRAL >
//inline FLOATING_DAY operator %(const FLOATING_DAY & time, INTEGRAL integral) { return FLOATING_DAY(time.m_d % integral); }
template < primitive_integral INTEGRAL >
inline FLOATING_DAY operator /(const FLOATING_DAY & time, INTEGRAL integral) { return FLOATING_DAY(time.m_d / integral); }
template < primitive_integral INTEGRAL >
inline FLOATING_DAY operator *(const FLOATING_DAY & time, INTEGRAL integral) { return FLOATING_DAY(time.m_d * integral); }
//template < primitive_integral INTEGRAL >
//inline FLOATING_DAY operator +(const FLOATING_DAY & time, INTEGRAL integral) { return FLOATING_DAY(time.m_d + integral); }
//template < primitive_integral INTEGRAL >
//inline FLOATING_DAY operator -(const FLOATING_DAY & time, INTEGRAL integral) { return FLOATING_DAY(time.m_d - integral); }


//template < primitive_floating FLOATING >
//inline FLOATING_NANOSECOND operator %(const FLOATING_NANOSECOND & time, FLOATING floating) { return FLOATING_NANOSECOND((::f64)(time.m_d % floating)); }
template < primitive_floating FLOATING >
inline FLOATING_NANOSECOND operator /(const FLOATING_NANOSECOND & time, FLOATING floating) { return FLOATING_NANOSECOND((::f64)(time.m_d / floating)); }
template < primitive_floating FLOATING >
inline FLOATING_NANOSECOND operator *(const FLOATING_NANOSECOND & time, FLOATING floating) { return FLOATING_NANOSECOND((::f64)(time.m_d * floating)); }
//template < primitive_floating FLOATING >
//inline FLOATING_NANOSECOND operator +(const FLOATING_NANOSECOND & time, FLOATING floating) { return FLOATING_NANOSECOND((::f64)(time.m_d + floating)); }
//template < primitive_floating FLOATING >
//inline FLOATING_NANOSECOND operator -(const FLOATING_NANOSECOND & time, FLOATING floating) { return FLOATING_NANOSECOND((::f64)(time.m_d - floating)); }


//template < primitive_floating FLOATING >
//inline FLOATING_MICROSECOND operator %(const FLOATING_MICROSECOND & time, FLOATING floating) { return FLOATING_MICROSECOND((::f64)(time.m_d % floating)); }
template < primitive_floating FLOATING >
inline FLOATING_MICROSECOND operator /(const FLOATING_MICROSECOND & time, FLOATING floating) { return FLOATING_MICROSECOND((::f64)(time.m_d / floating)); }
template < primitive_floating FLOATING >
inline FLOATING_MICROSECOND operator *(const FLOATING_MICROSECOND & time, FLOATING floating) { return FLOATING_MICROSECOND((::f64)(time.m_d * floating)); }
//template < primitive_floating FLOATING >
//inline FLOATING_MICROSECOND operator +(const FLOATING_MICROSECOND & time, FLOATING floating) { return FLOATING_MICROSECOND((::f64)(time.m_d + floating)); }
//template < primitive_floating FLOATING >
//inline FLOATING_MICROSECOND operator -(const FLOATING_MICROSECOND & time, FLOATING floating) { return FLOATING_MICROSECOND((::f64)(time.m_d - floating)); }


//template < primitive_floating FLOATING >
//inline FLOATING_MILLISECOND operator %(const FLOATING_MILLISECOND & time, FLOATING floating) { return FLOATING_MILLISECOND((::f64)(time.m_d % floating)); }
template < primitive_floating FLOATING >
inline FLOATING_MILLISECOND operator /(const FLOATING_MILLISECOND & time, FLOATING floating) { return FLOATING_MILLISECOND((::f64)(time.m_d / floating)); }
template < primitive_floating FLOATING >
inline FLOATING_MILLISECOND operator *(const FLOATING_MILLISECOND & time, FLOATING floating) { return FLOATING_MILLISECOND((::f64)(time.m_d * floating)); }
//template < primitive_floating FLOATING >
//inline FLOATING_MILLISECOND operator +(const FLOATING_MILLISECOND & time, FLOATING floating) { return FLOATING_MILLISECOND((::f64)(time.m_d + floating)); }
//template < primitive_floating FLOATING >
//inline FLOATING_MILLISECOND operator -(const FLOATING_MILLISECOND & time, FLOATING floating) { return FLOATING_MILLISECOND((::f64)(time.m_d - floating)); }


//template < primitive_floating FLOATING >
//inline FLOATING_SECOND operator %(const FLOATING_SECOND & time, FLOATING floating) { return FLOATING_SECOND((::f64)(time.m_d % floating)); }
template < primitive_floating FLOATING >
inline FLOATING_SECOND operator /(const FLOATING_SECOND & time, FLOATING floating) { return FLOATING_SECOND((::f64)(time.m_d / floating)); }
template < primitive_floating FLOATING >
inline FLOATING_SECOND operator *(const FLOATING_SECOND & time, FLOATING floating) { return FLOATING_SECOND((::f64)(time.m_d * floating)); }
//template < primitive_floating FLOATING >
//inline FLOATING_SECOND operator +(const FLOATING_SECOND & time, FLOATING floating) { return FLOATING_SECOND((::f64)(time.m_d + floating)); }
//template < primitive_floating FLOATING >
//inline FLOATING_SECOND operator -(const FLOATING_SECOND & time, FLOATING floating) { return FLOATING_SECOND((::f64)(time.m_d - floating)); }


//template < primitive_floating FLOATING >
//inline FLOATING_MINUTE operator %(const FLOATING_MINUTE & time, FLOATING floating) { return FLOATING_MINUTE((::f64)(time.m_d % floating)); }
template < primitive_floating FLOATING >
inline FLOATING_MINUTE operator /(const FLOATING_MINUTE & time, FLOATING floating) { return FLOATING_MINUTE((::f64)(time.m_d / floating)); }
template < primitive_floating FLOATING >
inline FLOATING_MINUTE operator *(const FLOATING_MINUTE & time, FLOATING floating) { return FLOATING_MINUTE((::f64)(time.m_d * floating)); }
//template < primitive_floating FLOATING >
//inline FLOATING_MINUTE operator +(const FLOATING_MINUTE & time, FLOATING floating) { return FLOATING_MINUTE((::f64)(time.m_d + floating)); }
//template < primitive_floating FLOATING >
//inline FLOATING_MINUTE operator -(const FLOATING_MINUTE & time, FLOATING floating) { return FLOATING_MINUTE((::f64)(time.m_d - floating)); }


//template < primitive_floating FLOATING >
//inline FLOATING_HOUR operator %(const FLOATING_HOUR & time, FLOATING floating) { return FLOATING_HOUR((::f64)(time.m_d % floating)); }
template < primitive_floating FLOATING >
inline FLOATING_HOUR operator /(const FLOATING_HOUR & time, FLOATING floating) { return FLOATING_HOUR((::f64)(time.m_d / floating)); }
template < primitive_floating FLOATING >
inline FLOATING_HOUR operator *(const FLOATING_HOUR & time, FLOATING floating) { return FLOATING_HOUR((::f64)(time.m_d * floating)); }
//template < primitive_floating FLOATING >
//inline FLOATING_HOUR operator +(const FLOATING_HOUR & time, FLOATING floating) { return FLOATING_HOUR((::f64)(time.m_d + floating)); }
//template < primitive_floating FLOATING >
//inline FLOATING_HOUR operator -(const FLOATING_HOUR & time, FLOATING floating) { return FLOATING_HOUR((::f64)(time.m_d - floating)); }


//template < primitive_floating FLOATING >
//inline FLOATING_DAY operator %(const FLOATING_DAY & time, FLOATING floating) { return FLOATING_DAY(time.m_d % floating); }
template < primitive_floating FLOATING >
inline FLOATING_DAY operator /(const FLOATING_DAY & time, FLOATING floating) { return FLOATING_DAY(time.m_d / floating); }
template < primitive_floating FLOATING >
inline FLOATING_DAY operator *(const FLOATING_DAY & time, FLOATING floating) { return FLOATING_DAY(time.m_d * floating); }
//template < primitive_floating FLOATING >
//inline FLOATING_DAY operator +(const FLOATING_DAY & time, FLOATING floating) { return FLOATING_DAY(time.m_d + floating); }
//template < primitive_floating FLOATING >
//inline FLOATING_DAY operator -(const FLOATING_DAY & time, FLOATING floating) { return FLOATING_DAY(time.m_d - floating); }

