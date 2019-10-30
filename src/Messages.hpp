#pragma once
#include <iostream>
#include <string>
#include <boost/format.hpp>

/*! \brief ANSI SDR 開頭 */
inline const std::string sdrh = "\033[";

/*! \brief ANSI SDR 結尾 */
inline const std::string sdre = "m";

/*! \brief ANSI SDR 重設代碼 */
inline const std::string sdrreset = sdrh + "0" + sdre;

/*! \brief 產生 ANSI SDR 序列
 *
 * \param sdr_comm SDR 指令
 * \return ANSISDR 序列
 */
std::string sdrstr(const std::string sdr_comm);

/*! \brief 錯誤訊息
 * 
 * \param message 訊息
 */
void errorMessage(const std::string message);

/*! \brief 警告訊息
 * 
 * \param message 訊息
 */
void warnMessage(const std::string message);

/*! \brief 資訊訊息
 * 
 * \param message 訊息
 */
void infoMessage(const std::string message);

/*! \brief 除錯訊息
 * 
 * \param debug 是否為除錯模式？
 * \param message 訊息
 */
void debugMessage(bool debug, const std::string message);
