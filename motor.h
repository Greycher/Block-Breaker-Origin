#include <chrono>
#include <list>
#include <graphics.h>
#include <math.h> 
#include <stdlib.h>
#include "customlibrary.h"
#include "worldobject.h"
#include "world.h"
#include "circle.h"
#include "rectangle.h"
#include "rigidbody.h"
#include "block.h"

float World::deltaTime = 0.0;
float World::fixedTime = 0.0;
Vector World::center(0.0, 0.0);
std::list<WorldObject*> World::worldObjects{}; 

void BeforeUpdate();

void Update()
{
	bool firstUpdatePassed = false;
	
	std::chrono::time_point<std::chrono::system_clock> start;
	std::chrono::time_point<std::chrono::system_clock> end;
	
	while(true)
	{
		BeforeUpdate();
		
		start = std::chrono::system_clock::now();
		
		World::deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(start - end).count() / 1000.0;
		
		if(firstUpdatePassed)
		{
			std::list<WorldObject*>::iterator woIt = World::worldObjects.begin();
					
			for(int i = 0; i< World::worldObjects.size(); i++)
			{
				WorldObject* ptrWo = (WorldObject*)*woIt;
				Rigidbody* ptrRb = (Rigidbody*)ptrWo->ptrRb;
						
				if(ptrRb != NULL)
				{
					if(ptrRb->bodyType == Dynamic)
					{
						ptrRb->CalculateMotion(World::deltaTime);
					}
				}
					
				std::advance(woIt, 1);
			}
					
			woIt = World::worldObjects.begin();
					
			for(int i = 0; i< World::worldObjects.size(); i++)
			{
				std::advance(woIt, i);
				WorldObject* ptrWo = (WorldObject*)*woIt;
				Rigidbody* ptrRb = (Rigidbody*)ptrWo->ptrRb;
				
				if(ptrRb != NULL)
				{
					if(ptrRb->bodyType == Dynamic)
					{
						woIt = World::worldObjects.begin();
						
						for(int j = 0; j < World::worldObjects.size(); j++)
						{
							if(j == i)
							{
								std::advance(woIt, 1);
								continue;
							}
							
							ptrWo = (WorldObject*)*woIt;
							std::advance(woIt, 1);
							
							if(ptrWo->ptrRb != NULL)
							{
								ptrRb->CollisionDetector(ptrWo);
							}	
						}
					}
				}
						
				woIt = World::worldObjects.begin();
			}
					
			cleardevice();
				
			for(int i = 0; i< World::worldObjects.size(); i++)
			{
				WorldObject* worldObject = *woIt;
				worldObject->RenderObject();
						
				std::advance(woIt, 1);
			}
		}
		
		firstUpdatePassed = true;
		
		end = std::chrono::system_clock::now();	
		
		delay(World::fixedTime * 1000);	
	}
}
	
