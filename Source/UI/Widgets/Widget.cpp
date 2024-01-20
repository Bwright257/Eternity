#include "Widget.h"
#include "Renderer.h"

void Widget::drawBorder(Location origin, Location size){
    std::string hori{"─"}, vert{"│"}, topLeft{"┌"}, topRight{"┐"}, bottomLeft{"└"}, bottomRight{"┘"};

    terminal_clear_area(origin.column(), origin.row(), size.column(), size.row());
    for (int i = origin.row(); i < origin.row() + size.row(); i++){
        for (int j = origin.column(); j < origin.column() + size.column(); j++){
            if (i == origin.row() && j == origin.column()){
                terminal_print(j, i, topLeft.c_str());
            } else if (i == origin.row() && j == origin.column() + size.column() - 1){
                terminal_print(j, i, topRight.c_str());
            } else if (i == origin.row() + size.row() - 1 && j == origin.column()){
                terminal_print(j, i, bottomLeft.c_str());
            } else if (i == origin.row() + size.row() - 1 && j == origin.column() + size.column() - 1){
                terminal_print(j, i, bottomRight.c_str());
            } else if (i == origin.row() || i == origin.row() + size.row() - 1){
                terminal_print(j, i, hori.c_str());
            } else if (j == origin.column() || j == origin.column() + size.column() - 1){
                terminal_print(j, i, vert.c_str());
            }
        }
    }

    return;
}

void Widget::autoSize(Menu menu){
    Location padding = (Location(1, 5) * 2) + 2;
    size_t longest{0};

    for (auto & choice : menu.choices()){
        if (choice.size() > longest){
            longest = choice.size();
        }
    }

    size() = Location(menu.choices().size() + padding.row(), longest + padding.column());
    return;
}

void Widget::alignOrigin(int horiAlign, int vertAlign){
    switch (horiAlign){
        case TK_ALIGN_LEFT:
            origin().column() = 0;
            break;
        case TK_ALIGN_CENTER:
            origin().column() = renderer()->windowSize().column() / 2 - size().column() / 2;
            break;
        case TK_ALIGN_RIGHT:
            origin().column() = renderer()->windowSize().column() - size().column();
            break;
        default:
            break;
    }
    
    switch (vertAlign){
        case TK_ALIGN_TOP:
            origin().row() = 0;
            break;
        case TK_ALIGN_MIDDLE:
            origin().row() = renderer()->windowSize().row() / 2 - size().row() / 2;
            break;
        case TK_ALIGN_BOTTOM:
            origin().row() = renderer()->windowSize().row() - size().row();
            break;
        default:
            break;
    }

    return;
}