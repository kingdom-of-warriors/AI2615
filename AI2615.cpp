#include <bits/stdc++.h>
using namespace std;

/*
//9.26 T1953 Partition

pair<int, int> partition(vector <int>& a, int pivot) {
    int len = a.size(); //数组长度
    int k = 0,i = 0,j = len - 1; //左右边界，i左边是小于区，j右边是大于区，k是扫描区域

    while(k <= j)
    {
        if(a[k] < pivot) //小于，则与<区最后一个交换
        {
            swap(a[i],a[k]);
            i++; //小于区向右扩
            k++;
        }
        else if(a[k] > pivot)
        {
            swap(a[k],a[j]);
            j--; //大于区域向左扩
        }
        else k++; //等于，直接向左
    }

    return pair<int,int>(i,j+1);
}

int main() {
    int n, pivot;
    cin >> n >> pivot;
    vector <int> arr;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        arr.push_back(x);
    }
    auto [l, r] = partition(arr, pivot);
    for (auto i : arr) cout << i << ' ';
    cout << '\n' << l << ' ' << r << '\n';
}
*/


/*
//9.26 T1301 bubbling bubbles

class Solution {
public:
    vector<int> res;
    Solution(int len) {res.resize(len);} //初始化答案数组

    void mergeSort(int left,int right,vector<int>& arr) //归并排序
    {
        if(left == right) return;

        int mid = (right - left)/2 + left; //计算中间数
        mergeSort(left,mid,arr);
        mergeSort(mid + 1,right,arr);

        vector<int> tmp(right - left + 1); //临时数组
        int i1 = left,i2 = mid + 1,j = 0;
        int add = 0; //这里是每一项需要的加数

        while(i1 <= mid && i2 <= right)
        {
            if(arr[i1] < arr[i2]) //没有逆序对贡献，但将arr[i1]逆序对算完
            {
                res[arr[i1] - 1] += add;
                tmp[j++] = arr[i1++];
            }
            else if(arr[i1] > arr[i2]) //有逆序对贡献
            {
                res[arr[i2] - 1] += mid - i1 + 1; //当前及之后的左边的数都比arr[i2]大，给arr[i2]贡献了这么多逆序对数
                add++; //当前及之后的左边的数，每个res都要+1
                tmp[j++] = arr[i2++];
            }
        }

        while(i2 <= right) tmp[j++] = arr[i2++]; //对逆序对没有贡献

        while(i1 <= mid) //有贡献
        {
            res[arr[i1] - 1] += add;
            tmp[j++] = arr[i1++];
        }
        
        for(j = left;j <= right;j++) arr[j] = tmp[j - left];
    }

    void printRes() {for(int i : res) cout << i <<' ';}
};

int main()
{
    int len = 0;vector<int> a; //初始化所有的东西
    cin >> len;
    for(int i = 0;i < len;i++)
    {
        int x;cin >> x;
        a.push_back(x);
    }

    Solution A(len);
    A.mergeSort(0,len - 1,a);
    A.printRes();
}
*/


/*
//9.27 第k小的数（用中位数的中位数）
vector <int> a;

pair<int, int> partition(int pivot) //复活partition，分为三组
{    
    int len = a.size(); //数组长度
    int k = 0,i = 0,j = len - 1; //左右边界，i左边是小于区，j右边是大于区，k是扫描区域

    while(k <= j)
    {
        if(a[k] < pivot) //小于，则与<区最后一个交换
        {
            swap(a[i],a[k]);
            i++; //小于区向右扩
            k++;
        }
        else if(a[k] > pivot)
        {
            swap(a[k],a[j]);
            j--; //大于区域向左扩
        }
        else k++; //等于，直接向左
    }

    return pair<int,int>(i,j+1);
}

int findGoodPivot(int left,int right);

int FindkSmall(int left,int right,int k)
{
    if(right - left + 1 < 5) //数比较少
    {
        sort(a.begin() + left,a.begin() + right + 1); //数字较少，直接排就好
        return a[left + k - 1];
    }

    int pivot = findGoodPivot(left,right); //找到中位数的中位数

    pair<int,int> part = partition(pivot); //划分
    if(k <= part.first) return FindkSmall(left,part.first - 1,k); //递归调用
    else if (k >= part.second + 1) return FindkSmall(part.second,right,k);
    else return a[part.first]; //直接返回
}

int findGoodPivot(int left,int right)
{
    if(right - left + 1 < 5) //数比较少
    {
        sort(a.begin() + left,a.begin() + right + 1); //数字较少，直接排就好
        return a[(left + right) / 2];
    }

    int len = (right - left + 1)/5; //能分多少个组（取出多少个中位数）
    for(int i = 0;i < len;i++) //同时找到中位数
    {
        int tmp = left + 5 * i;
        sort(a.begin() + tmp,a.begin() + tmp + 5); //数字较少，直接排就好
        swap(a[i],a[tmp + 2]); //把中位数交换到前面
    }

    return FindkSmall(left,left + len - 1,(len + 1)/2); //中位数的中位数
}


int main()
{
    int n, k, m;
    //读入数据
    cin >> n >> k >> m; a.resize(n);
    for (int i = 0; i < m; i++)
    {
        cin >> a[i];
    }
    unsigned int z = a[m - 1];
    for (int i = m; i < n; i++)
    {
        z ^= z << 13;
        z ^= z >> 17;
        z ^= z << 5;
        a[i] = z & 0x7fffffff;
    }
    
    cout << FindkSmall(0,n - 1,k);
}
*/


/*
//9.28 T1299 不用版本
vector<int> a;
int n,k;

int FindkSmall(int left,int right)
{
    while(true)
    {
        srand(time(0));
        int pivot = a[rand() % (right - left + 1) + left]; //随机序号
        int w = left,i = left,j = right; //左右边界，i左边是小于区，j右边是大于区，k是扫描区域

        while(w <= j)
        {
            if(a[w] < pivot) //小于，则与<区最后一个交换
            {
                swap(a[i],a[w]);
                i++; //小于区向右扩
                w++;
            }
            else if(a[w] > pivot)
            {
                swap(a[w],a[j]);
                j--; //大于区域向左扩
            }
            else w++; //等于，直接向左
        }

        if(k <= i) right = i - 1; //循环调用
        else if (k >= j + 2) left = j + 1;
        else return a[i];
    }

    return -1;
}


int main()
{
    int m;
    //读入数据
    scanf("%d%d%d", &n, &k, &m);a.resize(n);
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &a[i]);
    }
    unsigned int z = a[m - 1];
    for (int i = m; i < n; i++)
    {
        z ^= z << 13;
        z ^= z >> 17;
        z ^= z << 5;
        a[i] = z & 0x7fffffff;
    }
    
    printf("%d",FindkSmall(0,n - 1));
}
*/


/*
//9.28 T1299

typedef long long LL;
const long long INF = 1e18;

LL pow_2 (LL x) {
    return x * x;
}

struct point {
    LL x, y;
    point (LL _x, LL _y) : x(_x), y(_y) {} //初始化
    long long distance_2 (const point & other) const {
        return pow_2(x - other.x) + pow_2(y - other.y); //计算距离的函数
    }
};

LL solve (vector <point> &a, int l, int r) {
    if(l == r) return INF;
    if(l + 1 == r) return a[l].distance_2(a[r]); //剪枝

    int m = (r + l)/2; //中间的数
    LL ret = min(solve(a,l,m),solve(a,m,r)); //递归的最小值，也就是两个集合内部的最小值
    vector<point> strip; //用来储存两个集合中距离<ret的点

    for(int i = l;i <= r;i++)
    {
        if(pow_2(a[i].x - a[m].x) < ret) strip.push_back(a[i]);
    }
    sort(strip.begin(),strip.end(),[](auto &u,auto &v) { //对其进行排序
        return u.y < v.y;
    });
    int len = strip.size();

    for(int i = 0;i < len;i++)
    {
        for(int j = i + 1;j < len;j++)
        {
            if(pow_2(strip[i].y - strip[j].y) >= ret) break; //后面的也一定会小

            ret = min(ret,strip[i].distance_2(strip[j])); //更新ret
        }
    }
    
    return ret;
}

int main() {
    int n;
    cin >> n;
    vector <point> a;
    for (int i = 0; i < n; i++) {
        LL x, y;
        cin >> x >> y;
        a.push_back(point(x, y));
    }
    sort(a.begin(), a.end(), [](auto &u, auto &v) { //以x为先排序
        return u.x < v.x;
    });
    cout << solve (a, 0, n - 1) << endl; //wok，这里要改成n - 1，真离谱，我根本没看主函数，只改了一个数据类型
}
*/



/*
//10.5 T1982

typedef long double LD;
typedef long long LL;
const long long INF = 1e18;

LL pow_2 (LL x) {
    return x * x;
}

struct point {
    LL x, y;
    point (LL _x, LL _y) : x(_x), y(_y) {} //初始化
    LD circum(const point & other1,const point & other2) const {
        return sqrtl(pow_2(x - other1.x) + pow_2(y - other1.y)) + sqrtl(pow_2(x - other2.x) + pow_2(y - other2.y)) + sqrtl(pow_2(other2.x - other1.x) + pow_2(other2.y - other1.y)); //计算距离的函数
    }
};

LD solve (vector <point> &a, int l, int r) {
    if(l + 1 >= r) return INF; //剪枝
    if(l + 2 == r) return a[l].circum(a[l + 1],a[r]); //计算周长

    int m = (r + l)/2; //中间的数
    LD ret = min(solve(a,l,m),solve(a,m,r)); //递归的最小值，也就是两个集合内部的最小值
    vector<point> strip; //用来储存两个集合中距离<ret的点

    for(int i = l;i <= r;i++)
    {
        if(fabs(a[i].x - a[m].x) < ret/2) strip.push_back(a[i]); //注意加fabs!!!!
    }
    sort(strip.begin(),strip.end(),[](auto &u,auto &v) { //对其进行排序
        return u.y < v.y;
    });
    int len = strip.size();

    for(int i = 0;i < len;i++)
    {
        for(int j = i + 1;j < len;j++)
        {
            if(strip[j].y - strip[i].y >= ret/2) break; //后面的也一定会大
            for(int k = j + 1;k < len;k++)
            {
                if(strip[k].y - strip[i].y >= ret/2) break; //后面的也一定会大
                
                ret = min(ret,strip[i].circum(strip[j],strip[k])); //更新ret
            }
        }
    }
    
    return ret;
}

int main() {
    int n;
    cin >> n;
    vector <point> a;
    for (int i = 0; i < n; i++) {
        LL x, y;
        cin >> x >> y;
        a.push_back(point(x, y));
    }
    sort(a.begin(), a.end(), [](auto &u, auto &v) { //以x为先排序
        return u.x < v.x;
    });

    cout.setf(ios::fixed);
    cout << setprecision(9) << solve (a, 0, n - 1) << endl; //wok，这里要改成n - 1，真离谱，我根本没看主函数，只改了一个数据类型
}
*/


/*
//10.6 T1299 O(nlogn)写法

typedef long long LL;
const long long INF = 1e18;

LL pow_2 (LL x) {
    return x * x;
}

struct point {
    LL x, y;
    point() {}
    point (LL _x, LL _y) : x(_x), y(_y) {} //初始化
    long long distance_2 (const point & other) const {
        return pow_2(x - other.x) + pow_2(y - other.y); //计算距离的函数
    }
};

vector<point> a;

LL solve (int l, int r) {
    if(l == r) return INF;
    else if(l + 1 == r) return a[l].distance_2(a[r]); //剪枝

    int m = (r + l)/2; //中间的数
    LL pivot = a[m].x; //记录这个中位数，后面可能会变
    LL ret = min(solve(l,m),solve(m,r)); //递归的最小值，也就是两个集合内部的最小值

    //在这里按照y来merge
    vector<point> tmp(r - l + 1); //用来储存两个集合中距离<ret的点
    int k = 0,i = l,j = m; //起始点
    while(i <= m - 1 && j <= r)
    {
        tmp[k++] = (a[i].y < a[j].y) ? a[i++] : a[j++]; //归并过程
    }
    while(i <= m - 1) tmp[k++] = a[i++];
    while(j <= r) tmp[k++] = a[j++];

    for(i = 0;i <= r - l;i++) a[i + l] = tmp[i];
    //merge完成

    k = 0; //重新编排序号
    for(int i = l;i <= r;i++)
    {
        if(pow_2(a[i].x - pivot) < ret) tmp[k++] = a[i];
    }

    for(int i = 0;i < k;i++)
    {
        for(int j = i + 1;j < k;j++)
        {
            if(pow_2(tmp[j].y - tmp[i].y) >= ret) break; //后面的也一定会小

            ret = min(ret,tmp[i].distance_2(tmp[j])); //更新ret
        }
    }
    
    return ret;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        LL x, y;
        cin >> x >> y;
        a.push_back(point(x, y));
    }
    sort(a.begin(), a.end(), [](auto &u, auto &v) { //以x为先排序
        return u.x < v.x;
    });
    cout << solve (0, n - 1) << endl; //wok，这里要改成n - 1，真离谱，我根本没看主函数，只改了一个数据类型
}
*/


/*
//10.25 T1342 Shortest Path、无优化版本
typedef long long LL;
LL mat[2503][2503]; //邻接矩阵储存
int n, m, s, t; //n个点m条边，要求s到t，1-based

LL dijkstra()
{
    vector<bool> isFind(n + 1, false); //是否有找过
    vector<LL> res(n + 1); //找过的最小值 
    for(int i = 1;i <= n;i++)
    {
        res[i] = mat[s][i]; //赋初值
    }

    // 开始算法
    isFind[s] = true;
    for(int i = 1;i <= n;i++)
    {
        //取出没访问过的、离起点最近的点
        LL mini = LONG_LONG_MAX; int min_idx = 0; //最小长度以及其对应的点
        for(int j = 1;j <= n;j++)
        {
            if(!isFind[j] && res[j] != -1 && res[j] < mini) //没找过且有边
            {
                mini = res[j];
                min_idx = j;
            }
        }
        isFind[min_idx] = true; //已经访问过

        //更新
        for(int j = 1;j <= n;j++)
        {
            if(!isFind[j] && mat[j][min_idx] != -1) //没访问过并且j和min_idx之间有边
            {
                LL tmp = mat[j][min_idx] + res[min_idx];
                if(tmp < res[j] || res[j] == -1) //如果原来比较小或者是它们之间没有边，则更新
                {
                    res[j] = tmp;
                }
            }
        }
    }
    return res[t];
}

int main()
{
    cin >> n >> m >> s >> t;
    int i, j;
    for(i = 1;i <= n;i++)
    {
        for(j = 1;j <= n;j++) mat[i][j] = -1; //没有边
    }
    for(i = 0;i < m;i++)
    {
        int a,b;LL dis;
        cin >> a >> b >> dis;
        if(mat[a][b] != -1) //之前已经有边，考虑到可能有重边
        {
            mat[a][b] = mat[b][a] = min(dis, mat[a][b]);
        }
        else //之前没边
        {
            mat[a][b] = mat[b][a] = dis;
        }
    }
    cout << dijkstra();
}
*/

/*
//11.2
typedef long long LL;
int n, m, s ,t; // n个点m条边，要求s到t，1-based
vector<vector<pair<int, LL>>> adj; //邻接表储存，第二个LL是距离

struct cmp1 //比较类
{
    bool operator()(const pair<LL, int> &a, const pair<LL, int> &b)
    {
        return a.first > b.first;
    }
};

LL dijstra()
{
    priority_queue<pair<LL, int>, vector<pair<LL, int>>, cmp1> que; //优先队列，当前距离以及标号
    vector<LL> res(n + 1, LONG_LONG_MAX); //储存当前的答案
    res[s] = 0;
    que.emplace(0, s);
    while(!que.empty())
    {
        auto[dis, idx] = que.top(); que.pop(); //取堆顶元素并弹出
        if(dis > res[idx]) continue; //已经多次入队，相当于剪枝

        for(auto& [idx_next, dis_next] : adj[idx]) //在该点能访问到的其它点
        {
            if(res[idx_next] > dis_next + dis)
            {
                res[idx_next] = dis_next + dis; //更新
                que.emplace(res[idx_next], idx_next);
            }
        }
    }
    return res[t];
}

int main()
{
    cin >> n >> m >> s >> t;
    adj.resize(n + 1);
    for(int i = 0;i < m;i++) //输入边
    {
        int a, b; LL dis;
        cin >> a >> b >> dis;
        adj[a].push_back(pair<int, LL>(b, dis)); adj[b].push_back(pair<int, LL>(a, dis)); //存入边
    }
    cout << dijstra();
}
*/


/*
//11.1 T1985

int n, m, s, t; //全局变量 点数、边数、目标起点、目标终点、序号
vector < pair <int, int> > edges;
vector<vector<int>> adj; //邻接表储存
vector<int> res; //答案数组
vector<int> isSear; //是否寻找过

bool find_path(int s) { //使用回溯法，从s开始访问
    isSear[s] = 1; res.push_back(s); //初始化寻找和答案数组
    if(s == t) return true;//找到了

    for(int next : adj[s])
    {
        if(isSear[next] == 0) //没访问过
        {
            if(find_path(next)) return true; //如果中间有找到的，则返回true
        }
    }    

    res.pop_back(); 
    //isSear[s] = 0; 
    return false;//回溯法返回，而且这条路上没有找到
}

int main() {
    cin >> n >> m >> s >> t;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        edges.push_back({u, v});
    }
    adj.resize(n + 1); isSear.resize(n + 1); 
    for(auto edge : edges) //初始化邻接表
    {
        int a = edge.first, b = edge.second;
        adj[a].push_back(b); //a->b
    }
    
    find_path(s);
    if (!res.size()) cout << "-1\n";
    else {
        cout << res.size() << '\n';
        for (auto i : res) {
            cout << i << (i == t ? '\n' : ' ');
        }
    }
}
*/

/*
//11.16 T1985 用栈模拟，行不通，但是可以知道有没有路径，用以解决assignment2 T1

int n, m, s, t; //全局变量 点数、边数、目标起点、目标终点、序号
vector < pair <int, int> > edges;
vector<vector<int>> adj; //邻接表储存
vector<int> res; //答案数组
vector<int> isSear; //是否寻找过
stack<int> stk; //用栈模拟DFS

bool find_path(int s) { //使用回溯法，从s开始访问
    isSear[s] = 1; res.push_back(s); //初始化寻找和答案数组
    if(s == t) return true;//找到了
    stk.push(s); //入栈
    
    int top; //栈顶元素
    while(!stk.empty())
    {
        top = stk.top(); stk.pop(); //取出栈顶元素并弹出
        res.push_back(top); //进入答案候选
        if(top == t) return true; //又找到啦
        for(int next : adj[top])
        {
            if(isSear[next] == 0) //没访问过
            {
                isSear[next] = 1; //添加访问标志
                stk.push(next); //将这个节点推入栈中
            }
        }
        res.pop_back();    
    }
    //到这里就是没找到
    return false;
}

int main() {
    cin >> n >> m >> s >> t;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        edges.push_back({u, v});
    }
    adj.resize(n + 1); isSear.resize(n + 1); 
    for(auto edge : edges) //初始化邻接表
    {
        int a = edge.first, b = edge.second;
        adj[a].push_back(b); //a->b
    }
    
    find_path(s);
    if (!res.size()) cout << "-1\n";
    else {
        cout << res.size() << '\n';
        for (auto i : res) {
            cout << i << (i == t ? '\n' : ' ');
        }
    }
}
*/


/*
//11.13 T1340

typedef long long LL;
LL res = 0; //答案需要LL
int m, n; //边数、点数
vector<vector<int>> adj; //邻接表储存
vector<vector<int>> adj_; //反图储存
vector<int> order; //表示节点的访问顺序
vector<int> visited1; //访问标志1
vector<int> visited2; //访问标志2

void dfs1(int idx) //第一个DFS，用来找到遍历的顺序
{
    visited1[idx] = 1; //添加访问标志
    for(int next : adj[idx]) //对它的邻点进行DFS
    {
        if(!visited1[next]) dfs1(next);
    }
    order.push_back(idx); //访问顺序记录，即先结束的先记录
}

LL dfs2(int idx) //第二个DFS，用来找到强连通分量中以idx为开始的顶点个数
{
    visited2[idx] = 1; 
    LL num = 1; //记录SCC的顶点个数
    for(int next : adj_[idx])
    {
        if(!visited2[next]) num += dfs2(next); //顶点个数加上这么多
    }

    return num;
}

int main()
{
    cin >> n >> m;
    adj.resize(n + 1); adj_.resize(n + 1); visited1.resize(n + 1); visited2.resize(n + 1);//访问是1，没访问是0
    while(m--)
    {
        int a, b;
        cin >> a >> b;
        if(a != b) {adj[a].push_back(b); adj_[b].push_back(a);} //防止重边出现
    }

    //开始操作
    for(int i = 1;i <= n;i++)
    {
        if(!visited1[i]) dfs1(i); //如果没有访问，就DFS
    }
    for(int i = n - 1;i >= 0;i--)
    {
        int j = order[i]; //第n-i个访问的数
        if(!visited2[j])
        {
            LL tmp = dfs2(j);
            res += (tmp*(tmp - 1))/2;
        }
    }
    cout << res;
}
*/


/*
//11.14 T1341

int m, n; //边数/2、点数/2
vector<int> order; //表示节点的访问顺序
vector<vector<int>> adj; //邻接表储存
vector<vector<int>> adj_; //反图储存
vector<int> visited1; //访问标志1
vector<int> visited2; //访问标志2
vector<int> SCC; //最后经过缩点得到的排序
vector<int> res; //答案数组
int r = 1; //排序的顺序

void dfs1(int idx) //第一个DFS，用来找到遍历的顺序
{
    visited1[idx] = 1; //添加访问标志
    for(int next : adj[idx]) //对它的邻点进行DFS
    {
        if(!visited1[next]) dfs1(next);
    }
    order.push_back(idx); //访问顺序记录，即先结束的先记录
}

void dfs2(int idx) //第二个DFS，用来找到强连通分量中以idx为开始的顶点个数
{
    visited2[idx] = 1; 
    SCC[idx] = r;
    for(int next : adj_[idx])
    {
        if(!visited2[next]) dfs2(next);
    }
}


int main()
{
    cin >> n >> m;
    adj.resize(2*n + 1); adj_.resize(2*n + 1); //2i-1表示x[i]=1, 2i表示x[i]=0.
    visited1.resize(2*n + 1); visited2.resize(2*n + 1);//访问是1，没访问是0
    SCC.resize(2*n + 1); //这里储存最后的SCC标号，也就是大型拓扑排序的顺序。
    //若SCC[2i-1]<SCC[2i]，则x[i]=0
    //若SCC[2i-1]>SCC[2i]，则x[i]=1
    //若SCC[2i-1]=SCC[2i]，则矛盾没有解

    while(m--)
    {
        int idx1, val1, idx2, val2; //序号1，值1，序号2，值2
        cin >> idx1 >> val1 >> idx2 >> val2;
        int a1 = 2*idx1 + val1 - 1, a2 = 2*idx2 - val2, a3 = 2*idx2 + val2 - 1, a4 = 2*idx1 - val1;
        adj[a1].push_back(a2); //-A-->B
        adj[a3].push_back(a4); //-B-->A
        adj_[a2].push_back(a1); //反图
        adj_[a4].push_back(a3); 
    }

    //开始操作
    for(int i = 1;i <= 2*n;i++)
    {
        if(!visited1[i]) dfs1(i); //如果没有访问，就DFS
    }
    for(int i = 2*n - 1;i >= 0;i--)
    {
        int j = order[i]; //第n-i个访问的数
        if(!visited2[j])
        {
            dfs2(j); //这一层的rank都一样
            r++;
        }
    }
    //判断是否有解，一组一组判断
    bool flag = true;
    for(int i = 1;i <= 2*n && flag;i = i + 2)
    {
        if(SCC[i] == SCC[i + 1]) flag = false;
        else if(SCC[i] < SCC[i + 1]) res.push_back(0);
        else res.push_back(1);
    }

    if(!flag) cout << "No";
    else
    {
        cout << "Yes" << '\n';
        cout << res[0];
        for(int i = 1;i < res.size();i++) cout << ' ' << res[i]; 
    }
}
*/


/*
//11.21 T1344
typedef long long LL;

int n, m; //点、边
vector<vector<LL>> edges; //储存边，三个数分别为(u, v, distance)
vector<int> pre; //前驱数组，pre[u]记录u的上一个节点编号
vector<LL> dis; //储存距离

bool Bellman(int &finish)
{
    for(int i = 1;i < n;i++) //前n-1轮
    {
        bool flag = false; //记录是否有更新，若某一轮没有更新，则说明没有负环
        for(auto edge : edges) //遍历所有边
        {
            LL u = edge[0], v = edge[1], distance = edge[2];
            if(dis[v] > dis[u] + distance)
            {
                flag = true;
                dis[v] = dis[u] + distance;
                pre[v] = u; //v的前驱是u
            }
        }
        if(!flag) return false; //没有负环
    }

    //第n轮
    for(auto edge : edges)
    {
        LL u = edge[0], v = edge[1], distance = edge[2];
        if(dis[v] > dis[u] + distance) 
        {
            finish = v; //传出参数
            pre[v] = u; //v的前驱是u
            return true;//有更新，说明有负环
        }
    }
    return false; //能从循环出来，则没有负环
}

int main()
{
    cin >> n >> m;
    pre.resize(n + 1); 
    dis.resize(n + 1);//初始化，所有的其他节点到超级节点的距离为0
    for(int i = 1;i <= n;i++) //添加超级源点
    {
        edges.push_back({0, i, 0}); //到其他的点距离都是0，此时边数为m+n
    }
    //存入其他边
    for(int i = 0;i < m;i++)
    {
        LL u, v, distan;
        cin >> u >> v >> distan;
        edges.push_back({u, v, distan}); //直接这样存
    }

    int finish = 0; //结束节点
    bool flag = Bellman(finish);
    if(!flag) cout << "No";
    else
    {
        cout << "Yes" << '\n';
        vector<int> visited(n + 1); //访问数组，当某一个点被记录两遍的时候就停止
        int i = finish;
        //找到访问两次的数
        while(visited[i] != 1) //没访问过第二次
        {
            visited[i] = 1;
            i = pre[i];
        }

        int j = i, num = 0;
        vector<int> res; //储存点并且反向输出
        while(true)
        {
            res.push_back(j);
            j = pre[j];
            if(j == i) break;
        }

        cout << res.size() << '\n';
        for(j = res.size() - 1;j >= 0;j--) cout << res[j] << ' '; 
    }
}
*/



/*
//11.27 T1428 MST
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
struct edge
{
    int v;
    LL dis;
    edge(int a, LL b):v(a), dis(b) {}
};

int n, m; //点数、边数
vector<vector<edge>> adj; //邻接表存图
vector<LL> dis; //每个点到树的距离
vector<int> visited; //是否有访问过

LL prim(int s)
{
    //初始化，s以及s的邻边进行赋初值
    LL res = 0; //当前的树的长度
    visited[s] = 1;
    for(auto next : adj[s])
    {
        dis[next.v] = min(next.dis, dis[next.v]);
    }

    for(int j = 1;j < n;j++) //每一轮找到一条边
    {
        //寻找边权最小的未被访问的节点
        LL mini = 1e10; //比最长边还长的值
        int idx; //这个节点的序号
        for(int i = 1;i <= n;i++)
        {
            if(!visited[i] && dis[i] < mini) 
            {
                mini = dis[i]; idx = i; //序号长度更新
            }
        }

        visited[idx] = 1; res += mini;//这条边被选中为MST的一部分
        for(auto next : adj[idx]) //更新那个最小节点的邻边
        {
            dis[next.v] = min(dis[next.v], next.dis);
        }
    }

    return res;
}

int main()
{
    cin >> n >> m;
    adj.resize(n + 1); dis.resize(n + 1, 1e10); visited.resize(n + 1);
    for(int i = 0;i < m;i++)
    {
        int u, v; LL w; //点1，点2，距离
        cin >> u >> v >> w;
        adj[u].push_back(edge(v, w)); adj[v].push_back(edge(u, w)); //将边存入邻接表
    }

    cout << prim(1);
}
*/


/*
//11.29 T1429

//贪心解法
//打工的结构体
struct work{
    int s, t, money; //持续时间
    work() {}
    work(int a, int b, int c):s(a), t(b), money(c) {}
};

bool cmp(work& x, work& y) //按结束时间从小到大，且开始时间尽可能晚
{
    if(x.t == y.t) return x.s > y.s;
    return x.t < y.t; 
}

int main()
{
    int n, m, x; //放假天数、打工数量、旅游的开销
    cin >> n >> m >> x;
    vector<int> isWorked(n + 1); //是否已经工作过
    vector<work> works(m); //存所有的工作

    for(int i = 0;i < m;i++)
    {
        int s, t, a; //开始、结束、钱
        cin >> s >> t >> a;
        works[i] = work(s, t, a);
    }

    sort(works.begin(), works.end(), cmp); //按照持续时间排序
    int res = 0; //打工个数
    int finish = 0; //当前的结束天数
    for(auto w : works)
    {
        if(w.s <= finish) continue; //这个打不成
        else
        {
            res++;
            finish = w.t; //更新结束天数
        }
    }

    cout << res;
}
*/

/*
//dp解法
//打工的结构体
#include <bits/stdc++.h>
using namespace std;
struct work{
    int s, t, money; //持续时间
    work() {}
    work(int a, int b, int c):s(a), t(b), money(c) {}
};

int main()
{
    int n, m, x; //放假天数、打工数量、旅游的开销
    cin >> n >> m >> x;
    vector<work> works(m); //存所有的工作
    vector<int> dp(n + 1); //dp[i]表示第i天后最多多少钱

    for(int i = 0;i < m;i++)
    {
        int s, t, a; //开始、结束、钱
        cin >> s >> t >> a;
        works[i] = work(s, t, a);
    }

    for(int i = 1;i <= n;i++)
    {
        dp[i] = dp[i - 1]; //不减
        for(auto w : works) //找到结束时间=i的工作
        {
            if(w.t == i)
            {
                dp[i] = max(dp[i], dp[w.s - 1] + 1); //dp[i]:不做，dp[s - 1]+1:做
            }
        }
    }

    cout << dp[n];
}
*/


/*
//11.29 T1430
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

//打工的结构体
struct work{
    int s, t, money;
    work() {}
    work(int a, int b, int c):s(a), t(b), money(c) {}
};

int main()
{
    int n, m, x; //放假天数、打工数量、旅游的开销
    cin >> n >> m >> x;
    vector<work> works(m); //存所有的工作
    vector<LL> dp(n + 1); //dp[i]表示第i天后最多多少钱

    for(int i = 0;i < m;i++)
    {
        int s, t, a; //开始、结束、钱
        cin >> s >> t >> a;
        works[i] = work(s, t, a);
    }

    for(int i = 1;i <= n;i++)
    {
        if(dp[i - 1] >= x) //有钱去玩，那就去玩
        {
            dp[i] = dp[i - 1] - x;
        }
        else
        {
            dp[i] = dp[i - 1]; //赋初值
            for(auto w : works)
            {
                if(w.t == i) //第i天结束
                {
                    dp[i] = max(dp[i], dp[w.s - 1] + w.money); //多挣钱，为去玩做准备
                }
            }
        }
    }

    cout << dp[n];
}
*/


// 12.2 T1856
#include <bits/stdc++.h>
using namespace std;
const int N = 20;
int n; //点数
int res = INT_MAX;
int adj[20][20]; //邻接矩阵存边
bool visited[20]; //是否访问过

void dfs(int num, int pre, int val)
{
    if(num >= n)
    {
        res = min(res, val + adj[pre][0]);
    }

    if(val >= res) return; //剪枝
    for(int i = 1;i < n;i++)
    {
        if(!visited[i])
        {
            visited[i] = true; //已经访问过
            dfs(num + 1, i, val + adj[pre][i]);
            visited[i] = false; //回溯
        }
    }
}

int main()
{
    cin >> n;
    for(int i = 0;i < n;i++)
    {
        visited[i] = false;
        for(int j = 0;j < n;j++)
        {
            cin >> adj[i][j];
        }
    }

    //floyd算法
    for(int k = 0;k < n;k++)
    {
        for(int i = 0;i < n;i++)
        {
            for(int j = 0;j < n;j++)
            {
                adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]); //最短路算法
            }
        }
    }
    dfs(1, 0, 0);
    cout << res;
}