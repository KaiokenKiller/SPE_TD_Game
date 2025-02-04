#include <iostream>
#include <map>

#include "example_game.hpp"

namespace JanSordid::SDL_Example {
    Tower::Tower(Rect *placement, Texture *texture, Texture *projectileTexture) {
        _position = placement;
        _texture = texture;
        _projectileTexture = projectileTexture;
    }

    int Tower::_attackDamage = 0;
    int Tower::_attackRange = 0;
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
        return getPrice() /2;
    }

    Archer1::Archer1(Rect *placement, Texture *texture, Texture *projectileTexture, const Vector<Rect*>& towerIconSrc, const Vector<Texture*>& towerIconTextures, f32 scalingFactor) : Tower(
        placement, texture, projectileTexture) {
        _towerIconSrc = towerIconSrc;
        _towerIconTextures = towerIconTextures;

        int iconWidth = 16*scalingFactor;
        int iconHeight = 32*scalingFactor;

        _towerIconPosition.push_back(new Rect(_position->x - iconWidth, _position->y, iconWidth, iconHeight));
        _towerIconPosition.push_back(new Rect(_position->x + _position->w, _position->y, iconWidth, iconHeight));
        _towerIconPosition.push_back(new Rect(_position->x + ((_position->w / 2) - (iconWidth/2)), _position->y + (_position->h), iconWidth, iconHeight));

        _type = TowerType::Archer1;
    }

    int Archer1::_attackDamage = 5;
    int Archer1::_attackRange = 2;
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

    int Archer1::getPrice() {
        return _price;
    }

    Archer2_P1::Archer2_P1(Rect *placement, Texture *texture, Texture *projectileTexture, const Vector<Rect*>& towerIconSrc, const Vector<Texture*>& towerIconTextures, f32 scalingFactor) : Tower(
        placement, texture, projectileTexture) {
        _towerIconSrc = towerIconSrc;
        _towerIconTextures = towerIconTextures;

        int iconWidth = 16*scalingFactor;
        int iconHeight = 32*scalingFactor;

        _towerIconPosition.push_back(new Rect(_position->x + ((_position->w / 2) - (iconWidth/2)), _position->y + iconHeight, iconWidth, iconHeight));
        _towerIconPosition.push_back(new Rect(_position->x + ((_position->w / 2) - (iconWidth/2)), _position->y + (_position->h), iconWidth, iconHeight));

        _type = TowerType::Archer2_P1;
    }

    int Archer2_P1::_attackDamage = 5;
    int Archer2_P1::_attackRange = 2;
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

    int Archer2_P1::getPrice() {
        return _price;
    }

    Archer2_P2::Archer2_P2(Rect *placement, Texture *texture, Texture *projectileTexture, const Vector<Rect*>& towerIconSrc, const Vector<Texture*>& towerIconTextures, f32 scalingFactor) : Tower(
        placement, texture, projectileTexture) {
        _towerIconSrc = towerIconSrc;
        _towerIconTextures = towerIconTextures;

        int iconWidth = 16*scalingFactor;
        int iconHeight = 32*scalingFactor;

        _towerIconPosition.push_back(new Rect(_position->x + ((_position->w / 2) - (iconWidth/2)), _position->y + iconHeight, iconWidth, iconHeight));
        _towerIconPosition.push_back(new Rect(_position->x + ((_position->w / 2) - (iconWidth/2)), _position->y + (_position->h), iconWidth, iconHeight));

        _type = TowerType::Archer2_P2;
    }

    int Archer2_P2::_attackDamage = 10;
    int Archer2_P2::_attackRange = 2;
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

    int Archer2_P2::getPrice() {
        return _price;
    }

    Archer3_P1::Archer3_P1(Rect *placement, Texture *texture, Texture *projectileTexture, const Vector<Rect*>& towerIconSrc, const Vector<Texture*>& towerIconTextures, f32 scalingFactor) : Tower(
        placement, texture, projectileTexture) {
        _towerIconSrc = towerIconSrc;
        _towerIconTextures = towerIconTextures;

        int iconWidth = 16*scalingFactor;
        int iconHeight = 32*scalingFactor;

        _towerIconPosition.push_back(new Rect(_position->x + ((_position->w / 2) - (iconWidth/2)), _position->y + (_position->h), iconWidth, iconHeight));

        _type = TowerType::Archer3_P1;
    }

    int Archer3_P1::_attackDamage = 5;
    int Archer3_P1::_attackRange = 2;
    int Archer3_P1::_attackSpeed = 250;
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

    int Archer3_P1::getPrice() {
        return _price;
    }

    Archer3_P2::Archer3_P2(Rect *placement, Texture *texture, Texture *projectileTexture, const Vector<Rect*>& towerIconSrc, const Vector<Texture*>& towerIconTextures, f32 scalingFactor) : Tower(
        placement, texture, projectileTexture) {
        _towerIconSrc = towerIconSrc;
        _towerIconTextures = towerIconTextures;

        int iconWidth = 16*scalingFactor;
        int iconHeight = 32*scalingFactor;

        _towerIconPosition.push_back(new Rect(_position->x + ((_position->w / 2) - (iconWidth/2)), _position->y + (_position->h), iconWidth, iconHeight));

        _type = TowerType::Archer3_P2;
    }

    int Archer3_P2::_attackDamage = 25;
    int Archer3_P2::_attackRange = 2;
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

    int Archer3_P2::getPrice() {
        return _price;
    }

    Mage1::Mage1(Rect *placement, Texture *texture, Texture *projectileTexture, const Vector<Rect*>& towerIconSrc, const Vector<Texture*>& towerIconTextures, f32 scalingFactor) : Tower(
        placement, texture, projectileTexture) {
        _towerIconSrc = towerIconSrc;
        _towerIconTextures = towerIconTextures;

        int iconWidth = 16*scalingFactor;
        int iconHeight = 32*scalingFactor;

        _towerIconPosition.push_back(new Rect(_position->x - iconWidth, _position->y, iconWidth, iconHeight));
        _towerIconPosition.push_back(new Rect(_position->x + _position->w, _position->y, iconWidth, iconHeight));
        _towerIconPosition.push_back(new Rect(_position->x + ((_position->w / 2) - (iconWidth/2)), _position->y + (_position->h), iconWidth, iconHeight));

        _type = TowerType::Mage1;
    }

	int Mage1::getAttackSpeed() {
		return _attackSpeed;
	}

    int Mage1::getPrice() {
        return _price;
    }

    int Mage1::_attackDamage = 7;
    int Mage1::_attackRange = 2;
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

    Mage2_P1::Mage2_P1(Rect *placement, Texture *texture, Texture *projectileTexture, const Vector<Rect*>& towerIconSrc, const Vector<Texture*>& towerIconTextures, f32 scalingFactor) : Tower(
        placement, texture, projectileTexture) {
        _towerIconSrc = towerIconSrc;
        _towerIconTextures = towerIconTextures;

        int iconWidth = 16*scalingFactor;
        int iconHeight = 32*scalingFactor;

        _towerIconPosition.push_back(new Rect(_position->x + ((_position->w / 2) - (iconWidth/2)), _position->y + iconHeight, iconWidth, iconHeight));
        _towerIconPosition.push_back(new Rect(_position->x + ((_position->w / 2) - (iconWidth/2)), _position->y + (_position->h), iconWidth, iconHeight));

        _type = TowerType::Mage2_P1;
    }

    int Mage2_P1::getAttackSpeed() {
        return _attackSpeed;
    }

    int Mage2_P1::getPrice() {
        return _price;
    }

    int Mage2_P1::_attackDamage = 7;
    int Mage2_P1::_attackRange = 2;
    int Mage2_P1::_attackSpeed = 1000;
    int Mage2_P1::_price = 200;

    Projectile *Mage2_P1::shoot(Enemy *target, u64 totalMSec) {
        if (checkCooldown(totalMSec)) {
            Rect *startPosition = new Rect(_position->x + (_position->w / 2), _position->y + (_position->h / 2), 32,
                                           32);
            return new Projectile(startPosition, _projectileTexture, _attackDamage, target);
        }
        return nullptr;
    }

    Mage2_P2::Mage2_P2(Rect *placement, Texture *texture, Texture *projectileTexture, const Vector<Rect*>& towerIconSrc, const Vector<Texture*>& towerIconTextures, f32 scalingFactor) : Tower(
        placement, texture, projectileTexture) {
        _towerIconSrc = towerIconSrc;
        _towerIconTextures = towerIconTextures;

        int iconWidth = 16*scalingFactor;
        int iconHeight = 32*scalingFactor;

        _towerIconPosition.push_back(new Rect(_position->x + ((_position->w / 2) - (iconWidth/2)), _position->y + iconHeight, iconWidth, iconHeight));
        _towerIconPosition.push_back(new Rect(_position->x + ((_position->w / 2) - (iconWidth/2)), _position->y + (_position->h), iconWidth, iconHeight));

        _type = TowerType::Mage2_P2;
    }

    int Mage2_P2::getAttackSpeed() {
        return _attackSpeed;
    }

    int Mage2_P2::getPrice() {
        return _price;
    }

    int Mage2_P2::_attackDamage = 7;
    int Mage2_P2::_attackRange = 2;
    int Mage2_P2::_attackSpeed = 1000;
    int Mage2_P2::_price = 200;

    Projectile *Mage2_P2::shoot(Enemy *target, u64 totalMSec) {
        if (checkCooldown(totalMSec)) {
            Rect *startPosition = new Rect(_position->x + (_position->w / 2), _position->y + (_position->h / 2), 32,
                                           32);
            return new Projectile(startPosition, _projectileTexture, _attackDamage, target);
        }
        return nullptr;
    }

    Mage3_P1::Mage3_P1(Rect *placement, Texture *texture, Texture *projectileTexture, const Vector<Rect*>& towerIconSrc, const Vector<Texture*>& towerIconTextures, f32 scalingFactor) : Tower(
        placement, texture, projectileTexture) {
        _towerIconSrc = towerIconSrc;
        _towerIconTextures = towerIconTextures;

        int iconWidth = 16*scalingFactor;
        int iconHeight = 32*scalingFactor;

        _towerIconPosition.push_back(new Rect(_position->x + ((_position->w / 2) - (iconWidth/2)), _position->y + (_position->h), iconWidth, iconHeight));

        _type = TowerType::Mage3_P1;
    }

    int Mage3_P1::getAttackSpeed() {
        return _attackSpeed;
    }

    int Mage3_P1::getPrice() {
        return _price;
    }

    int Mage3_P1::_attackDamage = 7;
    int Mage3_P1::_attackRange = 2;
    int Mage3_P1::_attackSpeed = 1000;
    int Mage3_P1::_price = 250;

    Projectile *Mage3_P1::shoot(Enemy *target, u64 totalMSec) {
        if (checkCooldown(totalMSec)) {
            Rect *startPosition = new Rect(_position->x + (_position->w / 2), _position->y + (_position->h / 2), 32,
                                           32);
            return new Projectile(startPosition, _projectileTexture, _attackDamage, target);
        }
        return nullptr;
    }

    Mage3_P2::Mage3_P2(Rect *placement, Texture *texture, Texture *projectileTexture, const Vector<Rect*>& towerIconSrc, const Vector<Texture*>& towerIconTextures, f32 scalingFactor) : Tower(
        placement, texture, projectileTexture) {
        _towerIconSrc = towerIconSrc;
        _towerIconTextures = towerIconTextures;

        int iconWidth = 16*scalingFactor;
        int iconHeight = 32*scalingFactor;

        _towerIconPosition.push_back(new Rect(_position->x + ((_position->w / 2) - (iconWidth/2)), _position->y + (_position->h), iconWidth, iconHeight));

        _type = TowerType::Mage3_P2;
    }

    int Mage3_P2::getAttackSpeed() {
        return _attackSpeed;
    }

    int Mage3_P2::getPrice() {
        return _price;
    }

    int Mage3_P2::_attackDamage = 7;
    int Mage3_P2::_attackRange = 2;
    int Mage3_P2::_attackSpeed = 1000;
    int Mage3_P2::_price = 250;

    Projectile *Mage3_P2::shoot(Enemy *target, u64 totalMSec) {
        if (checkCooldown(totalMSec)) {
            Rect *startPosition = new Rect(_position->x + (_position->w / 2), _position->y + (_position->h / 2), 32,
                                           32);
            return new Projectile(startPosition, _projectileTexture, _attackDamage, target);
        }
        return nullptr;
    }

    Catapult1::Catapult1(Rect *placement, Texture *texture, Texture *projectileTexture, const Vector<Rect*>& towerIconSrc, const Vector<Texture*>& towerIconTextures, f32 scalingFactor) : Tower(
        placement, texture, projectileTexture) {
        _towerIconSrc = towerIconSrc;
        _towerIconTextures = towerIconTextures;

        int iconWidth = 16*scalingFactor;
        int iconHeight = 32*scalingFactor;

        _towerIconPosition.push_back(new Rect(_position->x - iconWidth, _position->y, iconWidth, iconHeight));
        _towerIconPosition.push_back(new Rect(_position->x + _position->w, _position->y, iconWidth, iconHeight));
        _towerIconPosition.push_back(new Rect(_position->x + ((_position->w / 2) - (iconWidth/2)), _position->y + (_position->h), iconWidth, iconHeight));

        _type = TowerType::Catapult1;
    }

    int Catapult1::_attackDamage = 10;
    int Catapult1::_attackRange = 4;
    int Catapult1::_attackSpeed = 1500;
    int Catapult1::_price = 200;

    Projectile *Catapult1::shoot(Enemy *target, u64 totalMSec) {
        if (checkCooldown(totalMSec)) {
            Rect *startPosition = new Rect(_position->x + (_position->w / 2), _position->y + (_position->h / 2), 32,
                                           32);
            return new Projectile(startPosition, _projectileTexture, _attackDamage, target);
        }
        return nullptr;
    }

	int Catapult1::getAttackSpeed() {
		return _attackSpeed;
	}

    int Catapult1::getPrice() {
        return _price;
    }

    Catapult2_P1::Catapult2_P1(Rect *placement, Texture *texture, Texture *projectileTexture, const Vector<Rect*>& towerIconSrc, const Vector<Texture*>& towerIconTextures, f32 scalingFactor) : Tower(
        placement, texture, projectileTexture) {
        _towerIconSrc = towerIconSrc;
        _towerIconTextures = towerIconTextures;

        int iconWidth = 16*scalingFactor;
        int iconHeight = 32*scalingFactor;

        _towerIconPosition.push_back(new Rect(_position->x + ((_position->w / 2) - (iconWidth/2)), _position->y + iconHeight, iconWidth, iconHeight));
        _towerIconPosition.push_back(new Rect(_position->x + ((_position->w / 2) - (iconWidth/2)), _position->y + (_position->h), iconWidth, iconHeight));

        _type = TowerType::Catapult2_P1;
    }

    int Catapult2_P1::_attackDamage = 10;
    int Catapult2_P1::_attackRange = 4;
    int Catapult2_P1::_attackSpeed = 1500;
    int Catapult2_P1::_price = 250;

    Projectile *Catapult2_P1::shoot(Enemy *target, u64 totalMSec) {
        if (checkCooldown(totalMSec)) {
            Rect *startPosition = new Rect(_position->x + (_position->w / 2), _position->y + (_position->h / 2), 32,
                                           32);
            return new Projectile(startPosition, _projectileTexture, _attackDamage, target);
        }
        return nullptr;
    }

    int Catapult2_P1::getAttackSpeed() {
        return _attackSpeed;
    }

    int Catapult2_P1::getPrice() {
        return _price;
    }

    Catapult2_P2::Catapult2_P2(Rect *placement, Texture *texture, Texture *projectileTexture, const Vector<Rect*>& towerIconSrc, const Vector<Texture*>& towerIconTextures, f32 scalingFactor) : Tower(
        placement, texture, projectileTexture) {
        _towerIconSrc = towerIconSrc;
        _towerIconTextures = towerIconTextures;

        int iconWidth = 16*scalingFactor;
        int iconHeight = 32*scalingFactor;

        _towerIconPosition.push_back(new Rect(_position->x + ((_position->w / 2) - (iconWidth/2)), _position->y + iconHeight, iconWidth, iconHeight));
        _towerIconPosition.push_back(new Rect(_position->x + ((_position->w / 2) - (iconWidth/2)), _position->y + (_position->h), iconWidth, iconHeight));

        _type = TowerType::Catapult2_P2;
    }

    int Catapult2_P2::_attackDamage = 10;
    int Catapult2_P2::_attackRange = 4;
    int Catapult2_P2::_attackSpeed = 1500;
    int Catapult2_P2::_price = 250;

    Projectile *Catapult2_P2::shoot(Enemy *target, u64 totalMSec) {
        if (checkCooldown(totalMSec)) {
            Rect *startPosition = new Rect(_position->x + (_position->w / 2), _position->y + (_position->h / 2), 32,
                                           32);
            return new Projectile(startPosition, _projectileTexture, _attackDamage, target);
        }
        return nullptr;
    }

    int Catapult2_P2::getAttackSpeed() {
        return _attackSpeed;
    }

    int Catapult2_P2::getPrice() {
        return _price;
    }

    Catapult3_P1::Catapult3_P1(Rect *placement, Texture *texture, Texture *projectileTexture, const Vector<Rect*>& towerIconSrc, const Vector<Texture*>& towerIconTextures, f32 scalingFactor) : Tower(
        placement, texture, projectileTexture) {
        _towerIconSrc = towerIconSrc;
        _towerIconTextures = towerIconTextures;

        int iconWidth = 16*scalingFactor;
        int iconHeight = 32*scalingFactor;

        _towerIconPosition.push_back(new Rect(_position->x + ((_position->w / 2) - (iconWidth/2)), _position->y + (_position->h), iconWidth, iconHeight));

        _type = TowerType::Catapult3_P1;
    }

    int Catapult3_P1::_attackDamage = 10;
    int Catapult3_P1::_attackRange = 4;
    int Catapult3_P1::_attackSpeed = 1500;
    int Catapult3_P1::_price = 300;

    Projectile *Catapult3_P1::shoot(Enemy *target, u64 totalMSec) {
        if (checkCooldown(totalMSec)) {
            Rect *startPosition = new Rect(_position->x + (_position->w / 2), _position->y + (_position->h / 2), 32,
                                           32);
            return new Projectile(startPosition, _projectileTexture, _attackDamage, target);
        }
        return nullptr;
    }

    int Catapult3_P1::getAttackSpeed() {
        return _attackSpeed;
    }

    int Catapult3_P1::getPrice() {
        return _price;
    }

    Catapult3_P2::Catapult3_P2(Rect *placement, Texture *texture, Texture *projectileTexture, const Vector<Rect*>& towerIconSrc, const Vector<Texture*>& towerIconTextures, f32 scalingFactor) : Tower(
        placement, texture, projectileTexture) {
        _towerIconSrc = towerIconSrc;
        _towerIconTextures = towerIconTextures;

        int iconWidth = 16*scalingFactor;
        int iconHeight = 32*scalingFactor;

        _towerIconPosition.push_back(new Rect(_position->x + ((_position->w / 2) - (iconWidth/2)), _position->y + (_position->h), iconWidth, iconHeight));

        _type = TowerType::Catapult3_P2;
    }

    int Catapult3_P2::_attackDamage = 10;
    int Catapult3_P2::_attackRange = 4;
    int Catapult3_P2::_attackSpeed = 1500;
    int Catapult3_P2::_price = 300;

    Projectile *Catapult3_P2::shoot(Enemy *target, u64 totalMSec) {
        if (checkCooldown(totalMSec)) {
            Rect *startPosition = new Rect(_position->x + (_position->w / 2), _position->y + (_position->h / 2), 32,
                                           32);
            return new Projectile(startPosition, _projectileTexture, _attackDamage, target);
        }
        return nullptr;
    }

    int Catapult3_P2::getAttackSpeed() {
        return _attackSpeed;
    }

    int Catapult3_P2::getPrice() {
        return _price;
    }

    TowerSlot::TowerSlot(Rect *position, Texture *texture,
                         Rect **towerIconSrc, Texture **towerIconTextures, f32 scalingFactor) {
        _position = position;
        _texture = texture;
        _textureSrcRect = new Rect(0, 0, 62, 61);

        for (int i = 0; i < 3; ++i) {
            _towerIconSrc[i] = towerIconSrc[i];
            _towerIconTextures[i] = towerIconTextures[i];
        }
        int iconWidth = 32*scalingFactor;
        int iconHeight = 64*scalingFactor;
        _towerIconPosition[0] = new Rect(_position->x - iconWidth, _position->y - iconHeight, iconWidth, iconHeight);
        _towerIconPosition[1] = new Rect(_position->x + ((_position->w / 2) - (iconWidth/2)), _position->y - (iconHeight + (8*scalingFactor)), iconWidth, iconHeight);
        _towerIconPosition[2] = new Rect(_position->x + _position->w, _position->y - iconHeight, iconWidth, iconHeight);
    }

    Rect *TowerSlot::placeTower(f32 scalingFactor) {
        if (!_used) {
                _used = true;
            return new Rect(_position->x - ((4/2)*scalingFactor), _position->y - ((66/2)*scalingFactor), ((70/2)*scalingFactor), ((130/2)*scalingFactor));
            }
        return nullptr;
    }

    Enemy::Enemy(Rect *position, Texture *texture, const Vector<FPoint> &path, int hp, int speed) {
        _isAlive = true;
        _position = position;
        _texture = texture;
        _hp = hp;
        _speed = speed;
        _textureSrcRect = new Rect(46 * 5, 0, 46, 46);
        _path = path;
    }

    bool Enemy::takeDamage(int damage) {
        _hp -= damage;
        if (_hp <= 0)
            _isAlive = false;
        return _isAlive;
    }

    void Enemy::move(const f32 deltaT,f32 scalingFactor) {
        if (!_isAlive || _currentPath >= _path.size()) return;

        int movement = static_cast<int>(deltaT * 100.0f * _speed * scalingFactor);

        // Sicherstellen, dass die Schleife nicht unendlich läuft
        while (movement > 0 && _currentPath < _path.size()) {
            FPoint &currentMove = _path[_currentPath];

            if (currentMove.x != 0) {
                int moveX = std::min(movement, static_cast<int>(std::abs(currentMove.x)));
                _position->x += (currentMove.x > 0) ? moveX : -moveX;
                currentMove.x += (currentMove.x > 0) ? -moveX : moveX;
                movement -= moveX;
            }
            else if (currentMove.y != 0) {
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
                    break;
                }
            }
        }
    }

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

    void Projectile::move(const f32 deltaT, f32 scalingFactor) {
        if (_isVisible) {
            _position->x += _direction.x * deltaT * _speed * scalingFactor;
            _position->y += _direction.y * deltaT * _speed * scalingFactor;

            if (SDL_HasIntersection(_position, _target->_position)) {
                _target->takeDamage(_damage);
                _isVisible = false;
            }
            _homingCounter -= deltaT * 1000;
            if (_homingCounter <= 0) {
                updateDirection();
            }
        }
    }

    void TdState::createTower(Tower::TowerType towerType, Rect *towerPosition) {
        switch (towerType) {
            case Tower::TowerType::Archer1: {
                Vector<Rect*> towerIconSrc {towerSrcRectMap[Tower::TowerType::Archer2_P1],towerSrcRectMap[Tower::TowerType::Archer2_P2],towerSrcRectMap[Tower::TowerType::Archer1]};
                Vector<Texture*> towerIconTextures {archerTower_2P1_Texture,archerTower_2P2_Texture,sellIconTexture};
                auto * newTower = new Archer1(towerPosition,archerTowerTexture,archerTowerArrowTexture,towerIconSrc,towerIconTextures,scalingFactor());
                _game.data._towers.push_back(newTower);
                break;
            }
            case Tower::TowerType::Archer2_P1: {
                Vector<Rect*> towerIconSrc {towerSrcRectMap[Tower::TowerType::Archer3_P1],towerSrcRectMap[Tower::TowerType::Archer1]};
                Vector<Texture*> towerIconTextures {archerTower_3P1_Texture,sellIconTexture};
                auto * newTower = new Archer2_P1(towerPosition,archerTower_2P1_Texture,archerTowerArrowTexture,towerIconSrc,towerIconTextures,scalingFactor());
                _game.data._towers.push_back(newTower);
                break;
            }
            case Tower::TowerType::Archer2_P2: {
                Vector<Rect*> towerIconSrc {towerSrcRectMap[Tower::TowerType::Archer3_P2],towerSrcRectMap[Tower::TowerType::Archer1]};
                Vector<Texture*> towerIconTextures {archerTower_3P2_Texture,sellIconTexture};
                auto * newTower = new Archer2_P2(towerPosition,archerTower_2P2_Texture,archerTowerArrowTexture,towerIconSrc,towerIconTextures,scalingFactor());
                _game.data._towers.push_back(newTower);
                break;
            }
            case Tower::TowerType::Archer3_P1: {
                Vector<Rect*> towerIconSrc {towerSrcRectMap[Tower::TowerType::Archer1]};
                Vector<Texture*> towerIconTextures {sellIconTexture};
                auto * newTower = new Archer3_P1(towerPosition,archerTower_3P1_Texture,archerTowerArrowTexture,towerIconSrc,towerIconTextures,scalingFactor());
                _game.data._towers.push_back(newTower);
                break;
            }
            case Tower::TowerType::Archer3_P2: {
                Vector<Rect*> towerIconSrc {towerSrcRectMap[Tower::TowerType::Archer1]};
                Vector<Texture*> towerIconTextures {sellIconTexture};
                auto * newTower = new Archer3_P2(towerPosition,archerTower_3P2_Texture,archerTowerArrowTexture,towerIconSrc,towerIconTextures,scalingFactor());
                _game.data._towers.push_back(newTower);
                break;
            }
            case Tower::TowerType::Mage1: {
                Vector<Rect*> towerIconSrc {towerSrcRectMap[Tower::TowerType::Mage2_P1],towerSrcRectMap[Tower::TowerType::Mage2_P2],towerSrcRectMap[Tower::TowerType::Archer1]};
                Vector<Texture*> towerIconTextures {mageTower_2P1_Texture,mageTower_2P2_Texture,sellIconTexture};
                auto * newTower = new Mage1(towerPosition,mageTowerTexture,mageTowerOrbTexture,towerIconSrc,towerIconTextures,scalingFactor());
                _game.data._towers.push_back(newTower);
                break;
            }
            case Tower::TowerType::Mage2_P1: {
                Vector<Rect*> towerIconSrc {towerSrcRectMap[Tower::TowerType::Mage3_P1],towerSrcRectMap[Tower::TowerType::Archer1]};
                Vector<Texture*> towerIconTextures {mageTower_3P1_Texture,sellIconTexture};
                auto * newTower = new Mage2_P1(towerPosition,mageTower_2P1_Texture,mageTowerOrbTexture,towerIconSrc,towerIconTextures,scalingFactor());
                _game.data._towers.push_back(newTower);
                break;
            }
            case Tower::TowerType::Mage2_P2: {
                Vector<Rect*> towerIconSrc {towerSrcRectMap[Tower::TowerType::Mage3_P2],towerSrcRectMap[Tower::TowerType::Archer1]};
                Vector<Texture*> towerIconTextures {mageTower_3P2_Texture,sellIconTexture};
                auto * newTower = new Mage2_P2(towerPosition,mageTower_2P2_Texture,mageTowerOrbTexture,towerIconSrc,towerIconTextures,scalingFactor());
                _game.data._towers.push_back(newTower);
                break;
            }
            case Tower::TowerType::Mage3_P1: {
                Vector<Rect*> towerIconSrc {towerSrcRectMap[Tower::TowerType::Archer1]};
                Vector<Texture*> towerIconTextures {sellIconTexture};
                auto * newTower = new Mage3_P1(towerPosition,mageTower_3P1_Texture,mageTowerOrbTexture,towerIconSrc,towerIconTextures,scalingFactor());
                _game.data._towers.push_back(newTower);
                break;
            }
            case Tower::TowerType::Mage3_P2: {
                Vector<Rect*> towerIconSrc {towerSrcRectMap[Tower::TowerType::Archer1]};
                Vector<Texture*> towerIconTextures {sellIconTexture};
                auto * newTower = new Mage3_P2(towerPosition,mageTower_3P2_Texture,mageTowerOrbTexture,towerIconSrc,towerIconTextures,scalingFactor());
                _game.data._towers.push_back(newTower);
                break;
            }
            case Tower::TowerType::Catapult1: {
                Vector<Rect*> towerIconSrc {towerSrcRectMap[Tower::TowerType::Catapult2_P1],towerSrcRectMap[Tower::TowerType::Catapult2_P2],towerSrcRectMap[Tower::TowerType::Archer1]};
                Vector<Texture*> towerIconTextures {catapultTower_2P1_Texture,catapultTower_2P2_Texture,sellIconTexture};
                auto * newTower = new Catapult1(towerPosition,catapultTowerTexture,catapultTowerStoneTexture,towerIconSrc,towerIconTextures,scalingFactor());
                _game.data._towers.push_back(newTower);
                break;
            }
            case Tower::TowerType::Catapult2_P1: {
                Vector<Rect*> towerIconSrc {towerSrcRectMap[Tower::TowerType::Catapult3_P1],towerSrcRectMap[Tower::TowerType::Archer1]};
                Vector<Texture*> towerIconTextures {catapultTower_3P1_Texture,sellIconTexture};
                auto * newTower = new Catapult2_P1(towerPosition,catapultTower_2P1_Texture,catapultTowerStoneTexture,towerIconSrc,towerIconTextures,scalingFactor());
                _game.data._towers.push_back(newTower);
                break;
            }
            case Tower::TowerType::Catapult2_P2: {
                Vector<Rect*> towerIconSrc {towerSrcRectMap[Tower::TowerType::Catapult3_P2],towerSrcRectMap[Tower::TowerType::Archer1]};
                Vector<Texture*> towerIconTextures {catapultTower_3P2_Texture,sellIconTexture};
                auto * newTower = new Catapult2_P2(towerPosition,catapultTower_2P2_Texture,catapultTowerStoneTexture,towerIconSrc,towerIconTextures,scalingFactor());
                _game.data._towers.push_back(newTower);
                break;
            }
            case Tower::TowerType::Catapult3_P1: {
                Vector<Rect*> towerIconSrc {towerSrcRectMap[Tower::TowerType::Archer1]};
                Vector<Texture*> towerIconTextures {sellIconTexture};
                auto * newTower = new Catapult3_P1(towerPosition,catapultTower_3P1_Texture,catapultTowerStoneTexture,towerIconSrc,towerIconTextures,scalingFactor());
                _game.data._towers.push_back(newTower);
                break;
            }
            case Tower::TowerType::Catapult3_P2: {
                Vector<Rect*> towerIconSrc {towerSrcRectMap[Tower::TowerType::Archer1]};
                Vector<Texture*> towerIconTextures {sellIconTexture};
                auto * newTower = new Catapult3_P2(towerPosition,catapultTower_3P2_Texture,catapultTowerStoneTexture,towerIconSrc,towerIconTextures,scalingFactor());
                _game.data._towers.push_back(newTower);
                break;
            }
            default: ;
        }
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
            towerSrcRectMap[Tower::TowerType::Archer1] = new Rect(0,0,towerWidth,towerHeight);
        }
        if (!archerTower_2P1_Texture) {
            archerTower_2P1_Texture = IMG_LoadTexture(renderer(), BasePathGraphic "/Archer-Tower/archer_tower_faster.png");
            towerSrcRectMap[Tower::TowerType::Archer2_P1] = new Rect(0,0,towerWidth,towerHeight);
        }
        if (!archerTower_2P2_Texture) {
            archerTower_2P2_Texture = IMG_LoadTexture(renderer(), BasePathGraphic "/Archer-Tower/archer_tower_crossbow.png");
            towerSrcRectMap[Tower::TowerType::Archer2_P2] = new Rect(0,0,towerWidth,towerHeight);
        }
        if (!archerTower_3P1_Texture) {
            archerTower_3P1_Texture = IMG_LoadTexture(renderer(), BasePathGraphic "/Archer-Tower/archer_tower.png");
            towerSrcRectMap[Tower::TowerType::Archer3_P1] = new Rect(0,0,towerWidth,towerHeight);
        }
        if (!archerTower_3P2_Texture) {
            archerTower_3P2_Texture = IMG_LoadTexture(renderer(), BasePathGraphic "/Archer-Tower/archer_tower_ballista.png");
            towerSrcRectMap[Tower::TowerType::Archer3_P2] = new Rect(0,0,towerWidth,towerHeight);
        }
        if (!archerTowerArrowTexture) {
            archerTowerArrowTexture = IMG_LoadTexture(
                renderer(), BasePathGraphic "/Archer-Tower/archer_tower_arrow.png");
        }
        if (!mageTowerTexture) {
            mageTowerTexture = IMG_LoadTexture(renderer(), BasePathGraphic "/Mage-Tower/mage_tower.png");
            towerSrcRectMap[Tower::TowerType::Mage1] = new Rect(0,0,towerWidth,towerHeight);
        }
        if (!mageTower_2P1_Texture) {
            mageTower_2P1_Texture = IMG_LoadTexture(renderer(), BasePathGraphic "/Mage-Tower/mage_tower.png");
            towerSrcRectMap[Tower::TowerType::Mage2_P1] = new Rect(0,0,towerWidth,towerHeight);
        }
        if (!mageTower_2P2_Texture) {
            mageTower_2P2_Texture = IMG_LoadTexture(renderer(), BasePathGraphic "/Mage-Tower/mage_tower.png");
            towerSrcRectMap[Tower::TowerType::Mage2_P2] = new Rect(0,0,towerWidth,towerHeight);
        }
        if (!mageTower_3P1_Texture) {
            mageTower_3P1_Texture = IMG_LoadTexture(renderer(), BasePathGraphic "/Mage-Tower/mage_tower.png");
            towerSrcRectMap[Tower::TowerType::Mage3_P1] = new Rect(0,0,towerWidth,towerHeight);
        }
        if (!mageTower_3P2_Texture) {
            mageTower_3P2_Texture = IMG_LoadTexture(renderer(), BasePathGraphic "/Mage-Tower/mage_tower.png");
            towerSrcRectMap[Tower::TowerType::Mage3_P2] = new Rect(0,0,towerWidth,towerHeight);
        }
        if (!mageTowerOrbTexture) {
            mageTowerOrbTexture = IMG_LoadTexture(renderer(), BasePathGraphic "/Mage-Tower/mage_tower_orb.png");
        }
        if (!catapultTowerTexture) {
            catapultTowerTexture = IMG_LoadTexture(renderer(), BasePathGraphic "Catapult-Tower/catapult_tower.png");
            towerSrcRectMap[Tower::TowerType::Catapult1] = new Rect(0,0,towerWidth,towerHeight);
        }
        if (!catapultTower_2P1_Texture) {
            catapultTower_2P1_Texture = IMG_LoadTexture(renderer(), BasePathGraphic "Catapult-Tower/catapult_tower.png");
            towerSrcRectMap[Tower::TowerType::Catapult2_P1] = new Rect(0,0,towerWidth,towerHeight);
        }
        if (!catapultTower_2P2_Texture) {
            catapultTower_2P2_Texture = IMG_LoadTexture(renderer(), BasePathGraphic "Catapult-Tower/catapult_tower.png");
            towerSrcRectMap[Tower::TowerType::Catapult2_P2] = new Rect(0,0,towerWidth,towerHeight);
        }
        if (!catapultTower_3P1_Texture) {
            catapultTower_3P1_Texture = IMG_LoadTexture(renderer(), BasePathGraphic "Catapult-Tower/catapult_tower.png");
            towerSrcRectMap[Tower::TowerType::Catapult3_P1] = new Rect(0,0,towerWidth,towerHeight);
        }
        if (!catapultTower_3P2_Texture) {
            catapultTower_3P2_Texture = IMG_LoadTexture(renderer(), BasePathGraphic "Catapult-Tower/catapult_tower.png");
            towerSrcRectMap[Tower::TowerType::Catapult3_P2] = new Rect(0,0,towerWidth,towerHeight);
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
            Rect *towerIconSrc[3] = {
                towerSrcRectMap[Tower::TowerType::Mage1], towerSrcRectMap[Tower::TowerType::Archer1],
                towerSrcRectMap[Tower::TowerType::Catapult1]
            };
            Texture *towerIconTexture[3] = {mageTowerTexture, archerTowerTexture, catapultTowerTexture};

            for (int i = 0; i < gridHeight; i++) {
                for (int j = 0; j < gridWidth; j++) {
                    char tile = levelData[i][j];
                    if( tile == 'T' ){
                        Rect *tempRect = new Rect(
                            j * tileSize * scalingFactor(),
                            i * tileSize * scalingFactor(),
                            62 / 2 * scalingFactor(),
                            62 / 2 * scalingFactor()
                        );

                        auto *tempTowerSlot = new TowerSlot(tempRect, towerSlotTexture, towerIconSrc, towerIconTexture, scalingFactor());
                        _towerSlots.push_back(tempTowerSlot);
                    }
                }
            }
        }

        // Spawning temporary Dummies
        if (_game.data._towers.empty()) {
            projectileSrcRectMap[archerTowerArrowTexture] = new Rect(1, 1, 2, 12);
            projectileSrcRectMap[mageTowerOrbTexture] = new Rect(0, 0, 32, 32);
            projectileSrcRectMap[catapultTowerTexture] = new Rect(0, 0, 32, 32);

            projectileTextureMap[Tower::TowerType::Archer1] = archerTowerArrowTexture;
            projectileTextureMap[Tower::TowerType::Mage1] = mageTowerOrbTexture;
            projectileTextureMap[Tower::TowerType::Catapult1] = catapultTowerStoneTexture;

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
        }
    }

    void TdState::Enter(bool stacking) {
        Base::Enter(stacking);
        Mix_PlayMusic(_music, -1);
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
                if (OverworldState::IsMouseOver(overworldButton, mouse)) {
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
                                        default: ;
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
                Tower* soldTower = nullptr;
                int towerIndex = 0;
                for (auto &tower: _game.data._towers) {
                    if (tower->_clicked) {
                        int i = 0;
                        Tower::TowerType towerType;
                        for (auto icon: tower->_towerIconPosition) {
                            if (SDL_PointInRect(&mouse, icon)) {
                                if (icon == tower->_towerIconPosition.back()) {
                                    _game.data.gold += tower->sellTower();
                                    soldTower = tower;
                                    for (auto &towerSlot: _towerSlots) {
                                        if (towerSlot->_position->x == tower->_position->x + ((4/2)*scalingFactor()) && towerSlot->_position->y == tower->_position->y + ((66/2)*scalingFactor())) {
                                            towerSlot->_used = false;
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
                                                createTower(towerType, tower->_position);
                                                return true;
                                            }
                                            break;
                                        }
                                        case Tower::TowerType::Archer2_P2: {
                                            if (Archer2_P2::_price <= _game.data.gold) {
                                                _game.data.gold -= Archer2_P2::_price;
                                                createTower(towerType, tower->_position);
                                                return true;
                                            }
                                            break;
                                        }
                                        case Tower::TowerType::Archer3_P1: {
                                            if (Archer3_P1::_price <= _game.data.gold) {
                                                _game.data.gold -= Archer3_P1::_price;
                                                createTower(towerType, tower->_position);
                                                return true;
                                            }
                                            break;
                                        }
                                        case Tower::TowerType::Archer3_P2: {
                                            if (Archer3_P2::_price <= _game.data.gold) {
                                                _game.data.gold -= Archer3_P2::_price;
                                                createTower(towerType, tower->_position);
                                                return true;
                                            }
                                            break;
                                        }
                                        case Tower::TowerType::Mage2_P1: {
                                            if (Mage2_P1::_price <= _game.data.gold) {
                                                _game.data.gold -= Mage2_P1::_price;
                                                createTower(towerType, tower->_position);
                                                return true;
                                            }
                                            break;
                                        }
                                        case Tower::TowerType::Mage2_P2: {
                                            if (Mage2_P2::_price <= _game.data.gold) {
                                                _game.data.gold -= Mage2_P2::_price;
                                                createTower(towerType, tower->_position);
                                                return true;
                                            }
                                            break;
                                        }
                                        case Tower::TowerType::Mage3_P1: {
                                            if (Mage3_P1::_price <= _game.data.gold) {
                                                _game.data.gold -= Mage3_P1::_price;
                                                createTower(towerType, tower->_position);
                                                return true;
                                            }
                                            break;
                                        }
                                        case Tower::TowerType::Mage3_P2: {
                                            if (Mage3_P2::_price <= _game.data.gold) {
                                                _game.data.gold -= Mage3_P2::_price;
                                                createTower(towerType, tower->_position);
                                                return true;
                                            }
                                            break;
                                        }
                                        case Tower::TowerType::Catapult2_P1: {
                                            if (Catapult2_P1::_price <= _game.data.gold) {
                                                _game.data.gold -= Catapult2_P1::_price;
                                                createTower(towerType, tower->_position);
                                                return true;
                                            }
                                            break;
                                        }
                                        case Tower::TowerType::Catapult2_P2: {
                                            if (Catapult2_P2::_price <= _game.data.gold) {
                                                _game.data.gold -= Catapult2_P2::_price;
                                                createTower(towerType, tower->_position);
                                                return true;
                                            }
                                            break;
                                        }
                                        case Tower::TowerType::Catapult3_P1: {
                                            if (Catapult3_P1::_price <= _game.data.gold) {
                                                _game.data.gold -= Catapult3_P1::_price;
                                                createTower(towerType, tower->_position);
                                                return true;
                                            }
                                            break;
                                        }
                                        case Tower::TowerType::Catapult3_P2: {
                                            if (Catapult3_P2::_price <= _game.data.gold) {
                                                _game.data.gold -= Catapult3_P2::_price;
                                                createTower(towerType, tower->_position);
                                                return true;
                                            }
                                            break;
                                        }
                                        default:
                                            return false;
                                    }
                                }
                                else {
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
                    auto towerIndexIterator = (_game.data._towers.begin() +towerIndex);
                    _game.data._towers.erase(towerIndexIterator);
                    delete soldTower;
                }
            }
        }
        return false;
    }

    bool TdState::Input() {
        return false;
    }

    void TdState::Update(const u64 frame, const u64 totalMSec, const f32 deltaT) {

        // Most basic enemy spawner copied from Jan
        if( respawnCD < totalMSec ) {
            if (!_deadEnemies.empty()) {
                // Gegner aus der "Toten"-Liste holen
                Enemy* tempEnemy = _deadEnemies.back();
                _deadEnemies.pop_back();

                // Gegner zurücksetzen
                tempEnemy->_position->x = _mapPathStart.second * tileSize * scalingFactor();
                tempEnemy->_position->y = _mapPathStart.first * tileSize * scalingFactor();
                tempEnemy->_path = _mapPath;
                tempEnemy->_currentPath = 0;
                tempEnemy->_isAlive = true;
                tempEnemy->_hp = 50;

                // Gegner der _enemies-Liste hinzufügen
                _enemies.push_back(tempEnemy);
                std::cout << "Reused old enemie" << std::endl;

            } else {
                // Neuen Gegner erstellen, falls kein "toter" Gegner verfügbar ist
                Rect* tempRect = new Rect(
                    _mapPathStart.second * tileSize * scalingFactor(),
                    _mapPathStart.first * tileSize * scalingFactor(),
                    46,
                    46
                );
                auto* tempEnemy = new Enemy(tempRect, enemyTexture, _mapPath, 50, 1);
                _enemies.push_back(tempEnemy);
            }

            respawnCD = totalMSec + 2000;
        }

        for (auto projectile: _projectiles) {
            projectile->move(deltaT,scalingFactor());
        }
        if (_projectiles.size() > 500) {
			_projectiles.erase(
					std::remove_if(_projectiles.begin(), _projectiles.end(),
								   [](Projectile* projectile) {
									   if (!projectile->_isVisible) {
										   delete projectile;  // Speicher freigeben
										   return true;  // Entfernen aus dem Vektor
									   }
									   return false;  // Behalten im Vektor
								   }),
					_projectiles.end());

		}

        for (auto enemy : _enemies) {
            enemy->move(deltaT,scalingFactor());
            if (!enemy->_isAlive) {
                _deadEnemies.push_back(enemy);
                _toRemove.push_back(enemy); // Gegner zum Entfernen markieren
            }
        }

        // Entferne die markierten Gegner aus _enemies
        for (Enemy* enemy : _toRemove) {
            _enemies.erase(std::remove(_enemies.begin(), _enemies.end(), enemy), _enemies.end());
        }
        _toRemove.clear(); // Hilfsvektor leeren

        for (auto tower: _game.data._towers) {
            Projectile *temp = tower->shoot(_enemies[0], totalMSec);
            if (temp != nullptr)
                _projectiles.push_back(temp);
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
                    case '.': SDL_RenderCopy(renderer(), grassTile, EntireRect, tileMap[i][j]);
                        break;
                    case 'S':
                    case 'Z':
                    case 'P':
                        SDL_RenderCopy(renderer(), enemyPathTile, EntireRect, tileMap[i][j]);
                        break;
                    default: SDL_RenderCopy(renderer(), grassTile, EntireRect, tileMap[i][j]);
                        break;
                }
                if ( std::isdigit(tile) ) {
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
                    SDL_RenderCopy(renderer(), element->_towerIconTextures[i], element->_towerIconSrc[i], icon_position);
                    i++;
                }
            }
        }
        for (const auto &element: _enemies) {
            if (element->_isAlive)
                SDL_RenderCopy(renderer(), element->_texture, element->_textureSrcRect, element->_position);
        }

        for (auto &element: _projectiles) {
            if (element->_isVisible)
                SDL_RenderCopy(renderer(), element->_texture, projectileSrcRectMap[element->_texture],
                               element->_position);
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

        SDL_RenderPresent(renderer());

        Uint32 rendererTimeNeeded = SDL_GetTicks() - rendererStart;
        int delay = 1000 / 60 - rendererTimeNeeded;

        if( delay > 0) {
            SDL_Delay(delay);
        }

    }
} // namespace
