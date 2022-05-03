#include <iostream>
#include <functional>
#include <forward_list>
#include <vector>

template <typename K, typename V>
struct MyHashNode
{
    MyHashNode() = delete;

    MyHashNode(const K& k, const V& v)
        : key_(k)
        , value_(v)
    {

    }

    K key_;
    V value_;
};

template <typename K, typename V>
class MyHashMap
{
public:

    MyHashMap();

    void insert(const K& key, const V& value);

    V* find(const K& key);

    void erase(const K& key);

private:

    std::hash<K> keyHash_;

    size_t bucketCount_{20};

    typedef std::forward_list< MyHashNode<K,V> > HashNodeList;

    std::vector<HashNodeList> buckets_;
};

template <typename K, typename V>
MyHashMap<K,V>::MyHashMap()
{
    buckets_.resize(bucketCount_);
}

template <typename K, typename V>
void MyHashMap<K,V>::insert(const K& key, const V& value)
{
    size_t bktIdx{keyHash_(key) % bucketCount_};

    MyHashMap::HashNodeList& bucket = buckets_[bktIdx];

    if(bucket.empty())
    {
        bucket.emplace_front(key, value);
    }
    else
    {
        for (auto it = bucket.begin(); it != bucket.end(); ++it)
        {
            if(it->key_ == key)
            {
                it->value_ = value;
                return;
            }
        }

        // Key does not currently exist within container
        bucket.emplace_front(key, value);
    }
}

template <typename K, typename V>
V* MyHashMap<K,V>::find(const K& key)
{
    size_t bktIdx{keyHash_(key) % bucketCount_};

    MyHashMap::HashNodeList& bucket = buckets_[bktIdx];

    if(bucket.empty())
    {
        return nullptr;
    }
    else
    {
        for (auto it = bucket.begin(); it != bucket.end(); ++it)
        {
            if(it->key_ == key)
            {
                return &it->value_;
            }
        }

        // Key does not currently exist within container
        return nullptr;
    }
}

template <typename K, typename V>
void MyHashMap<K,V>::erase(const K& key)
{
    size_t bktIdx{keyHash_(key) % bucketCount_};

    MyHashMap::HashNodeList& bucket = buckets_[bktIdx];

    if(bucket.empty())
    {
        return;
    }
    else
    {
        auto prev = bucket.before_begin();

        for (auto it = bucket.begin(); it != bucket.end(); ++it)
        {
            if(it->key_ == key)
            {
                bucket.erase_after(prev);
                return;
            }
            prev = it;
        }

        // Key does not currently exist within container
    }
}

int main(int argc, char** argv)
{
    MyHashMap<std::string, int> hashMap;

    for(int i=1; i<argc; i++)
    {
        hashMap.insert(argv[i], i);
    }

    for(int i=1; i<argc; i++)
    {
        int* val = hashMap.find(argv[i]);

        if(val)
        {
            std::cout << argv[i] << " = " << *val << std::endl;
        }
    }

    hashMap.insert("hundred", 100);

    int* val = hashMap.find("hundred");

    if(val)
    {
        std::cout << "hundred" << " = " << *val << std::endl;
    }

    hashMap.erase("hundred");

    val = hashMap.find("hundred");

    if(val)
    {
        std::cout << "hundred" << " = " << *val << std::endl;
    }
    else
    {
        std::cout << "hundred not found" << std::endl;
    }

    return 0;
}
