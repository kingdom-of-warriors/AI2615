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
    if(l + 1 >= r) return INF; //剪枝

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
    point(LL _x = 0, LL _y = 0) : x(_x), y(_y) {} //初始化
    LL distance_2 (const point & other) const {
        return pow_2(x - other.x) + pow_2(y - other.y); //计算距离的函数
    }
};

LL solve (vector <point> &a, vector <point> &b, int l, int r) {
    if(l == r) return INF; //中间没有点
    // if(l + 1 == r) //只有两个点
    // {
    //     if(b[l].y > b[r].y) swap(b[l],b[r]); //保证b以y为大小排序
    //     return a[l].distance_2(a[r]); //返回两点之间距离
    // }

    int m = (r + l)/2; //中间的数
    LL ret = min(solve(a,b,l,m),solve(a,b,m + 1,r)); //递归的最小值，也就是两个集合内部的最小值
    
    int i,j,k; //左右边的下标,Q中的下标
    vector<point> tmp(r - l + 1); //临时数组
    for(i = l,j = m + 1;(i <= m) && (j <= r);) //归并排序
    { 
        if(b[i].y < b[j].y)
        {
            tmp[k++] = b[i];
            if(pow_2(a[i].x - a[m].x) < ret) //满足条件，开始寻找
            {
                for(int w = j - 1; w > m && j - w < 3; w--) ret = min(ret, b[i].distance_2(b[w]));
                for(int w = j; w <= r && w - j < 3; w++) ret = min(ret, b[i].distance_2(b[w]));
            }
            i++;
        }
        else tmp[k++] = b[j++];
    }

    while(i <= m)
    {
        tmp[k++] = b[i];
        if(pow_2(a[i].x - a[m].x) < ret) //满足条件，开始寻找
        {
            for(int w = j - 1; w > m && j - w < 3; w--) ret = min(ret, b[i].distance_2(b[w]));
            for(int w = j; w <= r && w - j < 3; w++) ret = min(ret, b[i].distance_2(b[w]));
        }
        i++;
    }
    while(j <= r) tmp[k++] = b[j++];

    for(i = l;i <= r;i++) b[i] = tmp[i - l]; //复制
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
    vector <point> b = a;
    cout << solve (a, b, 0, n - 1) << endl; //wok，这里要改成n - 1，真离谱，我根本没看主函数，只改了一个数据类型
}
*/
