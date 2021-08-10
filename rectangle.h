#ifndef RECTANGLE
#define RECTANGLE

class RectangleShape : public WorldObject
{
	public:
		
		float width;
		float height;
		
		RectangleShape()
		{
			objectType = RectangleType;
			ptrChildObject = this;
			World::worldObjects.push_front(this);
			position = World::center;
			width = 100;
			height = 100;
			rectangle(position.x - width/2, position.y - height/2, position.x + width/2, position.y + height/2);	
		}
		
		RectangleShape(float posX, float posY, float argWidth, float argHeight)
		{
			objectType = RectangleType;
			ptrChildObject = this;
			World::worldObjects.push_front(this);
			width = argWidth;
			height = argHeight;
			SetPosition(posX, posY);
			rectangle(position.x - width/2, position.y - height/2, position.x + width/2, position.y + height/2);	
		}
		
		void RenderObject()
		{
			rectangle(position.x - width/2, position.y - height/2, position.x + width/2, position.y + height/2);	
		}
		
		void OnCollision()
		{
		}
};

#endif
