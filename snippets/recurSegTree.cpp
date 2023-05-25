template <typename T>
class SegmentTree
{
public:
    T n;
    vector<T> tree;
    vector<T> lazyTree;

    SegmentTree(vector<T> &arr)
    {
        this->n = arr.size();
        tree.resize(4 * this->n + 1);
        lazyTree.resize(4 * this->n + 1, 0);
        build(arr);
    }

    void build(T index, T start, T end, vector<T> &arr)
    {
        if (start == end)
        {
            tree[index] = arr[start];
            return;
        }
        T mid = (start + end) / 2;
        build(2 * index + 1, start, mid, arr);
        build(2 * index + 2, mid + 1, end, arr);
        tree[index] = tree[2 * index + 1] + tree[2 * index + 2];
    }

    T query(T index, T start, T end, T l, T r)
    {
        if (start > r || end < l)
        {
            return 0;
        }
        if (start >= l && end <= r)
            return tree[index];

        T mid = (start + end) / 2;
        T first = query(2 * index + 1, start, mid, l, r);
        T second = query(2 * index + 2, mid + 1, end, l, r);
        return first + second;
    }

    T lazyQuery(T index, T start, T end, T l, T r)
    {
        if (start > r || end < l)
        {
            return 0;
        }

        if (lazyTree[index] != 0)
        {
            tree[index] += lazyTree[index] * (end - start + 1);
            if (start != end)
            {
                lazyTree[2 * index + 1] += lazyTree[index];
                lazyTree[2 * index + 2] += lazyTree[index];
            }
            lazyTree[index] = 0;
        }
        
        if (start == end)
        {
            return tree[index];
        }

        if (start >= l && end <= r)
        {
            return tree[index];
        }

        T mid = (start + end) / 2;
        T first = lazyQuery(2 * index + 1, start, mid, l, r);
        T second = lazyQuery(2 * index + 2, mid + 1, end, l, r);
        return first + second;
    }

    void update(T index, T target, T value, T start, T end)
    {
        if (start == end)
        {
            tree[index] = value;
            return;
        }

        T mid = (start + end) / 2;
        if (target <= mid)
        {
            update(2 * index + 1, target, value, start, mid);
        }
        else
        {
            update(2 * index + 2, target, value, mid + 1, end);
        }
        tree[index] = tree[2 * index + 1] + tree[2 * index + 2];
    }

    void update(T index, T l, T r, T value, T start, T end)
    {
        if (end < l || start > r || start > end)
            return;
        if (start == end)
        {
            tree[index] += value;
            return;
        }
        if (start >= l && end <= r)
        {
            tree[index] += (end - start + 1) * value;
            lazyTree[2 * index + 1] += value;
            lazyTree[2 * index + 2] += value;
            return;
        }

        T mid = (start + end) / 2;
        if (l <= mid)
        {
            update(2 * index + 1, l, r, value, start, mid);
        }
        if (end > mid)
        {
            update(2 * index + 2, l, r, value, mid + 1, end);
        }
        tree[index] = tree[2 * index + 1] + tree[2 * index + 2];
    }

    void build(vector<T> &arr)
    {
        build(0, 0, arr.size() - 1, arr);
    }

    T lazyQuery(T l, T r)
    {
        return lazyQuery(0, 0, this->n - 1, --l, --r);
    }

    T query(T l, T r)
    {
        return query(0, 0, this->n - 1, --l, --r);
    }

    void update(T target, T value)
    {
        update(0, --target, value, 0, this->n - 1);
    }

    void update(T l, T r, T value)
    {
        update(0, --l, --r, value, 0, this->n - 1);
    }
};