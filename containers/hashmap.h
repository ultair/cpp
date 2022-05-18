#include <functional>
#include <forward_list>
#include <vector>

namespace mmw
{

template <typename K, typename V>
struct HashNode
{
    HashNode() = delete;

    HashNode(const K& k, const V& v)
        : key_(k)
        , value_(v)
    {

    }

    K key_;
    V value_;
};

template <typename K, typename V>
class HashMap
{
public:

    HashMap();

    void insert(const K& key, const V& value);

    V* find(const K& key);

    void erase(const K& key);

private:

    std::hash<K> keyHash_;

    size_t bucketCount_{20};

    typedef std::forward_list< HashNode<K,V> > HashNodeList;

    std::vector<HashNodeList> buckets_;
};

template <typename K, typename V>
mmw::HashMap<K,V>::HashMap()
{
    buckets_.resize(bucketCount_);
}

template <typename K, typename V>
void mmw::HashMap<K,V>::insert(const K& key, const V& value)
{
    size_t bktIdx{keyHash_(key) % bucketCount_};

    HashMap::HashNodeList& bucket = buckets_[bktIdx];

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
V* mmw::HashMap<K,V>::find(const K& key)
{
    size_t bktIdx{keyHash_(key) % bucketCount_};

    HashMap::HashNodeList& bucket = buckets_[bktIdx];

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
void mmw::HashMap<K,V>::erase(const K& key)
{
    size_t bktIdx{keyHash_(key) % bucketCount_};

    HashMap::HashNodeList& bucket = buckets_[bktIdx];

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

}
