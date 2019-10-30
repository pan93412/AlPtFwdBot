#pragma once
#include <tgbot/tgbot.h>
#include "Messages.hpp"

/*! \brief 專門放置處理器 Lib 的命名空間 */
namespace Handlers {
  /*! \brief 退出群組
  * 
  * \param api Bot.getApi()
  * \param msg 收到的訊息
  * \param triggerMsg 觸發退出訊息
  */
  void leaveChat(const TgBot::Api& api, TgBot::Message::Ptr msg, std::string triggerMsg);
}
