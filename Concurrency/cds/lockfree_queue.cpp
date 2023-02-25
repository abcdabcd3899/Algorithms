struct Node {
    void* data;
    Node* nxt;
};
struct Queue {
    Node *head;
    Node *tail;
};

//q->head和q->tail首先指向一个dummy节点，q->head==q->tail表示队列
//如果不这样做，队列里只有一个节点时，tail指向该节点，而head只能指向null
Queue* init() {
    Queue* q = (Queue*) malloc (sizeof (Queue) );
    q->head = q->tail = (Node*) malloc (sizeof (Node) );
    q->head->nxt = nullptr;
    return q;
}

void push (Queue* q, void* data) {
    Node *now = (Node*) malloc (sizeof (Node) );
    now->data = data;
    now->nxt = nullptr;

    Node *tail, *nxt;
    while (true) {
        tail = q->tail;
        nxt = tail->nxt;

        //先判断目前是否为队尾，如果不是队尾，则重新进入循环
        if (tail != q->tail) continue;
        
        //还是判断目前是否为队尾，如果tail->nxt不为空，则表示有其他线程push了数据，需要重新进入循环
        if (nxt != nullptr) {
            __sync_bool_compare_and_swap (&q->tail, tail, nxt);
            continue;
        }
        //原子操作，判断q->tail->nxt是否为空，
        //如果不为空则表示已经有其他线程push了数据，需要重新进入循环，否则将now加入队尾
        if (__sync_bool_compare_and_swap (&q->tail->nxt, nullptr, now) ) {
            break;
        }
    }
    //将队尾指针指向now，就算修改失败也没关系，其它线程会帮忙修改
    __sync_bool_compare_and_swap (&q->tail, tail, now);
}

void* pop (Queue* q) {
    void* data;
    Node *head, *tail, *nxt;

    while (true) {
        head = q->head;
        tail = q->tail;
        nxt = head->nxt;

        //先判断目前是否为队首，如果不是，则重新进入循环
        if (head != q->head) continue;

        //判断队列是否为空，如果为空则直接返回null
        if (nxt == nullptr) return nullptr;

        //上面一个if已经判断队列不为空，
        //如果head==tail，则表示队列已经push了数据，但没来得及修改tail，因此需要修改tail再重新进入循环
        if (head == tail) {
            __sync_bool_compare_and_swap (&q->tail, head, nxt);
            continue;
        }

        data = nxt->data;

        //取出数据后，原子操作，判断q->head是否被其他线程修改
        //如果q->head!=head，则表示已经被其他线程pop数据，因此需要重新进入循环
        //否则直接修改队首指向nxt
        if (__sync_bool_compare_and_swap (&q->head, head, nxt) ) {
            break;
        }
    }
    //释放head，避免内存泄漏
    free (head);
    return data;
}
