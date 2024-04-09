#include <string>
#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>

using namespace std;

class level {
private:
	int** mapPtr;
	unsigned width;
	unsigned height;
	int RanIndex;
public:

int getElement(int a, int b)
{
	return *(*(mapPtr + b) + a);
}

void setSize(unsigned w, unsigned h)
{
	width = w;
	height = h;
}
//0 - simple mode
//1 - spiral mode
void mapGenerating(int mode)
{
	mapPtr = new int* [height]();
	for (unsigned i = 0; i < width; i++)
		*(mapPtr + i) = new int[width]();	

	int N = width * height;

	int x = width/2;
	int y = height/2;

	int left = x;
	int right = x;
	int top = y;
	int bottom = y;

	int count = 0;

	int dir = 0;
	switch (mode) {
	case 0:
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{

				int top_index = 6;
				int left_index = 6;
				int right_index = 6;
				int bottom_index = 6;

				if (i > 0) {
					top_index = *(*(mapPtr + j) + i - 1);
				}

				if (j > 0) {
					left_index = *(*(mapPtr + j - 1) + i);
				}


				*(*(mapPtr + j) + i) = ruleCheck(top_index, bottom_index, left_index, right_index);
			}
		}
		break;
	case 1:
		while (count < N) {
			int top_index = 6;
			int left_index = 6;
			int right_index = 6;
			int bottom_index = 6;

			//проход слева направо
			switch (dir)
			{
			case 0:
				for (int i = top; i <= bottom; i++) {
					if (top > 0) {
						top_index = *(*(mapPtr + i - 1) + left);
					}
					right_index = *(*(mapPtr + i) + left + 1);

					*(*(mapPtr + i) + left) = ruleCheck(top_index, bottom_index, left_index, right_index);
					count++;
				}
				bottom++;
				dir++;
				break;
			case 1:
				for (int i = left; i <= right; i++) {
					if (left > 0) {
						left_index = *(*(mapPtr + bottom) + i - 1);
					}
					top_index = *(*(mapPtr + bottom - 1) + i);
					*(*(mapPtr + bottom) + i) = ruleCheck(top_index, bottom_index, left_index, right_index);
					count++;
				}
				right++;
				dir++;
				break;
			case 2:
				for (int i = bottom; i >= top; i--) {
					left_index = *(*(mapPtr + i) + right - 1);
					if (bottom < height) {
						bottom_index = *(*(mapPtr + i - 1) + right);
					}
					*(*(mapPtr + i) + right) = ruleCheck(top_index, bottom_index, left_index, right_index);
					count++;
				}
				top--;
				dir++;
				break;
			case 3:
				for (int i = right; i >= left; i--) {
					if (right < width) {
						right_index = *(*(mapPtr + top) + i + 1);
					}
					bottom_index = *(*(mapPtr + top + 1) + i);
					*(*(mapPtr + top) + i) = ruleCheck(top_index, bottom_index, left_index, right_index);
					count++;
				}
				left--;
				dir++;
				break;
			default:
				break;
			}
			dir = dir % 4;
		}
		break;
	default:
		break;
	}
}

int ruleCheck(int top_id = 6, int bottom_id = 6, int left_id = 6, int right_id = 6)
{
	//Cписок возможных тайлов
	//0 - лес
	//1 - трава
	//2 - густая трава
	//3 - земля
	//4 - песок
	//5 - вода
	int A[6] = { 0, 1, 2, 3, 4, 5 };
	int tyle_index = 0;

	switch (left_id)
	{
	case 0:
		A[1] = 6;
		A[3] = 6;
		A[4] = 6;
		A[5] = 6;
		break;
	case 1:
		A[0] = 6;
		A[5] = 6;
		break;
	case 2:
		A[4] = 6;
		A[5] = 6;
		break;
	case 3:
		A[0] = 6;
		A[4] = 6;
		A[5] = 6;
		break;
	case 4:
		A[0] = 6;
		A[2] = 6;
		A[3] = 6;
		break;
	case 5:
		A[0] = 6;
		A[1] = 6;
		A[2] = 6;
		A[3] = 6;
		break;
	default:
		break;
	}

	switch (right_id)
	{
	case 0:
		A[1] = 6;
		A[3] = 6;
		A[4] = 6;
		A[5] = 6;
		break;
	case 1:
		A[0] = 6;
		A[5] = 6;
		break;
	case 2:
		A[4] = 6;
		A[5] = 6;
		break;
	case 3:
		A[0] = 6;
		A[4] = 6;
		A[5] = 6;
		break;
	case 4:
		A[0] = 6;
		A[2] = 6;
		A[3] = 6;
		break;
	case 5:
		A[0] = 6;
		A[1] = 6;
		A[2] = 6;
		A[3] = 6;
		break;
	default:
		break;
	}

	switch (top_id)
	{
	case 0:
		A[1] = 6;
		A[3] = 6;
		A[4] = 6;
		A[5] = 6;
		break;
	case 1:
		A[0] = 6;
		A[5] = 6;
		break;
	case 2:
		A[4] = 6;
		A[5] = 6;
		break;
	case 3:
		A[0] = 6;
		A[4] = 6;
		A[5] = 6;
		break;
	case 4:
		A[0] = 6;
		A[2] = 6;
		A[3] = 6;
		break;
	case 5:
		A[0] = 6;
		A[1] = 6;
		A[2] = 6;
		A[3] = 6;
		break;
	default:
		break;
	}

	switch (bottom_id)
	{
	case 0:
		A[1] = 6;
		A[3] = 6;
		A[4] = 6;
		A[5] = 6;
		break;
	case 1:
		A[0] = 6;
		A[5] = 6;
		break;
	case 2:
		A[4] = 6;
		A[5] = 6;
		break;
	case 3:
		A[0] = 6;
		A[4] = 6;
		A[5] = 6;
		break;
	case 4:
		A[0] = 6;
		A[2] = 6;
		A[3] = 6;
		break;
	case 5:
		A[0] = 6;
		A[1] = 6;
		A[2] = 6;
		A[3] = 6;
		break;
	default:
		break;
	}

	do
	{
		tyle_index = A[rand() % 6];
	} while (tyle_index == 6);
	
	return tyle_index;
}

void killMap()
{
	for (unsigned i = 0; i < height; i++)
	{
		delete[] mapPtr[i];
	}
	delete[] mapPtr;
}

};

int main()
{
	srand(time(0));

	//Загрузка текстур
	sf::Texture trees;
	trees.create(30, 30);
	trees.loadFromFile("tyles/full/trees.png", sf::IntRect(0, 0, 20, 20));

	sf::Texture grass;
	grass.create(30, 30);
	grass.loadFromFile("tyles/full/grass.png", sf::IntRect(0, 0, 20, 20));

	sf::Texture grass_dark;
	grass_dark.create(30, 30);
	grass_dark.loadFromFile("tyles/full/grass_dark.png", sf::IntRect(0, 0, 20, 20));

	sf::Texture ground;
	ground.create(30, 30);
	ground.loadFromFile("tyles/full/ground.png", sf::IntRect(0, 0, 20, 20));

	sf::Texture sand;
	sand.create(30, 30);
	sand.loadFromFile("tyles/full/sand.png", sf::IntRect(0, 0, 20, 20));

	sf::Texture sea;
	sea.create(30, 30);
	sea.loadFromFile("tyles/full/sea.png", sf::IntRect(0, 0, 20, 20));

	//Создание спрайтов поверхности
	sf::Sprite tr_sprite;
	tr_sprite.setTexture(trees);

	sf::Sprite grs_sprite;
	grs_sprite.setTexture(grass);

	sf::Sprite grs_drk_sprite;
	grs_drk_sprite.setTexture(grass_dark);

	sf::Sprite grnd_sprite;
	grnd_sprite.setTexture(ground);

	sf::Sprite snd_sprite;
	snd_sprite.setTexture(sand);

	sf::Sprite sea_sprite;
	sea_sprite.setTexture(sea);
	
	//Генерация карты x на y тайлов
	level lvl;
	lvl.setSize(47, 47);
	lvl.mapGenerating(1);
	
	sf::RenderWindow window(sf::VideoMode(798, 799), "tile generator");
	
	//Рендер окна
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		//Рендер тайлов карты
		for (int i = 0; i < 47; i++)
		{
			for (int j = 0; j < 47; j++)
			{
				switch (lvl.getElement(j, i))
				{
				case 0:
					tr_sprite.setPosition(sf::Vector2f(i * 17, j * 17));
					window.draw(tr_sprite);
					break;
				case 1:
					grs_sprite.setPosition(sf::Vector2f(i * 17, j * 17));
					window.draw(grs_sprite);
					break;
				case 2:
					grs_drk_sprite.setPosition(sf::Vector2f(i * 17, j * 17));
					window.draw(grs_drk_sprite);
					break;
				case 3:
					grnd_sprite.setPosition(sf::Vector2f(i * 17, j * 17));
					window.draw(grnd_sprite);
					break;
				case 4:
					snd_sprite.setPosition(sf::Vector2f(i * 17, j * 17));
					window.draw(snd_sprite);
					break;
				case 5:
					sea_sprite.setPosition(sf::Vector2f(i * 17, j * 17));
					window.draw(sea_sprite);
					break;
				default:
					break;
				}
			}
		}
		window.display();
	}
	lvl.killMap();

	return 0;
}