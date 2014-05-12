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

    Copyright (C) 2012, 2013 Fredrik Johansson

******************************************************************************/

#include "arb.h"

void
arb_pow_fmpz(arb_t y, const arb_t b, const fmpz_t e, long prec)
{
    arb_pow_fmpz_binexp(y, b, e, prec);
}

void
arb_pow_ui(arb_t y, const arb_t b, ulong e, long prec)
{
    fmpz_t f;
    fmpz_init_set_ui(f, e);
    arb_pow_fmpz(y, b, f, prec);
    fmpz_clear(f);
}

void
arb_ui_pow_ui(arb_t y, ulong b, ulong e, long prec)
{
    arb_t t;
    arb_init(t);
    arb_set_ui(t, b);
    arb_pow_ui(y, t, e, prec);
    arb_clear(t);
}

void
arb_si_pow_ui(arb_t y, long b, ulong e, long prec)
{
    arb_t t;
    arb_init(t);
    arb_set_si(t, b);
    arb_pow_ui(y, t, e, prec);
    arb_clear(t);
}

