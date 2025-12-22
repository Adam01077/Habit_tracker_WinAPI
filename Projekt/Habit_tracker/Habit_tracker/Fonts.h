#pragma once


#pragma once


HFONT Font1 = CreateFont(
	50,                  // wysokoœæ czcionki (rozmiar)
	0,                   // szerokoœæ (0 = automatyczna)
	0,                   // k¹t nachylenia tekstu
	0,                   // k¹t nachylenia znaków
	FW_BOLD,             // gruboœæ (FW_NORMAL, FW_BOLD, FW_THIN...)
	TRUE,               // kursywa (TRUE/FALSE)
	FALSE,               // podkreœlenie
	FALSE,               // przekreœlenie
	DEFAULT_CHARSET,     // zestaw znaków
	OUT_DEFAULT_PRECIS,  // precyzja wyjœcia
	CLIP_DEFAULT_PRECIS, // precyzja przycinania
	DEFAULT_QUALITY,     // jakoœæ
	DEFAULT_PITCH,       // pitch i rodzina
	TEXT("MainMenuFont")        // nazwa czcionki
);
	
HFONT Font2 = CreateFont(
	35,                  // wysokoœæ czcionki (rozmiar)
	0,                   // szerokoœæ (0 = automatyczna)
	0,                   // k¹t nachylenia tekstu
	0,                   // k¹t nachylenia znaków
	FW_BOLD,             // gruboœæ (FW_NORMAL, FW_BOLD, FW_THIN...)
	TRUE,               // kursywa (TRUE/FALSE)
	FALSE,               // podkreœlenie
	FALSE,               // przekreœlenie
	DEFAULT_CHARSET,     // zestaw znaków
	OUT_DEFAULT_PRECIS,  // precyzja wyjœcia
	CLIP_DEFAULT_PRECIS, // precyzja przycinania
	DEFAULT_QUALITY,     // jakoœæ
	DEFAULT_PITCH,       // pitch i rodzina
	TEXT("")        // nazwa czcionki
);