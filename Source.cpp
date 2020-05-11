/* 2014707040 유진혁 */

#include <iostream>
#include <cstdlib>
using namespace std;

// 클래스 선언

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
	bool* current_cells;			// 격자에 속한 각 칸의 현재 상태를 저장하는 배열의 첫 원소 가르키는 포인터
	bool* next_cells;				// 격자에 속한 각 칸의 다음 상태를 저장하는 배열의 첫 원소 가르키는 포인터
};


// 멤버 함수 정의

LifeGame::LifeGame() : width(0), height(0)			// Default Constructor
{/*intentionally empty.*/
}

LifeGame::~LifeGame()								// Destructor
{
	delete[] current_cells;
	delete[] next_cells;
}

void LifeGame::initialize(int w, int h)				// 현재 상태 배열 동적 할당 및 초기화
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

void LifeGame::setState(int i, int j, bool s)		// j번째 행 i번째 열의 칸을 s로 설정
{
	*(current_cells + j*width + i) = s;
}

bool LifeGame::getState(int i, int j) const			// j번째 행 i번째 열의 칸 상태를 반환
{
	return *(current_cells + j*width + i);
}

void LifeGame::clear()								// 현재 모든 칸의 상태를 죽음(false)로 설정
{
	for (int i = 0; i < width*height; i++)
		*(current_cells + i) = false;
}

void LifeGame::update()								// 모든 칸의 상태를 다음 상태로 변환
{
	int i, live_cell_num;
	next_cells = new bool[width*height];			// next_cells 배열 동적할당
	for (i = 0; i < width*height; i++)				// next_cells를 currnet_cells와 같은 값으로 초기화
		*(next_cells + i) = *(current_cells + i);

	for (i = 0; i < width*height; i++)
	{
		live_cell_num = 0;				// 주위 칸의 상태 저장

		if ((i - width) < 0)					// 첫 번째 행인 경우
		{
			if (*(current_cells + i + (width * (height - 1))) == true)				// 위 칸 확인
				live_cell_num += 1;
			if (*(current_cells + i + width) == true)								// 아래 칸 확인
				live_cell_num += 1;
			if (i == (width - 1))							// 첫 번째 행 오른쪽 끝 칸
			{
				if (*(current_cells + i + (width * (height - 2)) + 1) == true)		// 오른쪽 위 칸 확인
					live_cell_num += 1;
				if (*(current_cells + i + (1 - width)) == true)						// 오른쪽 칸 확인
					live_cell_num += 1;
				if (*(current_cells + i + 1) == true)								// 오른쪽 아래 칸 확인
					live_cell_num += 1;
				if (*(current_cells + i + (width * (height - 1)) - 1) == true)		// 왼쪽 위 칸 확인
					live_cell_num += 1;
				if (*(current_cells + i - 1) == true)								// 왼쪽 칸 확인
					live_cell_num += 1;
				if (*(current_cells + i + width - 1) == true)						// 왼쪽 아래 칸 확인
					live_cell_num += 1;
			}
			else if (i == 0)								// 첫 번째 행 왼쪽 끝 칸
			{
				if (*(current_cells + i + (width * (height - 1)) + 1) == true)		// 오른쪽 위 칸 확인
					live_cell_num += 1;
				if (*(current_cells + i + 1) == true)								// 오른쪽 칸 확인
					live_cell_num += 1;
				if (*(current_cells + i + width + 1) == true)						// 오른쪽 아래 칸 확인
					live_cell_num += 1;
				if (*(current_cells + (width * height - 1)) == true)				// 왼쪽 위 칸 확인
					live_cell_num += 1;
				if (*(current_cells + i + (width - 1)) == true)						// 왼쪽 칸 확인
					live_cell_num += 1;
				if (*(current_cells + i + (2 * width - 1)) == true)					// 왼쪽 아래 칸 확인
					live_cell_num += 1;
			}
			else											// 첫 번째 행 가운데 칸
			{
				if (*(current_cells + i + (width * (height - 1)) + 1) == true)		// 오른쪽 위 칸 확인
					live_cell_num += 1;
				if (*(current_cells + i + 1) == true)								// 오른쪽 칸 확인
					live_cell_num += 1;
				if (*(current_cells + i + width + 1) == true)						// 오른쪽 아래 칸 확인
					live_cell_num += 1;
				if (*(current_cells + i + (width * (height - 1)) - 1) == true)		// 왼쪽 위 칸 확인
					live_cell_num += 1;
				if (*(current_cells + i - 1) == true)								//왼쪽  칸 확인
					live_cell_num += 1;
				if (*(current_cells + i + width - 1) == true)						// 왼쪽 아래 칸 확인
					live_cell_num += 1;
			}
		}

		else if (i >= (width * (height - 1)))	// 마지막 행인 경우
		{
			if (*(current_cells + i - width) == true)								// 위 칸 확인
				live_cell_num += 1;
			if (*(current_cells + i - (width * (height - 1))) == true)				// 아래 칸 확인
				live_cell_num += 1;
			if (i == (width * height - 1))					// 마지막 행 오른쪽 끝 칸
			{
				if (*(current_cells + i - (2 * width) + 1) == true)					// 오른쪽 위 칸 확인
					live_cell_num += 1;
				if (*(current_cells + i + (1 - width)) == true)						// 오른쪽 칸 확인
					live_cell_num += 1;
				if (*current_cells == true)											// 오른쪽 아래 칸 확인
					live_cell_num += 1;
				if (*(current_cells + i - width - 1) == true)						// 왼쪽 위 칸 확인
					live_cell_num += 1;
				if (*(current_cells + i - 1) == true)								// 왼쪽 칸 확인
					live_cell_num += 1;
				if (*(current_cells + i - (width * (height - 1)) - 1) == true)		// 왼쪽 아래
					live_cell_num += 1;
			}
			else if (i == (width*(height - 1)))				// 마지막 행 왼쪽 끝 칸
			{
				if (*(current_cells + i - width + 1) == true)						// 오른쪽 위 칸 확인
					live_cell_num += 1;
				if (*(current_cells + i + 1) == true)								// 오른쪽 칸 확인
					live_cell_num += 1;
				if (*(current_cells + i - (width * (height - 1)) + 1) == true)		// 오른쪽 아래 칸 확인
					live_cell_num += 1;
				if (*(current_cells + i - 1) == true)								// 왼쪽 위 칸 확인
					live_cell_num += 1;
				if (*(current_cells + i + (width - 1)) == true)						// 왼쪽 칸 확인
					live_cell_num += 1;
				if (*(current_cells + i - (width * (height - 2)) - 1) == true)		// 왼쪽 아래 칸 확인
					live_cell_num += 1;
			}
			else											// 마지막 행 가운데 칸
			{
				if (*(current_cells + i - width + 1) == true)						// 오른쪽 위 칸 확인
					live_cell_num += 1;
				if (*(current_cells + i + 1) == true)								// 오른쪽 칸 확인
					live_cell_num += 1;
				if (*(current_cells + i - (width * (height - 1)) + 1) == true)		// 오른쪽 아래 칸 확인
					live_cell_num += 1;
				if (*(current_cells + i - width - 1) == true)						// 왼쪽 위 칸 확인
					live_cell_num += 1;
				if (*(current_cells + i - 1) == true)								// 왼쪽 칸 확인
					live_cell_num += 1;
				if (*(current_cells + i - (width * (height - 1)) - 1) == true)		// 왼쪽 아래 칸 확인
					live_cell_num += 1;
			}
		}

		else									//  중간 행인 경우
		{
			if (*(current_cells + i - width) == true)								// 위 칸 확인
				live_cell_num += 1;
			if (*(current_cells + i + width) == true)								// 아래 칸 확인
				live_cell_num += 1;
			if ((i + 1) % width == 0)						// 중간 행 오른쪽 끝 칸
			{
				if (*(current_cells + i - (2 * width) + 1) == true)					// 오른쪽 위 칸 확인
					live_cell_num += 1;
				if (*(current_cells + i + (1 - width)) == true)						// 오른쪽 칸 확인
					live_cell_num += 1;
				if (*(current_cells + i + 1) == true)								// 오른쪽 아래 칸 확인
					live_cell_num += 1;
				if (*(current_cells + i - width - 1) == true)						// 왼쪽 위 칸 확인
					live_cell_num += 1;
				if (*(current_cells + i - 1) == true)								// 왼쪽 칸 확인
					live_cell_num += 1;
				if (*(current_cells + i + width - 1) == true)						// 왼쪽 아래 칸 확인
					live_cell_num += 1;
			}
			else if (i % width == 0)						// 중간 행 왼쪽 끝 칸
			{
				if (*(current_cells + i - width + 1) == true)						// 오른쪽 위 칸 확인
					live_cell_num += 1;
				if (*(current_cells + i + 1) == true)								// 오른쪽 칸 확인
					live_cell_num += 1;
				if (*(current_cells + i + width + 1) == true)						// 오른쪽 아래 칸 확인
					live_cell_num += 1;
				if (*(current_cells + i - 1) == true)								// 왼쪽 위 칸 확인
					live_cell_num += 1;
				if (*(current_cells + i + (width - 1)) == true)						// 왼쪽 칸 확인
					live_cell_num += 1;
				if (*(current_cells + i + (2 * width - 1)) == true)					// 왼쪽 아래 칸 확인
					live_cell_num += 1;
			}
			else											// 중간 행 가운데 칸
			{
				if (*(current_cells + i - width + 1) == true)						// 오른쪽 위 칸 확인
					live_cell_num += 1;
				if (*(current_cells + i + 1) == true)								// 오른쪽 칸 확인
					live_cell_num += 1;
				if (*(current_cells + i + width + 1) == true)						// 오른쪽 아래 칸 확인
					live_cell_num += 1;
				if (*(current_cells + i - width - 1) == true)						// 왼쪽 위 칸 확인
					live_cell_num += 1;
				if (*(current_cells + i - 1) == true)								// 왼쪽 칸 확인
					live_cell_num += 1;
				if (*(current_cells + i + width - 1) == true)						// 왼쪽 아래 칸 확인
					live_cell_num += 1;
			}
		}


		if (*(current_cells + i) == true && live_cell_num <= 1)									// 자신이 현재 살아있고, 주위에 1개 이하의 칸만 살아있다면,
			*(next_cells + i) = false;															// 죽는다.
		else if (*(current_cells + i) == true && live_cell_num >= 4)							// 자신이 현재 살아있고, 주위에 4개 이상의 칸이 살아있다면,
			*(next_cells + i) = false;															// 죽는다.
		else if (*(current_cells + i) == true && (live_cell_num == 2 || live_cell_num == 3))	// 자신이 현재 살아있고, 주위에 2~3개의 칸이 살아있다면,
			*(next_cells + i) = true;															// 계속 산다.
		else if (*(current_cells + i) == false && live_cell_num == 3)							// 자신이 현재 죽어있고, 주위에 정확히 3개의 칸이 살아있다면,
			*(next_cells + i) = true;															// 살아난다.
	}

	for (i = 0; i < width*height; i++)					// next_cells에 보관된 값을 current_cells로 복사
		*(current_cells + i) = *(next_cells + i);
}


// friend 함수 정의

ostream& operator <<(ostream& os, const LifeGame& game)		// 객체를 cout으로 출력하기 위한 "<<" Overloading
{
	for (int j = 0; j < game.height; j++)					// j번째 행
	{
		for (int i = 0; i < game.width; i++)				// i번째 열
		{
			if (game.getState(i, j) == true)				// 칸이 살아있으면 0 출력
				os << "O ";
			else											// 칸이 죽어있으면 . 출력
				os << ". ";
		}
		os << endl;											// j번째 행의 열 다 출력하면 개행
	}
	return os;
}



// 아래 내용은 수정하지 말 것

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
