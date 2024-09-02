#include <iostream>
#include "BotStarter.hpp"
#include "DiscordBotStarter.hpp"
#include "Storage.hpp"
#include "LogStream.hpp" 
#include "ControllerEbobot.hpp"
#include <memory>
#include "FakeStorage.hpp"
#include <thread>
#include "SpinLock.hpp"


void T1(std::shared_ptr<Log> logger)
{
	for(int i = 0; i < 10000; i++)
		logger->Logging("Message1", 8, ClassError::INFO);
	
	
}

void T2(std::shared_ptr<Log> logger)
{
	for(int i = 0; i < 10000; i++)
		logger->Logging("Message2", 8, ClassError::INFO);
}


int main()
{
	std::ios_base::sync_with_stdio(false);
	std::shared_ptr<Log> logger ( new LogStream(std::cerr.rdbuf()));
	std::thread t1(T1, logger);
	std::thread t2(T2, logger);
	
	t1.join();
	t2.join();
	/*
	std::cout << i << std::endl;
	
	std::shared_ptr<Log> logger(new LogStream(std::cerr.rdbuf()));
	std::thread t1(T1, logger);
	std::thread t2(T2, logger);

	std::shared_ptr<Storage> storage(new FakeStorage(logger));
	
	t1.join();
	t2.join();	
		*/
	/*DiscordBotStarter dsbot("", log);	
	ControllerEbobot controller(storage, log);	
	BotStarter& bot = dsbot;
	bot.Start(controller);*/

}

