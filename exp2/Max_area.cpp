#include <vector>
#include <random>
#include <iostream>
#include <stack>

int max_histogram_area(const std::vector<int>& heights)
{
    std::stack<int> indices;
    int max_area = 0;
    int index = 0;

    while (index < heights.size())
    {
        if (indices.empty() || heights[index] >= heights[indices.top()])
        {
            indices.push(index++);
        }
        else
        {
            int top = indices.top();
            indices.pop();
            int area = heights[top] * (indices.empty() ? index : index - indices.top() - 1);
            max_area = std::max(max_area, area);
        }
    }

    while (!indices.empty())
    {
        int top = indices.top();
        indices.pop();
        int area = heights[top] * (indices.empty() ? index : index - indices.top() - 1);
        max_area = std::max(max_area, area);
    }

    return max_area;
}

// 生成随机测试数据
std::vector<int> generate_test_case(int max_length = 105, int max_height = 104)
{
    std::vector<int> heights;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> height_distribution(0, max_height);

    int length = rand() % max_length + 1;
    for (int i = 0; i < length; ++i)
    {
        heights.push_back(height_distribution(generator));
    }

    return heights;
}

int main()
{
    for (int i = 0; i < 10; ++i)
    {
        std::vector<int> heights = generate_test_case();

        // 输出生成的随机数组
        std::cout << "Test case " << i + 1 << ": Heights = ";
        for (const int height : heights)
        {
            std::cout << height << " ";
        }
        std::cout << std::endl;

        int area = max_histogram_area(heights);
        std::cout << "Max Area = " << area << std::endl
                  << std::endl;
    }

    // 示例用例
    std::vector<int> test1 = {2, 1, 5, 6, 2, 3};
    std::cout << "Test case 1: Max Area = " << max_histogram_area(test1) << std::endl; // 输出: 10

    std::vector<int> test2 = {2, 4};
    std::cout << "Test case 2: Max Area = " << max_histogram_area(test2) << std::endl; // 输出: 4

    return 0;
}
