#include <iostream>
#include <vector>
#include <complex>
#include <algorithm>
#include <ctime>
#include <cstdlib>

class Complex     //Complex �ࣺ��ʾ����������ʵ�����鲿����ʵ���˱ȽϺ�����������
{
public:
    std::complex<double> value;

    Complex(double real = 0, double imag = 0)
        : value(real, imag)
    {
    }

    double modulus() const
    {
        return std::abs(value);
    }

    bool operator==(const Complex& other) const
    {
        return value == other.value;
    }

    bool operator<(const Complex& other) const
    {
        if (modulus() != other.modulus())
        {
            return modulus() < other.modulus();
        }
        return value.real() < other.value.real();
    }

    bool operator>(const Complex& other) const
    {
        // �Ƚ�ģ�Ĵ�С�������ͬ��Ƚ�ʵ��
        if (modulus() != other.modulus())
        {
            return modulus() > other.modulus();
        }
        return value.real() > other.value.real();
    }

    bool operator<=(const Complex& other) const
    {
        return !(*this > other); // ������Ǵ��ڣ���С�ڵ���
    }

    bool operator>=(const Complex& other) const
    {
        return !(*this < other); // �������С�ڣ�����ڵ���
    }

    void display() const
    {
        std::cout << value << " ";
    }
};

// �����������������generateRandomComplexVector ��������ָ����С�����������������
std::vector<Complex> generateRandomComplexVector(size_t size)
{
    std::vector<Complex> vec;
    for (size_t i = 0; i < size; ++i)
    {
        double real = static_cast<double>(rand() % 100 - 50); // ���ʵ����-50��50֮��
        double imag = static_cast<double>(rand() % 100 - 50); // ��-50��50�������鲿
        vec.emplace_back(real, imag);
    }
    return vec;
}

// �����������
void shuffleVector(std::vector<Complex>& vec)
{
    std::random_shuffle(vec.begin(), vec.end());
}

// �������в���Ԫ��
void insertElement(std::vector<Complex>& vec, const Complex& element)
{
    vec.push_back(element);
}

// ɾ�������е�Ԫ��
bool deleteElement(std::vector<Complex>& vec, const Complex& element)
{
    auto it = std::remove(vec.begin(), vec.end(), element);
    if (it != vec.end())
    {
        vec.erase(it, vec.end());
        return true;
    }
    return false;
}

// ȥ���ظ���
void uniqueVector(std::vector<Complex>& vec)
{
    std::sort(vec.begin(), vec.end());
    vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
}

// ʹ��ð������Ը���������������
void bubbleSort(std::vector<Complex>& vec)
{
    size_t n = vec.size();
    for (size_t i = 0; i < n - 1; ++i)
    {
        for (size_t j = 0; j < n - i - 1; ++j)
        {
            if (vec[j] > vec[j + 1])
            {
                std::swap(vec[j], vec[j + 1]);
            }
        }
    }
}

// ʹ�ù鲢����Ը���������������
void merge(std::vector<Complex>& vec, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<Complex> L(n1), R(n2);
    for (int i = 0; i < n1; ++i)
        L[i] = vec[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = vec[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            vec[k] = L[i];
            i++;
        }
        else
        {
            vec[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        vec[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        vec[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<Complex>& vec, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(vec, left, mid);
        mergeSort(vec, mid + 1, right);
        merge(vec, left, mid, right);
    }
}

// ������ң���������ģ�ڸ�����Χ�ڵ�Ԫ��
std::vector<Complex> intervalSearch(const std::vector<Complex>& vec, double m1, double m2)
{
    std::vector<Complex> result;
    for (const auto& c : vec)
    {
        double mod = c.modulus();
        if (mod >= m1 && mod < m2)
        {
            result.push_back(c);
        }
    }
    return result;
}

int main()
{
    srand(static_cast<unsigned>(time(0)));

    // ����һ������ĸ�������
    std::vector<Complex> complexVec = generateRandomComplexVector(10);

    std::cout << "Original Vector: ";
    for (const auto& c : complexVec)
    {
        c.display();
    }
    std::cout << std::endl;

    // �任ʸ��
    shuffleVector(complexVec);
    std::cout << "Shuffled Vector: ";
    for (const auto& c : complexVec)
    {
        c.display();
    }
    std::cout << std::endl;

    // ����Ԫ��
    Complex newElement(3, 4);
    insertElement(complexVec, newElement);
    std::cout << "After Inserting (3, 4): ";
    for (const auto& c : complexVec)
    {
        c.display();
    }
    std::cout << std::endl;

    // ɾ��Ԫ��
    deleteElement(complexVec, newElement);
    std::cout << "After Deleting (3, 4): ";
    for (const auto& c : complexVec)
    {
        c.display();
    }
    std::cout << std::endl;

    // Ψһ������
    uniqueVector(complexVec);
    std::cout << "Unique Vector: ";
    for (const auto& c : complexVec)
    {
        c.display();
    }
    std::cout << std::endl;

    //ʹ�� clock() ����������ð������͹鲢�����Ч�ʡ����Ը�����Ҫ����������ɵĸ����������������ܡ�

    // ʹ��ð�������������������
    std::vector<Complex> bubbleSortVec = complexVec;
    clock_t beginBubble = clock();
    bubbleSort(bubbleSortVec);
    clock_t endBubble = clock();
    std::cout << "Bubble Sorted Vector: ";
    for (const auto& c : bubbleSortVec)
    {
        c.display();
    }
    std::cout << "\nBubble Sort Time: " << double(endBubble - beginBubble) / CLOCKS_PER_SEC << " seconds." << std::endl;

    // ʹ�ù鲢�����������������
    std::vector<Complex> mergeSortVec = complexVec;
    clock_t beginMerge = clock();
    mergeSort(mergeSortVec, 0, mergeSortVec.size() - 1);
    clock_t endMerge = clock();
    std::cout << "Merge Sorted Vector: ";
    for (const auto& c : mergeSortVec)
    {
        c.display();
    }
    std::cout << "\nMerge Sort Time: " << double(endMerge - beginMerge) / CLOCKS_PER_SEC << " seconds." << std::endl;

    // �������
    double m1 = 5.0, m2 = 20.0;
    std::vector<Complex> intervalResult = intervalSearch(mergeSortVec, m1, m2);
    std::cout << "Interval Search Result (modulus between " << m1 << " and " << m2 << "): ";
    for (const auto& c : intervalResult)
    {
        c.display();
    }
    std::cout << std::endl;

    return 0;
}
