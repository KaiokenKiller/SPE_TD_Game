#include <iostream>
#include <map>
#include <cmath>
#include "example_game.hpp"

namespace JanSordid::SDL_Example {
#pragma region Classes
#pragma region Towers

    Tower::Tower(Rect *placement, Texture *texture, Texture *projectileTexture) {
        _position = placement;
        _texture = texture;
        _projectileTexture = projectileTexture;
    }

    int Tower::_attackDamage = 0;
    int Tower::_attackSpeed = 0;
    int Tower::_price = 0;


    bool Tower::checkCooldown(u64 totalMSec) {
        if (_cooldown < totalMSec) {
            _cooldown = totalMSec + getAttackSpeed();
            return true;
        }
        return false;
    }


    int Tower::sellTower() {
        return getPrice() / 2;
    }

#pragma region Archers

    Archer1::Archer1(Rect *placement, Texture *texture, Texture *projectileTexture, const Vector<Rect *> &towerIconSrc,
                     const Vector<Texture *> &towerIconTextures, f32 scalingFactor) : Tower(
            placement, texture, projectileTexture) {
        _towerIconSrc = towerIconSrc;
        _towerIconTextures = towerIconTextures;

        int iconWidth = 16 * scalingFactor;
        int iconHeight = 32 * scalingFactor;

        _towerIconPosition.push_back(new Rect(_position->x - iconWidth, _position->y, iconWidth, iconHeight));
        _towerIconPosition.push_back(new Rect(_position->x + _position->w, _position->y, iconWidth, iconHeight));
        _towerIconPosition.push_back(
                new Rect(_position->x + ((_position->w / 2) - (iconWidth / 2)), _position->y + (_position->h),
                         iconWidth, iconHeight));

        _type = TowerType::Archer1;
    }

    int Archer1::_attackDamage = 5;
    int Archer1::_attackRange = 75;
    int Archer1::_attackSpeed = 750;
    int Archer1::_price = 100;


    Projectile *Archer1::shoot(Enemy *target, u64 totalMSec) {
        if (checkCooldown(totalMSec)) {
            Rect *startPosition = new Rect(_position->x + (_position->w / 2), _position->y + (_position->h / 2), 3, 14);
            return new Projectile(startPosition, _projectileTexture, _attackDamage, target);
        }
        return nullptr;
    }

    int Archer1::getAttackSpeed() {
        return _attackSpeed;
    }

    int Archer1::getAttackRange() {
        return _attackRange;
    }


    int Archer1::getPrice() {
        return _price;
    }

    Archer2_P1::Archer2_P1(Rect *placement, Texture *texture, Texture *projectileTexture,
                           const Vector<Rect *> &towerIconSrc, const Vector<Texture *> &towerIconTextures,
                           f32 scalingFactor) : Tower(
            placement, texture, projectileTexture) {
        _towerIconSrc = towerIconSrc;
        _towerIconTextures = towerIconTextures;

        int iconWidth = 16 * scalingFactor;
        int iconHeight = 32 * scalingFactor;

        _towerIconPosition.push_back(
                new Rect(_position->x + ((_position->w / 2) - (iconWidth / 2)), _position->y - iconHeight / 2,
                         iconWidth,
                         iconHeight));
        _towerIconPosition.push_back(
                new Rect(_position->x + ((_position->w / 2) - (iconWidth / 2)), _position->y + (_position->h),
                         iconWidth, iconHeight));

        _type = TowerType::Archer2_P1;
    }

    int Archer2_P1::_attackDamage = 5;
    int Archer2_P1::_attackRange = 75;
    int Archer2_P1::_attackSpeed = 500;
    int Archer2_P1::_price = 150;


    Projectile *Archer2_P1::shoot(Enemy *target, u64 totalMSec) {
        if (checkCooldown(totalMSec)) {
            Rect *startPosition = new Rect(_position->x + (_position->w / 2), _position->y + (_position->h / 2), 3, 14);
            return new Projectile(startPosition, _projectileTexture, _attackDamage, target);
        }
        return nullptr;
    }

    int Archer2_P1::getAttackSpeed() {
        return _attackSpeed;
    }

    int Archer2_P1::getAttackRange() {
        return _attackRange;
    }

    int Archer2_P1::getPrice() {
        return _price;
    }


    Archer2_P2::Archer2_P2(Rect *placement, Texture *texture, Texture *projectileTexture,
                           const Vector<Rect *> &towerIconSrc, const Vector<Texture *> &towerIconTextures,
                           f32 scalingFactor) : Tower(
            placement, texture, projectileTexture) {
        _towerIconSrc = towerIconSrc;
        _towerIconTextures = towerIconTextures;

        int iconWidth = 16 * scalingFactor;
        int iconHeight = 32 * scalingFactor;

        _towerIconPosition.push_back(
                new Rect(_position->x + ((_position->w / 2) - (iconWidth / 2)), _position->y - iconHeight / 2,
                         iconWidth,
                         iconHeight));
        _towerIconPosition.push_back(
                new Rect(_position->x + ((_position->w / 2) - (iconWidth / 2)), _position->y + (_position->h),
                         iconWidth, iconHeight));

        _type = TowerType::Archer2_P2;
    }

    int Archer2_P2::_attackDamage = 10;
    int Archer2_P2::_attackRange = 75;
    int Archer2_P2::_attackSpeed = 1000;
    int Archer2_P2::_price = 150;


    Projectile *Archer2_P2::shoot(Enemy *target, u64 totalMSec) {
        if (checkCooldown(totalMSec)) {
            Rect *startPosition = new Rect(_position->x + (_position->w / 2), _position->y + (_position->h / 2), 3, 14);
            return new Projectile(startPosition, _projectileTexture, _attackDamage, target);
        }
        return nullptr;
    }

    int Archer2_P2::getAttackSpeed() {
        return _attackSpeed;
    }

    int Archer2_P2::getAttackRange() {
        return _attackRange;
    }

    int Archer2_P2::getPrice() {
        return _price;
    }

    Archer3_P1::Archer3_P1(Rect *placement, Texture *texture, Texture *projectileTexture,
                           const Vector<Rect *> &towerIconSrc, const Vector<Texture *> &towerIconTextures,
                           f32 scalingFactor) : Tower(
            placement, texture, projectileTexture) {
        _towerIconSrc = towerIconSrc;
        _towerIconTextures = towerIconTextures;

        int iconWidth = 16 * scalingFactor;
        int iconHeight = 32 * scalingFactor;

        _towerIconPosition.push_back(
                new Rect(_position->x + ((_position->w / 2) - (iconWidth / 2)), _position->y + (_position->h),
                         iconWidth, iconHeight));

        _type = TowerType::Archer3_P1;
    }

    int Archer3_P1::_attackDamage = 5;
    int Archer3_P1::_attackRange = 75;
    int Archer3_P1::_attackSpeed = 200;
    int Archer3_P1::_price = 200;


    Projectile *Archer3_P1::shoot(Enemy *target, u64 totalMSec) {
        if (checkCooldown(totalMSec)) {
            Rect *startPosition = new Rect(_position->x + (_position->w / 2), _position->y + (_position->h / 2), 3, 14);
            return new Projectile(startPosition, _projectileTexture, _attackDamage, target);
        }
        return nullptr;
    }

    int Archer3_P1::getAttackSpeed() {
        return _attackSpeed;
    }

    int Archer3_P1::getAttackRange() {
        return _attackRange;
    }

    int Archer3_P1::getPrice() {
        return _price;
    }

    Archer3_P2::Archer3_P2(Rect *placement, Texture *texture, Texture *projectileTexture,
                           const Vector<Rect *> &towerIconSrc, const Vector<Texture *> &towerIconTextures,
                           f32 scalingFactor) : Tower(
            placement, texture, projectileTexture) {
        _towerIconSrc = towerIconSrc;
        _towerIconTextures = towerIconTextures;

        int iconWidth = 16 * scalingFactor;
        int iconHeight = 32 * scalingFactor;

        _towerIconPosition.push_back(
                new Rect(_position->x + ((_position->w / 2) - (iconWidth / 2)), _position->y + (_position->h),
                         iconWidth, iconHeight));

        _type = TowerType::Archer3_P2;
    }

    int Archer3_P2::_attackDamage = 25;
    int Archer3_P2::_attackRange = 150;
    int Archer3_P2::_attackSpeed = 1500;
    int Archer3_P2::_price = 200;


    Projectile *Archer3_P2::shoot(Enemy *target, u64 totalMSec) {
        if (checkCooldown(totalMSec)) {
            Rect *startPosition = new Rect(_position->x + (_position->w / 2), _position->y + (_position->h / 2), 3, 14);
            return new Projectile(startPosition, _projectileTexture, _attackDamage, target);
        }
        return nullptr;
    }

    int Archer3_P2::getAttackSpeed() {
        return _attackSpeed;
    }

    int Archer3_P2::getAttackRange() {
        return _attackRange;
    }

    int Archer3_P2::getPrice() {
        return _price;
    }

#pragma endregion

#pragma region Mages

    Mage1::Mage1(Rect *placement, Texture *texture, Texture *projectileTexture, const Vector<Rect *> &towerIconSrc,
                 const Vector<Texture *> &towerIconTextures, f32 scalingFactor) : Tower(
            placement, texture, projectileTexture) {
        _towerIconSrc = towerIconSrc;
        _towerIconTextures = towerIconTextures;

        int iconWidth = 16 * scalingFactor;
        int iconHeight = 32 * scalingFactor;

        _towerIconPosition.push_back(new Rect(_position->x - iconWidth, _position->y, iconWidth, iconHeight));
        _towerIconPosition.push_back(new Rect(_position->x + _position->w, _position->y, iconWidth, iconHeight));
        _towerIconPosition.push_back(
                new Rect(_position->x + ((_position->w / 2) - (iconWidth / 2)), _position->y + (_position->h),
                         iconWidth, iconHeight));

        _type = TowerType::Mage1;
    }

    int Mage1::getAttackSpeed() {
        return _attackSpeed;
    }

    int Mage1::getAttackRange() {
        return _attackRange;
    }

    int Mage1::getPrice() {
        return _price;
    }

    int Mage1::_attackDamage = 10;
    int Mage1::_attackRange = 75;
    int Mage1::_attackSpeed = 1000;
    int Mage1::_price = 150;

    Projectile *Mage1::shoot(Enemy *target, u64 totalMSec) {
        if (checkCooldown(totalMSec)) {
            Rect *startPosition = new Rect(_position->x + (_position->w / 2), _position->y + (_position->h / 2), 32,
                                           32);
            return new Projectile(startPosition, _projectileTexture, _attackDamage, target);
        }
        return nullptr;
    }

    Mage2_P1::Mage2_P1(Rect *placement, Texture *texture, Texture *projectileTexture,
                       const Vector<Rect *> &towerIconSrc, const Vector<Texture *> &towerIconTextures,
                       f32 scalingFactor) : Tower(
            placement, texture, projectileTexture) {
        _towerIconSrc = towerIconSrc;
        _towerIconTextures = towerIconTextures;

        int iconWidth = 16 * scalingFactor;
        int iconHeight = 32 * scalingFactor;

        _towerIconPosition.push_back(
                new Rect(_position->x + ((_position->w / 2) - (iconWidth / 2)), _position->y - iconHeight / 2,
                         iconWidth,
                         iconHeight));
        _towerIconPosition.push_back(
                new Rect(_position->x + ((_position->w / 2) - (iconWidth / 2)), _position->y + (_position->h),
                         iconWidth, iconHeight));

        _type = TowerType::Mage2_P1;
    }

    int Mage2_P1::getAttackSpeed() {
        return _attackSpeed;
    }

    int Mage2_P1::getAttackRange() {
        return _attackRange;
    }

    int Mage2_P1::getPrice() {
        return _price;
    }

    int Mage2_P1::_attackDamage = 10;
    int Mage2_P1::_attackRange = 75;
    int Mage2_P1::_attackSpeed = 1000;
    int Mage2_P1::_price = 200;
    int Mage2_P1::_burnDamage = 1;
    int Mage2_P1::_burnDuration = 2500;

    Projectile *Mage2_P1::shoot(Enemy *target, u64 totalMSec) {
        if (checkCooldown(totalMSec)) {
            Rect *startPosition = new Rect(_position->x + (_position->w / 2), _position->y + (_position->h / 2), 32,
                                           32);
            return new BurningProjectile(startPosition, _projectileTexture, _attackDamage, _burnDamage, _burnDuration,
                                         target);
        }
        return nullptr;
    }

    Mage2_P2::Mage2_P2(Rect *placement, Texture *texture, Texture *projectileTexture,
                       const Vector<Rect *> &towerIconSrc, const Vector<Texture *> &towerIconTextures,
                       f32 scalingFactor) : Tower(
            placement, texture, projectileTexture) {
        _towerIconSrc = towerIconSrc;
        _towerIconTextures = towerIconTextures;

        int iconWidth = 16 * scalingFactor;
        int iconHeight = 32 * scalingFactor;

        _towerIconPosition.push_back(
                new Rect(_position->x + ((_position->w / 2) - (iconWidth / 2)), _position->y - iconHeight / 2,
                         iconWidth,
                         iconHeight));
        _towerIconPosition.push_back(
                new Rect(_position->x + ((_position->w / 2) - (iconWidth / 2)), _position->y + (_position->h),
                         iconWidth, iconHeight));

        _type = TowerType::Mage2_P2;
    }

    int Mage2_P2::getAttackSpeed() {
        return _attackSpeed;
    }

    int Mage2_P2::getAttackRange() {
        return _attackRange;
    }

    int Mage2_P2::getPrice() {
        return _price;
    }

    int Mage2_P2::_attackDamage = 5;
    int Mage2_P2::_attackRange = 75;
    int Mage2_P2::_attackSpeed = 750;
    int Mage2_P2::_price = 200;
    float Mage2_P2::_slowFactor = 0.75;
    int Mage2_P2::_slowDuration = 2500;


    Projectile *Mage2_P2::shoot(Enemy *target, u64 totalMSec) {
        if (checkCooldown(totalMSec)) {
            Rect *startPosition = new Rect(_position->x + (_position->w / 2), _position->y + (_position->h / 2), 32,
                                           32);
            return new Projectile(startPosition, _projectileTexture, _attackDamage, target);
        }
        return nullptr;
    }

    Mage3_P1::Mage3_P1(Rect *placement, Texture *texture, Texture *projectileTexture,
                       const Vector<Rect *> &towerIconSrc, const Vector<Texture *> &towerIconTextures,
                       f32 scalingFactor) : Tower(
            placement, texture, projectileTexture) {
        _towerIconSrc = towerIconSrc;
        _towerIconTextures = towerIconTextures;

        int iconWidth = 16 * scalingFactor;
        int iconHeight = 32 * scalingFactor;

        _towerIconPosition.push_back(
                new Rect(_position->x + ((_position->w / 2) - (iconWidth / 2)), _position->y + (_position->h),
                         iconWidth, iconHeight));

        _type = TowerType::Mage3_P1;
    }

    int Mage3_P1::getAttackSpeed() {
        return _attackSpeed;
    }

    int Mage3_P1::getAttackRange() {
        return _attackRange;
    }

    int Mage3_P1::getPrice() {
        return _price;
    }

    int Mage3_P1::_attackDamage = 10;
    int Mage3_P1::_attackRange = 150;
    int Mage3_P1::_attackSpeed = 1000;
    int Mage3_P1::_price = 250;
    int Mage3_P1::_burnDamage = 2;
    int Mage3_P1::_burnDuration = 5000;
    int Mage3_P1::_splashDamage = 5;
    int Mage3_P1::_splashRadius = 50;

    Projectile *Mage3_P1::shoot(Enemy *target, u64 totalMSec) {
        if (checkCooldown(totalMSec)) {
            Rect *startPosition = new Rect(_position->x + (_position->w / 2), _position->y + (_position->h / 2), 32,
                                           32);
            return new BurningSplashProjectile(startPosition, _projectileTexture, _attackDamage, _burnDamage,
                                               _burnDuration, _splashDamage, _splashRadius, target);
        }
        return nullptr;
    }

    Mage3_P2::Mage3_P2(Rect *placement, Texture *texture, Texture *projectileTexture,
                       const Vector<Rect *> &towerIconSrc, const Vector<Texture *> &towerIconTextures,
                       f32 scalingFactor) : Tower(
            placement, texture, projectileTexture) {
        _towerIconSrc = towerIconSrc;
        _towerIconTextures = towerIconTextures;

        int iconWidth = 16 * scalingFactor;
        int iconHeight = 32 * scalingFactor;

        _towerIconPosition.push_back(
                new Rect(_position->x + ((_position->w / 2) - (iconWidth / 2)), _position->y + (_position->h),
                         iconWidth, iconHeight));

        _type = TowerType::Mage3_P2;
    }

    int Mage3_P2::getAttackSpeed() {
        return _attackSpeed;
    }

    int Mage3_P2::getAttackRange() {
        return _attackRange;
    }

    int Mage3_P2::getPrice() {
        return _price;
    }

    int Mage3_P2::_attackDamage = 3;
    int Mage3_P2::_attackRange = 75;
    int Mage3_P2::_attackSpeed = 250;
    int Mage3_P2::_price = 250;
    float Mage3_P2::_slowFactor = 0.5;
    int Mage3_P2::_slowDuration = 2500;
    int Mage3_P2::_splashRadius = 50;

    Projectile *Mage3_P2::shoot(Enemy *target, u64 totalMSec) {
        if (checkCooldown(totalMSec)) {
            Rect *startPosition = new Rect(_position->x + (_position->w / 2), _position->y + (_position->h / 2), 32,
                                           32);
            return new SlowingSplashProjectile(startPosition, _projectileTexture, _attackDamage, _slowFactor,
                                               _slowDuration, 0, _splashRadius, target);
        }
        return nullptr;
    }

#pragma endregion

#pragma region Catapults

    Catapult1::Catapult1(Rect *placement, Texture *texture, Texture *projectileTexture,
                         const Vector<Rect *> &towerIconSrc, const Vector<Texture *> &towerIconTextures,
                         f32 scalingFactor) : Tower(
            placement, texture, projectileTexture) {
        _towerIconSrc = towerIconSrc;
        _towerIconTextures = towerIconTextures;

        int iconWidth = 16 * scalingFactor;
        int iconHeight = 32 * scalingFactor;

        _towerIconPosition.push_back(new Rect(_position->x - iconWidth, _position->y, iconWidth, iconHeight));
        _towerIconPosition.push_back(new Rect(_position->x + _position->w, _position->y, iconWidth, iconHeight));
        _towerIconPosition.push_back(
                new Rect(_position->x + ((_position->w / 2) - (iconWidth / 2)), _position->y + (_position->h),
                         iconWidth, iconHeight));

        _type = TowerType::Catapult1;
    }

    int Catapult1::_attackDamage = 7;
    int Catapult1::_attackRange = 100;
    int Catapult1::_attackSpeed = 1500;
    int Catapult1::_price = 200;
    int Catapult1::_splashDamage = 5;
    int Catapult1::_splashRadius = 40;

    Projectile *Catapult1::shoot(Enemy *target, u64 totalMSec) {
        if (checkCooldown(totalMSec)) {
            Rect *startPosition = new Rect(_position->x + (_position->w / 2), _position->y + (_position->h / 2), 32,
                                           32);
            return new SplashProjectile(startPosition, _projectileTexture, _attackDamage, _splashDamage, _splashRadius,
                                        target);
        }
        return nullptr;
    }

    int Catapult1::getAttackSpeed() {
        return _attackSpeed;
    }

    int Catapult1::getAttackRange() {
        return _attackRange;
    }

    int Catapult1::getPrice() {
        return _price;
    }

    Catapult2_P1::Catapult2_P1(Rect *placement, Texture *texture, Texture *projectileTexture,
                               const Vector<Rect *> &towerIconSrc, const Vector<Texture *> &towerIconTextures,
                               f32 scalingFactor) : Tower(
            placement, texture, projectileTexture) {
        _towerIconSrc = towerIconSrc;
        _towerIconTextures = towerIconTextures;

        int iconWidth = 16 * scalingFactor;
        int iconHeight = 32 * scalingFactor;

        _towerIconPosition.push_back(
                new Rect(_position->x + ((_position->w / 2) - (iconWidth / 2)), _position->y - iconHeight / 2,
                         iconWidth,
                         iconHeight));
        _towerIconPosition.push_back(
                new Rect(_position->x + ((_position->w / 2) - (iconWidth / 2)), _position->y + (_position->h),
                         iconWidth, iconHeight));

        _type = TowerType::Catapult2_P1;
    }

    int Catapult2_P1::_attackDamage = 10;
    int Catapult2_P1::_attackRange = 150;
    int Catapult2_P1::_attackSpeed = 1500;
    int Catapult2_P1::_price = 250;
    int Catapult2_P1::_splashDamage = 5;
    int Catapult2_P1::_splashRadius = 50;

    Projectile *Catapult2_P1::shoot(Enemy *target, u64 totalMSec) {
        if (checkCooldown(totalMSec)) {
            Rect *startPosition = new Rect(_position->x + (_position->w / 2), _position->y + (_position->h / 2), 32,
                                           32);
            return new SplashProjectile(startPosition, _projectileTexture, _attackDamage, _splashDamage, _splashRadius,
                                        target);
        }
        return nullptr;
    }

    int Catapult2_P1::getAttackSpeed() {
        return _attackSpeed;
    }

    int Catapult2_P1::getAttackRange() {
        return _attackRange;
    }

    int Catapult2_P1::getPrice() {
        return _price;
    }

    Catapult2_P2::Catapult2_P2(Rect *placement, Texture *texture, Texture *projectileTexture,
                               const Vector<Rect *> &towerIconSrc, const Vector<Texture *> &towerIconTextures,
                               f32 scalingFactor) : Tower(
            placement, texture, projectileTexture) {
        _towerIconSrc = towerIconSrc;
        _towerIconTextures = towerIconTextures;

        int iconWidth = 16 * scalingFactor;
        int iconHeight = 32 * scalingFactor;

        _towerIconPosition.push_back(
                new Rect(_position->x + ((_position->w / 2) - (iconWidth / 2)), _position->y - iconHeight / 2,
                         iconWidth,
                         iconHeight));
        _towerIconPosition.push_back(
                new Rect(_position->x + ((_position->w / 2) - (iconWidth / 2)), _position->y + (_position->h),
                         iconWidth, iconHeight));

        _type = TowerType::Catapult2_P2;
        std::vector<FPoint> temp;
        _dummyEnemy = new Enemy(placement, nullptr, temp, 0, 0);
    }

    int Catapult2_P2::_attackDamage = 2;
    int Catapult2_P2::_attackRange = 30;
    int Catapult2_P2::_attackSpeed = 100;
    int Catapult2_P2::_price = 250;

    Projectile *Catapult2_P2::shoot(Enemy *target, u64 totalMSec) {
        if (checkCooldown(totalMSec)) {
            Rect *startPosition = new Rect(_position->x + (_position->w / 2), _position->y + (_position->h / 2), 32,
                                           32);
            return new SplashProjectile(startPosition, _projectileTexture, _attackDamage, _attackDamage, _attackRange,
                                        _dummyEnemy);
        }
        return nullptr;
    }

    int Catapult2_P2::getAttackSpeed() {
        return _attackSpeed;
    }

    int Catapult2_P2::getAttackRange() {
        return _attackRange;
    }

    int Catapult2_P2::getPrice() {
        return _price;
    }

    Catapult3_P1::Catapult3_P1(Rect *placement, Texture *texture, Texture *projectileTexture,
                               const Vector<Rect *> &towerIconSrc, const Vector<Texture *> &towerIconTextures,
                               f32 scalingFactor) : Tower(
            placement, texture, projectileTexture) {
        _towerIconSrc = towerIconSrc;
        _towerIconTextures = towerIconTextures;

        int iconWidth = 16 * scalingFactor;
        int iconHeight = 32 * scalingFactor;

        _towerIconPosition.push_back(
                new Rect(_position->x + ((_position->w / 2) - (iconWidth / 2)), _position->y + (_position->h),
                         iconWidth, iconHeight));

        _type = TowerType::Catapult3_P1;
    }

    int Catapult3_P1::_attackDamage = 15;
    int Catapult3_P1::_attackRange = 150;
    int Catapult3_P1::_attackSpeed = 1500;
    int Catapult3_P1::_price = 300;
    int Catapult3_P1::_splashDamage = 7;
    int Catapult3_P1::_splashRadius = 60;

    Projectile *Catapult3_P1::shoot(Enemy *target, u64 totalMSec) {
        if (checkCooldown(totalMSec)) {
            Rect *startPosition = new Rect(_position->x + (_position->w / 2), _position->y + (_position->h / 2), 32,
                                           32);
            return new SplashProjectile(startPosition, _projectileTexture, _attackDamage, _splashDamage, _splashRadius,
                                        target);
        }
        return nullptr;
    }

    int Catapult3_P1::getAttackSpeed() {
        return _attackSpeed;
    }

    int Catapult3_P1::getAttackRange() {
        return _attackRange;
    }

    int Catapult3_P1::getPrice() {
        return _price;
    }

    Catapult3_P2::Catapult3_P2(Rect *placement, Texture *texture, Texture *projectileTexture,
                               const Vector<Rect *> &towerIconSrc, const Vector<Texture *> &towerIconTextures,
                               f32 scalingFactor) : Tower(
            placement, texture, projectileTexture) {
        _towerIconSrc = towerIconSrc;
        _towerIconTextures = towerIconTextures;

        int iconWidth = 16 * scalingFactor;
        int iconHeight = 32 * scalingFactor;

        _towerIconPosition.push_back(
                new Rect(_position->x + ((_position->w / 2) - (iconWidth / 2)), _position->y + (_position->h),
                         iconWidth, iconHeight));

        _type = TowerType::Catapult3_P2;
        std::vector<FPoint> temp;
        _dummyEnemy = new Enemy(placement, nullptr, temp, 0, 0);
    }

    int Catapult3_P2::_attackDamage = 2;
    int Catapult3_P2::_attackRange = 50;
    int Catapult3_P2::_attackSpeed = 100;
    int Catapult3_P2::_price = 300;
    int Catapult3_P2::_burnDamage = 2;
    int Catapult3_P2::_burnDuration = 2500;

    Projectile *Catapult3_P2::shoot(Enemy *target, u64 totalMSec) {
        if (checkCooldown(totalMSec)) {
            Rect *startPosition = new Rect(_position->x + (_position->w / 2), _position->y + (_position->h / 2), 32,
                                           32);
            return new BurningSplashProjectile(startPosition, _projectileTexture, _attackDamage, _burnDamage,
                                               _burnDuration, _attackDamage, _attackRange, _dummyEnemy);
        }
        return nullptr;
    }

    int Catapult3_P2::getAttackSpeed() {
        return _attackSpeed;
    }

    int Catapult3_P2::getAttackRange() {
        return _attackRange;
    }

    int Catapult3_P2::getPrice() {
        return _price;
    }

#pragma endregion

    TowerSlot::TowerSlot(Rect *position, Texture *texture,
                         Rect **towerIconSrc, Texture **towerIconTextures, f32 scalingFactor) {
        _position = position;
        _texture = texture;
        _textureSrcRect = new Rect(0, 0, 62, 61);

        for (int i = 0; i < 3; ++i) {
            _towerIconSrc[i] = towerIconSrc[i];
            _towerIconTextures[i] = towerIconTextures[i];
        }
        int iconWidth = 32 * scalingFactor;
        int iconHeight = 64 * scalingFactor;
        _towerIconPosition[0] = new Rect(_position->x - iconWidth, _position->y - iconHeight, iconWidth, iconHeight);
        _towerIconPosition[1] = new Rect(_position->x + ((_position->w / 2) - (iconWidth / 2)),
                                         _position->y - (iconHeight + (8 * scalingFactor)), iconWidth, iconHeight);
        _towerIconPosition[2] = new Rect(_position->x + _position->w, _position->y - iconHeight, iconWidth, iconHeight);
    }

    Rect *TowerSlot::placeTower(f32 scalingFactor) {
        if (!_used) {
            _used = true;
            return new Rect(_position->x - ((4 / 2) * scalingFactor), _position->y - ((66 / 2) * scalingFactor),
                            ((70 / 2) * scalingFactor), ((130 / 2) * scalingFactor));
        }
        return nullptr;
    }

#pragma endregion

#pragma region Enemys

    Enemy::Enemy(Rect *position, Texture *texture, const Vector<FPoint> &path, int hp, int speed, EnemyType type) {
        _isAlive = true;
        _position = position;
        _texture = texture;
        _maxHp = hp;
        _hp = hp;
        _maxSpeed = speed;
        _speed = speed;
        _textureSrcRect = new Rect(46 * 5, 0, 46, 46);
        _path = path;
        _type = type;
    }

    bool Enemy::takeDamage(int damage) {
        _hp -= damage;
        if (_hp <= 0)
            _isAlive = false;
        return _isAlive;
    }

    bool Enemy::move(const f32 deltaT, f32 scalingFactor) {
        if (!_isAlive || _currentPath >= _path.size()) return false;

        int movement = static_cast<int>(deltaT * 100.0f * _speed * scalingFactor);

        // Sicherstellen, dass die Schleife nicht unendlich läuft
        while (movement > 0 && _currentPath < _path.size()) {
            FPoint &currentMove = _path[_currentPath];

            if (currentMove.x != 0) {
                int moveX = std::min(movement, static_cast<int>(std::abs(currentMove.x)));
                _position->x += (currentMove.x > 0) ? moveX : -moveX;
                currentMove.x += (currentMove.x > 0) ? -moveX : moveX;
                movement -= moveX;
            } else if (currentMove.y != 0) {
                int moveY = std::min(movement, static_cast<int>(std::abs(currentMove.y)));
                _position->y += (currentMove.y > 0) ? moveY : -moveY;
                currentMove.y += (currentMove.y > 0) ? -moveY : moveY;
                movement -= moveY;
            }

            // Wichtige Abfrage: Wenn die Bewegung abgeschlossen ist, gehe zum nächsten Punkt
            if (currentMove.x == 0 && currentMove.y == 0) {
                _currentPath++;
                if (_currentPath >= _path.size()) {
                    _isAlive = false; // Gegner hat Ziel erreicht
                    return true;
                }
            }
        }
        return false;
    }


    WaveSystem::WaveSystem(const std::vector<FPoint> &path, FPoint mapStart,
                           const std::unordered_map<Enemy::EnemyType, Texture *> &enemyTextures,
                           const std::vector<std::vector<std::pair<Enemy::EnemyType, int>>> &waves) {
        _path = path;
        _enemyTextures = enemyTextures;
        _waves = waves;
        _mapStart = mapStart;
    }

    bool WaveSystem::spawn(u64 totalMSec, int tileSize, f32 scalingFactor) {
        if (_currentWave < _waves.size()) {
            if (_cooldown > totalMSec) {
                return false;
            }
            if (_currentEnemy < _waves[_currentWave].size()) {
                bool enemyCreated = false;
                if (!_deadEnemies.empty()) {
                    for (auto enemy: _deadEnemies) {
                        if (enemy->_type == _waves[_currentWave][_currentEnemy].first) {
                            resetEnemy(enemy, tileSize, scalingFactor);
                            enemyCreated = true;
                            break;
                        }
                    }
                }

                if (!enemyCreated) {
                    createEnemy(_waves[_currentWave][_currentEnemy].first, tileSize, scalingFactor);
                }
                _cooldown = totalMSec + _waves[_currentWave][_currentEnemy].second;
                _currentEnemy++;
                return true;
            }
        }
        return false;
    }

    bool WaveSystem::wavesFinished() {
        if (_currentEnemy >= _waves[_currentWave].size()) {
            if (!enemiesAlive()) {
                if (_currentWave + 1 >= _waves.size()) {
                    return true;
                }
                _currentWave++;

                _currentEnemy = 0;
            }
        }
        return false;
    }

    void WaveSystem::createEnemy(Enemy::EnemyType type, int tileSize, f32 scalingFactor) {
        Enemy *enemy;
        switch (type) {
            case Enemy::EnemyType::Slime: {
                Rect *tempRect = new Rect(
                        _mapStart.x * tileSize * scalingFactor,
                        _mapStart.y * tileSize * scalingFactor,
                        46,
                        46
                );
                enemy = new Enemy(tempRect, _enemyTextures[Enemy::EnemyType::Slime], _path, 15, 1);
                break;
            }
            default: {
                Rect *tempRect = new Rect(
                        _mapStart.x * tileSize * scalingFactor,
                        _mapStart.y * tileSize * scalingFactor,
                        46 / 2 * scalingFactor,
                        46 / 2 * scalingFactor
                );
                enemy = new Enemy(tempRect, _enemyTextures[Enemy::EnemyType::Slime], _path, 15, 1);
            }
        }
        _enemies.push_back(enemy);
    }

    void WaveSystem::resetEnemy(Enemy *enemy, int tileSize, f32 scalingFactor) {
        switch (enemy->_type) {
            case Enemy::EnemyType::Slime: {
                enemy->_position->x = _mapStart.x * tileSize * scalingFactor;
                enemy->_position->y = _mapStart.y * tileSize * scalingFactor;
                enemy->_path = _path;
                enemy->_currentPath = 0;
                enemy->_isAlive = true;
                enemy->_hp = enemy->_maxHp;
                break;
            }
            default: {
                enemy->_position->x = _mapStart.x * tileSize * scalingFactor;
                enemy->_position->y = _mapStart.y * tileSize * scalingFactor;
                enemy->_path = _path;
                enemy->_currentPath = 0;
                enemy->_isAlive = true;
                enemy->_hp = enemy->_maxHp;
            }
        }
        _enemies.push_back(enemy);

        _deadEnemies.erase(
                std::remove_if(_deadEnemies.begin(), _deadEnemies.end(),
                               [](Enemy *enemy) {
                                   if (enemy->_isAlive) {// Speicher freigeben
                                       return true;  // Entfernen aus dem Vektor
                                   }
                                   return false;  // Behalten im Vektor
                               }),
                _deadEnemies.end());
    }

    bool WaveSystem::enemiesAlive() {
        for (auto enemy: _enemies) {
            if (enemy->_isAlive)
                return true;
        }
        return false;
    }


#pragma endregion

#pragma region Status

    Status::Status(int duration, Enemy *target, u64 totalMSec) {
        _duration = duration;
        _target = target;
        _startTime = totalMSec;
    }

    BurningStatus::BurningStatus(int burnDamage, int duration, Enemy *target, u64 totalMSec) : Status(duration, target,
                                                                                                      totalMSec) {
        _damage = burnDamage;
        _cooldown = totalMSec;
    }

    void BurningStatus::tick(u64 totalMSec) {
        if (_isActive) {
            if (totalMSec > _startTime + _duration) {
                _isActive = false;
                return;
            }

            int tickTime = 500;
            if (totalMSec > _cooldown + tickTime) {
                while (totalMSec > _cooldown + tickTime) {
                    _target->takeDamage(_damage);
                    _cooldown += tickTime;
                }
                _cooldown = totalMSec;
            }
        }
    }

    SlowingStatus::SlowingStatus(float slownessFactor, int duration, Enemy *target, u64 totalMSec) : Status(duration,
                                                                                                            target,
                                                                                                            totalMSec) {
        _slownessFactor = slownessFactor;
    }

    void SlowingStatus::tick(u64 totalMSec) {
        if (_isActive) {
            if (totalMSec > _startTime + _duration) {
                _isActive = false;
                _target->_speed = _target->_maxSpeed;
                return;
            }
            if (!_isSlowed) {
                if (_target->_speed > _target->_maxSpeed * _slownessFactor) {
                    _target->_speed = _target->_maxSpeed * _slownessFactor;
                }
                _isSlowed = true;
            }
        }
    }


#pragma endregion

#pragma region Projectiles

    Projectile::Projectile(Rect *position, Texture *texture, int damage, Enemy *target) {
        _isVisible = true;
        _position = position;
        _texture = texture;
        _damage = damage;
        _target = target;

        _direction = FPoint((_target->_position->x - _position->x), _target->_position->y - _position->y);
        if (float directionLength = sqrt((_direction.x * _direction.x) + (_direction.y * _direction.y));
                directionLength != 0) {
            _direction.x /= directionLength;
            _direction.x *= 2;
            _direction.y /= directionLength;
            _direction.y *= 2;
        }
    }

    void Projectile::updateDirection() {
        _direction.x = _target->_position->x - _position->x;
        _direction.y = _target->_position->y - _position->y;

        float directionLength = sqrt((_direction.x * _direction.x) + (_direction.y * _direction.y));
        if (directionLength != 0) {
            _direction.x /= directionLength;
            _direction.x *= 2;
            _direction.y /= directionLength;
            _direction.y *= 2;
        }
    }

    bool Projectile::move(const f32 deltaT, f32 scalingFactor) {
        if (_isVisible) {
            _position->x += _direction.x * deltaT * _speed * scalingFactor;
            _position->y += _direction.y * deltaT * _speed * scalingFactor;

            if (SDL_HasIntersection(_position, _target->_position)) {
                _target->takeDamage(_damage);
                _isVisible = false;
                return true;
            }
            _homingCounter -= deltaT * 1000;
            if (_homingCounter <= 0) {
                updateDirection();
            }
        }
        return false;
    }

    BurningProjectile::BurningProjectile(Rect *position, Texture *texture, int damage, int burnDamage, int burnDuration,
                                         Enemy *target) : Projectile(position, texture, damage, target) {
        _burnDamage = burnDamage;
        _burnDuration = burnDuration;
        _type.insert(ProjectileType::Burn);
    }

    Status *BurningProjectile::applyEffect(u64 totalMSec) {
        return new BurningStatus(_burnDamage, _burnDuration, _target, totalMSec);
    }

    SlowingProjectile::SlowingProjectile(Rect *position, Texture *texture, int damage, float slowFactor,
                                         int slowDuration, Enemy *target) : Projectile(position, texture, damage,
                                                                                       target) {
        _slowFactor = slowFactor;
        _slowDuration = slowDuration;
        _type.insert(ProjectileType::Slow);
    }

    Status *SlowingProjectile::applyEffect(u64 totalMSec) {
        return new SlowingStatus(_slowFactor, _slowDuration, _target, totalMSec);
    }

    SplashProjectile::SplashProjectile(Rect *position, Texture *texture, int damage, int splashDamage, int splashRadius,
                                       Enemy *target) : Projectile(position, texture, damage, target) {
        _splashDamage = splashDamage;
        _splashRadius = splashRadius;
        _type.insert(ProjectileType::Splash);
    }

    BurningSplashProjectile::BurningSplashProjectile(Rect *position, Texture *texture, int damage, int burnDamage,
                                                     int burnDuration, int splashDamage, int splashRadius,
                                                     Enemy *target) : SplashProjectile(position, texture, damage,
                                                                                       splashDamage, splashRadius,
                                                                                       target) {
        _burnDamage = burnDamage;
        _burnDuration = burnDuration;
        _type.insert(ProjectileType::Burn);
    }

    Status *BurningSplashProjectile::applyEffect(Enemy *target, u64 totalMSec) {
        return new BurningStatus(_burnDamage, _burnDuration, _target, totalMSec);
    }

    SlowingSplashProjectile::SlowingSplashProjectile(Rect *position, Texture *texture, int damage, float slowFacotr,
                                                     int slowDuration, int splashDamage, int splashRadius,
                                                     Enemy *target) : SplashProjectile(position, texture, damage,
                                                                                       splashDamage, splashRadius,
                                                                                       target) {
        _slowFactor = slowFacotr;
        _slowDuration = slowDuration;
        _type.insert(ProjectileType::Slow);
    }

    Status *SlowingSplashProjectile::applyEffect(Enemy *target, u64 totalMSec) {
        return new SlowingStatus(_slowFactor, _slowDuration, _target, totalMSec);
    }

#pragma endregion
#pragma endregion

    void TdState::createTower(Tower::TowerType towerType, Rect *towerPosition) {
        switch (towerType) {
            case Tower::TowerType::Archer1: {
                Vector<Rect *> towerIconSrc{towerSrcRectMap[Tower::TowerType::Archer2_P1],
                                            towerSrcRectMap[Tower::TowerType::Archer2_P2],
                                            towerSrcRectMap[Tower::TowerType::Archer1]};
                Vector<Texture *> towerIconTextures{archerTower_2P1_Texture, archerTower_2P2_Texture, sellIconTexture};
                auto *newTower = new Archer1(towerPosition, archerTowerTexture, archerTowerArrowTexture, towerIconSrc,
                                             towerIconTextures, scalingFactor());
                _game.data._towers.push_back(newTower);
                break;
            }
            case Tower::TowerType::Archer2_P1: {
                Vector<Rect *> towerIconSrc{towerSrcRectMap[Tower::TowerType::Archer3_P1],
                                            towerSrcRectMap[Tower::TowerType::Archer1]};
                Vector<Texture *> towerIconTextures{archerTower_3P1_Texture, sellIconTexture};
                auto *newTower = new Archer2_P1(towerPosition, archerTower_2P1_Texture, archerTowerArrowTexture,
                                                towerIconSrc, towerIconTextures, scalingFactor());
                _game.data._towers.push_back(newTower);
                break;
            }
            case Tower::TowerType::Archer2_P2: {
                Vector<Rect *> towerIconSrc{towerSrcRectMap[Tower::TowerType::Archer3_P2],
                                            towerSrcRectMap[Tower::TowerType::Archer1]};
                Vector<Texture *> towerIconTextures{archerTower_3P2_Texture, sellIconTexture};
                auto *newTower = new Archer2_P2(towerPosition, archerTower_2P2_Texture, archerTowerArrowTexture,
                                                towerIconSrc, towerIconTextures, scalingFactor());
                _game.data._towers.push_back(newTower);
                break;
            }
            case Tower::TowerType::Archer3_P1: {
                Vector<Rect *> towerIconSrc{towerSrcRectMap[Tower::TowerType::Archer1]};
                Vector<Texture *> towerIconTextures{sellIconTexture};
                auto *newTower = new Archer3_P1(towerPosition, archerTower_3P1_Texture, archerTowerArrowTexture,
                                                towerIconSrc, towerIconTextures, scalingFactor());
                _game.data._towers.push_back(newTower);
                break;
            }
            case Tower::TowerType::Archer3_P2: {
                Vector<Rect *> towerIconSrc{towerSrcRectMap[Tower::TowerType::Archer1]};
                Vector<Texture *> towerIconTextures{sellIconTexture};
                auto *newTower = new Archer3_P2(towerPosition, archerTower_3P2_Texture, archerTowerArrowTexture,
                                                towerIconSrc, towerIconTextures, scalingFactor());
                _game.data._towers.push_back(newTower);
                break;
            }
            case Tower::TowerType::Mage1: {
                Vector<Rect *> towerIconSrc{towerSrcRectMap[Tower::TowerType::Mage2_P1],
                                            towerSrcRectMap[Tower::TowerType::Mage2_P2],
                                            towerSrcRectMap[Tower::TowerType::Archer1]};
                Vector<Texture *> towerIconTextures{mageTower_2P1_Texture, mageTower_2P2_Texture, sellIconTexture};
                auto *newTower = new Mage1(towerPosition, mageTowerTexture, mageTowerOrbTexture, towerIconSrc,
                                           towerIconTextures, scalingFactor());
                _game.data._towers.push_back(newTower);
                break;
            }
            case Tower::TowerType::Mage2_P1: {
                Vector<Rect *> towerIconSrc{towerSrcRectMap[Tower::TowerType::Mage3_P1],
                                            towerSrcRectMap[Tower::TowerType::Archer1]};
                Vector<Texture *> towerIconTextures{mageTower_3P1_Texture, sellIconTexture};
                auto *newTower = new Mage2_P1(towerPosition, mageTower_2P1_Texture, mageTowerOrbTexture, towerIconSrc,
                                              towerIconTextures, scalingFactor());
                _game.data._towers.push_back(newTower);
                break;
            }
            case Tower::TowerType::Mage2_P2: {
                Vector<Rect *> towerIconSrc{towerSrcRectMap[Tower::TowerType::Mage3_P2],
                                            towerSrcRectMap[Tower::TowerType::Archer1]};
                Vector<Texture *> towerIconTextures{mageTower_3P2_Texture, sellIconTexture};
                auto *newTower = new Mage2_P2(towerPosition, mageTower_2P2_Texture, mageTowerOrbTexture, towerIconSrc,
                                              towerIconTextures, scalingFactor());
                _game.data._towers.push_back(newTower);
                break;
            }
            case Tower::TowerType::Mage3_P1: {
                Vector<Rect *> towerIconSrc{towerSrcRectMap[Tower::TowerType::Archer1]};
                Vector<Texture *> towerIconTextures{sellIconTexture};
                auto *newTower = new Mage3_P1(towerPosition, mageTower_3P1_Texture, mageTowerOrbTexture, towerIconSrc,
                                              towerIconTextures, scalingFactor());
                _game.data._towers.push_back(newTower);
                break;
            }
            case Tower::TowerType::Mage3_P2: {
                Vector<Rect *> towerIconSrc{towerSrcRectMap[Tower::TowerType::Archer1]};
                Vector<Texture *> towerIconTextures{sellIconTexture};
                auto *newTower = new Mage3_P2(towerPosition, mageTower_3P2_Texture, mageTowerOrbTexture, towerIconSrc,
                                              towerIconTextures, scalingFactor());
                _game.data._towers.push_back(newTower);
                break;
            }
            case Tower::TowerType::Catapult1: {
                Vector<Rect *> towerIconSrc{towerSrcRectMap[Tower::TowerType::Catapult2_P1],
                                            towerSrcRectMap[Tower::TowerType::Catapult2_P2],
                                            towerSrcRectMap[Tower::TowerType::Archer1]};
                Vector<Texture *> towerIconTextures{catapultTower_2P1_Texture, catapultTower_2P2_Texture,
                                                    sellIconTexture};
                auto *newTower = new Catapult1(towerPosition, catapultTowerTexture, catapultTowerStoneTexture,
                                               towerIconSrc, towerIconTextures, scalingFactor());
                _game.data._towers.push_back(newTower);
                break;
            }
            case Tower::TowerType::Catapult2_P1: {
                Vector<Rect *> towerIconSrc{towerSrcRectMap[Tower::TowerType::Catapult3_P1],
                                            towerSrcRectMap[Tower::TowerType::Archer1]};
                Vector<Texture *> towerIconTextures{catapultTower_3P1_Texture, sellIconTexture};
                auto *newTower = new Catapult2_P1(towerPosition, catapultTower_2P1_Texture, catapultTowerStoneTexture,
                                                  towerIconSrc, towerIconTextures, scalingFactor());
                _game.data._towers.push_back(newTower);
                break;
            }
            case Tower::TowerType::Catapult2_P2: {
                Vector<Rect *> towerIconSrc{towerSrcRectMap[Tower::TowerType::Catapult3_P2],
                                            towerSrcRectMap[Tower::TowerType::Archer1]};
                Vector<Texture *> towerIconTextures{catapultTower_3P2_Texture, sellIconTexture};
                auto *newTower = new Catapult2_P2(towerPosition, catapultTower_2P2_Texture, catapultTowerStoneTexture,
                                                  towerIconSrc, towerIconTextures, scalingFactor());
                _game.data._towers.push_back(newTower);
                break;
            }
            case Tower::TowerType::Catapult3_P1: {
                Vector<Rect *> towerIconSrc{towerSrcRectMap[Tower::TowerType::Archer1]};
                Vector<Texture *> towerIconTextures{sellIconTexture};
                auto *newTower = new Catapult3_P1(towerPosition, catapultTower_3P1_Texture, catapultTowerStoneTexture,
                                                  towerIconSrc, towerIconTextures, scalingFactor());
                _game.data._towers.push_back(newTower);
                break;
            }
            case Tower::TowerType::Catapult3_P2: {
                Vector<Rect *> towerIconSrc{towerSrcRectMap[Tower::TowerType::Archer1]};
                Vector<Texture *> towerIconTextures{sellIconTexture};
                auto *newTower = new Catapult3_P2(towerPosition, catapultTower_3P2_Texture, catapultTowerStoneTexture,
                                                  towerIconSrc, towerIconTextures, scalingFactor());
                _game.data._towers.push_back(newTower);
                break;
            }
            default:;
        }
    }

    bool checkRange(const Rect *src, const Rect *dst, int range, f32 scalingFactor) {
        int xdist = (src->x + (src->w / 2)) - (dst->x + (dst->w / 2));
        int ydist = (src->y + (src->h / 2)) - (dst->y + (dst->h / 2));

        int distance = std::sqrt((xdist * xdist) + (ydist * ydist));
        if (distance <= range * scalingFactor) {
            return true;
        }
        return false;
    }

    void TdState::Init() {
        Base::Init();

        // Init assets
        if (!enemyPathTile) {
            enemyPathTile = IMG_LoadTexture(renderer(), BasePathGraphic "/Floor/enemy_path_tile.png");
        }
        if (!grassTile) {
            grassTile = IMG_LoadTexture(renderer(), BasePathGraphic "/Floor/grass_tile.png");
        }
        if (!towerSlotTexture) {
            towerSlotTexture = IMG_LoadTexture(renderer(), BasePathGraphic "/Floor/PlaceForTower.png");
        }
        if (!archerTowerTexture) {
            archerTowerTexture = IMG_LoadTexture(renderer(), BasePathGraphic "/Archer-Tower/archer_tower.png");
            towerSrcRectMap[Tower::TowerType::Archer1] = new Rect(0, 0, towerWidth, towerHeight);
        }
        if (!archerTower_2P1_Texture) {
            archerTower_2P1_Texture = IMG_LoadTexture(renderer(),
                                                      BasePathGraphic "/Archer-Tower/archer_tower_faster.png");
            towerSrcRectMap[Tower::TowerType::Archer2_P1] = new Rect(0, 0, towerWidth, towerHeight);
        }
        if (!archerTower_2P2_Texture) {
            archerTower_2P2_Texture = IMG_LoadTexture(renderer(),
                                                      BasePathGraphic "/Archer-Tower/archer_tower_crossbow.png");
            towerSrcRectMap[Tower::TowerType::Archer2_P2] = new Rect(0, 0, towerWidth, towerHeight);
        }
        if (!archerTower_3P1_Texture) {
            archerTower_3P1_Texture = IMG_LoadTexture(renderer(),
                                                      BasePathGraphic "/Archer-Tower/archer_tower_faster.png");
            towerSrcRectMap[Tower::TowerType::Archer3_P1] = new Rect(0, 0, towerWidth, towerHeight);
        }
        if (!archerTower_3P2_Texture) {
            archerTower_3P2_Texture = IMG_LoadTexture(renderer(),
                                                      BasePathGraphic "/Archer-Tower/archer_tower_ballista.png");
            towerSrcRectMap[Tower::TowerType::Archer3_P2] = new Rect(0, 0, towerWidth, towerHeight);
        }
        if (!archerTowerArrowTexture) {
            archerTowerArrowTexture = IMG_LoadTexture(
                    renderer(), BasePathGraphic "/Archer-Tower/archer_tower_arrow.png");
        }
        if (!mageTowerTexture) {
            mageTowerTexture = IMG_LoadTexture(renderer(), BasePathGraphic "/Mage-Tower/mage_tower.png");
            towerSrcRectMap[Tower::TowerType::Mage1] = new Rect(0, 0, towerWidth, towerHeight);
        }
        if (!mageTower_2P1_Texture) {
            mageTower_2P1_Texture = IMG_LoadTexture(renderer(), BasePathGraphic "/Mage-Tower/mage_tower_fire.png");
            towerSrcRectMap[Tower::TowerType::Mage2_P1] = new Rect(0, 0, towerWidth, towerHeight);
        }
        if (!mageTower_2P2_Texture) {
            mageTower_2P2_Texture = IMG_LoadTexture(renderer(), BasePathGraphic "/Mage-Tower/mage_tower_ice.png");
            towerSrcRectMap[Tower::TowerType::Mage2_P2] = new Rect(0, 0, towerWidth, towerHeight);
        }
        if (!mageTower_3P1_Texture) {
            mageTower_3P1_Texture = IMG_LoadTexture(renderer(), BasePathGraphic "/Mage-Tower/mage_tower_fire.png");
            towerSrcRectMap[Tower::TowerType::Mage3_P1] = new Rect(0, 0, towerWidth, towerHeight);
        }
        if (!mageTower_3P2_Texture) {
            mageTower_3P2_Texture = IMG_LoadTexture(renderer(), BasePathGraphic "/Mage-Tower/mage_tower_ice.png");
            towerSrcRectMap[Tower::TowerType::Mage3_P2] = new Rect(0, 0, towerWidth, towerHeight);
        }
        if (!mageTowerOrbTexture) {
            mageTowerOrbTexture = IMG_LoadTexture(renderer(), BasePathGraphic "/Mage-Tower/mage_tower_orb.png");
        }
        if (!catapultTowerTexture) {
            catapultTowerTexture = IMG_LoadTexture(renderer(), BasePathGraphic "Catapult-Tower/catapult_tower.png");
            towerSrcRectMap[Tower::TowerType::Catapult1] = new Rect(0, 0, towerWidth, towerHeight);
        }
        if (!catapultTower_2P1_Texture) {
            catapultTower_2P1_Texture = IMG_LoadTexture(renderer(),
                                                        BasePathGraphic "Catapult-Tower/catapult_tower.png");
            towerSrcRectMap[Tower::TowerType::Catapult2_P1] = new Rect(0, 0, towerWidth, towerHeight);
        }
        if (!catapultTower_2P2_Texture) {
            catapultTower_2P2_Texture = IMG_LoadTexture(renderer(),
                                                        BasePathGraphic "Catapult-Tower/catapult_tower.png");
            towerSrcRectMap[Tower::TowerType::Catapult2_P2] = new Rect(0, 0, towerWidth, towerHeight);
        }
        if (!catapultTower_3P1_Texture) {
            catapultTower_3P1_Texture = IMG_LoadTexture(renderer(),
                                                        BasePathGraphic "Catapult-Tower/catapult_tower.png");
            towerSrcRectMap[Tower::TowerType::Catapult3_P1] = new Rect(0, 0, towerWidth, towerHeight);
        }
        if (!catapultTower_3P2_Texture) {
            catapultTower_3P2_Texture = IMG_LoadTexture(renderer(),
                                                        BasePathGraphic "Catapult-Tower/catapult_tower.png");
            towerSrcRectMap[Tower::TowerType::Catapult3_P2] = new Rect(0, 0, towerWidth, towerHeight);
        }
        if (!catapultTowerStoneTexture) {
            catapultTowerStoneTexture = IMG_LoadTexture(
                    renderer(), BasePathGraphic "Catapult-Tower/catapult_tower_stone.png");
        }

        if (!sellIconTexture) {
            sellIconTexture = IMG_LoadTexture(renderer(), BasePathGraphic "/Archer-Tower/archer_tower.png");
        }
        if (!enemyTexture) {
            enemyTexture = IMG_LoadTexture(renderer(), BasePathGraphic "/Enemies/slime_walk.png");
        }

        if (!_music) {
            _music = Mix_LoadMUS(BasePath "asset/music/TD_Music.wav");
            if (!_music)
                print(stderr, "Mix_LoadMUS failed: {}\n", Mix_GetError());
        }

        if (!infoBackgroundTexture) {
            infoBackgroundTexture = IMG_LoadTexture(renderer(), BasePathGraphic "ui-elements.png");
        }

        // Read map from file
        std::ifstream file(BasePath "asset/map/map2");

        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                levelData.emplace_back(line.begin(), line.end());
            }
            file.close();
        } else {
            SDL_Log("Fehler: Konnte die Level-Datei nicht öffnen!");
            SDL_Quit();
        }

        if (tileMap[0][0] == nullptr) {
            for (int i = 0; i < gridHeight; i++) {
                for (int j = 0; j < gridWidth; j++) {
                    Rect *temp = new Rect(
                            j * tileSize * scalingFactor(),
                            i * tileSize * scalingFactor(),
                            tileSize * scalingFactor(),
                            tileSize * scalingFactor()
                    );
                    tileMap[i][j] = temp;
                }
            }
        }
        if (_towerSlots.empty()) {
            int windowWidth, windowHeight;
            SDL_GetRendererOutputSize(renderer(), &windowWidth, &windowHeight);
            infoBackground = new Rect(
                    windowWidth - (85 * scalingFactor()),
                    8 * scalingFactor(),
                    85 * scalingFactor(),
                    42 * scalingFactor());

            Rect *towerIconSrc[3] = {
                    towerSrcRectMap[Tower::TowerType::Mage1], towerSrcRectMap[Tower::TowerType::Archer1],
                    towerSrcRectMap[Tower::TowerType::Catapult1]
            };
            Texture *towerIconTexture[3] = {mageTowerTexture, archerTowerTexture, catapultTowerTexture};

            for (int i = 0; i < gridHeight; i++) {
                for (int j = 0; j < gridWidth; j++) {
                    char tile = levelData[i][j];
                    if (tile == 'T') {
                        Rect *tempRect = new Rect(
                                j * tileSize * scalingFactor(),
                                i * tileSize * scalingFactor(),
                                62 / 2 * scalingFactor(),
                                62 / 2 * scalingFactor()
                        );

                        auto *tempTowerSlot = new TowerSlot(tempRect, towerSlotTexture, towerIconSrc, towerIconTexture,
                                                            scalingFactor());
                        _towerSlots.push_back(tempTowerSlot);
                    }
                }
            }

            // Temporary unlock everything
            /*
            _game.data.unlocks.insert(Tower::TowerType::Archer2_P1);
            _game.data.unlocks.insert(Tower::TowerType::Archer2_P2);
            _game.data.unlocks.insert(Tower::TowerType::Archer3_P1);
            _game.data.unlocks.insert(Tower::TowerType::Archer3_P2);
            _game.data.unlocks.insert(Tower::TowerType::Catapult1);
            _game.data.unlocks.insert(Tower::TowerType::Catapult2_P1);
            _game.data.unlocks.insert(Tower::TowerType::Catapult2_P2);
            _game.data.unlocks.insert(Tower::TowerType::Catapult3_P1);
            _game.data.unlocks.insert(Tower::TowerType::Catapult3_P2);
            _game.data.unlocks.insert(Tower::TowerType::Mage1);
            _game.data.unlocks.insert(Tower::TowerType::Mage2_P1);
            _game.data.unlocks.insert(Tower::TowerType::Mage2_P2);
            _game.data.unlocks.insert(Tower::TowerType::Mage3_P1);
            _game.data.unlocks.insert(Tower::TowerType::Mage3_P2);
            */




            projectileSrcRectMap[archerTowerArrowTexture] = new Rect(1, 1, 2, 12);
            projectileSrcRectMap[mageTowerOrbTexture] = new Rect(0, 0, 32, 32);
            projectileSrcRectMap[catapultTowerTexture] = new Rect(0, 0, 32, 32);

            projectileTextureMap[Tower::TowerType::Archer1] = archerTowerArrowTexture;
            projectileTextureMap[Tower::TowerType::Mage1] = mageTowerOrbTexture;
            projectileTextureMap[Tower::TowerType::Catapult1] = catapultTowerStoneTexture;

            enemyTextureMap[Enemy::EnemyType::Slime] = enemyTexture;

            std::map<int, std::pair<int, int>> edges; // Automatisch sortiert nach Zahlen

            // 'S`, `Z` und Nummern für Pfad suchen
            for (int i = 0; i < levelData.size(); i++) {
                for (int j = 0; j < levelData[i].size(); j++) {
                    char tile = levelData[i][j];
                    if (tile == 'S') {
                        _mapPathStart = {i, j};
                    } else if (tile == 'Z') {
                        _mapPathEnd = {i, j};
                    } else if (isdigit(tile)) {
                        int edgeNum = tile - '0';
                        edges[edgeNum] = {i, j}; // Eckpunkte nach Nummer sortieren
                    }
                }
            }

            if (edges.empty()) {
                std::cout << "Fehler: Keine nummerierten `E`-Punkte gefunden!" << std::endl;
                SDL_Quit();
            }

            // Start → Erster Punkt im Pfad
            auto firstEdge = edges.begin()->second;  // Koordinaten des ersten Pfadpunkts
            int start_dx = (firstEdge.second - _mapPathStart.second) * tileSize * scalingFactor();
            int start_dy = (firstEdge.first - _mapPathStart.first) * tileSize * scalingFactor();

            if (start_dx != 0) {
                _mapPath.push_back(FPoint(start_dx, 0));
            }
            if (start_dy != 0) {
                _mapPath.push_back(FPoint(0, start_dy));
            }

            // Bewegung entlang der Edges
            for (auto it = edges.begin(); next(it) != edges.end(); ++it) {
                auto current = it->second;       // (i, j) aktueller Punkt
                auto nextPos = next(it)->second; // (i, j) nächster Punkt

                int dx = (nextPos.second - current.second) * tileSize * scalingFactor();
                int dy = (nextPos.first - current.first) * tileSize * scalingFactor();

                if (dx != 0) {
                    _mapPath.push_back(FPoint(dx, 0)); // Bewegung in X-Richtung
                }
                if (dy != 0) {
                    _mapPath.push_back(FPoint(0, dy)); // Bewegung in Y-Richtung
                }
            }

            // Letzter Punkt → Endpunkt (`end`)
            auto lastEdge = edges.rbegin()->second;  // Koordinaten des letzten Pfadpunkts
            int end_dx = (_mapPathEnd.second - lastEdge.second) * tileSize * scalingFactor();
            int end_dy = (_mapPathEnd.first - lastEdge.first) * tileSize * scalingFactor();

            if (end_dx != 0) {
                _mapPath.push_back(FPoint(end_dx, 0));
            }
            if (end_dy != 0) {
                _mapPath.push_back(FPoint(0, end_dy));
            }

            if (!overworldButtonTexture) {
                if (TTF_Font *buttonFont = TTF_OpenFont(BasePathFont "RobotoSlab-Bold.ttf", 24)) {
                    SDL_Color white = {255, 255, 255, 255};
                    if (SDL_Surface *btnSurf = TTF_RenderText_Blended(buttonFont, "Enter Overworld", white)) {
                        overworldButtonTexture = SDL_CreateTextureFromSurface(renderer(), btnSurf);
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
        }

        // temporarily fills waves
        std::vector<std::vector<std::pair<Enemy::EnemyType, int>>> waves;
        int waveCount = 10;
        int enemyCount = 10;
        int delay = 1000;
        for (int i = 0; i < waveCount; i++) {
            std::vector<std::pair<Enemy::EnemyType, int>> tempWaves;
            for (int j = 0; j < enemyCount; j++) {
                tempWaves.emplace_back(Enemy::EnemyType::Slime, delay);
            }
            waves.push_back(tempWaves);
            enemyCount *= 1.5;
            delay *= 0.8;
        }
        _waveSystem = new WaveSystem(_mapPath, FPoint(_mapPathStart.second, _mapPathStart.first), enemyTextureMap,
                                     waves);

        lifes = 10;
    }

    void TdState::Enter(bool stacking) {
        Base::Enter(stacking);
        //Mix_PlayMusic(_music, -1);
    }

    void TdState::Exit(bool stacking) {
        Mix_HaltMusic();
        Base::Exit(stacking);
    }

    void TdState::Destroy() {
        // TODO

        Base::Destroy();
    }

    bool TdState::HandleEvent(const Event &event) {
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                Point mouse = {event.button.x, event.button.y};
                if (SDL_PointInRect(&mouse, &overworldButton)) {
                    _game.PushState(MyGS::Overworld);
                    return true;
                }
                for (auto &towerSlot: _towerSlots) {
                    if (!towerSlot->_used) {
                        if (towerSlot->_clicked) {
                            for (int i = 0; i < 3; ++i) {
                                if (SDL_PointInRect(&mouse, towerSlot->_towerIconPosition[i])) {
                                    Tower::TowerType towerType;
                                    switch (i) {
                                        case 0: {
                                            towerType = Tower::TowerType::Mage1;
                                            break;
                                        }
                                        case 1: {
                                            towerType = Tower::TowerType::Archer1;
                                            break;
                                        }
                                        case 2: {
                                            towerType = Tower::TowerType::Catapult1;
                                            break;
                                        }
                                        default:;
                                    }
                                    if (_game.data.unlocks.contains(towerType)) {
                                        switch (towerType) {
                                            case Tower::TowerType::Mage1: {
                                                if (Mage1::_price <= _game.data.gold) {
                                                    _game.data.gold -= Mage1::_price;
                                                    Rect *newTowerPosition = towerSlot->placeTower(scalingFactor());
                                                    if (newTowerPosition != nullptr) {
                                                        createTower(towerType, newTowerPosition);
                                                        return true;
                                                    }
                                                }
                                                break;
                                            }
                                            case Tower::TowerType::Archer1: {
                                                if (Archer1::_price <= _game.data.gold) {
                                                    _game.data.gold -= Archer1::_price;
                                                    Rect *newTowerPosition = towerSlot->placeTower(scalingFactor());
                                                    if (newTowerPosition != nullptr) {
                                                        createTower(towerType, newTowerPosition);
                                                        return true;
                                                    }
                                                }
                                                break;
                                            }
                                            case Tower::TowerType::Catapult1: {
                                                if (Catapult1::_price <= _game.data.gold) {
                                                    _game.data.gold -= Catapult1::_price;
                                                    Rect *newTowerPosition = towerSlot->placeTower(scalingFactor());
                                                    if (newTowerPosition != nullptr) {
                                                        createTower(towerType, newTowerPosition);
                                                        return true;
                                                    }
                                                }
                                                break;
                                            }
                                            default:;
                                        }

                                    }
                                }
                            }
                        }
                        if (SDL_PointInRect(&mouse, towerSlot->_position)) {
                            towerSlot->_clicked = !towerSlot->_clicked;
                        }
                    }
                }
                Tower *soldTower = nullptr;
                int towerIndex = 0;
                Tower::TowerType towerType;
                Rect *newTowerPosition = nullptr;
                for (auto &tower: _game.data._towers) {
                    if (tower->_clicked) {
                        int i = 0;
                        for (auto icon: tower->_towerIconPosition) {
                            if (SDL_PointInRect(&mouse, icon)) {
                                if (icon == tower->_towerIconPosition.back()) {
                                    _game.data.gold += tower->sellTower();
                                    soldTower = tower;
                                    for (auto &towerSlot: _towerSlots) {
                                        if (towerSlot->_position->x ==
                                            tower->_position->x + ((4 / 2) * scalingFactor()) &&
                                            towerSlot->_position->y ==
                                            tower->_position->y + ((66 / 2) * scalingFactor())) {
                                            towerSlot->_used = false;
                                            towerSlot->_clicked = false;
                                            break;
                                        }
                                    }
                                    break;
                                }
                                for (const auto &srcRect: towerSrcRectMap) {
                                    if (srcRect.second == tower->_towerIconSrc[i]) {
                                        towerType = srcRect.first;
                                        break;
                                    }
                                }
                                if (_game.data.unlocks.contains(towerType)) {
                                    switch (towerType) {
                                        case Tower::TowerType::Archer2_P1: {
                                            if (Archer2_P1::_price <= _game.data.gold) {
                                                _game.data.gold -= Archer2_P1::_price;
                                                newTowerPosition = new Rect(tower->_position->x, tower->_position->y,
                                                                            tower->_position->w, tower->_position->h);
                                                soldTower = tower;
                                            }
                                            break;
                                        }
                                        case Tower::TowerType::Archer2_P2: {
                                            if (Archer2_P2::_price <= _game.data.gold) {
                                                _game.data.gold -= Archer2_P2::_price;
                                                newTowerPosition = new Rect(tower->_position->x, tower->_position->y,
                                                                            tower->_position->w, tower->_position->h);
                                                soldTower = tower;
                                            }
                                            break;
                                        }
                                        case Tower::TowerType::Archer3_P1: {
                                            if (Archer3_P1::_price <= _game.data.gold) {
                                                _game.data.gold -= Archer3_P1::_price;
                                                newTowerPosition = new Rect(tower->_position->x, tower->_position->y,
                                                                            tower->_position->w, tower->_position->h);
                                                soldTower = tower;
                                            }
                                            break;
                                        }
                                        case Tower::TowerType::Archer3_P2: {
                                            if (Archer3_P2::_price <= _game.data.gold) {
                                                _game.data.gold -= Archer3_P2::_price;
                                                newTowerPosition = new Rect(tower->_position->x, tower->_position->y,
                                                                            tower->_position->w, tower->_position->h);
                                                soldTower = tower;
                                            }
                                            break;
                                        }
                                        case Tower::TowerType::Mage2_P1: {
                                            if (Mage2_P1::_price <= _game.data.gold) {
                                                _game.data.gold -= Mage2_P1::_price;
                                                newTowerPosition = new Rect(tower->_position->x, tower->_position->y,
                                                                            tower->_position->w, tower->_position->h);
                                                soldTower = tower;
                                            }
                                            break;
                                        }
                                        case Tower::TowerType::Mage2_P2: {
                                            if (Mage2_P2::_price <= _game.data.gold) {
                                                _game.data.gold -= Mage2_P2::_price;
                                                newTowerPosition = new Rect(tower->_position->x, tower->_position->y,
                                                                            tower->_position->w, tower->_position->h);
                                                soldTower = tower;
                                            }
                                            break;
                                        }
                                        case Tower::TowerType::Mage3_P1: {
                                            if (Mage3_P1::_price <= _game.data.gold) {
                                                _game.data.gold -= Mage3_P1::_price;
                                                newTowerPosition = new Rect(tower->_position->x, tower->_position->y,
                                                                            tower->_position->w, tower->_position->h);
                                                soldTower = tower;
                                            }
                                            break;
                                        }
                                        case Tower::TowerType::Mage3_P2: {
                                            if (Mage3_P2::_price <= _game.data.gold) {
                                                _game.data.gold -= Mage3_P2::_price;
                                                newTowerPosition = new Rect(tower->_position->x, tower->_position->y,
                                                                            tower->_position->w, tower->_position->h);
                                                soldTower = tower;
                                            }
                                            break;
                                        }
                                        case Tower::TowerType::Catapult2_P1: {
                                            if (Catapult2_P1::_price <= _game.data.gold) {
                                                _game.data.gold -= Catapult2_P1::_price;
                                                newTowerPosition = new Rect(tower->_position->x, tower->_position->y,
                                                                            tower->_position->w, tower->_position->h);
                                                soldTower = tower;
                                            }
                                            break;
                                        }
                                        case Tower::TowerType::Catapult2_P2: {
                                            if (Catapult2_P2::_price <= _game.data.gold) {
                                                _game.data.gold -= Catapult2_P2::_price;
                                                newTowerPosition = new Rect(tower->_position->x, tower->_position->y,
                                                                            tower->_position->w, tower->_position->h);
                                                soldTower = tower;
                                            }
                                            break;
                                        }
                                        case Tower::TowerType::Catapult3_P1: {
                                            if (Catapult3_P1::_price <= _game.data.gold) {
                                                _game.data.gold -= Catapult3_P1::_price;
                                                newTowerPosition = new Rect(tower->_position->x, tower->_position->y,
                                                                            tower->_position->w, tower->_position->h);
                                                soldTower = tower;
                                            }
                                            break;
                                        }
                                        case Tower::TowerType::Catapult3_P2: {
                                            if (Catapult3_P2::_price <= _game.data.gold) {
                                                _game.data.gold -= Catapult3_P2::_price;
                                                newTowerPosition = new Rect(tower->_position->x, tower->_position->y,
                                                                            tower->_position->w, tower->_position->h);
                                                soldTower = tower;
                                            }
                                            break;
                                        }
                                        default:
                                            return false;
                                    }
                                } else {
                                    return false;
                                }
                            }
                            i++;
                        }
                    }
                    if (SDL_PointInRect(&mouse, tower->_position)) {
                        tower->_clicked = !tower->_clicked;
                    }

                    if (!soldTower)
                        towerIndex++;
                    else
                        break;
                }
                if (soldTower != nullptr) {
                    auto towerIndexIterator = (_game.data._towers.begin() + towerIndex);
                    _game.data._towers.erase(towerIndexIterator);
                    delete soldTower;
                }
                if (newTowerPosition != nullptr) {
                    createTower(towerType, newTowerPosition);
                }
            }
        }
        return false;
    }

    bool TdState::Input() {
        return false;
    }

    void TdState::Update(const u64 frame, const u64 totalMSec, const f32 deltaT) {
        _game.data.wave = _waveSystem->_currentWave;
        _game.data.life = lifes;
        _waveSystem->spawn(totalMSec, tileSize, scalingFactor());

        for (auto projectile: _projectiles) {
            if (projectile->move(deltaT, scalingFactor())) {
                if (projectile->_type.contains(Projectile::ProjectileType::Splash)) {
                    if (projectile->_type.contains(Projectile::ProjectileType::Burn)) {
                        auto *splashProjectile = static_cast<BurningSplashProjectile *>(projectile);
                        _statuses.push_back(splashProjectile->applyEffect(splashProjectile->_target, totalMSec));
                        for (auto enemy: _waveSystem->_enemies) {
                            if (enemy != projectile->_target) {
                                if (checkRange(splashProjectile->_position, enemy->_position,
                                               splashProjectile->_splashRadius, scalingFactor())) {
                                    enemy->takeDamage(splashProjectile->_splashDamage);
                                    _statuses.push_back(splashProjectile->applyEffect(enemy, totalMSec));
                                }
                            }
                        }
                    } else if (projectile->_type.contains(Projectile::ProjectileType::Slow)) {
                        auto *splashProjectile = static_cast<SlowingSplashProjectile *>(projectile);
                        _statuses.push_back(splashProjectile->applyEffect(splashProjectile->_target, totalMSec));
                        for (auto enemy: _waveSystem->_enemies) {
                            if (enemy != projectile->_target) {
                                if (checkRange(splashProjectile->_position, enemy->_position,
                                               splashProjectile->_splashRadius, scalingFactor())) {
                                    enemy->takeDamage(splashProjectile->_splashDamage);
                                    _statuses.push_back(splashProjectile->applyEffect(enemy, totalMSec));
                                }
                            }
                        }
                    } else {
                        for (auto enemy: _waveSystem->_enemies) {
                            if (enemy != projectile->_target) {
                                auto *splashProjectile = static_cast<SplashProjectile *>(projectile);
                                if (checkRange(splashProjectile->_position, enemy->_position,
                                               splashProjectile->_splashRadius, scalingFactor())) {
                                    enemy->takeDamage(splashProjectile->_splashDamage);
                                }
                            }
                        }
                    }
                } else if (projectile->_type.contains(Projectile::ProjectileType::Burn)) {
                    _statuses.push_back(static_cast<BurningProjectile *>(projectile)->applyEffect(totalMSec));
                } else if (projectile->_type.contains(Projectile::ProjectileType::Slow)) {
                    _statuses.push_back(static_cast<SlowingProjectile *>(projectile)->applyEffect(totalMSec));
                }
            }
        }
        if (_projectiles.size() > 500) {
            print("Projectile");
            _projectiles.erase(
                    std::remove_if(_projectiles.begin(), _projectiles.end(),
                                   [](Projectile *projectile) {
                                       if (!projectile->_isVisible) {
                                           delete projectile;  // Speicher freigeben
                                           return true;  // Entfernen aus dem Vektor
                                       }
                                       return false;  // Behalten im Vektor
                                   }),
                    _projectiles.end());
        }

        for (auto status: _statuses) {
            status->tick(totalMSec);
        }
        if (_statuses.size() > 500) {
            print("Status");
            _statuses.erase(
                    std::remove_if(_statuses.begin(), _statuses.end(),
                                   [](Status *status) {
                                       if (!status->_isActive) {
                                           delete status;  // Speicher freigeben
                                           return true;  // Entfernen aus dem Vektor
                                       }
                                       return false;  // Behalten im Vektor
                                   }),
                    _statuses.end());
        }

        for (auto enemy: _waveSystem->_enemies) {
            if (enemy->move(deltaT, scalingFactor()))
                lifes--;
            if (!enemy->_isAlive) {
                _waveSystem->_deadEnemies.push_back(enemy);
            }
        }
        if (lifes <= 0) {
            print("Player died!\n");
            _game.PushState(MyGS::Overworld);
        }
        _waveSystem->_enemies.erase(
                std::remove_if(_waveSystem->_enemies.begin(), _waveSystem->_enemies.end(),
                               [](Enemy *enemy) {
                                   if (!enemy->_isAlive) {// Speicher freigeben
                                       return true;  // Entfernen aus dem Vektor
                                   }
                                   return false;  // Behalten im Vektor
                               }),
                _waveSystem->_enemies.end());

        for (auto tower: _game.data._towers) {
            for (auto enemy: _waveSystem->_enemies) {
                if (enemy->_isAlive) {
                    if (checkRange(tower->_position, enemy->_position, tower->getAttackRange(), scalingFactor())) {
                        Projectile *temp = tower->shoot(enemy, totalMSec);
                        if (temp != nullptr)
                            _projectiles.push_back(temp);
                    }
                }
            }
        }

        if (_waveSystem->wavesFinished()) {
            _game.PushState(MyGS::Overworld);
        }
    }

    void TdState::Render(const u64 frame, u64 totalMSec, const f32 deltaT) {
        // Try the limits, moments before wraparound
        //totalMSec += 2147470000u + 2147480000u;
        Point windowSize;
        SDL_GetWindowSize(window(), &windowSize.x, &windowSize.y);
        Uint32 rendererStart = SDL_GetTicks();

        for (int i = 0; i < gridHeight; i++) {
            for (int j = 0; j < gridWidth; j++) {
                char tile = levelData[i][j];
                switch (tile) {
                    case '.':
                        SDL_RenderCopy(renderer(), grassTile, EntireRect, tileMap[i][j]);
                        break;
                    case 'S':
                    case 'Z':
                    case 'P':
                        SDL_RenderCopy(renderer(), enemyPathTile, EntireRect, tileMap[i][j]);
                        break;
                    default:
                        SDL_RenderCopy(renderer(), grassTile, EntireRect, tileMap[i][j]);
                        break;
                }
                if (std::isdigit(tile)) {
                    SDL_RenderCopy(renderer(), enemyPathTile, EntireRect, tileMap[i][j]);
                }
            }
        }

        for (auto &element: _towerSlots) {
            if (!element->_used) {
                SDL_RenderCopy(renderer(), element->_texture, element->_textureSrcRect, element->_position);
            }
        }

        for (const auto &element: _game.data._towers) {
            SDL_RenderCopy(renderer(), element->_texture, towerSrcRectMap[element->_type], element->_position);
            if (element->_clicked) {
                int i = 0;
                for (auto &icon_position: element->_towerIconPosition) {
                    SDL_RenderCopy(renderer(), element->_towerIconTextures[i], element->_towerIconSrc[i],
                                   icon_position);
                    i++;
                }
            }
        }
        for (const auto &element: _waveSystem->_enemies) {
            if (element->_isAlive)
                SDL_RenderCopy(renderer(), element->_texture, element->_textureSrcRect, element->_position);
        }

        for (auto &element: _projectiles) {
            if (element->_isVisible)
                if (element->_texture == archerTowerArrowTexture) {
                    SDL_Point center = SDL_Point(element->_position->w / 2, element->_position->h / 2);
                    SDL_RenderCopyEx(renderer(), element->_texture, projectileSrcRectMap[element->_texture],
                                     element->_position,
                                     (atan2(element->_direction.y, element->_direction.x) * (180 / M_PI)) + 90, &center,
                                     SDL_FLIP_NONE);
                } else {
                    SDL_RenderCopy(renderer(), element->_texture, projectileSrcRectMap[element->_texture],
                                   element->_position);
                }
        }

        for (auto &element: _towerSlots) {
            if (!element->_used) {
                if (element->_clicked) {
                    for (int i = 0; i < 3; ++i) {
                        SDL_RenderCopy(renderer(), element->_towerIconTextures[i], element->_towerIconSrc[i],
                                       element->_towerIconPosition[i]);
                    }
                }
            }
        }

        if (overworldButtonTexture) {
            int texW, texH;
            SDL_QueryTexture(overworldButtonTexture, nullptr, nullptr, &texW, &texH);

            SDL_Rect destRect;
            destRect.w = texW;
            destRect.h = texH;
            destRect.x = overworldButton.x + (overworldButton.w - texW) / 2;
            destRect.y = overworldButton.y + (overworldButton.h - texH) / 2;
            SDL_RenderCopy(renderer(), overworldButtonTexture, nullptr, &destRect);
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
                std::string waveText = "Wave: " + std::to_string(_waveSystem->_currentWave + 1) + "/" +
                                       std::to_string(_waveSystem->_waves.size());
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
                std::string waveText = "Lifes: " + std::to_string(lifes);
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

        SDL_RenderPresent(renderer());

        Uint32 rendererTimeNeeded = SDL_GetTicks() - rendererStart;
        int delay = 1000 / 60 - rendererTimeNeeded;

        if (delay > 0) {
            SDL_Delay(delay);
        }

    }
} // namespace
