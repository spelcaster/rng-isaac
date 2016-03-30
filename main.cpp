#include "isaac.hpp"

#include <iostream>
#include <iomanip>
#include <cstring>

void run_isaac_test (rand_ctx ctx);

int main() {
    ub4 i;

    rand_ctx ctx;

    ctx.rand_a = ctx.rand_b = ctx.rand_c = (ub4) 0;

    for (i = 0; i < RANDSIZ; ++i) {
        ctx.rand_rsl[i] = (ub4) 0;
    }

    run_isaac_test(ctx);

    return 0;
}

void run_isaac_test (rand_ctx ctx) {
    ub4 i;
    ub4 j;
    ub4 k;

    static char text[] = "This is <i>not</i> the right mytext.";

    std::memcpy((char *) ctx.rand_rsl, (char *) text, sizeof(text));

    rand_init(&ctx, TRUE);

    for (i = 0, k = 0; i < 10; ++i) {
        for (j = 0; j < RANDSIZ; ++j) {
            std::cout << std::hex << std::setfill('0') << std::setw(8);
            std::cout << get_random_value(&ctx) << " ";

            if (++k == 8) {
                k = 0;
                std::cout << std::endl;
            }
        }
    }
}
