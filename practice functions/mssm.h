#ifndef MSSM_H
#define MSSM_H

#include <iostream>

#include "utility/array.h"
#include "utility/rand.h"
#include "fmt/core.h"
#include <fmt/format.h>
#include <fmt/color.h>

template <typename T>
struct fmt::formatter<Array<T>>: formatter<T> {
    template <typename FormatContext>
    auto format(Array<T> c, FormatContext& ctx) const {
        auto out = ctx.out();
        auto format_element = [&](const T& value) {
            ctx.advance_to(out);
            out = formatter<T>::format(value, ctx);
        };
        out = format_to(out, "{{");
        for (int i = 0; i < c.size(); i++) {
            if (i > 0) {
                out = format_to(out, ", ");
            }
            format_element(c[i]);
        }
        return format_to(out, "}}");
    }
};

using namespace std;
using namespace fmt;

#endif // MSSM_H
