#ifndef WORLD
#define WORLD

class World
{	
	private:
		int width;
		int height;
		
	public:
		static Vector center;
		static float fixedTime;
		static float deltaTime;
		static std::list<WorldObject*> worldObjects;
		
		
	public: 
		World(int argWidth, int argHeight)
		{
			width = argWidth;
			height = argHeight;
			center.x = (int)width/2;
			center.y = (int)height/2;
			initwindow(width, height, "2D Physic Engine");
		}
};

#endif

