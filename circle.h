#ifndef CIRCLE
#define CIRCLE

class Circle : public WorldObject
{
	private:
		float radius;
		
	public:
		
		Circle()
		{
			objectType = CircleType;
			ptrChildObject = this;
			World::worldObjects.push_front(this);
			radius = 1;
			SetPosition(World::center.x, World::center.y);
			circle(position.x, position.y, radius);	
		}
		
		Circle(float x, float y, float argRadius)
		{
			objectType = CircleType;
			ptrChildObject = this;
			World::worldObjects.push_front(this);
			radius = argRadius;
			SetPosition(x, y);
			circle(position.x, position.y, radius);
		}
		
		float GetRadius()
		{
			return radius;
		}
		
		void RenderObject()
		{
			circle(position.x, position.y, radius);
		}
		
		void OnCollision()
		{
		}
};
#endif

