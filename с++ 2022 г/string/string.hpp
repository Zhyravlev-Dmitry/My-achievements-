#include <cstring>
#include <iostream>

class String {
 public:
  String() = default;

  String(size_t sz, char ch = '\0')
      : size_(sz), capacity_(sz), str_(new char[sz]) {
    memset(str_, ch, size_);
  }

  String(const char* c_str)
      : size_(strlen(c_str)), capacity_(size_), str_(new char[size_]) {
    memcpy(str_, c_str, size_);
  }

  String(char ch) : size_(1), capacity_(size_), str_(new char[size_]) {
    str_[0] = ch;
  }

  String(std::initializer_list<char> lst) {
    size_ = lst.size();
    capacity_ = size_;
    str_ = new char[size_];
    std::copy(lst.begin(), lst.end(), str_);
  }

  String(const String& s)
      : size_(s.size_), capacity_(size_), str_(new char[size_]) {
    memcpy(str_, s.str_, size_);
  }  // copy

  String& operator=(String str) {
    swap(str);
    return *this;
  }

  const char& operator[](size_t index) const { return str_[index]; }

  char& operator[](size_t index) { return str_[index]; }

  size_t length() const { return size_; }

  void push_back(char value) {
    if (size_ == capacity_) {
      update(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    str_[size_++] = value;
  }

  bool empty() const { return size_ == 0; }

  void pop_back() {
    if (!empty()) {
      --size_;
      if (size_ <= capacity_ / (2 * 2)) {
        update(capacity_ / 2);
      }
    }
  }

  const char& back() const { return str_[size_ - 1]; }

  char& back() { return str_[size_ - 1]; }

  const char& front() const { return str_[0]; }

  char& front() { return str_[0]; }

  String& operator+=(const String& str) {
    size_t size = str.size_;
    for (size_t i = 0; i < size; ++i) {
      push_back(str[i]);
    }
    return *this;
  }

  String& operator+=(char value) {
    push_back(value);
    return *this;
  }

  size_t find(const String& substring) const {
    if (size_ < substring.size_) {
      return size_;
    }
    size_t first_number = 0;
    while ((first_number < size_ - substring.size_ + 1) &&
           !coincidence(first_number, substring)) {
      first_number += 1;
    }
    if (first_number == size_ - substring.size_ + 1) {
      first_number = size_;
    }
    return first_number;
  }

  size_t rfind(const String& substring) const {
    if (size_ < substring.size_) {
      return size_;
    }
    int first_number =
        static_cast<int>(size_) - static_cast<int>(substring.size_);
    while (first_number >= 0 &&
           !coincidence(static_cast<size_t>(first_number), substring)) {
      first_number -= 1;
    }
    if (first_number == -1) {
      first_number = size_;
    }
    return first_number;
  }

  String substr(size_t start, size_t count) const {
    String substr(count);
    memcpy(substr.str_, str_ + start, count);
    return substr;
  }

  void clear() {
    size_ = 0;
    capacity_ = 0;
    delete[] str_;
    str_ = nullptr;
  }

  ~String() { delete[] str_; }

 private:
  size_t size_ = 0;
  size_t capacity_ = 0;
  char* str_ = nullptr;

  void swap(String& str) {
    std::swap(size_, str.size_);
    std::swap(capacity_, str.capacity_);
    std::swap(str_, str.str_);
  }

  void update(size_t new_capacity) {
    char* new_str = new char[new_capacity];
    memcpy(new_str, str_, size_);
    delete[] str_;
    str_ = new_str;
    capacity_ = new_capacity;
  }

  bool coincidence(size_t first_number, const String& substring) const {
    bool coincidence = true;
    for (size_t i = 0; i < substring.size_; ++i) {
      if (substring[i] != str_[i + first_number]) {
        coincidence = false;
        break;
      }
    }
    return coincidence;
  }
};

String operator+(const String& str_1, const String& str_2) {
  String copy = str_1;
  copy += str_2;
  return copy;
}

bool operator==(const String& str_1, const String& str_2) {
  if (str_1.length() != str_2.length()) {
    return false;
  }
  bool ans = true;
  for (size_t i = 0; i < str_1.length(); ++i) {
    if (str_1[i] != str_2[i]) {
      ans = false;
      break;
    }
  }
  return ans;
}

std::ostream& operator<<(std::ostream& out, const String& str) {
  for (size_t i = 0; i < str.length(); ++i) {
    out << str[i];
  }
  return out;
}

std::istream& operator>>(std::istream& in, String& str) {
  str.clear();
  char value;
  while (in.get(value) && (std::isspace(value) != 0) && value != '\0') {
  }
  if (std::isspace(value) == 0) {
    str.push_back(value);
  }
  while (in.get(value) && (std::isspace(value) == 0) && value != '\0') {
    str.push_back(value);
  }
  return in;
}
