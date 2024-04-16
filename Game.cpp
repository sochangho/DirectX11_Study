#include "pch.h"
#include "Game.h"



Game::Game()
{

}

Game::~Game()
{

}

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;

	_graphics = make_shared<Graphics>(_hwnd);	
	_pipeline = make_shared<Pipeline>(_graphics->GetDeviceContext());

	//GO
	_gameObject = make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());

}

void Game::Update()
{
	_gameObject->Update();

}

void Game::Render()
{
	_graphics->RenderBegin();
	
	//TODO : 랜더링 파이프라인
	//IA - VS - RS - PS - OM
	{		
		_gameObject->Render(_pipeline);
	}
	_graphics->RederEnd();
}








