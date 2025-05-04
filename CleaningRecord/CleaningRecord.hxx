#ifndef CLEANING_RECORD_HXX
#define CLEANING_RECORD_HXX

#include <string>
#include <iostream>

class Date {
private:
    unsigned short day, month, year;
public:
    Date(void) noexcept;
    Date(unsigned short day, unsigned short month, unsigned short year);
    unsigned short getDay(void) const noexcept;
    unsigned short getMonth(void) const noexcept;
    unsigned short getYear(void) const noexcept;
    void setDay(unsigned short day) noexcept;
    void setMonth(unsigned short month) noexcept;
    void setYear(unsigned short year) noexcept;
    std::string toString() const noexcept;
    std::time_t toTimeT() const;
};

class CleaningRecord {
private:
    unsigned int recordID;
    std::string clientName;
    std::string address;
    std::string phone;
    std::string workType;
    double cost;
    Date workDate;
    std::string employeeInitials;

public:
    CleaningRecord(void) noexcept = default;
    CleaningRecord(unsigned int id, const std::string& name, const std::string& address,
                   const std::string& phone, const std::string& workType,
                   double cost, const Date& workDate, const std::string& executor) noexcept;

    unsigned int getRecordID(void) const noexcept;
    std::string getClientName(void) const noexcept;
    std::string getAddress(void) const noexcept;
    std::string getPhone(void) const noexcept;
    std::string getWorkType(void) const noexcept;
    double getCost(void) const noexcept;
    Date getDate(void) const noexcept;
    std::string getEmployeeInitials(void) const noexcept;

    void setRecordID(unsigned int id) noexcept;
    void setClientName(const std::string& name) noexcept;
    void setAddress(const std::string& addr) noexcept;
    void setPhone(const std::string& phone) noexcept;
    void setWorkType(const std::string& type) noexcept;
    void setCost(double cost) noexcept;
    void setWorkDate(const Date& date) noexcept;
    void setEmployeeInitials(const std::string& initials) noexcept;

    friend std::ostream& operator<<(std::ostream& os, const CleaningRecord& record);
};

#endif // CLEANING_RECORD_HXX
