#include <tgbot/tgbot.h>
#include "AlPtBot/Messages.hpp"

void reset(TgBot::Api& api) {
  auto upd = api.getUpdates();
  api.getUpdates(upd[upd.size()-1]->updateId+1);
}

int main(int argc, char* argv[]) {
  // 從 argv 取得 TG Bot Token
  if (argc < 2) {
    errorMessage("錯誤：請設定 Token！");
    return 1;
  }
    
  TgBot::Bot bot((std::string(argv[1])));
  auto api = bot.getApi();

  bot.getEvents().onAnyMessage([=](TgBot::Message::Ptr msg) {
    if (msg->text.compare("機器人退散！！星爆氣流滾出斬！") == 0) {
      api.leaveChat(msg->chat->id);
      infoMessage("\n資訊：" + std::to_string(msg->from->id) + " 已讓這台機器人從 " + std::to_string(msg->chat->id) + " 滾蛋。");
    }
    api.sendMessage(msg->chat->id, "你傳的是 " + msg->text + " 嗎？");
  });

  while (true) try {
    infoMessage("正在啟動…… 機器人名稱：" + bot.getApi().getMe()->username);
    TgBot::TgLongPoll longPoll(bot);
    int times = 0;機器人退散！！星爆氣流滾出斬！
    while (true) {
      std::cout << sdrstr("90") << "\r已啟動長期輪詢 (Long Poll) - " + std::to_string(times) << sdrreset << std::flush;
      longPoll.start();
      times++;
    }
  } catch (TgBot::TgException& e) {
    errorMessage("發生錯誤：" + std::string(e.what()));
    warnMessage("正在嘗試重新啟動…");
    reset(api); // 重設訊息記錄
    continue;
  }
  return 0;
}
