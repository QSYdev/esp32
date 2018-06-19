#pragma once
#include <WiFiManager.hpp>
#include <Multicast.hpp>
#include <TCPReceiver.hpp>
#include <DeadNodesPurger.hpp>
//TODO #include <BluetoothReceiver.hpp>
#include <Executor.hpp>
#include <TCPSender.hpp>
#include <Observer.hpp>
#include <list>

class Terminal : public Observer
{

private:
	WiFiManager mWiFiManager;
	Multicast mMulticast;
	TCPReceiver mTCPReceiver;
	DeadNodesPurger mDeadNodesPurger;
	//TODO BluetoothReceiver mBluetoothReceiver;
	Executor* mExecutor;
	TCPSender mTCPSender;
	std::list<uint16_t> mConnectedNodes;

public:
	Terminal();

	void notify(const Event* event) override;

	void start();

private:
	static void task0(void* args);
	static void task1(void* args);
	static void task2(void* args);

};