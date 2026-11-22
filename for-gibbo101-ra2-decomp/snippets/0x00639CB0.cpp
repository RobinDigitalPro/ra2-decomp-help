// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00639CB0 (239 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x20e630 (VA 0x0060E630, 240 bytes incl. padding)
// RA2 symbol : ?Planning_Convert_Loop_Moves@@YIXPAVTechnoClass@@@Z
// similarity : 0.9901 (very-similar, masked instruction tokens; shape 0.9951)
// source TU  : src/m85/src/planmgr.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __fastcall Planning_Convert_Loop_Moves(TechnoClass * techno) // RA2: 0x00616A50; in the path of the techno turns the move orders after the loop start into the other move mission (event mission 2 into 0x29)
{
	// level-2 1.001: the member test sets a flag and the loop calls Promote_Events,
	// as gibbo101/ra2-decomp src/planmgr.cpp FUN_00639CB0 (YR 0x00639CB0, @719fcc7).
	PlanningTokenClass * token = techno->Get_Planning_Token(); // RA2: as above
	int count = token->Node_Count(); // RA2: as above
	int start = token->Get_Loop_Start(); // RA2: as above
	PlanningNodeClass * first = token->Node_At(0); // RA2: as above
	int members = first->Get_Count(); // RA2: as above
	bool attack_move = false;
	for (int i = 0; i < members; ++i) { // RA2: as above
		TechnoClass * owner = first->Member_Owner(i); // RA2: as above
		if (owner->CanAttackOnTheMove()) { // RA2: as above
			attack_move = true;
			break;
		}
	}
	if (attack_move) {
		for (int j = start; j < count; ++j) token->Node_At(j)->Promote_Events(); // RA2: as above
	}
}
