#include "Menu.h"

Menu::Menu(std::vector<std::string> choices) : WidgetObject(), _choices(choices){
    for (size_t i = 0; i < _choices.size(); i++){
        _enabledStatus.push_back(true);
    }

    return;
}

void Menu::display(Location origin, Location size, int horiAlign, int vertAlign){
    Location innerOrigin{origin + 1};
    Location innerSize{size - 2};
    int offset{0};

    switch (vertAlign){
        case TK_ALIGN_TOP:
            offset = 0;
            break;
        case TK_ALIGN_MIDDLE:
            offset = _choices.size() / 2;
            break;
        case TK_ALIGN_BOTTOM:
            offset = _choices.size() - 1;
            break;
        default:
            break;
    }

    for (size_t i = 0; i < _choices.size(); i++){
        if (isEnabled(i)){
            if (i == _selection){
                terminal_bkcolor(color_from_name("white"));
                terminal_color(color_from_name("black"));
            } else {
                terminal_bkcolor(color_from_name("black"));
                terminal_color(color_from_name("white"));
            }
        } else {
            terminal_bkcolor(color_from_name("black"));
            terminal_color(color_from_name("gray"));
        }

        terminal_print_ext(innerOrigin.column(), innerOrigin.row() + i - offset, innerSize.column(), innerSize.row(), horiAlign | vertAlign, std::string{' ' + _choices[i] + ' '}.c_str());
    }

    terminal_bkcolor(color_from_name("black"));
    terminal_color(color_from_name("white"));
    return;
}

void Menu::incrementSelection(){
    _selection++;

    bool allDisabled{true};
    for (size_t i = _selection; i < _choices.size(); i++){
        if (isEnabled(i)){
            allDisabled = false;
        }
    }

    if (allDisabled){
         _selection = firstAvailableChoice(0, true);
    }

    if (!isEnabled(_selection)){
        _selection = firstAvailableChoice(_selection, true);

        if (!isEnabled(_selection)){
            _selection = firstAvailableChoice(_selection, false);
        }
    }

    return;
}

void Menu::decrementSelection(){
    _selection--;
    
    bool allDisabled{true};
    for (int i = _selection; i >= 0; i--){
        if (isEnabled(i)){
            allDisabled = false;
        }
    }

    if (allDisabled){
        _selection = firstAvailableChoice(_choices.size() - 1, false);
    }

    if (!isEnabled(_selection)){
        _selection = firstAvailableChoice(_selection, false);

        if (!isEnabled(_selection)){
            _selection = firstAvailableChoice(_selection, true);
        }
    }

    return;
}

size_t Menu::firstAvailableChoice(size_t selection, bool forwards){
    size_t choice{selection};

    if (forwards){
        for (size_t i = choice; i < _choices.size(); i++){
            if (isEnabled(i)){
                choice = i;
                i = _choices.size();
            }
        }
    } else {
        for (int i = choice; i >= 0; i--){
            if (isEnabled(i)){
                choice = i;
                i = -1;
            }
        }
    }

    return choice;
}

void Menu::enableChoice(size_t selection){
    _enabledStatus[selection] = true;
    return;
}

void Menu::disableChoice(size_t selection){
    _enabledStatus[selection] = false;
    return;
}

bool Menu::isEnabled(size_t selection){
    return _enabledStatus[selection];
}