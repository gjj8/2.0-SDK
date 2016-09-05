#ifndef _USER_CONFIG_H_
#define _USER_CONFIG_H_

#define CFG_HOLDER	0x00FF55A4	/* Change this value to load default configurations */
#define CFG_LOCATION	0x3C	/* Please don't change or if you know what you doing */
#define CLIENT_SSL_ENABLE

/*DEFAULT CONFIGURATIONS*/

#define VERSION "6"

#define MQTT_HOST			 "54.222.211.139" //or "mqtt.yourdomain.com"
#define MQTT_PORT			8888
#define MQTT_BUF_SIZE		1024
#define MQTT_KEEPALIVE		120	 /*second*/

#define MQTT_CLIENT_ID		"DVES_%08X"
#define MQTT_USER			"system"
#define MQTT_PASS			"manager"

#define NET_DOMAIN "gziot.zjucolourlife.com"
#define HTTP_PORT 8090


#define STA_SSID "ancaihua001"
#define STA_SSID2 "ancaihua002"

#define STA_PASS "ach123456789"
#define STA_TYPE AUTH_WPA2_PSK

#define MQTT_RECONNECT_TIMEOUT 	5	/*second*/

#define DEFAULT_SECURITY	0
#define QUEUE_BUFFER_SIZE		 		2048


#define LED1 GPIO_ID_PIN(4)
#define LED2 GPIO_ID_PIN(5)
#define LED3 GPIO_ID_PIN(13)


#define LED_ON(n) GPIO_OUTPUT_SET(n, 0)
#define LED_OFF(n) GPIO_OUTPUT_SET(n, 1)

#define PROTOCOL_NAMEv31	/*MQTT version 3.1 compatible with Mosquitto v0.15*/
//PROTOCOL_NAMEv311			/*MQTT version 3.11 compatible with https://eclipse.org/paho/clients/testing/*/
#endif
