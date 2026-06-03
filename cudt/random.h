#ifndef OPENUDT___CUDT_RANDOM_H
#define OPENUDT___CUDT_RANDOM_H

/**
 * @file random.h
 * @brief random struct and related functions for simple random number generation.
 * @details This module defines the random struct, which holds a core integer and a state double for
 * a simple linear congruential generator (LCG).  It provides functions to set the core value and
 * update the core and state according to the LCG algorithm.  Users can call set_core
 * to initialize the generator and update_core to advance the state.  The current state can be
 * accessed via the state field of the random struct.
 * @author Ali Lafi
 * @date 2024-06
 */

#include "clite/micros.h"

cobject(crandom,
        int core;
        double state;);

void set_core(crandom *self, int core)
{
    self->core = core;
    self->state = (double)(core / (core >> 2));
}

void update_core(crandom *self)
{
    self->core = (self->core * 1103515245 + 12345) & 0x7fffffff;
    self->state = (double)self->core / 0x7fffffff;
}

void update_state();

#endif // OPENUDT___CUDT_RANDOM_H