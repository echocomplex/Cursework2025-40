#include "Filer.hxx"

Filer::Filer (const std::string& path, const bool createNew) {
    if (createNew) {
        this->file.open(path, std::ios::in);
        if (!this->file.is_open()) {
            this->file.open(path, std::ios::out);
            this->file.close();
            this->file.open(path, std::ios::in);
            if (!this->file.is_open()) throw std::runtime_error("Failed to create the file.");
        }
    }
    else {
        this->file.open(path, std::ios::in);
        if (!this->file.is_open()) throw std::runtime_error("File cannot be opened or does not exists");
    }
    this->path = path;
}

Filer::~Filer (void) noexcept {
    if (this->file.is_open()) this->file.close();
}

void Filer::open (const std::string& path, const bool createNew) {
    if (createNew) {
        this->file.open(path, std::ios::in);
        if (!this->file.is_open()) {
            this->file.open(path, std::ios::out);
            this->file.close();
            this->file.open(path, std::ios::in);
            if (!this->file.is_open()) throw std::runtime_error("Failed to create the file.");
        }
    }
    else {
        this->file.open(path, std::ios::in);
        if (!this->file.is_open()) throw std::runtime_error("File cannot be opened or does not exists");
    }
    this->path = path;
}

void Filer::read (std::string& str) {
    if (!this->file.is_open()) throw std::runtime_error("File does not open now");
    
    this->mutex.lock();

    this->file.close();
    this->file.open(this->path, std::ios::in);

    this->file.seekg(0, std::ios::beg);
    std::string temp;

    this->file.seekp(0, std::ios::beg);
    while (std::getline(this->file, temp)) str += temp + '\n';
    
    this->mutex.unlock();
}

void Filer::readToList (List<CleaningRecord>& list) {
    if (!this->file.is_open()) throw std::runtime_error("File does not open now");

    this->mutex.lock();
    this->file.close();
    this->file.open(this->path, std::ios::in);

    std::string temp;
    while (std::getline(this->file, temp)) {
        CleaningRecord record;
        this->stringToRecord(record, temp);
        list.append(record);
    }

    this->mutex.unlock();
}


void Filer::writeBack (std::string& string) {
    if (!this->file.is_open()) throw std::runtime_error("File does not open now");
    else if (string.empty()) return;

    this->mutex.lock();

    this->file.close();
    this->file.open(this->path, std::ios::out | std::ios::app);

    this->file << string << '\n';
    this->file.flush();
    this->mutex.unlock();
}

void Filer::writeBackFromRecord(const CleaningRecord& record) {
    if (!this->file.is_open()) throw std::runtime_error("File does not open now");

    this->mutex.lock();
    this->file.close();
    this->file.open(this->path, std::ios::out | std::ios::app);

    this->file <<
        record.getRecordID() << "$$" <<
        record.getDate().getDay() << "$$" <<
        record.getDate().getMonth() << "$$" <<
        record.getDate().getYear() << "$$" <<
        record.getAddress() << "$$" <<
        record.getClientName() << "$$" <<
        record.getPhone() << "$$" <<
        record.getWorkType() << "$$" <<
        record.getCost() << "$$" <<
        record.getEmployeeInitials() << '\n';

    this->file.flush();
    this->mutex.unlock();
}



void Filer::rewrite (std::string& string) {
    if (!this->file.is_open()) throw std::runtime_error("File does not open now");
    else if (string.empty()) return;

    this->mutex.lock();

    this->file.close();
    this->file.open(this->path, std::ios::out | std::ios::trunc);

    this->file << string << '\n';
    this->file.flush();

    this->mutex.unlock();
}

void Filer::rewriteFromList(const List<CleaningRecord>& list) {
    if (!this->file.is_open()) throw std::runtime_error("File does not open now");
    else if (list.length() == 0) return;

    this->mutex.lock();
    this->file.close();
    this->file.open(this->path, std::ios::out | std::ios::trunc);

    for (unsigned int i = 0; i < list.length(); ++i) {
        const CleaningRecord& record = list[i];
        this->file <<
            record.getRecordID() << "$$" <<
            record.getDate().getDay() << "$$" <<
            record.getDate().getMonth() << "$$" <<
            record.getDate().getYear() << "$$" <<
            record.getAddress() << "$$" <<
            record.getClientName() << "$$" <<
            record.getPhone() << "$$" <<
            record.getWorkType() << "$$" <<
            record.getCost() << "$$" <<
            record.getEmployeeInitials() << '\n';
    }

    this->file.flush();
    this->mutex.unlock();
}


void Filer::stringToRecord(CleaningRecord& record, const std::string& str) {
    if (str.empty()) return;

    std::string arr[10];
    unsigned short count = 0;

    for (size_t i = 0; i < (str.size() - 1) && count < 10; ++i) {
        if (str[i] == '$' && str[i + 1] == '$') {
            ++count; ++i;
        } else {
            arr[count].push_back(str[i]);
        }
    }
    if (count < 10) arr[count].push_back(str[str.size() - 1]);

    try {
        record.setRecordID(std::stoul(arr[0]));
    } catch (...) {
        record.setRecordID(0);
    }

    try {
        record.setWorkDate(Date(std::stoul(arr[1]), std::stoul(arr[2]), std::stoul(arr[3])));  // Date
    } catch (...) {
        record.setWorkDate(Date(1, 1, 2000));
    }

    record.setAddress(arr[4]);
    record.setClientName(arr[5]);
    record.setPhone(arr[6]);
    record.setWorkType(arr[7]);
    
    try {
        record.setCost(std::stod(arr[8]));
    } catch (...) {
        record.setCost(0);
    }
    
    record.setEmployeeInitials(arr[9]); 
}
