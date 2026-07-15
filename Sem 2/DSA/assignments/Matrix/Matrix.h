#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

class Matrix {

private:
	static constexpr double LOAD_FACTOR_THRESHOLD = 0.75;

	static constexpr int PRIMES[] = {11, 23, 47, 97, 199, 409, 823, 1741, 3469, 6949, 14033, 28411, 57557, 116731, 236897, 480217, 974711, 1978207, 4015439, 8150471, 16544927, 33585283, 68175517, 138392131, 280735867, 569601377, 1156519181};
	static constexpr int NO_PRIMES = sizeof(PRIMES) / sizeof(int);
	int primeIndex;

	struct Node{
		int r, c;
		TElem value;
		Node* next;

		Node(int r, int c, int value, Node* next = nullptr);
	};

	int rows, columns;
	int noElements;
	Node** head;
	int capacity;

	TElem a, b;

	void checkCoordinates(int row, int col) const;

	int getRandomInt(int min, int max);

	bool isPrime(int n);
	int getNextCapacity();
	void resize();

	int hash(int i, int j) const;

public:
	//constructor
	Matrix(int nrLines, int nrCols);

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

	//by me
	~Matrix();
};
