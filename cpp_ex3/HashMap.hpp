//
// Created by User on 12-Jan-20.
//

#ifndef EX3_HASHMAP_H
#define EX3_HASHMAP_H

#include <cmath>
#include <vector>
#include <list>
#include <array>
#include <utility>
#include <map>

#define LOW_LOAD_FACTOR 0.25f
#define HIGH_LOAD_FACTOR 0.75f
#define INITIALIZE_CAPACITY 16
#define BIGGER 1
#define SMALLER 2
#define DIFFERENT_VECTOR_SIZE_INPUT_MSG "The vectors are in different size."
#define AT_OUT_OF_RANGE_MSG  "at method is out of range."
#define BUCKET_OUT_OF_RANGE_MSG "Bucket is out of range. "


template<typename KeyT, typename ValueT>
/**
 * Hashmap class that contain an array of buckets which if list of pairs.
 */
class HashMap
{
private:
    typedef typename std::pair<KeyT, ValueT> Pair;
    typedef typename std::list<Pair> Bucket;
    typedef typename Bucket::const_iterator bucket_citerator;

    int _size, _capacity;

    Bucket *_arrayMap;

    /**
     * function to get the index of the bucket that the suspected or should be.
     * @param key - the key to check for.
     * @return - the index. the number of the bucket.
     */
    int _getHashFunction(KeyT key) const
    {
        std::hash<KeyT> hashFunc;
        return hashFunc(key) & (_capacity - 1);
    }

    /**
     * resize the array of the buckets into new one.
     * @param typeOfResize - it says if it need to be bigger or smaller.
     */
    void _resize(int typeOfResize)
    {
        int tempCapacity = _capacity;
        if (typeOfResize == SMALLER)
        {
            _capacity = (_capacity > 1) ? _capacity / 2 : _capacity;
        }
        else
        {
            _capacity += _capacity;
        }
        Bucket *temp = _arrayMap;
        _size = 0;
        _arrayMap = new Bucket[_capacity];

        for (int i = 0; i < tempCapacity; i++)
        {
            for (auto it = temp[i].begin(); it != temp[i].end(); it++)
            {
                (*this)[it->first] = it->second;
            }
        }
        delete[] temp;
    }

    /**
     * get a pair by given key. If it is not find it will throw an exception.
     * @param key - to search for.
     * @return - the pair that it found.
     */
    Pair &_getPairByKey(const KeyT &key) const
    {
        int index = _getHashFunction(key);
        for (auto &pairRun :_arrayMap[index])
        {
            if (pairRun.first == key)
            {
                return pairRun;
            }
        }
        throw std::out_of_range(AT_OUT_OF_RANGE_MSG);
    }

public:
    /**
     * Default Ctor. Initialize the capacity and the size of the map.
     */
    HashMap() : _size(0), _capacity(INITIALIZE_CAPACITY), _arrayMap(new Bucket[_capacity])
    {
    }

    /**
     * Ctor of the HashMap. Its get two vectors and insert it to the vector Map in the same order
     * of the vectors.
     * @param vectorKeyT - Vector of the keys.
     * @param vectorValueT - Vector of the Values.
     */
    HashMap(const std::vector<KeyT> &vectorKeyT, const std::vector<ValueT> &vectorValueT) : _size(
            0), _capacity(INITIALIZE_CAPACITY), _arrayMap(new Bucket[_capacity])
    {
        if (vectorKeyT.size() != vectorValueT.size())
        {
            delete[] _arrayMap;
            throw std::invalid_argument(DIFFERENT_VECTOR_SIZE_INPUT_MSG);
        }
        else
        {
            for (int i = 0; i < (int) vectorKeyT.size(); i++)
            {
                (*this)[vectorKeyT[i]] = vectorValueT[i];
            }
        }
    }

    /**
     * Copy Ctor which copy the vector and all the members of the copied HashMap.
     * @param copyHashMap - The object to copy from.
     */
    HashMap(const HashMap &copyHashMap)
    {
        _capacity = copyHashMap._capacity;
        _size = copyHashMap._size;
        _arrayMap = new Bucket[_capacity];
        for (int i = 0; i < _capacity; i++)
        {
            _arrayMap[i] = copyHashMap._arrayMap[i];
        }
    }

    /**
     * D'tor of the hashmap.
     */
    ~HashMap()
    {
        delete[] _arrayMap;
    }

    /**
     * @return how many args in the map.
     */
    int size() const
    {
        return _size;
    }

    /**
     * @return how many buckets in the array.
     */
    int capacity() const
    {
        return _capacity;
    }

    /**
     * @return bool value if the map is empty.
     */
    int empty() const
    {
        return !_size;
    }

    /**
     * insert method in the hashmap.
     * @param key - the Key to insert
     * @param value - the value to insert.
     * @return - true if its success false otherwise.
     */
    bool insert(const KeyT &key, const ValueT &value)
    {
        if (containsKey(key))
        {
            return false;
        }
        else
        {
            int index = _getHashFunction(key);
            if (_size + 1 > _capacity * HIGH_LOAD_FACTOR)
            {
                _resize(BIGGER);
                index = _getHashFunction(key);
            }
            _arrayMap[index].push_back({key, value});
            _size++;
            return true;
        }
    }

    /**
     * Checks if the key is in the hashMap.
     * @param key - The key to check if contain.
     * @return - true if it is contain false otherwise.
     */
    bool containsKey(const KeyT key) const noexcept
    {
        try
        {
            _getPairByKey(key);
            return true;
        } catch (std::out_of_range &e)
        {
            return false;
        }
    }

    /**
     * get key and return the value of the key. If the key is not exist it will throw an exception.
     */
    ValueT &at(const KeyT key) const
    {
        return _getPairByKey(key).second;
    }

    /**
     * An operator that receive a key and return the value of it. This is the non const operation
     * what means that the value can be change.
     * @return - the value of the key or a reference if its a new key.
     */
    ValueT &operator[](const KeyT key) noexcept
    {
        try
        {
            return _getPairByKey(key).second;
        } catch (std::out_of_range &e)
        {
            ValueT value = ValueT();
            insert(key, value);
            return _getPairByKey(key).second;
        }
    }

    /**
     * An operator that receive a key and return the value of it. This is the const operation
     * what means that the value can not be change.
     * @return - the value of the key.
     */
    const ValueT &operator[](const KeyT key) const
    {
        try
        {
            return _getPairByKey(key).second;

        } catch (std::out_of_range &e)
        {
            return (*this).end()->second;
        }
    }

    /**
     * assign another map to one another.
     * @param mapToBeAssign - map to asign to this.
     * @return - this map.
     */
    HashMap &operator=(HashMap const &mapToBeAssign)
    {
        if (*this != mapToBeAssign)
        {
            if (!empty())
            {
                delete[] _arrayMap;
            }
            for (int i = 0; i < mapToBeAssign._capacity; i++)
            {
                _arrayMap[i] = mapToBeAssign._arrayMap[i];
            }

            _capacity = mapToBeAssign._capacity;
            _size = mapToBeAssign._size;
        }
        return *this;
    }

    /**
     * Erase pair from the map.
     * @param key - The key according to it the pair will be remove.
     * @return - true if it is erase the pair.
     */
    bool erase(KeyT key)
    {
        try
        {
            Pair pairToRemove = _getPairByKey(key);
            int index = _getHashFunction(key);
            _arrayMap[index].remove(pairToRemove);
            _size--;
            if (getLoadFactor() < LOW_LOAD_FACTOR)
            {
                _resize(SMALLER);
            }
            return true;
        } catch (std::out_of_range &e)
        {
            return false;
        }
    }

    /**
     * @return the load factor of the map.
     */
    double getLoadFactor() const
    {
        return (double) _size / _capacity;
    }

    /**
     * @return the index of the bucket in the array according to the key.
     */
    int bucketIndex(KeyT key) const
    {
        if (containsKey(key))
        {
            return _getHashFunction(key);
        }
        else
        {
            throw std::out_of_range(BUCKET_OUT_OF_RANGE_MSG);
        }
    }

    /**
     * @return the size of the bucket if the key in it. if it is not in it it will throw an
     * exception.
     */
    int bucketSize(KeyT key) const
    {
        int index = _getHashFunction(key);
        if (containsKey(key))
        {
            return _arrayMap[index].size();
        }
        else
        {
            throw std::out_of_range(BUCKET_OUT_OF_RANGE_MSG);
        }
    }

    /**
     * clear all the values in the map.
     */
    void clear()
    {
        for (int i = 0; i < _capacity; i++)
        {
            _arrayMap[i].clear();
        }
        _size = 0;
    }

    /**
     * Class of const iterator for hashMap.
     */
    class const_iterator
    {
    private:
        const HashMap *_hashMap;
        bucket_citerator _pairIterator;
        int _curBucketIndex;

        /**
         * put the member pointer to the end of the iterator of the map.
         */
        void _endIterator()
        {
            if (_hashMap->_capacity == _curBucketIndex)
            {
                _pairIterator = bucket_citerator();
                return;
            }
            for (int i = _hashMap->_capacity - 1; i > 0; i--)
            {
                if (!_hashMap->_arrayMap[i].empty())
                {
                    _pairIterator = _hashMap->_arrayMap[i].cend();
                    return;
                }
            }
        }

        /**
         * update the pointer to the next pair in the hashMap. If it was the last pair, the
         * pointer points to the end of the hashMap (end of the last list).
         */
        void _setToFirstInBucket()
        {
            for (int i = _curBucketIndex; i < _hashMap->_capacity; i++)
            {
                if (!_hashMap->_arrayMap[i].empty())
                {
                    _curBucketIndex = i;
                    _pairIterator = _hashMap->_arrayMap[i].cbegin();
                    return;
                }
            }
            _curBucketIndex = _hashMap->_capacity;
            _endIterator();
        }

        /**
         * Set th pointer member to the next pair in the hashMap. If it is the last pair in the
         * list it will call the method 'setToFirstInBucket' and search for the next pair.
         */
        void _setNextPairInBucket()
        {
            _pairIterator++;
            if (_pairIterator == _hashMap->_arrayMap[_curBucketIndex].cend())
            {
                _curBucketIndex++;
                _setToFirstInBucket();
            }
        }

    public:
        typedef const_iterator self_type;
        typedef Pair value_type;
        typedef const value_type *pointer;
        typedef const value_type &reference;
        typedef std::ptrdiff_t difference_type;
        typedef std::forward_iterator_tag iterator_category;


        /**
         * Ctor of the const iterator.
         * @param hashMap - The hashMap to iterate in.
         */
        const_iterator(const HashMap *hashMap, bool pointsToEnd) : _hashMap(hashMap),
                _curBucketIndex(0)
        {
            if (_hashMap->empty())
            {
                _curBucketIndex = _hashMap->_capacity;
                _endIterator();
            }
            else if (pointsToEnd)
            {
                _pairIterator = bucket_citerator();
                //_endIterator();
            }
            else
            {
                _setToFirstInBucket();
            }
        }

        bool operator!=(const const_iterator &itr) const
        {
            return (_pairIterator != itr._pairIterator);
        }

        bool operator==(const const_iterator &itr) const
        {
            return (_pairIterator == itr._pairIterator);
        }

        reference operator*() const
        {
            return *_pairIterator;
        }

        pointer operator->() const
        {
            return &(*_pairIterator);
        }

        self_type &operator++()
        {
            _setNextPairInBucket();
            return *this;
        }

        self_type operator++(int)
        {
            self_type temp = *this;
            _setNextPairInBucket();
            return temp;
        }
    };

    /**
     * begin method for the operator. it is still const iterator because we use only const forward
     * iterator.
     */
    const_iterator begin() const
    {
        const_iterator newIterator(this, false);
        return newIterator;
    }

    /**
     * const begin method for the operator.
     */
    const_iterator cbegin() const
    {
        return begin();
    }

    /**
     * end method for the operator.it is still const iterator because we use only const forward
     * iterator.
     */
    const_iterator end() const
    {
        return const_iterator(this, true);
    }

    /**
     * const end method for the operator.
     */
    const_iterator cend() const
    {
        return  end();
    }

    bool operator==(HashMap const &hashMapR) const noexcept
    {
        if (_size == hashMapR._size)
        {

            for (auto it = hashMapR.begin(); it != hashMapR.end(); it++)
            {
                try
                {
                    if (_getPairByKey(it->first).second != it->second)
                    {
                        return false;
                    }
                } catch (std::out_of_range &e)
                {
                    return false;
                }
            }
            return true;
        }
        return false;
    }

    bool operator!=(HashMap const &hashMap) const
    {
        return !(*this == hashMap);
    }
};


#endif //EX3_HASHMAP_H