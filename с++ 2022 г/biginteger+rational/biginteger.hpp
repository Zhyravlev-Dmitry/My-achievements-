#include <iostream>
#include <string>
#include <vector>

class BigInteger {
 public:
  BigInteger() { big_int_.push_back(0); }

  BigInteger(long long value) {
    if (value < 0) {
      value *= -1;
      sign_ = -1;
    }
    while (value >= kBlock) {
      big_int_.push_back(value % kBlock);
      value /= kBlock;
    }
    if ((value != 0) || big_int_.empty()) {
      big_int_.push_back(value);
    }
  }

  BigInteger(const std::string& value) {
    int begin = 0;
    if (value[0] == '-') {
      begin = 1;
      sign_ = -1;
    }
    for (int i = value.size(); i > begin; i -= kSizeBlock) {
      if (i - kSizeBlock >= begin) {
        big_int_.push_back(std::stol(value.substr(i - kSizeBlock, kSizeBlock)));
      } else {
        big_int_.push_back(std::stol(value.substr(begin, i - begin)));
      }
    }
    removeZeros();
  }

  BigInteger(const BigInteger& value) = default;
  ~BigInteger() = default;

  explicit operator bool() const {
    return !(big_int_.size() == 1 && big_int_[0] == 0);
  }

  std::string toString() const {
    std::string str;
    if ((sign_ == -1) && !((big_int_.size() == 1) && (big_int_[0] == 0))) {
      str += '-';
    }
    for (int i = static_cast<int>(big_int_.size()) - 1; i >= 0; --i) {
      const int kNumberSystem = 10;
      if ((big_int_[i] < kBlock / kNumberSystem) &&
          !((big_int_.size() == 1) && (big_int_[0] == 0)) &&
          (i != static_cast<int>(big_int_.size()) - 1)) {
        int flag = big_int_[i];
        if (flag == 0) {
          flag = 1;
        }
        while (flag < kBlock / kNumberSystem) {
          str += '0';
          flag *= kNumberSystem;
        }
      }
      str += std::to_string(big_int_[i]);
    }
    return str;
  }

  BigInteger& operator=(BigInteger big_int) {
    std::swap(big_int.big_int_, big_int_);
    std::swap(big_int.sign_, sign_);
    return *this;
  }

  BigInteger& operator+=(const BigInteger& value) {
    if (value.sign_ == sign_) {
      modularAdd(value);
      return *this;
    }
    if (modularLess(*this, value)) {
      sign_ *= -1;
    }
    modularSubtract(value);
    return *this;
  }

  BigInteger& operator-=(const BigInteger& value) {
    if (value.sign_ != sign_) {
      modularAdd(value);
      return *this;
    }
    if (modularLess(*this, value)) {
      sign_ *= -1;
    }
    modularSubtract(value);
    return *this;
  }

  BigInteger& operator*=(const BigInteger& value) {
    BigInteger answer;
    if (value.sign_ != sign_) {
      answer.sign_ = -1;
    } else {
      answer.sign_ = 1;
    }
    answer.resizeZeros(value.big_int_.size() + big_int_.size());
    for (size_t i = 0; i < value.big_int_.size(); ++i) {
      for (size_t j = 0; j < big_int_.size(); ++j) {
        answer.big_int_[i + j] += value.big_int_[i] * big_int_[j];
        if (answer.big_int_[i + j] >= kBlock) {
          answer.big_int_[i + j + 1] += answer.big_int_[i + j] / kBlock;
          answer.big_int_[i + j] %= kBlock;
        }
      }
    }
    answer.removeZeros();
    *this = answer;
    return *this;
  }

  BigInteger& operator/=(const BigInteger& value) {
    if (value.sign_ != sign_) {
      sign_ = -1;
    } else {
      sign_ = 1;
    }
    if (modularLess(*this, value)) {
      big_int_.resize(1);
      big_int_[0] = 0;
      return *this;
    }
    division(value);
    return *this;
  }

  BigInteger& operator%=(const BigInteger& value) {
    BigInteger factor = *this;
    factor /= value;
    factor *= value;
    *this -= factor;
    return *this;
  }

  BigInteger& operator++() {
    *this += 1;
    return *this;
  }

  BigInteger operator++(int) {
    BigInteger copy = *this;
    *this += 1;
    return copy;
  }

  BigInteger& operator--() {
    *this -= 1;
    return *this;
  }

  BigInteger operator--(int) {
    BigInteger copy = *this;
    *this -= 1;
    return copy;
  }

  BigInteger operator-() {
    BigInteger copy = *this;
    copy.sign_ *= -1;
    return copy;
  }

  static void swap(BigInteger& big_int_1, BigInteger& big_int_2) {
    std::swap(big_int_1.big_int_, big_int_2.big_int_);
    std::swap(big_int_1.sign_, big_int_2.sign_);
  }

  static bool modularLess(const BigInteger& big_int_1,
                          const BigInteger& big_int_2) {
    if (big_int_1.big_int_.size() < big_int_2.big_int_.size()) {
      return true;
    }
    if (big_int_1.big_int_.size() > big_int_2.big_int_.size()) {
      return false;
    }
    for (int i = big_int_1.big_int_.size() - 1; i >= 0; --i) {
      if (big_int_1.big_int_[i] < big_int_2.big_int_[i]) {
        return true;
      }
      if (big_int_1.big_int_[i] > big_int_2.big_int_[i]) {
        return false;
      }
    }
    return false;
  }

  int getSign() const {
    if ((big_int_.size() == 1) && (big_int_[0] == 0)) {
      return 1;
    }
    return sign_;
  }

 private:
  std::vector<long long> big_int_;
  const int kSizeBlock = 8;
  const long long kBlock = 1e8;
  int sign_ = 1;

  void resizeZeros(size_t size) {
    size_t old_size = big_int_.size();
    big_int_.resize(size);
    for (size_t i = old_size; i < big_int_.size(); ++i) {
      big_int_[i] = 0;
    }
  }

  void removeZeros() {
    int quantity = 0;
    for (int i = big_int_.size() - 1; i >= 1; --i) {
      if (big_int_[i] != 0) {
        break;
      }
      quantity += 1;
    }
    big_int_.resize(big_int_.size() - quantity);
  }

  void modularAddSmaller(const BigInteger& value) {
    for (size_t i = 0; i < value.big_int_.size(); ++i) {
      big_int_[i] += value.big_int_[i];
      if ((big_int_[i] >= kBlock) && (i + 1 < big_int_.size())) {
        big_int_[i] -= kBlock;
        big_int_[i + 1] += 1;
      }
    }
  }

  void modularAdd(const BigInteger& value) {
    if (value.big_int_.size() > big_int_.size()) {
      resizeZeros(value.big_int_.size());
    }
    modularAddSmaller(value);
    if (value.big_int_.size() == big_int_.size()) {
      if (big_int_[big_int_.size() - 1] >= kBlock) {
        big_int_[big_int_.size() - 1] -= kBlock;
        big_int_.push_back(1);
      }
    }
  }

  void modularSubtract(const BigInteger& value) {
    if (modularLess(value, *this)) {
      subtractionSmaller(value);
      return;
    }
    resizeZeros(value.big_int_.size());
    long long occupy = 0;
    long long reduced;
    for (size_t i = 0; i < big_int_.size(); ++i) {
      reduced = value.big_int_[i] - occupy;
      occupy = 0;
      if (value.big_int_[i] < big_int_[i]) {
        occupy = 1;
        reduced += kBlock;
      }
      big_int_[i] = reduced - big_int_[i];
    }
    removeZeros();
  }

  void subtractionSmaller(const BigInteger& value) {
    for (size_t i = 0; i < value.big_int_.size(); ++i) {
      if (big_int_[i] < value.big_int_[i]) {
        big_int_[i + 1] -= 1;
        big_int_[i] += kBlock;
      }
      big_int_[i] -= value.big_int_[i];
    }
    size_t i = value.big_int_.size();
    while ((i < big_int_.size()) && (big_int_[i] < 0)) {
      big_int_[i + 1] -= 1;
      big_int_[i] += kBlock;
      ++i;
    }
    removeZeros();
  }

  void pushBack(long long value) {
    big_int_.resize(big_int_.size() + 1);
    for (int i = big_int_.size() - 1; i >= 1; --i) {
      big_int_[i] = big_int_[i - 1];
    }
    big_int_[0] = value;
  }

  void rightResize(int length) {
    if (length >= static_cast<int>(big_int_.size())) {
      return;
    }
    int this_iter = big_int_.size() - length;
    for (int i = 0; i < length; ++i) {
      big_int_[i] = big_int_[this_iter];
      ++this_iter;
    }
    big_int_.resize(length);
  }

  long long factorSearch(const BigInteger& divisible,
                         const BigInteger& divider) const {
    long long left = 0;
    long long right = kBlock;
    while (right - left > 1) {
      long long median = (left + right) / 2;
      BigInteger factor = divider;
      factor *= median;
      if (!(modularLess(divisible, factor))) {
        left = median;
      } else {
        right = median;
      }
    }
    return left;
  }

  void division(const BigInteger& value) {
    BigInteger deduct;
    int deduct_iter = 0;
    deduct.big_int_.resize(value.big_int_.size());
    int this_iter;
    for (this_iter = big_int_.size() - value.big_int_.size();
         this_iter < static_cast<int>(big_int_.size()); ++this_iter) {
      deduct.big_int_[deduct_iter] = big_int_[this_iter];
      deduct_iter += 1;
    }
    this_iter = big_int_.size() - deduct.big_int_.size() - 1;
    if (modularLess(deduct, value)) {
      deduct.pushBack(big_int_[this_iter]);
      deduct_iter += 1;
      this_iter -= 1;
    }
    int new_value_iter = big_int_.size() - 1;
    BigInteger factor;
    for (; deduct_iter <= static_cast<int>(big_int_.size()); ++deduct_iter) {
      factor = value;
      big_int_[new_value_iter] = factorSearch(deduct, value);
      factor *= big_int_[new_value_iter];
      deduct.modularSubtract(factor);
      deduct.pushBack(big_int_[this_iter]);
      deduct.removeZeros();
      new_value_iter -= 1;
      this_iter -= 1;
    }
    rightResize(big_int_.size() - 1 - new_value_iter);
  }
};

bool operator<(const BigInteger& big_int_1, const BigInteger& big_int_2) {
  if (big_int_1.getSign() < big_int_2.getSign()) {
    return false;
  }
  if (big_int_1.getSign() > big_int_2.getSign()) {
    return false;
  }
  if (big_int_1.getSign() == 1) {
    return BigInteger::modularLess(big_int_1, big_int_2);
  }
  return !BigInteger::modularLess(big_int_1, big_int_2);
}

bool operator>(const BigInteger& big_int_1, const BigInteger& big_int_2) {
  return big_int_2 < big_int_1;
}

bool operator==(const BigInteger& big_int_1, const BigInteger& big_int_2) {
  bool answer = !((big_int_1 < big_int_2) || (big_int_2 < big_int_1));
  return answer;
}

bool operator!=(const BigInteger& big_int_1, const BigInteger& big_int_2) {
  bool answer = ((big_int_1 < big_int_2) || (big_int_2 < big_int_1));
  return answer;
}

bool operator<=(const BigInteger& big_int_1, const BigInteger& big_int_2) {
  bool answer = !(big_int_2 < big_int_1);
  return answer;
}

bool operator>=(const BigInteger& big_int_1, const BigInteger& big_int_2) {
  bool answer = !(big_int_1 < big_int_2);
  return answer;
}

std::ostream& operator<<(std::ostream& out, const BigInteger& big_int) {
  out << big_int.toString();
  return out;
}

std::istream& operator>>(std::istream& in, BigInteger& big_int) {
  std::string str;
  in >> str;
  big_int = str;
  return in;
}

BigInteger operator*(const BigInteger& big_int_1, const BigInteger& big_int_2) {
  BigInteger copy = big_int_1;
  copy *= big_int_2;
  return copy;
}

BigInteger operator+(const BigInteger& big_int_1, const BigInteger& big_int_2) {
  BigInteger copy = big_int_1;
  copy += big_int_2;
  return copy;
}

BigInteger operator-(const BigInteger& big_int_1, const BigInteger& big_int_2) {
  BigInteger copy = big_int_1;
  copy -= big_int_2;
  return copy;
}

BigInteger operator/(const BigInteger& big_int_1, const BigInteger& big_int_2) {
  BigInteger copy = big_int_1;
  copy /= big_int_2;
  return copy;
}

BigInteger operator%(const BigInteger& big_int_1, const BigInteger& big_int_2) {
  BigInteger copy = big_int_1;
  copy %= big_int_2;
  return copy;
}

class Rational {
 public:
  Rational(const BigInteger& value) : numerator_(value) {}
  Rational(long long value) : numerator_(value) {}

  Rational() = default;
  Rational(const Rational& value) = default;
  ~Rational() = default;

  std::string toString() const {
    std::string answer = numerator_.toString();
    if (denominator_ > 1) {
      answer += "/";
      answer += denominator_.toString();
    }
    return answer;
  }

  Rational& operator=(Rational rational) {
    BigInteger::swap(rational.numerator_, numerator_);
    BigInteger::swap(rational.denominator_, denominator_);
    return *this;
  }

  Rational& operator*=(const Rational& value) {
    numerator_ *= value.numerator_;
    denominator_ *= value.denominator_;
    cutBack();
    return *this;
  }

  Rational& operator/=(const Rational& value) {
    numerator_ *= value.denominator_;
    denominator_ *= value.numerator_;
    if (value.numerator_ < 0) {
      denominator_ *= -1;
      numerator_ *= -1;
    }
    cutBack();
    return *this;
  }

  Rational& operator+=(const Rational& value) {
    BigInteger lcm = lCM(denominator_, value.denominator_);
    numerator_ *= (lcm / denominator_);
    numerator_ += (value.numerator_ * (lcm / value.denominator_));
    denominator_ = lcm;
    cutBack();
    return *this;
  }

  Rational& operator-=(const Rational& value) {
    BigInteger lcm = lCM(denominator_, value.denominator_);
    numerator_ *= (lcm / denominator_);
    numerator_ -= (value.numerator_ * (lcm / value.denominator_));
    denominator_ = lcm;
    cutBack();
    return *this;
  }

  Rational operator-() {
    Rational copy = *this;
    copy.numerator_ *= -1;
    return copy;
  }

  std::string asDecimal(size_t precision = 0) const {
    std::string answer;
    BigInteger divider = (numerator_ % denominator_);
    if (divider < 0) {
      divider *= -1;
      answer += '-';
    }
    answer += (numerator_ / denominator_).toString();
    const int kNumberSystem = 10;
    for (size_t i = 0; i < precision; ++i) {
      divider *= kNumberSystem;
    }
    if (precision > 0) {
      answer += '.';
      std::string fractional = (divider / denominator_).toString();
      for (size_t i = fractional.size(); i < precision; ++i) {
        answer += '0';
      }
      answer += fractional;
    }
    return answer;
  }

  explicit operator double() const {
    const int kPrecision = 30;
    return std::stod(asDecimal(kPrecision));
  }

 private:
  BigInteger numerator_ = 0;
  BigInteger denominator_ = 1;

  static BigInteger gCD(BigInteger big_int_1, BigInteger big_int_2) {  //  НОД
    if (big_int_1 < 0) {
      big_int_1 *= -1;
    }
    if (big_int_2 < 0) {
      big_int_2 *= -1;
    }
    while (big_int_2 != 0) {
      big_int_1 %= big_int_2;
      BigInteger::swap(big_int_1, big_int_2);
    }
    return big_int_1;
  }

  static BigInteger lCM(const BigInteger& big_int_1,
                        const BigInteger& big_int_2) {  //  НОК
    BigInteger lcm = big_int_1 * big_int_2;
    lcm /= gCD(big_int_1, big_int_2);
    if (lcm < 0) {
      lcm *= -1;
    }
    return lcm;
  }

  void cutBack() {
    BigInteger gcd = gCD(numerator_, denominator_);
    numerator_ /= gcd;
    denominator_ /= gcd;
  }

  friend bool operator<(const Rational& rational_1, const Rational& rational_2);
};

std::ostream& operator<<(std::ostream& out, const Rational& rational) {
  out << rational.toString();
  return out;
}

Rational operator+(const Rational& rational_1, const Rational& rational_2) {
  Rational copy = rational_1;
  copy += rational_2;
  return copy;
}

Rational operator-(const Rational& rational_1, const Rational& rational_2) {
  Rational copy = rational_1;
  copy -= rational_2;
  return copy;
}

Rational operator/(const Rational& rational_1, const Rational& rational_2) {
  Rational copy = rational_1;
  copy /= rational_2;
  return copy;
}

Rational operator*(const Rational& rational_1, const Rational& rational_2) {
  Rational copy = rational_1;
  copy *= rational_2;
  return copy;
}

bool operator<(const Rational& rational_1, const Rational& rational_2) {
  bool answer;
  BigInteger lcm =
      Rational::lCM(rational_1.denominator_, rational_2.denominator_);
  BigInteger factor_1 = lcm / rational_1.denominator_;
  BigInteger factor_2 = lcm / rational_2.denominator_;
  answer = rational_1.numerator_ * factor_1 < rational_2.numerator_ * factor_2;
  return answer;
}

bool operator>(const Rational& rational_1, const Rational& rational_2) {
  return rational_2 < rational_1;
}

bool operator>=(const Rational& rational_1, const Rational& rational_2) {
  return !(rational_1 < rational_2);
}

bool operator<=(const Rational& rational_1, const Rational& rational_2) {
  return !(rational_2 < rational_1);
}

bool operator==(const Rational& rational_1, const Rational& rational_2) {
  return !(rational_2 < rational_1) && !(rational_1 < rational_2);
}

bool operator!=(const Rational& rational_1, const Rational& rational_2) {
  return (rational_2 < rational_1) || (rational_1 < rational_2);
}
