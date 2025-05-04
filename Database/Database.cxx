#include "Database.hxx"
#include <ctime>
#include <set>

Database::Database() {
    this->filename = "database.txt";
    this->filename_enc = "database.enc";
    this->crypter.decrypt(this->filename_enc, this->filename);
    this->file.open(this->filename, true);
    this->file.readToList(this->data);
}

Database::Database(const std::string& filename) {
    this->filename = filename + ".txt";
    this->filename_enc = filename + ".enc";
    this->crypter.decrypt(this->filename_enc, this->filename);
    this->file.open(this->filename);
    this->file.readToList(this->data);
}

Database::Database(const List<CleaningRecord>& unit, const std::string& filename) {
    this->data = unit;
    this->filename = filename + ".txt";
    this->filename_enc = filename + ".enc";
    this->file.open(this->filename);
}

Database::Database(const Database& unit) {
    this->data = unit.data;
    this->filename = unit.filename;
    this->filename_enc = unit.filename_enc;
    this->file.open(unit.filename);
}

Database::~Database() {
    this->file.rewriteFromList(this->data);
    this->crypter.encrypt(this->filename, this->filename_enc);
}

Database& Database::operator=(const Database& unit) noexcept {
    if (this == &unit) return *this;
    this->data = unit.data;
    this->filename = unit.filename;
    this->filename_enc = unit.filename_enc;
    this->file.open(unit.filename);
    return *this;
}

CleaningRecord& Database::operator[](const unsigned int index) noexcept {
    return this->data[index];
}

const CleaningRecord& Database::operator[](const unsigned int index) const noexcept {
    return this->data[index];
}

std::ostream& operator<<(std::ostream& os, const Database& unit) {
    for (unsigned int i = 0; i < unit.data.length(); ++i)
        os << i + 1 << ' ' << unit[i] << std::endl;
    return os;
}

void Database::append(const CleaningRecord& unit) noexcept {
    this->data.append(unit);
}

void Database::remove(const unsigned int index) noexcept {
    this->data.remove(index);
}

unsigned int Database::size() noexcept {
    return this->data.length();
}

void Database::getAddressesLast3Days(List<std::string>& addresses) const noexcept {
    std::time_t now = std::time(nullptr);
    std::time_t threeDaysAgo = now - 3 * 24 * 60 * 60;

    std::set<std::string> unique;

    for (unsigned int i = 0; i < this->data.length(); ++i) {
        const CleaningRecord& record = this->data[i];
        std::time_t recordTime = record.getDate().toTimeT();
        if (recordTime >= threeDaysAgo) {
            unique.insert(record.getAddress());
        }
    }

    for (const std::string& addr : unique) {
        addresses.append(addr);
    }
}

void Database::getClientsByWorkLastWeek(List<std::string>& clients, const std::string& workType) const noexcept {
    std::time_t now = std::time(nullptr);
    std::time_t weekAgo = now - 7 * 24 * 60 * 60;

    std::set<std::string> unique;

    for (unsigned int i = 0; i < this->data.length(); ++i) {
        const CleaningRecord& record = this->data[i];
        std::time_t recordTime = record.getDate().toTimeT();
        if (recordTime >= weekAgo && record.getWorkType() == workType) {
            unique.insert(record.getClientName());
        }
    }

    for (const std::string& client : unique) {
        clients.append(client);
    }
}

unsigned int Database::countClientsInPeriod(std::time_t start, std::time_t end) const noexcept {
    std::set<std::string> unique;
    for (unsigned int i = 0; i < this->data.length(); ++i) {
        const CleaningRecord& record = this->data[i];
        std::time_t recordTime = record.getDate().toTimeT();
        if (recordTime >= start && recordTime <= end) {
            unique.insert(record.getClientName());
        }
    }
    return unique.size();
}
