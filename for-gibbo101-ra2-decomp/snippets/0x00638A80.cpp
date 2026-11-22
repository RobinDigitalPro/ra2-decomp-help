// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00638A80 (195 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20d400 (VA 0x0060D400, 208 bytes incl. padding)
// RA2 symbol : ?Planning_New_Token@@YIPAVPlanningTokenClass@@PAVTechnoClass@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9023)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

PlanningTokenClass * __fastcall Planning_New_Token(TechnoClass * techno) // RA2: 0x00615820; makes the planning token of a techno and lists it
{
	PlanningTokenClass * token = new PlanningTokenClass(techno); // RA2: as above
	PlanningTokenClass::Array.Add(token); // RA2: as above
	techno->Set_Planning_Token(token); // RA2: as above
	return token; // RA2: as above
}
