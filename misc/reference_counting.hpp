template <typename T, size_t S, size_t A = sizeof(T)>
class Rc {
    struct Block {
        std::byte data[A];
        int ref;
    };
    static int head;
    static Block pool[S];
    static int alloc() {
        int x = head;
        head += pool[head].ref + 1;
        return x;
    }
    static void free(int idx) {
        reinterpret_cast<T *>(pool[idx].data)->~T();
        pool[idx].ref = head - idx - 1;
        head = idx;
    }

    int idx{};
    void release(int idx) {
        if (idx) {
            if (--pool[idx].ref == 0) {
                free(idx);
            }
        }
    }
    explicit Rc(int x) : idx(x) {}

public:
    Rc() = default;
    Rc(const Rc &other) {
        idx = other.idx;
        if (idx) pool[idx].ref += 1;
    }
    Rc(Rc &&other) {
        idx = other.idx;
        if (idx) other.idx = 0;
    }
    ~Rc() { release(idx); }
    Rc &operator=(const Rc &other) {
        if (this != &other) {
            release(idx);
            idx = other.idx;
            if (idx) pool[idx].ref += 1;
        }
        return *this;
    }
    Rc &operator=(Rc &&other) {
        if (this != &other) {
            release(idx);
            idx = other.idx;
            if (idx) other.idx = 0;
        }
        return *this;
    }
    template <typename... Args>
    static Rc make(Args &&...args) {
        int idx = alloc();
        new (pool[idx].data) T(std::forward<Args>(args)...);
        pool[idx].ref = 1;
        return Rc{idx};
    }

    T &operator*() const { return *reinterpret_cast<T *>(pool[idx].data); }
    T *operator->() const { return reinterpret_cast<T *>(pool[idx].data); }
    explicit operator bool() const { return idx; }
};
template <typename T, size_t S, size_t A>
constinit int Rc<T, S, A>::head = 1;
template <typename T, size_t S, size_t A>
constinit Rc<T, S, A>::Block Rc<T, S, A>::pool[S];
