// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0065D480 (47 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x230ad0 (VA 0x00630AD0, 48 bytes incl. padding)
// RA2 symbol : ?Assign@rc_ptr_base@@QAEXPAX@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9744)
// source TU  : src/m85/src/rc_ptr_base.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void rc_ptr_base::Assign(void * ptr)
{
	rc_object * p = (rc_object *)ptr;
	if (p != Ptr) {
		if (p) {
			p->RefCount++;
		}
		rc_object * old = Ptr;
		if (old) {
			Ptr = 0;
			old->Release();
		}
		Ptr = p;
	}
}
