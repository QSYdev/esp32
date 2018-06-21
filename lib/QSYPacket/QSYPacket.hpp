#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define QSY_SSID						"ESP32"
#define QSY_PASSWORD					"123456789"
#define QSY_BLUETOOTH					"ESP32"
#define QSY_SERVICE_UUID				"4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define QSY_CHARACTERISTIC_UUID			"beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define QSY_MAX_CONNECTIONS				8
#define QSY_PACKET_SIZE					16
#define QSY_MULTICAST_ADDRESS			{224, 0, 0, 12}
#define QSY_MULTICAST_PORT				3000
#define QSY_TCP_SERVER_PORT				3000
#define QSY_MAX_ALLOWED_TIME			750
#define QSY_MAX_TRIES					5
#define QSY_DEAD_NODES_PURGER_PERIOD	1125

class Color
{

private:
	const uint8_t mRed;
	const uint8_t mGreen;
	const uint8_t mBlue;

public:
	inline color()	{}
	inline color(uint8_t red, uint8_t green, uint8_t blue)	:mRed(red), mGreen(green), mBlue(blue)	{}

} __attribute__ ((packed));

class QSY_PACKET_SIZE
{

private:
	char signature[3];
	uint8_t type;
	uint16_t id;
	uint16_t color;
	uint32_t delay;
	uint16_t step;
	uint16_t config;

public:
	enum class PacketType
	{
		hello = 0,
		command = 1,
		touche = 2,
		keepalive = 3
	};

public:

	QsyPacket();
	
	bool isValid();

	enum PacketType getType();
	uint16_t getId();
	Color getColor();
	uint32_t getDelay();
	uint16_t getStep();

	void setType(enum PacketType type);
	void setId(uint16_t id);
	void setColor()

} __attribute__ ((packed));

struct qsy_packet {
	char privated[QSY_PACKET_SIZE];
	
	inline qsy_packet()
	{
	}
	
	inline qsy_packet(const qsy_packet* packet)
	{
		memcpy(privated, packet->privated, QSY_PACKET_SIZE);
	}
} __attribute__ ((packed));

enum packet_type {
	hello = 0,
	command = 1,
	touche = 2,
	keepalive = 3
};

struct color {
	uint8_t red;
	uint8_t green;
	uint8_t blue;

	inline color()	{}
	inline color(uint8_t r, uint8_t g, uint8_t b)	:red(r), green(g), blue(b)	{}
} __attribute__ ((packed));

void packet_init(struct qsy_packet* packet);
bool packet_is_valid(const struct qsy_packet* packet);

enum packet_type packet_get_type(const struct qsy_packet* packet);
uint16_t packet_get_id(const struct qsy_packet* packet);
struct color packet_get_color(const struct qsy_packet* packet);
uint32_t packet_get_delay(const struct qsy_packet* packet);
uint16_t packet_get_step(const struct qsy_packet* packet);

void packet_set_type(struct qsy_packet* packet, enum packet_type type);
void packet_set_id(struct qsy_packet* packet, uint16_t id);
void packet_set_color(struct qsy_packet* packet, struct color c);
void packet_set_delay(struct qsy_packet* packet, uint32_t delay);
void packet_set_step(struct qsy_packet* packet, uint16_t step);