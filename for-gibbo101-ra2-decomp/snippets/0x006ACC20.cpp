// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x006ACC20 (114 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x277fe0 (VA 0x00677FE0, 128 bytes incl. padding)
// RA2 symbol : ?AI_Difficulty_Name@@YIPBGH@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8293)
// source TU  : src/ra2/Skirmish.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

wchar_t const * AI_Difficulty_Name(int difficulty)
{
    if (difficulty == AI_NONE) {
#line 133 "C:\\RA2\\Skirmish.cpp"
        return Fetch_String("STT:PlayerNone", NULL, __FILE__, __LINE__);
    } else if (difficulty == AI_EASY) {
        return Fetch_String("STT:PlayerDumbAI", NULL, __FILE__, __LINE__);
    } else if (difficulty == AI_MEDIUM) {
        return Fetch_String("STT:PlayerSmartAI", NULL, __FILE__, __LINE__);
    } else if (difficulty == AI_HARD) {
        return Fetch_String("STT:PlayerGeniusAI", NULL, __FILE__, __LINE__);
    }
    return 0;
}
