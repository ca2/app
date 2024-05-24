//
// Created by camilo on 2024-05-22 03:04 <3ThomaasBorregaardSorensen!!
//
// From acme by camilo on 2024-05-22 11:16 <3ThomasBorregaardSorensen!!
// From string by camilo on 2024-05-22 23:18 <3ThomasBorregaardSorensen!!
#pragma once


class string_pointer
{
public:
    char* m_psz;


    string_pointer();
    string_pointer(const char* psz);


    strsize size() const;
    constexpr bool is_empty() const { return ::is_null(m_psz) || *m_psz == '\0'; }
    constexpr bool has_char() const { return !is_empty(); }

    bool case_insensitive_equals(const string_pointer& strpointer) const;
    ::std::strong_ordering case_insensitive_order(const string_pointer& strpointer) const;

    ::std::strong_ordering case_insensitive_order(const string_pointer& strpointer, strsize start,
                                                  strsize count = -1) const;

    string_pointer find_character(char ch, strsize start = 0) const;

    string_pointer skip_any_not_in(const string_pointer& strpointer) const;
    string_pointer find_any_in(const string_pointer& strpointer) const;
    const char* c_str() const { return m_psz; }

    bool is_null() const { return ::is_null(m_psz); }


    char operator [](strsize i) const { return m_psz[i]; }

    constexpr explicit operator bool() const { return this->has_char(); }


    operator const char*() const { return m_psz; }

    void find_replace_character(char chSource, char chTarget);

    string_pointer find(const string_pointer& strpointer) const;
    bool contains(const string_pointer& strpointer) const;

    string_pointer case_insensitive_find(const string_pointer& strpointer) const;
    bool case_insensitive_contains(const string_pointer& strpointer) const;
};
