#include <iostream>
#include "Game.h"
#include "MainMenuState.h"

using namespace std;

Game* Game::Instance()
{
	static Game* instance = new Game();
	return instance;
}

// h�m kh?i t?o 
bool Game::Init(const char* title, const int xPos, const int yPos, const int width, const int height, const int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		cout << "SDL Initialization successful\n";

		sdlWindow = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
		if (sdlWindow == nullptr)
		{
			cout << "Window initialization failed.\n";
			return false;
		}
		cout << "Window successfully created.\n";
		sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, 0);
		if (sdlRenderer == nullptr)
		{
			cout << "renderer initialization failed.\n";
			return false;
		}
	}
	else
	{
		cout << "SDL Initialization failed\n";
		return false;
	}

	if (Mix_Init(MIX_INIT_MP3) == 0) 
	{
		cout << "Mixer init failed\n";
		return false;
	}
	else
	{
		Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096);
		Mix_AllocateChannels(16);
	
	}

	if (TTF_Init() == 0) 
	{
		cout << "Font init success!\n";
	}
	else
	{
		cout << "Font init fail!\n";
		return false;
	}


	m_iKeystates = SDL_GetKeyboardState(nullptr);
	isAppRunning = true;

	m_pFSM = new StateMachine();
	m_pFSM->ChangeState(new MainMenuState());

	return true;
}


// load ?nh 
SDL_Texture* Game::LoadTexture(const char* path)
{
	SDL_Surface *surface = IMG_Load(path);
	return SDL_CreateTextureFromSurface(sdlRenderer, surface);

}


bool Game::IsRunning()
{
	return isAppRunning; // return n?u ?ang ch?y 
}

// ktra tr?ng th�i ph�m 
bool Game::KeyDown(SDL_Scancode c)
{
	if (m_iKeystates == nullptr)
		return false;

	if (m_iKeystates[c] == 1)
		return true;
	else return false;
}

bool Game::KeyUp(SDL_Scancode c)
{
	if (m_iKeystates == nullptr)
		return false;

	if (m_iKeystates[c] == 0)
		return true;
	else return false;
}


// C?p nh?t tr?ng th�i State machine 
void Game::Update()
{

	GetFSM()->Update();
}

//X? l� s? ki?n trong h�ng ??i
void Game::HandleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			isAppRunning = false;
			break;
	
		case SDL_MOUSEMOTION:
			SDL_GetMouseState(&m_iMouseX, &m_iMouseY);
			break;

		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
				m_bLeftMouse = true;
			break;

		case SDL_MOUSEBUTTONUP:
		{
			if (event.button.button == SDL_BUTTON_LEFT)
				m_bLeftMouse = false;
		}
		break;

		}
	}
}

// V? k?t xu?t 
void Game::Render()
{
	GetFSM()->Render();
}

// gi?i ph�ng d?n d?p 
void Game::Clean()
{
	cout << "Cleaning up and shutting down engine...\n";
	SDL_DestroyWindow(sdlWindow);
	SDL_DestroyRenderer(sdlRenderer);

	TTF_Quit();

	Mix_CloseAudio();
	Mix_Quit();
	IMG_Quit();

	SDL_Quit();

}


