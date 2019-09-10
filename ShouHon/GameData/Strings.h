#pragma once

#include "../FlashString.h"

#if defined(CHOICE_TEST)

const char String000[] PROGMEM = "Choose your weapon";
const char String001[] PROGMEM = "Mushy Peas";
const char String002[] PROGMEM = "Green Spaghetti";
const char String003[] PROGMEM = "A ladle";
const char String004[] PROGMEM = "Are you sure you want Mushy Peas?";
const char String005[] PROGMEM = "Green Spaghetti... the best choice!";
const char String006[] PROGMEM = "A ladle? It'll do!";
const char String007[] PROGMEM = "An impossible choice!!!";

FlashString const Strings[] PROGMEM =
{
	AsFlashString(String000),
	AsFlashString(String001),
	AsFlashString(String002),
	AsFlashString(String003),
	AsFlashString(String004),
	AsFlashString(String005),
	AsFlashString(String006),
	AsFlashString(String007),
};

#elif defined(TIMER_TEST)

const char String000[] PROGMEM = "This is a timer test";
const char String001[] PROGMEM = "The timer works";
const char String002[] PROGMEM = "The end.";

FlashString const Strings[] PROGMEM =
{
	AsFlashString(String000),
	AsFlashString(String001),
	AsFlashString(String002),
};

#elif defined(IMAGE_TEST)

const char String000[] PROGMEM = "Hello World!";
const char String001[] PROGMEM = "Look at this image.";
const char String002[] PROGMEM = "Now look at this image.";
const char String003[] PROGMEM = "Multiple images.";
const char String004[] PROGMEM = "This was a test.";

FlashString const Strings[] PROGMEM =
{
	AsFlashString(String000),
	AsFlashString(String001),
	AsFlashString(String002),
	AsFlashString(String003),
	AsFlashString(String004),
};

#elif defined(LONG_TEST)

const char String000[] PROGMEM = "Hello World!";
const char String001[] PROGMEM = "The end.";
const char String002[] PROGMEM = "You have ";
const char String003[] PROGMEM = " lives remaining";
const char String004[] PROGMEM = ", you fool!";
const char String005[] PROGMEM = "I am the great eye.";
const char String006[] PROGMEM = "I am going to\ntell you a story.";
const char String007[] PROGMEM = "Once upon a time,";
const char String008[] PROGMEM = "there was\na boy called Tim.";
const char String009[] PROGMEM = "Tim was an idiot...";

FlashString const Strings[] PROGMEM =
{
	AsFlashString(String000),
	AsFlashString(String001),
	AsFlashString(String002),
	AsFlashString(String003),
	AsFlashString(String004),
	AsFlashString(String005),
	AsFlashString(String006),
	AsFlashString(String007),
	AsFlashString(String008),
	AsFlashString(String009),
};

#endif