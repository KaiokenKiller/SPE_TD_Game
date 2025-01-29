#pragma once

#include "../global.hpp"

#include <sor/sdl_game.hpp>
#include <sor/sdl_shapeops.hpp>
//#include <autocast_ptr.h>
//#include <sor/tiles.h>

namespace JanSordid::SDL_Example {
    using namespace JanSordid;
    using namespace JanSordid::SDL;

    class MyGame;

    class MyGameState;

    class IntroState;

    class TdState;

    class OverworldState;

    // MyGameState-Index
    // Why not in the classes themselves? For reusability!
    enum class MyGS : u8 {
        Intro = 0,
        TdState,
        Overworld,
        Invalid
    };

    struct BuildingGUI {
        SDL_Window *window = nullptr;
        SDL_Renderer *renderer = nullptr;
        TTF_Font *font = nullptr;

        SDL_Texture *textTexture;
        SDL_Rect textRect = {};

        SDL_Texture *goldTexture;
        SDL_Rect goldRect = {};

        SDL_Texture *upgradeTexture;
        SDL_Rect upgradeRect = {};
        SDL_Rect upgradeButton = {20, 170, 60, 30};

        SDL_Texture *mageTexture;
        SDL_Rect mageRect = {};
        SDL_Rect mageButton = {20, 170, 60, 30};

        SDL_Texture *catapultTexture;
        SDL_Rect catapultRect = {};
        SDL_Rect catapultButton = {100, 170, 60, 30};

        SDL_Rect exitButton = {20, 10, 60, 30};

        bool shouldClose = false;

        const char *title;
    };

    class Enemy {
    public:

        int _hp;
        int _speed;
        bool _isAlive;

        Rect *_position = nullptr;
        Rect *_textureSrcRect = nullptr;
        Texture *_texture = nullptr;
		std::vector<FPoint> _path;
		int _currentPath = 0;

        Enemy(Rect *position, Texture *texture, const std::vector<FPoint> &path, int hp, int speed);

        void move(f32 deltaT);
		FPoint predictMove(f32 deltaT) const;

		bool takeDamage(int damage);
    };


    class Projectile {
    public:
        int _damage;
        bool _isVisible;
		FPoint _direction{};
        Enemy *_target;
		int _homingCounter = 100;
		int _speed = 200;

        Projectile(Rect *position, Texture *texture, int damage, Enemy *target);

        Rect *_position = nullptr;
        Texture *_texture = nullptr;

        void move(f32 deltaT);
	protected:
		void updateDirection();
    };

    class Tower {
    public:
        enum class TowerType {
            Archer1, Archer2_P1, Archer2_P2, Archer3_P1, Archer3_P2,
            Mage1, Mage2_P1, Mage2_P2, Mage3_P1, Mage3_P2,
            Catapult1, Catapult2_P1, Catapult2_P2, Catapult3_P1, Catapult3_P2
        };
        TowerType _type = TowerType::Archer1;
        Rect *_position = nullptr;
        Texture *_texture = nullptr;
		Texture * _projectileTexture = nullptr;
        int _attackDamage = 0;
        int _attackSpeed = 0;
        int _attackRange = 0;
        int _cooldown = 0;

        Tower(Rect *placement, Texture *texture, Texture * projectileTexture);

        virtual ~Tower() = default;

        virtual Projectile * shoot(Enemy *target, u64 totalMSec) = 0;

	protected:
		bool checkCooldown(u64 totalMSec);
    };

    class TowerArcher1 : public Tower {
    public:

        TowerArcher1(Rect *placement, Texture *texture, Texture * projectileTexture);

		Projectile * shoot(Enemy *target, u64 totalMSec) override;
    };

    class Mage1 : public Tower {
    public:

        Mage1(Rect *placement, Texture *texture, Texture * projectileTexture);

		Projectile * shoot(Enemy *target, u64 totalMSec) override;
    };

    class Catapult1 : public Tower {
    public:

        Catapult1(Rect *placement, Texture *texture, Texture * projectileTexture);

		Projectile * shoot(Enemy *target, u64 totalMSec) override;
    };

	class TowerSlot {
	public:
		Rect* _position;
		Texture* _texture;
		Rect* _textureSrcRect;
		Rect * _towerIconPosition[3];
		Rect* _towerIconSrc [3];
		Texture* _towerIconTextures[3];
		bool _clicked = false;
		bool _used = false;

		TowerSlot(Rect* position, Texture* texture, Rect* towerIconSrc [3], Texture* towerIconTextures[3]);
		Tower* placeTower(int selectedTower, const std::unordered_set<Tower::TowerType>& unlocks, std::unordered_map<Tower::TowerType,Texture*> projectileTextures);
	};

    struct GameData {
        int gold = 100;

        int mineLevel = 1;
        int day = 0;
        std::unordered_set<Tower::TowerType> unlocks;
        std::vector<Tower *> _towers;
    };

    // abstract
    class MyGameState : public SDL::GameState<MyGame> {
        using Base = GameState;

    public:
        // ctor
        using Base::Base;

    };

    class MyGame final : public SDL::Game<MyGameState, MyGS> {
        using Base = Game;

    public:
        MyGame();

        GameData data;

        bool HandleEvent(const Event &event) override;
    };


    class IntroState final : public MyGameState {
        using Base = MyGameState;

    protected:
        Owned<Font> _font = nullptr;
        Owned<Font> _fontButtons = nullptr;
        Owned<Texture> _image = nullptr;
        Owned<Texture> _logo = nullptr;
        Owned<Texture> _UISprite = nullptr;
        Owned<Texture> _blendedText = nullptr;
        Owned<Texture> _blendedStartText = nullptr;
        Owned<Texture> _blendedExitText = nullptr;
        Owned<Music> _music = nullptr;
        Owned<Chunk> _sound = nullptr;

        Point _blendedTextSize = {100, 100};
        Point _blendedStartTextSize = {100, 100};
        Point _blendedExitTextSize = {100, 100};

        u8 _textmode = 0;

        // Testvars controlled by ImGui
        Point _p = {0, 0};
        int _colorIndex = 9;
        bool _isDarkOutline = true;

        static constexpr const Color white{255, 255, 255, SDL_ALPHA_OPAQUE};
        static constexpr const Color black{0, 0, 0, SDL_ALPHA_OPAQUE};
        SDL_Rect startButton = {50, 50, 120, 40};
        Texture *startButtonTexture = nullptr;
        SDL_Rect exitButton = {50, 50, 120, 40};
        Texture *exitButtonTexture = nullptr;

    public:
        /// Ctors & Dtor
        using Base::Base;

        /// Getters & Setters: non-virtual first, followed by (pure) virtual/override
        [[nodiscard]] constexpr Color clearColor() const noexcept override {
            return Color{255, 255, 255, SDL_ALPHA_OPAQUE};
        }

        /// Methods: non-virtual first, followed by (pure) virtual/override
        void Init() override;

        void Enter(bool isStacking) override;

        void Exit(bool isStackedUpon) override;

        void Destroy() override;

        bool HandleEvent(const Event &event) override;

        void Update(u64 frame, u64 totalMSec, f32 deltaT) override;

        void Render(u64 frame, u64 totalMSec, f32 deltaT) override;

        ImGuiOnly(
                void RenderUI(u64 framesSinceStart, u64 msSinceStart, f32 deltaTNeeded) override;)
    };

    class TdState : public MyGameState {
        using Base = MyGameState;

    protected:
        //Eigener Stuff:
        SDL_Rect overworldButton = {50, 50, 120, 40};
        Texture *overworldButtonTexture = nullptr;
        Texture *enemyPathTile = nullptr;
        Texture *grassTile = nullptr;
        Texture *towerSlotTexture = nullptr;
        Texture *archerTowerTexture = nullptr;
		Texture *archerTowerArrowTexture = nullptr;
		Texture *mageTowerTexture = nullptr;
		Texture *mageTowerOrbTexture = nullptr;
        Texture *catapultTowerTexture = nullptr;
		Texture *catapultTowerStoneTexture = nullptr;
        Texture *enemyTexture = nullptr;

		Music * _music = nullptr;

        static constexpr int gridWidth = 40;
        static constexpr int gridHeight = 22;
        static constexpr int tileSize = 16;
        static constexpr int towerWidth = 70;
        static constexpr int towerHeight = 130;

        Rect *tileMap[gridHeight][gridWidth] = {nullptr};
        std::unordered_map<Tower::TowerType, Rect *> towerSrcRectMap;
		std::unordered_map<Texture *,Rect *> projectileSrcRectMap;
		std::unordered_map<Tower::TowerType,Texture *> projectileTextureMap;

		std::vector<TowerSlot*> _towerSlots;
        std::vector<Projectile *> _projectiles;
        std::vector<Enemy *> _enemies;

    public:
        // ctor
        using Base::Base;

        void Init() override;

        void Destroy() override;

        bool Input() override;

        bool HandleEvent(const Event &event) override;

        void Update(u64 frame, u64 totalMSec, f32 deltaT) override;

        void Render(u64 frame, u64 totalMSec, f32 deltaT) override;
    };

    class OverworldState : public MyGameState {
        using Base = MyGameState;

    protected:
        Texture *bg[4] = {nullptr};
        Texture *buildingSprites[4] = {nullptr};
        Point bgSize[4]; // Is initialized in Init()
        bool bgIsVisible[4] = {
                true,
                true,
                true,
                true,
        };
        SDL_Rect buildings[3];
        const char *buildingTitles[3] = {
                "Castle",
                "Research",
                "Mine"
        };
        BuildingGUI *gui = nullptr;
        SDL_Rect tdButton = {50, 50, 120, 40};
        Texture *tdButtonTexture = nullptr;
    public:
        // ctor
        using Base::Base;

        void Init() override;

        void Destroy() override;

        bool Input() override;

        bool HandleEvent(const Event &event) override;

        void Update(u64 frame, u64 totalMSec, f32 deltaT) override;

        void Render(u64 frame, u64 totalMSec, f32 deltaT) override;

        void RenderLayer(const Point windowSize, int index) const;

        void RenderBuildings(SDL_Renderer *renderer);

        static bool IsMouseOver(const SDL_Rect &rect, Point mouse);

        BuildingGUI *OpenBuildingGUI(const char *windowTitle);

        void HandleGUIEvent(const Event &event);

        void UpdateGUI();

        void RenderGUI();
    };
}
