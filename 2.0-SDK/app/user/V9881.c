#include "V9881.h"
#include "user_interface.h"
#include "osapi.h"
#include "os_type.h"
#include "mem.h"

extern u8 mqtt_id[11];
extern u8 mqtt_topic_send[16];

extern struct ip_info IP_Info;

extern u32 times;

int ICACHE_FLASH_ATTR  getBcd(uint8 hex)
{
	int h = hex / 16;
	int l = hex % 16;

	return h * 10 + l;
}

uint32 ICACHE_FLASH_ATTR  int2bcd(char *b, int offset)
{
	//b 是输入数组
	//offset是数据在数组中的偏移量
	//rate是倍率
	uint32 bcd = 0;

	int gw = getBcd(b[offset + 0]);
	int sw = getBcd(b[offset + 1]);
	int bw = getBcd(b[offset + 2]);
	int qw = getBcd(b[offset + 3]);


	bcd = qw * 100 * 100 * 100 + bw * 100 * 100 + sw * 100 + gw;
	return bcd;
}



void  ICACHE_FLASH_ATTR V9881_ReadData(V9881_Data *v9881_data, u8 *bufSource, u16 len)
{
	u8 *temp = (u8 *)os_zalloc(32);

	if (len == 36)
	{
		v9881_data->W = int2bcd(bufSource, offset_W);
		v9881_data->U = int2bcd(bufSource, offset_U);
		v9881_data->I= int2bcd(bufSource, offset_I);
		v9881_data->Hz = int2bcd(bufSource, offset_Hz);
		v9881_data->P = int2bcd(bufSource, offset_P);
		v9881_data->var = int2bcd(bufSource, offset_var);
		v9881_data->Va = int2bcd(bufSource, offset_Va);
		v9881_data->F = int2bcd(bufSource, offset_F);

		wifi_get_ip_info(0, &IP_Info);
		os_sprintf(temp, "%d.%d",(u8)((IP_Info.ip.addr) >> 16), (u8)((IP_Info.ip.addr) >> 24));

		os_sprintf(v9881_data->jsonString, 
			"{ \"ID\":\"%s\", \"U\":\"%d.%d\", \"I\":\"%d.%d%d%d%d\", \"P\":\"%d.%d\", \"W\":\"%d.%d%d\", \"F\":\"0.%d%d%d\",\"V\":\"%s\", \"T\":\"%d\",\"IP\":\"%d_%d_%s\" }",
			mqtt_id, 
			(v9881_data->U/ 10), (v9881_data->U / 1) % 10,
			(v9881_data->I / 10000), (v9881_data->I  / 1000) % 10, (v9881_data->I  / 100) % 10,(v9881_data->I  / 10) % 10,(v9881_data->I  / 1) % 10,
			(v9881_data->P / 10), (v9881_data->P / 1) % 10, 
			(v9881_data->W / 100),(v9881_data->W / 10) % 10, (v9881_data->W / 1)% 10, 
			(v9881_data->F / 100) % 10,(v9881_data->F / 10) % 10,(v9881_data->F / 1) % 10,
			VERSION,
			user_time_get(),
			times, wifi_station_get_rssi(), temp);
	}

	else
	{
		os_printf("长度不符\r\n");
	}

	os_free(temp);
}

