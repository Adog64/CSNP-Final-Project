#include "Table.h"
#include <ctime>

Table::Table()
{
    _size = 5;
}

Table::Table(int size)
{
    _size = size;
}

int Table::getSize()
{
    return _size;
}

bool Table::reserve()
{
    if (!_reserved)
    {
        _reserved = true;
        _timestamp = time(0);
        return true;
    }
    return false;
}

bool Table::isReserved()
{
    return _reserved;
}

int Table::when()
{
    return _timestamp;
}

bool Table::clean()
{
    if (_reserved)
    {
        _reserved = false;
        return true;
    }
    return false;
}