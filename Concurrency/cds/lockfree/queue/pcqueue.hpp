// A single producer and A single consumer lock free queue
#include <atomic>
#include <memory>
constexpr static auto const N_WORKER_PAIRS  = 1ul;
constexpr static auto const WORK_PER_THREAD = 100ul;

template <typename T>
class PCQueue{
public:
    struct Node{
        Node* next;
        std::shared_ptr<T>data;
        Node(): next(nullptr){};
    };

    std::atomic<Node*> head;
    std::atomic<Node*> tail;

public:
    PCQueue(): head(new Node{}), tail(head.load(std::memory_order_relaxed)){};
    ~PCQueue(){
        while(auto* current = head.load()){
            head.store(current->next);  // 让 head 指向下一个节点
            delete current;  // 删除当前节点
        }
    }

    // non copy constructor
    PCQueue(PCQueue const& ) =delete;
    PCQueue& operator=(PCQueue const&) = delete;

    // non movable constructor
    PCQueue(PCQueue&&)            = delete;
    PCQueue& operator=(PCQueue&&) = delete;

    void push(T const& data);
    std::shared_ptr<T>pop();
    bool is_empty_unsafe()const noexcept;

private:
    Node* pop_head() {
        Node* old_head = head.load();
        if(old_head == tail.load()){
            // no data
            return nullptr;
        }
        head.store(old_head->next);
        return old_head;
    }
};

template <typename T>
void PCQueue<T>::push(const T &data) {
    auto shared_data = std::make_shared<T>(data);
    Node* new_node = new Node{};  // create dummy tail node

    // replace data in the current tail node
    Node* const old_tail = tail.load();
    old_tail->data.swap(shared_data);
    old_tail->next = new_node;

    // update tail pointer
    tail.store(new_node);
};

template <typename T>
std::shared_ptr<T> PCQueue<T>::pop() {
    auto* old_head = pop_head();
    if(nullptr == old_head){
        // no data
        return std::shared_ptr<T>{};
    }
    std::shared_ptr<T> popdata{old_head->data};
    delete old_head;
    return popdata;
};

template <typename T>
bool PCQueue<T>::is_empty_unsafe() const noexcept {
    return head.load(std::memory_order_relaxed) == tail.load(std::memory_order_relaxed);
};



