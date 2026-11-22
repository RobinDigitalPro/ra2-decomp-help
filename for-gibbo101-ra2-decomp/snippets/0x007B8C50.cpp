// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007B8C50 (9 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x35d880 (VA 0x0075D880, 16 bytes incl. padding)
// RA2 symbol : ?Is_Data_Valid@WWMouseClass@@ABE_NXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.5333)
// source TU  : src/m85/src/wwmouse.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/***********************************************************************************************
 * WWMouseClass::Is_Data_Valid -- Determines if there is valid shape image data.               *
 *                                                                                             *
 *    This routine does a simple check to determine if the shape handler has been supplied     *
 *    a pointer to shape imagery. Any internal routine that requires the data to be present    *
 *    should call this routine to be sure it actually is.                                      *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  bool; Has a shape image data pointer been supplied to this mouse handler?          *
 *                                                                                             *
 * WARNINGS:   When the mouse object is first created, no image data has been assigned. The    *
 *             Set_Cursor must be called before this routine will return TRUE.                 *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   03/10/1997 JLB : Created.                                                                 *
 *=============================================================================================*/
bool WWMouseClass::Is_Data_Valid(void) const
{
	if (MouseShape != NULL) {
		return(true);
	}
	return(false);
}
