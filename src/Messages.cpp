#include "AlPtBot/Messages.hpp"
#include <string>

std::string sdrstr(const std::string sdr_comm) {
  return sdrh + sdr_comm + sdre;
}

// 自己加 std::flush 啦
void errorMessage(const std::string message) {
  std::cout << sdrstr("1") << sdrstr("31") << message << sdrreset << "\n";
}

void warnMessage(const std::string message) {
  std::cout << sdrstr("1") << sdrstr("31") << message << sdrreset << "\n";
}

void infoMessage(const std::string message) {
  std::cout << sdrstr("1") << sdrstr("36") << message << sdrreset << "\n";
}

void debugMessage(bool debug, const std::string message) {
  if (debug) std::cout << sdrstr("90") << message << sdrreset << "\n";
}
