//
// Created by louis on 19/05/22.
//

#ifndef TERRE_MAINMENU_H
#define TERRE_MAINMENU_H

#include "../Panel.h"
#include "../elements/Image.h"

namespace ui {

    class MainMenu : public Panel {
    private:
        void eventCallback(Element*, PanelEvent event, void* data);

    public:
        MainMenu(const unsigned int* width, const unsigned int* height);
    };

} // ui

#endif //TERRE_MAINMENU_H
