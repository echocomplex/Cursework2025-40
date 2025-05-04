#include "Interface.hxx"
#include <limits>

void Interface::clearInputBuffer(void) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Interface::getCleaningRecord(CleaningRecord& unit) {
    std::string temp;
    unsigned short day, month, year;
    unsigned int recordID;
    std::string phone, employeeInitials;

    std::cout << "Enter record ID: ";
    std::cin >> recordID;
    this->clearInputBuffer();
    unit.setRecordID(recordID);

    std::cout << "Enter client name: ";
    std::getline(std::cin, temp);
    unit.setClientName(temp);

    std::cout << "Enter address: ";
    std::getline(std::cin, temp);
    unit.setAddress(temp);

    std::cout << "Enter phone number: ";
    std::getline(std::cin, phone);
    unit.setPhone(phone);

    std::cout << "Enter work type: ";
    std::getline(std::cin, temp);
    unit.setWorkType(temp);

    std::cout << "Enter day: ";
    std::cin >> day;
    this->clearInputBuffer();
    std::cout << "Enter month: ";
    std::cin >> month;
    this->clearInputBuffer();
    std::cout << "Enter year: ";
    std::cin >> year;
    this->clearInputBuffer();
    unit.setWorkDate(Date(day, month, year));

    std::cout << "Enter employee initials: ";
    std::getline(std::cin, employeeInitials);
    unit.setEmployeeInitials(employeeInitials);
}


int Interface::removeRecord(void) {
    int number;
    while (true) {
        std::cout << "Enter record number to delete (1-" << this->unit.size() << "): ";
        if (!(std::cin >> number)) {
            std::cin.clear();
            this->clearInputBuffer();
            std::cerr << "Error: Please enter a number\n\n";
            continue;
        }

        if (number > 0 && number <= this->unit.size()) {
            this->clearInputBuffer();
            return number - 1;
        }

        std::cerr << "Error: Number must be between 1 and " << this->unit.size() << "\n\n";
    }
}

void Interface::displayMenu(void) {
    std::cout << "\n=== Cleaning Records Menu ===" << std::endl;
    std::cout << "1. Display all records" << std::endl;
    std::cout << "2. Add new record" << std::endl;
    std::cout << "3. Remove record" << std::endl;
    std::cout << "4. Get addresses of cleanings in last 3 days" << std::endl;
    std::cout << "5. Get clients by work type (last week)" << std::endl;
    std::cout << "6. Count clients in a date range" << std::endl;
    std::cout << "7. Exit" << std::endl;
    std::cout << "Enter your choice (1-7): ";
}

void Interface::inputDateRange(std::time_t& start, std::time_t& end) {
    unsigned short d, m, y;
    Date from, to;

    std::cout << "Enter start date (DD MM YYYY): ";
    std::cin >> d >> m >> y;
    this->clearInputBuffer();
    from = Date(d, m, y);

    std::cout << "Enter end date (DD MM YYYY): ";
    std::cin >> d >> m >> y;
    this->clearInputBuffer();
    to = Date(d, m, y);

    start = from.toTimeT();
    end = to.toTimeT();
}

void Interface::pool(void) {
    short choice = 0;
    CleaningRecord newRecord;
    List<std::string> result;
    std::string temp;
    std::time_t start, end;

    while (true) {
        this->displayMenu();

        while (!(std::cin >> choice) || choice < 1 || choice > 7) {
            std::cout << "Invalid input. Please enter 1-7: ";
            this->clearInputBuffer();
        }

        this->clearInputBuffer();

        switch (choice) {
            case 1:
                std::cout << "\n[All Records]\n";
                std::cout << this->unit << std::endl;
                break;
            case 2:
                std::cout << "\n[Add Record]\n";
                this->getCleaningRecord(newRecord);
                this->unit.append(newRecord);
                break;
            case 3:
                std::cout << "\n[Remove Record]\n";
                this->unit.remove(this->removeRecord());
                break;
            case 4:
                std::cout << "\n[Addresses from last 3 days]\n";
                this->unit.getAddressesLast3Days(result);
                for (int i = 0; i < result.length(); ++i) std::cout << result[i] << std::endl;
                result.clear();
                break;
            case 5:
                std::cout << "Enter work type: ";
                std::getline(std::cin, temp);
                std::cout << "\n[Clients by work type]\n";
                this->unit.getClientsByWorkLastWeek(result, temp);
                for (int i = 0; i < result.length(); ++i) std::cout << result[i] << std::endl;
                result.clear();
                break;
            case 6:
                std::cout << "[Count clients in period]\n";
                this->inputDateRange(start, end);
                std::cout << "Clients in period: " << this->unit.countClientsInPeriod(start, end) << std::endl;
                break;
            case 7:
                std::cout << "\nExiting program...\n";
                return;
        }

        std::cout << "\nPress Enter to continue...";
        this->clearInputBuffer();
    }
}
