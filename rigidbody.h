enum BodyType
{
	Static,
	Dynamic
};

class Rectangle;

class Rigidbody 
{
	private:
		Vector velocity;
		WorldObject* ptrObject;
		
	public:
		float mass;
		float gravityScale;
		BodyType bodyType = Dynamic;
		
		Rigidbody(WorldObject &object)
		{
			ptrObject = &object;
			object.ptrRb = this;
			
			if(object.objectType == CircleType)
			{
				Circle* circle = (Circle*)object.ptrChildObject;
				mass = circle->GetRadius();
			}
			else
			{
				RectangleShape* rectangle = (RectangleShape*)object.ptrChildObject;
				mass = (rectangle->height/2 + rectangle->width/2) / 2;
			}
		}
		
		void SetVelocity(float x, float y)
		{
			velocity.x = x;
			velocity.y = y;
		}
	
		void CalculateMotion(float deltaTime)
		{
			if(velocity.x != 0 | velocity.y != 0)
			{
				Vector pos = ptrObject->GetPosition();
				pos.x += velocity.x * deltaTime;
				pos.y += velocity.y * deltaTime;
				
				ptrObject->SetPosition(pos.x, pos.y);	
			}
		}
		
		void OneUpdateBackwards()
		{
			Vector pos = ptrObject->GetPosition();
			
			pos.x -= velocity.x * World::deltaTime;
			pos.y -= velocity.y * World::deltaTime;
			
			ptrObject->SetPosition(pos.x, pos.y);
		}
		
		void CollisionDetector(WorldObject* ptrOtherObject)
		{
			if(ptrOtherObject == ptrObject)
			{
				return;
			}
			
			if(ptrObject->objectType == CircleType)
			{
				Circle* ptrThisCircle = (Circle *)ptrObject->ptrChildObject;
				
				switch(ptrOtherObject->objectType)
				{
					case CircleType:
					{
						Circle* ptrOtherCircle = (Circle *)ptrOtherObject->ptrChildObject;
						CircleVsCircle(ptrThisCircle, ptrOtherCircle);
						break;
					}
					
					case RectangleType:
					{
						RectangleShape* ptrRect = (RectangleShape*) ptrOtherObject->ptrChildObject;
						RectVsCircle(ptrRect, ptrThisCircle);
						break;
					}
				}
			}
			else
			{
				RectangleShape* ptrThisRect = (RectangleShape*)ptrObject->ptrChildObject;
				
				switch(ptrOtherObject->objectType)
				{
					case RectangleType:
					{
						RectangleShape* ptrOtherRect = (RectangleShape*)ptrOtherObject->ptrChildObject;
						RectvsRect(ptrThisRect, ptrOtherRect);
						break;
					}
						
					case CircleType:
					{
						Circle* ptrCircle = (Circle *)ptrOtherObject->ptrChildObject;
						RectVsCircle(ptrThisRect, ptrCircle);
						break;
					}
				}
			}
		}
		
		void CircleVsCircle(Circle* ptrThisCircle, Circle* ptrOtherCircle)
		{
			Circle acircle1 = *ptrThisCircle;
			Circle acircle2 = *ptrOtherCircle;
			
			if(IsCollidingCircleVsCircle(*ptrThisCircle, *ptrOtherCircle))
			{
				Rigidbody* ptrRb1 = (Rigidbody*)ptrThisCircle->ptrRb;
				Rigidbody* ptrRb2 = (Rigidbody*)ptrOtherCircle->ptrRb;
						
				float deltaTime = World::deltaTime;
						
				do
				{
					ptrRb1->OneUpdateBackwards();
					ptrRb2->OneUpdateBackwards();
						
					ptrRb1->CalculateMotion(deltaTime);
					ptrRb2->CalculateMotion(deltaTime);
							
					deltaTime /= 1.05;
				}while(IsCollidingCircleVsCircle(*ptrThisCircle, *ptrOtherCircle));
				
				ResolveCollision(ptrRb1, ptrRb2);
			}
		}
		
		bool IsCollidingCircleVsCircle(Circle circle1, Circle circle2)
		{
			float sumRadius = circle1.GetRadius() + circle2.GetRadius();
			Vector pos1 = circle1.GetPosition();
			Vector pos2 = circle2.GetPosition();
			float distance = Distance(pos1, pos2);
			return sumRadius > distance;
		}
		
		void RectvsRect(RectangleShape* ptrThisRect, RectangleShape* ptrOtherRect)
		{
			if(IsCollidingRectVsRect(*ptrThisRect, *ptrOtherRect))
			{
				Rigidbody* ptrRb1 = (Rigidbody*)ptrThisRect->ptrRb;
				Rigidbody* ptrRb2 = (Rigidbody*)ptrOtherRect->ptrRb;
						
				float deltaTime = World::deltaTime;
						
				do
				{
					ptrRb1->OneUpdateBackwards();
					ptrRb2->OneUpdateBackwards();
						
					ptrRb1->CalculateMotion(deltaTime);
					ptrRb2->CalculateMotion(deltaTime);
							
					deltaTime /= 1.05;
				}while(IsCollidingRectVsRect(*ptrThisRect, *ptrOtherRect));
				
				ResolveCollision(ptrRb1, ptrRb2);
			}
		}
		
		bool IsCollidingRectVsRect(RectangleShape rect1, RectangleShape rect2)
		{
			Vector pos1 = rect1.GetPosition();
			Vector pos2 = rect2.GetPosition();
			
			Vector min1(pos1.x - rect1.width/2, pos1.y - rect1.height/2);
		  	Vector max1(pos1.x + rect1.width/2, pos1.y + rect1.height/2);
		  	
		  	Vector min2(pos2.x - rect2.width/2, pos2.y - rect2.height/2);
		  	Vector max2(pos2.x + rect2.width/2, pos2.y + rect2.height/2);
		  	
			if(max1.x < min2.x | min1.x > max2.x)
			{
				return false;
			}
			if(max1.y < min2.y | min1.y > max2.y)
			{
				return false;
			}
			
		  	return true;
		}
		
		void RectVsCircle(RectangleShape* ptrRect, Circle* ptrCircle)
		{
			if(IsCollidingRectVsCircle(*ptrRect, *ptrCircle))
			{
				Rigidbody* ptrRb1 = (Rigidbody*)ptrRect->ptrRb;
				Rigidbody* ptrRb2 = (Rigidbody*)ptrCircle->ptrRb;
						
				float deltaTime = World::deltaTime;
						
				do
				{
					ptrRb1->OneUpdateBackwards();
					ptrRb2->OneUpdateBackwards();
						
					ptrRb1->CalculateMotion(deltaTime);
					ptrRb2->CalculateMotion(deltaTime);
							
					deltaTime /= 1.05;
				}while(IsCollidingRectVsCircle(*ptrRect, *ptrCircle));
				
				if(ptrObject->objectType == CircleType) ResolveCollision(ptrRb2, ptrRb1);
				else ResolveCollision(ptrRb1, ptrRb2);
			}
		}
		
		bool IsCollidingRectVsCircle(RectangleShape rect, Circle circle)
		{
			Vector circlePos = circle.GetPosition();
			Vector rectPos = rect.GetPosition();
			
			float closestX = Clamp(circlePos.x, rectPos.x - rect.width/2, rectPos.x + rect.width/2);
			float closestY = Clamp(circlePos.y, rectPos.y - rect.height/2, rectPos.y + rect.height/2);
			
			Vector closestPos(closestX, closestY);
			
			float distance = Distance(closestPos, circlePos);
			float radius = circle.GetRadius();
			
			return radius > distance;
		}
		
		void ResolveCollision(Rigidbody* ptrRb1, Rigidbody* ptrRb2)
		{
			if(ptrRb2->bodyType == Dynamic)
			{
				float mass1 = ptrRb1->mass;
				float mass2 = ptrRb2->mass;
				float sumMass = mass1 + mass2;
			
				Vector velocity1 = ptrRb1->velocity;
				Vector velocity2 = ptrRb2->velocity;	
							
				ptrRb1->velocity.x = (mass1*velocity1.x + mass2*(2*velocity2.x - velocity1.x)) / sumMass;
				ptrRb1->velocity.y = (mass1*velocity1.y + mass2*(2*velocity2.y - velocity1.y)) / sumMass;
				
				ptrRb2->velocity.x = (mass2*velocity2.x + mass1*(2*velocity1.x - velocity2.x)) / sumMass;
				ptrRb2->velocity.y = (mass2*velocity2.y + mass1*(2*velocity1.y - velocity2.y)) / sumMass;
			}
			else
			{
				if(ptrRb2->ptrObject->objectType == RectangleType )
				{
					RectangleShape* ptrRect = (RectangleShape*)ptrRb2->ptrObject;
					WorldObject* ptrThisObject = ptrRb1->ptrObject;
					
					Vector rectPos = ptrRect->GetPosition();
					Vector thisPos = ptrThisObject->GetPosition();
					
					if(thisPos.y > rectPos.y + ptrRect->height/2 | thisPos.y < rectPos.y - ptrRect->height/2)
					{
						velocity.y *= -1;
						
						srand (time(NULL));
						velocity.x += rand() % 300 - 150;
						velocity.x = Clamp(velocity.x, -500, 500);
					}
					else if(thisPos.x > rectPos.x | thisPos.x < rectPos.x)
					{
						velocity.x *= -1;
					}
				}
			}
			
			ptrRb1->ptrObject->OnCollision();
			ptrRb2->ptrObject->OnCollision();
		}
};
