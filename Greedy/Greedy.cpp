/*Oscar Greedy*/

#include <iostream>
#include <cstdlib>  // rand(), srand()
#include <ctime>    // time()
#include <random>   // C++11 亂數庫
#include <vector>   // std::vector
#include <numeric>  // std::iota
#include <map>      //std::map
#include <unordered_map>  //std::unordered_map
#include <deque>    //std::deque
#include <queue>    //std::queue & std::priority_queue

#include"Greedy.h"
using namespace std;

DLL_API Greedy GreedyInstance;
enum LeetcodeExam {
    Leetcodexxx,
    Leetcode45,
    None,
};

#pragma region 解題思路&技巧
/*
* 一、解題思路：
1.局部最優 → 全局最優(每步都選最優解，"不回溯")
2.分析題目有無比較性質(比如說：空間、時間、場地、金錢...)
3.分析是否只需比較一個性質
4.最小化 / 最大化問題(觀察題目如果有說明最大or最小就要考慮是否DP or Greedy)

前面三項是必要!
後面一項是非必要，但如果題目問，就可以試著從這方面想!
(Ex：如果題目有說求 "最小" or "最大" ，那麼就可以考慮
然後再用1~3項去確定)

二、技巧：
1.是否要用sort => 判斷sort完後題目會不會失真!
很多題目都需要排序(跟BinarySearch一樣)

2.排序用start 還是 end?
a.用 start 排序 (a[0] < b[0])：
看是否要「盡量延長使用時間」，避免錯過某些範圍(也就是從頭看過一次)
**技巧(記 imp!)：left => 擴大空間資源
ex：合併區間、區間插入
b.用 end 排序 (a[1] < b[1])：
看是否要「盡量早結束，讓後面更彈性」
技巧(記 imp!)：right => 壓縮空間資源
ex：最小資源覆蓋（如最少箭數、最少會議室）、最多活動選擇(意味著花單個活動花的時間最少)

3.找到"單一"性值，能跑出極大值與極小值

4.如果你有找到要比較的性質，但難的點在不好找要跟誰比較的話。
那你第一個方式：
有"單位相同"的值可以試著比較看看並思考反例!
Ex：Jump Game 就是超標準很難找到同性質的比較單位

5.有區間為題的類型：重要(imp)：*****(五顆星)
排序完後
if判斷式一定是一個start跟一個end去比較(這樣才會有交錯!)
(幾乎都是遍歷vector<int>::begin() 去跟被比較值(end)比較)
原因：你會想知道每次的頭部(begin)會不會低於上一個尾部(back)
通常題目會說：
最小房間、最小區間....or "砍掉"最小次數
(這些本來就是最優解，所以會"留下運用資源最少的，刪除最大的!")

6.檢查：
有沒有情況是「當下選擇最優，卻導致後面沒辦法得到整體最優解」？
*/

#pragma endregion

#pragma region 主程式(main)
int main()
{
    LeetcodeExam ExamEnum = Leetcode45;                         //ChangeForExam
    vector<int> vInput1 = { 2,3,1,1,4 };                        //ChangeForExam
    vector<int> vInput2 = { 7,13,11,10,1 };                     //ChangeForExam
    int iInput1 = 0; int iInput2 = 0;
    vector<vector<int>> vvInput1 = {{1,2} ,{2,3},{3,4},{1,3}};
    
    int Ans = 0; vector<int> AnsVector; string AnsStr = "";
    string strinput1 = "bab";
    string strinput2 = "xaabacxcabaaxcabaax";


    Greedy* Implementation = new Greedy();

    switch (ExamEnum)
    {
    case Leetcodexxx:
        Ans = Implementation->Leetcode_Sol_435(vvInput1, 1);
        break;
    case Leetcode45:
        Ans = Implementation->Leetcode_Sol_45(vInput1, 1);
        Ans = Implementation->Leetcode_Sol_45(vInput1, 2);
        break;



        

    default:
        break;
    }
#pragma region Greedy
    Greedy obj1;              // 呼叫預設建構式
    obj1.display();

    Greedy obj2(10);          // 呼叫帶參數建構式
    obj2.display();

    obj1.setData(20);          // 修改資料成員
    obj1.display();

    return 0;
#pragma endregion


}

#pragma endregion

#pragma region Greedy
// 預設建構式，初始化指標
Greedy::Greedy() : data(new int(0)) {
    std::cout << "Default constructor called. Data initialized to 0." << std::endl;
}

// 帶參數建構式，初始化指標並設置初始值
Greedy::Greedy(int value) : data(new int(value)) {
    std::cout << "Parameterized constructor called. Data initialized to " << value << "." << std::endl;
}

// 解構式，釋放動態分配的記憶體
Greedy::~Greedy() {
    delete data;
    std::cout << "Destructor called. Memory for data released." << std::endl;
}

// 設定資料成員
void Greedy::setData(int value) {
    *data = value;
}

// 取得資料成員
int Greedy::getData() const {
    return *data;
}

// 顯示資料
void Greedy::display() const {
    std::cout << "Data: " << *data << std::endl;
}
#pragma endregion

#pragma region Leetcode_Exam

#pragma region 考題一：區間選擇（Activity Selection, Interval Scheduling）

#pragma region a.擁有最大資源 (sort by right)

#pragma region Leetcode 435. Non-overlapping Intervals
//Leetcode 435. Non-overlapping Intervals
int Greedy::Leetcode_Sol_435(std::vector<std::vector<int>>& intervals, int _solution) {
    switch (_solution)
    {
    case 1:
        return Greedy_startingpoint_435(intervals);
    case 2:
        return Greedy_finalingpoint_435(intervals);

    default:
        return 0; // 確保所有路徑都有回傳值
    }

    return 0;
}

int Greedy::Greedy_startingpoint_435(std::vector<std::vector<int>>& intervals) {
    std::sort(intervals.begin(), intervals.end());
    int icount = 0;
    int right = *(intervals.begin()->end() - 1); //之後intervals.begin()->end() - 1 可以換成intervals.begin()->back() //他是值類，不是指標
    for (auto it = intervals.begin() + 1; it != intervals.end(); ++it) {
        if (*(it->begin()) < right) {
            right = *(it->end() - 1) < right ? *(it->end() - 1) : right;
            icount++;
        }
        else {
            right = *(it->end() - 1);
        }
    }
    return icount;
}

int Greedy::Greedy_finalingpoint_435(std::vector<std::vector<int>>& intervals) {
    //Lamda表示：
    std::sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
        return a[1] < b[1];
        });
    //用Greedy.h裡面自定義比較器Struct：
    std::sort(intervals.begin(),intervals.end(),Greedy::CompareBySecond());

    int icount = 0;
    int right = *(intervals.begin()->end() - 1);
    for (auto it = intervals.begin() + 1; it != intervals.end(); ++it) {
        if (*(it->begin()) < right) {
            icount++;
        }
        else {
            right = *(it->end() - 1);
        }
    }
    return icount;
}
#pragma endregion

#pragma endregion

#pragma region b.擴大資源 (sort by left)

#pragma region Leetcode 56. Merge Intervals
//Leetcode 56. Merge Intervals
vector<vector<int>> Greedy::Leetcode_Sol_56(std::vector<std::vector<int>>& intervals, int _solution) {
    switch (_solution)
    {
    case 1:
        return Greedy_startingpoint_iterator_56(intervals);
    case 2:
        return Greedy_startingpoint_56(intervals);

    default:
        return {}; // 確保所有路徑都有回傳值
    }

    return {};
}

vector<vector<int>> Greedy::Greedy_startingpoint_iterator_56(std::vector<std::vector<int>>& intervals) {
    if (!intervals.size()) return {};
    std::sort(intervals.begin(), intervals.end());
    vector<vector<int>> ans;
    ans.push_back(*intervals.begin());
    for (std::vector<vector<int>>::iterator it = intervals.begin() + 1; it != intervals.end(); ++it) {
        if (*it->begin() > ans.back().back()) {   //只要超過上一個數組的最大值，那就加進來
            ans.push_back(*it);
        }
        else {                                   //沒超過下一個數組的話(<=)，那就比較前面數組的最大值
            ans.back().back() = std::max(ans.back().back(), it->back());
        }
    }
    return ans;
}

vector<vector<int>> Greedy::Greedy_startingpoint_56(std::vector<std::vector<int>>& intervals) {
    if (intervals.empty()) return{};
    std::sort(intervals.begin(), intervals.end());
    vector<vector<int>> ans;
    ans.push_back(*intervals.begin());
    for (int i = 1; i < intervals.size(); i++) {
        if (intervals[i][0] <= ans.back()[1]) {
            if (intervals[i][1] > ans.back()[1])
                ans.back()[1] = intervals[i][1];
        }
        else {
            ans.push_back(intervals[i]);
        }
    }
    return ans;
}
#pragma endregion

#pragma region Leetcode 57. Insert Interval
//Leetcode 57. Insert Interval
vector<vector<int>> Greedy::Leetcode_Sol_57(std::vector<std::vector<int>>& intervals, std::vector<int>& newInterval, int _solution) {
    switch (_solution)
    {
    case 1:
        return Greedy_startingpoint_merge_57(intervals, newInterval);
    case 2:
        return Greedy_startingpoint_binary_57(intervals, newInterval);
    case 3:
        return Greedy_startingpoint_binary_iterator_57(intervals, newInterval);
       
    default:
        return {}; // 確保所有路徑都有回傳值
    }

    return {};
}

vector<vector<int>> Greedy::Greedy_startingpoint_merge_57(std::vector<std::vector<int>>& intervals, std::vector<int>& newInterval) {
    vector<vector<int>> res;
    int i = 0, n = intervals.size();

    // 1️. 加入左側不重疊區間
    while (i < n && intervals[i][1] < newInterval[0]) {
        res.push_back(intervals[i]);
        i++;
    }

    // 2️. 合併重疊區間
    while (i < n && intervals[i][0] <= newInterval[1]) {
        newInterval[0] = min(newInterval[0], intervals[i][0]);
        newInterval[1] = max(newInterval[1], intervals[i][1]);
        i++;
    }
    res.push_back(newInterval); // 加入合併後的新區間

    // 3️. 加入右側不重疊區間
    while (i < n) {
        res.push_back(intervals[i]);
        i++;
    }

    return res;
}

vector<vector<int>> Greedy::Greedy_startingpoint_binary_57(std::vector<std::vector<int>>& intervals, std::vector<int>& newInterval) {
    if (intervals.empty()) return { newInterval };
    vector<vector<int>>::iterator atpos =
        lower_bound(intervals.begin(), intervals.end(), newInterval, Greedy::CompareByFirst());
    intervals.insert(atpos, newInterval); // 插入新區間imp：*****
    vector<vector<int>> ans;
    ans.push_back(intervals[0]);
    for (int i = 1; i < intervals.size(); i++) {
        if (intervals[i][0] > ans.back()[1])
            ans.push_back(intervals[i]);
        else
            ans.back()[1] = std::max(ans.back()[1], intervals[i][1]);
    }
    return ans;
}

vector<vector<int>> Greedy::Greedy_startingpoint_binary_iterator_57(std::vector<std::vector<int>>& intervals, std::vector<int>& newInterval) {
    std::vector<vector<int>>::iterator it = lower_bound(intervals.begin(), intervals.end(), newInterval,
        [](const vector<int>& a, const vector<int>& b) {return a[0] < b[0]; });

    intervals.insert(it, newInterval);
    vector<vector<int>> ans;
    ans.push_back(intervals[0]);
    for (auto it2 = intervals.begin() + 1; it2 != intervals.end(); ++it2) {
        if (ans.back()[1] < *it2->begin())
            ans.push_back(*it2);
        else
            ans.back()[1] = max(ans.back()[1], it2->back());
    }
    return ans;
}
#pragma endregion

#pragma region Leetcode 452. Minimum Number of Arrows to Burst Balloons
//Leetcode 452. Minimum Number of Arrows to Burst Balloons
int Greedy::Leetcode_Sol_452(std::vector<std::vector<int>>& points, int _solution) {
    switch (_solution)
    {
    case 1:
        return Greedy_startingpoint_iterator_452(points);
    case 2:
        return Greedy_startingpoint_452(points);

    default:
        return 0; // 確保所有路徑都有回傳值
    }

    return 0;
}

int Greedy::Greedy_startingpoint_iterator_452(std::vector<std::vector<int>>& points) {
    if (!points.size()) return 0;
    //如果b不加'&'，vector<int> b 會發生複製，每次比較都會額外複製一個 vector<int>，大幅降低效率！
    std::sort(points.begin(), points.end(),
        [](const vector<int>& a, const vector<int> b) {return a.back() < b.back(); });
    int right = points.begin()->back();
    int icount = 1; //至少要射一次
    for (vector<vector<int>>::iterator it = points.begin() + 1; it != points.end(); ++it) {
        if (*it->begin() > right) {
            icount++;
            right = std::max(right, it->back());
        }
    }
    return icount;
}

int Greedy::Greedy_startingpoint_452(std::vector<std::vector<int>>& points) {
    std::sort(points.begin(), points.end(), [](const vector<int>& a, const vector<int>& b) {
        return a[1] < b[1];
        });
    int icount = 1; 
    int right = points[0][1];
    for (int i = 1; i < points.size(); i++) {
        if (points[i][0] > right) {
            icount++;
            right = points[i][1];
        }
    }
    return icount;
}
#pragma endregion

#pragma endregion

#pragma endregion

#pragma region 考題二：特殊性值(尋找比較單一性值)

#pragma region 1.跳躍遊戲（Jump Game）
#pragma region Leetcode 55. Jump Game
//Leetcode 55. Jump Game
bool Greedy::Leetcode_Sol_55(vector<int>& nums, int _solution) {
    switch (_solution)
    {
    case 1:
        return Greedy_55(nums);
    case 2:
        return Greedy_MySol_55(nums);

    default:
        return false; // 確保所有路徑都有回傳值
    }

    return false;
}

/*主要判別：每個位置你能跳多遠!*/
bool Greedy::Greedy_55(vector<int>& nums) {
    int lastpos = nums.size() - 1;
    int maxReach = 0;  // 目前能到達的最遠位置
    for (int i = 0; i < nums.size(); ++i) {
        if (i > maxReach) return false;         // 如果最遠可達位置無法跳躍刀前位置，表示無法繼續跳
        maxReach = max(maxReach, i + nums[i]);  // 更新最遠可達位置
        if (maxReach >= lastpos) return true;   // 如果最遠可達位置已經超過或達到最後位置
        
    }
    return false;
}

/*跟上面的差異在於：我是跟當次比較，所以會有一個問題是當nums.size() == 1，特殊test case：nums= {0};*/
bool Greedy::Greedy_MySol_55(vector<int>& nums) {
    if (nums.size() == 1) return true;
        int maxpos = 0;
    for (int curpos = 0; curpos < nums.size(); curpos++) {
        maxpos = std::max(maxpos, nums[curpos] + curpos);
        if (maxpos == curpos) return false;

        if (maxpos >= nums.size() - 1) return true;
    }
    return true;
}
#pragma endregion

#pragma region Leetcode 45. Jump Game II
//Leetcode 45. Jump Game II
int Greedy::Leetcode_Sol_45(vector<int>& nums, int _solution) {
    switch (_solution)
    {
    case 1:
        return Greedy_recordrealpos_45(nums);
    case 2:
        return Greedy_MySol_45(nums);

    default:
        return false; // 確保所有路徑都有回傳值
    }

    return false;
}

/*主要判別：選擇跳躍到下一個位置之間最大的跳躍位移!*/
/*說明：這題不用紀錄位置，但如果能記錄位置，代表真的有搞懂(所以就改一下題目)
        跳到的位置一定是下一次要跳躍最大位移的位置，所以前面讓他去比較跳躍最大位移，只有在到達這次跳躍目標時，
        才要去知道這期間哪個"跳躍到下一個位置的位移最大"，然後選擇那個位置跳!*/
int Greedy::Greedy_recordrealpos_45(vector<int>& nums) {
    int lastpos = nums.size() - 1;
    int jumps = 0, farthest = 0, end = 0;
    int nextJump = 0;  // 記錄「最佳跳躍點」
    vector<int> path;  // 記錄跳躍路徑

    for (int i = 0; i < lastpos; i++) {
        if (i + nums[i] > farthest) {
            farthest = i + nums[i];  // 更新目前區間內最遠能到的位置
            nextJump = i;  // 記錄當前最佳的跳躍起點
        }

        if (i == end) {  // 走到當前範圍的盡頭，必須跳躍
            jumps++;
            end = farthest;
            path.push_back(nextJump);  // 記錄跳躍點

            if (end >= lastpos) {
                path.push_back(lastpos);  // 最後一步直接到終點
                break;
            }
        }
    }
    return jumps;
    //return path; //紀錄每個跳耀的位置(不一定只有一個解)

    /*由於題目說test case一定能跳過到最後一個，所以在遍歷的過程中，
      即使上一次跳躍會跳到0，但在中途就會更換可跳躍的最遠位置，
      這樣就變相直接將上一次的跳躍縮小到不會跳進0，而且改跳到在這區間中最大的跳躍值*/
}


int Greedy::Greedy_MySol_45(vector<int>& nums) {
    if (nums.size() == 1) return 0;
    int icount = 0, lastpos = nums.size() - 1;
    int curMaxpos = nums[0], maxpos = nums[0];
    int jumppos = 0;
    vector<int> jumppass;
    jumppass.push_back(jumppos);
    for (int pos = 0; pos < nums.size(); pos++) {
        //比較每輪跳躍之間的下一次最大位移
        int maxpos_temp = pos + nums[pos];
        if (maxpos < maxpos_temp) {
            maxpos = maxpos_temp;
            jumppos = pos;
        }

        if (pos == curMaxpos) {
            icount++;
            jumppass.push_back(jumppos);
            curMaxpos = maxpos;
        }

        if (curMaxpos >= lastpos) {
            icount++;
            jumppass.push_back(lastpos);
            break;
        }
    }
    return icount;
    //每一輪如果能更換更大的位置，就代表當下那倫會跳到這裡來
}

#pragma endregion
#pragma endregion

#pragma region Leetcode 134. Gas Station
//Leetcode 134. Gas Station
int Greedy::Leetcode_Sol_134(vector<int>& gas,vector<int>& cost, int _solution) {
    switch (_solution)
    {
    case 1:
        return Greedy_134(gas, cost);

    default:
        return false; // 確保所有路徑都有回傳值
    }

    return false;
}

/*主要判別：
1. 總油量一定要超過花費油量(很值觀)
2. 跑到現在的油量是否能cover這站花的油量(如果不是，代表這站不能是起頭，換到下一站重新開始算) (這個條件難找!*****)*/
int Greedy::Greedy_134(vector<int>& gas,vector<int>& cost) {
    //If there exists a solution, it is guaranteed to be unique. => greedy
    int total_tank = 0, curr_tank = 0, start = 0;

    for (int i = 0; i < gas.size(); i++) {
        int net_gain = gas[i] - cost[i];
        total_tank += net_gain;
        curr_tank += net_gain;

        // 如果當前的總油量 < 0，表示無法從 `start` 到 `i+1`
        if (curr_tank < 0) {
            start = i + 1;  // 從下一個站點開始
            curr_tank = 0;  // 重置當前油量
        }
    }

    return (total_tank >= 0) ? start : -1;
}
#pragma endregion

#pragma region Leetcode 135. Candy
//Leetcode 135. Candy
int Greedy::Leetcode_Sol_135(vector<int>& ratings, int _solution) {
    switch (_solution)
    {
    case 1:
        return Greedy_135(ratings);
    case 2:
        return Greedy_MySol_135(ratings);

    default:
        return false; // 確保所有路徑都有回傳值
    }

    return false;
}

/*主要判別：坡度高低變化(鄰近數值高低)*/
/*說明：
難點："你要怎麼想到要做兩次遍歷"，先從左到右確保遞增，再從右到左確保遞減，並不是難在greedy*/
int Greedy::Greedy_135(vector<int>& ratings) {
    int n = ratings.size();
    vector<int> candies(n, 1);  // 每個學生至少 1 顆糖

    // 左 -> 右 遍歷
    for (int i = 1; i < n; i++) {
        if (ratings[i] > ratings[i - 1]) {
            candies[i] = candies[i - 1] + 1;
        }
    }

    // 右 -> 左 遍歷
    for (int i = n - 2; i >= 0; i--) {
        if (ratings[i] > ratings[i + 1]) {
            candies[i] = max(candies[i], candies[i + 1] + 1);
        }
    }

    return accumulate(candies.begin(), candies.end(), 0);
}

/*與上面寫法不一樣，不過上面比較好*/
int Greedy::Greedy_MySol_135(vector<int>& ratings) {
    vector<int> child_candy(ratings.size(), 1);
    int candyup = 0;
    for (int i = 1; i < ratings.size(); i++) {
        if (ratings[i] > ratings[i - 1]) {
            candyup++;
            child_candy[i] += candyup;
        }
        else
            candyup = 0;
    }
    candyup = 1;
    for (int i = ratings.size() - 2; i >= 0; i--) {
        if (ratings[i] > ratings[i + 1]) {
            candyup++;
            child_candy[i] = std::max(child_candy[i], candyup);
        }
        else
            candyup = 1;
    }
    return std::accumulate(child_candy.begin(), child_candy.end(), 0);
}
#pragma endregion

#pragma region Leetcode 455. Assign Cookies
//Leetcode 455. Assign Cookies
int Greedy::Leetcode_Sol_455(vector<int>& g, vector<int>& s, int _solution) {
    switch (_solution)
    {
    case 1:
        return Greedy_455(g, s);

    default:
        return false; // 確保所有路徑都有回傳值
    }

    return false;
}

/*主要判別：只要比小孩數值大的餅就給他 (雙指標 + sort)，一顆星可不看!*/
int Greedy::Greedy_455(vector<int>& g, vector<int>& s) {
    std::sort(g.begin(), g.end());
    std::sort(s.begin(), s.end());
    int cookie = 0;
    int person = 0;
    int icount = 0;
    while (cookie < s.size() && person < g.size()) {
        if (g[person] <= s[cookie]) {
            icount++;
            person++;
            cookie++;
        }
        else {
            cookie++;
        }
    }
    return icount;
}
#pragma endregion

#pragma region Leetcode 376. Wiggle Subsequence
//Leetcode 376. Wiggle Subsequence
int Greedy::Leetcode_Sol_376(vector<int>& nums, int _solution) {
    switch (_solution)
    {
    case 1:
        return Greedy_376(nums);
    case 2:
        return Greedy_MySol_376(nums);

    default:
        return false; // 確保所有路徑都有回傳值
    }

    return false;
}

/*主要判別：轉折點*/
/*說明：
局部最優解在於你只需要知道轉則處為局部最高點與最低點即可=>就一定可以形成最優解*/
int Greedy::Greedy_376(vector<int>& nums) {
    if(nums.size() < 2) return nums.size();
    int icount = 1, inflectpoint = nums[0];
    int curdif = 0,predif = 0;
    vector<int> ans;
    ans.push_back(inflectpoint);

    for(int i = 1;i<nums.size();i++){
        curdif = nums[i]-nums[i-1];
        inflectpoint = nums[i];
        if(curdif > 0 && predif <= 0 || curdif < 0 && predif >= 0){
            icount++;
            predif = curdif;
            ans.push_back(inflectpoint);
        }
    }
     return icount;
     //return ans; //要找的是局部上升or下降的最大值 (自創題：找最大與最小轉擇點)
}
    


/*比較土的方式，不過時間複雜度O(n)*/
int Greedy::Greedy_MySol_376(vector<int>& nums) {
    std::deque<int> longestsub;
    longestsub.push_back(nums[0]);
    int Ascending = 0, Dscending = 0;
    bool bAscending = false, bDscending = false;

    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] > longestsub.back() && (!bAscending || bDscending)) {
            if (i + 1 < nums.size() && nums[i] <= nums[i + 1]) {
                continue;
            }
            bAscending = true;
            bDscending = false;
            Ascending++;
            longestsub.push_back(nums[i]);
        }
        else if (nums[i] < longestsub.back() && (bAscending || !bDscending)) {
            if (i + 1 < nums.size() && nums[i] >= nums[i + 1]) {
                continue;
            }
            bAscending = false;
            bDscending = true;
            Dscending++;
            longestsub.push_back(nums[i]);
        }
    }
    return Ascending + Dscending + 1;//記得+1的原因，最一開始被push_back進去的nums[0]
}
#pragma endregion

#pragma region Leetcode 2136. Earliest Possible Day of Full Bloom
//Leetcode 2136. Earliest Possible Day of Full Bloom
int Greedy::Leetcode_Sol_2136(vector<int>& plantTime, vector<int>& growTime, int _solution) {
    switch (_solution)
    {
    case 1:
        return Greedy_2136(plantTime, growTime);

    default:
        return false; // 確保所有路徑都有回傳值
    }

    return false;
}

/*主要判別：「生長時間長的花應該先種」，這樣可以最大化地利用並行種植的特性*/
/*說明：因為Greedy的緣故，所以能在種植(Plant)與生長(Grow)能重疊的時間最大化(省的時間越多)
        換句話說，我們會希望把生長日子越多天的先種(那就能先讓重疊度使用最大化)*/
int Greedy::Greedy_2136(vector<int>& plantTime, vector<int>& growTime) {
    vector<pair<int, int>> flowers(plantTime.size());
    for (size_t i = 0; i < plantTime.size(); i++) {
        //法一：
        //flowers[i].first = growTime[i];
        //flowers[i].second = plantTime[i];
        //法二：
        flowers[i] = { growTime[i], plantTime[i] };
    }

    std::sort(flowers.begin(), flowers.end(), CompareByPair_Descending());
    //std::sort(flowers.begin(),flowers.end(),great<>());
    /*greater<>：自動推導型(c++11)，適用於 pair<int, int>，並按 first 降序，若 first 相同則按 second 降序。*/
    

    int curplant = 0, minday = 0;
    //因為Greedy的緣故，所以能在種植(Plant)與生長(Grow)能重疊的時間最大化(省的時間越多)
    //標準打法：
    for (int i = 0; i < flowers.size(); i++) {
        curplant += flowers[i].second;  // 累積種植時間(因為Plant的時候不能做其他事情，所以她一定要獨立出來)
        minday = std::max(minday, curplant + flowers[i].first); //計算最晚開花日：因為種植(Plant)的累加天數會超過前面Grow的天數，所以要更新最大天數
    }

    #pragma region for迴圈打法
    //c++14：
    /*for (auto& flower : flowers) {
        auto& g = flower.first;  // 第一個元素
        auto& p = flower.second; // 第二個元素
        curplant += p;
        minday = std::max(minday, curplant + g);
    }*/
    //C++17的解法：
    /*for (auto [g, p] : flowers) {
        curplant += p;   //累加時間(因為Plant的時候不能做其他事情，所以她一定要獨立出來)
        minday = std::max(minday, curplant + g);//因為種植(Plant)的累加天數會超過前面Grow的天數，所以要更新最大天數
    }*/
    #pragma endregion

    return minday;
}
#pragma endregion

#pragma region Leetcode 621. Task Scheduler
//Leetcode 621. Task Scheduler
int Greedy::Leetcode_Sol_621(vector<int>& tasks,int n, int _solution) {
    switch (_solution)
    {
    case 1:
        return Greedy_simulation_cooldowntasks_621(tasks,n);
    case 2:
        return Greedy_formula_unordered_map_621(tasks,n);
    case 3:
        return Greedy_formula_vector_621(tasks, n);

    default:
        return false; // 確保所有路徑都有回傳值
    }

    return false;
}

/*主要判別：最頻繁的task優先做! (priority_queue + queue + Greedy)*/
int Greedy::Greedy_simulation_cooldowntasks_621(vector<int>& tasks,int n) {
    unordered_map<char, int> maps;
    int times = 0;
    for (int i = 0; i < tasks.size(); i++) {
        maps[tasks[i]]++;
    }
    priority_queue<int> dotask;
    for (auto map : maps) {
        dotask.push(map.second);
    }

    std::queue<pair<int, int>> cooldown;
    while (!cooldown.empty() || !dotask.empty()) {
        times++;
        if (!dotask.empty()) {
            int count_temp = dotask.top() - 1;
            dotask.pop();        //pop出來做事情
            if (count_temp > 0) {//這個label還有事情做，那就先放回冷卻queue進行冷卻(不是times + n + 1 的原因：當在times + n的時候會先做pop()的動作)
                cooldown.push({ count_temp,times + n });    
            }
        }
        if (!cooldown.empty() && cooldown.front().second == times) { //到時的前一次把冷卻好的放回去，因為下一次準備換執行他的任務
            dotask.push(cooldown.front().first);
            cooldown.pop();
        }
    }
    return times;
}

/*這個不會難推導，用greedy的概念，把最頻繁的任務拿出來就推導的出來了*/
/*公式：max((maxFreq - 1) * (n + 1) + maxCount, (int)tasks.size())*/
int Greedy::Greedy_formula_unordered_map_621(vector<int>& tasks, int n) {
    unordered_map<char, int> map;
    int maxlabel = 0;
    for (int i = 0; i < tasks.size(); i++) {
        map[tasks[i]]++;
        maxlabel = std::max(map[tasks[i]], maxlabel);
    }
    int maxcount = 0;
    for (auto label : map) {
        if (label.second == maxlabel) maxcount++;
    }
    int calculate = (maxlabel - 1) * (n + 1) + maxcount;
    return std::max((int)tasks.size(), calculate);//注意：size()是size_t型別，並非int，max要求type一致
}

int Greedy::Greedy_formula_vector_621(vector<int>& tasks, int n) {
    vector<int> freq(26, 0);//因為最多就26字母 => 26個label
    for (char task : tasks) {
        freq[task - 'A']++;
    }

    int maxFreq = *max_element(freq.begin(), freq.end());
    int maxCount = count(freq.begin(), freq.end(), maxFreq);

    return max((maxFreq - 1) * (n + 1) + maxCount, (int)tasks.size());
}
#pragma endregion

#pragma region Leetcode 406. Queue Reconstruction by Height
//Leetcode 406. Queue Reconstruction by Height
vector<vector<int>> Greedy::Leetcode_Sol_406(std::vector<std::vector<int>>& people, int _solution) {
    switch (_solution)
    {
    case 1:
        return Greedy_406(people);
    case 2:
        return BinaryIndexedTree_406(people);
    case 3:
        return SegmentTree_406(people);

    default:
        return {}; // 確保所有路徑都有回傳值
    }

    return {};
}
/*主要判別：每個人都可以看到前面的人;換句話說，只要先排序：身高 h 降序，k 升序 (Greedy + insert)*/
/*說明：上述Greedy的局部化最佳化，因為當前比他高的人已經排入，所以只需要管看到前面有幾個人就插入當下那個位置即可(之後的人比她矮所以不構成影響)
時間複雜度：
1.Sorting the list takes O(nlogn)
2.Inserting each person into the result list takes O(n^2) (位移O(n)* 每個元素O(n)) 

空間複雜度：
The space complexity is O(n) because we need space to store the final reconstructed queue.
(Additionally, the sorting step uses constant extra space (depending on the sorting algorithm))*/
vector<vector<int>> Greedy::Greedy_406(std::vector<std::vector<int>>& people) {
    // 先排序：身高 h 降序，k 升序
    sort(people.begin(), people.end(), [](vector<int>& a, vector<int>& b) {
        return (a[0] > b[0]) || (a[0] == b[0] && a[1] < b[1]);
        });

    // 依照 k 插入
    vector<vector<int>> result;
    for (auto& p : people) {
        result.insert(result.begin() + p[1], p);
    }

    return result;
}

#pragma region BinaryIndexedTree_406
vector<vector<int>> Greedy::BinaryIndexedTree_406(std::vector<std::vector<int>>& people) {
    int n = people.size();
    sort(people.begin(), people.end(),
        [](vector<int>& p1, vector<int>& p2) {
            if (p1[0] == p2[0])
                return p1[1] > p2[1];
            return p1[0] < p2[0];
        });
    vector<int> bit(n + 1);
    for (int i = 0; i < n; i++)
        update_BIT(bit, i + 1, 1);
    vector<vector<int>> ans(n);
    for (int i = 0; i < n; i++) {
        int l = 0, r = n - 1;
        while (l < r) {
            int m = l + (r - l) / 2;
            if (query_BIT(bit, m + 1) < people[i][1] + 1)
                l = m + 1;
            else
                r = m;
        }
        ans[l] = people[i];
        update_BIT(bit, l + 1, -1);
    }
    return ans;
}
void Greedy::update_BIT(vector<int>& bit, int idx, int delta) {
    for (int i = idx; i < bit.size(); i += i & -i)
        bit[i] += delta;
}
int Greedy::query_BIT(vector<int>& bit, int idx) {
    int sum = 0;
    for (int i = idx; i > 0; i -= i & -i)
        sum += bit[i];
    return sum;
}
#pragma endregion

#pragma region SegmentTree_406

std::vector<int> tree_406; //BIT、ST
vector<vector<int>>  Greedy::SegmentTree_406(std::vector<std::vector<int>>& people) {
    sort(people.begin(), people.end(), [](vector<int>a, vector<int>b) {
        if (a[0] != b[0]) return a[0] < b[0];
        return a[1] > b[1];
        });
    int n = people.size();
    tree_406.clear();
    tree_406.resize(4 * n + 10);
    vector<vector<int>> res(people.size(), vector<int>());
    build_ST(1, 0, n - 1);
    for (int i = 0; i < people.size(); i++) {
        int j = query_ST(1, 0, n - 1, people[i][1] + 1);
        res[j] = people[i];
        update_ST(1, 0, n - 1, j);
    }
    return res;
}
void Greedy::build_ST(int node, int start, int end) {
    if (start == end) {
        tree_406[node] = 1;
        return;
    }
    int mid = (start + end) / 2;
    build_ST(2 * node, start, mid);
    build_ST(2 * node + 1, mid + 1, end);
    tree_406[node] = tree_406[2 * node] + tree_406[2 * node + 1];
}

int Greedy::query_ST(int node, int start, int end, int k) {
    if (start == end) {
        return start;
    }
    int mid = (start + end) / 2;
    int left = tree_406[2 * node];
    int right = tree_406[2 * node + 1];
    if (k > left) {
        return query_ST(2 * node + 1, mid + 1, end, k - left);
    }
    else {
        return query_ST(2 * node, start, mid, k);
    }
}

void Greedy::update_ST(int node, int start, int end, int idx) {
    if (start == end) {
        tree_406[node] = 0;
        return;
    }
    int mid = (start + end) / 2;
    if (idx <= mid) {
        update_ST(2 * node, start, mid, idx);
    }
    else {
        update_ST(2 * node + 1, mid + 1, end, idx);
    }
    tree_406[node] = tree_406[2 * node] + tree_406[2 * node + 1];
}
#pragma endregion

#pragma endregion






#pragma endregion


#pragma endregion






