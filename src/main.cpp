#include <tgbot/tgbot.h>
#include "Messages.hpp"
#include "BotMessageHandlerLibs.hpp"

/*! \brief 重設訊息記錄
 * 
 * \param api getApi()
 */
void reset(TgBot::Api& api) {
  auto upd = api.getUpdates();
  api.getUpdates(upd[upd.size()-1]->updateId+1);
}

int main(int argc, char* argv[]) {
  // 從 argv 取得 TG Bot Token
  if (argc < 2) {
    errorMessage("請設定 Token！");
    return 1;
  }
    
  TgBot::Bot bot((std::string(argv[1])));
  auto api = bot.getApi();
//   int64_t forwardTo = 0;
//   
//   bot.getEvents().onCommand("start", [=](TgBot::Message::Ptr msg) {
//     api.sendMessage(msg->chat->id, "傳送訊息後會轉寄到 msg->text);
//   });
  bot.getEvents().onAnyMessage([=](TgBot::Message::Ptr msg) {
    Handlers::leaveChat(api, msg, "=~=~=~!LeAvE!~@@n!b"); // Handlers: 某個指令可以讓機器人離開
    
    /* 實際邏輯 */
    if (msg->text.compare("") != 0) api.sendMessage(msg->chat->id, msg->text);
  });

  while (true) try {
    infoMessage("正在啟動...");
    infoMessage("機器人名稱：" + bot.getApi().getMe()->username);
    TgBot::TgLongPoll longPoll(bot);
    
    // 計數器
    int times = 0;
    while (true) {
      std::cout << sdrstr("90") << "\r資訊：已啟動長期輪詢 (Long Poll) - " + std::to_string(times) << sdrreset << std::flush;
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
