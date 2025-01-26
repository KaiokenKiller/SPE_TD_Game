#include <iostream>

#include "example_game.hpp"
#include "example_game.hpp"

namespace JanSordid::SDL_Example {

    Tower::Tower(Rect *placement, Texture *texture, Texture * projectileTexture) {
        _position = placement;
        _texture = texture;
		_projectileTexture = projectileTexture;
    }

    TowerArcher1::TowerArcher1(Rect *placement, Texture *texture, Texture * projectileTexture) : Tower(placement, texture, projectileTexture) {
        _type = TowerType::Archer1;
        _attackDamage = 5;
        _attackRange = 2;
        _attackSpeed = 5;
    }

	Projectile * TowerArcher1::shoot(Enemy *target, f32 deltaT) {
		Rect * startPosition = new Rect( _position->x + (_position->w/2), _position->y + (_position->h/2), 3, 14);
		return new Projectile(startPosition, _projectileTexture, _attackDamage, target);
	}

    Mage1::Mage1(Rect *placement, Texture *texture, Texture * projectileTexture) : Tower(placement, texture, projectileTexture) {
        _type = TowerType::Mage1;
        _attackDamage = 7;
        _attackRange = 2;
        _attackSpeed = 3;
    }

	Projectile * Mage1::shoot(Enemy *target, f32 deltaT) {
		Rect * startPosition = new Rect( _position->x + (_position->w/2), _position->y + (_position->h/2), 32, 32 );
		return new Projectile(startPosition, _projectileTexture, _attackDamage, target);
    }

    Catapult1::Catapult1(Rect *placement, Texture *texture, Texture * projectileTexture) : Tower(placement, texture, projectileTexture) {
        _type = TowerType::Catapult1;
        _attackDamage = 10;
        _attackRange = 4;
        _attackSpeed = 2;
    }

	Projectile * Catapult1::shoot(Enemy *target, f32 deltaT) {
		Rect * startPosition = new Rect( _position->x + (_position->w/2), _position->y + (_position->h/2), 32, 32 );
		return new Projectile(startPosition, _projectileTexture, _attackDamage, target);
    }

	Enemy::Enemy(Rect *position, Texture *texture, Vector<FPoint> path,int hp, int speed) {
		_isAlive = true;
		_position = position;
		_texture = texture;
		_hp = hp;
		_speed = speed;
		_textureSrcRect = new Rect(46*5,0,46,46);
		_path = path;
	}

	bool Enemy::takeDamage(int damage) {
		_hp -= damage;
		if (_hp<=0)
			_isAlive = false;
		return _isAlive;
	}

	void Enemy::move(const f32 deltaT ) {
		if (_isAlive) {
			int movement = deltaT * 100 * _speed;

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

	FPoint Enemy::predictMove(f32 deltaT) {
		FPoint predictedMovement = FPoint (_position->x,_position->y);
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

	Projectile::Projectile(Rect *position, Texture *texture, int damage, Enemy *target) {
		_isVisible = true;
		_position = position;
		_texture = texture;
		_damage = damage;
		_target = target;

		_direction = FPoint ((_target->_position->x - _position->x),_target->_position->y - _position->y);
		float directionLength = sqrt((_direction.x * _direction.x) + (_direction.y * _direction.y));
		if (directionLength != 0){
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
		if (directionLength != 0){
			_direction.x /= directionLength;
			_direction.x *= 2;
			_direction.y /= directionLength;
			_direction.y *= 2;
		}
	}

	void Projectile::move(const f32 deltaT) {
		if (_isVisible){
			_position->x += _direction.x * deltaT * _speed;
			_position->y += _direction.y * deltaT * _speed;

			if (SDL_HasIntersection(_position,_target->_position)){
				_target->takeDamage(_damage);
				_isVisible = false;
			}
			_homingCounter -= deltaT * 1000;
			if (_homingCounter <= 0){
				updateDirection();
			}
		}
	}

    void TdState::Init() {
        Base::Init();

        if (!enemyPathTile) {
            enemyPathTile = IMG_LoadTexture(renderer(), BasePathGraphic "/Floor/enemy_path_tile.png");
        }
        if (!grassTile) {
            grassTile = IMG_LoadTexture(renderer(), BasePathGraphic "/Floor/grass_tile.png");
        }
        if (!archerTowerTexture) {
            archerTowerTexture = IMG_LoadTexture(renderer(), BasePathGraphic "/Archer-Tower/archer_tower_idle.png");
        }
		if (!archerTowerArrowTexture){
			archerTowerArrowTexture = IMG_LoadTexture(renderer(), BasePathGraphic "/Archer-Tower/archer_tower_arrow.png");
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
			catapultTowerStoneTexture = IMG_LoadTexture(renderer(), BasePathGraphic "Catapult-Tower/catapult_tower_stone.png");
		}
        if (!enemyTexture) {
            enemyTexture = IMG_LoadTexture(renderer(), BasePathGraphic "/Enemies/slime_walk.png");
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

        // Spawning temporary Dummies
		if (_game.data._towers.empty()) {
			projectileSrcRectMap[archerTowerArrowTexture] = new Rect(1, 1, 2, 12);
			projectileSrcRectMap[mageTowerOrbTexture] = new Rect(0, 0, 32, 32);
			projectileSrcRectMap[catapultTowerTexture] = new Rect(0, 0, 32, 32);


			Rect *tempRect = new Rect(0, 0, towerWidth, towerHeight);
			towerSrcRectMap[Tower::TowerType::Archer1] = tempRect;


			tempRect = new Rect(
					20 * tileSize * scalingFactor(),
					11 * tileSize * scalingFactor(),
					towerWidth / 2 * scalingFactor(),
					towerHeight / 2 * scalingFactor()
			);

			TowerArcher1 *tempTower = new TowerArcher1(tempRect, archerTowerTexture, archerTowerArrowTexture);
			_game.data._towers.push_back(tempTower);

			tempRect = new Rect(
					25 * tileSize * scalingFactor(),
					11 * tileSize * scalingFactor(),
					towerWidth / 1.5 * scalingFactor(),
					towerHeight / 1.5 * scalingFactor()
			);

			Mage1 *tempMageTower = new Mage1(tempRect, mageTowerTexture, mageTowerOrbTexture);
			_game.data._towers.push_back(tempMageTower);

			tempRect = new Rect(
					15 * tileSize * scalingFactor(),
					11 * tileSize * scalingFactor(),
					towerWidth / 1.5 * scalingFactor(),
					towerHeight / 1.5 * scalingFactor()
			);

			Catapult1 *tempCatapultTower = new Catapult1(tempRect, catapultTowerTexture, catapultTowerStoneTexture);
			_game.data._towers.push_back(tempCatapultTower);

			tempRect = new Rect(
					0,
					gridHeight / 4 * 3*  tileSize * scalingFactor(),
					46,
					46
			);

			Vector<FPoint> path;

			path.push_back(FPoint(40 * tileSize * scalingFactor(), 0));


			Enemy *tempEnemy = new Enemy(tempRect, enemyTexture, path, 10, 2);
			_enemies.push_back(tempEnemy);

			if (!overworldButtonTexture) {
				TTF_Font *buttonFont = TTF_OpenFont(BasePathFont "RobotoSlab-Bold.ttf", 24);
				if (buttonFont) {
					SDL_Color white = {255, 255, 255, 255};
					SDL_Surface *btnSurf = TTF_RenderText_Blended(buttonFont, "Enter Overworld", white);
					if (btnSurf) {
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
            }
        }
    }

    bool TdState::Input() {
        return false;
    }

    void TdState::Update(const u64 frame, const u64 totalMSec, const f32 deltaT) {
		for (auto projectile:_projectiles) {
			projectile->move(deltaT);
		}

		for (auto enemy:_enemies) {
			enemy->move(deltaT);
			// temporary for testing
			if (!enemy->_isAlive) {
				Vector<FPoint> path;
				path.push_back(FPoint(40*tileSize*scalingFactor(),0));

				enemy->_position->x = 0;
				enemy->_path = path;
				enemy->_currentPath = 0;
				enemy->_isAlive = true;
				enemy->_hp = 10;
			}
		}

		static u64 cd = 0;
		if (totalMSec > cd) {
			for (auto tower: _game.data._towers) {
				_projectiles.push_back(tower->shoot(_enemies[0], deltaT));
			}
			cd = totalMSec + 500;
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

        for (const auto &element: _game.data._towers) {
            SDL_RenderCopy(renderer(), element->_texture, towerSrcRectMap[element->_type], element->_position);
        }
        for (const auto &element: _enemies) {
			if (element->_isAlive)
				SDL_RenderCopy(renderer(), element->_texture, element->_textureSrcRect, element->_position);
        }

		for (auto &element: _projectiles) {
			if (element->_isVisible)
				SDL_RenderCopy(renderer(), element->_texture, projectileSrcRectMap[element->_texture], element->_position);
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
