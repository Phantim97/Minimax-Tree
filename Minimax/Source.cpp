#include <iostream>
#include <Bits.h>
#include <ctime>

#define MAX MAXINT
#define MIN -MAXINT

// Assembly code to derive depth function is in Depth_.asm
extern "C" int Depth_(int nodeCount);

class InvalidInputException
{
public:
	void getErrorMessage() { std::cout << "Invalid input try again.\n"; }
};

int minimax(int *nodes, int depth, int alpha, int beta, int index, bool maximizer)
{
	
	if (depth == 0)
	{
		return nodes[index]; 
	}

	if (maximizer) // maximizing player
	{
		int max_eval = MIN;

		for (int i = 0 ; i < 2; i++)
		{
			int eval = minimax(nodes, depth - 1, alpha, beta, (index * 2) + i, false); // minimizing player's turn

			max_eval = max(max_eval, eval);
			alpha = max(alpha, max_eval);

			if (beta <= alpha)
			{
				break;
			}
		}
	
		return max_eval;
	}
	else // minimizing player
	{
		int min_eval = MAX;
		for (int i = 0; i < 2; i++)
		{
			int eval = minimax(nodes, depth - 1, alpha, beta, (index * 2) + i, true); // maximizing player's turn

			min_eval = min(min_eval, eval);
			beta = min(beta, min_eval);

			if (beta <= alpha)
			{
				break;
			}
		}
		return min_eval;
	}
}

int main()
{
	srand(time(0));
	int nodeCount = 0;
	// User inputs node count 
	do
	{
		std::cout << "Enter the amount of leaf nodes present: ";

		try
		{
			std::cin >> nodeCount;
			if (std::cin.fail())
			{
				throw InvalidInputException();
			}

			if (nodeCount == 0)
			{
				std::cout << "Node count cannot be 0\n";
			}
			if (nodeCount < 0)
			{
				std::cout << "Node count cannot be negative.\n";
			}
			if (nodeCount > 1000000)
			{
				std::cout << "Too much heap space, enter a smaller number\n";
			}
		}
		catch (InvalidInputException e)
		{
			e.getErrorMessage();
			std::cin.clear();
			std::cin.ignore(999999, '\n');
		}
		
	}
	while (nodeCount <= 0 || nodeCount > 1000000);
	system("cls");

	std::cout << "Node Count: " << nodeCount << '\n';
	int *nodes = new int[nodeCount];
	
	//Populate node array
	for (int i = 0; i < nodeCount; i++)
	{
		nodes[i] = rand() % 10;
		// Randomize negative or positive
		if (rand() % 2 == 0)
		{
			nodes[i] = -nodes[i];
		}
	}

	for (int i = 0; i < nodeCount; i++)
	{
		std::cout << nodes[i] << " ";
		if (i % 20 == 0 && i != 0)
		{
			std::cout << '\n';
		}
	}

	std::cout << '\n';

	int depth = Depth_(nodeCount); //asm function

	std::cout << "Depth: " << depth << '\n';
	std::cout << "Ideal leaf: " << minimax(nodes, depth, MIN, MAX, 0, true) << '\n';

	delete[] nodes;

	system("pause");
	return 0;
}