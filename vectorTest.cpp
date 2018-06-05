#include <iostream>
#include <vector>

typedef std::vector<int> IntVec;
typedef std::vector<std::vector<int>> Matrix;

void printMatrix(Matrix &printThis)
{
	for(int i=0;i < printThis.size();i++)
	{
		for(int j=0;j < printThis.at(i).size(); j++)
		{
			std::cout << printThis.at(i).at(j);
		}
		std::cout << std::endl;
	}
}

void fillMatrix(Matrix &fillThis, IntVec &fillFrom, int rows, int col, int fillSize)
{
	IntVec row_tmp;
	std::cout << "Rows: " << rows << std::endl;
	std::cout << "Columns: " << col << std::endl;
	
	//int fillSize = fillFrom.size();
	std::cout << "\n\nfillFrom Size: " << fillSize << std::cout << "\n\n";
	
	for(int i=0;i<fillSize;i)
	{
		std::cout << "\nI Value: " << i << std::endl;
		int secondLoopMax = i+col;
		for(int j=i; j < secondLoopMax; j++)
		{
			std::cout << "Value: " << fillFrom.at(j) << std::endl;
			row_tmp.push_back(fillFrom.at(j));
			i+=j;
		}
	}
}

void print_vec(IntVec &print_this)
{
    for(int i=0;i<print_this.size();i++)
        std::cout << print_this.at(i) << std::endl;
}

void fillVec(IntVec &fillThis, int fillTo)
{
    for(int i=0;i<fillTo;i++)
        fillThis.push_back(i);
}

void printSize(IntVec &checkThis)
{
	std::cout << "Size of vector: " << checkThis.size() << std::endl;
}

int main()
{
    IntVec m_vec;
    IntVec new_vec;
    fillVec(new_vec, 9);
    Matrix m_mat;
    
    fillVec(m_vec, 9);
    int size=9;
    fillMatrix(m_mat, m_vec, 3, 3, size);
    
    printMatrix(m_mat);
    
    printSize(m_vec);
    
    print_vec(m_vec);
    
    return 0;
}
