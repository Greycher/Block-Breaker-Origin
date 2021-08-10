
class Block : public RectangleShape
{
	private:
		
		int health;
		
	public:
		
		Block(float posX, float posY, float argWidth, float argHeight, int argHealth)
		: RectangleShape(posX, posY, argWidth, argHeight)
		{
			health = argHealth;
		}
		
		void OnCollision()
		{
			World::worldObjects.remove(this);
			delete (Rigidbody*)ptrRb;
			delete this;		 
		}
};
