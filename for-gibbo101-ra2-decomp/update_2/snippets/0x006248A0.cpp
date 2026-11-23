// ra2-decomp help snippet, update 2 (RA2 1.001 level-2 reconstruction; NOT verified on gamemd.exe)
// YR address : 0x006248A0 (136 bytes; gibbo101/ra2-decomp name: none)
// RA2 address: RVA 0x1f9500 (VA 0x005F9500, 136 bytes without padding)
// RA2 symbol : ?shrinkVector@?$ArrayList@UCellData@OwnerDraw@@@@AAEDXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 1.0000)
// evidence   : byte-identical in RA2 1.001 under VC6 12.00.8168 -O2 -Ob2 -Gr -GR -DNDEBUG -Gy
// source TU  : src/m85/src/ownrdraw.cpp
// License    : GPL-3.0-or-later. Our source is GPL and contains EA GPL code (section 7 terms)
//              and code adapted from mischa85/RedAlert2 and gibbo101/ra2-decomp; their
//              credits are kept. The notice of the source file follows. See ../README.md.
// Use        : a read-only lead. RA2 layouts and names; port it and match it on your own checker.
// defined in : src/m85/include/arraylist.h (an inline or template member, emitted in this TU)

/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2025 Electronic Arts Inc.
 * Copyright 2026 OpenTS contributors
 *
 * Contains material derived from Electronic Arts source code.
 * Modified by OpenTS contributors, 2026.
 * EA's GPLv3 Section 7 additional terms and supplemental warranty
 * disclaimers apply; see LICENSE.md.
 ******************************************************************************/

template <class T>
char ArrayList<T>::shrinkVector(void)
{

	if ((Entries_ * 3) > Slots_)
		return(FALSE);

	int   newSlots = Slots_ / 2;
	if (newSlots < INITIAL_SIZE)
		newSlots = INITIAL_SIZE;

	if (newSlots >= Slots_)
		return(FALSE);

	T * newVector = (T*)(new unsigned char[newSlots * sizeof(T)]);

	if (Vector_)
		memcpy(newVector, Vector_, Entries_ * sizeof(T));

	delete[]((unsigned char*)Vector_);

	Vector_ = newVector;
	Slots_ = newSlots;

	return(TRUE);
}
