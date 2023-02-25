// 外存排序算法，首先拆分 runs ， 然后使用小顶堆实现 k-ways merge
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <ctime>
#include <queue>
#include <vector>

using namespace std;

struct MinHeapNode {
    // The element to be stored
    int element;

    // index of the array from which
    // the element is taken
    int i;

    MinHeapNode(int i_) : i(i_) {};
};

// 小顶堆排序操作符， 也可以使用 lambda 代替
struct cmp {
    bool operator()(MinHeapNode *a, MinHeapNode *b) const {
        return a->element > b->element;
    }
};

// 快速排序算法
void quicksort(vector<int> &nums, int left, int right) {
    if (left >= right) return;
    int i = left - 1;
    int j = right + 1;
    int pivot = nums[left + right + 1 >> 1];
    while (i < j) {
        do ++i; while (nums[i] < pivot);
        do --j; while (nums[j] > pivot);
        if (i < j) swap(nums[i], nums[j]);
    }
    quicksort(nums, left, i - 1);
    quicksort(nums, i, right);
}

// merge of merge sort
void merge(vector<int> &nums, int l, int r) {
    if (l >= r) return;
    int mid = l + r >> 1;
    merge(nums, l, mid), merge(nums, mid + 1, r);
    int i = l, j = mid + 1, k = 0;
    vector<int> ans(r - l + 1);   //这里如果ans(nums.size()) 代码通不过，特别注意
    while (i <= mid && j <= r) {
        if (nums[i] <= nums[j]) {
            ans[k++] = nums[i++];
        } else
            ans[k++] = nums[j++];
    }
    while (i <= mid) {
        ans[k++] = nums[i++];
    }
    while (j <= r) {
        ans[k++] = nums[j++];
    }
    for (int i = l, j = 0; i <= r; i++, j++) {
        nums[i] = ans[j];
    }
}

void mergeSort(vector<int> &arr) {
    merge(arr, 0, arr.size() - 1);

}

FILE *openFile(char *fileName, char *mode) {
    FILE *fp = fopen(fileName, mode);
    if (fp == NULL) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
    return fp;
}

// 使用小顶堆合并所有 runs 结果
void mergeFiles(char *output_file, int n, int k) {
    FILE *in[k];
    for (int i = 0; i < k; i++) {
        char fileName[2];

        // convert i to string
        snprintf(fileName, sizeof(fileName),
                 "%d", i);

        // Open input files in read mode.
        in[i] = openFile(fileName, "r");
    }

    // FINAL OUTPUT FILE
    FILE *out = openFile(output_file, "w");

    priority_queue<MinHeapNode *, vector<MinHeapNode *>, cmp> harr;
    int i;
    for (i = 0; i < k; i++) {
        MinHeapNode *tmp = new MinHeapNode(i);
        if (fscanf(in[i], "%d ", &tmp->element) != 1)
            break;

        // 构造一个 MinHeapNode 对象 插入到小顶堆中
        harr.push(tmp);
    }

    int count = 0;

    while (count != i) {
        MinHeapNode *root = harr.top();
        fprintf(out, "%d ", root->element);

        if (fscanf(in[root->i], "%d ",
                   &root->element)
            != 1) {  // fscanf 函数的返回值表示成功赋值的个数
            root->element = INT_MAX;
            count++;
        }

        harr.pop();  // 弹出根结点，并将新的节点 push 到小顶堆中，push 进去的过程会自动插入到合适的位置
        harr.push(root);
    }

    // close input and output files
    for (int i = 0; i < k; i++)
        fclose(in[i]);

    fclose(out);
}

// 拆分 runs， 并将排序后的结果写入 output file 中
void createInitialRuns(
        char *input_file, int run_size,
        int num_ways) {
    // For big input file
    FILE *in = openFile(input_file, "r");

    // output scratch files
    FILE *out[num_ways];
    char fileName[2];  // 这里支持的最大 runs 数目为 256
    for (int i = 0; i < num_ways; i++) {
        // convert i to string
        snprintf(fileName, sizeof(fileName),
                 "%d", i);

        // Open output files in write mode.
        out[i] = openFile(fileName, "w");
    }

    vector<int> arr(run_size);
    bool more_input = true;
    int next_output_file = 0;

    int i;
    while (more_input) {
        // 从 big file 中读出 run_size 个元素，同时将 run_size 个元素写入到 arr 数组中
        for (i = 0; i < run_size; i++) {
            if (fscanf(in, "%d ", &arr[i]) != 1) {  // 1000 个数字读入一次，排好序写回去
                more_input = false;
                break;
            }
        }

        // 内存排序算法，这里也可以使用 quick sort 排序算法
        // mergeSort(arr);
        quicksort(arr, 0, arr.size() - 1);

        // 将排序好的 arr 数组写入到输出文件中
        for (int j = 0; j < i; j++)
            fprintf(out[next_output_file],
                    "%d ", arr[j]);
        // 开始操作 run_size 的文件
        next_output_file++;
    }

    // 关闭输出文件
    for (int i = 0; i < num_ways; i++)
        fclose(out[i]);

    fclose(in);
}

// 从磁盘读入数据，完整 big data 数据排序
void externalSort(
        char *input_file, char *output_file,
        int num_ways, int run_size) {

    createInitialRuns(input_file,
                      run_size, num_ways);

    mergeFiles(output_file, run_size, num_ways);
}

int main() {
    // Number of Partitions of input file.
    int num_ways = 10;

    // The size of each partition
    int run_size = 1000;

    char input_file[] = "input.txt";
    char output_file[] = "output.txt";

    FILE *in = openFile(input_file, "w");

    srand(unsigned(time(NULL)));

    // generate input [1, 10]
//    for (int i = 0; i < num_ways * run_size; i++)
//        fprintf(in, "%d ",  (rand() % (10-1+1))+ 1);
    for (int i = 0; i < num_ways * run_size; i++)
        fprintf(in, "%d ", rand());

    fclose(in);

    externalSort(input_file, output_file, num_ways,
                 run_size);

    return 0;
}
