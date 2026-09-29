#include "random_vector.h"

#include <cstdlib>
#include <stdexcept>

RandomVector::RandomVector(int size, double max_val) {
  if (size <= 0) {
    throw std::invalid_argument("size must be greater than zero");
  }

  if (max_val < 0) {
    throw std::invalid_argument("max_val must not be negative");
  }

  for (int i = 0; i < size; ++i) {
    double random_value =
        max_val * static_cast<double>(std::rand()) / RAND_MAX;

    vect.push_back(random_value);
  }
}

void RandomVector::print() {
  for (double value : vect) {
    std::cout << value << " ";
  }

  std::cout << std::endl;
}

double RandomVector::mean() {
  if (vect.empty()) {
    throw std::runtime_error("cannot calculate the mean of an empty vector");
  }

  double sum = 0;

  for (double value : vect) {
    sum += value;
  }

  return sum / vect.size();
}

double RandomVector::max() {
  if (vect.empty()) {
    throw std::runtime_error("cannot find the maximum of an empty vector");
  }

  double maximum = vect[0];

  for (double value : vect) {
    if (value > maximum) {
      maximum = value;
    }
  }

  return maximum;
}

double RandomVector::min() {
  if (vect.empty()) {
    throw std::runtime_error("cannot find the minimum of an empty vector");
  }

  double minimum = vect[0];

  for (double value : vect) {
    if (value < minimum) {
      minimum = value;
    }
  }

  return minimum;
}

void RandomVector::printHistogram(int bins) {
  if (bins <= 0) {
    throw std::invalid_argument("bins must be greater than zero");
  }

  if (vect.empty()) {
    return;
  }

  std::vector<int> counts(bins, 0);

  double minimum = min();
  double maximum = max();
  double range = maximum - minimum;

  for (double value : vect) {
    int index;

    if (range == 0) {
      index = 0;
    } else {
      index = static_cast<int>(
          (value - minimum) / range * bins
      );

      // 最大值会恰好落在 bins，需要放回最后一个分组。
      if (index >= bins) {
        index = bins - 1;
      }
    }

    ++counts[index];
  }

  int greatest_count = counts[0];

  for (int count : counts) {
    if (count > greatest_count) {
      greatest_count = count;
    }
  }

  // 从最高一行开始，纵向打印直方图。
  for (int level = greatest_count; level > 0; --level) {
    for (int count : counts) {
      if (count >= level) {
        std::cout << "*** ";
      } else {
        std::cout << "    ";
      }
    }

    std::cout << std::endl;
  }
}
