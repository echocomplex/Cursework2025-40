#ifndef INTERFACE_HXX
#define INTERFACE_HXX

#include <iostream>
#include <List.hxx>
#include <CleaningRecord.hxx>
#include <Database.hxx>

class Interface {
private:
    Database unit;
    void displayMenu(void);
    void getCleaningRecord(CleaningRecord& unit);
    int removeRecord(void);
    void clearInputBuffer(void);
    void inputDateRange(std::time_t& start, std::time_t& end);
public:
    Interface(void) = default;
    Interface(const Interface& unit) = delete;
    Interface& operator=(const Interface& unit) = delete;
    ~Interface(void) noexcept = default;
    void pool(void);
};

#endif // INTERFACE_HXX
