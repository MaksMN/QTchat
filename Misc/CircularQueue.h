#pragma once
#include <deque>

/*!
 * \brief Круговая очередь. При добавлении элемента удаляется элемент с другой стороны
 */
template <typename T, typename N = int>
class CircularQueue
{
private:
    std::deque<T> _deque;
    N _size = 20;

public:
    explicit CircularQueue(N size = 20);
    ~CircularQueue() = default;
    void push_front(T &obj);
    void push_front(T &&obj);
    void pop_front();
    void push_back(T &obj);
    void push_back(T &&obj);
    void pop_back();
    void resize_front(N new_size);
    void resize_back(N new_size);
    N size();
    T operator[](N index);
    std::deque<T> &decue();
};

template<typename T, typename N>
inline CircularQueue<T, N>::CircularQueue(N size)
    : _size(size)
{}

template <typename T, typename N>
inline void CircularQueue<T, N>::push_front(T &obj)
{
    _deque.push_front(obj);
    if (_deque.size() > _size)
        _deque.pop_back();
}
template <typename T, typename N>
inline void CircularQueue<T, N>::push_front(T &&obj)
{
    push_front(obj);
}

template <typename T, typename N>
inline void CircularQueue<T, N>::pop_front()
{
    _deque.pop_front();
}

template <typename T, typename N>
inline void CircularQueue<T, N>::push_back(T &obj)
{
    _deque.push_back(obj);
    if (_deque.size() > _size)
        _deque.pop_front();
}
template <typename T, typename N>
inline void CircularQueue<T, N>::push_back(T &&obj)
{
    push_back(obj);
}

template <typename T, typename N>
inline void CircularQueue<T, N>::pop_back()
{
    _deque.pop_back();
}
template<typename T, typename N>
inline void CircularQueue<T, N>::resize_front(N new_size)
{
    if (new_size < _deque.size()) {
        for (int i = 0; i < _deque.size - new_size; ++i) {
            _deque.pop_front();
        }
    }
    _size = new_size;
}
template<typename T, typename N>
inline void CircularQueue<T, N>::resize_back(N new_size)
{
    if (new_size < _deque.size()) {
        for (int i = 0; i < _deque.size - new_size; ++i) {
            _deque.pop_back();
        }
    }
    _size = new_size;
}
template<typename T, typename N>
inline N CircularQueue<T, N>::size()
{
    return _size;
}

template<typename T, typename N>
inline T CircularQueue<T, N>::operator[](N index)
{
    if (index < 0 || index >= _size)
        return T();
    return _deque[index];
}
template<typename T, typename N>
inline std::deque<T> &CircularQueue<T, N>::decue()
{
    return _deque;
}
