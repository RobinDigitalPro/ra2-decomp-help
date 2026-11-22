// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x006386E0 (337 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20d060 (VA 0x0060D060, 352 bytes incl. padding)
// RA2 symbol : ?Planning_Clear_Techno@@YIXPAVTechnoClass@@PAVEventClass@@@Z
// similarity : 0.9911 (very-similar, masked instruction tokens; shape 0.9372)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __fastcall Planning_Clear_Techno(TechnoClass * techno, EventClass * event) // RA2: 0x00615480; after an order that is not a planned one, lets go of the planning token of a techno that has nodes, and lets the token run again
{
	if (techno) { // RA2: as above
		PlanningTokenClass * token = techno->Get_Planning_Token(); // RA2: as above
		if (token) { // RA2: as above
			int planned = event ? event->Data.MegaMission.IsPlanningEvent : 0; // RA2: as above
			if (!planned && token->Node_Count() > 0) { // RA2: as above
				Planning_Cancel_Token(techno); // RA2: as above
			}
			token->Clear_F1C(); // RA2: as above
		}
	}
}
