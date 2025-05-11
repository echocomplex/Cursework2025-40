#ifndef DATABASE_HXX
#define DATABASE_HXX

#include <List.hxx>
#include <CleaningRecord.hxx>
#include <Filer.hxx>
#include <Crypter.hxx>
#include <string>
#include <iostream>

class Database {
protected:
    Filer file;
    std::string filename;
    std::string filename_enc;
    List<CleaningRecord> data;
    Crypter crypter;

public:
    Database();
    Database(const std::string& filename);
    Database(const List<CleaningRecord>& unit, const std::string& filename);
    Database(const Database& unit);
    ~Database();

    Database& operator=(const Database& unit) noexcept;
    CleaningRecord& operator[](const unsigned int index) noexcept;
    const CleaningRecord& operator[](const unsigned int index) const noexcept;
    friend std::ostream& operator<<(std::ostream& os, const Database& unit);

    void append(const CleaningRecord& unit) noexcept;
    void remove(const unsigned int index) noexcept;
    unsigned int size() noexcept;

    void getAddressesLast3Days(List<std::string>& addresses) const noexcept;
    void getClientsByWorkLastWeek(List<std::string>& clients, const std::string& workType) const noexcept;
    unsigned int countClientsInPeriod(std::time_t start, std::time_t end) const noexcept;
};

#endif // DATABASE_HXX
