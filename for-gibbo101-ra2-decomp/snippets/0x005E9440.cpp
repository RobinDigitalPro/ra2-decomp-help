// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005E9440 (37 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1c2de0 (VA 0x005C2DE0, 48 bytes incl. padding)
// RA2 symbol : ?Is_AI_Entry@@YI_NPAUNodeNameType@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.6857)
// source TU  : src/m85/src/netshare.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

bool __fastcall Is_AI_Entry(NodeNameType * entry) // RA2: 0x005C9370, not in TibSun; the entry is a computer player, as above
{
	return(entry != NULL && (entry == LobbyEntries[2] || entry == LobbyEntries[3] || entry == LobbyEntries[4])); // RA2: as above
}
