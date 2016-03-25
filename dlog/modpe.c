/*=============================================================================

    This file is part of ARB.

    ARB is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    ARB is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with ARB; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2016 Pascal Molin

******************************************************************************/

#include "dlog.h"

ulong
dlog_modpe(const dlog_modpe_t t, ulong b)
{
    ulong x;
    x = dlog_precomp(t->modp, b % t->p);
    if (t->e > 1)
    {
        ulong b1, y;
#if 0
        b1 = nmod_mul(b, nmod_pow_ui(t->inva, x, t->pe), t->pe);
#else
        b1 = nmod_pow_ui(b, t->p - 1, t->pe);
#endif
        if (1 || t->e <= 2)
            y = dlog_1modpe_rec(t->modpe.rec, b1, t->p, t->e, t->pe);
        else
            y = dlog_1modpe_padic(t->modpe.padic, b1);
        y = y % t->pe1;
#if 0
        x = x + (t->p - 1) * y;
#else
        x = n_submod(x, y % (t->p - 1), t->p - 1);
        x = y + t->pe1 * x;
#endif
    }
    return x;
}
