#include <algorithm>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>
#include <cctype>
#include <string_view>

typedef struct stat Stat_t;

bool CompareString(const std::string_view &, const std::string_view &);

bool CompareStringReversed(const std::string_view &, const std::string_view &);

void FindLines(std::vector<std::string_view> &, char *, int);

void WriteVector(std::vector<std::string_view> &, int);

char *ReadFullBook(int &);

int main() {

  int length_of_book;
  char *all_book = ReadFullBook(length_of_book);

  std::vector<std::string_view> book;

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

void SkipSymbolsInc(const std::string_view &str, int &id) {
  while (id < str.size() && std::ispunct(str[id])) {
    ++id;
  }
}

bool CompareString(const std::string_view &first_str,
                   const std::string_view &second_str) {
  int id_first = 0;
  int id_second = 0;

  while (true) {
    SkipSymbolsInc(first_str, id_first);
    SkipSymbolsInc(second_str, id_second);

    if (id_second == second_str.size()) {
      return false;
    }
    if (id_first == first_str.size()) {
      return true;
    }

    if (first_str[id_first] != second_str[id_second]) {
      return first_str[id_first] < second_str[id_second];
    }

    ++id_first;
    ++id_second;
  }
}

void SkipSymbolsDecr(const std::string_view &str, int &id) {
  while (id >= 0 && std::ispunct(str[id])) {
    --id;
  }
}

bool CompareStringReversed(const std::string_view &first_str,
                           const std::string_view &second_str) {
  int id_first = first_str.size();
  int id_second = second_str.size();

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

    if (first_str[id_first] != second_str[id_second]) {
      return first_str[id_first] < second_str[id_second];
    }
  }
}

void FindLines(std::vector<std::string_view> &book, char *all_book,
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

void Write(std::string_view &string, int fd_out) {
  write(fd_out, string.data(), string.size());
  write(fd_out, "\n", 1);
}

void WriteVector(std::vector<std::string_view> &book, int fd_out) {
  for (auto &line : book) {
    Write(line, fd_out);
  }
}

char *ReadFullBook(int &length_of_book) {
  int fd_in = open("in.txt", O_RDONLY);

  Stat_t stat;
  fstat(fd_in, &stat);
  length_of_book = stat.st_size;

  char *all_book = new char[length_of_book];
  read(fd_in, all_book, length_of_book);

  close(fd_in);

  return all_book;
}