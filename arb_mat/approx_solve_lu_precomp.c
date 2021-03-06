/*
    Copyright (C) 2018 arbguest

    This file is part of Arb.

    Arb is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/

#include "arb_mat.h"

void
_arb_approx_submul(arb_t z, const arb_t x, const arb_t y, slong prec)
{
    arf_submul(arb_midref(z),
               arb_midref(x), arb_midref(y), prec, ARF_RND_DOWN);
}

void
_arb_approx_div(arb_t z, const arb_t x, const arb_t y, slong prec)
{
    arf_div(arb_midref(z), arb_midref(x), arb_midref(y), prec, ARB_RND);
}

void
arb_mat_approx_solve_lu_precomp(arb_mat_t X, const slong * perm,
    const arb_mat_t A, const arb_mat_t B, slong prec)
{
    slong i, j, c, n, m;

    n = arb_mat_nrows(X);
    m = arb_mat_ncols(X);

    if (X == B)
    {
        arb_ptr tmp = flint_malloc(sizeof(arb_struct) * n);

        for (c = 0; c < m; c++)
        {
            for (i = 0; i < n; i++)
                tmp[i] = B->rows[perm[i]][c];
            for (i = 0; i < n; i++)
                X->rows[i][c] = tmp[i];
        }

        flint_free(tmp);
    }
    else
    {
        for (c = 0; c < m; c++)
        {
            for (i = 0; i < n; i++)
            {
                arb_set(arb_mat_entry(X, i, c),
                    arb_mat_entry(B, perm[i], c));
            }
        }
    }

    arb_mat_get_mid(X, X);

    for (c = 0; c < m; c++)
    {
        /* solve Ly = b */
        for (i = 1; i < n; i++)
        {
            for (j = 0; j < i; j++)
            {
                _arb_approx_submul(arb_mat_entry(X, i, c),
                    arb_mat_entry(A, i, j), arb_mat_entry(X, j, c), prec);
            }
        }

        /* solve Ux = y */
        for (i = n - 1; i >= 0; i--)
        {
            for (j = i + 1; j < n; j++)
            {
                _arb_approx_submul(arb_mat_entry(X, i, c),
                    arb_mat_entry(A, i, j), arb_mat_entry(X, j, c), prec);
            }

            _arb_approx_div(arb_mat_entry(X, i, c), arb_mat_entry(X, i, c),
                arb_mat_entry(A, i, i), prec);
        }
    }
}
