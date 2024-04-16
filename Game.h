#pragma once

#include"GameObject.h"

class Game
{
public:
	Game();
	~Game();

public:
	void Init(HWND hwnd);
	void Update();
	void Render();



private:
	HWND _hwnd;	
	shared_ptr<Graphics> _graphics = nullptr;
	shared_ptr<Pipeline> _pipeline = nullptr;

	shared_ptr<GameObject> _gameObject;
private :
	


};

