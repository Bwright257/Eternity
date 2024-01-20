#include "Text.h"

void Text::display(Location origin, Location size, int horiAlign, int vertAlign){
    Location innerOrigin = origin + 1;
    Location innerSize = size - 2;

    if (_isUnderlined){
        std::string line;

        for (size_t i = 0; i < _text.size(); i++){
            line += "─";
        }

        terminal_print_ext(innerOrigin.column(), innerOrigin.row() + 1, innerSize.column(), innerSize.row(), horiAlign | vertAlign, line.c_str());
        terminal_print_ext(innerOrigin.column(), innerOrigin.row(), innerSize.column(), innerSize.row(), horiAlign | vertAlign, _text.c_str());
    } else {
        terminal_print_ext(innerOrigin.column(), innerOrigin.row(), innerSize.column(), innerSize.row(), horiAlign | vertAlign, _text.c_str());
    }

    return;
}