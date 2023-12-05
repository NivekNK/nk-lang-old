#include "nkpch.h"

#include "parser/lexer.h"

int main(void) {
    nk::str source = "test: f32 = 0.2;\n";
    nk::Lexer lexer{source};
    lexer.pretty_print();

    return 0;
}
