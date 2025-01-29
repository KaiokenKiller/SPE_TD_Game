#include <iostream>
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

    bool Tower::checkPrice(int gold) {
        return gold >= _price;
    }


    bool Tower::checkCooldown(u64 totalMSec) {
        if (_cooldown < totalMSec) {
            _cooldown = totalMSec + getAttackSpeed();
            return true;
        }
        return false;
    }

    Archer1::Archer1(Rect *placement, Texture *texture, Texture *projectileTexture) : Tower(
        placement, texture, projectileTexture) {
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

    Mage1::Mage1(Rect *placement, Texture *texture, Texture *projectileTexture) : Tower(
        placement, texture, projectileTexture) {
        _type = TowerType::Mage1;
    }

	int Mage1::getAttackSpeed() {
		return _attackSpeed;
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

    Catapult1::Catapult1(Rect *placement, Texture *texture, Texture *projectileTexture) : Tower(
        placement, texture, projectileTexture) {
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

    Tower *TowerSlot::placeTower(Tower::TowerType towerType, std::unordered_map<Tower::TowerType, Texture *> projectileTextures, f32 scalingFactor) {
        if (!_used) {
                _used = true;
                Rect *towerPosition = new Rect(_position->x - ((4/2)*scalingFactor), _position->y - ((66/2)*scalingFactor), ((70/2)*scalingFactor), ((130/2)*scalingFactor));
                switch (towerType) {
                    case Tower::TowerType::Archer1: {
                        return new Archer1{towerPosition, _towerIconTextures[1], projectileTextures[towerType]};
                    }
                    case Tower::TowerType::Mage1: {
                        return new Mage1{towerPosition, _towerIconTextures[0], projectileTextures[towerType]};
                    }
                    case Tower::TowerType::Catapult1: {
                        return new Catapult1{towerPosition, _towerIconTextures[2], projectileTextures[towerType]};
                    }
                }
            }
        return nullptr;
    }

    Enemy::Enemy(Rect *position, Texture *texture, const Vector<FPoint> &path, int hp, int speed, int spawnDelay) {
        _position = position;
        _texture = texture;
        _hp = hp;
        _speed = speed;
		_spawnDelay = spawnDelay;

        _textureSrcRect = new Rect(46 * 5, 0, 46, 46);
        _path = path;
    }

    bool Enemy::takeDamage(int damage) {
        _hp -= damage;
        if (_hp <= 0)
            _isAlive = false;
        return _isAlive;
    }

    void Enemy::move(const f32 deltaT, f32 scalingFactor) {
        if (_isAlive) {
            int movement = deltaT * 100 * _speed * scalingFactor;

            while (movement > 0) {
                if (_path[_currentPath].x != 0) {
                    if (abs(_path[_currentPath].x) - movement < 0) {
                        _position->x += _path[_currentPath].x;
                        movement -= abs(_path[_currentPath].x);
                        _path[_currentPath].x = 0;
                        _currentPath++;
                    } else {
                        if (_path[_currentPath].x > 0) {
                            _position->x += movement;
                            _path[_currentPath].x -= movement;
                            movement = 0;
                        } else {
                            _position->x -= movement;
                            _path[_currentPath].x += movement;
                            movement = 0;
                        }
                    }
                } else if (_path[_currentPath].y != 0) {
                    if (abs(_path[_currentPath].y) - movement < 0) {
                        _position->y += _path[_currentPath].y;
                        movement -= abs(_path[_currentPath].y);
                        _path[_currentPath].y = 0;
                        _currentPath++;
                    } else {
                        if (_path[_currentPath].y > 0) {
                            _position->y += movement;
                            _path[_currentPath].y -= movement;
                            movement = 0;
                        } else {
                            _position->y -= movement;
                            _path[_currentPath].y += movement;
                            movement = 0;
                        }
                    }
                }
                if (_currentPath == _path.size())
                    _isAlive = false; //Ziel erreicht
            }
        }
    }

	/*
    FPoint Enemy::predictMove(f32 deltaT) const {
        auto predictedMovement = FPoint(_position->x, _position->y);
        int movement = deltaT * 100 * _speed;
        int tempCurrentPath = _currentPath;

        while (movement > 0) {
            if (_path[tempCurrentPath].x != 0) {
                if (abs(_path[tempCurrentPath].x) - movement < 0) {
                    predictedMovement.x += _path[tempCurrentPath].x;
                    movement -= abs(_path[tempCurrentPath].x);
                    tempCurrentPath++;
                } else {
                    if (_path[tempCurrentPath].x > 0) {
                        predictedMovement.x += movement;
                        movement = 0;
                    } else {
                        predictedMovement.x -= movement;
                        movement = 0;
                    }
                }
            } else if (_path[tempCurrentPath].y != 0) {
                if (abs(_path[tempCurrentPath].y) - movement < 0) {
                    predictedMovement.y += _path[tempCurrentPath].y;
                    movement -= abs(_path[tempCurrentPath].y);
                    tempCurrentPath++;
                } else {
                    if (_path[tempCurrentPath].y > 0) {
                        predictedMovement.y += movement;
                        movement = 0;
                    } else {
                        predictedMovement.y -= movement;
                        movement = 0;
                    }
                }
            }
        }
        return predictedMovement;
    }
    */

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

	EnemySpawner::EnemySpawner(Vector<Enemy*> &enemies) :_enemies(enemies) {}

	Enemy *EnemySpawner::spawn(JanSordid::Core::u64 totalMSec) {
		if (_delay <= totalMSec){
			if (currentEnemy < _enemies.size()){
				Enemy* enemy = _enemies[currentEnemy];
				_delay = totalMSec + enemy->_spawnDelay;
				currentEnemy++;
				return enemy;
			}
		}
		return nullptr;
	}

    void TdState::Init() {
        Base::Init();

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
            archerTowerTexture = IMG_LoadTexture(renderer(), BasePathGraphic "/Archer-Tower/archer_tower_idle.png");
        }
        if (!archerTowerArrowTexture) {
            archerTowerArrowTexture = IMG_LoadTexture(
                renderer(), BasePathGraphic "/Archer-Tower/archer_tower_arrow.png");
        }
        if (!mageTowerTexture) {
            mageTowerTexture = IMG_LoadTexture(renderer(), BasePathGraphic "/Mage-Tower/mage-tower.png");
        }
        if (!mageTowerOrbTexture) {
            mageTowerOrbTexture = IMG_LoadTexture(renderer(), BasePathGraphic "/Mage-Tower/mage_tower_orb.png");
        }
        if (!catapultTowerTexture) {
            catapultTowerTexture = IMG_LoadTexture(renderer(), BasePathGraphic "Catapult-Tower/catapult_tower.png");
        }
        if (!catapultTowerStoneTexture) {
            catapultTowerStoneTexture = IMG_LoadTexture(
                renderer(), BasePathGraphic "Catapult-Tower/catapult_tower_stone.png");
        }
        if (!enemyTexture) {
            enemyTexture = IMG_LoadTexture(renderer(), BasePathGraphic "/Enemies/slime_walk.png");
        }

        if (!_music) {
            _music = Mix_LoadMUS(BasePath "asset/music/TD_Music.wav");
            if (!_music)
                print(stderr, "Mix_LoadMUS failed: {}\n", Mix_GetError());
        }
        Mix_PlayMusic(_music, -1);

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


        // Spawning temporary Dummies
        if (_game.data._towers.empty()) {
            projectileSrcRectMap[archerTowerArrowTexture] = new Rect(1, 1, 2, 12);
            projectileSrcRectMap[mageTowerOrbTexture] = new Rect(0, 0, 32, 32);
            projectileSrcRectMap[catapultTowerTexture] = new Rect(0, 0, 32, 32);

            projectileTextureMap[Tower::TowerType::Archer1] = archerTowerArrowTexture;
            projectileTextureMap[Tower::TowerType::Mage1] = mageTowerOrbTexture;
            projectileTextureMap[Tower::TowerType::Catapult1] = catapultTowerStoneTexture;

            Rect *tempRect = new Rect(0, 0, towerWidth, towerHeight);
            towerSrcRectMap[Tower::TowerType::Archer1] = tempRect;


            tempRect = new Rect(
                20 * tileSize * scalingFactor(),
                11 * tileSize * scalingFactor(),
                towerWidth / 2 * scalingFactor(),
                towerHeight / 2 * scalingFactor()
            );

            auto *tempTower = new Archer1(tempRect, archerTowerTexture, archerTowerArrowTexture);
            _game.data._towers.push_back(tempTower);

            tempRect = new Rect(
                25 * tileSize * scalingFactor(),
                11 * tileSize * scalingFactor(),
                towerWidth / 1.5 * scalingFactor(),
                towerHeight / 1.5 * scalingFactor()
            );

            auto *tempMageTower = new Mage1(tempRect, mageTowerTexture, mageTowerOrbTexture);
            _game.data._towers.push_back(tempMageTower);

            tempRect = new Rect(
                15 * tileSize * scalingFactor(),
                11 * tileSize * scalingFactor(),
                towerWidth / 1.5 * scalingFactor(),
                towerHeight / 1.5 * scalingFactor()
            );

            auto *tempCatapultTower = new Catapult1(tempRect, catapultTowerTexture, catapultTowerStoneTexture);
            _game.data._towers.push_back(tempCatapultTower);

            tempRect = new Rect(
                10 * tileSize * scalingFactor(),
                13 * tileSize * scalingFactor(),
                62 / 1.5 * scalingFactor(),
                62 / 1.5 * scalingFactor()
            );

            Rect *towerIconSrc[3] = {
                towerSrcRectMap[Tower::TowerType::Mage1], towerSrcRectMap[Tower::TowerType::Archer1],
                towerSrcRectMap[Tower::TowerType::Catapult1]
            };
            Texture *towerIconTexture[3] = {mageTowerTexture, archerTowerTexture, catapultTowerTexture};


            auto *tempTowerSlot = new TowerSlot(tempRect, towerSlotTexture, towerIconSrc, towerIconTexture,scalingFactor());
            _towerSlots.push_back(tempTowerSlot);

            tempRect = new Rect(
                0,
                gridHeight / 4 * 3 * tileSize * scalingFactor(),
                46/2*scalingFactor(),
                46/2*scalingFactor()
            );

            Vector<FPoint> path;

            path.push_back(FPoint(40 * tileSize * scalingFactor(), 0));

			Vector<Enemy*> enemiesToSpawn;

			for (int i = 0; i < 100; ++i) {
				auto *tempEnemy = new Enemy(tempRect, enemyTexture, path, 50, 1,1000);
				enemiesToSpawn.push_back(tempEnemy);
			}

			enemySpawner = new EnemySpawner(enemiesToSpawn);

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
									}
									if (_game.data.unlocks.contains(towerType)) {
										bool priceCheck = false;
										switch (towerType) {
											case Tower::TowerType::Mage1: {
												if ((priceCheck = Mage1::checkPrice(_game.data.gold)))
													_game.data.gold -= Mage1::_price;
												break;
											}
											case Tower::TowerType::Archer1: {
												if ((priceCheck = Archer1::checkPrice(_game.data.gold)))
													_game.data.gold -= Archer1::_price;
												break;
											}
											case Tower::TowerType::Catapult1: {
												if ((priceCheck = Catapult1::checkPrice(_game.data.gold)))
													_game.data.gold -= Catapult1::_price;
												break;
											}
											default:;
										}
										if (priceCheck) {
											Tower *newTower = towerSlot->placeTower(towerType, projectileTextureMap,scalingFactor());
											if (newTower != nullptr) {
												_game.data._towers.push_back(newTower);
												return true;
											}
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

                for (auto &tower: _game.data._towers) {
                    //ToDo Upgrades implementieren
                }
            }
        }
        return false;
    }

    bool TdState::Input() {
        return false;
    }

    void TdState::Update(const u64 frame, const u64 totalMSec, const f32 deltaT) {
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

        for (auto enemy: _enemies) {
            enemy->move(deltaT,scalingFactor());
            // temporary for testing
            if (!enemy->_isAlive) {
                Vector<FPoint> path;
                path.push_back(FPoint(40 * tileSize * scalingFactor(), 0));

                enemy->_position->x = 0;
                enemy->_path = path;
                enemy->_currentPath = 0;
                enemy->_isAlive = true;
                enemy->_hp = 50;
            }
        }

		Enemy* spawnedEnemy = enemySpawner->spawn(totalMSec);
		if (spawnedEnemy != nullptr){
			_enemies.push_back(spawnedEnemy);
		}

        for (auto tower: _game.data._towers) {
			// ToDo ordentliches Range handeling und Enemy selecting
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


        for (int i = 0; i < gridHeight; i++) {
            for (int j = 0; j < gridWidth; j++) {
                if (i == gridHeight / 2 || i == (gridHeight / 2) + 1) {
                    SDL_RenderCopy(renderer(), enemyPathTile, EntireRect, tileMap[i][j]);
                } else {
                    SDL_RenderCopy(renderer(), grassTile, EntireRect, tileMap[i][j]);
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
    }
} // namespace
