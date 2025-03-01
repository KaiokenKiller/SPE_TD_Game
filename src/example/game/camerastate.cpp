#include <iostream>
#include "example_game.hpp"

namespace JanSordid::SDL_Example {

    std::string TowerTypeToString(Tower::TowerType type) {
        switch (type) {
            case Tower::TowerType::Archer1:
                return "Archer 1";
            case Tower::TowerType::Archer2_P1:
                return "Archer 2 P1";
            case Tower::TowerType::Archer3_P1:
                return "Archer 3 P1";
            case Tower::TowerType::Archer2_P2:
                return "Archer 2 P2";
            case Tower::TowerType::Archer3_P2:
                return "Archer 3 P2";
            case Tower::TowerType::Mage1:
                return "Mage 1";
            case Tower::TowerType::Mage2_P1:
                return "Mage 2 P1";
            case Tower::TowerType::Mage3_P1:
                return "Mage 3 P1";
            case Tower::TowerType::Mage2_P2:
                return "Mage 2 P2";
            case Tower::TowerType::Mage3_P2:
                return "Mage 3 P2";
            case Tower::TowerType::Catapult1:
                return "Catapult 1";
            case Tower::TowerType::Catapult2_P1:
                return "Catapult 2 P1";
            case Tower::TowerType::Catapult3_P1:
                return "Catapult 3 P1";
            case Tower::TowerType::Catapult2_P2:
                return "Catapult 2 P2";
            case Tower::TowerType::Catapult3_P2:
                return "Catapult 3 P2";
            default:
                return "Unknown Tower";
        }
    }

    bool OverworldState::unlockTower(Tower::TowerType tower, int unlockPrice) {
        if (_game.data.gold < unlockPrice)
            return false;


        _game.data.gold -= unlockPrice;
        _game.data.unlocks.insert(tower);
        if (_game.data.upgradePaths.contains(tower)) {
            for (const auto &upgrade: _game.data.upgradePaths[tower]) {
                _game.data.availableUpgrades.insert(upgrade);
            }
        }
        std::cout << "Unlocked: " + TowerTypeToString(tower) << std::endl;
        return true;
    }

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
        int windowWidth, windowHeight;
        SDL_GetRendererOutputSize(renderer(), &windowWidth, &windowHeight);
        buildings[0] = {50, windowSize.y - 250, 400, 200};
        buildings[1] = {500, windowSize.y - 230, 300, 200};
        buildings[2] = {1000, windowSize.y - 250, 200, 200};

        infoBackground = new Rect(
                windowWidth - (85 * scalingFactor()),
                8 * scalingFactor(),
                85 * scalingFactor(),
                42 * scalingFactor());

        mineBackground = new Rect({20, 120, 300, 400});

        researchBackground = new Rect({20, 120, 300, 400});

        if (!infoBackgroundTexture) {
            infoBackgroundTexture = IMG_LoadTexture(renderer(), BasePathGraphic "ui-elements.png");
        }

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

        if (!goldDisplayTexture) {
            if (TTF_Font *Font = TTF_OpenFont(BasePathFont "RobotoSlab-Bold.ttf", 24)) {
                SDL_Color white = {255, 255, 255, 255};
                std::string goldText = "Gold: " + std::to_string(_game.data.gold);
                const char *goldChar = goldText.c_str();
                if (SDL_Surface *btnSurf = TTF_RenderText_Blended(Font, goldChar, white)) {
                    goldDisplayTexture = SDL_CreateTextureFromSurface(renderer(), btnSurf);
                    SDL_FreeSurface(btnSurf);
                }
                TTF_CloseFont(Font);
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
                    if (SDL_PointInRect(&mouse, &buildings[i])) {
                        if (std::string(buildingTitles[i]) == "Research") {
                            showResearchIcons = !showResearchIcons;
                            if (showMineGui)
                                showMineGui = !showMineGui;
                        }

                        if (std::string(buildingTitles[i]) == "Mine") {
                            showMineGui = !showMineGui;
                            if (showResearchIcons)
                                showResearchIcons = !showResearchIcons;
                        }
                    }
                }

                if (showResearchIcons) {
                    for (const auto &unlockButton: buttonRects) {
                        if (SDL_PointInRect(&mouse, &unlockButton.button)) {
                            unlockTower(unlockButton.type, _game.data.upgradePrices[unlockButton.type]);
                        }
                    }
                }

                if (showMineGui) {
                    for (const auto &unlockButton: buttonRects) {
                        if (SDL_PointInRect(&mouse, &unlockButton.button)) {
                            if (_game.data.gold >= _game.data.mineLevel * 3) {
                                _game.data.gold -= _game.data.mineLevel * 3;
                                _game.data.mineLevel += 1;
                            }
                        }
                    }
                }

                if (SDL_PointInRect(&mouse, &tdButton)) {
                    _game.PushState(MyGS::TdState);
                    return true;
                }
            }
        }
        return false;
    }

    bool OverworldState::Input() {
        return false;
    }

    void OverworldState::Update(const u64 frame, const u64 totalMSec, const f32 deltaT) {
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

            SDL_Rect destRect = {tdButton.x + (tdButton.w - texW) / 2, tdButton.y + (tdButton.h - texH) / 2, texW,
                                 texH};
            SDL_RenderCopy(renderer(), tdButtonTexture, nullptr, &destRect);
        }
        SDL_RenderCopy(renderer(), infoBackgroundTexture, &infoBackgroundSrc, infoBackground);

        if (goldDisplayTexture) {
            SDL_DestroyTexture(goldDisplayTexture);
            goldDisplayTexture = nullptr;
            if (TTF_Font *Font = TTF_OpenFont(BasePathFont "RobotoSlab-Bold.ttf", 24)) {
                SDL_Color white = {255, 255, 255, 255};
                std::string goldText = "Gold: " + std::to_string(_game.data.gold);
                const char *goldChar = goldText.c_str();
                if (SDL_Surface *btnSurf = TTF_RenderText_Blended(Font, goldChar, white)) {
                    goldDisplayTexture = SDL_CreateTextureFromSurface(renderer(), btnSurf);
                    SDL_FreeSurface(btnSurf);
                }
                TTF_CloseFont(Font);
            }

            int texW, texH;
            SDL_QueryTexture(goldDisplayTexture, nullptr, nullptr, &texW, &texH);

            int windowWidth, windowHeight;
            SDL_GetRendererOutputSize(renderer(), &windowWidth, &windowHeight);

            SDL_Rect destRect;
            destRect.w = texW;
            destRect.h = texH;
            destRect.x = windowWidth - texW - 10 * scalingFactor();
            destRect.y = 10 * scalingFactor();
            SDL_RenderCopy(renderer(), goldDisplayTexture, nullptr, &destRect);
        }
        {
            if (waveDisplayTexture) {
                SDL_DestroyTexture(waveDisplayTexture);
                waveDisplayTexture = nullptr;
            }
            if (TTF_Font *Font = TTF_OpenFont(BasePathFont "RobotoSlab-Bold.ttf", 24)) {
                SDL_Color white = {255, 255, 255, 255};
                std::string waveText = "Wave: " + std::to_string(_game.data.wave + 1) + "/" +
                                       std::to_string(_game.data.totalWaves);
                const char *waveChar = waveText.c_str();
                if (SDL_Surface *btnSurf = TTF_RenderText_Blended(Font, waveChar, white)) {
                    waveDisplayTexture = SDL_CreateTextureFromSurface(renderer(), btnSurf);
                    SDL_FreeSurface(btnSurf);
                }
                TTF_CloseFont(Font);
            }

            int texW, texH;
            SDL_QueryTexture(waveDisplayTexture, nullptr, nullptr, &texW, &texH);

            int windowWidth, windowHeight;
            SDL_GetRendererOutputSize(renderer(), &windowWidth, &windowHeight);

            SDL_Rect destRect;
            destRect.w = texW;
            destRect.h = texH;
            destRect.x = windowWidth - texW - 10 * scalingFactor();
            destRect.y = 20 * scalingFactor();
            SDL_RenderCopy(renderer(), waveDisplayTexture, nullptr, &destRect);
        }

        {
            if (lifesDisplayTexture) {
                SDL_DestroyTexture(lifesDisplayTexture);
                lifesDisplayTexture = nullptr;
            }
            if (TTF_Font *Font = TTF_OpenFont(BasePathFont "RobotoSlab-Bold.ttf", 24)) {
                SDL_Color white = {255, 255, 255, 255};
                std::string waveText = "Lifes: " + std::to_string(_game.data.life);
                const char *waveChar = waveText.c_str();
                if (SDL_Surface *btnSurf = TTF_RenderText_Blended(Font, waveChar, white)) {
                    lifesDisplayTexture = SDL_CreateTextureFromSurface(renderer(), btnSurf);
                    SDL_FreeSurface(btnSurf);
                }
                TTF_CloseFont(Font);
            }

            int texW, texH;
            SDL_QueryTexture(lifesDisplayTexture, nullptr, nullptr, &texW, &texH);

            int windowWidth, windowHeight;
            SDL_GetRendererOutputSize(renderer(), &windowWidth, &windowHeight);

            SDL_Rect destRect;
            destRect.w = texW;
            destRect.h = texH;
            destRect.x = windowWidth - texW - 10 * scalingFactor();
            destRect.y = 30 * scalingFactor();
            SDL_RenderCopy(renderer(), lifesDisplayTexture, nullptr, &destRect);
        }

        if (showResearchIcons) {
            //SDL_RenderCopy(renderer(), infoBackgroundTexture, &infoBackgroundSrc, researchBackground);
            int buttonY = 120;
            buttonRects.clear();
            for (const auto &upgrade: _game.data.availableUpgrades) {
                if (_game.data.unlocks.contains(upgrade))
                    continue;

                UnlockButtons button;
                button.type = upgrade;
                std::string upgradeString =
                        TowerTypeToString(upgrade) + " - Cost: " + std::to_string(_game.data.upgradePrices[upgrade]);

                TTF_Font *font = TTF_OpenFont(BasePathFont "RobotoSlab-Bold.ttf", 24);
                SDL_Surface *surf = TTF_RenderText_Blended(font, upgradeString.c_str(), {255, 255, 255, 255});

                if (surf) {
                    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer(), surf);
                    int texW, texH;
                    SDL_QueryTexture(texture, nullptr, nullptr, &texW, &texH);
                    SDL_Rect buttonRect = {20, buttonY, texW, texH};
                    button.button = buttonRect;
                    SDL_RenderCopy(renderer(), texture, nullptr, &buttonRect);
                    SDL_FreeSurface(surf);
                    SDL_DestroyTexture(texture);
                }
                buttonY += 40;
                buttonRects.push_back(button);
            }

            SDL_RenderPresent(renderer());
        }

        if (showMineGui) {
            //SDL_RenderCopy(renderer(), infoBackgroundTexture, &infoBackgroundSrc, mineBackground);
            int buttonY = 120;
            buttonRects.clear();

            UnlockButtons button;
            std::string upgradeString = "Current Upgrade Level: " + std::to_string(_game.data.mineLevel);

            SDL_Color white = {255, 255, 255, 255};
            TTF_Font *font = TTF_OpenFont(BasePathFont "RobotoSlab-Bold.ttf", 24);
            SDL_Surface *upgradeSurf = TTF_RenderText_Blended(font, upgradeString.c_str(), white);
            if (upgradeSurf) {
                SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer(), upgradeSurf);
                int texW, texH;
                SDL_QueryTexture(texture, nullptr, nullptr, &texW, &texH);
                SDL_Rect buttonRect = {20, buttonY, texW, texH};
                button.button = buttonRect;
                SDL_RenderCopy(renderer(), texture, nullptr, &buttonRect);
                SDL_FreeSurface(upgradeSurf);
                SDL_DestroyTexture(texture);
            }
            buttonRects.push_back(button);
            SDL_RenderPresent(renderer());
        }

    }

    void OverworldState::RenderLayer(const Point /*windowSize*/, const int index) const {
        SDL_RenderCopy(renderer(), bg[index], EntireRect, nullptr);
    }

    void OverworldState::RenderBuildings(SDL_Renderer *renderer) {
        Point mouse;
        SDL_GetMouseState(&mouse.x, &mouse.y);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (int i = 0; i < 3; ++i) {

            SDL_RenderCopy(renderer, buildingSprites[i], nullptr, &buildings[i]);

            if (SDL_PointInRect(&mouse, &buildings[i]))
                SDL_RenderDrawRect(renderer, &buildings[i]);
        }
    }
} // namespace
