#include <iostream>

#include "example_game.hpp"
#include "example_game.hpp"

namespace JanSordid::SDL_Example {

    Projectile::Projectile(Rect * position, Texture * texture, int damage, int velocity_X, int velocity_Y) {
        _isVisible = true;
        _position = position;
        _texture = texture;
        _damage = damage;
        _velocity_x = velocity_X;
        _velocity_y = velocity_Y;
    }

    Tower::Tower(Rect *placement, Texture *texture) {
        _position = placement;
        _texture = texture;
    }

    TowerArcher1::TowerArcher1(Rect *placement, Texture *texture) : Tower(placement, texture) {
        _attackDamage = 5;
        _attackRange = 2;
        _attackSpeed = 5;
    }
    void TowerArcher1::shoot(Rect * enemyPosition) {
        //ToDo
        //Projectile *projectile = new Projectile()
    }

    Enemy::Enemy(Rect *position, Texture *texture, int hp, int speed) {
        _isAlive = true;
        _position = position;
        _texture = texture;
        _hp = hp;
        _speed = speed;
        _textureSrcRect = new Rect(46*5,0,46,46);
    }

    void TdState::Init()
    {
        Base::Init();

        if( !enemyPathTile ) {
            enemyPathTile = IMG_LoadTexture( renderer(), BasePathGraphic "/Floor/enemy_path_tile.png" );
        }
        if( !grassTile ) {
            grassTile = IMG_LoadTexture( renderer(), BasePathGraphic "/Floor/grass_tile.png" );
        }
        if( !towerTexture ) {
            towerTexture = IMG_LoadTexture( renderer(), BasePathGraphic "/Archer-Tower/archer_tower_idle.png" );
        }
        if( !enemyTexture ) {
            enemyTexture = IMG_LoadTexture( renderer(), BasePathGraphic "/Enemies/slime_walk.png" );
        }

        if (tileMap[0][0] == nullptr) {
            for( int i = 0; i < gridHeight; i++ ) {
                for ( int j = 0; j < gridWidth; j++ ) {
                    Rect * temp = new Rect(
                        j * tileSize * scalingFactor(),
                        i * tileSize * scalingFactor(),
                        tileSize * scalingFactor(),
                        tileSize * scalingFactor()
                        );
                    tileMap[i][j] = temp;
                }
            }
        }

        // Spawning temporary Dummies

        Rect* tempRect = new Rect(0, 0, towerWidth, towerHeight);
        towerSrcRectMap[Tower::TowerType::Archer1] = tempRect;

        tempRect = new Rect(
            20 * tileSize * scalingFactor(),
            11 * tileSize * scalingFactor(),
            towerWidth / 2 * scalingFactor(),
            towerHeight / 2 * scalingFactor()
            );

        TowerArcher1 *tempTower = new TowerArcher1(tempRect, towerTexture);
        _game.data._towers.push_back(tempTower);

        tempRect = new Rect(gridWidth/2 * tileSize * scalingFactor(),gridHeight /2 * tileSize * scalingFactor(),46,46);
        Enemy *tempEnemy = new Enemy(tempRect,enemyTexture,10,5);
        _enemies.push_back(tempEnemy);
    }

    void TdState::Destroy()
    {
        // TODO

        Base::Destroy();
    }

    bool TdState::HandleEvent(const Event & event )
    {
        return true;
    }

    bool TdState::Input()
    {
        return false;
    }

    void TdState::Update(const u64 frame, const u64 totalMSec, const f32 deltaT )
    {
        std::cout << _game.data.gold << std::endl;
    }



    void TdState::Render(const u64 frame, u64 totalMSec, const f32 deltaT )
    {
        // Try the limits, moments before wraparound
        //totalMSec += 2147470000u + 2147480000u;
        Point windowSize;
        SDL_GetWindowSize( window(), &windowSize.x, &windowSize.y );


        for( int i = 0; i < gridHeight; i++ ) {
            for ( int j = 0; j < gridWidth; j++ ) {

                if( i == gridHeight / 2 || i == (gridHeight / 2) +1) {
                    SDL_RenderCopy(renderer(), enemyPathTile, EntireRect, tileMap[i][j] );
                }
                else {
                    SDL_RenderCopy(renderer(), grassTile, EntireRect, tileMap[i][j] );
                }
            }
        }

        for (const auto& element: _game.data._towers) {
            SDL_RenderCopy(renderer(), element->_texture,towerSrcRectMap[element->type],element->_position );
        }
        for (const auto& element: _enemies) {
            SDL_RenderCopy(renderer(), element->_texture,element->_textureSrcRect,element->_position );
        }
    }
} // namespace
