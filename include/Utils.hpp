#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <functional>

namespace rlib {

  template<typename T>
  class Observer {
  public:
      Observer(std::function<void(T)> callback) : data(), callback(callback) { }

      Observer& operator=(const T& newValue) {
        if (data != newValue) {
          data = newValue;
          callback(data);
        }
        return *this;
      }

      operator T() const {
        return data;
      }

  private:
      T data;
      std::function<void(T)> callback;
  };

}

#endif // UTILS_HPP
