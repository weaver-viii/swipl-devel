/*  Part of SWI-Prolog

    Author:        Jan Wielemaker
    E-mail:        J.Wielemaker@cs.vu.nl
    WWW:           http://www.swi-prolog.org
    Copyright (C): 2013, VU University Amsterdam

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "pl-incl.h"
#ifdef O_META_ATOMS
#include "pl-metaatom.h"

		 /*******************************
		 *           META ATOMS		*
		 *******************************/

static int	compareMetaAtom(atom_t h1, atom_t h2);

static PL_blob_t meta_atom =
{ PL_BLOB_MAGIC,
  PL_BLOB_UNIQUE,
					/* unique representation of text */
  "meta_atom",
  NULL,					/* release */
  compareMetaAtom,			/* compare */
  writeMetaAtom,			/* write */
  NULL,					/* acquire */
  NULL,					/* save load to/from .qlf files */
  NULL
};


static const atom_t meta_atoms[] =
{ ATOM_nil,
  (atom_t)0
};


void
initMetaAtoms(void)
{ const atom_t *ap;

  PL_register_blob_type(&meta_atom);
  for(ap=meta_atoms; *ap; ap++)
  { Atom a = atomValue(*ap);
    a->type = &meta_atom;
  }
}


int
isMetaAtom(word w)
{ return isAtom(w) && atomValue(w)->type == &meta_atom;
}


atom_t
PL_new_meta_atom(const char *s)
{ int new;

  return lookupBlob(s, strlen(s), &meta_atom, &new);
}


static int
compareMetaAtom(atom_t h1, atom_t h2)
{ return strcmp(stringAtom(h1), stringAtom(h2));
}

#endif /* O_META_ATOMS */