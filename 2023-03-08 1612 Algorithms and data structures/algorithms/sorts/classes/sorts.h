#pragma once
#include <vector>
#include "../interface/i_sorts.h"

namespace sorts
{
    class RadixSort : public ISorts
    {
    private:
        int velichRazr(int chislo, int id, int count);

    public:
        void startLoop(std::vector<int> arr, const int count) override;
    };

    class SelectionSort : public ISorts
    {
    public:
        void startLoop(std::vector<int> arr, const int count) override;
    };

    class HeapSort : public ISorts
    {
    private:
        void heapify(std::vector<int> arr, int count, int id);

    public:
        void startLoop(std::vector<int> arr, const int count) override;
    };
}