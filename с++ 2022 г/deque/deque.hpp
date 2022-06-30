#include <stdexcept>
#include <vector>

template <typename T>
class Deque {
 public:
  template <bool is_const>
  class CommonIterator {
   public:
    using value_type = std::conditional_t<is_const, const T, T>;  //  NOLINT
    using pointer = value_type*;                                  //  NOLINT
    using reference = value_type&;                                //  NOLINT
    using iterator_category = std::random_access_iterator_tag;    //  NOLINT
    using difference_type = unsigned long long;                   //  NOLINT

    std::vector<T*>& data;
    long long index;

    CommonIterator(const size_t kIndex, std::vector<T*>& data)
        : data(data), index(kIndex) {}

    CommonIterator(const CommonIterator<false>& iterator)
        : data(iterator.data), index(iterator.index) {}

    CommonIterator<is_const>& operator++() {
      ++index;
      return *this;
    }

    CommonIterator<is_const> operator++(int) {
      CommonIterator<is_const> copy = *this;
      ++index;
      return copy;
    }

    CommonIterator<is_const>& operator--() {
      --index;
      return *this;
    }

    CommonIterator<is_const> operator--(int) {
      CommonIterator<is_const> copy = *this;
      --index;
      return copy;
    }

    CommonIterator<is_const>& operator+=(int n) {
      index += n;
      return *this;
    }

    CommonIterator<is_const>& operator-=(int n) {
      index -= n;
      return *this;
    }

    CommonIterator operator+(int n) const {
      CommonIterator<is_const> iterator(index + n, data);
      return iterator;
    }

    CommonIterator operator-(int n) {
      CommonIterator<is_const> iterator(index - n, data);
      return iterator;
    }

    std::conditional_t<is_const, const T&, T&> operator*() {
      return data[index / kPartSize][index % kPartSize];
    }

    std::conditional_t<is_const, const T*, T*> operator->() {
      return &data[index / kPartSize][index % kPartSize];
    }

    CommonIterator& operator=(const CommonIterator<false>& it) {
      data = it.data;
      index = it.index;
      return *this;
    }

    bool operator<(const CommonIterator<is_const>& compared) const {
      return index < compared.index;
    }

    bool operator>(const CommonIterator<is_const>& compared) const {
      return index > compared.index;
    }

    bool operator<=(const CommonIterator<is_const>& compared) const {
      return index <= compared.index;
    }

    bool operator>=(const CommonIterator<is_const>& compared) const {
      return index >= compared.index;
    }

    bool operator==(const CommonIterator<is_const>& compared) const {
      return index == compared.index;
    }

    bool operator!=(const CommonIterator<is_const>& compared) const {
      return index != compared.index;
    }

    difference_type operator-(const CommonIterator<is_const>& another) const {
      if (index >= another.index) {
        return index - another.index;
      }
      return another.index - index;
    }
  };

  template <bool is_const>
  class ReversIterator {
   public:
    using value_type = std::conditional_t<is_const, const T, T>;  //  NOLINT
    using pointer = value_type*;                                  //  NOLINT
    using reference = value_type&;                                //  NOLINT
    using iterator_category = std::random_access_iterator_tag;    //  NOLINT
    using difference_type = unsigned long long;                   //  NOLINT

    std::vector<T*>& data;
    long long index;

    ReversIterator(const size_t kIndex, std::vector<T*>& data)
        : data(data), index(kIndex) {}

    ReversIterator(const ReversIterator<false>& iterator)
        : data(iterator.data), index(iterator.index) {}

    ReversIterator(const CommonIterator<false>& iterator)
        : data(iterator.data), index(iterator.index) {}

    ReversIterator<is_const>& operator--() {
      ++index;
      return *this;
    }

    ReversIterator<is_const> operator--(int) {
      ReversIterator<is_const> copy = *this;
      ++index;
      return copy;
    }

    ReversIterator<is_const>& operator++() {
      --index;
      return *this;
    }

    ReversIterator<is_const> operator++(int) {
      ReversIterator<is_const> copy = *this;
      --index;
      return copy;
    }

    ReversIterator<is_const>& operator-=(int n) {
      index += n;
      return *this;
    }

    ReversIterator<is_const>& operator+=(int n) {
      index -= n;
      return *this;
    }

    ReversIterator operator-(int n) const {
      ReversIterator<is_const> iterator(index + n, data);
      return iterator;
    }

    ReversIterator operator+(int n) {
      ReversIterator<is_const> iterator(index - n, data);
      return iterator;
    }

    std::conditional_t<is_const, const T&, T&> operator*() {
      return data[index / kPartSize][index % kPartSize];
    }

    std::conditional_t<is_const, const T*, T*> operator->() {
      return &data[index / kPartSize][index % kPartSize];
    }

    ReversIterator& operator=(const ReversIterator<false>& it) {
      data = it.data;
      index = it.index;
      return *this;
    }

    bool operator>(const ReversIterator<is_const>& compared) const {
      return index < compared.index;
    }

    bool operator<(const ReversIterator<is_const>& compared) const {
      return index > compared.index;
    }

    bool operator>=(const ReversIterator<is_const>& compared) const {
      return index <= compared.index;
    }

    bool operator<=(const ReversIterator<is_const>& compared) const {
      return index >= compared.index;
    }

    bool operator==(const ReversIterator<is_const>& compared) const {
      return index == compared.index;
    }

    bool operator!=(const ReversIterator<is_const>& compared) const {
      return index != compared.index;
    }

    difference_type operator-(const ReversIterator<is_const>& another) const {
      if (index >= another.index) {
        return index - another.index;
      }
      return another.index - index;
    }
  };

  using iterator = CommonIterator<false>;              //  NOLINT
  using const_iterator = CommonIterator<true>;         //  NOLINT
  using revers_iterator = ReversIterator<false>;       //  NOLINT
  using const_revers_iterator = ReversIterator<true>;  //  NOLINT

  Deque() : begin_(0, pointers_), end_(0, pointers_) { capacity_ = 0; }

  Deque(const Deque& deque)
      : begin_(deque.begin_.index, pointers_),
        end_(deque.end_.index, pointers_) {
    capacity_ = deque.capacity_;
    pointers_.resize(capacity_);
    for (size_t i = 0; i < capacity_; ++i) {
      pointers_[i] = reinterpret_cast<T*>(new int8_t[kPartSize * sizeof(T)]);
      for (size_t j = 0; j < kPartSize; ++j) {
        pointers_[i][j] = deque.pointers_[i][j];
      }
    }
  }

  Deque(size_t n) : begin_(0, pointers_), end_(n, pointers_) {
    initialization(n);
    for (size_t i = 0; i < capacity_; ++i) {
      for (size_t j = 0; j < kPartSize; ++j) {
        new (pointers_[i] + j) T();
      }
    }
  }

  Deque(size_t n, const T& value) : begin_(0, pointers_), end_(n, pointers_) {
    initialization(n);
    for (size_t i = 0; i < capacity_; ++i) {
      for (size_t j = 0; j < kPartSize; ++j) {
        new (pointers_[i] + j) T(value);
      }
    }
  }

  ~Deque() { clear_pointer(); }

  size_t size() const { return static_cast<long long>(end_ - begin_); }

  T& operator[](size_t n) {
    iterator it = begin_ + n;
    return *it;
  }

  const T& operator[](size_t n) const {
    iterator it = begin_ + n;
    return *it;
  }

  T& at(long unsigned int n) {
    iterator iter(n, pointers_);
    if (iter >= end_ || iter < begin_ || end_ == begin_) {
      throw std::out_of_range("");
    }
    return *iter;
  }

  const T& at(long unsigned int n) const {
    iterator iter(n, pointers_);
    if (iter >= end_ || iter < begin_) {
      throw std::out_of_range("");
    }
    return *iter;
  }

  void push_back(const T& value) {
    if (end_.index % kPartSize == 0) {
      pointers_.push_back(
          reinterpret_cast<T*>(new int8_t[kPartSize * sizeof(T)]));
      ++capacity_;
    }
    new (end_.operator->()) T(value);
    ++end_;
  }

  void push_front(const T& val) {
    if (begin_.index == 0) {
      reserve_begin(capacity_ / 2 + 1);
    }
    --begin_;
    new (begin_.operator->()) T(val);
  }

  void pop_back() {
    --end_;
    end_.operator->()->~T();
  }

  void pop_front() {
    begin_.operator->()->~T();
    ++begin_;
  }

  void insert(iterator iter, const T& value) {
    T current_value = value;
    while (iter != end()) {
      std::swap(*iter, current_value);
      ++iter;
    }
    push_back(current_value);
  }

  void erase(iterator iter) {
    for (iterator i = iter; i != end() - 1; ++i) {
      std::swap(*i, *(i + 1));
    }
    pop_back();
  }

  void swap(Deque<T>& other) {
    std::swap(pointers_, other.pointers_);
    std::swap(capacity_, other.capacity_);
    std::swap(begin_.data, other.begin_.data);
    std::swap(end_.data, other.end_.data);
    std::swap(begin_.index, other.begin_.index);
    std::swap(end_.index, other.end_.index);
  };

  Deque<T>& operator=(const Deque<T>& other) {
    Deque<T> deque(other);
    deque.swap(*this);
    return *this;
  };

  iterator begin() { return begin_; }

  iterator end() { return end_; }

  const_iterator begin() const { return const_iterator(begin_); }

  const_iterator end() const { return const_iterator(end_); }

  const_iterator cbegin() const { return const_iterator(begin_); }

  const_iterator cend() const { return const_iterator(end_); }

  revers_iterator rbegin() { return revers_iterator(end_ - 1); }

  revers_iterator rend() { return revers_iterator(begin_ - 1); }

  const_revers_iterator rbegin() const {
    return const_revers_iterator(end_ - 1);
  }

  const_revers_iterator rend() const {
    return const_revers_iterator(begin_ - 1);
  }

  const_revers_iterator crbegin() const {
    return const_revers_iterator(end_ - 1);
  }

  const_revers_iterator crend() const {
    return const_revers_iterator(begin_ - 1);
  }

 private:
  const static size_t kPartSize = 100;
  std::vector<T*> pointers_;
  size_t capacity_;
  iterator begin_;
  iterator end_;

  void reserve_begin(size_t additional) {
    std::vector<T*> new_pointers(capacity_ + additional);
    for (size_t j = 0; j < additional; ++j) {
      new_pointers[j] = reinterpret_cast<T*>(new int8_t[kPartSize * sizeof(T)]);
    }
    std::uninitialized_copy(pointers_.begin(), pointers_.end(),
                            new_pointers.begin() + additional);
    pointers_ = new_pointers;  //  здесь могла быть утечка
    capacity_ += additional;
    begin_ += additional * kPartSize;
    end_ += additional * kPartSize;
  }

  void initialization(size_t n) {
    capacity_ = n / kPartSize + 1;
    pointers_.resize(capacity_);
    for (size_t i = 0; i < capacity_; ++i) {
      pointers_[i] = reinterpret_cast<T*>(new int8_t[kPartSize * sizeof(T)]);
    }
  }

  void clear_pointer() {
    for (auto iter = begin_; iter < end_; ++iter) {
      iter->~T();
    }
    for (size_t i = 0; i < capacity_; ++i) {
      delete[] reinterpret_cast<uint8_t*>(pointers_[i]);
    }
  }
};
