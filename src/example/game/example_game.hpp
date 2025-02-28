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

#pragma region IngameObjects
#pragma region Enemies

    class Enemy {
    public:
        enum class EnemyType {
            Slime
        };

        int _maxHp;
        int _hp;
        float _maxSpeed;
        float _speed;
        bool _isAlive;
        EnemyType _type;

        Rect *_position = nullptr;
        Rect *_textureSrcRect = nullptr;
        Texture *_texture = nullptr;
        std::vector<FPoint> _path;
        int _currentPath = 0;

        Enemy(Rect *position, Texture *texture, const std::vector<FPoint> &path, int hp, int speed, EnemyType type = EnemyType::Slime);

        void move(f32 deltaT, f32 scalingFactor);

        bool takeDamage(int damage);
    };

    class WaveSystem {
        public:
        std::vector<FPoint> _path;
        std::unordered_map<Enemy::EnemyType,Texture*> _enemyTextures;
        std::vector<std::vector<std::pair<Enemy::EnemyType,int>>> _waves;
        std::vector<Enemy*> _enemies;
        std::vector<Enemy*> _deadEnemies;
        FPoint _mapStart;
        int _cooldown = 0;
        int _currentEnemy = 0;
        int _currentWave = 0;

        WaveSystem(const std::vector<FPoint> &path, FPoint mapStart, const std::unordered_map<Enemy::EnemyType,Texture*> &enemyTextures, const std::vector<std::vector<std::pair<Enemy::EnemyType,int>>>& waves);
        bool spawn(u64 totalMSec, int tileSize, f32 scalingFactor);
        bool wavesFinished();

    protected:

        void createEnemy(Enemy::EnemyType type, int tileSize, f32 scalingFactor);
        void resetEnemy(Enemy* enemy, int tileSize, f32 scalingFactor);
        bool enemiesAlive();
    };

#pragma endregion

#pragma region Status

    class Status {
    public:

        int _startTime;
        int _duration;
        Enemy *_target;
        bool _isActive = true;

        Status(int duration, Enemy *target, u64 totalMSec);

        virtual ~Status() = default;

        virtual void tick(u64 totalMSec) = 0;
    };

    class BurningStatus : public Status {
    public:
        int _damage;
        int _cooldown;

        BurningStatus(int damage, int duration, Enemy *target, u64 totalMSec);

        void tick(u64 totalMSec) override;
    };

    class SlowingStatus : public Status {
    public:
        float _slownessFactor;
        bool _isSlowed = false;

        SlowingStatus(float slownessFactor, int duration, Enemy *target, u64 totalMSec);

        void tick(u64 totalMSec) override;
    };

#pragma endregion

#pragma region Projectiles

    class Projectile {
    public:
        enum class ProjectileType {
            Burn, Slow, Splash
        };

        int _damage;
        bool _isVisible;
        FPoint _direction{};
        Enemy *_target;
        int _homingCounter = 100;
        int _speed = 200;
        std::unordered_set<ProjectileType> _type;


        Projectile(Rect *position, Texture *texture, int damage, Enemy *target);

        Rect *_position = nullptr;
        Texture *_texture = nullptr;

        bool move(f32 deltaT, f32 scalingFactor);

    protected:
        void updateDirection();
    };

    class BurningProjectile : public Projectile {
    public:
        int _burnDamage;
        int _burnDuration;

        BurningProjectile(Rect *position, Texture *texture, int damage, int burnDamage, int burnDuration,
                          Enemy *target);

        Status *applyEffect(u64 totalMSec);
    };

    class SlowingProjectile : public Projectile {
    public:
        float _slowFactor;
        int _slowDuration;

        SlowingProjectile(Rect *position, Texture *texture, int damage, float slowFactor, int slowDuration,
                          Enemy *target);

        Status *applyEffect(u64 totalMSec);
    };

    class SplashProjectile : public Projectile {
    public:
        int _splashRadius;
        int _splashDamage;

        SplashProjectile(Rect *position, Texture *texture, int damage, int splashDamage, int splashRadius,
                         Enemy *target);
    };

    class BurningSplashProjectile : public SplashProjectile {
    public:
        int _burnDamage;
        int _burnDuration;

        BurningSplashProjectile(Rect *position, Texture *texture, int damage, int burnDamage, int burnDuration,
                                int splashDamage, int splashRadius, Enemy *target);

        Status *applyEffect(Enemy *target, u64 totalMSec);
    };

    class SlowingSplashProjectile : public SplashProjectile {
    public:
        float _slowFactor;
        int _slowDuration;

        SlowingSplashProjectile(Rect *position, Texture *texture, int damage, float slowFacotr, int slowDuration,
                                int splashDamage, int splashRadius, Enemy *target);

        Status *applyEffect(Enemy *target, u64 totalMSec);
    };

#pragma endregion

#pragma region Towers

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
        Texture *_projectileTexture = nullptr;
        std::vector<Rect *> _towerIconPosition = {};
        std::vector<Rect *> _towerIconSrc = {};
        std::vector<Texture *> _towerIconTextures = {};
        bool _clicked = false;
        static int _attackDamage;
        static int _attackSpeed;
        int _attackRange = 1;
        int _cooldown = 0;
        static int _price;

        Tower(Rect *placement, Texture *texture, Texture *projectileTexture);

        virtual ~Tower() = default;

        virtual Projectile *shoot(Enemy *target, u64 totalMSec) = 0;

        virtual int getAttackSpeed() = 0;

        virtual int getAttackRange() = 0;

        virtual int getPrice() = 0;


        int sellTower();

    protected:
        bool checkCooldown(u64 totalMSec);

    };

    class Archer1 : public Tower {
    public:
        static int _attackDamage;
        static int _attackSpeed;
        static int _attackRange;
        static int _price;

        Archer1(Rect *placement, Texture *texture, Texture *projectileTexture, const Vector<Rect *> &towerIconSrc,
                const Vector<Texture *> &towerIconTextures, f32 scalingFactor);

        Projectile *shoot(Enemy *target, u64 totalMSec) override;

        int getAttackSpeed() override;

        int getAttackRange() override;

        int getPrice() override;
    };

    class Archer2_P1 : public Tower {
    public:
        static int _attackDamage;
        static int _attackSpeed;
        static int _attackRange;
        static int _price;

        Archer2_P1(Rect *placement, Texture *texture, Texture *projectileTexture, const Vector<Rect *> &towerIconSrc,
                   const Vector<Texture *> &towerIconTextures, f32 scalingFactor);

        Projectile *shoot(Enemy *target, u64 totalMSec) override;

        int getAttackSpeed() override;

        int getAttackRange() override;

        int getPrice() override;
    };

    class Archer2_P2 : public Tower {
    public:
        static int _attackDamage;
        static int _attackSpeed;
        static int _attackRange;
        static int _price;

        Archer2_P2(Rect *placement, Texture *texture, Texture *projectileTexture, const Vector<Rect *> &towerIconSrc,
                   const Vector<Texture *> &towerIconTextures, f32 scalingFactor);

        Projectile *shoot(Enemy *target, u64 totalMSec) override;

        int getAttackSpeed() override;

        int getAttackRange() override;

        int getPrice() override;
    };

    class Archer3_P1 : public Tower {
    public:
        static int _attackDamage;
        static int _attackSpeed;
        static int _attackRange;
        static int _price;

        Archer3_P1(Rect *placement, Texture *texture, Texture *projectileTexture, const Vector<Rect *> &towerIconSrc,
                   const Vector<Texture *> &towerIconTextures, f32 scalingFactor);

        Projectile *shoot(Enemy *target, u64 totalMSec) override;

        int getAttackSpeed() override;

        int getAttackRange() override;

        int getPrice() override;
    };

    class Archer3_P2 : public Tower {
    public:
        static int _attackDamage;
        static int _attackSpeed;
        static int _attackRange;
        static int _price;

        Archer3_P2(Rect *placement, Texture *texture, Texture *projectileTexture, const Vector<Rect *> &towerIconSrc,
                   const Vector<Texture *> &towerIconTextures, f32 scalingFactor);

        Projectile *shoot(Enemy *target, u64 totalMSec) override;

        int getAttackSpeed() override;

        int getAttackRange() override;

        int getPrice() override;
    };

    class Mage1 : public Tower {
    public:
        static int _attackDamage;
        static int _attackSpeed;
        static int _attackRange;
        static int _price;

        Mage1(Rect *placement, Texture *texture, Texture *projectileTexture, const Vector<Rect *> &towerIconSrc,
              const Vector<Texture *> &towerIconTextures, f32 scalingFactor);

        Projectile *shoot(Enemy *target, u64 totalMSec) override;

        int getAttackSpeed() override;

        int getAttackRange() override;

        int getPrice() override;
    };

    class Mage2_P1 : public Tower {
    public:
        static int _attackDamage;
        static int _attackSpeed;
        static int _attackRange;
        static int _price;
        static int _burnDamage;
        static int _burnDuration;

        Mage2_P1(Rect *placement, Texture *texture, Texture *projectileTexture, const Vector<Rect *> &towerIconSrc,
                 const Vector<Texture *> &towerIconTextures, f32 scalingFactor);

        Projectile *shoot(Enemy *target, u64 totalMSec) override;

        int getAttackSpeed() override;

        int getAttackRange() override;

        int getPrice() override;
    };

    class Mage2_P2 : public Tower {
    public:
        static int _attackDamage;
        static int _attackSpeed;
        static int _attackRange;
        static int _price;
        static float _slowFactor;
        static int _slowDuration;

        Mage2_P2(Rect *placement, Texture *texture, Texture *projectileTexture, const Vector<Rect *> &towerIconSrc,
                 const Vector<Texture *> &towerIconTextures, f32 scalingFactor);

        Projectile *shoot(Enemy *target, u64 totalMSec) override;

        int getAttackSpeed() override;

        int getAttackRange() override;

        int getPrice() override;
    };

    class Mage3_P1 : public Tower {
    public:
        static int _attackDamage;
        static int _attackSpeed;
        static int _attackRange;
        static int _price;
        static int _burnDamage;
        static int _burnDuration;
        static int _splashDamage;
        static int _splashRadius;

        Mage3_P1(Rect *placement, Texture *texture, Texture *projectileTexture, const Vector<Rect *> &towerIconSrc,
                 const Vector<Texture *> &towerIconTextures, f32 scalingFactor);

        Projectile *shoot(Enemy *target, u64 totalMSec) override;

        int getAttackSpeed() override;

        int getAttackRange() override;

        int getPrice() override;
    };

    class Mage3_P2 : public Tower {
    public:
        static int _attackDamage;
        static int _attackSpeed;
        static int _attackRange;
        static int _price;
        static float _slowFactor;
        static int _slowDuration;

        Mage3_P2(Rect *placement, Texture *texture, Texture *projectileTexture, const Vector<Rect *> &towerIconSrc,
                 const Vector<Texture *> &towerIconTextures, f32 scalingFactor);

        Projectile *shoot(Enemy *target, u64 totalMSec) override;

        int getAttackSpeed() override;

        int getAttackRange() override;

        int getPrice() override;
    };

    class Catapult1 : public Tower {
    public:
        static int _attackDamage;
        static int _attackSpeed;
        static int _attackRange;
        static int _price;
        static int _splashDamage;
        static int _splashRadius;

        Catapult1(Rect *placement, Texture *texture, Texture *projectileTexture, const Vector<Rect *> &towerIconSrc,
                  const Vector<Texture *> &towerIconTextures, f32 scalingFactor);

        Projectile *shoot(Enemy *target, u64 totalMSec) override;

        int getAttackSpeed() override;

        int getAttackRange() override;

        int getPrice() override;
    };

    class Catapult2_P1 : public Tower {
    public:
        static int _attackDamage;
        static int _attackSpeed;
        static int _attackRange;
        static int _price;
        static int _splashDamage;
        static int _splashRadius;

        Catapult2_P1(Rect *placement, Texture *texture, Texture *projectileTexture, const Vector<Rect *> &towerIconSrc,
                     const Vector<Texture *> &towerIconTextures, f32 scalingFactor);

        Projectile *shoot(Enemy *target, u64 totalMSec) override;

        int getAttackSpeed() override;

        int getAttackRange() override;

        int getPrice() override;
    };

    class Catapult2_P2 : public Tower {
    public:
        static int _attackDamage;
        static int _attackSpeed;
        static int _attackRange;
        static int _price;
        Enemy *_dummyEnemy;

        Catapult2_P2(Rect *placement, Texture *texture, Texture *projectileTexture, const Vector<Rect *> &towerIconSrc,
                     const Vector<Texture *> &towerIconTextures, f32 scalingFactor);

        Projectile *shoot(Enemy *target, u64 totalMSec) override;

        int getAttackSpeed() override;

        int getAttackRange() override;

        int getPrice() override;
    };

    class Catapult3_P1 : public Tower {
    public:
        static int _attackDamage;
        static int _attackSpeed;
        static int _attackRange;
        static int _price;
        static int _splashDamage;
        static int _splashRadius;

        Catapult3_P1(Rect *placement, Texture *texture, Texture *projectileTexture, const Vector<Rect *> &towerIconSrc,
                     const Vector<Texture *> &towerIconTextures, f32 scalingFactor);

        Projectile *shoot(Enemy *target, u64 totalMSec) override;

        int getAttackSpeed() override;

        int getAttackRange() override;

        int getPrice() override;
    };

    class Catapult3_P2 : public Tower {
    public:
        static int _attackDamage;
        static int _attackSpeed;
        static int _attackRange;
        static int _price;
        static int _burnDamage;
        static int _burnDuration;
        Enemy *_dummyEnemy;

        Catapult3_P2(Rect *placement, Texture *texture, Texture *projectileTexture, const Vector<Rect *> &towerIconSrc,
                     const Vector<Texture *> &towerIconTextures, f32 scalingFactor);

        Projectile *shoot(Enemy *target, u64 totalMSec) override;

        int getAttackSpeed() override;

        int getAttackRange() override;

        int getPrice() override;
    };

#pragma endregion

    class TowerSlot {
    public:
        Rect *_position;
        Texture *_texture;
        Rect *_textureSrcRect;
        Rect *_towerIconPosition[3]{};
        Rect *_towerIconSrc[3]{};
        Texture *_towerIconTextures[3]{};
        bool _clicked = false;
        bool _used = false;

        TowerSlot(Rect *position, Texture *texture, Rect *towerIconSrc[3], Texture *towerIconTextures[3],
                  f32 scalingFactor);

        Rect *placeTower(f32 scalingFactor);
    };

#pragma endregion
    struct GameData {
        int gold = 10000;

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
        Texture *goldDisplayTexture = nullptr;
        Texture *enemyPathTile = nullptr;
        Texture *grassTile = nullptr;
        Texture *towerSlotTexture = nullptr;
        Texture *archerTowerTexture = nullptr;
        Texture *archerTower_2P1_Texture = nullptr;
        Texture *archerTower_2P2_Texture = nullptr;
        Texture *archerTower_3P1_Texture = nullptr;
        Texture *archerTower_3P2_Texture = nullptr;
        Texture *archerTowerArrowTexture = nullptr;
        Texture *mageTowerTexture = nullptr;
        Texture *mageTower_2P1_Texture = nullptr;
        Texture *mageTower_2P2_Texture = nullptr;
        Texture *mageTower_3P1_Texture = nullptr;
        Texture *mageTower_3P2_Texture = nullptr;
        Texture *mageTowerOrbTexture = nullptr;
        Texture *catapultTowerTexture = nullptr;
        Texture *catapultTower_2P1_Texture = nullptr;
        Texture *catapultTower_2P2_Texture = nullptr;
        Texture *catapultTower_3P1_Texture = nullptr;
        Texture *catapultTower_3P2_Texture = nullptr;
        Texture *catapultTowerStoneTexture = nullptr;
        Texture *sellIconTexture = nullptr;
        Texture *enemyTexture = nullptr;
        Texture *waveDisplayTexture = nullptr;
        Texture *lifesDisplayTexture = nullptr;

        Music *_music = nullptr;

        static constexpr int gridWidth = 40;
        static constexpr int gridHeight = 22;
        static constexpr int tileSize = 16;
        static constexpr int towerWidth = 70;
        static constexpr int towerHeight = 130;
        int respawnCD = 0;

        Rect *tileMap[gridHeight][gridWidth] = {nullptr};
        std::vector<std::vector<char>> levelData;
        Vector<FPoint> _mapPath;
        std::pair<int, int> _mapPathStart;
        std::pair<int, int> _mapPathEnd;

        std::unordered_map<Tower::TowerType, Rect *> towerSrcRectMap;
        std::unordered_map<Texture *, Rect *> projectileSrcRectMap;
        std::unordered_map<Enemy::EnemyType, Texture*> enemyTextureMap;
        std::unordered_map<Tower::TowerType, Texture *> projectileTextureMap;

        WaveSystem *_waveSystem;
        std::vector<TowerSlot *> _towerSlots;
        std::vector<Projectile *> _projectiles;
        std::vector<Status *> _statuses;

        int lifes = 10;

        void createTower(Tower::TowerType towerType, Rect *towerPosition);

    public:
        // ctor
        using Base::Base;

        void Init() override;

        void Enter(bool isStacking) override;

        void Exit(bool isStackedUpon) override;

        void Destroy() override;

        bool Input() override;

        bool HandleEvent(const Event &event) override;

        void Update(u64 frame, u64 totalMSec, f32 deltaT) override;

        void Render(u64 frame, u64 totalMSec, f32 deltaT) override;
    };

    class OverworldState : public MyGameState {
        using Base = MyGameState;

    protected:
        Texture *goldDisplayTexture = nullptr;
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
