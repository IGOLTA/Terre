//
// Created by louis on 19/05/22.
//

#include "MainMenu.h"

ui::MainMenu::MainMenu(const unsigned int* width, const unsigned int* height) : Panel(width, height){
    auto image = new Image(this, "image");

    image->setTexture(new resources::Texture("test.jpg", resources::TextureType::UI));
    image->setFitting(ui::ImageFitting::FIT_LARGER);

    addElement(image);
}

void ui::MainMenu::elementEventCallback(std::string name, std::string event) {

}