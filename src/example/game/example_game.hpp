#pragma once

#include "../global.hpp"

#include <sor/sdl_game.hpp>
#include <sor/sdl_shapeops.hpp>
//#include <autocast_ptr.h>
//#include <sor/tiles.h>

namespace JanSordid::SDL_Example
{
	using namespace JanSordid;
	using namespace JanSordid::SDL;

	class MyGame;
	class MyGameState;

	class IntroState;
	class TdState;
	class OverworldState;

	// MyGameState-Index
	// Why not in the classes themselves? For reusability!
	enum class MyGS : u8
	{
		Intro = 0,
		TdState,
		Overworld,
        Invalid
	};


	// abstract
	class MyGameState : public SDL::GameState<MyGame>
	{
		using Base = GameState;

	public:
		// ctor
		using Base::Base;
        int cash;
	};

	class MyGame final : public SDL::Game<MyGameState,MyGS>
	{
		using Base = Game;

	public:
		MyGame();

		bool HandleEvent( const Event & event ) override;
	};


	class IntroState final : public MyGameState
	{
		using Base = MyGameState;

	protected:
		Owned<Font>    _font        = nullptr;
		Owned<Texture> _image       = nullptr;
		Owned<Music>   _music       = nullptr;
		Owned<Chunk>   _sound       = nullptr;
		Owned<Texture> _blendedText = nullptr;

		Point _blendedTextSize = { 0, 0 };
		u8    _textmode        = 0;

		// Testvars controlled by ImGui
		Point _p             = { 32, 50 };
		int   _colorIndex    = 9;
		bool  _isDarkOutline = true;

		static constexpr const Color white { 255, 255, 255, SDL_ALPHA_OPAQUE };
		static constexpr const Color black {   0,   0,   0, SDL_ALPHA_OPAQUE };

	public:
		/// Ctors & Dtor
		using Base::Base;

		/// Getters & Setters: non-virtual first, followed by (pure) virtual/override
		[[nodiscard]] constexpr Color clearColor() const noexcept override { return Color { 255, 255, 255, SDL_ALPHA_OPAQUE }; }

		/// Methods: non-virtual first, followed by (pure) virtual/override
		void Init()                     override;
		void Enter( bool isStacking )   override;
		void Exit( bool isStackedUpon ) override;
		void Destroy()                  override;

		bool HandleEvent( const Event & event ) override;
		void Update( u64 frame, u64 totalMSec, f32 deltaT ) override;
		void Render( u64 frame, u64 totalMSec, f32 deltaT ) override;
		ImGuiOnly(
			void RenderUI( u64 framesSinceStart, u64 msSinceStart, f32 deltaTNeeded ) override;)
	};

    class TdState : public MyGameState
    {
        using Base = MyGameState;

    protected:
        Texture *    bg[4]      = { nullptr };
        Point        bgSize[4]; // Is initialized in Init()
        const FPoint bgStart[4] = {
                { 0,    -330 },
                { -350, -330 },
                { -450, -900 },
                { -800, -1500 },
        };
        const FPoint bgFactor[4] = {
                { 0.2f, 0.3f },
                { 0.4f, 0.45f },
                { 0.8f, 0.8f },
                { 1.2f, 1.2f },
        };
        bool bgIsVisible[4] = {
                true,
                true,
                true,
                true,
        };
        FPoint mouseOffset      = { 0, 0 };
        FPoint mouseOffsetEased = { 0, 0 };

        bool isInverted = false;
        bool isEased    = true;
        bool isFlux     = true;
        FPoint dir      = { 0, 0 };
        FPoint cam      = { 0, 0 };

    public:
        // ctor
        using Base::Base;

        void Init() override;
        void Destroy() override;

        bool Input() override;
        bool HandleEvent( const Event & event ) override;
        void Update( u64 frame, u64 totalMSec, f32 deltaT ) override;
        void Render( u64 frame, u64 totalMSec, f32 deltaT ) override;

        FPoint CalcFluxCam(const u64 totalMSec) const;
        void RenderLayer( const Point windowSize, const FPoint camPos, const int index) const;
    };

	class OverworldState : public MyGameState
	{
		using Base = MyGameState;

	protected:
		Texture *    bg[4]      = { nullptr };
		Point        bgSize[4]; // Is initialized in Init()
		const FPoint bgStart[4] = {
			{ 0,    -330 },
			{ -350, -330 },
			{ -450, -900 },
			{ -800, -1500 },
		};
		const FPoint bgFactor[4] = {
			{ 0.2f, 0.3f },
			{ 0.4f, 0.45f },
			{ 0.8f, 0.8f },
			{ 1.2f, 1.2f },
		};
		bool bgIsVisible[4] = {
			true,
			true,
			true,
			true,
		};
		FPoint mouseOffset      = { 0, 0 };
		FPoint mouseOffsetEased = { 0, 0 };

		bool isInverted = false;
		bool isEased    = true;
		bool isFlux     = true;
		FPoint dir      = { 0, 0 };
		FPoint cam      = { 0, 0 };

	public:
		// ctor
		using Base::Base;

		void Init() override;
		void Destroy() override;

		bool Input() override;
		bool HandleEvent( const Event & event ) override;
		void Update( u64 frame, u64 totalMSec, f32 deltaT ) override;
		void Render( u64 frame, u64 totalMSec, f32 deltaT ) override;

		FPoint CalcFluxCam(const u64 totalMSec) const;
		void RenderLayer( const Point windowSize, const FPoint camPos, const int index) const;
	};
}
