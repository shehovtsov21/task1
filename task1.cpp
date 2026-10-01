#include <iostream>
using namespace std;

class Array
{
    int* ptr;
    int size;

public:
    Array(int s = 0)
    {
        size = s > 0 ? s : 0;
        ptr = size > 0 ? new int[size]{} : nullptr;
    }

    Array(const Array& obj)
    {
        size = obj.size;
        ptr = size > 0 ? new int[size] : nullptr;
        for (int i = 0; i < size; i++)
            ptr[i] = obj.ptr[i];
    }

    Array& operator=(const Array& obj)
    {
        if (this != &obj)
        {
            int* temp = obj.size > 0 ? new int[obj.size] : nullptr;
            for (int i = 0; i < obj.size; i++)
                temp[i] = obj.ptr[i];
            delete[] ptr;
            ptr = temp;
            size = obj.size;
        }
        return *this;
    }

    ~Array()
    {
        delete[] ptr;
    }

    int& operator[](int index)
    {
        if (index < 0 || index >= size)
            throw "Invalid index";
        return ptr[index];
    }

    const int& operator[](int index) const
    {
        if (index < 0 || index >= size)
            throw "Invalid index";
        return ptr[index];
    }

    void operator()(int value)
    {
        for (int i = 0; i < size; i++)
            ptr[i] += value;
    }

    operator int() const
    {
        int sum = 0;
        for (int i = 0; i < size; i++)
            sum += ptr[i];
        return sum;
    }

    operator char*() const
    {
        int length = 0;
        for (int i = 0; i < size; i++)
        {
            long long value = ptr[i];
            if (value < 0)
            {
                length++;
                value = -value;
            }
            do
            {
                length++;
                value /= 10;
            } while (value != 0);
            if (i + 1 < size)
                length++;
        }

        char* result = new char[length + 1];
        int position = 0;
        for (int i = 0; i < size; i++)
        {
            long long value = ptr[i];
            if (value < 0)
            {
                result[position++] = '-';
                value = -value;
            }
            char digits[20];
            int count = 0;
            do
            {
                digits[count++] = static_cast<char>('0' + value % 10);
                value /= 10;
            } while (value != 0);
            for (int j = count - 1; j >= 0; j--)
                result[position++] = digits[j];
            if (i + 1 < size)
                result[position++] = ' ';
        }
        result[position] = '\0';
        return result;
    }

    void Print() const
    {
        for (int i = 0; i < size; i++)
            cout << ptr[i] << " ";
        cout << endl;
    }
};

int main()
{
    Array a(5);
    for (int i = 0; i < 5; i++)
        a[i] = (i + 1) * 10;

    cout << "Array: ";
    a.Print();
    cout << "a[2] = " << a[2] << endl;
    a[2] = 100;
    cout << "After a[2] = 100: ";
    a.Print();

    a(5);
    cout << "After a(5): ";
    a.Print();

    int sum = a;
    cout << "Sum = " << sum << endl;
    char* text = a;
    cout << "String = " << text << endl;
    delete[] text;

    Array b(a);
    b[0] = -7;
    cout << "Copy: ";
    b.Print();
    cout << "Original: ";
    a.Print();

    Array c;
    c = a;
    cout << "Assigned copy: ";
    c.Print();

    const Array d(a);
    cout << "Const index: " << d[1] << endl;

    Array empty;
    char* emptyText = empty;
    cout << "Empty string: [" << emptyText << "]" << endl;
    delete[] emptyText;
    return 0;
}