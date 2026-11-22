// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0049B720 (62 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x8df30 (VA 0x0048DF30, 64 bytes incl. padding)
// RA2 symbol : ??1CoopCampaignClass@@QAE@XZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9655)
// source TU  : src/ra2/coopcamp.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x48df30
CoopCampaignClass::~CoopCampaignClass()
{
    if (Maps != NULL) {
        for (int index = 0; index < MapCount; index++) {
            if (Maps[index] != NULL) {
                delete Maps[index];
            }
        }
        delete Maps;
    }
}
