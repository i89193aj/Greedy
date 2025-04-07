#pragma once

#define Build_DLL

#ifdef Build_DLL 
#define DLL_API _declspec(dllexport)
#else 
#define DLL_API _declspec(dllimport)
#endif // BuildDLL _declspec(DLLExport)

#include <string>
#include <iostream>
#include <vector>       // 若成員變數用到 std::vector
#include <map>          // 若有 std::map 變數
#include <unordered_map>// 若有 std::unordered_map 變數

class Greedy {
private:
    int* data;  // 假設資料成員是指標

public:
    // 預設建構式
    Greedy();

    // 帶參數建構式
    Greedy(int value);

    // 解構式
    ~Greedy();

    // 方法：設定值
    void setData(int value);

    // 方法：取得值
    int getData() const;

    // 顯示資料
    void display() const;

    struct CompareByFirst {
        bool operator()(const std::vector<int>& a, const std::vector<int>& b) const {
            return a[0] < b[0];
        }
    };

    struct CompareBySecond {
        bool operator()(const std::vector<int>& a, const std::vector<int>& b) const {
            return a.back() < b.back();
        }
    };

    struct CompareByPair_Descending {
        bool operator()(const std::pair<int, int>& a, const std::pair<int, int>& b) const {
            return a > b;
        }
    };


    // ======= Leetcode Solutions =======
    int Leetcode_Sol_435(std::vector<std::vector<int>>& intervals, int _solution);
    int Greedy_startingpoint_435(std::vector<std::vector<int>>& intervals);
    int Greedy_finalingpoint_435(std::vector<std::vector<int>>& intervals);

    std::vector<std::vector<int>> Leetcode_Sol_56(std::vector<std::vector<int>>& intervals, int _solution);
    std::vector<std::vector<int>> Greedy_startingpoint_iterator_56(std::vector<std::vector<int>>& intervals);
    std::vector<std::vector<int>> Greedy_startingpoint_56(std::vector<std::vector<int>>& intervals);

    std::vector<std::vector<int>> Leetcode_Sol_57(std::vector<std::vector<int>>& intervals, std::vector<int>& newInterval, int _solution);
    std::vector<std::vector<int>> Greedy_startingpoint_merge_57(std::vector<std::vector<int>>& intervals, std::vector<int>& newInterval);
    std::vector<std::vector<int>> Greedy_startingpoint_binary_57(std::vector<std::vector<int>>& intervals, std::vector<int>& newInterval);
    std::vector<std::vector<int>> Greedy_startingpoint_binary_iterator_57(std::vector<std::vector<int>>& intervals, std::vector<int>& newInterval);

    int Leetcode_Sol_452(std::vector<std::vector<int>>& points, int _solution);
    int Greedy_startingpoint_iterator_452(std::vector<std::vector<int>>& intervals);
    int Greedy_startingpoint_452(std::vector<std::vector<int>>& intervals);

    bool Leetcode_Sol_55(std::vector<int>& nums, int _solution);
    bool Greedy_55(std::vector<int>& nums);
    bool Greedy_MySol_55(std::vector<int>& nums);

    int Leetcode_Sol_45(std::vector<int>& nums, int _solution);
    int Greedy_45(std::vector<int>& nums);
    int Greedy_MySol_45(std::vector<int>& nums);

    int Leetcode_Sol_134(std::vector<int>& gas, std::vector<int>& cost, int _solution);
    int Greedy_134(std::vector<int>& gas, std::vector<int>& cost);

    int Leetcode_Sol_135(std::vector<int>& ratings, int _solution);
    int Greedy_135(std::vector<int>& ratings);
    int Greedy_MySol_135(std::vector<int>& ratings);

    int Leetcode_Sol_455(std::vector<int>& g, std::vector<int>& s, int _solution);
    int Greedy_455(std::vector<int>& g, std::vector<int>& s);

    int Leetcode_Sol_376(std::vector<int>& nums, int _solution);
    int Greedy_376(std::vector<int>& nums);
    int Greedy_MySol_376(std::vector<int>& nums);

    int Leetcode_Sol_2136(std::vector<int>& plantTime, std::vector<int>& growTime, int _solution);
    int Greedy_2136(std::vector<int>& plantTime, std::vector<int>& growTime);

    int Leetcode_Sol_621(std::vector<int>& tasks,int n, int _solution);
    int Greedy_simulation_cooldowntasks_621(std::vector<int>& tasks, int n);
    int Greedy_formula_unordered_map_621(std::vector<int>& tasks, int n);
    int Greedy_formula_vector_621(std::vector<int>& tasks, int n);

    std::vector<std::vector<int>> Leetcode_Sol_406(std::vector<std::vector<int>>& people, int _solution);
    std::vector<std::vector<int>> Greedy_406(std::vector<std::vector<int>>& people);
    std::vector<std::vector<int>> BinaryIndexedTree_406(std::vector<std::vector<int>>& people);     //先不看
    std::vector<std::vector<int>> SegmentTree_406(std::vector<std::vector<int>>& people);           //先不看

private:
    //BIT (BinaryIndexedTree_621)
    void update_BIT(std::vector<int>& bit, int idx, int delta); 
    int query_BIT(std::vector<int>& bit, int idx);
    //ST (SegmentTree_621)
    void build_ST(int node, int start, int end);
    int query_ST(int node, int start, int end, int k);
    void update_ST(int node, int start, int end, int idx);











    // ======= Leetcode Solutions =======

    /*這種有三種方式：
        第一種：
        同一個class (像現在)
        第二種：
        宣告全域變數 (在cpp裡寫static void.....宣告成全域且要寫在使用他的func上面(不然他找不到))
        第三種：
        寫namespace 一樣要寫在使用他的func上面!(如果只在當前 .cpp 文件中使用，可以將這些函式放到匿名命名空間中))
     */

};



extern DLL_API Greedy GreedyInstance;
