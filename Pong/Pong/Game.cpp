#pragma once
#include "Game.h"

const int thickness = 15;
const float paddleH = 100.0f;

Game::Game()
	:mWindow(nullptr)
	,mRenderer(nullptr)
	,mIsRunning(true)
	,mTicksCount(0)
	,mPaddleDir(0)
	,mPaddle2Dir(0)
{

}

bool Game::Initialize()
{
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);

	if (sdlResult != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());

		return false;
	}

	mWindow = SDL_CreateWindow(
		"Game Programming in C++ (Chapter 1)", // Window Title
		100, //Top left x-coordinate of window
		100, //Top left y-coordinate of window
		1024, // Width of window
		768, // Height of window
		0 // Flag (0 for no flags set)
	);

	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());

		return false;
	}

	mRenderer = SDL_CreateRenderer(
		mWindow, //WIndow to create renderer for
		-1, // Usually -1
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC

	);

	if (!mRenderer)
	{
		SDL_Log("Failed to Create Renderer: %s", SDL_GetError());

		return false;
	}

	mBallPos.x = 1024.0f / 2.0f;
	mBallPos.y = 768.0f / 2.0f;

	mPaddlePos.x = 10.0f;
	mPaddlePos.y = 768.0f / 2.0f;

	mPaddle2Pos.x = 1024.0f - thickness;
	mPaddle2Pos.y = 768.0f / 2.0f;

	mBallVel.x = -200.0f;
	mBallVel.y = 235.0f;

	return true;

}

void Game::Shutdown()
{
	SDL_DestroyWindow(mWindow);

	SDL_DestroyRenderer(mRenderer);

	SDL_Quit();

}

void Game::RunLoop()
{

	while (mIsRunning)
	{
		ProcessInput();

		UpdateGame();

		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	SDL_Event event;

	//While there are still events in the queue

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			// Handle different event types here

		case SDL_QUIT:

			mIsRunning = false;
			break;

		}
	}

	// Get state of keyboard

	const Uint8* state = SDL_GetKeyboardState(NULL);

	// If escape is pressed, also end loop

	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

	mPaddleDir = 0;
	mPaddle2Dir = 0;

	if (state[SDL_SCANCODE_W])
	{
		mPaddleDir -= 1;
	}

	if (state[SDL_SCANCODE_S])
	{
		mPaddleDir += 1;
	}

	if (state[SDL_SCANCODE_I])
	{
		mPaddle2Dir -= 1;
	}

	if (state[SDL_SCANCODE_K])
	{
		mPaddle2Dir += 1;
	}
}

void Game::UpdateGame()
{
	// Wait until 16ms have elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;

	// Delta time is the difference in ticks from last frame
	// (converted to seconds by dividing by 1000.f)

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

	// Clamp maximum delta time value
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	// Update ticks counts (for next frame)
	mTicksCount = SDL_GetTicks();

	// Update paddle position based on direction
	if (mPaddleDir != 0)
	{
		mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;

		// Make sure paddle doesn't move off screen!
		if (mPaddlePos.y < (paddleH / 2.0f + thickness))
		{
			mPaddlePos.y = paddleH / 2.0f + thickness;
		}

		else if (mPaddlePos.y > (768.0f - paddleH / 2.0f - thickness))
		{
			mPaddlePos.y = 768.0f - paddleH / 2.0f - thickness;
		}
	}

	//Update paddle 2 position based on direction
	if (mPaddle2Dir != 0)
	{
		mPaddle2Pos.y += mPaddle2Dir * 300.0f * deltaTime;

		// Make sure paddle doesn't move off screen!
		if (mPaddle2Pos.y < (paddleH / 2.0f + thickness))
		{
			mPaddle2Pos.y = paddleH / 2.0f + thickness;
		}

		else if (mPaddle2Pos.y > (768.0f - paddleH / 2.0f - thickness))
		{
			mPaddle2Pos.y = 768.0f - paddleH / 2.0f - thickness;
		}
	}

	// Update position of the ball
	mBallPos.x += mBallVel.x * deltaTime;
	mBallPos.y += mBallVel.y * deltaTime;

	if (mBallPos.y <= thickness && mBallVel.y < 0.0f)
	{
		mBallVel.y *= -1;
	}

	if (mBallPos.y >= 768 - thickness && mBallVel.y > 0.0f)
	{
		mBallVel.y *= -1;
	}

	if (mBallPos.x > 1024 - thickness && mBallVel.x > 0.0f)
	{
		mBallVel.x *= -1;
	}

	float diff1 = mBallPos.y - mPaddlePos.y;

	//Take absolute value of difference
	diff1 = (diff1 > 0.0f) ? diff1 : -diff1;

	if (
		// Our y-difference is small enough
		diff1 <= paddleH / 2.0f &&
		//Ball is at the correct x-position
		mBallPos.x <= 25.0f && mBallPos.x >= 20.f &&
		//The ball is moving to the left
		mBallVel.x < 0.0f)
	{
		mBallVel.x *= -1.0f;
	}

	float diff2 = mBallPos.y - mPaddle2Pos.y;

	diff2 = (diff2 > 0.0f) ? diff2 : -diff2;

	if (
		diff2 <= paddleH / 2.0f &&
		mBallPos.x <= 1024 - 20.0f && mBallPos.x >= 20.f &&
		mBallVel.x > 0.0f)
	{
		mBallVel.x *= -1.0f;
	}
	

}

void Game::GenerateOutput()
{


	SDL_SetRenderDrawColor(
		mRenderer,
		0, // Red
		0, // Green
		255, // Blue
		255 // Alpha
	);

	SDL_RenderClear(mRenderer);

	SDL_SetRenderDrawColor(mRenderer, 255, 0, 255, 255);

	// Top Wall
	SDL_Rect wall{
		0, // Top left x
		0, // Top left y
		1024, // Width
		thickness // Height
	};
	SDL_RenderFillRect(mRenderer, &wall);

	// Bottom Wall
	wall.y = 768 - thickness;
	SDL_RenderFillRect(mRenderer, &wall);

	//Right Wall
	/*wall.w = thickness;
	wall.h = 1024;
	wall.y = 0;
	wall.x = 1024 - thickness;
	SDL_RenderFillRect(mRenderer, &wall);*/ //removed for exercise

	SDL_Rect ball{
		static_cast<int>(mBallPos.x - thickness / 2),
		static_cast<int>(mBallPos.y - thickness / 2),
		thickness,
		thickness
	};

	SDL_RenderFillRect(mRenderer, &ball);

	SDL_Rect paddle{
		static_cast<int>(mPaddlePos.x),
		static_cast<int>(mPaddlePos.y - paddleH / 2),
		thickness,
		static_cast<int>(paddleH)
	};
	SDL_RenderFillRect(mRenderer, &paddle);

	//Put in as exercise 1.1
	SDL_Rect paddle2{
		static_cast<int>(mPaddle2Pos.x),
		static_cast<int>(mPaddle2Pos.y - paddleH / 2),
		thickness,
		static_cast<int>(paddleH)
	};
	SDL_RenderFillRect(mRenderer, &paddle2);

	SDL_RenderPresent(mRenderer);
}