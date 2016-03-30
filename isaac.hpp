#ifndef __ISAAC_HPP
#define __ISAAC_HPP

#include "standard.hpp"

#define RANDSIZL     (8)
#define RANDSIZ      (1 << RANDSIZL) // 1 << 8 -> 256
#define GOLDEN_RATIO 0x9e3779b9

#define get_random_value(r) \
    (!(r)->rand_cnt-- ? \
      (isaac(r), (r)->rand_cnt =RANDSIZ-1, (r)->rand_rsl[(r)->rand_cnt]) : \
      (r)->rand_rsl[(r)->rand_cnt])

/* random number generator context */
struct rand_context {
    ub4 rand_cnt;          /* Result counter */
    ub4 rand_rsl[RANDSIZ]; /* Result array */
    ub4 rand_mem[RANDSIZ]; /* Array of RANDSIZ */
    ub4 rand_a;            /* Accumulator, a single value */
    ub4 rand_b;            /* The previous result */
    ub4 rand_c;            /* Counter */
};

typedef struct rand_context rand_ctx;

void rand_init(rand_ctx *r, word flag);

void isaac(rand_ctx *r);

#endif // __ISAAC_HPP

