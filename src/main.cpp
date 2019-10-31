#include <cstdlib>
#include "BotMessageHandlerLibs.hpp"

/*! \brief 重設訊息記錄
 * 
 * \param api getApi()
 */
void reset(TgBot::Api& api) {
  auto upd = api.getUpdates();
  api.getUpdates(upd[upd.size()-1]->updateId+1);
}

/*! \brief 處理傳入的使用者名稱成 MD 格式
 * 
 * \param username 使用者名稱
 */
std::string mdUsername(std::string username) {
  if (username.compare("") == 0) return "";
  return (boost::format("([@%1%](https://t.me/%1%))") % username).str();
}

int main(int argc, char* argv[]) {
  // 從 argv 取得 TG Bot Token
  if (argc < 2) {
    errorMessage("請設定 token 和 / 或 接收者！");
    infoMessage("usage: " + std::string(argv[0]) + " token 接收者");
    infoMessage("token   @BotFather 取得的機器人憑證");
    infoMessage("接收者  誰要接收轉傳的訊息？設 0 則不受理轉傳訊息。");
    return 1;
  }
    
  TgBot::Bot bot((std::string(argv[1])));
  auto api = bot.getApi();
  int64_t forwardTo = atoll(argv[2]);

  bot.getEvents().onCommand("start", [=](TgBot::Message::Ptr msg) {
    api.sendMessage(msg->chat->id, "嗨！這是台私訊機器人，傳送訊息後會轉寄給管理員 :)");
  });

  bot.getEvents().onCommand("chatid", [=](TgBot::Message::Ptr msg) {
    api.sendMessage(msg->chat->id, std::to_string(msg->chat->id));
  });

  bot.getEvents().onCommand("reply", [=](TgBot::Message::Ptr msg) {
    std::smatch results;
    std::regex_match(msg->text, results, std::regex("/reply.* (.+)-(.+) (.+)"));
    try {
      api.sendMessage(std::stoll(results[1].str()), results[3].str(), true, std::stol(results[2].str()));
      api.sendMessage(msg->chat->id, "我們幫你轉傳出去了喔！👍", true, msg->messageId);
    } catch (std::invalid_argument e) {
      errorMessage("轉傳時發生錯誤。可能是格式錯誤？what()：" + std::string(e.what()));
    }
  });

  if (forwardTo != 0) bot.getEvents().onAnyMessage([=](TgBot::Message::Ptr msg) {
    // (1) 轉傳處等於來源處 (2) 接收者 == 0
    if (msg->chat->id == forwardTo || forwardTo == 0) return;
    auto fwdmsg = api.forwardMessage(forwardTo, msg->chat->id, msg->messageId);
    api.sendMessage(
      forwardTo,
      (boost::format(
          "來源：%1%\n傳送者：%2% %3%\n若要回覆，請用 `/reply %1%-%4% 訊息` 。"
      ) % msg->chat->id % (msg->from->firstName + " " + msg->from->lastName) % mdUsername(msg->from->username) % msg->messageId).str(),
      true, fwdmsg->messageId,
      std::make_shared< TgBot::GenericReply >(), "Markdown"
    );
    api.sendMessage(msg->chat->id, "我們幫你轉傳出去了喔！👍", true, msg->messageId);
  });

  while (true) try {
    infoMessage("正在啟動...");
    infoMessage("機器人名稱：" + api.getMe()->username);
    TgBot::TgLongPoll longPoll(bot);
    
    while (true) {
      std::cout << sdrstr("90") << "\rI: 已啟動長期輪詢 (Long Poll) " << sdrreset << std::flush;
      longPoll.start();
    }
  } catch (TgBot::TgException& e) {
    errorMessage("\n發生錯誤：" + std::string(e.what()));
    warnMessage("正在重新啟動...");
    reset(api); // 重設訊息記錄
    continue;
  }

  return 0;
}
