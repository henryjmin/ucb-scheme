#include "gmp-stklos.h"
#include "gmp.h"
#include "gmp-impl.h"
#include "longlong.h"
#undef ASSERT
#define ASSERT(expr)
/* mpn_cmp -- Compare two low-level natural-number integers.

Copyright (C) 1991, 1993, 1994, 1996 Free Software Foundation, Inc.

This file is part of the GNU MP Library.

The GNU MP Library is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or (at your
option) any later version.

The GNU MP Library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
License for more details.

You should have received a copy of the GNU Lesser General Public License
along with the GNU MP Library; see the file COPYING.LIB.  If not, write to
the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
MA 02111-1307, USA. */


/* Compare OP1_PTR/OP1_SIZE with OP2_PTR/OP2_SIZE.
   There are no restrictions on the relative sizes of
   the two arguments.
   Return 1 if OP1 > OP2, 0 if they are equal, and -1 if OP1 < OP2.  */

int
#if __STDC__
mpn_cmp (mp_srcptr op1_ptr, mp_srcptr op2_ptr, mp_size_t size)
#else
mpn_cmp (op1_ptr, op2_ptr, size)
     mp_srcptr op1_ptr;
     mp_srcptr op2_ptr;
     mp_size_t size;
#endif
{
  mp_size_t i;
  mp_limb_t op1_word, op2_word;

  for (i = size - 1; i >= 0; i--)
    {
      op1_word = op1_ptr[i];
      op2_word = op2_ptr[i];
      if (op1_word != op2_word)
	goto diff;
    }
  return 0;
 diff:
  /* This can *not* be simplified to
	op2_word - op2_word
     since that expression might give signed overflow.  */
  return (op1_word > op2_word) ? 1 : -1;
}
