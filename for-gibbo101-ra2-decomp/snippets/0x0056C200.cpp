// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0056C200 (6 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x14bd50 (VA 0x0054BD50, 16 bytes incl. padding)
// RA2 symbol : ?Validate@MapClass@@QAEHXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.2857)
// source TU  : src/m85/src/map.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/***************************************************************************
 * MapClass::Validate -- validates every cell on the map                   *
 *                                                                         *
 * This is a debugging routine, designed to detect memory trashers that    *
 * alter the map.  This routine is slow, but thorough.                     *
 *                                                                         *
 * INPUT:                                                                  *
 *      none.                                                              *
 *                                                                         *
 * OUTPUT:                                                                 *
 *      true = map is OK, false = an error was found                       *
 *                                                                         *
 * WARNINGS:                                                               *
 *      none.                                                              *
 *                                                                         *
 * HISTORY:                                                                *
 *   07/08/1995 BRR : Created.                                             *
 *=========================================================================*/
int MapClass::Validate(void)
{
#if NEVER
	CELL cell;
	TemplateType ttype;
	unsigned char ticon;
	TemplateTypeClass const *tclass;
	unsigned char map[13*8];
	OverlayType overlay;
	SmudgeType smudge;
	ObjectClass * obj;
	LandType land;
	int i;

	BlubCell = &Array[797];

	if (BlubCell->Overlapper[1]) {
		obj = BlubCell->Overlapper[1];
		if (obj) {
			if (obj->IsInLimbo)
			obj = obj;
		}
	}

	/*
	**	Check every cell on the map, even those that aren't displayed,
	**	in the hopes of detecting a memory trasher.
	*/
	for (cell = 0; cell < MAP_CELL_TOTAL; cell++) {
		/*
		**	Validate Template & Icon data
		*/
		ttype = (*this)[cell].TType;
		ticon = (*this)[cell].TIcon;
		if (ttype >= TEMPLATE_COUNT && ttype != TEMPLATE_NONE)
			return(false);

		/*
		**	To validate the icon value, we have to get a copy of the template's
		**	"icon map"; this map will have 0xff's in spots where there is no
		**	icon.  If the icon value is out of range or points to an invalid spot,
		**	return an error.
		*/
		if (ttype != TEMPLATE_NONE) {
			tclass = TemplateTypes[ttype];
			ticon = (*this)[cell].TIcon;
			Mem_Copy(Get_Icon_Set_Map(tclass->Get_Image_Data()), map, tclass->Width * tclass->Height);
			if (ticon < 0 || ticon >= (tclass->Width * tclass->Height) || map[ticon] == ISOTILE_NONE_LEGACY) {
				return(false);
			}
		}

		/*
		**	Validate Overlay
		*/
		overlay = (*this)[cell].Overlay;
		if (overlay < OVERLAY_NONE || overlay >= OVERLAY_COUNT) {
			return(false);
		}

		/*
		**	Validate Smudge
		*/
		smudge = (*this)[cell].Smudge;
		if (smudge < SMUDGE_NONE || smudge >= SMUDGE_COUNT) {
			return(false);
		}

		/*
		**	Validate LandType
		*/
		land = (*this)[cell].Land_Type();
		if (land < LAND_CLEAR || land >= LAND_COUNT) {
			return(false);
		}

		/*
		**	Validate Occupier
		*/
		obj = (*this)[cell].Cell_Occupier();
		if (obj) {
			if (
				((unsigned int)obj & 0xff000000) ||
				((unsigned int)obj->Next & 0xff000000) ||
//				((unsigned int)obj->Trigger & 0xff000000) ||
				obj->IsInLimbo ||
				((unsigned int)obj->PositionCell >= MAP_CELL_TOTAL)) {

				return(false);
			}
		}

		/*
		**	Validate Overlappers
		*/
		for (i = 0; i < ARRAY_SIZE((*this)[cell].CellClass::Overlapper); i++) {
			obj = (*this)[cell].Overlapper[i];
			if (obj) {
				if (
					((unsigned int)obj & 0xff000000) ||
					((unsigned int)obj->Next & 0xff000000) ||
//					((unsigned int)obj->Trigger & 0xff000000) ||
					obj->IsInLimbo ||
					((unsigned int)obj->PositionCell >= MAP_CELL_TOTAL)) {

					return(false);
				}
			}
		}
	}
#endif
	return(true);
}
