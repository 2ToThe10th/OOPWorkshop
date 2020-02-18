#include <algorithm>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>

typedef struct stat Stat;

class String {
public:
  char *start_of_string;
  int number_of_symbols;

  String(char *start_of_string, int number_of_symbols)
      : start_of_string(start_of_string), number_of_symbols(number_of_symbols) {}

  void swap(String& other) {
    std::swap(start_of_string, other.start_of_string);
    std::swap(number_of_symbols, other.number_of_symbols);
  }
  void Write(int fd_out) {
    write(fd_out, start_of_string, number_of_symbols);
    write(fd_out, "\n", 1);
  }
};

void SkipSymbolsInc(const String &str, int &id) {
  while (id < str.number_of_symbols && (str.start_of_string[id] == '.' || str.start_of_string[id] == ',' ||
                             str.start_of_string[id] == '?' || str.start_of_string[id] == '!')) {
    ++id;
  }
}

bool CompareString(const String &first_str,
                    const String &second_str) {
  int id_first = 0;
  int id_second = 0;

  while (true) {
    SkipSymbolsInc(first_str, id_first);
    SkipSymbolsInc(second_str, id_second);

    if (id_second == second_str.number_of_symbols) {
      return false;
    }
    if (id_first == first_str.number_of_symbols) {
      return true;
    }

    if (first_str.start_of_string[id_first] != second_str.start_of_string[id_second]) {
      return first_str.start_of_string[id_first] < second_str.start_of_string[id_second];
    }

    ++id_first;
    ++id_second;
  }
}

void SkipSymbolsDecr(const String &str, int &id) {
  while (id >= 0 && (str.start_of_string[id] == '.' || str.start_of_string[id] == ',' || str.start_of_string[id] == '?' ||
                     str.start_of_string[id] == '!')) {
    --id;
  }
}

bool CompareStringReversed(const String &first_str,
                             const String &second_str) {
  int id_first = first_str.number_of_symbols;
  int id_second = second_str.number_of_symbols;

  while (true) {
    --id_first;
    --id_second;

    SkipSymbolsDecr(first_str, id_first);
    SkipSymbolsDecr(second_str, id_second);

    if (id_second < 0) {
      return false;
    }
    if (id_first < 0) {
      return true;
    }

    if (first_str.start_of_string[id_first] != second_str.start_of_string[id_second]) {
      return first_str.start_of_string[id_first] < second_str.start_of_string[id_second];
    }
  }
}

void FindLines(std::vector<String> &book, char *all_book,
                int length_of_book) {
  int start_of_line = 0;
  for (int i = 0; i < length_of_book; ++i) {
    if (all_book[i] == '\n') {
      if (start_of_line != i) {
        book.emplace_back(all_book + start_of_line, i - start_of_line);
      }
      start_of_line = i + 1;
    }
  }
  if (start_of_line != length_of_book) {
    book.emplace_back(all_book + start_of_line, length_of_book - start_of_line);
  }
}

void WriteVector(std::vector<String> &book, int fd_out) {
  for (auto &line : book) {
    line.Write(fd_out);
  }
}

char *ReadFullBook(int &length_of_book) {
  int fd_in = open("in.txt", O_RDONLY);

  Stat stat;
  fstat(fd_in, &stat);
  length_of_book = stat.st_size;

  char *all_book = new char[length_of_book];
  read(fd_in, all_book, length_of_book);

  close(fd_in);

  return all_book;
}

int main() {

  int length_of_book;
  char *all_book = ReadFullBook(length_of_book);

  std::vector<String> book;

  FindLines(book, all_book, length_of_book);

  int fd_out = open("out.txt", O_WRONLY | O_TRUNC);

  std::sort(book.begin(), book.end(), CompareString);
  WriteVector(book, fd_out);
  write(fd_out, "-------------------------\n", 26);

  std::sort(book.begin(), book.end(), CompareStringReversed);
  WriteVector(book, fd_out);
  write(fd_out, "-------------------------\n", 26);

  write(fd_out, all_book, length_of_book);

  close(fd_out);
}