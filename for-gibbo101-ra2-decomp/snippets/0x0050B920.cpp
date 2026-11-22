// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0050B920 (219 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0xf4990 (VA 0x004F4990, 224 bytes incl. padding)
// RA2 symbol : ?Normalize_Color@@YIXAAN00@Z
// similarity : 0.9600 (very-similar, masked instruction tokens; shape 0.9677)
// source TU  : src/m85/src/house.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Handles the computer's use of the drop pod super weapon.
/// This routine picks a landing site out along a randomly chosen edge of the map and
/// fires the super weapon at it, provided the house has an enemy worth harassing.
/// </summary>
void __fastcall Normalize_Color(double & red, double & green, double & blue) // RA2: RA2's form
{
	double length = fastmath::sqrt(red * red + green * green + blue * blue); // RA2: as above
	if (length == 0.0) { // RA2: as above
		blue = 255.0; // RA2: as above
		green = 255.0; // RA2: as above
		red = 255.0; // RA2: as above
	} else {
		red = red * 240.0 / length; // RA2: as above
		if (red > 255.0) { // RA2: as above
			red = 255.0; // RA2: as above
		}
		green = green * 240.0 / length; // RA2: as above
		if (green > 255.0) { // RA2: as above
			green = 255.0; // RA2: as above
		}
		blue = blue * 240.0 / length; // RA2: as above
		if (blue > 255.0) { // RA2: as above
			blue = 255.0; // RA2: as above
		}
	}
}
