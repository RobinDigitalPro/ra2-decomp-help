// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00623880 (1094 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x1f84d0 (VA 0x005F84D0, 1104 bytes incl. padding)
// RA2 symbol : ?Draw_Edit_Text@OwnerDraw@@YIXPAVSurface@@AAV?$TRect@H@@PBGHPAVBitFont@@IPAHHHHH@Z
// similarity : 0.9887 (very-similar, masked instruction tokens; shape 0.9860)
// source TU  : src/m85/src/ownrdraw.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

void __fastcall Draw_Edit_Text(Surface *surface, Rect &rect, wchar_t const *text, int caret, // RA2: as above
                                              BitFont *font, unsigned int color, int *scroll, int ime, // RA2: as above
                                              int password, int frame, int unknown9) // RA2: as above
{
    wchar_t buffer[0x800]; // RA2: as above
    int caret_x = -1; // RA2: as above
    int composition_length = 0; // RA2: as above
    int composing = 0; // RA2: as above
    if (text == 0) { // RA2: as above
        text = L""; // RA2: as above
    }
    int text_length = wcslen(text); // RA2: as above
    if (caret < 0 || caret > text_length) { // RA2: as above
        caret = 0; // RA2: as above
    }
    if (ime) { // RA2: as above
        IME_Update_Composition(); // RA2: as above
        composition_length = IMECompositionStringLength; // RA2: as above
        composing = IMEComposing; // RA2: as above
    }
    buffer[0] = 0; // RA2: as above
    wcsncpy(buffer, text, 0x800); // RA2: as above
    if (composition_length) { // RA2: as above
        wcsncpy(&buffer[caret], IMECompositionString, 0x800 - caret); // RA2: as above
        wcsncpy(&buffer[composition_length + caret], &text[caret], 0x800 - composition_length - caret); // RA2: as above
    }
    buffer[0x7FF] = 0; // RA2: as above
    int length = wcslen(buffer); // RA2: as above
    if (password && length > 0) { // RA2: as above
        wchar_t *p = buffer; // RA2: as above
        for (int i = length; i != 0; i--) { // RA2: as above
            *p++ = '*';
        }
    }
    int cursor; // RA2: as above
    if (composing || composition_length) { // RA2: as above
        cursor = IMECompositionCursorPos + caret; // RA2: as above
    } else {
        cursor = caret; // RA2: as above
    }
    if (cursor < *scroll + 5) { // RA2: as above
        if (cursor >= 5) { // RA2: as above
            *scroll = cursor - 5;
        } else {
            *scroll = 0;
        }
    }
    while (*scroll < length) { // RA2: as above
        if (font->Chars_In_Width(&buffer[*scroll], rect.Width - 5, 0, 0) >= cursor - *scroll) { // RA2: as above
            break;
        }
        (*scroll)++; // RA2: as above
    }
    int before = caret - *scroll; // RA2: as above
    int lead = Max_Of(before, 0); // RA2: as above
    int composed = composition_length; // RA2: as above
    if (before < 0) { // RA2: as above
        before += composition_length; // RA2: as above
        composed = Max_Of(before, 0); // RA2: as above
    }
    int after = length - composition_length - caret; // RA2: as above
    if (before < 0) { // RA2: as above
        after += before; // RA2: as above
    }
    if (after < 0) { // RA2: as above
        after = 0; // RA2: as above
    }
    text = &buffer[*scroll]; // RA2: as above
    if (frame) { // RA2: as above
        Rect area(rect.X - 1, rect.Y - 1, font->String_Pixel_Width(text, 0) + 5, rect.Height + 2); // RA2: as above
        surface->Fill_Rect(area, 0); // RA2: as above
    }
    if (lead) { // RA2: as above
        int width = OD_Draw_Text(color, font, rect, text, lead, 0, 0, surface, unknown9); // RA2: as above
        rect.X += width; // RA2: as above
        rect.Width -= width; // RA2: as above
        if (rect.Width < 0) { // RA2: as above
            rect.Width = 0; // RA2: as above
        }
        text += lead; // RA2: as above
    }
    if (composed) { // RA2: as above
        cursor -= *scroll + lead; // RA2: as above
        int rest; // RA2: as above
        if (cursor < 0 || cursor > composed) { // RA2: as above
            rest = -1; // RA2: as above
        } else {
            rest = composed - cursor; // RA2: as above
            composed -= rest; // RA2: as above
        }
        if (composed > 0) { // RA2: as above
            int width = OD_Draw_Text(Tab_Text_Color, font, rect, text, composed, 0, 0, surface, unknown9); // RA2: as above
            rect.X += width; // RA2: as above
            rect.Width -= width; // RA2: as above
            if (rect.Width < 0) { // RA2: as above
                rect.Width = 0; // RA2: as above
            }
            text += composed; // RA2: as above
        }
        if (rest >= 0) { // RA2: as above
            caret_x = rect.X; // RA2: as above
            if (rest) { // RA2: as above
                int width = OD_Draw_Text(Tab_Text_Color, font, rect, text, rest, 0, 0, surface, unknown9); // RA2: as above
                rect.X += width; // RA2: as above
                rect.Width -= width; // RA2: as above
                if (rect.Width < 0) { // RA2: as above
                    rect.Width = 0; // RA2: as above
                }
                text += rest; // RA2: as above
            }
        }
    } else {
        caret_x = rect.X; // RA2: as above
    }
    if (after) { // RA2: as above
        int width = OD_Draw_Text(color, font, rect, text, after, 0, 0, surface, unknown9); // RA2: as above
        rect.X += width; // RA2: as above
        rect.Width -= width; // RA2: as above
        if (rect.Width < 0) { // RA2: as above
            rect.Width = 0; // RA2: as above
        }
    }
    if (ime && caret_x > 0 && !Caret_Hidden) { // RA2: as above
        Draw_Edge_Glow(surface, Point2D(caret_x, rect.Y), Point2D(caret_x, rect.Y + rect.Height - 2), // RA2: as above
                                      White_Color, 0xFF); // RA2: as above
        Draw_Edge_Glow(surface, Point2D(caret_x + 1, rect.Y), Point2D(caret_x + 1, rect.Y + rect.Height - 2), // RA2: as above
                                      White_Color, 0xFF); // RA2: as above
    }
    Caret_Hidden = 0; // RA2: as above
}
