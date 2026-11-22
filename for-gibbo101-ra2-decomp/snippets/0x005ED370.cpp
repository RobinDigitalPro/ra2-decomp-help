// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005ED370 (136 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1c5140 (VA 0x005C5140, 144 bytes incl. padding)
// RA2 symbol : ?Load_Random_Map_Preview@@YIXPAUHWND__@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9200)
// source TU  : src/m85/src/netshare.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __fastcall Load_Random_Map_Preview(HWND dialog) // RA2: 0x005CC800, not in TibSun; the preview of a random map is read from RandMap.img, any other map's is drawn
{
	if (Session.Scenarios[Session.Options.ScenarioIndex]->Is_Random_Map()) { // RA2: as above
		delete MultiplayerMapPreview; // RA2: as above
		MultiplayerMapPreview = new MapPreviewClass; // RA2: as above
		MultiplayerMapPreview->Read_PCX_Preview("RandMap.img"); // RA2: as above
		if (MultiplayerMapPreview->Get_Preview_Surface() == NULL) { // RA2: as above
			Update_Network_Dialog_Preview(dialog); // RA2: as above
		}
		InvalidateRect(dialog, NULL, FALSE); // RA2: as above
	} else {
		Update_Network_Dialog_Preview(dialog); // RA2: as above
	}
}
