#include "example_game.hpp"
#include "hsnr64/palette.hpp"

#include <hsnr64/offset.hpp>
#include <iostream>
//#include <tilefont.h>

namespace JanSordid::SDL_Example {
    void IntroState::Init() {
        Base::Init();

        if (!_font) {
            _font = TTF_OpenFont(BasePath "asset/font/RobotoSlab-Bold.ttf", 4.0f * _game.scalingFactor());
            TTF_SetFontHinting(_font, TTF_HINTING_LIGHT);
            if (!_font)
                print(stderr, "TTF_OpenFont failed: {}\n", TTF_GetError());
        }

        if (!_fontButtons) {
            _fontButtons = TTF_OpenFont(BasePath "asset/font/KellyAnnGothic.ttf", 16.0f * _game.scalingFactor());
            TTF_SetFontHinting(_fontButtons, TTF_HINTING_LIGHT);
            if (!_fontButtons)
                print(stderr, "TTF_OpenFont failed: {}\n", TTF_GetError());
        }

        if (!_UISprite) {
            _UISprite = IMG_LoadTexture(renderer(), BasePath "asset/graphic/ui-elements.png");
            if (!_UISprite)
                print(stderr, "IMG_LoadTexture UI Elements failed: {}\n", SDL_GetError());
        }

        if (!_image) {
            _image = IMG_LoadTexture(renderer(), BasePath "asset/graphic/Main-Menu/background.png");
            if (!_image)
                print(stderr, "IMG_LoadTexture Background failed: {}\n", IMG_GetError());
        }

        if (!_logo) {
            _logo = IMG_LoadTexture(renderer(), BasePath "asset/graphic/Main-Menu/logo.png");
            if (!_logo)
                print(stderr, "IMG_LoadTexture Logo failed: {}\n", IMG_GetError());
        }

        if (!_music) {
            _music = Mix_LoadMUS(BasePath "asset/music/The True Story of Beelzebub.ogg");
            if (!_music)
                print(stderr, "Mix_LoadMUS failed: {}\n", Mix_GetError());
        }

        _game.data.unlocks.insert(Tower::TowerType::Archer1);

        if (!startButtonTexture) {
            //TTF_Font *buttonFont = TTF_OpenFont(BasePathFont "RobotoSlab-Bold.ttf", 24);
            if (_fontButtons) {
                SDL_Color white = {255, 255, 255, 255};
                SDL_Surface *btnSurf = TTF_RenderText_Blended(_fontButtons, "Start", white);
                if (btnSurf) {
                    startButtonTexture = SDL_CreateTextureFromSurface(renderer(), btnSurf);
                    SDL_FreeSurface(btnSurf);
                }
            }
        }

        if (!exitButtonTexture) {
            //TTF_Font *buttonFont = TTF_OpenFont(BasePathFont "RobotoSlab-Bold.ttf", 24);
            if (_fontButtons) {
                SDL_Color white = {255, 255, 255, 255};
                SDL_Surface *btnSurf = TTF_RenderText_Blended(_fontButtons, "Exit", white);
                if (btnSurf) {
                    exitButtonTexture = SDL_CreateTextureFromSurface(renderer(), btnSurf);
                    SDL_FreeSurface(btnSurf);
                }
            }
        }

    }

    void IntroState::Enter(bool stacking) {
        Base::Enter(stacking);
        Mix_PlayMusic(_music, -1);
    }

    void IntroState::Exit(bool stacking) {
        Mix_HaltMusic();
        Base::Exit(stacking);
    }

    void IntroState::Destroy() {
        // Keep everything loaded/allocated is also an option
        /*
        TTF_CloseFont( font );
        SDL_DestroyTexture( image );
        SDL_DestroyTexture( _blendedText );
        font = nullptr;
        image = nullptr;
        _blendedText = nullptr;
        */
        Base::Destroy();
    }

    bool IntroState::HandleEvent(const Event &event) {
        switch (event.type) {
            case SDL_KEYDOWN: {
                const Keysym &what_key = event.key.keysym;
                if (what_key.scancode == SDL_SCANCODE_F9) {
                    // crash/shutdown, since State #6 does not exist
                    _game.ReplaceState(MyGS::Invalid);
                } else if (what_key.scancode == SDL_SCANCODE_ESCAPE) {
                    _game.ReplaceState(MyGS::Intro);
                } else {
                    return false; // Not handled
                }

                return true; // Confusing control flow: Handled by all but the else case
            }

            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    Point mouse = {event.button.x, event.button.y};
                    if (OverworldState::IsMouseOver(startButton, mouse)) {
                        _game.PushState(MyGS::TdState);
                        return true;
                    } else if (OverworldState::IsMouseOver(exitButton, mouse)) {
                        SDL_Event quitEvent = {SDL_QUIT};
                        SDL_PushEvent(&quitEvent);
                    }
                }
                break;

            default:
                break;
        }

        return false;
    }

    void IntroState::Update(const u64 frame, const u64 totalMSec, const f32 deltaT) {
    }

    void IntroState::Render(const u64 frame, const u64 totalMSec, const f32 deltaTNeeded) {
        Point windowSize;
        SDL_GetWindowSize(window(), &windowSize.x, &windowSize.y);
        {
            const Rect dst_rect = {0, 0, windowSize.x, windowSize.y};
            SDL_RenderCopy(renderer(), _image, EntireRect, &dst_rect /* same result as EntireRect */ );
        }

        // Poor persons benchmark
        //for (uint x = 0; x < 100; ++x)

        constexpr const char *text =
                "Music by Patrick de Arteaga"
                "\nSource: https://patrickdearteaga.com";

        const Color outlineColor = _isDarkOutline
                                   ? Color{0, 0, 0, SDL_ALPHA_OPAQUE}
                                   : Color{255, 255, 255, SDL_ALPHA_OPAQUE};

        // Draw the text on top
        // _textmode == 0 is True Type (currently cached)
        // _textmode == 1 is Bitmap Font (currently uncached)

        if (_textmode == 0) {
            if (_blendedText == nullptr) {
                Surface *surf = TTF_RenderUTF8_Blended_Wrapped(_font, text, white, windowSize.x - _p.x);
                _blendedText = SDL_CreateTextureFromSurface(renderer(), surf);
                SDL_FreeSurface(surf);

                u32 fmt;
                int access;
                SDL_QueryTexture(_blendedText, &fmt, &access, &_blendedTextSize.x, &_blendedTextSize.y);
            }

            SDL_SetTextureColorMod(_blendedText, outlineColor.r, outlineColor.g, outlineColor.b);

            for (const Point &offset: HSNR64::ShadowOffset::Rhombus) {
                const Rect dst_rect = Rect{
                        windowSize.x - _blendedTextSize.x,
                        windowSize.y - _blendedTextSize.y,
                        _blendedTextSize.x,
                        _blendedTextSize.y
                } + offset;

                SDL_RenderCopy(renderer(), _blendedText, EntireRect, &dst_rect);
            }

            const Color &color = HSNR64::Palette(_colorIndex);
            SDL_SetTextureColorMod(_blendedText, color.r, color.g, color.b);

            const Rect dst_rect = {
                    windowSize.x - _blendedTextSize.x,
                    windowSize.y - _blendedTextSize.y,
                    _blendedTextSize.x,
                    _blendedTextSize.y
            };

            SDL_RenderCopy(renderer(), _blendedText, EntireRect, &dst_rect);
        }


        if (_logo) {
            SDL_Rect logoRect;
            SDL_QueryTexture(_logo, nullptr, nullptr, &logoRect.w, &logoRect.h);
            logoRect.x = (windowSize.x - logoRect.w) / 2;
            logoRect.y = (windowSize.y - logoRect.h) / 8;
            SDL_RenderCopy(renderer(), _logo, EntireRect, &logoRect);
        }

        int buttonWidth = windowSize.x / 4;
        int buttonHeight = windowSize.y / 12;

        Rect startButtonRect = {
                (windowSize.x - buttonWidth) / 2,
                windowSize.y / 2 + buttonHeight,
                buttonWidth,
                buttonHeight
        };
        startButton = startButtonRect;
        Rect exitButtonRect = {
                (windowSize.x - buttonWidth) / 2,
                startButtonRect.y + buttonHeight * 2,
                buttonWidth,
                buttonHeight
        };
        exitButton = exitButtonRect;
        Rect srcRect = {33, 0, 32, 32};

        // Buttons rendern
        SDL_RenderDrawRect(renderer(), &startButtonRect);
        SDL_RenderCopy(renderer(), _UISprite, &srcRect, &startButtonRect);
        SDL_RenderDrawRect(renderer(), &exitButtonRect);
        SDL_RenderCopy(renderer(), _UISprite, &srcRect, &exitButtonRect);

        // Buttons Text rendern
        // Poor persons benchmark
        //for (uint x = 0; x < 100; ++x)
        /*
        constexpr const char *startText = "Start";
        constexpr const char *exitText = "Exit";

        const Color outlineColor = _isDarkOutline
                                   ? Color{0, 0, 0, SDL_ALPHA_OPAQUE}
                                   : Color{255, 255, 255, SDL_ALPHA_OPAQUE};

        if (_textmode == 0) {
            if (_blendedStartText == nullptr) {
                Surface *surf = TTF_RenderUTF8_Blended_Wrapped(_fontButtons, startText, white, windowSize.x - _p.x);
                _blendedStartText = SDL_CreateTextureFromSurface(renderer(), surf);
                SDL_FreeSurface(surf);

                u32 fmt;
                int access;
                SDL_QueryTexture(_blendedStartText, &fmt, &access, &_blendedStartTextSize.x,
                                 &_blendedStartTextSize.y);
            }

            SDL_SetTextureColorMod(_blendedStartText, outlineColor.r, outlineColor.g, outlineColor.b);

            for (const Point &offset: HSNR64::ShadowOffset::Rhombus) {
                const Rect dst_rect = Rect{
                        startButtonRect.x - _blendedStartTextSize.x,
                        startButtonRect.y - _blendedStartTextSize.y,
                        _blendedStartTextSize.x,
                        _blendedStartTextSize.y
                } + offset;

                SDL_RenderCopy(renderer(), _blendedStartText, EntireRect, &dst_rect);
            }
        }
        */
        if (startButtonTexture) {
            int texW, texH;
            SDL_QueryTexture(startButtonTexture, nullptr, nullptr, &texW, &texH);

            SDL_Rect destRect;
            destRect.w = texW;
            destRect.h = texH;
            destRect.x = startButtonRect.x + (startButtonRect.w - texW) / 2;
            destRect.y = startButtonRect.y + (startButtonRect.h - texH) / 2;
            SDL_RenderCopy(renderer(), startButtonTexture, nullptr, &destRect);
        }

        if (exitButtonTexture) {
            int texW, texH;
            SDL_QueryTexture(exitButtonTexture, nullptr, nullptr, &texW, &texH);

            SDL_Rect destRect;
            destRect.w = texW;
            destRect.h = texH;
            destRect.x = exitButtonRect.x + (exitButtonRect.w - texW) / 2;
            destRect.y = exitButtonRect.y + (exitButtonRect.h - texH) / 2;
            SDL_RenderCopy(renderer(), exitButtonTexture, nullptr, &destRect);
        }

    }


#ifdef IMGUI

    void IntroState::RenderUI(const u64 frame, const u64 totalMSec, const f32 deltaTNeeded) {
        /*
        // ImGui Demo
        static bool show_demo_window = true;
        ImGui::SetNextWindowCollapsed( true, ImGuiCond_Once );
        ImGui::ShowDemoWindow( &show_demo_window );

        Point windowSize;
        SDL_GetWindowSize( window(), &windowSize.x, &windowSize.y );

        static bool autoUpdate = false;
        static bool drawColorNumber = false;
        //ImGuiIO & io = ImGui::GetIO();
        ImGui::Begin( "Introstate", nullptr, ImGuiWindowFlags_NoFocusOnAppearing );
        if( frame == 0 ) // Do not focus this new window
            ImGui::SetWindowFocus( nullptr );

        if( ImGui::SliderInt( "int", &_p.x, 0, windowSize.x/2 ) && autoUpdate )
            _blendedText = nullptr;

        ImGui::Checkbox( "Auto-Redraw", &autoUpdate );
        ImGui::SameLine();
        ImGui::Checkbox( "Dark Outline", &_isDarkOutline );

        if( ImGui::Button( "Redraw" ) )                            // Buttons return true when clicked (most widgets return true when edited/activated)
            _blendedText = nullptr;

        if( ImGui::SliderInt( "color index", &_colorIndex, 0, 63 ) ) {}

        static int charSelect = 65;
        ImGui::Text( "'%c'", (char) charSelect );
        ImGui::SameLine();
        if( ImGui::SliderInt( "charSel", &charSelect, 0, 255 ) ) {}

        /*
        TileFont::CharMetric & m = TileFont::char_metrics[charSelect];
        u8  min = 0,
            max = 8;
        ImGui::SliderScalarN( "cavity left", ImGuiDataType_U8, m.left, 8, &min, &max );
        ImGui::SliderScalarN( "cavity right", ImGuiDataType_U8, m.right, 8, &min, &max );
        */
        /*
        ImGui::Checkbox( "Draw Color Number", &drawColorNumber );

        ImGui::PushID( "fg color" );
        ImGui::PushStyleVar( ImGuiStyleVar_FrameBorderSize, 1 );
        // CARE: ImU32 as color is 0xAABBGGRR - opposite of what might be expected
        ImGui::PushStyleColor( ImGuiCol_Border, 0xAAFFFFFF );
        constexpr fmt::format_string<int>
            withNumber( "{:02}" ),
            withoutNumber( "  ##{:02}" );
        const fmt::format_string<int> & fmt = drawColorNumber
            ? withNumber
            : withoutNumber;

        auto needsLinebreak =[]( int i )
        {
            return i == 10 || i == 25 || i == 40 || i == 52;
        };

        for( int i = 0; i < 64; ++i )
        {
            const SDL_Color & color = HSNR64::Palette( i );
            const ImU32 pcol = ToU32( color );
            //const ImU32 pcol = std::bit_cast<ImU32>( hsnr64::Palette[i] );
            //Color color = hsnr64::Palette[i];
            ImGui::PushStyleColor( ImGuiCol_Button, pcol );
            ImGui::PushStyleColor( ImGuiCol_Text, pcol ^ 0x00808080 );
            if( ImGui::Button( format( fmt::runtime( fmt ), i ).c_str() ) )
                _colorIndex = i;
            ImGui::PopStyleColor( 2 );
            //ImGui::ColorButton( format( "color{}", i ).c_str(), *((ImVec4*)&hsnr64::Palette[i]), ImGuiColorEditFlags_Uint8 );
            //if(i%10 != 0)
            if( !needsLinebreak( i ) )
                ImGui::SameLine();
        }
        ImGui::NewLine(); // undo last SameLine
        ImGui::PopStyleColor();
        ImGui::PopStyleVar();
        ImGui::PopID();

        if( ImGui::Button( "Open" ) )
        {
            nfdwindowhandle_t nw;
            NFD::GetNativeWindowFromSDLWindow( window(), &nw );

            NFD::UniquePathN path;
            const NFD::Result result = NFD::OpenDialog( path, NFD::EmptyFilter, 0, NFD::EmptyDefaultPath, nw );    // Freezes execution of the Game

            //if( result == NFD::Result::NFD_OKAY )
                //print( "Success! Path is {0}\n", path.get() );
        }
        ImGui::SameLine();
        if( ImGui::Button( "OpenMultiple" ) )
        {
            NFD::UniquePathSet paths;
            const NFD::Result result = NFD::OpenDialogMultiple( paths, NFD::EmptyFilter, 0, NFD::EmptyDefaultPath );     // Freezes execution of the Game

            // TODO
            //if( result == NFD_OKAY )
            //	print( "Success! Path is {0}\n", fmt::join( paths.get(), ", " ) );
        }
        ImGui::SameLine();
        if( ImGui::Button( "Save" ) )
        {
            NFD::UniquePathN path;
            const NFD::Result result = NFD::SaveDialog( path, NFD::EmptyFilter, 0, NFD::EmptyDefaultPath );     // Freezes execution of the Game
            //	const NFD::Result result = NFD::SaveDialog();   // The same as above

            //if( result == NFD::Result::NFD_OKAY )
                //print( "Success! Path is {0}\n", path.get() );
        }
        ImGui::SameLine();
        if( ImGui::Button( "PickFolder" ) )
        {
            NFD::UniquePathN path;
            const NFD::Result result = NFD::PickFolder( path, NFD::EmptyDefaultPath );     // Freezes execution of the Game

            //if( result == NFD_OKAY )
                //print( "Success! Path is {0}\n", path.get() );
        }

        ImGui::End();
        */
    }

#endif

}