#include <iostream>
#include <queue>
#include <array>
#include <deque>
#include <vector>
using namespace std;

//Завдання 1
int task1(string s)
{
    queue<pair<char, int>> q;
    int num = 0, index;

    for (char c : s)
    {
        int num = 0;
        for (char c1 : s)
        {
            if (c == c1)
                num++;
        }

        q.push(make_pair(c, num));
    }

    while(!q.empty())
    {
        if (q.front().second == 1)
        {
            index = s.find(q.front().first);
            return index;
        }
        q.pop();
    }

    return '-1';
}

//Завдання 2
class MyStack {
    queue<int> input, output;
public:

    void push(int val)
    {
        input.push(val);
    }

    int pop()
    {
        int res;
        while (input.size() > 1)
        {
            output.push(input.front());
            input.pop();
        }
        res = input.front();
        input.pop();
        input.swap(output);

        return res;
    }

    int top(){
        int res;
        while (input.size() > 1)
        {
            output.push(input.front());
            input.pop();
        }
        res = input.front();
        output.push(input.front());
        input.pop();
        input.swap(output);

        return res;
    }

    bool empty()
    {
        return input.empty() && output.empty();
    }

    void printStack()
    {
        while (!input.empty())
        {
            cout << input.front() << " ";
            output.push(input.front());
            input.pop();
        }

        input.swap(output);
    }
};

//Завдання 3
class RecentCounter {
    queue<int> requests;
public:
    RecentCounter(){}
    int ping(int t)
    {
        requests.push(t); 

        while (!requests.empty() && requests.front() < t - 3000) {
            requests.pop();
        }

        return requests.size();
    }
};

//Завдання 4
class MyCircularQueue {
    vector<int> data;
    int front;
    int rear;
    int size;
    int capacity;
public:
    MyCircularQueue(int k) {
        data.resize(k);
        front = -1;
        rear = -1;
        size = 0;
        capacity = k;
    }

    int Front(){
        if (isEmpty()) return -1;
        return data[front];
    }
    int Rear(){
        if (isEmpty()) return -1;
        return data[rear];
    }
    bool enQueue(int value){
        if (isFull()) return false;

        if (isEmpty()) {
            front = 0;
        }

        rear = (rear + 1) % capacity;
        data[rear] = value;
        size++;

        return true;
    }
    bool deQueue() {
        if (isEmpty()) return false;

        if (front == rear) {
            front = -1;
            rear = -1;
        }
        else {
            front = (front + 1) % capacity;
        }

        size--;
        return true;
    }
    bool isEmpty(){ return size == 0; }
    bool isFull(){ return size == capacity; }
};

//Завдання 5
class  task5{
public:
    vector<int> movesToStamp(string stamp, string target) {
        int m = stamp.size(), n = target.size();
        vector<int> indeg(n - m + 1, m);
        vector<vector<int>> g(n);
        queue<int> q;
        for (int i = 0; i < n - m + 1; ++i) {
            for (int j = 0; j < m; ++j) {
                if (target[i + j] == stamp[j]) {
                    if (--indeg[i] == 0) {
                        q.push(i);
                    }
                }
                else {
                    g[i + j].push_back(i);
                }
            }
        }
        vector<int> ans;
        vector<bool> vis(n);
        while (q.size()) {
            int i = q.front();
            q.pop();
            ans.push_back(i);
            for (int j = 0; j < m; ++j) {
                if (!vis[i + j]) {
                    vis[i + j] = true;
                    for (int k : g[i + j]) {
                        if (--indeg[k] == 0) {
                            q.push(k);
                        }
                    }
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            if (!vis[i]) {
                return {};
            }
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};

//Завдання 6
vector<int> task6(vector<int>& nums, int k) {
    if (nums.empty() || k <= 0) {
        return {};
    }

    int n = nums.size();
    vector<int> result;
    deque<int> window;

    for (int i = 0; i < n; ++i) {
        if (!window.empty() && window.front() == i - k) {
            window.pop_front();
        }

        while (!window.empty() && nums[i] >= nums[window.back()]) {
            window.pop_back();
        }

        window.push_back(i);

        if (i >= k - 1) {
            result.push_back(nums[window.front()]);
        }
    }

    return result;
}

//Завдання 7
int task7(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> dp(n);

    deque<int> dq;
    int maxSum = nums[0];
    dp[0] = nums[0];

    for (int i = 0; i < n; ++i) {
        while (!dq.empty() && i - dq.front() > k) {
            dq.pop_front();
        }

        dp[i] = nums[i];
        if (!dq.empty()) {
            dp[i] += max(0, dp[dq.front()]);
        }

        while (!dq.empty() && dp[i] >= dp[dq.back()]) {
            dq.pop_back();
        }

        dq.push_back(i);
        maxSum = max(maxSum, dp[i]);
    }

    return maxSum;
}

int main()
{
    cout << task1("leopard") << '\n';
    MyStack mst;
    mst.push(4);
    mst.push(-1);
    mst.push(5);
    mst.push(7);
    mst.push(33);
    mst.printStack();
    cout << "\nPop: " << mst.pop() << endl;
    mst.printStack();
    cout << "\nTop: " << mst.top() << "\n";
    (mst.empty()) ? cout << "Empty" : cout << "Not empty";
    MyStack st;
    cout << "\n";
    (st.empty()) ? cout << "Empty" : cout << "Not empty";
    cout << "\n";

    RecentCounter counter;
    cout << counter.ping(1) << endl;    
    cout << counter.ping(100) << endl;  
    cout << counter.ping(3001) << endl; 
    cout << counter.ping(3002) << endl << endl;


    MyCircularQueue myCircularQueue(3);
    cout << myCircularQueue.enQueue(1) << endl; 
    cout << myCircularQueue.enQueue(2) << endl; 
    cout << myCircularQueue.enQueue(3) << endl; 
    cout << myCircularQueue.enQueue(4) << endl; 
    cout << myCircularQueue.Rear() << endl; 
    cout << myCircularQueue.isFull() << endl; 
    cout << myCircularQueue.deQueue() << endl;
    cout << myCircularQueue.enQueue(4) << endl;
    cout << myCircularQueue.Rear() << endl;

    string stamp = "abc", target = "ababc";
    task5 t5;
    vector<int> v = t5.movesToStamp(stamp, target);
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }

    vector<int> nums = { 1, 3, -1, -3, 5, 3, 6, 7 };
    int k = 3;

    cout << endl;
    vector<int> res = task6(nums, k);
    for (int i = 0; i < res.size(); i++)
    {
        cout << res[i] << " ";
    }

    vector<int> nums1 = { 10, 2, -10, 5, 20 };
    int k1 = 2;

    cout << "\n" << task7(nums1, k1) << endl;
}

