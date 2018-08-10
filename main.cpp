#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
#include <Windows.h>

bool isPrime(int n)		//Check if the given number is a prime number
{
	bool toReturn = false;
	bool primeFlag = false;

	if (n == 1)
	{
		primeFlag = false;
	}

	else if (n == 2)
	{
		primeFlag = true;
	}

	else
	{
		for (int i = 2; i < sqrt(n); i++)
		{
			if (n % i == 0)
			{
				primeFlag = false;
				break;
			}

			else
			{
				primeFlag = true;
			}
		}
	}

	if (primeFlag)
	{
		toReturn = true;
	}

	else
	{
		toReturn = false;
	}

	return toReturn;
}

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
	int size = 800;
	int gridSize = size * size;
	int pointsIndex = 0;
	int xLocVal = 0;
	int xLoc = xLocVal;
	int yLoc = 0;
	int midRow = (size % 2 == 0 ? size / 2 : (size - 1) / 2);
	int midCol = (size % 2 == 0 ? (size / 2) - 1 : (size - 1) / 2);
	int ulamCount = 2;
	int spacesToGo = 0;
	int numberOfSteps = 1;
	int sign = 1;
	int timesCompleted = 0;
	int signSwapCount = 1;
	bool doRow = false;

	std::vector< std::vector<int> > ulamArr(size, std::vector<int>(size));
	std::vector< std::vector<bool> > primeArr(size, std::vector<bool>(size));

	sf::VertexArray points(sf::Points, gridSize);
	sf::RenderWindow window(sf::VideoMode(800, 800), "Ulam Spiral");

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			ulamArr[i][j] = 0;
		}
	}

	ulamArr[midRow][midCol] = 1;

	while (spacesToGo < (size * 2) - 2)
	{
		for (int i = 0; i < numberOfSteps; i++)
		{
			if (doRow)
			{
				midRow += sign;
				ulamArr[midRow][midCol] = ulamCount;
				ulamCount++;
			}

			else
			{
				midCol += sign;
				ulamArr[midRow][midCol] = ulamCount;
				ulamCount++;
			}
		}

		timesCompleted++;

		if(doRow)
		{
			doRow = false;
		}

		else
		{
			doRow = true;
		}

		if(signSwapCount == 1)
		{
			sign *= -1;
			signSwapCount = 0;
		}

		if(timesCompleted == 2)
		{
			numberOfSteps++;
			timesCompleted = 0;
			signSwapCount++;
		}

		spacesToGo++;
	}

	if(size % 2 == 0)
	{
		for(int i = size - 2; i >= 0; i--)
		{
			ulamArr[0][i] = ulamArr[0][i + 1] + 1;
		}
	}

	else
	{
		for(int i = 1; i < size; i++)
		{
			ulamArr[size - 1][i] = ulamArr[size - 1][i - 1] + 1;
		}
	}

	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			if(isPrime(ulamArr[i][j]))
			{
				points[pointsIndex].color = sf::Color::Green;
				points[pointsIndex].position.x = xLoc;
				points[pointsIndex].position.y = yLoc;
			}

			else
			{
				points[pointsIndex].color = sf::Color::Black;
				points[pointsIndex].position.x = xLoc;
				points[pointsIndex].position.y = yLoc;
			}

			xLoc += 1;
			pointsIndex++;
		}

		yLoc += 1;
		xLoc = xLocVal;
	}

	//Main draw loop

	while(window.isOpen())
	{
		sf::Event event;

		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(points);
		window.display();
	}

	return 0;
}