#include <iostream>
using namespace std;

class MyString
{
public:

	MyString(MyString&& SecondString) noexcept
		: ptr{ SecondString.ptr },
		size{ SecondString.size }
	{
		SecondString.ptr = nullptr;
	}

	// Copy Assignment
	MyString& operator=(const MyString& SecondString) noexcept
	{
		if (!(this == &SecondString))
		{
			if (SecondString.ptr == nullptr)
			{
				ptr = nullptr;
				size = SecondString.size;
				return *this;
			}
			if (ptr != nullptr)
			{
				this->~MyString();
			}
			ptr = new char[strlen(SecondString.ptr) + 1];
			strcpy_s(ptr, strlen(SecondString.ptr) + 1, SecondString.ptr);
			size = SecondString.size;
		}
		return *this;
	}

	// Default constructor
	MyString()
	{
		size = 80;
		ptr = new char[size + 1];
		StringCount++;
	};

	// Constructor with constant string parameter
	MyString(const char* SecondString)
	{
		size = strlen(SecondString);
		ptr = new char[size + 1];
		strcpy_s(ptr, strlen(SecondString) + 1, SecondString);
		StringCount++;
	}

	// Constructor for an object of the same String class
	MyString(const MyString& SecondString)
	{
		size = SecondString.size;
		ptr = new char[size + 1];
		strcpy_s(ptr, size + 1, SecondString.ptr);
		StringCount++;
	}

	// Overloading the + operator for string concatenation
	MyString operator+(const MyString& SecondString)
	{
		size += SecondString.size;
		char* temp = new char[size];

		int i, j;
		for (i = 0; ptr[i] != '\0'; i++)
		{
			temp[i] = ptr[i];
		}

		for (j = 0; SecondString.ptr[j] != '\0'; j++)
			temp[i + j] = SecondString.ptr[j];

		temp[i + j] = '\0';

		MyString tempStr(temp);

		return tempStr;
	}

	// Overloading the < operator for string comparison
	int operator<(const MyString& SecondString) const
	{
		for (int i = 0;; i++)
		{
			// Check the value of the elements with the second elements
			// If the element does not match, check which one and return the value
			if (ptr[i] != SecondString.ptr[i])
			{
				return ptr[i] < SecondString.ptr[i] ? -1 : 1;
			}

			// If all elements match, we reach the Null Terminator and return the value
			if (ptr[i] == '\0')
			{
				return 0;
			}
		}
	}

	// Overloading the ++ prefix operator (Adding x to the beginning)
	/*

	char* operator++()
	{
		size++;
		char* temp = new char[size];
		for (int i = 0; i < size; i++)
		{
			temp[i + 1] = ptr[i];
		}
		temp[0] = 'x';

		delete[] ptr;
		ptr = new char[size + 1];
		Mystrcpy_s(ptr, strlen(temp) + 1, temp);
		return temp;
	}

	*/

	// Overloading the ++ prefix operator (Adding x to the end)
	MyString operator++()
	{
		size++;
		char* temp = new char[size];
		for (int i = 0; i < size; i++)
		{
			temp[i] = ptr[i];
		}

		delete[] ptr;
		ptr = new char[size + 1];
		temp[size - 1] = 'x';
		temp[size] = '\0';
		Mystrcpy_s(ptr, strlen(temp) + 1, temp);
		return temp;
	}

	// Overloading the -- prefix operator (Deletion from the beginning)

	/*

	MyString operator--()
	{
		size--;
		char* temp = new char[size];
		for (int i = 0; i < size; i++)
		{
			temp[i] = ptr[i + 1];
		}
		ptr = new char[size + 1];
		temp[size] = '\0';
		Mystrcpy_s(ptr, strlen(temp) + 1, temp);
		return temp;
	}

	*/


	// Overloading the -- prefix operator (Deletion from the end)
	MyString operator--()
	{
		size--;
		char* temp = new char[size];
		for (int i = 0; i < size; i++)
		{
			temp[i] = ptr[i];
		}
		delete[] ptr;
		ptr = new char[size + 1];
		temp[size] = '\0';
		Mystrcpy_s(ptr, strlen(temp) + 1, temp);
		return temp;
	}


	// Overloading the + operator (Adding x to the beginning depending on int value)

	/*

	MyString operator+(int value)
	{
		size += value;
		char* temp = new char[size];
		int i = 0;
		for (i = 0; i < value; i++)
		{
			temp[i] = 'x';
		}

		for (int j = 0; j < size; j++,i++)
		{
			temp[i] = ptr[j];
		}
		delete[] ptr;
		ptr = new char[size + 1];
		Mystrcpy_s(ptr, strlen(temp) + 1, temp);
		return temp;
	}

	*/

	// Overloading the + operator (Adding x to the end depending on int value)
	MyString operator+(int value)
	{
		size += value;
		char* temp = new char[size];
		int i = 0;
		for (i = size; i > size - value - 1; i--)
		{
			temp[i] = 'x';
		}

		for (int j = 0; j < size - value; j++, i++)
		{
			temp[j] = ptr[j];
		}
		delete[] ptr;
		temp[size] = '\0';
		ptr = new char[size + 1];
		Mystrcpy_s(ptr, strlen(temp) + 1, temp);
		return temp;
	}

	// Overloading the - operator (Deletion from the end depending on int value)
	MyString operator-(int value)
	{
		size -= value;
		char* temp = new char[size];

		for (int i = 0; i < size; i++)
		{
			temp[i] = ptr[i];
		}
		temp[size] = '\0';
		ptr = new char[size + 1];
		Mystrcpy_s(ptr, strlen(temp) + 1, temp);
		return temp;
	}

	// Displaying values on the screen
	void Output()
	{
		if (ptr == nullptr)
		{
			return;
		}
		cout << ptr;
	}

	// Strlen Function
	int MyStrlen(const char* UserString)
	{
		int count = 0;
		while (*UserString != '\0')
		{
			count++;
			UserString++;
		}
		return count;
	}

	// Strcpy Function (secure)
	char* Mystrcpy_s(char* UserString, int Size, const char* SecondUserString)
	{
		if (Size > MyStrlen(UserString))
		{
			cout << "Error Buffer too small\n";
			return 0;
		}

		int i;
		for (i = 0; i < Size - 1; i++)
		{
			UserString[i] = SecondUserString[i];
		}
		UserString[i] = '\0';
		return UserString;
	}

	// Return Value Indicator
	//    0 Strings are equal
	//  < 0 the first character that does not match has a lower value in FirstString than in SecondString
	//  > 0 the first character that does not match has a greater value in FirstString than in SecondString
	int MyStrCmp(const char* SecondString)
	{
		for (int i = 0;; i++)
		{
			// Check the value of the elements with the second elements
			// If the element does not match, check which one and return the value
			if (ptr[i] != SecondString[i])
			{
				return ptr[i] < SecondString[i] ? -1 : 1;
			}

			// If all elements match, we reach the Null Terminator and return the value
			if (ptr[i] == '\0')
			{
				return 0;
			}
		}
	}


	char* MyStrCat(const char* secondString)
	{
		// Count variables 
		int i, j;

		// Count i variable while element is not equal to Null Terminator
		for (i = 0; ptr[i] != '\0'; i++);



		// Count j variable while element is not equal to Null Terminator
		// By that receive our element of second String to i + j index of Second Array
		for (j = 0; secondString[j] != '\0'; j++)
			ptr[i + j] = secondString[j];

		// Artificially added Null Terminator to our Variable
		ptr[i + j] = '\0';

		return ptr;
	}

	// Get Pointer Method
	char* Getptr()
	{
		return ptr;
	}

	// Method Get Size
	int GetSize()
	{
		return size;
	}

	// Method get the value stored in the pointer depending on the index passed in the function arguments
	char Getptrs(int value)
	{
		return ptr[value];
	}

	static int GetCount()
	{
		return StringCount;
	}

	// Destructor 
	~MyString()
	{
		delete[] ptr;
		StringCount--;
	}

private:
	char* ptr;
	int size;
	static int StringCount;
};
int::MyString::StringCount = 0;

// Overloading the Global + operator (Adding x to the start depending on int value)
// Using Methods
MyString operator+(int value, MyString& StringValue)
{
	char* temp = new char[value + StringValue.GetSize() + 1];

	int i;
	for (i = 0; i < value; i++)
	{
		temp[i] = 'x';
	}

	for (int j = 0; j < StringValue.GetSize(); j++, i++)
	{
		temp[i] = StringValue.Getptrs(j);
	}

	temp[value + StringValue.GetSize()] = '\0';
	MyString temps(temp);
	return temps;
}

// Move Constructor
MyString Func()
{
	MyString str("World");
	return str;
}

// Copy Constructor
// Move Constructor
MyString CopyFunc(MyString CopyString)
{
	MyString str("World");
	return str;
}

int main()
{
	// Copy Constructor
	MyString D("Hello World");

	// Passing an object to the function arguments and returning with a return
	// (if the move constructor is not overridden)
	MyString G = CopyFunc(D);

	// Assignment operator
	MyString E = G;

	// Initializing one object by another on creation
	MyString F(E);

	// Move Constructor

	// Function return value
	MyString A = Func();
	A.Output();
	cout << endl;
	MyString B = "Hello";

	// In the event that a temporary object is returned in the + operator,
	// there will be an implicit conversion to rvalue
	MyString C = B + A;
	C.Output();
}