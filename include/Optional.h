#ifndef OPTIONAL_H
#define OPTIONAL_H

// Optional definition
#ifdef __has_include

// Check for standard library
#  if __has_include(<optional>)
#    include<optional>
     using std::optional;
     using std::make_optional;
     using std::nullopt;

// Check for exprimental version (bug fix for Xcode on macOS)
#  elif __has_include(<experimental/optional>)
#    include <experimental/optional>
     using std::experimental::optional;
     using std::experimental::make_optional;
     using std::experimental::nullopt;

// Not found
#  else
#     error "Missing <optional>"
#  endif
#endif

#endif OPTIONAL_H
