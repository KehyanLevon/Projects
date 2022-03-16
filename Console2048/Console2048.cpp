#include <iostream>
#include <vector>
#include <cstdlib>
#include <conio.h>
using namespace std;
vector<vector<vector<int>>> undoRedo;
int position = 0;
vector<vector<int>> creatMatrix(int size)
{
	vector<vector<int>> matrix;
	for (int i = 0; i < size; ++i)
	{
		vector<int> lineTemp;
		for (int j = 0; j < size; ++j)
		{
			lineTemp.push_back(0);
		}
		matrix.push_back(lineTemp);
	}
	return matrix;
}
void printMatrix(int size, vector<vector<int>> matrix)
{
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}
void left(int size, vector<vector<int>>& matrix)
{
	for (int i = 0; i < size; i++) 
	{
		int k = -1;
		for (int j = 0; j < size; ++j)//2 0 2 4
		{
			if (matrix[i][j] != 0)
			{
				if (matrix[i][j] != 0 && k == -1)
				{
					k = j;
				}
				else if ((k != -1 && matrix[i][j] == matrix[i][k]) && j != k)
				{
					matrix[i][k] *= 2;
					matrix[i][j] = 0;
					k = -1;
				}
				else if ((k != -1 && matrix[i][j] != matrix[i][k]) && j != k)
				{
					k = j;
				}
			}
		}
		for (int j = 0; j < size; j++)
		{
			if (matrix[i][j] != 0)
			{
				int x = j;
				while (x != 0)
				{
					if (matrix[i][x - 1] == 0)
					{
						matrix[i][x - 1] = matrix[i][x];
						matrix[i][x] = 0;
					}
					--x;
				}
			}
		}
	}
}
void right(int size, vector<vector<int>>& matrix)
{
	for (int i = 0; i < size; ++i)
	{
		int k = -1;
		for (int j = size - 1; j >= 0; --j)
		{
			if (matrix[i][j] != 0)
			{
				if (matrix[i][j] != 0 && k == -1)
				{
					k = j;
				}
				else if (k != -1 && k != j && matrix[i][j] == matrix[i][k])
				{
					matrix[i][k] *= 2;
					matrix[i][j] = 0;
					k = -1;
				}
				else if (k != -1 && k != j && matrix[i][j] != matrix[i][k])
				{
					k = j;
				}
			}
		}
		int m = 0;
		for (int j = 0; j < size; j++)
		{
			if (matrix[i][j] == 0)
			{
				for (int k = j; k > m; k--)
				{
					swap(matrix[i][k], matrix[i][k - 1]);
				}
				++m;
			}
		}
	}
}
void up(int size, vector<vector<int>>& matrix)
{
	for (int j = 0; j < size ; ++j)
	{
		int k = -1;
		for (int i = 0; i < size; ++i)
		{
			if (matrix[i][j] != 0)
			{
				if (matrix[i][j] != 0 && k == -1)
				{
					k = i;
				}
				else if (k != -1 && i != k && matrix[i][j] == matrix[k][j])
				{
					matrix[k][j] *= 2;
					matrix[i][j] = 0;
					k = -1;
				}
				else if (k != -1 && i != k && matrix[i][j] != matrix[k][j])
				{
					k = i;
				}
			}
		}
		for (int i = 0; i < size; ++i)
		{
			int y = i;
			while (y > 0) {
				if (matrix[y - 1][j] == 0) {

					matrix[y - 1][j] = matrix[y][j];
					matrix[y][j] = 0;
				}
				y--;
			}
		}
	}
}
void down(int size, vector<vector<int>>& matrix)
{
	for (int j = 0; j < size; ++j)
	{
		int k = -1;
		for (int i = size - 1; i >= 0; --i)
		{
			if (matrix[i][j] != 0)
			{
				if (matrix[i][j] != 0 && k == -1)
				{
					k = i;
				}
				else if (k != -1 && i != k && matrix[i][j] == matrix[k][j])
				{
					matrix[k][j] *= 2;
					matrix[i][j] = 0;
					k = -1;
				}
				else if (k != -1 && i != k && matrix[i][j] != matrix[k][j])
				{
					k = i;
				}
			}
		}
		for (int i = size - 2; i >= 0; --i) {

			if (matrix[i][j] > 0) {

				int y = i;
				while (y < size - 1) {

					if (matrix[y + 1][j] == 0) {

						matrix[y + 1][j] = matrix[y][j];
						matrix[y][j] = 0;
					}
					y++;
				}
			}
		}
	}
}
bool gameOver(int size, vector<vector<int>> matrix)
{
    bool isZero = true;
    bool isZeroElem = false;
    for(int i = 0; i < size; ++i)
	{
	    for(int j = 0; j < size; ++j)
	    {
	        if(matrix[i][j]!=0)
	        {
	            isZero = false;
	        }
	        else
	        {
	            isZeroElem = true;
	        }
	    }
	}
	if(isZero)
	{
	    return false;
	}
	vector<vector<int>> tmp = matrix;
	left(size, tmp);
	if (matrix == tmp && !isZeroElem)
	{
		tmp = matrix;
		up(size, tmp);
		if (matrix == tmp)
		{
		    return true;
		}
	}
	return false;
}
void randomGeneration(int size, vector<vector<int>>& matrix)
{
	int randRow = rand() % size;
	int randColumn = rand() % size;
	if(!gameOver(size, matrix))
	{
		if (matrix[randRow][randColumn] != 0)
		{
			while (matrix[randRow][randColumn] != 0)
			{
				randRow = rand() % size;
				randColumn = rand() % size;
			}
			((rand() % size + 1) % 2) == 0 ? matrix[randRow][randColumn] = 2 : matrix[randRow][randColumn] = 4;
		}
		else
		{
			((rand() % size + 1) % 2) == 0 ? matrix[randRow][randColumn] = 2 : matrix[randRow][randColumn] = 4;
		}
	}
}
bool victory(int size, vector<vector<int>>& matrix)
{
    for(int i = 0; i < size; ++i)
    {
        for(int j = 0; j < size; ++j)
        {
            if(matrix[i][j] == 2048)
            {
                return true;
            }
        }
    }
    return false;
}
int main()
{
	vector<vector<int>> matrix;
	int size;
	cout << "Input size for your game:";
	cin >> size;
	matrix = creatMatrix(size);
	
	/*     -----------------GAME-------------------    */
	randomGeneration(size, matrix);
	printMatrix(size,matrix);
	char move = ' ';
	while(move != 'q' && !gameOver(size,matrix) && !victory(size,matrix))
	{
	    cout << "which way will you choose?:";
	    cin >> move;
	    if(move == 'd')
	    {
	        if(position != undoRedo.size())
	        {
	            undoRedo.erase(undoRedo.begin() + position, undoRedo.end());
	        }
	        vector<vector<int>> tmp = matrix;
	        right(size,matrix);
	        if(matrix == tmp)
	        {
	            cout<<"Choose another way:";
	            continue;
	        }
	        ++position;
	    }
	    else if(move == 'a')
	    {
	        if(position != undoRedo.size())
	        {
	            undoRedo.erase(undoRedo.begin() + position, undoRedo.end());
	        }
	        vector<vector<int>> tmp = matrix;
	        left(size,matrix);
	        if(matrix == tmp)
	        {
	            continue;
	        }
	        ++position;
	    }
	    else if(move == 's')
	    {
	        if(position != undoRedo.size())
	        {
	            undoRedo.erase(undoRedo.begin() + position, undoRedo.end());
	        }
	        vector<vector<int>> tmp = matrix;
	        down(size,matrix);
	        if(matrix == tmp)
	        {
	            continue;
	        }
	        ++position;
	    }
	    else if(move == 'w')
	    {
	        if(position != undoRedo.size())
	        {
	            undoRedo.erase(undoRedo.begin() + position, undoRedo.end());
	        }
	        vector<vector<int>> tmp = matrix;
	        up(size,matrix);
	        if(matrix == tmp)
	        {
	            continue;
	        }
	        ++position;
	    }
	    else if(move == 'u' && position > 0)
	    {
	        --position;
	        matrix = undoRedo[position];
	        printMatrix(size,matrix);
	        continue;
	    }
	    else if(move == 'r' && position < undoRedo.size())
	    {
	        ++position;
	        matrix = undoRedo[position];
	        printMatrix(size,matrix);
	        continue;
	    }
	    randomGeneration(size,matrix);
	    printMatrix(size,matrix);
	    undoRedo.push_back(matrix);
	}
	
}
/*
{ 1,2,3,4 }     {0, 4, 2, 0}     {1,2,3,4}       {0,0,4,2}
{ 5,6,7,8 }      {0, 2, 4, 2}     {5,6,7,8}       {0,0,2,4}
{ 9,10,11,12 }   {2, 2, 2, 2}     {9,10,11,12}    {0,0,0,8}
{ 13,14,15,16 }  {2, 0, 2, 4}     {13,14,15,16}   {0,0,2,4}
*/