#include "isaac.hpp"

#define ind(mm, x) (*(ub4 *)((ub1 *)(mm) + ((x) & ((RANDSIZ-1) << 2))))

#define rngstep(mix, a, b, mm, m, m2, r, x) { \
    x = *m; \
    a = (a ^ (mix)) + *(m2++); \
    *(m++) = y = ind(mm, x) + a + b; \
    *(r++) = b = ind(mm, y >> RANDSIZL) + x; \
}

#define mix(a, b, c, d, e, f, g, h) { \
    a ^= b << 11; d += a; b += c; \
    b ^= c >> 2; e += b; c += d; \
    c ^= d << 8; f += c; d += e; \
    d ^= e >> 16; g += d; e += f; \
    e ^= f << 10; h += e; f += g; \
    f ^= g >> 4; a += f; g += h; \
    g ^= h << 8; b += g; h += a; \
    h ^= a >> 9; c += h; a += b; \
}

void isaac (rand_ctx *ctx) {
    ub4 a;
    ub4 b;
    ub4 x;
    ub4 y;
    ub4 *m;
    ub4 *mm;
    ub4 *m2;
    ub4 *r;
    ub4 *mend;

    mm = ctx->rand_mem;
    r = ctx->rand_rsl;
    a = ctx->rand_a;
    b = ctx->rand_b + (++ctx->rand_c);

    for (m = mm, mend = m2 = m + (RANDSIZ/2); m < mend;) {
        rngstep((a << 13), a, b, mm, m, m2, r, x);
        rngstep((a >> 6), a, b, mm, m, m2, r, x);
        rngstep((a << 2), a, b, mm, m, m2, r, x);
        rngstep((a >> 16), a, b, mm, m, m2, r, x);
    }

    for (m2 = mm; m2 < mend;) {
        rngstep((a << 13), a, b, mm, m, m2, r, x);
        rngstep((a >> 6), a, b, mm, m, m2, r, x);
        rngstep((a << 2), a, b, mm, m, m2, r, x);
        rngstep((a >> 16), a, b, mm, m, m2, r, x);
    }

    ctx->rand_b = b;
    ctx->rand_a = a;
}

/* If (flag == TRUE), then use the contents of rand_rsl[] to initialize mm[] */
void rand_init (rand_ctx *ctx, word flag) {
    word i;
    ub4 a;
    ub4 b;
    ub4 c;
    ub4 d;
    ub4 e;
    ub4 f;
    ub4 g;
    ub4 h;
    ub4 *m;
    ub4 *r;

    ctx->rand_a = ctx->rand_b = ctx->rand_c = 0;

    m = ctx->rand_mem;
    r = ctx->rand_rsl;

    a = b = c = d = e = f = g = h = GOLDEN_RATIO;

    for (i = 0; i < 4; ++i) {
        mix(a, b, c, d, e, f, g ,h);
    }

    if (!flag) {
        // Fill in m[] with messy stuff
        for (i = 0; i < RANDSIZ; i += 8) {
            mix(a, b, c, d, e, f, g, h);
            m[i  ] = a; m[i+1] = b; m[i+2] = c; m[i+3] = d;
            m[i+4] = e; m[i+5] = f; m[i+6] = g; m[i+7] = h;
        }
        // Create the first set of results
        isaac(ctx);
        // Prepare to use the first set of results
        ctx->rand_cnt = RANDSIZ;

        return;
    }

    // Initialize using the contents of r[] as the seed
    for (i = 0; i < RANDSIZ; i+= 8) {
        a += r[i  ]; b += r[i+1]; c += r[i+2]; d += r[i+3];
        e += r[i+4]; f += r[i+5]; g += r[i+6]; h += r[i+7];
        mix(a, b, c, d, e, f, g, h);
        m[i  ] = a; m[i+1] = b; m[i+2] = c; m[i+3] = d;
        m[i+4] = e; m[i+5] = f; m[i+6] = g; m[i+7] = h;
    }

    // do a second pass to make all of the seed affect all of m
    for (i = 0; i < RANDSIZ; i += 8) {
        a += r[i  ]; b += r[i+1]; c += r[i+2]; d += r[i+3];
        e += r[i+4]; f += r[i+5]; g += r[i+6]; h += r[i+7];
        mix(a, b, c, d, e, f, g, h);
        m[i  ] = a; m[i+1] = b; m[i+2] = c; m[i+3] = d;
        m[i+4] = e; m[i+5] = f; m[i+6] = g; m[i+7] = h;
    }

    // Create the first set of results
    isaac(ctx);
    // Prepare to use the first set of results
    ctx->rand_cnt = RANDSIZ;
}

