
#pragma once


#include <gloperate/pipeline/DataSlot.h>

#include <gloperate/pipeline/Stage.h>


namespace gloperate
{


template <typename T>
DataSlot<T>::DataSlot(const T & value)
: cppexpose::DirectValue<T, AbstractDataSlot>(value)
{
}

template <typename T>
DataSlot<T>::~DataSlot()
{
}

template <typename T>
T & DataSlot<T>::operator*()
{
    return *this->ptr();
}

template <typename T>
const T & DataSlot<T>::operator*() const
{
    return *this->ptr();
}

template <typename T>
T * DataSlot<T>::operator->()
{
    return this->ptr();
}

template <typename T>
const T * DataSlot<T>::operator->() const
{
    return this->ptr();
}

template <typename T>
bool DataSlot<T>::isObject() const
{
    return false;
}

template <typename T>
void DataSlot<T>::onValueChanged(const T & value)
{
    this->valueChanged(value);

    if (Stage * stage = this->parentStage())
    {
        // [TODO] Propagate change
    }
}


} // namespace gloperate
