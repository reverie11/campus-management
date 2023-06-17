#pragma once

#include <string>

class Displayable {
public:
  virtual std::string to_string() const = 0;
};

/**
 * Gibt ein beliebiges Objekt welches die abstrakte Displayable implementiert
 * auf der Standardausgabe aus, in dem es dessen to_string Methode nutzt. (2)
 *
 * @param displayable Das Objekt welches ausgegeben wird.
 */
void print_stdout(Displayable &displayable);

bool all_digits(const std::string &str);
bool digits_exist(const std::string &str);
