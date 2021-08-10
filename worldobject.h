#ifndef WORLDOBJECT
#define WORLDOBJECT

class WorldObject
{
	protected:
		Vector position;
	
	public: 
		void* ptrChildObject;
		void* ptrRb = NULL;
		ObjectType objectType;
		virtual void RenderObject() = 0;
		virtual void OnCollision() = 0;
		
		Vector GetPosition()
		{
			return position;
		}
		
		void SetPosition(float x, float y)
		{
			position.x = x;
			position.y = y;
		}
};

#endif

