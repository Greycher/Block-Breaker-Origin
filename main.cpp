#include <iostream>
#include <windows.h>
#include "motor.h"

RectangleShape* bouncer;
Circle* ball;
Rigidbody* rbBall;
bool launched = false;

int main()
{
	World world(1200,600);
	
	RectangleShape leftBorder(-10,World::center.y,20,600);
	Rigidbody rbLeftBorder(leftBorder);
	rbLeftBorder.bodyType = Static;
	
	RectangleShape rigthBorder(1210,World::center.y,20,600);
	Rigidbody rbRightBorder(rigthBorder);
	rbRightBorder.bodyType = Static;
	
	RectangleShape topBorder(World::center.x,-10,1200,20);
	Rigidbody rbTopBorder(topBorder);
	rbTopBorder.bodyType = Static;
	
	bouncer = new RectangleShape(World::center.x,560,140,20);
	Rigidbody rbBouncer(*bouncer);
	rbBouncer.bodyType = Static;
	
	ball = new Circle(World::center.x, 540,10);
	rbBall = new Rigidbody(*ball);

	std::list<Block*> blocks;
	std::list<Rigidbody*> rbBlocks;
	
	float posY = 100.0;
	
	for(int i = 0; i < 6; i++)
	{
		float posX = 150.0;
		float width = 50.0;
		float heigth = 20.0;
		
		for(int j = 0; j < 20; j++)
		{
			Block* block = new Block(posX,posY, width,heigth,1);
			Rigidbody* rbBlock= new Rigidbody(*block);
			rbBlock->bodyType = Static;
			
			blocks.push_front(block);
			rbBlocks.push_front(rbBlock);
			
			posX += width;
		}
		
		posY += heigth;
	}
	
	Update();
	
	getch();
	
	return 0;
}

void BeforeUpdate()
{
	POINT cursorPositionLong;
	GetCursorPos(&cursorPositionLong);
	
	Vector cursorPos(0.0,0.0);
	cursorPos.x = cursorPositionLong.x;
	cursorPos.y = cursorPositionLong.y;
	
	Vector ballPos = ball->GetPosition();
	
	if(!launched && GetAsyncKeyState(VK_LBUTTON))
	{
		srand (time(NULL));
		rbBall->SetVelocity(rand() % 1000 - 500, 500);
		launched = true;
	}
	
	Vector bouncerPos = bouncer->GetPosition();
	bouncer->SetPosition(Clamp(cursorPos.x,0 + bouncer->width/2, 1200 -  bouncer->width/2),bouncerPos.y);
	
	if(!launched)
	{
		bouncerPos = bouncer->GetPosition();
		ball->SetPosition(bouncerPos.x, ballPos.y);	
	}
}
