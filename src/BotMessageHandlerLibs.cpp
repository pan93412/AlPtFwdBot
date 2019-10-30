#include "BotMessageHandlerLibs.hpp"

namespace Handlers {
  void leaveChat(const TgBot::Api& api, TgBot::Message::Ptr msg, std::string triggerMsg) {
    if (msg->text.compare(triggerMsg) == 0) {
      api.sendMessage(msg->chat->id, "喔，我是時候得走了，掰掰～");
      api.leaveChat(msg->chat->id);
      infoMessage((boost::format("\n資訊：%1% 傳了會讓機器人從 %2% 離開的訊息。") % std::to_string(msg->from->id) % std::to_string(msg->chat->id)).str());
    }
  }
}
