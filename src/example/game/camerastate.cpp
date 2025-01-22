#include <iostream>
#include "example_game.hpp"

namespace JanSordid::SDL_Example {

    void OverworldState::Init() {
        Base::Init();
        TTF_Init();

        if (!bg[0]) {
            bg[0] = IMG_LoadTexture(renderer(), BasePathGraphic "bg-layer-4.png");
            bg[1] = IMG_LoadTexture(renderer(), BasePathGraphic "bg-layer-3.png");
            bg[2] = IMG_LoadTexture(renderer(), BasePathGraphic "bg-layer-2.png");
            bg[3] = IMG_LoadTexture(renderer(), BasePathGraphic "bg-layer-1.png");

            SDL_QueryTexture(bg[0], nullptr, nullptr, &bgSize[0].x, &bgSize[0].y);
            SDL_QueryTexture(bg[1], nullptr, nullptr, &bgSize[1].x, &bgSize[1].y);
            SDL_QueryTexture(bg[2], nullptr, nullptr, &bgSize[2].x, &bgSize[2].y);
            SDL_QueryTexture(bg[3], nullptr, nullptr, &bgSize[3].x, &bgSize[3].y);

            SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
        }

        if (!buildingSprites[0]) {
            buildingSprites[0] = IMG_LoadTexture(renderer(), BasePathGraphic "Buildings/House_Hay_1.png");
            buildingSprites[1] = IMG_LoadTexture(renderer(), BasePathGraphic "Buildings/House_Hay_2.png");
            buildingSprites[2] = IMG_LoadTexture(renderer(), BasePathGraphic "Buildings/House_Hay_3.png");
            buildingSprites[3] = IMG_LoadTexture(renderer(), BasePathGraphic "Buildings/House_Hay_4_Purple.png");
        }

        Point windowSize;
        SDL_GetWindowSize(window(), &windowSize.x, &windowSize.y);

        buildings[0] = {50, windowSize.y - 250, 400, 200};
        buildings[1] = {500, windowSize.y - 230, 300, 200};
        buildings[2] = {1000, windowSize.y - 250, 200, 200};

        if (!tdButtonTexture) {
            TTF_Font *buttonFont = TTF_OpenFont(BasePathFont "RobotoSlab-Bold.ttf", 24);
            if (buttonFont) {
                SDL_Color white = {255, 255, 255, 255};
                SDL_Surface *btnSurf = TTF_RenderText_Blended(buttonFont, "Enter TD", white);
                if (btnSurf) {
                    tdButtonTexture = SDL_CreateTextureFromSurface(renderer(), btnSurf);
                    SDL_FreeSurface(btnSurf);
                }
                TTF_CloseFont(buttonFont);
            }
        }
        _game.data.day += 1;
        _game.data.gold += _game.data.mineLevel * 10;
        std::cout << _game.data.gold << std::endl;
    }

    void OverworldState::Destroy() {
        // TODO
        Base::Destroy();
        TTF_Quit();
    }

    bool OverworldState::HandleEvent(const Event &event) {
        if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
            if (event.key.keysym.scancode == SDL_SCANCODE_F1) bgIsVisible[0] = !bgIsVisible[0];
            if (event.key.keysym.scancode == SDL_SCANCODE_F2) bgIsVisible[1] = !bgIsVisible[1];
            if (event.key.keysym.scancode == SDL_SCANCODE_F3) bgIsVisible[2] = !bgIsVisible[2];
            if (event.key.keysym.scancode == SDL_SCANCODE_F4) bgIsVisible[3] = !bgIsVisible[3];

            if (event.key.keysym.scancode == SDL_SCANCODE_F5)
                bgIsVisible[0] = bgIsVisible[1] = bgIsVisible[2] = bgIsVisible[3] = !bgIsVisible[0];

            return true;
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                Point mouse = {event.button.x, event.button.y};
                for (int i = 0; i < 3; ++i) {
                    if (IsMouseOver(buildings[i], mouse)) {
                        if (gui == nullptr)
                            gui = OpenBuildingGUI(buildingTitles[i]);
                    }
                }
                if (IsMouseOver(tdButton, mouse)) {
                    _game.PushState(MyGS::TdState);
                    return true;
                }
            }
        }
        if (gui != nullptr) {
            HandleGUIEvent(event);
        }
        return false;
    }

    bool OverworldState::Input() {
        return false;
    }

    void OverworldState::Update(const u64 frame, const u64 totalMSec, const f32 deltaT) {

        if (gui != nullptr)
            UpdateGUI();
    }

    void OverworldState::Render(const u64 frame, u64 totalMSec, const f32 deltaT) {
        Point windowSize;
        SDL_GetWindowSize(window(), &windowSize.x, &windowSize.y);


        for (int i = 0; i < 4; ++i) {
            if (bgIsVisible[i]) {
                RenderLayer(windowSize, i);
            }
        }

        RenderBuildings(renderer());

        SDL_SetRenderDrawColor(renderer(), 80, 80, 80, 255);
        SDL_RenderFillRect(renderer(), &tdButton);

        SDL_SetRenderDrawColor(renderer(), 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer(), &tdButton);

        if (tdButtonTexture) {
            int texW, texH;
            SDL_QueryTexture(tdButtonTexture, nullptr, nullptr, &texW, &texH);

            SDL_Rect destRect;
            destRect.w = texW;
            destRect.h = texH;
            destRect.x = tdButton.x + (tdButton.w - texW) / 2;
            destRect.y = tdButton.y + (tdButton.h - texH) / 2;
            SDL_RenderCopy(renderer(), tdButtonTexture, nullptr, &destRect);
        }

        SDL_RenderPresent(renderer());
        if (gui != nullptr) {
            RenderGUI();
        }
    }

    void OverworldState::RenderLayer(const Point /*windowSize*/, const int index) const {
        SDL_RenderCopy(renderer(), bg[index], EntireRect, nullptr);
    }

    bool OverworldState::IsMouseOver(const SDL_Rect &rect, Point mouse) {
        return mouse.x >= rect.x && mouse.x < (rect.x + rect.w) &&
               mouse.y >= rect.y && mouse.y < (rect.y + rect.h);
    }

    void OverworldState::RenderBuildings(SDL_Renderer *renderer) {
        Point mouse;
        SDL_GetMouseState(&mouse.x, &mouse.y);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (int i = 0; i < 3; ++i) {

            SDL_RenderCopy(renderer, buildingSprites[i], nullptr, &buildings[i]);

            if (IsMouseOver(buildings[i], mouse))
                SDL_RenderDrawRect(renderer, &buildings[i]);
        }
    }

    BuildingGUI *OverworldState::OpenBuildingGUI(const char *windowTitle) {

        BuildingGUI *bgui = new BuildingGUI();
        bgui->title = windowTitle;
        bgui->shouldClose = false;
        bgui->window = SDL_CreateWindow(
                bgui->title,
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                400,
                300,
                SDL_WINDOW_SHOWN
        );

        if (!bgui->window) {
            std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
            delete bgui;
            return nullptr;
        }

        bgui->renderer = SDL_CreateRenderer(bgui->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        if (!bgui->renderer) {
            std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(bgui->window);
            delete bgui;
            return nullptr;
        }


        bgui->font = TTF_OpenFont(BasePathFont "RobotoSlab-Bold.ttf", 24);
        if (!bgui->font) {
            std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        } else {
            SDL_Color white = {255, 255, 255, 255};
            SDL_Surface *surf = TTF_RenderText_Blended(bgui->font, windowTitle, white);

            if (!surf) {
                std::cerr << "Failed to create text surface: " << TTF_GetError() << std::endl;
            } else {
                bgui->textTexture = SDL_CreateTextureFromSurface(bgui->renderer, surf);
                bgui->textRect = {20, 60, surf->w, surf->h}; // place the text
                SDL_FreeSurface(surf);
            }

            if (std::string(windowTitle) == "Mine") {
                std::cout << _game.data.gold << std::endl;
                std::string goldString = "Current Gold: " + std::to_string(_game.data.gold);
                const char *c_goldString = goldString.c_str();
                SDL_Surface *goldSurf = TTF_RenderText_Blended(bgui->font, c_goldString, white);
                if (!goldSurf) {
                    std::cerr << "Failed to create text surface: " << TTF_GetError() << std::endl;
                } else {
                    bgui->goldTexture = SDL_CreateTextureFromSurface(bgui->renderer, goldSurf);
                    bgui->goldRect = {20, 120, goldSurf->w, goldSurf->h}; // place the text
                    SDL_FreeSurface(goldSurf);
                }
                std::string upgradeString = "Current Upgrade Level: " + std::to_string(_game.data.mineLevel);
                const char *c_upgradeString = upgradeString.c_str();
                SDL_Surface *upgradeSurf = TTF_RenderText_Blended(bgui->font, c_upgradeString, white);
                if (upgradeSurf) {
                    bgui->upgradeTexture = SDL_CreateTextureFromSurface(bgui->renderer, upgradeSurf);
                    bgui->upgradeRect = {20, 240, upgradeSurf->w, upgradeSurf->h}; // place the text
                    SDL_FreeSurface(upgradeSurf);
                }
            } else if (std::string(windowTitle) == "Research") {
                if (!_game.data.unlocks.contains(Tower::TowerType::Mage1)) {
                    SDL_Surface *mageSurf = TTF_RenderText_Blended(bgui->font, "Mage", white);
                    if (mageSurf) {
                        bgui->mageTexture = SDL_CreateTextureFromSurface(bgui->renderer, mageSurf);
                        bgui->mageRect = {20, 120, mageSurf->w, mageSurf->h};
                        SDL_FreeSurface(mageSurf);
                    }
                }

                if (!_game.data.unlocks.contains(Tower::TowerType::Catapult1)) {
                    SDL_Surface *catapultSurf = TTF_RenderText_Blended(bgui->font, "Catapult", white);
                    if (catapultSurf) {
                        bgui->catapultTexture = SDL_CreateTextureFromSurface(bgui->renderer, catapultSurf);
                        bgui->catapultRect = {100, 120, catapultSurf->w, catapultSurf->h};
                        SDL_FreeSurface(catapultSurf);
                    }
                }
            }
        }

        return bgui;
    }

    void OverworldState::HandleGUIEvent(const JanSordid::SDL::Event &event) {
        if (gui == nullptr || gui->shouldClose)
            return;

        if (event.type == SDL_WINDOWEVENT) {
            if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
                gui->shouldClose = true;
            }
        } else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
            if (event.button.windowID == SDL_GetWindowID(gui->window)) {
                Point mouse = {event.button.x, event.button.y};
                SDL_Rect & button = gui->exitButton;
                SDL_Rect & upgradeButton = gui->upgradeButton;
                if (IsMouseOver(button, mouse))
                    gui->shouldClose = true;

                if (std::string(gui->title) == "Mine") {
                    //dummy upgrade cost
                    if (IsMouseOver(upgradeButton, mouse)) {
                        if (_game.data.gold >= _game.data.mineLevel * 3) {
                            _game.data.gold -= _game.data.mineLevel * 3;
                            _game.data.mineLevel += 1;
                        }
                    }
                } else if (std::string(gui->title) == "Research") {
                    if (!_game.data.unlocks.contains(Tower::TowerType::Mage1)) {
                        if (IsMouseOver(gui->mageButton, mouse)) {
                            if (_game.data.gold >= 100) {
                                _game.data.unlocks.insert(Tower::TowerType::Mage1);
                                std::cout << "Unlocked Mage tower" << std::endl;
                            }
                        }
                    }
                    if (!_game.data.unlocks.contains(Tower::TowerType::Catapult1)) {
                        if (IsMouseOver(gui->catapultButton, mouse)) {
                            if (_game.data.gold >= 500) {
                                _game.data.unlocks.insert(Tower::TowerType::Catapult1);
                                std::cout << "Unlocked Catapult tower." << std::endl;
                            }
                        }
                    }
                }
            }
        }
    }

    void OverworldState::UpdateGUI() {
        if (gui->shouldClose) {
            if (gui->textTexture) SDL_DestroyTexture(gui->textTexture);
            if (gui->goldTexture) SDL_DestroyTexture(gui->goldTexture);
            if (gui->upgradeTexture) SDL_DestroyTexture(gui->upgradeTexture);
            if (gui->mageTexture) SDL_DestroyTexture(gui->mageTexture);
            if (gui->catapultTexture) SDL_DestroyTexture(gui->catapultTexture);
            if (gui->font) TTF_CloseFont(gui->font);
            if (gui->renderer) SDL_DestroyRenderer(gui->renderer);
            if (gui->window) SDL_DestroyWindow(gui->window);
            delete gui;
            gui = nullptr;
        }
    }

    void OverworldState::RenderGUI() {
        if (!gui || gui->shouldClose) return;

        SDL_SetRenderDrawColor(gui->renderer, 40, 40, 40, 255);
        SDL_RenderClear(gui->renderer);

        if (gui->textTexture) {
            SDL_RenderCopy(gui->renderer, gui->textTexture, nullptr, &gui->textRect);
        }

        if (std::string(gui->title) == "Mine") {
            if (gui->goldTexture) {
                SDL_DestroyTexture(gui->goldTexture);
                gui->goldTexture = nullptr;

                std::string goldString = "Current Gold: " + std::to_string(_game.data.gold);
                const char *c_goldString = goldString.c_str();

                SDL_Color white = {255, 255, 255, 255};
                SDL_Surface *goldSurf = TTF_RenderText_Blended(gui->font, c_goldString, white);
                if (!goldSurf) {
                    std::cerr << "Failed to create gold text surface: " << TTF_GetError() << std::endl;
                } else {
                    gui->goldTexture = SDL_CreateTextureFromSurface(gui->renderer, goldSurf);
                    gui->goldRect = {20, 120, goldSurf->w, goldSurf->h};
                    SDL_FreeSurface(goldSurf);
                }

                SDL_RenderCopy(gui->renderer, gui->goldTexture, nullptr, &gui->goldRect);

            }

            if (gui->upgradeTexture) {
                SDL_DestroyTexture(gui->upgradeTexture);
                gui->upgradeTexture = nullptr;
                std::string upgradeString = "Current Upgrade Level: " + std::to_string(_game.data.mineLevel);
                const char *c_upgradeString = upgradeString.c_str();
                SDL_Color white = {255, 255, 255, 255};
                SDL_Surface *upgradeSurf = TTF_RenderText_Blended(gui->font, c_upgradeString, white);
                if (!upgradeSurf) {
                    std::cerr << "Failed to create text surface: " << TTF_GetError() << std::endl;
                } else {
                    gui->upgradeTexture = SDL_CreateTextureFromSurface(gui->renderer, upgradeSurf);
                    gui->upgradeRect = {20, 240, upgradeSurf->w, upgradeSurf->h}; // place the text
                    SDL_FreeSurface(upgradeSurf);
                }


                SDL_RenderCopy(gui->renderer, gui->upgradeTexture, nullptr, &gui->upgradeRect);

            }

            SDL_Rect upgradeButton = gui->upgradeButton;
            SDL_SetRenderDrawColor(gui->renderer, 80, 80, 80, 255);
            SDL_RenderFillRect(gui->renderer, &upgradeButton);

            SDL_SetRenderDrawColor(gui->renderer, 255, 255, 255, 255);
            SDL_RenderDrawRect(gui->renderer, &upgradeButton);

        } else if (std::string(gui->title) == "Research") {
            if (!_game.data.unlocks.contains(Tower::TowerType::Mage1)) {
                if (gui->mageTexture) {
                    SDL_RenderCopy(gui->renderer, gui->mageTexture, nullptr, &gui->mageRect);
                }
                // Mage Button
                SDL_SetRenderDrawColor(gui->renderer, 80, 80, 80, 255);
                SDL_RenderFillRect(gui->renderer, &gui->mageButton);

                SDL_SetRenderDrawColor(gui->renderer, 255, 255, 255, 255);
                SDL_RenderDrawRect(gui->renderer, &gui->mageButton);
            }

            if (!_game.data.unlocks.contains(Tower::TowerType::Catapult1)) {
                if (gui->catapultTexture) {
                    SDL_RenderCopy(gui->renderer, gui->catapultTexture, nullptr, &gui->catapultRect);
                }
                // Catapult Button
                SDL_SetRenderDrawColor(gui->renderer, 80, 80, 80, 255);
                SDL_RenderFillRect(gui->renderer, &gui->catapultButton);

                SDL_SetRenderDrawColor(gui->renderer, 255, 255, 255, 255);
                SDL_RenderDrawRect(gui->renderer, &gui->catapultButton);
            }
        }

        SDL_Rect button = gui->exitButton;
        SDL_SetRenderDrawColor(gui->renderer, 80, 80, 80, 255);
        SDL_RenderFillRect(gui->renderer, &button);

        SDL_SetRenderDrawColor(gui->renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(gui->renderer, &button);

        SDL_RenderPresent(gui->renderer);
    }


} // namespace
