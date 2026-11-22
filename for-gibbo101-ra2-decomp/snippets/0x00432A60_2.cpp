// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00432A60 (80 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x30130 (VA 0x00430130, 80 bytes incl. padding)
// RA2 symbol : ?Close@BinkMovieClass@@QAEXXZ
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 1.0000)
// source TU  : src/ra2/unnamed/TU_42FD50.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x430130
void BinkMovieClass::Close()
{
    if (Subtitles) {
        delete Subtitles;
        Subtitles = NULL;
    }
    if (Bink) {
        BinkClose(Bink);
        Bink = NULL;
    }
    if (File != INVALID_HANDLE_VALUE) {
        CloseHandle(File);
        File = INVALID_HANDLE_VALUE;
    }
}
