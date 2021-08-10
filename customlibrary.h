#ifndef CUSTOMLIBRARY
#define CUSTOMLIBRARY

struct Vector
{
    float x;
    float y;
    
    public:
    	
    	Vector()
		{
    		x = 0.0;
    		y = 0.0;
		}
		
		Vector(float argX, float argY)
		{
			x = argX;
			y = argY;
		}
};

enum ObjectType
{
	CircleType,
	RectangleType
};

float Distance(Vector vector1, Vector vector2)
{
	return sqrt(pow(abs(vector1.x - vector2.x), 2) + pow(abs(vector1.y - vector2.y), 2));
}

float Clamp(float val, float min, float max) 
{
    return std::max(min, std::min(max, val));
}

Vector VectorNorm(Vector vector)
{
	Vector origin(0.0,0.0);
	float length = Distance(origin,vector);
	vector.x /= length;
	vector.y /= length;
	return vector;
}

#endif

