// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007693F0 (69 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x31f2e0 (VA 0x0071F2E0, 80 bytes incl. padding)
// RA2 symbol : ?Set_Back_Down@Map@WorldDominationTour@@QAEXPAVMSEngine@@_N@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8254)
// source TU  : src/m85/src/wdtmap.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// RA2: as Set_Back_Hot, for whether the button is down.
/// </summary>
void Map::Set_Back_Down(MSEngine * engine, bool down) // RA2: as Set_Back_Hot, for whether the button is down
{
	if (BackButton.IsDown != down) { // RA2: as above
		BackButton.IsDown = down; // RA2: as above
		BackButton.Anim->Set_Frame(BackFrames.IsHot && BackButton.IsDown ? BackFrames.Depressed : BackFrames.Normal); // RA2: as above
		engine->Broadcast(&BackButtonRect); // RA2: as above
		engine->Redraw(); // RA2: as above
	}
}
