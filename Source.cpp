/* 2014707040 ������ */

#include <iostream>
#include <cstdlib>
using namespace std;

// Ŭ���� ����

class LifeGame
{
public:
	LifeGame();
	~LifeGame();
	void initialize(int w, int h);
	int getWidth() const;
	int getHeight() const;
	void setState(int i, int j, bool s);
	bool getState(int i, int j) const;
	void clear();
	void update();
	friend ostream& operator <<(ostream& os, const LifeGame& game);

private:
	int width, height;
	bool* current_cells;			// ���ڿ� ���� �� ĭ�� ���� ���¸� �����ϴ� �迭�� ù ���� ����Ű�� ������
	bool* next_cells;				// ���ڿ� ���� �� ĭ�� ���� ���¸� �����ϴ� �迭�� ù ���� ����Ű�� ������
};


// ��� �Լ� ����

LifeGame::LifeGame() : width(0), height(0)			// Default Constructor
{/*intentionally empty.*/
}

LifeGame::~LifeGame()								// Destructor
{
	delete[] current_cells;
	delete[] next_cells;
}

void LifeGame::initialize(int w, int h)				// ���� ���� �迭 ���� �Ҵ� �� �ʱ�ȭ
{
	current_cells = new bool[w*h];
	for (int i = 0; i < w*h; i++)
		*(current_cells + i) = false;
	width = w;
	height = h;
}

int LifeGame::getWidth() const
{
	return width;
}

int LifeGame::getHeight() const
{
	return height;
}

void LifeGame::setState(int i, int j, bool s)		// j��° �� i��° ���� ĭ�� s�� ����
{
	*(current_cells + j*width + i) = s;
}

bool LifeGame::getState(int i, int j) const			// j��° �� i��° ���� ĭ ���¸� ��ȯ
{
	return *(current_cells + j*width + i);
}

void LifeGame::clear()								// ���� ��� ĭ�� ���¸� ����(false)�� ����
{
	for (int i = 0; i < width*height; i++)
		*(current_cells + i) = false;
}

void LifeGame::update()								// ��� ĭ�� ���¸� ���� ���·� ��ȯ
{
	int i, live_cell_num;
	next_cells = new bool[width*height];			// next_cells �迭 �����Ҵ�
	for (i = 0; i < width*height; i++)				// next_cells�� currnet_cells�� ���� ������ �ʱ�ȭ
		*(next_cells + i) = *(current_cells + i);

	for (i = 0; i < width*height; i++)
	{
		live_cell_num = 0;				// ���� ĭ�� ���� ����

		if ((i - width) < 0)					// ù ��° ���� ���
		{
			if (*(current_cells + i + (width * (height - 1))) == true)				// �� ĭ Ȯ��
				live_cell_num += 1;
			if (*(current_cells + i + width) == true)								// �Ʒ� ĭ Ȯ��
				live_cell_num += 1;
			if (i == (width - 1))							// ù ��° �� ������ �� ĭ
			{
				if (*(current_cells + i + (width * (height - 2)) + 1) == true)		// ������ �� ĭ Ȯ��
					live_cell_num += 1;
				if (*(current_cells + i + (1 - width)) == true)						// ������ ĭ Ȯ��
					live_cell_num += 1;
				if (*(current_cells + i + 1) == true)								// ������ �Ʒ� ĭ Ȯ��
					live_cell_num += 1;
				if (*(current_cells + i + (width * (height - 1)) - 1) == true)		// ���� �� ĭ Ȯ��
					live_cell_num += 1;
				if (*(current_cells + i - 1) == true)								// ���� ĭ Ȯ��
					live_cell_num += 1;
				if (*(current_cells + i + width - 1) == true)						// ���� �Ʒ� ĭ Ȯ��
					live_cell_num += 1;
			}
			else if (i == 0)								// ù ��° �� ���� �� ĭ
			{
				if (*(current_cells + i + (width * (height - 1)) + 1) == true)		// ������ �� ĭ Ȯ��
					live_cell_num += 1;
				if (*(current_cells + i + 1) == true)								// ������ ĭ Ȯ��
					live_cell_num += 1;
				if (*(current_cells + i + width + 1) == true)						// ������ �Ʒ� ĭ Ȯ��
					live_cell_num += 1;
				if (*(current_cells + (width * height - 1)) == true)				// ���� �� ĭ Ȯ��
					live_cell_num += 1;
				if (*(current_cells + i + (width - 1)) == true)						// ���� ĭ Ȯ��
					live_cell_num += 1;
				if (*(current_cells + i + (2 * width - 1)) == true)					// ���� �Ʒ� ĭ Ȯ��
					live_cell_num += 1;
			}
			else											// ù ��° �� ��� ĭ
			{
				if (*(current_cells + i + (width * (height - 1)) + 1) == true)		// ������ �� ĭ Ȯ��
					live_cell_num += 1;
				if (*(current_cells + i + 1) == true)								// ������ ĭ Ȯ��
					live_cell_num += 1;
				if (*(current_cells + i + width + 1) == true)						// ������ �Ʒ� ĭ Ȯ��
					live_cell_num += 1;
				if (*(current_cells + i + (width * (height - 1)) - 1) == true)		// ���� �� ĭ Ȯ��
					live_cell_num += 1;
				if (*(current_cells + i - 1) == true)								//����  ĭ Ȯ��
					live_cell_num += 1;
				if (*(current_cells + i + width - 1) == true)						// ���� �Ʒ� ĭ Ȯ��
					live_cell_num += 1;
			}
		}

		else if (i >= (width * (height - 1)))	// ������ ���� ���
		{
			if (*(current_cells + i - width) == true)								// �� ĭ Ȯ��
				live_cell_num += 1;
			if (*(current_cells + i - (width * (height - 1))) == true)				// �Ʒ� ĭ Ȯ��
				live_cell_num += 1;
			if (i == (width * height - 1))					// ������ �� ������ �� ĭ
			{
				if (*(current_cells + i - (2 * width) + 1) == true)					// ������ �� ĭ Ȯ��
					live_cell_num += 1;
				if (*(current_cells + i + (1 - width)) == true)						// ������ ĭ Ȯ��
					live_cell_num += 1;
				if (*current_cells == true)											// ������ �Ʒ� ĭ Ȯ��
					live_cell_num += 1;
				if (*(current_cells + i - width - 1) == true)						// ���� �� ĭ Ȯ��
					live_cell_num += 1;
				if (*(current_cells + i - 1) == true)								// ���� ĭ Ȯ��
					live_cell_num += 1;
				if (*(current_cells + i - (width * (height - 1)) - 1) == true)		// ���� �Ʒ�
					live_cell_num += 1;
			}
			else if (i == (width*(height - 1)))				// ������ �� ���� �� ĭ
			{
				if (*(current_cells + i - width + 1) == true)						// ������ �� ĭ Ȯ��
					live_cell_num += 1;
				if (*(current_cells + i + 1) == true)								// ������ ĭ Ȯ��
					live_cell_num += 1;
				if (*(current_cells + i - (width * (height - 1)) + 1) == true)		// ������ �Ʒ� ĭ Ȯ��
					live_cell_num += 1;
				if (*(current_cells + i - 1) == true)								// ���� �� ĭ Ȯ��
					live_cell_num += 1;
				if (*(current_cells + i + (width - 1)) == true)						// ���� ĭ Ȯ��
					live_cell_num += 1;
				if (*(current_cells + i - (width * (height - 2)) - 1) == true)		// ���� �Ʒ� ĭ Ȯ��
					live_cell_num += 1;
			}
			else											// ������ �� ��� ĭ
			{
				if (*(current_cells + i - width + 1) == true)						// ������ �� ĭ Ȯ��
					live_cell_num += 1;
				if (*(current_cells + i + 1) == true)								// ������ ĭ Ȯ��
					live_cell_num += 1;
				if (*(current_cells + i - (width * (height - 1)) + 1) == true)		// ������ �Ʒ� ĭ Ȯ��
					live_cell_num += 1;
				if (*(current_cells + i - width - 1) == true)						// ���� �� ĭ Ȯ��
					live_cell_num += 1;
				if (*(current_cells + i - 1) == true)								// ���� ĭ Ȯ��
					live_cell_num += 1;
				if (*(current_cells + i - (width * (height - 1)) - 1) == true)		// ���� �Ʒ� ĭ Ȯ��
					live_cell_num += 1;
			}
		}

		else									//  �߰� ���� ���
		{
			if (*(current_cells + i - width) == true)								// �� ĭ Ȯ��
				live_cell_num += 1;
			if (*(current_cells + i + width) == true)								// �Ʒ� ĭ Ȯ��
				live_cell_num += 1;
			if ((i + 1) % width == 0)						// �߰� �� ������ �� ĭ
			{
				if (*(current_cells + i - (2 * width) + 1) == true)					// ������ �� ĭ Ȯ��
					live_cell_num += 1;
				if (*(current_cells + i + (1 - width)) == true)						// ������ ĭ Ȯ��
					live_cell_num += 1;
				if (*(current_cells + i + 1) == true)								// ������ �Ʒ� ĭ Ȯ��
					live_cell_num += 1;
				if (*(current_cells + i - width - 1) == true)						// ���� �� ĭ Ȯ��
					live_cell_num += 1;
				if (*(current_cells + i - 1) == true)								// ���� ĭ Ȯ��
					live_cell_num += 1;
				if (*(current_cells + i + width - 1) == true)						// ���� �Ʒ� ĭ Ȯ��
					live_cell_num += 1;
			}
			else if (i % width == 0)						// �߰� �� ���� �� ĭ
			{
				if (*(current_cells + i - width + 1) == true)						// ������ �� ĭ Ȯ��
					live_cell_num += 1;
				if (*(current_cells + i + 1) == true)								// ������ ĭ Ȯ��
					live_cell_num += 1;
				if (*(current_cells + i + width + 1) == true)						// ������ �Ʒ� ĭ Ȯ��
					live_cell_num += 1;
				if (*(current_cells + i - 1) == true)								// ���� �� ĭ Ȯ��
					live_cell_num += 1;
				if (*(current_cells + i + (width - 1)) == true)						// ���� ĭ Ȯ��
					live_cell_num += 1;
				if (*(current_cells + i + (2 * width - 1)) == true)					// ���� �Ʒ� ĭ Ȯ��
					live_cell_num += 1;
			}
			else											// �߰� �� ��� ĭ
			{
				if (*(current_cells + i - width + 1) == true)						// ������ �� ĭ Ȯ��
					live_cell_num += 1;
				if (*(current_cells + i + 1) == true)								// ������ ĭ Ȯ��
					live_cell_num += 1;
				if (*(current_cells + i + width + 1) == true)						// ������ �Ʒ� ĭ Ȯ��
					live_cell_num += 1;
				if (*(current_cells + i - width - 1) == true)						// ���� �� ĭ Ȯ��
					live_cell_num += 1;
				if (*(current_cells + i - 1) == true)								// ���� ĭ Ȯ��
					live_cell_num += 1;
				if (*(current_cells + i + width - 1) == true)						// ���� �Ʒ� ĭ Ȯ��
					live_cell_num += 1;
			}
		}


		if (*(current_cells + i) == true && live_cell_num <= 1)									// �ڽ��� ���� ����ְ�, ������ 1�� ������ ĭ�� ����ִٸ�,
			*(next_cells + i) = false;															// �״´�.
		else if (*(current_cells + i) == true && live_cell_num >= 4)							// �ڽ��� ���� ����ְ�, ������ 4�� �̻��� ĭ�� ����ִٸ�,
			*(next_cells + i) = false;															// �״´�.
		else if (*(current_cells + i) == true && (live_cell_num == 2 || live_cell_num == 3))	// �ڽ��� ���� ����ְ�, ������ 2~3���� ĭ�� ����ִٸ�,
			*(next_cells + i) = true;															// ��� ���.
		else if (*(current_cells + i) == false && live_cell_num == 3)							// �ڽ��� ���� �׾��ְ�, ������ ��Ȯ�� 3���� ĭ�� ����ִٸ�,
			*(next_cells + i) = true;															// ��Ƴ���.
	}

	for (i = 0; i < width*height; i++)					// next_cells�� ������ ���� current_cells�� ����
		*(current_cells + i) = *(next_cells + i);
}


// friend �Լ� ����

ostream& operator <<(ostream& os, const LifeGame& game)		// ��ü�� cout���� ����ϱ� ���� "<<" Overloading
{
	for (int j = 0; j < game.height; j++)					// j��° ��
	{
		for (int i = 0; i < game.width; i++)				// i��° ��
		{
			if (game.getState(i, j) == true)				// ĭ�� ��������� 0 ���
				os << "O ";
			else											// ĭ�� �׾������� . ���
				os << ". ";
		}
		os << endl;											// j��° ���� �� �� ����ϸ� ����
	}
	return os;
}



// �Ʒ� ������ �������� �� ��

void setBoat(LifeGame& life);
void setToad(LifeGame& life);
void setGlider(LifeGame& life);
void setCross(LifeGame& life);
void setRandom(LifeGame& life);

void main()
{
	int width = 0, height = 0;
	char answer = ' ';

	cout << "Input grid width: ";
	cin >> width;

	cout << "Input grid height: ";
	cin >> height;

	LifeGame life;
	life.initialize(width, height);
	do
	{
		int n, i;

		cout << endl << "[Menu]" << endl;
		cout << "(0) No change\n";
		cout << "(1) Boat\n";
		cout << "(2) Toad\n";
		cout << "(3) Glider\n";
		cout << "(4) Cross\n";
		cout << "(5) Random\n";
		cout << "Select a command (0-5) : ";
		cin >> n;

		switch( n ) {
			case 0:							break;
			case 1:	setBoat( life );		break;
			case 2:	setToad( life );		break;
			case 3:	setGlider( life );		break;
			case 4: setCross( life );		break;
			case 5:	setRandom( life );		break;
			default:						break;
		}

		for( i=0; i < 10; i++ )
		{
			cout << "[" << i << "] generation: " << endl;
			cout << life;
			cout << endl;
			life.update();
		}

		cout << "Continue (Y/N)? ";
		cin >> answer;
	}
	while( answer == 'Y' || answer == 'y' );
}

void setBoat( LifeGame& life )
{
	int w = life.getWidth();
	int h = life.getHeight();

	if( w < 3 || h < 3 )
	{
		return;
	}

	int ci = w / 2;
	int cj = h / 2;

	life.clear();
	life.setState( ci-1, cj, true );
	life.setState( ci+1, cj, true );
	life.setState( ci, cj-1, true );
	life.setState( ci, cj+1, true );
	life.setState( ci-1, cj-1, true );
}

void setToad( LifeGame& life )
{
	int w = life.getWidth();
	int h = life.getHeight();

	if( w < 5 || h < 3 )
	{
		return;
	}

	int ci = w / 2;
	int cj = h / 2;

	life.clear();
	life.setState( ci, cj, true );
	life.setState( ci-1, cj, true );
	life.setState( ci-2, cj, true );
	life.setState( ci, cj-1, true );
	life.setState( ci-1, cj-1, true );
	life.setState( ci+1, cj-1, true );
}

void setGlider( LifeGame& life )
{
	int w = life.getWidth();
	int h = life.getHeight();

	if( w < 3 || h < 3 )
	{
		return;
	}

	int ci = w / 2;
	int cj = h / 2;

	life.clear();
	life.setState( ci-1, cj, true );
	life.setState( ci, cj-1, true );
	life.setState( ci, cj+1, true );
	life.setState( ci-1, cj-1, true );
	life.setState( ci+1, cj-1, true );
}

void setCross( LifeGame& life )
{
	int w = life.getWidth();
	int h = life.getHeight();

	if( w < 3 || h < 3 )
	{
		return;
	}

	int ci = w / 2;
	int cj = h / 2;

	life.clear();
	life.setState( ci, cj, true );
	life.setState( ci-1, cj, true );
	life.setState( ci+1, cj, true );
	life.setState( ci, cj-1, true );
	life.setState( ci, cj+1, true );
}

void setRandom( LifeGame& life )
{
	int w = life.getWidth();
	int h = life.getHeight();
	int num_cells = w * h;
	int num_live_cells = (int)( (float)num_cells * 0.1f );

	life.clear();
	for( int c=0; c < num_live_cells; c++ )
	{
		int i = rand() % w;
		int j = rand() % h;

		life.setState( i, j, true );
	}
}
