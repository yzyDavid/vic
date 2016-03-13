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
        "_Noreturn", "_Static_assert", "_Thread_local"
};
