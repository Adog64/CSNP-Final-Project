#ifndef TABLE
#define TABLE_H

class Table
{
private:
    int _size;           // how many people can be seated at this table
    bool _reserved;
    int _timestamp;

public:
    Table();
    Table(int size);
    bool reserve();     // reserve the table
    bool clean();       // prepare the table for the next customer
    bool isReserved();
    int when();
    int getSize();
};

#endif