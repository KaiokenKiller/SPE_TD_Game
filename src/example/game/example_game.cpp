#include "example_game.hpp"

namespace JanSordid::SDL_Example
{
	constexpr bool doBenchmark = true;

	MyGame::MyGame()
		: Base( "Example SDL Game", -1.0f, Point { 640, 360 }, !doBenchmark )
	//	: Base( "Example SDL Game", 1.0f, Point { 1280, 960 }, !doBenchmark )
	{
		AddStates<
			IntroState,
			TdState,
			OverworldState>(*this );

		// Set initial State
		PushState( MyGS::Intro );

		IfNotFinal
			SetPerfDrawMode( PerformanceDrawMode::Title );
	}

	bool MyGame::HandleEvent( const Event & event )
	{
		// Global Keybindings, will be checked before the ones in GameState
		if( Base::HandleEvent( event ) )
			return true;

		switch( event.type )
		{
			case SDL_KEYDOWN:
			{
				const Keysym & what_key = event.key.keysym;

				if( what_key.scancode == SDL_SCANCODE_1 )
				{
					// Both Game and GameState can change the State,
					// but it will only be changed after the current frame
					ReplaceState( MyGS::Intro );
					return true;
				}
				else if( what_key.scancode == SDL_SCANCODE_2 )
				{
					ReplaceState( MyGS::TdState );
					return true;
				}
				else if( what_key.scancode == SDL_SCANCODE_3 )
				{
					ReplaceState( MyGS::Overworld );
					return true;
				}
				break;
			}

			default:
				break;
		}

		return false;
	}
}


extern "C"
int main( int argc, char * argv [] )
{
	using namespace JanSordid;

	try
	{
		std::ios_base::sync_with_stdio( false );

		SDL_Example::MyGame game;
		return game.Run();
	}
	catch( ... )
	{
		Core::print( "Non-SDL Exception has occurred!\n" );

		// put a breakpoint in this line, to prevent the shell from closing
		return 667;
	}
}
