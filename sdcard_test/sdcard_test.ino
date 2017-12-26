/*
SD card test
This example shows how use the utility libraries on which the'
SD library is based in order to get info about your SD card.
Very useful for testing a card when you're not sure whether its working or not.

The circuit:
* SD card attached to SPI bus as follows:
** MOSI - pin 11 on Arduino Uno/Duemilanove/Diecimila
** MISO - pin 12 on Arduino Uno/Duemilanove/Diecimila
** CLK - pin 13 on Arduino Uno/Duemilanove/Diecimila
** CS - depends on your SD card shield or module.
Pin 4 used here for consistency with other Arduino examples
created  28 Mar 2011
by Limor Fried
modified 9 Apr 2012
by Tom Igoe
*/

// SD카드를 사용하기 위한 SD라이브러리를 불러온다.
#include <SD.h>

Sd2Card card;
SdVolume volume;
SdFile root;

const int chipSelect = 4;

void setup() {
	// Open serial communications and wait for port to open:
	Serial.begin(9600);

	Serial.print("\nInitializing SD card...");

	// SD카드를 사용하기 위해서는 꼭 10번 핀을 출력모드로 설정해야 한다.
	// 아두이노 mega를 쓰시는분은 53번핀으로 바꿔준다.
	pinMode(10, OUTPUT);

	// SD카드가 인식이 안되면 오류 메시지를 출력
	if (!card.init(SPI_HALF_SPEED, chipSelect)) {
		Serial.println("initialization failed. Things to check:");
		Serial.println("* is a card is inserted?");
		Serial.println("* Is your wiring correct?");
		Serial.println("* did you change the chipSelect pin to match your shield or module?");
		return;

			// SD카드가 인식 됬을 경우 확인 메시지를 출력
	}
	else {
		Serial.println("Wiring is correct and a card is present.");
	}

	// SD카드의 종류를 출력한다.
	Serial.print("\nCard type: ");
	switch (card.type()) {
	case SD_CARD_TYPE_SD1:
		Serial.println("SD1");
		break;
	case SD_CARD_TYPE_SD2:
		Serial.println("SD2");
		break;
	case SD_CARD_TYPE_SDHC:
		Serial.println("SDHC");
		break;
	default:
		Serial.println("Unknown");
	}

	if (!volume.init(card)) {
		Serial.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
		return;
	}

	// SD카드의 voilume type과 size 를 출력한다.
	uint32_t volumesize;
	Serial.print("\nVolume type is FAT");
	Serial.println(volume.fatType(), DEC);
	Serial.println();

	volumesize = volume.blocksPerCluster();
	volumesize *= volume.clusterCount();
	volumesize *= 512;
	Serial.print("Volume size (bytes): ");
	Serial.println(volumesize);
	Serial.print("Volume size (Kbytes): ");
	volumesize /= 1024;
	Serial.println(volumesize);
	Serial.print("Volume size (Mbytes): ");
	volumesize /= 1024;
	Serial.println(volumesize);

	Serial.println("\nFiles found on the card (name, date and size in bytes): ");
	root.openRoot(volume);

	// SD카드 안에 있는 파일들의 이름, 날짜, 크기를 출력한다.
	root.ls(LS_R | LS_DATE | LS_SIZE);
}

void loop()
{

  /* add main program code here */

}
