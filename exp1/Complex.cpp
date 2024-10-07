#include <iostream>
#include <vector>
#include <complex>
#include <algorithm>
#include <ctime>
#include <cstdlib>

class Complex     //Complex 类：表示复数，包含实部和虚部，并实现了比较和相等运算符。
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
        // 比较模的大小，如果相同则比较实部
        if (modulus() != other.modulus())
        {
            return modulus() > other.modulus();
        }
        return value.real() > other.value.real();
    }

    bool operator<=(const Complex& other) const
    {
        return !(*this > other); // 如果不是大于，则小于等于
    }

    bool operator>=(const Complex& other) const
    {
        return !(*this < other); // 如果不是小于，则大于等于
    }

    void display() const
    {
        std::cout << value << " ";
    }
};

// 生成随机复数向量：generateRandomComplexVector 函数生成指定大小的随机复杂数向量。
std::vector<Complex> generateRandomComplexVector(size_t size)
{
    std::vector<Complex> vec;
    for (size_t i = 0; i < size; ++i)
    {
        double real = static_cast<double>(rand() % 100 - 50); // 随机实部在-50到50之间
        double imag = static_cast<double>(rand() % 100 - 50); // 从-50到50的任意虚部
        vec.emplace_back(real, imag);
    }
    return vec;
}

// 随机打乱向量
void shuffleVector(std::vector<Complex>& vec)
{
    std::random_shuffle(vec.begin(), vec.end());
}

// 在向量中插入元素
void insertElement(std::vector<Complex>& vec, const Complex& element)
{
    vec.push_back(element);
}

// 删除向量中的元素
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

// 去除重复项
void uniqueVector(std::vector<Complex>& vec)
{
    std::sort(vec.begin(), vec.end());
    vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
}

// 使用冒泡排序对复数向量进行排序
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

// 使用归并排序对复数向量进行排序
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

// 区间查找：函数查找模在给定范围内的元素
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

    // 生成一个随机的复数向量
    std::vector<Complex> complexVec = generateRandomComplexVector(10);

    std::cout << "Original Vector: ";
    for (const auto& c : complexVec)
    {
        c.display();
    }
    std::cout << std::endl;

    // 变换矢量
    shuffleVector(complexVec);
    std::cout << "Shuffled Vector: ";
    for (const auto& c : complexVec)
    {
        c.display();
    }
    std::cout << std::endl;

    // 插入元素
    Complex newElement(3, 4);
    insertElement(complexVec, newElement);
    std::cout << "After Inserting (3, 4): ";
    for (const auto& c : complexVec)
    {
        c.display();
    }
    std::cout << std::endl;

    // 删除元素
    deleteElement(complexVec, newElement);
    std::cout << "After Deleting (3, 4): ";
    for (const auto& c : complexVec)
    {
        c.display();
    }
    std::cout << std::endl;

    // 唯一的向量
    uniqueVector(complexVec);
    std::cout << "Unique Vector: ";
    for (const auto& c : complexVec)
    {
        c.display();
    }
    std::cout << std::endl;

    //使用 clock() 函数来测试冒泡排序和归并排序的效率。可以根据需要调整随机生成的复数数量来测试性能。

    // 使用冒泡排序对向量进行排序
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

    // 使用归并排序对向量进行排序
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

    // 区间查找
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
