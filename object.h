class Plane
{
private:
	int xN;
	int yN;
	int vX;
	int vY;
public:
	Plane(int xX,int yY);
	int xLeft();
	int xRight();
	int yTop();
	int yBottom();
	void UpVLeft();
	void UpVRight();
	void UpVUp();
	void UpVDown();
	void Next();
	void Restart();
	void Show();
};
class Block
{
private:
	int xN;
	int yN;
	int vX;
	int vY;
public:
	Block(int xX,int yY);
	Block();
	int xLeft();
	int xRight();
	int yTop();
	int yBottom();
	void Next();
	void Restart();
	bool CheckHit(Plane p);
	void Show();
};
