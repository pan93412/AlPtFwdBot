#include "BotMessageHandler.hpp"

void anyMessageHandler(TgBot::Message::Ptr msg) {
    if (msg->text.compare("機器人退散！！星爆氣流滾出斬！") == 0) {
    api.leaveChat(msg->chat->id);
    infoMessage("\n資訊：" + std::to_string(msg->from->id) + " 已讓這台機器人從 " + std::to_string(msg->chat->id) + " 滾蛋。");
  }
  api.sendMessage(msg->chat->id, "你傳的是 " + msg->text + " 嗎？");
}
