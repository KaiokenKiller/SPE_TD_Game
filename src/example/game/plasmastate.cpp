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
                         Rect **towerIconSrc, Texture **towerIconTextures) {
        _position = position;
        _texture = texture;
        _textureSrcRect = new Rect(0, 0, 62, 61);

        for (int i = 0; i < 3; ++i) {
            _towerIconSrc[i] = towerIconSrc[i];
            _towerIconTextures[i] = towerIconTextures[i];
        }
        _towerIconPosition[0] = new Rect(_position->x - 32, _position->y - 64 - 16, 32, 64);
        _towerIconPosition[1] = new Rect(_position->x + ((_position->w / 2) - 16), _position->y - 64 - 16, 32, 64);
        _towerIconPosition[2] = new Rect(_position->x + _position->w, _position->y - 64 - 16, 32, 64);
    }

    Tower *TowerSlot::placeTower(Tower::TowerType towerType, std::unordered_map<Tower::TowerType, Texture *> projectileTextures) {
        if (!_used) {
                _used = true;
                Rect *towerPosition = new Rect(_position->x - 4, _position->y - 66, 70, 130);
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

    void Enemy::move(const f32 deltaT) {
        if (!_isAlive || _currentPath >= _path.size()) return;

        int movement = static_cast<int>(deltaT * 100.0f * _speed);

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

    void Projectile::move(const f32 deltaT) {
        if (_isVisible) {
            _position->x += _direction.x * deltaT * _speed;
            _position->y += _direction.y * deltaT * _speed;

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
        }
        if (!archerTowerArrowTexture) {
            archerTowerArrowTexture = IMG_LoadTexture(
                renderer(), BasePathGraphic "/Archer-Tower/archer_tower_arrow.png");
        }
        if (!mageTowerTexture) {
            mageTowerTexture = IMG_LoadTexture(renderer(), BasePathGraphic "/Mage-Tower/mage_tower.png");
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

        // Read map from file
        std::ifstream file(BasePath "asset/map/map2");
        std::string line;

        if (file.is_open()) {
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
                            62 / 1.5 * scalingFactor(),
                            62 / 1.5 * scalingFactor()
                        );

                        auto *tempTowerSlot = new TowerSlot(tempRect, towerSlotTexture, towerIconSrc, towerIconTexture);
                        _towerSlots.push_back(tempTowerSlot);
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

            //auto *tempTower = new Archer1(tempRect, archerTowerTexture, archerTowerArrowTexture);
            //_game.data._towers.push_back(tempTower);

            tempRect = new Rect(
                25 * tileSize * scalingFactor(),
                11 * tileSize * scalingFactor(),
                towerWidth / 1.5 * scalingFactor(),
                towerHeight / 1.5 * scalingFactor()
            );

            //auto *tempMageTower = new Mage1(tempRect, mageTowerTexture, mageTowerOrbTexture);
            //_game.data._towers.push_back(tempMageTower);

            tempRect = new Rect(
                15 * tileSize * scalingFactor(),
                11 * tileSize * scalingFactor(),
                towerWidth / 1.5 * scalingFactor(),
                towerHeight / 1.5 * scalingFactor()
            );

            //auto *tempCatapultTower = new Catapult1(tempRect, catapultTowerTexture, catapultTowerStoneTexture);
            //_game.data._towers.push_back(tempCatapultTower);



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

            tempRect = new Rect(
                _mapPathStart.second * tileSize * scalingFactor(),
                _mapPathStart.first * tileSize * scalingFactor(),
                46,
                46
            );

            auto *tempEnemy = new Enemy(tempRect, enemyTexture, _mapPath, 50, 2);
            _enemies.push_back(tempEnemy);

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
											Tower *newTower = towerSlot->placeTower(towerType, projectileTextureMap);
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

        // Most basic enemy spawner copied from Jan
        if( respawnCD < totalMSec ) {
            Rect *tempRect = new Rect(
                _mapPathStart.second * tileSize * scalingFactor(),
                _mapPathStart.first * tileSize * scalingFactor(),
                46,
                46
            );
            auto *tempEnemy = new Enemy(tempRect, enemyTexture, _mapPath, 50, 2);
            _enemies.push_back(tempEnemy);

            respawnCD = totalMSec + 2000;
        }

        for (auto projectile: _projectiles) {
            projectile->move(deltaT);
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
            enemy->move(deltaT);
            // temporary for testing
            if (!enemy->_isAlive) {
                //Vector<FPoint> path;
                //path.push_back(FPoint(40 * tileSize * scalingFactor(), 0));

                enemy->_position->x = _mapPathStart.second;
                enemy->_position->y = _mapPathStart.first;
                enemy->_path = _mapPath;
                enemy->_currentPath = 0;
                enemy->_isAlive = true;
                enemy->_hp = 50;
            }
        }

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
