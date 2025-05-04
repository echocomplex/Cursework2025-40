#include "CleaningRecord.hxx"

Date::Date(void) noexcept {
    this->day = 1;
    this->month = 1;
    this->year = 1;
}

Date::Date(unsigned short day, unsigned short month, unsigned short year) {
    this->day = (day >= 1 && day <= 31) ? day : 1;
    this->month = (month >= 1 && month <= 12) ? month : 1;
    this->year = (year >= 1) ? year : 1;
}

unsigned short Date::getDay(void) const noexcept {
    return this->day;
}

unsigned short Date::getMonth(void) const noexcept {
    return this->month;
}

unsigned short Date::getYear(void) const noexcept {
    return this->year;
}

void Date::setDay(unsigned short day) noexcept {
    this->day = day;
}

void Date::setMonth(unsigned short month) noexcept {
    this->month = month;
}

void Date::setYear(unsigned short year) noexcept {
    this->year = year;
}

std::string Date::toString() const noexcept {
    return std::to_string(day) + '.' + std::to_string(month) + '.' + std::to_string(year);
}

CleaningRecord::CleaningRecord(unsigned int id, const std::string& name, const std::string& address,
                               const std::string& phone, const std::string& workType,
                               double cost, const Date& workDate, const std::string& executor) noexcept {
    this->recordID = id;
    this->clientName = name;
    this->address = address;
    this->phone = phone;
    this->workType = workType;
    this->cost = cost;
    this->workDate = workDate;
    this->employeeInitials = executor;
}

unsigned int CleaningRecord::getRecordID() const noexcept {
    return this->recordID;
}

std::string CleaningRecord::getClientName() const noexcept {
    return this->clientName;
}

std::string CleaningRecord::getAddress() const noexcept {
    return this->address;
}

std::string CleaningRecord::getPhone() const noexcept {
    return this->phone;
}

std::string CleaningRecord::getWorkType() const noexcept {
    return this->workType;
}

double CleaningRecord::getCost() const noexcept {
    return this->cost;
}

Date CleaningRecord::getDate() const noexcept {
    return this->workDate;
}

std::string CleaningRecord::getEmployeeInitials() const noexcept {
    return this->employeeInitials;
}

void CleaningRecord::setRecordID(unsigned int id) noexcept {
    this->recordID = id;
}

void CleaningRecord::setClientName(const std::string& name) noexcept {
    this->clientName = name;
}

void CleaningRecord::setAddress(const std::string& addr) noexcept {
    this->address = addr;
}

void CleaningRecord::setPhone(const std::string& phone) noexcept {
    this->phone = phone;
}

void CleaningRecord::setWorkType(const std::string& type) noexcept {
    this->workType = type;
}

void CleaningRecord::setCost(double cost) noexcept {
    this->cost = cost;
}

void CleaningRecord::setWorkDate(const Date& date) noexcept {
    this->workDate = date;
}

void CleaningRecord::setEmployeeInitials(const std::string& initials) noexcept {
    this->employeeInitials = initials;
}

std::ostream& operator<<(std::ostream& os, const CleaningRecord& record) {
    os << "ID: " << record.recordID << "\n"
       << "Client: " << record.clientName << "\n"
       << "Address: " << record.address << "\n"
       << "Phone: " << record.phone << "\n"
       << "Work Type: " << record.workType << "\n"
       << "Cost: $" << record.cost << "\n"
       << "Date: " << record.workDate.toString() << "\n"
       << "Executor: " << record.employeeInitials;
    return os;
}

std::time_t Date::toTimeT() const {
    std::tm timeStruct{};
    timeStruct.tm_mday = this->day;
    timeStruct.tm_mon = this->month - 1;
    timeStruct.tm_year = this->year - 1900;
    timeStruct.tm_hour = 0;
    timeStruct.tm_min = 0;
    timeStruct.tm_sec = 0;
    timeStruct.tm_isdst = -1;

    return std::mktime(&timeStruct);
}
