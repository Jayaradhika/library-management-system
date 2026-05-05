#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <ctime>
#include <sstream>

using namespace std;

// ═══════════════════════════════════════════════════════
//  Utility helpers
// ═══════════════════════════════════════════════════════
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string currentDate() {
    time_t now = time(nullptr);
    char buf[12];
    strftime(buf, sizeof(buf), "%Y-%m-%d", localtime(&now));
    return string(buf);
}

void printLine(char c = '-', int w = 62) { cout << string(w, c) << "\n"; }

// ═══════════════════════════════════════════════════════
//  Class: Book
// ═══════════════════════════════════════════════════════
class Book {
private:
    int    bookId;
    string title;
    string author;
    string genre;
    int    totalCopies;
    int    availableCopies;

public:
    // ── Constructors ──────────────────────────────────
    Book() : bookId(0), totalCopies(0), availableCopies(0) {}

    Book(int id, const string& t, const string& a,
         const string& g, int copies)
        : bookId(id), title(t), author(a), genre(g),
          totalCopies(copies), availableCopies(copies) {}

    // ── Getters ───────────────────────────────────────
    int    getBookId()          const { return bookId;          }
    string getTitle()           const { return title;           }
    string getAuthor()          const { return author;          }
    string getGenre()           const { return genre;           }
    int    getTotalCopies()     const { return totalCopies;     }
    int    getAvailableCopies() const { return availableCopies; }
    bool   isAvailable()        const { return availableCopies > 0; }

    // ── Setters ───────────────────────────────────────
    void setTitle(const string& t)  { title  = t; }
    void setAuthor(const string& a) { author = a; }
    void setGenre(const string& g)  { genre  = g; }

    // ── Operations ────────────────────────────────────
    bool issueBook() {
        if (availableCopies <= 0) return false;
        --availableCopies;
        return true;
    }

    bool returnBook() {
        if (availableCopies >= totalCopies) return false;
        ++availableCopies;
        return true;
    }

    // ── Display ───────────────────────────────────────
    void printRow() const {
        cout << "  " << left
             << setw(6)  << bookId
             << setw(28) << (title.length() > 26 ? title.substr(0,24)+"..." : title)
             << setw(20) << (author.length()> 18 ? author.substr(0,16)+"..." : author)
             << setw(5)  << availableCopies << "/" << totalCopies << "\n";
    }

    void printDetail() const {
        printLine('-', 50);
        cout << "  Book ID        : " << bookId          << "\n"
             << "  Title          : " << title           << "\n"
             << "  Author         : " << author          << "\n"
             << "  Genre          : " << genre           << "\n"
             << "  Copies (Avail) : " << availableCopies
             << " / " << totalCopies                     << "\n"
             << "  Status         : " << (isAvailable() ? "Available" : "All Issued") << "\n";
        printLine('-', 50);
    }

    // ── File I/O ──────────────────────────────────────
    string serialise() const {
        ostringstream o;
        o << bookId << "\n" << title  << "\n" << author << "\n"
          << genre  << "\n" << totalCopies << "\n" << availableCopies << "\n";
        return o.str();
    }

    static Book deserialise(istream& in) {
        Book b;
        string line;
        getline(in, line); b.bookId          = stoi(line);
        getline(in, b.title);
        getline(in, b.author);
        getline(in, b.genre);
        getline(in, line); b.totalCopies     = stoi(line);
        getline(in, line); b.availableCopies = stoi(line);
        return b;
    }
};

// ═══════════════════════════════════════════════════════
//  Class: Member
// ═══════════════════════════════════════════════════════
class Member {
private:
    int    memberId;
    string name;
    string email;
    string phone;
    int    booksIssued;   // current count
    static const int MAX_BOOKS = 3;

public:
    Member() : memberId(0), booksIssued(0) {}

    Member(int id, const string& n, const string& e, const string& p)
        : memberId(id), name(n), email(e), phone(p), booksIssued(0) {}

    int    getMemberId()    const { return memberId;   }
    string getName()        const { return name;       }
    string getEmail()       const { return email;      }
    string getPhone()       const { return phone;      }
    int    getBooksIssued() const { return booksIssued;}
    bool   canBorrow()      const { return booksIssued < MAX_BOOKS; }

    void setName(const string& n)  { name  = n; }
    void setEmail(const string& e) { email = e; }
    void setPhone(const string& p) { phone = p; }

    void incrementIssued()  { if (booksIssued < MAX_BOOKS) ++booksIssued; }
    void decrementIssued()  { if (booksIssued > 0)         --booksIssued; }

    void printRow() const {
        cout << "  " << left
             << setw(8)  << memberId
             << setw(22) << (name.length() > 20 ? name.substr(0,18)+"..." : name)
             << setw(26) << email
             << setw(6)  << booksIssued << "/" << MAX_BOOKS << "\n";
    }

    void printDetail() const {
        printLine('-', 50);
        cout << "  Member ID      : " << memberId    << "\n"
             << "  Name           : " << name        << "\n"
             << "  Email          : " << email       << "\n"
             << "  Phone          : " << phone       << "\n"
             << "  Books Issued   : " << booksIssued << " / " << MAX_BOOKS << "\n"
             << "  Can Borrow     : " << (canBorrow() ? "Yes" : "No (limit reached)") << "\n";
        printLine('-', 50);
    }

    string serialise() const {
        ostringstream o;
        o << memberId << "\n" << name  << "\n" << email << "\n"
          << phone    << "\n" << booksIssued << "\n";
        return o.str();
    }

    static Member deserialise(istream& in) {
        Member m;
        string line;
        getline(in, line); m.memberId    = stoi(line);
        getline(in, m.name);
        getline(in, m.email);
        getline(in, m.phone);
        getline(in, line); m.booksIssued = stoi(line);
        return m;
    }
};

// ═══════════════════════════════════════════════════════
//  Class: BorrowRecord
// ═══════════════════════════════════════════════════════
class BorrowRecord {
public:
    int    recordId;
    int    memberId;
    int    bookId;
    string memberName;
    string bookTitle;
    string issueDate;
    string returnDate;   // empty = not yet returned
    bool   returned;

    BorrowRecord() : recordId(0), memberId(0), bookId(0), returned(false) {}

    BorrowRecord(int rid, int mid, int bid,
                 const string& mname, const string& btitle)
        : recordId(rid), memberId(mid), bookId(bid),
          memberName(mname), bookTitle(btitle),
          issueDate(currentDate()), returned(false) {}

    void markReturned() {
        returned    = true;
        returnDate  = currentDate();
    }

    void printRow() const {
        cout << "  " << left
             << setw(6)  << recordId
             << setw(8)  << memberId
             << setw(22) << (memberName.length()>20 ? memberName.substr(0,18)+"..." : memberName)
             << setw(6)  << bookId
             << setw(22) << (bookTitle.length()>20  ? bookTitle.substr(0,18)+"..."  : bookTitle)
             << setw(12) << issueDate
             << (returned ? returnDate : "  (active)")
             << "\n";
    }

    string serialise() const {
        ostringstream o;
        o << recordId   << "\n" << memberId   << "\n" << bookId     << "\n"
          << memberName << "\n" << bookTitle  << "\n" << issueDate  << "\n"
          << returnDate << "\n" << (returned ? 1 : 0) << "\n";
        return o.str();
    }

    static BorrowRecord deserialise(istream& in) {
        BorrowRecord r;
        string line;
        getline(in, line); r.recordId   = stoi(line);
        getline(in, line); r.memberId   = stoi(line);
        getline(in, line); r.bookId     = stoi(line);
        getline(in, r.memberName);
        getline(in, r.bookTitle);
        getline(in, r.issueDate);
        getline(in, r.returnDate);
        getline(in, line); r.returned   = (stoi(line) == 1);
        return r;
    }
};

// ═══════════════════════════════════════════════════════
//  Class: Library  (main controller)
// ═══════════════════════════════════════════════════════
class Library {
private:
    string            libraryName;
    vector<Book>      books;
    vector<Member>    members;
    vector<BorrowRecord> records;

    const string BOOKS_FILE   = "books.dat";
    const string MEMBERS_FILE = "members.dat";
    const string RECORDS_FILE = "records.dat";

    // ── ID helpers ────────────────────────────────────
    int nextBookId() const {
        int mx = 1000;
        for (const auto& b : books) mx = max(mx, b.getBookId());
        return mx + 1;
    }
    int nextMemberId() const {
        int mx = 2000;
        for (const auto& m : members) mx = max(mx, m.getMemberId());
        return mx + 1;
    }
    int nextRecordId() const {
        int mx = 0;
        for (const auto& r : records) mx = max(mx, r.recordId);
        return mx + 1;
    }

    // ── Find helpers ──────────────────────────────────
    Book*   findBook(int id) {
        for (auto& b : books)   if (b.getBookId()   == id) return &b;
        return nullptr;
    }
    Member* findMember(int id) {
        for (auto& m : members) if (m.getMemberId() == id) return &m;
        return nullptr;
    }

    // ── File I/O ──────────────────────────────────────
    template<typename T>
    void saveVec(const vector<T>& vec, const string& file) const {
        ofstream out(file);
        if (!out) { cerr << "  [ERROR] Cannot write " << file << "\n"; return; }
        out << vec.size() << "\n";
        for (const auto& item : vec) out << item.serialise();
        out.close();
    }

    template<typename T>
    vector<T> loadVec(const string& file) const {
        vector<T> vec;
        ifstream in(file);
        if (!in) return vec;
        int count; string line;
        getline(in, line); count = stoi(line);
        for (int i = 0; i < count; ++i) vec.push_back(T::deserialise(in));
        in.close();
        return vec;
    }

    void saveAll() {
        saveVec(books,   BOOKS_FILE);
        saveVec(members, MEMBERS_FILE);
        saveVec(records, RECORDS_FILE);
    }

public:
    // ── Constructor ───────────────────────────────────
    explicit Library(const string& name) : libraryName(name) {
        books   = loadVec<Book>        (BOOKS_FILE);
        members = loadVec<Member>      (MEMBERS_FILE);
        records = loadVec<BorrowRecord>(RECORDS_FILE);
    }

    // ════════════════════════════════════════════════
    //  BOOK MANAGEMENT
    // ════════════════════════════════════════════════
    void addBook() {
        cout << "\n  ── Add New Book ──\n";
        string title, author, genre;
        int copies;

        clearInput();
        cout << "  Title   : "; getline(cin, title);
        cout << "  Author  : "; getline(cin, author);
        cout << "  Genre   : "; getline(cin, genre);
        cout << "  Copies  : ";
        while (!(cin >> copies) || copies < 1) {
            cout << "  [!] Enter a positive number: "; clearInput();
        }

        int id = nextBookId();
        books.emplace_back(id, title, author, genre, copies);
        saveAll();
        cout << "  ✔  Book added! Book ID: " << id << "\n";
    }

    void displayAllBooks() const {
        cout << "\n  ── All Books (" << books.size() << ") ──\n";
        if (books.empty()) { cout << "  No books in the library.\n"; return; }
        printLine('=', 62);
        cout << "  " << left << setw(6) << "ID"
             << setw(28) << "Title"
             << setw(20) << "Author"
             << "Avail\n";
        printLine('-', 62);
        for (const auto& b : books) b.printRow();
        printLine('=', 62);
    }

    void searchBooks() {
        cout << "\n  Search by:\n"
             << "  1. Title\n"
             << "  2. Author\n"
             << "  Choice: ";
        int ch; cin >> ch;
        clearInput();
        cout << "  Keyword: ";
        string kw; getline(cin, kw);
        // case-insensitive
        string kwl = kw;
        transform(kwl.begin(), kwl.end(), kwl.begin(), ::tolower);

        vector<Book*> results;
        for (auto& b : books) {
            string field = (ch == 2) ? b.getAuthor() : b.getTitle();
            transform(field.begin(), field.end(), field.begin(), ::tolower);
            if (field.find(kwl) != string::npos) results.push_back(&b);
        }

        cout << "\n  " << results.size() << " result(s) found:\n";
        if (results.empty()) return;
        printLine('=', 62);
        cout << "  " << left << setw(6) << "ID"
             << setw(28) << "Title"
             << setw(20) << "Author"
             << "Avail\n";
        printLine('-', 62);
        for (const auto* b : results) b->printRow();
        printLine('=', 62);
    }

    void updateBook() {
        int id;
        cout << "\n  Enter Book ID to update: "; cin >> id;
        Book* b = findBook(id);
        if (!b) { cout << "  [!] Book not found.\n"; return; }
        b->printDetail();

        clearInput();
        string tmp;
        cout << "  New Title  [" << b->getTitle()  << "]: "; getline(cin, tmp);
        if (!tmp.empty()) b->setTitle(tmp);
        cout << "  New Author [" << b->getAuthor() << "]: "; getline(cin, tmp);
        if (!tmp.empty()) b->setAuthor(tmp);
        cout << "  New Genre  [" << b->getGenre()  << "]: "; getline(cin, tmp);
        if (!tmp.empty()) b->setGenre(tmp);

        saveAll();
        cout << "  ✔  Book updated.\n";
    }

    void deleteBook() {
        int id;
        cout << "\n  Enter Book ID to delete: "; cin >> id;
        auto it = find_if(books.begin(), books.end(),
                          [id](const Book& b){ return b.getBookId() == id; });
        if (it == books.end()) { cout << "  [!] Book not found.\n"; return; }

        cout << "  Delete \"" << it->getTitle() << "\"? (y/n): ";
        char c; cin >> c;
        if (tolower(c) == 'y') {
            books.erase(it);
            saveAll();
            cout << "  ✔  Book deleted.\n";
        } else cout << "  Cancelled.\n";
    }

    // ════════════════════════════════════════════════
    //  MEMBER MANAGEMENT
    // ════════════════════════════════════════════════
    void addMember() {
        cout << "\n  ── Add New Member ──\n";
        string name, email, phone;
        clearInput();
        cout << "  Name   : "; getline(cin, name);
        cout << "  Email  : "; getline(cin, email);
        cout << "  Phone  : "; getline(cin, phone);

        int id = nextMemberId();
        members.emplace_back(id, name, email, phone);
        saveAll();
        cout << "  ✔  Member added! Member ID: " << id << "\n";
    }

    void displayAllMembers() const {
        cout << "\n  ── All Members (" << members.size() << ") ──\n";
        if (members.empty()) { cout << "  No members registered.\n"; return; }
        printLine('=', 66);
        cout << "  " << left << setw(8) << "ID"
             << setw(22) << "Name"
             << setw(26) << "Email"
             << "Books\n";
        printLine('-', 66);
        for (const auto& m : members) m.printRow();
        printLine('=', 66);
    }

    void searchMember() {
        cout << "\n  Enter Member ID or Name keyword: ";
        clearInput();
        string kw; getline(cin, kw);

        // try numeric ID first
        try {
            int id = stoi(kw);
            Member* m = findMember(id);
            if (m) { m->printDetail(); return; }
        } catch (...) {}

        // name search
        string kwl = kw;
        transform(kwl.begin(), kwl.end(), kwl.begin(), ::tolower);
        for (const auto& m : members) {
            string nl = m.getName();
            transform(nl.begin(), nl.end(), nl.begin(), ::tolower);
            if (nl.find(kwl) != string::npos) m.printDetail();
        }
    }

    void deleteMember() {
        int id;
        cout << "\n  Enter Member ID to remove: "; cin >> id;
        auto it = find_if(members.begin(), members.end(),
                          [id](const Member& m){ return m.getMemberId() == id; });
        if (it == members.end()) { cout << "  [!] Member not found.\n"; return; }
        if (it->getBooksIssued() > 0) {
            cout << "  [!] Member has " << it->getBooksIssued()
                 << " book(s) outstanding. Cannot remove.\n";
            return;
        }
        cout << "  Remove \"" << it->getName() << "\"? (y/n): ";
        char c; cin >> c;
        if (tolower(c) == 'y') { members.erase(it); saveAll(); cout << "  ✔  Member removed.\n"; }
        else cout << "  Cancelled.\n";
    }

    // ════════════════════════════════════════════════
    //  BORROW / RETURN
    // ════════════════════════════════════════════════
    void issueBook() {
        int mid, bid;
        cout << "\n  ── Issue Book ──\n";
        cout << "  Member ID : "; cin >> mid;
        Member* m = findMember(mid);
        if (!m) { cout << "  [!] Member not found.\n"; return; }
        if (!m->canBorrow()) {
            cout << "  [!] " << m->getName() << " has reached the borrowing limit (3 books).\n";
            return;
        }

        cout << "  Book ID   : "; cin >> bid;
        Book* b = findBook(bid);
        if (!b) { cout << "  [!] Book not found.\n"; return; }
        if (!b->isAvailable()) {
            cout << "  [!] No available copies of \"" << b->getTitle() << "\".\n";
            return;
        }

        b->issueBook();
        m->incrementIssued();
        records.emplace_back(nextRecordId(), mid, bid, m->getName(), b->getTitle());
        saveAll();

        cout << "  ✔  \"" << b->getTitle() << "\" issued to "
             << m->getName() << " on " << currentDate() << "\n";
    }

    void returnBook() {
        int mid, bid;
        cout << "\n  ── Return Book ──\n";
        cout << "  Member ID : "; cin >> mid;
        cout << "  Book ID   : "; cin >> bid;

        // find active record
        BorrowRecord* rec = nullptr;
        for (auto& r : records)
            if (r.memberId == mid && r.bookId == bid && !r.returned)
                { rec = &r; break; }

        if (!rec) {
            cout << "  [!] No active borrow record found for this member+book.\n";
            return;
        }

        Member* m = findMember(mid);
        Book*   b = findBook(bid);
        rec->markReturned();
        if (m) m->decrementIssued();
        if (b) b->returnBook();
        saveAll();

        cout << "  ✔  \"" << rec->bookTitle << "\" returned by "
             << rec->memberName << " on " << currentDate() << "\n";
    }

    // ════════════════════════════════════════════════
    //  RECORDS
    // ════════════════════════════════════════════════
    void viewAllRecords() const {
        cout << "\n  ── Borrow Records (" << records.size() << ") ──\n";
        if (records.empty()) { cout << "  No records.\n"; return; }
        printLine('=', 82);
        cout << "  " << left
             << setw(6)  << "RecID"
             << setw(8)  << "MemID"
             << setw(22) << "Member"
             << setw(6)  << "BkID"
             << setw(22) << "Book"
             << setw(12) << "Issued"
             << "Returned\n";
        printLine('-', 82);
        for (const auto& r : records) r.printRow();
        printLine('=', 82);
    }

    void viewActiveIssues() const {
        cout << "\n  ── Active Issues ──\n";
        printLine('=', 82);
        cout << "  " << left
             << setw(6)  << "RecID"
             << setw(8)  << "MemID"
             << setw(22) << "Member"
             << setw(6)  << "BkID"
             << setw(22) << "Book"
             << "Issued\n";
        printLine('-', 82);
        int cnt = 0;
        for (const auto& r : records)
            if (!r.returned) { r.printRow(); ++cnt; }
        printLine('=', 82);
        cout << "  Total active: " << cnt << "\n";
    }

    // ════════════════════════════════════════════════
    //  MENUS
    // ════════════════════════════════════════════════
    void bookMenu() {
        int ch;
        do {
            cout << "\n  ┌─ Book Management ──────────────────────\n"
                 << "  │  1. Add Book\n"
                 << "  │  2. Display All Books\n"
                 << "  │  3. Search Book (Title / Author)\n"
                 << "  │  4. Update Book\n"
                 << "  │  5. Delete Book\n"
                 << "  │  6. Back\n"
                 << "  └────────────────────────────────────────\n"
                 << "  Choice: ";
            while (!(cin >> ch)) { cout << "  [!] Enter a number: "; clearInput(); }
            switch(ch) {
                case 1: addBook();        break;
                case 2: displayAllBooks();break;
                case 3: searchBooks();    break;
                case 4: updateBook();     break;
                case 5: deleteBook();     break;
                case 6: break;
                default: cout << "  [!] Invalid.\n";
            }
        } while (ch != 6);
    }

    void memberMenu() {
        int ch;
        do {
            cout << "\n  ┌─ Member Management ────────────────────\n"
                 << "  │  1. Register Member\n"
                 << "  │  2. Display All Members\n"
                 << "  │  3. Search Member\n"
                 << "  │  4. Remove Member\n"
                 << "  │  5. Back\n"
                 << "  └────────────────────────────────────────\n"
                 << "  Choice: ";
            while (!(cin >> ch)) { cout << "  [!] Enter a number: "; clearInput(); }
            switch(ch) {
                case 1: addMember();          break;
                case 2: displayAllMembers();  break;
                case 3: searchMember();       break;
                case 4: deleteMember();       break;
                case 5: break;
                default: cout << "  [!] Invalid.\n";
            }
        } while (ch != 5);
    }

    void recordMenu() {
        int ch;
        do {
            cout << "\n  ┌─ Borrow / Return ──────────────────────\n"
                 << "  │  1. Issue Book to Member\n"
                 << "  │  2. Return Book from Member\n"
                 << "  │  3. View All Records\n"
                 << "  │  4. View Active Issues\n"
                 << "  │  5. Back\n"
                 << "  └────────────────────────────────────────\n"
                 << "  Choice: ";
            while (!(cin >> ch)) { cout << "  [!] Enter a number: "; clearInput(); }
            switch(ch) {
                case 1: issueBook();       break;
                case 2: returnBook();      break;
                case 3: viewAllRecords();  break;
                case 4: viewActiveIssues();break;
                case 5: break;
                default: cout << "  [!] Invalid.\n";
            }
        } while (ch != 5);
    }

    void run() {
        int ch;
        do {
            cout << "\n";
            printLine('=');
            cout << "         " << libraryName << "\n";
            printLine('=');
            cout << "  1. Book Management\n"
                 << "  2. Member Management\n"
                 << "  3. Issue / Return Books\n"
                 << "  4. Exit\n";
            printLine();
            cout << "  Choice: ";
            while (!(cin >> ch)) { cout << "  [!] Enter a number: "; clearInput(); }
            switch(ch) {
                case 1: bookMenu();   break;
                case 2: memberMenu(); break;
                case 3: recordMenu(); break;
                case 4: cout << "\n  Thank you! Goodbye.\n\n"; break;
                default: cout << "  [!] Invalid option.\n";
            }
        } while (ch != 4);
    }
};

// ═══════════════════════════════════════════════════════
//  Entry Point
// ═══════════════════════════════════════════════════════
int main() {
    Library lib("CITY PUBLIC LIBRARY");
    lib.run();
    return 0;
}
