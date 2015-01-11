#include "AnyValue.h"

AnyValue::~AnyValue() {
    delete content;
}

AnyValue AnyValue::&swap(AnyValue & rhs) {
  std::swap(content, rhs.content);
  return *this;
}

template<typename ValueType>
AnyValue AnyValue::&operator = (const ValueType & rhs) {
  AnyValue(rhs).swap(*this);
  return *this;
}

AnyValue AnyValue::&operator = (const AnyValue & rhs) {
  AnyValue(rhs).swap(*this);
  return *this;
}

bool AnyValue::empty() const {
    return !content;
}

const std::type_info AnyValue::&type() const {
  return content ? content->type() : typeid(void);
}

template <class T>
bool AnyValue::hastype() const { 
   return &type() == &typeid(T);
}

template <class ValueType>
bool AnyValue::operator == (const ValueType &rhs) const {
    if(&type() != &typeid(ValueType)) return false;
    return *AnyCast<ValueType>(this) == rhs;
}

template <class ValueType>
bool AnyValue::operator != (const ValueType &rhs) const {
  return !operator == (rhs);
}
