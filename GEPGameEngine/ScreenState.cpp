#pragma once

#include "ScreenState.h"
#include "Game.h"

void ScreenState::Render()
{
	SDL_RenderPresent(Game::Instance()->GetRenderer());

}

void ScreenState::RenderFont(bool isRefreshText, const char *text, int x, int y)
{

	if (isRefreshText)
	{
		SDL_Color textColor = { 255,255,255,0 };
		SDL_Surface * fontSurface = TTF_RenderText_Solid(gFont, text, textColor);

		SDL_DestroyTexture(m_pFontTexture); 
		m_pFontTexture = SDL_CreateTextureFromSurface(Game::Instance()->GetRenderer(), fontSurface);
		m_rFontRect = { x,y,fontSurface->w,fontSurface->h };

	}

	SDL_RenderCopy(Game::Instance()->GetRenderer(), m_pFontTexture, 0, &m_rFontRect);

}

void ScreenState::setPtsFontColor(SDL_Color c) {
	ptsFontColor = c;
}