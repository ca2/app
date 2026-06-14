//
//  ini.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 04/04/26.
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//
#include "framework.h"
#include "ini.h"
//#include "winprofile_compat_v2.h"

//#ifndef _WIN32

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#ifndef FALSE
#define FALSE 0

#endif


#ifndef TRUE
#define TRUE 1

#endif

/* ============================================================
   Config
   ============================================================ */

#define WP_MAX_LINE     8192
#define WP_MAX_NAME     1024
#define WP_MAX_VALUE    4096

/* ============================================================
   Helpers
   ============================================================ */

namespace acme
{

static char_pointer wp_strdup(const_char_pointer s) {
    size_t n;
    char_pointer p;
    if (!s) return NULL;
    n = strlen(s);
    p = (char_pointer )::malloc(n + 1);
    if (!p) return NULL;
    memcpy(p, s, n + 1);
    return p;
}

static ::i32 wp_stricmp(const_char_pointer a, const_char_pointer b) {
    ::u8 ca, cb;
    while (*a && *b) {
        ca = (::u8)tolower((::u8)*a);
        cb = (::u8)tolower((::u8)*b);
        if (ca != cb) return (::i32)ca - (::i32)cb;
        ++a;
        ++b;
    }
    ca = (::u8)tolower((::u8)*a);
    cb = (::u8)tolower((::u8)*b);
    return (::i32)ca - (::i32)cb;
}

static char_pointer wp_ltrim(char_pointer s) {
    while (*s && isspace((::u8)*s)) ++s;
    return s;
}

static void wp_rtrim_inplace(char_pointer s) {
    size_t len = strlen(s);
    while (len > 0 && isspace((::u8)s[len - 1])) {
        s[len - 1] = '\0';
        --len;
    }
}

static char_pointer wp_trim(char_pointer s) {
    s = wp_ltrim(s);
    wp_rtrim_inplace(s);
    return s;
}

static ::i32 wp_is_blank(const_char_pointer s) {
    while (*s) {
        if (!isspace((::u8)*s)) return 0;
        ++s;
    }
    return 1;
}

static ::i32 wp_is_comment_line(const_char_pointer s) {
    ::i8 buf[WP_MAX_LINE];
    char_pointer t;
    strncpy(buf, s ? s : "", sizeof(buf) - 1);
    buf[sizeof(buf) - 1] = '\0';
    t = wp_trim(buf);
    return (*t == ';' || *t == '#');
}

static ::i32 wp_starts_with_space(const_char_pointer s) {
    return s && *s && isspace((::u8)*s);
}

static ::i32 wp_build_assignment_line(
    char_pointer dst,
    size_t dstsz,
    const_char_pointer key,
    const_char_pointer value,
    const_char_pointer comment
) {
    size_t keylen = strlen(key);
    size_t valuelen = strlen(value);
    size_t commentlen = comment ? strlen(comment) : 0;
    char_pointer p;

    if (keylen >= dstsz || valuelen >= dstsz - keylen - 1) return 0;
    if (commentlen && commentlen >= dstsz - keylen - 1 - valuelen - 1) return 0;

    p = dst;
    memcpy(p, key, keylen);
    p += keylen;
    *p++ = '=';
    memcpy(p, value, valuelen);
    p += valuelen;
    if (commentlen) {
        *p++ = ' ';
        memcpy(p, comment, commentlen);
        p += commentlen;
    }
    *p = '\0';
    return 1;
}

static ::i32 wp_build_section_line(char_pointer dst, size_t dstsz, const_char_pointer section) {
    size_t sectionlen = strlen(section);

    if (dstsz < 3 || sectionlen >= dstsz - 2) return 0;

    dst[0] = '[';
    memcpy(dst + 1, section, sectionlen);
    dst[sectionlen + 1] = ']';
    dst[sectionlen + 2] = '\0';
    return 1;
}

/* ============================================================
   Dynamic line array
   ============================================================ */

typedef struct {
    char_pointer *items;
    size_t count;
    size_t cap;
} WpLines;

static void wp_lines_free(WpLines *a) {
    size_t i;
    if (!a) return;
    for (i = 0; i < a->count; ++i) free(a->items[i]);
    free(a->items);
    a->items = NULL;
    a->count = 0;
    a->cap = 0;
}

static ::i32 wp_lines_reserve(WpLines *a, size_t need) {
    char_pointer *p;
    size_t newcap;
    if (need <= a->cap) return 1;
    newcap = (a->cap == 0) ? 16 : a->cap;
    while (newcap < need) newcap *= 2;
    p = (char_pointer *)realloc(a->items, newcap * sizeof(char_pointer ));
    if (!p) return 0;
    a->items = p;
    a->cap = newcap;
    return 1;
}

static ::i32 wp_lines_push(WpLines *a, const_char_pointer line) {
    if (!wp_lines_reserve(a, a->count + 1)) return 0;
    a->items[a->count] = wp_strdup(line ? line : "");
    if (!a->items[a->count]) return 0;
    ++a->count;
    return 1;
}

static ::i32 wp_lines_insert(WpLines *a, size_t pos, const_char_pointer line) {
    size_t i;
    if (pos > a->count) pos = a->count;
    if (!wp_lines_reserve(a, a->count + 1)) return 0;
    for (i = a->count; i > pos; --i) {
        a->items[i] = a->items[i - 1];
    }
    a->items[pos] = wp_strdup(line ? line : "");
    if (!a->items[pos]) return 0;
    ++a->count;
    return 1;
}

static void wp_lines_remove_range(WpLines *a, size_t start, size_t end) {
    size_t i, n;
    if (start >= end || start >= a->count) return;
    if (end > a->count) end = a->count;
    for (i = start; i < end; ++i) free(a->items[i]);
    n = end - start;
    for (i = end; i < a->count; ++i) a->items[i - n] = a->items[i];
    a->count -= n;
}

static ::i32 wp_read_all_lines(const_char_pointer pszFilename, WpLines *out) {
    FILE *fp;
    ::i8 buf[WP_MAX_LINE];
    memset(out, 0, sizeof(*out));

    fp = fopen(pszFilename, "rb");
    if (!fp) return 1; /* treat missing file as empty */

    while (fgets(buf, sizeof(buf), fp)) {
        size_t len = strlen(buf);
        while (len > 0 && (buf[len - 1] == '\n' || buf[len - 1] == '\r')) {
            buf[len - 1] = '\0';
            --len;
        }
        if (!wp_lines_push(out, buf)) {
            fclose(fp);
            wp_lines_free(out);
            return 0;
        }
    }

    fclose(fp);
    return 1;
}

static ::i32 wp_write_all_lines(const_char_pointer pszFilename, const WpLines *a) {
    FILE *fp;
    size_t i;
    fp = fopen(pszFilename, "wb");
    if (!fp) return 0;
    for (i = 0; i < a->count; ++i) {
        if (fputs(a->items[i], fp) == EOF || fputc('\n', fp) == EOF) {
            fclose(fp);
            return 0;
        }
    }
    if (fclose(fp) != 0) return 0;
    return 1;
}

/* ============================================================
   Parsing: sections
   ============================================================ */

static ::i32 wp_parse_section_name(const_char_pointer line, char_pointer out, size_t outsz) {
    ::i8 buf[WP_MAX_LINE];
    char_pointer t, start, end;
    size_t len;

    if (!line) return 0;

    strncpy(buf, line, sizeof(buf) - 1);
    buf[sizeof(buf) - 1] = '\0';
    t = wp_trim(buf);

    if (*t != '[') return 0;
    start = t + 1;
    end = strchr(start, ']');
    if (!end) return 0;

    len = (size_t)(end - start);
    if (len >= outsz) len = outsz - 1;
    memcpy(out, start, len);
    out[len] = '\0';
    wp_trim(out);
    return 1;
}

/* ============================================================
   Parsing: escaped / quoted values
   ============================================================ */

static void wp_append_char(char_pointer dst, size_t dstsz, size_t *di, ::i8 c) {
    if (*di + 1 < dstsz) {
        dst[*di] = c;
        ++(*di);
        dst[*di] = '\0';
    }
}

static void wp_unescape_string(const_char_pointer src, char_pointer dst, size_t dstsz) {
    size_t i = 0;
    size_t di = 0;
    dst[0] = '\0';

    while (src[i]) {
        if (src[i] == '\\') {
            ++i;
            switch (src[i]) {
                case 'n':  wp_append_char(dst, dstsz, &di, '\n'); break;
                case 'r':  wp_append_char(dst, dstsz, &di, '\r'); break;
                case 't':  wp_append_char(dst, dstsz, &di, '\t'); break;
                case '\\': wp_append_char(dst, dstsz, &di, '\\'); break;
                case '"':  wp_append_char(dst, dstsz, &di, '"'); break;
                case ';':  wp_append_char(dst, dstsz, &di, ';'); break;
                case '#':  wp_append_char(dst, dstsz, &di, '#'); break;
                case '=':  wp_append_char(dst, dstsz, &di, '='); break;
                case '\0':
                    return;
                default:
                    wp_append_char(dst, dstsz, &di, src[i]);
                    break;
            }
            if (src[i]) ++i;
        } else {
            wp_append_char(dst, dstsz, &di, src[i]);
            ++i;
        }
    }
}

static void wp_escape_string(const_char_pointer src, char_pointer dst, size_t dstsz) {
    size_t i = 0, di = 0;
    dst[0] = '\0';

    while (src[i]) {
        ::i8 c = src[i++];
        switch (c) {
            case '\n':
                if (di + 2 < dstsz) { dst[di++]='\\'; dst[di++]='n'; }
                break;
            case '\r':
                if (di + 2 < dstsz) { dst[di++]='\\'; dst[di++]='r'; }
                break;
            case '\t':
                if (di + 2 < dstsz) { dst[di++]='\\'; dst[di++]='t'; }
                break;
            case '\\':
                if (di + 2 < dstsz) { dst[di++]='\\'; dst[di++]='\\'; }
                break;
            case '"':
                if (di + 2 < dstsz) { dst[di++]='\\'; dst[di++]='"'; }
                break;
            default:
                if (di + 1 < dstsz) dst[di++] = c;
                break;
        }
    }
    dst[di] = '\0';
}

static ::i32 wp_needs_quotes(const_char_pointer s) {
    if (!s || !*s) return 1;
    if (isspace((::u8)s[0])) return 1;
    while (*s) {
        if (*s == ';' || *s == '#' || *s == '=' || *s == '"')
            return 1;
        ++s;
    }
    return 0;
}

static void wp_encode_value(const_char_pointer value, char_pointer dst, size_t dstsz) {
    ::i8 esc[WP_MAX_VALUE * 2];
    wp_escape_string(value ? value : "", esc, sizeof(esc));

    if (wp_needs_quotes(value ? value : "")) {
        snprintf(dst, dstsz, "\"%s\"", esc);
    } else {
        snprintf(dst, dstsz, "%s", esc);
    }
}

/*
Parses:
  key = value ; comment
  key="hello\nworld" # comment
Preserves:
  prefix spacing around key and '='
  inline comment suffix (returned separately)

Returns 1 if line is key/value.
*/
static ::i32 wp_parse_key_value_line_ex(
    const_char_pointer line,
    char_pointer out_key, size_t keysz,
    char_pointer out_value, size_t valsz,
    char_pointer out_inline_comment, size_t commentsz
) {
    const_char_pointer p;
    const_char_pointer eq;
    ::i8 keybuf[WP_MAX_NAME];
    ::i8 valbuf[WP_MAX_VALUE];
    size_t klen = 0, vlen = 0;
    ::i32 in_quotes = 0;
    ::i32 escaped = 0;
    const_char_pointer comment_start = NULL;

    out_key[0] = '\0';
    out_value[0] = '\0';
    if (out_inline_comment && commentsz > 0) out_inline_comment[0] = '\0';

    if (!line) return 0;

    p = line;
    while (*p && isspace((::u8)*p)) ++p;
    if (*p == '\0' || *p == ';' || *p == '#') return 0;

    eq = strchr(p, '=');
    if (!eq) return 0;

    /* key */
    while (p < eq && klen + 1 < sizeof(keybuf)) {
        keybuf[klen++] = *p++;
    }
    keybuf[klen] = '\0';
    {
        char_pointer tk = wp_trim(keybuf);
        memmove(keybuf, tk, strlen(tk) + 1);
    }

    /* value */
    p = eq + 1;
    while (*p && isspace((::u8)*p)) ++p;

    if (*p == '"') {
        in_quotes = 1;
        ++p;
    }

    while (*p) {
        if (escaped) {
            if (vlen + 2 < sizeof(valbuf)) {
                valbuf[vlen++] = '\\';
                valbuf[vlen++] = *p;
            }
            escaped = 0;
            ++p;
            continue;
        }

        if (*p == '\\') {
            escaped = 1;
            ++p;
            continue;
        }

        if (in_quotes) {
            if (*p == '"') {
                ++p;
                break;
            }
            if (vlen + 1 < sizeof(valbuf)) valbuf[vlen++] = *p;
            ++p;
        } else {
            if (*p == ';' || *p == '#') {
                comment_start = p;
                break;
            }
            if (vlen + 1 < sizeof(valbuf)) valbuf[vlen++] = *p;
            ++p;
        }
    }

    valbuf[vlen] = '\0';
    wp_rtrim_inplace(valbuf);

    /* after quoted value, allow spaces then inline comment */
    if (!comment_start) {
        while (*p && isspace((::u8)*p)) ++p;
        if (*p == ';' || *p == '#') comment_start = p;
    }

    if (comment_start && out_inline_comment && commentsz > 0) {
        strncpy(out_inline_comment, comment_start, commentsz - 1);
        out_inline_comment[commentsz - 1] = '\0';
    }

    wp_unescape_string(valbuf, out_value, valsz);

    strncpy(out_key, keybuf, keysz - 1);
    out_key[keysz - 1] = '\0';

    return 1;
}

/* ============================================================
   Section/key location
   ============================================================ */

typedef struct {
    ::i32 found_section;
    size_t section_start;
    size_t section_end;      /* one past last line in section */

    ::i32 found_key;
    size_t key_line;

    size_t key_block_start;  /* includes immediately preceding comments */
} WpLocation;

static WpLocation wp_find_section_and_key(
    const WpLines *lines,
    const_char_pointer section,
    const_char_pointer key
) {
    WpLocation loc;
    size_t i;
    ::i32 in_target = 0;
    ::i8 sec[WP_MAX_NAME];
    ::i8 k[WP_MAX_NAME], v[WP_MAX_VALUE], c[WP_MAX_VALUE];

    memset(&loc, 0, sizeof(loc));
    loc.section_start = (size_t)-1;
    loc.section_end   = lines->count;
    loc.key_line      = (size_t)-1;
    loc.key_block_start = (size_t)-1;

    for (i = 0; i < lines->count; ++i) {
        if (wp_parse_section_name(lines->items[i], sec, sizeof(sec))) {
            if (in_target) {
                loc.section_end = i;
                break;
            }
            if (wp_stricmp(sec, section) == 0) {
                loc.found_section = 1;
                loc.section_start = i;
                in_target = 1;
            }
            continue;
        }

        if (in_target && key) {
            if (wp_parse_key_value_line_ex(lines->items[i], k, sizeof(k), v, sizeof(v), c, sizeof(c))) {
                if (wp_stricmp(k, key) == 0) {
                    size_t start = i;
                    while (start > loc.section_start + 1) {
                        const_char_pointer prev = lines->items[start - 1];
                        if (wp_is_comment_line(prev) || wp_is_blank(prev)) {
                            --start;
                        } else {
                            break;
                        }
                    }
                    loc.found_key = 1;
                    loc.key_line = i;
                    loc.key_block_start = start;
                }
            }
        }
    }

    if (in_target && loc.section_end == lines->count) {
        loc.section_end = lines->count;
    }

    return loc;
}

/* ============================================================
   Win32-style multi-string helpers
   ============================================================ */

static ::u32 wp_copy_cstr(char_pointer dst, ::u32 nSize, const_char_pointer src) {
    size_t len;
    if (!dst || nSize == 0) return 0;
    if (!src) src = "";
    strncpy(dst, src, nSize - 1);
    dst[nSize - 1] = '\0';
    len = strlen(dst);
    return (::u32)len;
}

static ::u32 wp_multisz_append(char_pointer dst, ::u32 nSize, ::u32 used, const_char_pointer s) {
    size_t len;
    if (!dst || nSize == 0) return 0;
    if (!s) s = "";
    len = strlen(s);

    if (used >= nSize) return nSize;

    while (*s && used + 1 < nSize) {
        dst[used++] = *s++;
    }

    if (used < nSize) dst[used++] = '\0';
    if (used < nSize) dst[used] = '\0';
    else dst[nSize - 1] = '\0';

    return used;
}

/* ============================================================
   Public API
   ============================================================ */

::i32 WritePrivateProfileString(
    const_char_pointer lpAppName,
    const_char_pointer lpKeyName,
    const_char_pointer lpString,
    const_char_pointer lpFileName
) {
    WpLines lines;
    WpLocation loc;
    ::i8 newline[WP_MAX_LINE];
    ::i8 encoded[WP_MAX_VALUE * 2];
    ::i8 k[WP_MAX_NAME], v[WP_MAX_VALUE], comment[WP_MAX_VALUE];

    if (!lpAppName || !lpFileName) return FALSE;

    if (!wp_read_all_lines(lpFileName, &lines)) return FALSE;

    loc = wp_find_section_and_key(&lines, lpAppName, lpKeyName);

    /* delete section */
    if (lpKeyName == NULL) {
        if (loc.found_section) {
            wp_lines_remove_range(&lines, loc.section_start, loc.section_end);
            if (loc.section_start < lines.count && wp_is_blank(lines.items[loc.section_start])) {
                wp_lines_remove_range(&lines, loc.section_start, loc.section_start + 1);
            }
        }
        if (!wp_write_all_lines(lpFileName, &lines)) {
            wp_lines_free(&lines);
            return FALSE;
        }
        wp_lines_free(&lines);
        return TRUE;
    }

    /* delete key */
    if (lpString == NULL) {
        if (loc.found_key) {
            /* delete only the actual key line, preserve surrounding comments */
            wp_lines_remove_range(&lines, loc.key_line, loc.key_line + 1);
        }
        if (!wp_write_all_lines(lpFileName, &lines)) {
            wp_lines_free(&lines);
            return FALSE;
        }
        wp_lines_free(&lines);
        return TRUE;
    }

    wp_encode_value(lpString, encoded, sizeof(encoded));

    /* replace existing key, preserving inline comment */
    if (loc.found_key) {
        comment[0] = '\0';
        if (wp_parse_key_value_line_ex(lines.items[loc.key_line], k, sizeof(k), v, sizeof(v), comment, sizeof(comment))) {
            if (!wp_build_assignment_line(newline, sizeof(newline), lpKeyName, encoded, comment)) {
                wp_lines_free(&lines);
                return FALSE;
            }
        } else {
            if (!wp_build_assignment_line(newline, sizeof(newline), lpKeyName, encoded, NULL)) {
                wp_lines_free(&lines);
                return FALSE;
            }
        }

        free(lines.items[loc.key_line]);
        lines.items[loc.key_line] = wp_strdup(newline);
        if (!lines.items[loc.key_line]) {
            wp_lines_free(&lines);
            return FALSE;
        }
    }
    /* append key to existing section */
    else if (loc.found_section) {
        if (!wp_build_assignment_line(newline, sizeof(newline), lpKeyName, encoded, NULL)) {
            wp_lines_free(&lines);
            return FALSE;
        }
        if (!wp_lines_insert(&lines, loc.section_end, newline)) {
            wp_lines_free(&lines);
            return FALSE;
        }
    }
    /* create section + key */
    else {
        if (lines.count > 0 && !wp_is_blank(lines.items[lines.count - 1])) {
            if (!wp_lines_push(&lines, "")) {
                wp_lines_free(&lines);
                return FALSE;
            }
        }

        if (!wp_build_section_line(newline, sizeof(newline), lpAppName)) {
            wp_lines_free(&lines);
            return FALSE;
        }
        if (!wp_lines_push(&lines, newline)) {
            wp_lines_free(&lines);
            return FALSE;
        }

        if (!wp_build_assignment_line(newline, sizeof(newline), lpKeyName, encoded, NULL)) {
            wp_lines_free(&lines);
            return FALSE;
        }
        if (!wp_lines_push(&lines, newline)) {
            wp_lines_free(&lines);
            return FALSE;
        }
    }

    if (!wp_write_all_lines(lpFileName, &lines)) {
        wp_lines_free(&lines);
        return FALSE;
    }

    wp_lines_free(&lines);
    return TRUE;
}

::u32 GetPrivateProfileString(
    const_char_pointer lpAppName,
    const_char_pointer lpKeyName,
    const_char_pointer lpDefault,
    char_pointer lpReturnedString,
    ::u32 nSize,
    const_char_pointer lpFileName
) {
    WpLines lines;
    size_t i;
    ::i32 in_target = 0;
    ::i8 sec[WP_MAX_NAME];
    ::i8 key[WP_MAX_NAME], val[WP_MAX_VALUE], comment[WP_MAX_VALUE];
    ::u32 used = 0;

    if (!lpReturnedString || nSize == 0) return 0;
    lpReturnedString[0] = '\0';

    if (!lpFileName) {
        return wp_copy_cstr(lpReturnedString, nSize, lpDefault ? lpDefault : "");
    }

    if (!wp_read_all_lines(lpFileName, &lines)) {
        return wp_copy_cstr(lpReturnedString, nSize, lpDefault ? lpDefault : "");
    }

    /* Win32-ish enumeration: app==NULL -> section names */
    if (lpAppName == NULL && lpKeyName == NULL) {
        for (i = 0; i < lines.count; ++i) {
            if (wp_parse_section_name(lines.items[i], sec, sizeof(sec))) {
                used = wp_multisz_append(lpReturnedString, nSize, used, sec);
                if (used >= nSize) break;
            }
        }
        if (used == 0 && nSize >= 2) {
            lpReturnedString[0] = '\0';
            lpReturnedString[1] = '\0';
            used = 1;
        } else if (used < nSize) {
            lpReturnedString[used] = '\0';
        } else {
            lpReturnedString[nSize - 1] = '\0';
        }
        wp_lines_free(&lines);
        return used ? (used - 1) : 0;
    }

    /* Win32-ish enumeration: key==NULL -> keys in section */
    if (lpAppName != NULL && lpKeyName == NULL) {
        for (i = 0; i < lines.count; ++i) {
            if (wp_parse_section_name(lines.items[i], sec, sizeof(sec))) {
                in_target = (wp_stricmp(sec, lpAppName) == 0);
                continue;
            }

            if (!in_target) continue;

            if (wp_parse_key_value_line_ex(lines.items[i], key, sizeof(key), val, sizeof(val), comment, sizeof(comment))) {
                used = wp_multisz_append(lpReturnedString, nSize, used, key);
                if (used >= nSize) break;
            }
        }

        if (used == 0 && nSize >= 2) {
            lpReturnedString[0] = '\0';
            lpReturnedString[1] = '\0';
            used = 1;
        } else if (used < nSize) {
            lpReturnedString[used] = '\0';
        } else {
            lpReturnedString[nSize - 1] = '\0';
        }

        wp_lines_free(&lines);
        return used ? (used - 1) : 0;
    }

    /* normal key lookup */
    if (!lpAppName || !lpKeyName) {
        wp_lines_free(&lines);
        return wp_copy_cstr(lpReturnedString, nSize, lpDefault ? lpDefault : "");
    }

    for (i = 0; i < lines.count; ++i) {
        if (wp_parse_section_name(lines.items[i], sec, sizeof(sec))) {
            in_target = (wp_stricmp(sec, lpAppName) == 0);
            continue;
        }

        if (!in_target) continue;

        if (wp_parse_key_value_line_ex(lines.items[i], key, sizeof(key), val, sizeof(val), comment, sizeof(comment))) {
            if (wp_stricmp(key, lpKeyName) == 0) {
                wp_lines_free(&lines);
                return wp_copy_cstr(lpReturnedString, nSize, val);
            }
        }
    }

    wp_lines_free(&lines);
    return wp_copy_cstr(lpReturnedString, nSize, lpDefault ? lpDefault : "");
}

::u32 GetPrivateProfileInt(
    const_char_pointer lpAppName,
    const_char_pointer lpKeyName,
    ::i32 nDefault,
    const_char_pointer lpFileName
) {
    ::i8 buf[64];
    char_pointer endptr;
    long v;

    GetPrivateProfileString(lpAppName, lpKeyName, "", buf, (::u32)sizeof(buf), lpFileName);
    if (buf[0] == '\0') return (::u32)nDefault;

    v = strtol(buf, &endptr, 0);
    if (endptr == buf) return (::u32)nDefault;
    return (::u32)v;
}

::u32 GetPrivateProfileSection(
    const_char_pointer lpAppName,
    char_pointer lpReturnedString,
    ::u32 nSize,
    const_char_pointer lpFileName
) {
    WpLines lines;
    size_t i;
    ::i32 in_target = 0;
    ::i8 sec[WP_MAX_NAME];
    ::i8 key[WP_MAX_NAME], val[WP_MAX_VALUE], comment[WP_MAX_VALUE];
    ::i8 kv[WP_MAX_LINE];
    ::u32 used = 0;

    if (!lpReturnedString || nSize == 0) return 0;
    lpReturnedString[0] = '\0';

    if (!lpAppName || !lpFileName) {
        if (nSize >= 2) {
            lpReturnedString[0] = '\0';
            lpReturnedString[1] = '\0';
        }
        return 0;
    }

    if (!wp_read_all_lines(lpFileName, &lines)) {
        if (nSize >= 2) {
            lpReturnedString[0] = '\0';
            lpReturnedString[1] = '\0';
        }
        return 0;
    }

    for (i = 0; i < lines.count; ++i) {
        if (wp_parse_section_name(lines.items[i], sec, sizeof(sec))) {
            if (in_target) break;
            in_target = (wp_stricmp(sec, lpAppName) == 0);
            continue;
        }

        if (!in_target) continue;

        if (wp_parse_key_value_line_ex(lines.items[i], key, sizeof(key), val, sizeof(val), comment, sizeof(comment))) {
            snprintf(kv, sizeof(kv), "%s=%s", key, val);
            used = wp_multisz_append(lpReturnedString, nSize, used, kv);
            if (used >= nSize) break;
        }
    }

    if (used == 0 && nSize >= 2) {
        lpReturnedString[0] = '\0';
        lpReturnedString[1] = '\0';
        used = 1;
    } else if (used < nSize) {
        lpReturnedString[used] = '\0';
    } else {
        lpReturnedString[nSize - 1] = '\0';
    }

    wp_lines_free(&lines);
    return used ? (used - 1) : 0;
}

::u32 GetPrivateProfileSectionNames(
    char_pointer lpszReturnBuffer,
    ::u32 nSize,
    const_char_pointer lpFileName
) {
    return GetPrivateProfileString(NULL, NULL, "", lpszReturnBuffer, nSize, lpFileName);
}



} // namespace acme
//#endif /* !_WIN32 */
