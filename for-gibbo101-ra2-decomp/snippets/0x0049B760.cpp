// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0049B760 (117 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x8df70 (VA 0x0048DF70, 128 bytes incl. padding)
// RA2 symbol : ?Set_Players@CoopCampaignClass@@QAEXPBG0@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9043)
// source TU  : src/ra2/coopcamp.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x48df70
void CoopCampaignClass::Set_Players(wchar_t const * name1, wchar_t const * name2)
{
    if (name1 != NULL) {
        strcpy(Players[0].Name, To_Narrow(name1));
    } else {
        Players[0].Name[0] = '\0';
    }
    if (name2 != NULL) {
        strcpy(Players[1].Name, To_Narrow(name2));
    } else {
        Players[1].Name[0] = '\0';
    }
}
