#include <iostream>
#include "example_game.hpp"

namespace JanSordid::SDL_Example {

    MyGameState::Projectile::Projectile(Rect * position, Texture * texture, int damage, int velocity) {
        _isVisible = true;
        _position = position;
        _texture = texture;
        _damage = damage;
        _velocity = velocity;
    }

   MyGameState::Tower::Tower(Rect *placement, Texture *texture) {
        _placement = placement;
        _texture = texture;
   }

    MyGameState::Enemy::Enemy(Rect *position, Texture *texture, int hp, int speed) {
        _isAlive = true;
        _position = position;
        _texture = texture;
        _hp = hp;
        _speed = speed;
    }

    void TdState::Init()
    {
        Base::Init();

        if( !bg[0] )
        {
            //SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "best" );

            bg[0] = IMG_LoadTexture( renderer(), BasePathGraphic "bg-layer-4.png" );
            bg[1] = IMG_LoadTexture( renderer(), BasePathGraphic "bg-layer-3.png" );
            bg[2] = IMG_LoadTexture( renderer(), BasePathGraphic "bg-layer-2.png" );
            bg[3] = IMG_LoadTexture( renderer(), BasePathGraphic "bg-layer-1.png" );



            SDL_QueryTexture( bg[0], nullptr, nullptr, &bgSize[0].x, &bgSize[0].y );
            SDL_QueryTexture( bg[1], nullptr, nullptr, &bgSize[1].x, &bgSize[1].y );
            SDL_QueryTexture( bg[2], nullptr, nullptr, &bgSize[2].x, &bgSize[2].y );
            SDL_QueryTexture( bg[3], nullptr, nullptr, &bgSize[3].x, &bgSize[3].y );

            //SDL_SetTextureColorMod( bg[0], 163, 163, 163 );
            //SDL_SetTextureColorMod( bg[1], 191, 191, 191 );
            //SDL_SetTextureColorMod( bg[2], 191, 191, 191 );
            //SDL_SetTextureColorMod( bg[3], 225, 225, 255 );

            //SDL_SetTextureAlphaMod( bg[2], 210 );
            //SDL_SetTextureAlphaMod( bg[3], 127 );

            SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "nearest" );
        }

        if( !enemyPathTile ) {
            enemyPathTile = IMG_LoadTexture( renderer(), BasePathGraphic "/Floor/enemy_path_tile.png" );
        }
        if( !grasTile ) {
            grasTile = IMG_LoadTexture( renderer(), BasePathGraphic "/Floor/grass_tile.png" );
        }
        if( !towerTexture ) {
            towerTexture = IMG_LoadTexture( renderer(), BasePathGraphic "/Archer-Tower/archer_tower_idle.png" );
        }
        if( !enemy ) {
            enemy = IMG_LoadTexture( renderer(), BasePathGraphic "/Enemies/slime_walk.png" );
        }

        for( int i = 0; i < gridHeight; i++ ) {
            for ( int j = 0; j < gridWidth; j++ ) {
                Rect * temp = new Rect(
                    j * tileSize * scalingFactor(),
                    i * tileSize * scalingFactor(),
                    tileSize * scalingFactor(),
                    tileSize * scalingFactor()
                    );
                map[i][j] = temp;
            }
        }

        // Reinit on reenter
        cam = { .x = 0, .y = 0 };

        Rect * temp = new Rect(
            20 * tileSize * scalingFactor(),
            9 * tileSize * scalingFactor(),
            tileSize * scalingFactor(),
            tileSize * scalingFactor()
            );

        Tower tempTower = Tower(temp, towerTexture);
    }

    void TdState::Destroy()
    {
        // TODO

        Base::Destroy();
    }

    bool TdState::HandleEvent(const Event & event )
    {
        if( event.type == SDL_KEYDOWN && event.key.repeat == 0 )
        {
            if( event.key.keysym.scancode == SDL_SCANCODE_F1 ) bgIsVisible[0] = !bgIsVisible[0];
            if( event.key.keysym.scancode == SDL_SCANCODE_F2 ) bgIsVisible[1] = !bgIsVisible[1];
            if( event.key.keysym.scancode == SDL_SCANCODE_F3 ) bgIsVisible[2] = !bgIsVisible[2];
            if( event.key.keysym.scancode == SDL_SCANCODE_F4 ) bgIsVisible[3] = !bgIsVisible[3];

            // Toggle all
            if( event.key.keysym.scancode == SDL_SCANCODE_F5 )
                bgIsVisible[0] = bgIsVisible[1] = bgIsVisible[2] = bgIsVisible[3] = !bgIsVisible[0];

            if( event.key.keysym.scancode == SDL_SCANCODE_F6 ) isInverted = !isInverted;
            if( event.key.keysym.scancode == SDL_SCANCODE_F7 ) isEased    = !isEased;
            if( event.key.keysym.scancode == SDL_SCANCODE_F8 ) isFlux     = !isFlux;

            return true; // Not 100% correct
        }
        else if( (event.type == SDL_MOUSEBUTTONDOWN)
                 || (event.type == SDL_MOUSEMOTION && event.motion.state != 0) )
        {
            Point windowSize;
            SDL_GetWindowSize( window(), &windowSize.x, &windowSize.y );

            const FPoint halfWinSize = toF( windowSize / 2 );
            const FPoint mousePos    = { (float) event.motion.x, (float) event.motion.y };

            mouseOffset = isInverted
                          ? halfWinSize - mousePos
                          : mousePos - halfWinSize;

            return true;
        }
        else if( event.type == SDL_MOUSEBUTTONUP )
        {
            mouseOffset = { 0, 0 };

            return true;
        }
        else
        {
            return false;
        }
    }

    bool TdState::Input()
    {
        const u8 *  key_array = SDL_GetKeyboardState( nullptr );
        const float factor    = key_array[SDL_SCANCODE_RSHIFT]
                                ? 600.f
                                : 80.0f;

        // Reset direction
        dir = { 0, 0 };
        if( key_array[SDL_SCANCODE_LEFT]  ) dir.x += factor;
        if( key_array[SDL_SCANCODE_RIGHT] )	dir.x -= factor;

        if( key_array[SDL_SCANCODE_UP]    ) dir.y += factor;
        if( key_array[SDL_SCANCODE_DOWN]  ) dir.y -= factor;

        return false;
    }

    void TdState::Update(const u64 frame, const u64 totalMSec, const f32 deltaT )
    {
        //cam += dir * deltaT;
/*
	if( isEased )
	{
		SDL_FPoint diff = (mouseOffset - mouseOffsetEased);

		//constexpr const float thresh = 20.0f; // 1.2f;
		//if( -thresh < diff.x && diff.x < thresh ) diff.x = 0;
		//if( -thresh < diff.y && diff.y < thresh ) diff.y = 0;

		//constexpr const float thresh = 2.2f;
		//if( -thresh < diff.x && diff.x < thresh ) { mouseOffsetEased.x = mouseOffset.x; diff.x = 0; }
		//if( -thresh < diff.y && diff.y < thresh ) { mouseOffsetEased.y = mouseOffset.y; diff.y = 0; }

		mouseOffsetEased += diff * max( 0.1f, min( 0.4f, deltaT * 10.0f ) );
	}
	else
	{
		mouseOffsetEased = mouseOffset;
	}*/
    }

    FPoint TdState::CalcFluxCam(const u64 totalMSec ) const
    {
        const FPoint flux = isFlux
                            ? FPoint {
                        .x = (float)sin( totalMSec / 650.0f ) * 5.0f,
                        .y = (float)sin( totalMSec / 500.0f ) * 10.0f
                             + (float)sin( totalMSec / 850.0f ) * 5.0f
                             + (float)cos( totalMSec / 1333.0f ) * 5.0f }
                            : FPoint { 0, 0 };
        const FPoint fluxCam = cam + flux + mouseOffsetEased;
        return fluxCam;
    }

    void TdState::Render(const u64 frame, u64 totalMSec, const f32 deltaT )
    {
        // Try the limits, moments before wraparound
        //totalMSec += 2147470000u + 2147480000u;
        Point windowSize;
        SDL_GetWindowSize( window(), &windowSize.x, &windowSize.y );
        //const FPoint fluxCam = CalcFluxCam( totalMSec );

        for( int i = 0; i <= 3; ++i ) // The 4 layers, rendered back to front
        {
            //RenderLayer( windowSize, cam, i );
        }

        for( int i = 0; i < gridHeight; i++ ) {
            for ( int j = 0; j < gridWidth; j++ ) {

                if( i == gridHeight / 2 ) {
                    SDL_RenderCopy(renderer(), enemyPathTile, EntireRect, map[i][j] );
                }
            }
        }

        for (auto element: _towers) {
            SDL_RenderCopy(renderer(), element._texture, )
        }
    }

    void TdState::RenderLayer(const Point windowSize, const FPoint camPos, const int index ) const
    {
        if( !bgIsVisible[index] )
            return;
        SDL_RenderCopy( renderer(), bg[index], EntireRect, nullptr );
        //const Point size = bgSize[index];
        //const FPoint offset = bgStart[index] + camPos * bgFactor[index];
        //for( float x = offset.x; x < windowSize.x; x += size.x * 2 )
        //{
        //	for( float y = offset.y; y < windowSize.y; y += size.y * 2 )
        //	{
        //		Rect off = { .x = (int)x, .y = (int)y, .w = size.x * 2, .h = size.y * 2 };


        // Makes only sense with texture hint == best
        //FRect offset = { .x = x, .y = y, .w = size.x * 2.0f, .h = size.y * 2.0f };
        //SDL_RenderCopyF( renderer, bg[i], EntireRect, &offset );
        //	}
        //}
    }

} // namespace
