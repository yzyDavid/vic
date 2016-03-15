//
// Created by yzy on 3/13/16.
//

#include "highlight.h"

char *c_highlight_list[] = {
        "char", "short", "int", "unsigned",
        "long", "float", "double", "struct",
        "union", "void", "enum", "signed",
        "const", "volatile", "typedef", "auto",
        "register", "static", "extern", "break",
        "case", "continue", "default", "do",
        "else", "for", "goto", "if",
        "return", "switch", "while", "sizeof",

        "_Bool", "_Complex", "_Imaginary", "inline", "restrict",

        "_Alignas", "_Alignof", "_Atomic", "_Generic",
        "_Noreturn", "_Static_assert", "_Thread_local",

        ""
};

char *cplusplus_highlight_list[] = {
        "char", "short", "int", "unsigned",
        "long", "float", "double", "struct",
        "union", "void", "enum", "signed",
        "const", "volatile", "typedef", "auto",
        "register", "static", "extern", "break",
        "case", "continue", "default", "do",
        "else", "for", "goto", "if",
        "return", "switch", "while", "sizeof",

        "asm", "inline", "typeid", "bool",
        "dynamic_cast", "typename", "mutable",
        "catch","explicit","namespace","static_cast",
        "using","export","new","virtual",
        "class","operator","private","false",
        "template","const_cast","protected","this",
        "wchar_t","public","throw","friend",
        "true","delete","reinterpret_cast","try",

        "alignas","alignof","char16_t","char32_t",
        "constexpr","decltype","noexcept","nullptr",
        "static_assert","thread_local",

        ""
};

char word_char_list[]="qwertyuiopasdfghjklzxcvbnm_QWERTYUIOPASDFGHJKLZXCVBNM";

