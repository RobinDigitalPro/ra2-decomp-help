// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x005FC000 (287 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1d2af0 (VA 0x005D2AF0, 288 bytes incl. padding)
// RA2 symbol : ?Fill_Movie_List@OptionsClass@@QBEXPAUHWND__@@@Z
// similarity : 0.9545 (very-similar, masked instruction tokens; shape 0.9955)
// source TU  : src/ra2/Options.CPP (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/*
**  Fills a list box with the intro and all unlocked campaign movies.
*/
void OptionsClass::Fill_Movie_List(HWND list) const
{
    Add_Movie(list, &IntroMovie);

    if (SovietMovies >= 0) {
        int count = SovietMovies + 1;
        for (MovieInfoStruct const * movie = SovietMovieList; movie->Name != NULL && count > 0; movie++, count--) {
            Add_Movie(list, movie);
        }
    }

    if (AlliedMovies >= 0) {
        int count = AlliedMovies + 1;
        for (MovieInfoStruct const * movie = AlliedMovieList; movie->Name != NULL && count > 0; movie++, count--) {
            Add_Movie(list, movie);
        }
    }
}
