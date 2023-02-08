import re


questions = {
    "Które z poniższych stwierdzeń jest prawdziwe dla architektury Harvardzkiej (AH)":
    "1. W AH mikroprocesor może jednocześnie pobrać rozkaz i daną \n2. AH charakteryzuje się rozdzieloną szyną danych i programu",
    "Które z poniższych stwierdzeń dotyczące pamięci danych i programu jest prawdziwe dla architektury Harvardzkiej (AH)":
    "1. W AH pamięć danych i programu może różnić się długością słowa \n2. W AH program nie może się sam modyfikować",
    "Które z poniższych stwierdzeń jest prawdziwe dla architektury von Neumana (AvN)":
    "1. AvN charakteryzuje się wspólną szyną danych i programu\n2. W AvN mikroprocesor nie może jednocześnie pobrać rozkaz i czegoś tam jeszcze",
    "Które z poniższych stwierdzeń dotyczące pamięci danych i programu jest prawdziwe dla architektury von Neumana (AvN)":
    "1. W AvN program może się sam modyfikować\n2. W AvN pamięć danych i programu nie może różnić się długością",
    "Mikrokontroler bywa zwany komputerem ... (wskaż najbardziej pasującą odpowiedź)":
    "jednoukładowym",
    "Mikrokontrolery PIC mają zestaw instrukcji":
    "RISC",
    "Które z poniższych stwierdzeń jest prawdziwe dla mikrokontrolerów PIC":
    "1. Instrukcje nie różnią się długością\n2. Szerokość szyny danych i rozkazów nie musi być taka sama",
    "Dane mikrokontrolerów PIC mają rozmiar":
    "8 bitów",
    "Dostęp do pinów wej/wyj na poziomie sprzętowym w mikrokontrolerze PIC realizowany jest za pomocą ...":
    "3 specjalnych rejestrów",
    "1. Do usypiania mikrokontrolerów PIC służy instrukcja 2. Po wybudzeniu mikrokontrolera program jest kontynuowany":
    "1. SLEEP\n2. Od kolejnej instrukcji po instrukcji usypiania",
    "Interfejs szeregowy który zawsze wymaga wymiany danych to":
    "1-wire",
    "Interfejs szeregowy synchroniczny nie wymagający zwiększenia ilości linii przy dołączeniu dodatkowych urządzeń to":
    "I2C",
    "Do realizacji najprostszej transmisji szeregowej za pomocą interfejsu RS232 wymagane są":
    "2 linie sygnałowe",
    "W interfejsie I2C do transmisji wykorzystywane są":
    "Linia zegarowa",
    "Intefejs I2C jest interfejsem":
    "Szeregowym synchronicznym",
    "W interfejsie I2C transmisja jest typu":
    "Half-duplex",
    "W interfejsie SPI do transmisji wykorzystywane są":
    "1. 3 linie sygnałowe\n2. Linia wyboru urządzenia SLAVE",
    "Intefejs SPI jest interfejsem":
    "Szeregowym synchronicznym",
    "W interfejsie SPI transmisja jest typu:":
    "Full-duplex",
    "Pamięć EEPROM jest rodzajem pamięci":
    "Nieulotnej o ograniczonej liczbie zapisów i kasowań",
    "Mikrokontrolery AVR mają zestaw instrukcji":
    "RISC",
    "1. Do usypiania mikrokontrolerów AVR służy instrukcja 2. Po wybudzeniu mikrokontrolera program jest kontynuowany":
    "1. sleep()\n2. od kolej instrukcji po instrukcji usypiania",
    "Źródłem sygnału RESET w mikrokontrolerze AVR może być":
    "1. Układ kontroli zasilania\n2. Sygnał generowany przez układ Watchdoga\n3. Układ startu po włączeniu zasilania\n4. Zewnętrzny sygnał podany do pinu o nazwie reset",
    "Dostęp do pinów wej/wyj na poziomie sprzętowym w mikrokontrolerze AVR realizowany jest za pomocą":
    "3 specjalnych rejestrów",
    "W mikrokontrolerze AVR procedury (wektory) obsługi przerwań domyślnie znajdują się w pamięci FLASH począwszy od adresu":
    "0x0000",
    "Dla 10-bitowego przetwornika analogowo-cyfrowego mikrokontrolera AVR, jako źródło napięcia referencyjnego wybrano napięcie Maksymalna wartość napięcia zmierzonego przez ten przetwornik wynosi":
    "AVcc",
    "1. Licznik mikrokontrolera AVR w trybie CTC zlicza od 0 do wartości 2. Po doliczeniu do niej":
    "1. zadanej\n2. liczy od 0",
    "1. Dla interfejsu USB transfer masowy danych ma charakter 2. W tego typu transmisji powtórne przesłanie uszkodzonych pakietów danych jest":
    "1. asynchroniczny\n2. zapewnione",
    "W interfejsie 1-wire transmisja odbywa się za pomocą tzw. slotów (szczelin czasowych) w których najważniejsze jest":
    "Zachowanie reżimu czasowego dla stanów logicznych",
    "Specjalny program tzw. BOOTLOADER umieszczony w pamięci mikrokontrolera pozwala na":
    "1. Uruchomienie programu głównego na mikrokontrolerze\n2. Wgranie oprogramowania na mikrokontroler za pomocą dowolnego interfejsu dostępnego na miktrokontrolerze\n3. Aktualizację oprogramowania na mikrokontroler za pomocą dowolnego interfejsu dostępnego na mikrokontrolerze",
    "Wymień trzy interfejsy komunikacji szeregowej stosowanej w mikrokontrolerach":
    "1. I2C\n2. USART\n3. 1-wire",
    "Czy mikrokontrolery PIC16Fxxx posiadają cechy load-store ?":
    "Nie",
    "Wymień trzy dodatkowe bloki które wraz z mikroprocesorem tworzą mikrokontroler":
    "1. CPU\n2. Pamięć RAM\n3. Pamięć nieulotna programu",
    "Jaką architekturę pamięci ma rodzina mikrokontrolerów PIC ?":
    "Harvardzką",
    "Czy instrukcje mikrokontrolerów PIC różnią się długością ?":
    "Nie",
    "Czy szerokość szyny rozkazów jest taka sama jak szyny danych w mikrokontrolerach PIC ?":
    "Nie",
    "Wymień rodzaje szczelin czasowych dla komunikacji za pomocą magistrali 1-wire":
    "1. Inicjująca\n2. Zapisu \"1\"\n3. Zapisu \"0\"\n4. Odczytu",
    "Które z poniższych zdań jest prawdziwe dla standardu USB w przypadku transferu izochronicznego danych ?":
    "1. Rezerwowany jest fragment pasma magistrali w ściśle określonych momentach czasu\n2. Trasmisja danych, które muszą być dostarczone w czasie rzeczywistym z określoną częstotliwością\n3. Błędy transmisji nie są korygowane.\n4. Pierwszeństwo przed transmisją asynchroniczną",
    "Które z poniższych zdań jest prawdziwe dla standardu USB w przypadku transferu masowego danych ?":
    "1. Ma charakter asynchroniczny\n2. Gwarantuje stałą prędkość transmisji danych\n3. Nie zapewnia powtarzania pakietów uszkodzonych\n4. Nie gwarantuje limitu czasu transmisji",
    "Architektura procesora sygnałowego zawiera przesuwnik, w skład którego wchodzą rejestry zawierające...":
    "32-bitowy rejestr wyjściowy, 16-bitowy rejestr wejściowy SI, 8-bitowy rejestr SE, 8-bitowy rejestr SB, 32-bitowy rejestr SR",
    "Architektura procesora sygnałowego zawiera generatory adresowe, w skład których wchodzą rejestry zawierające...":
    "I – rejestry indeksowe, M – rejestry modyfikacji, L – rejestry długości",
    "Wymień trzy różnice pomiędzy procesorem sygnałowym a standardowym procesorem":
    "- równoległe mnożenie z akumulacją wykonywane w jednym cyklu\n- generatory adresu ze specjalnymi trybami\n- wydajny zestaw instrukcji z jednocyklowymi równoległymi operacjami matematycznymi i przesłań w pamięci oraz sprawną realizacją pętli.",
    "Które z poniższych zdań, mówiące o standardzie Bluetooth jest prawdziwe ?":
    "1. Układy podrzędne slave są głupie - robią tylko to, co każe im wezeł główny master\n2. Węzeł główny kontroluje zegar i przydziela szczeliny czasowe urządzeniom",
    "Ułóż w kolejności od najwyższej do najniższej warstwy protokołu Bluetooth":
    "1. aplikacji 2. pośrednia 3. łącza danych 4. fizyczna",
    "Wymień cztery narzędzia ( programy ) stosowane do testowania systemów wbudowanych":
    "- analizator logiczny\n- oscyloskop- ICE (In-Circuit Emulator)\n- JTAG, \n- wbudowany program śledzący",
    "W sieciach ATM, jako medium trasmisyjne stosuje się":
    "1. Kabel koncentryczny\n2. Fale radiowe\n3. Światłowód",
    "W którym z poniższych trybów może pracować procesor w architekturze MIPS":
    "1. Jądra\n2. Użytkownika",
    "Zaznacz określenie najlepiej określające mikroprocesor w przeciwieństwie do procesora, komputera, automatu, pozytywki":
    "Jeden układ scalony (ewentualnie programowalny, bo się ludzie kłócą w opracowaniu)",
    "Architektura Harvardzka charakteryzuje się":
    "Rozdzielczą szyną danych i programu",
    "W której architekturze mikroprocesor może jednocześnie pobierać rozkaz i dane z pamięci?":
    "Harvardzkiej",
    "Mikroprocesor o zredukowanej liście instrukcji to":
    "RISC",
    "Czy mikroprocesory CISC wykonują wszystkie instrukcje w takim samym czasie":
    "Nie",
    "Jakie instrukcje niweczą zalety przetwarzania potokowego":
    "Przerwania oraz skoki (int, goto) (różna wersje w opracowaniach)",
    "Wymień dodatkowe bloki, które wraz z mikroprocesorem tworzą mikrokontroler":
    "- pamięć programu\n- pamięć danych\n- interfejs wejścia/wyjścia",
    "Słowo danych mikrokontrolerów PIC ma długość":
    "8 bitów",
    "Jaka instrukcja wprowadza mikrokontroler w tryb oszczędzania energii":
    "sleep",
    "Mikrokontrolery ATMega128 mają zestaw instrukcji":
    "RISC",
    "Wynik przetwarzania napięcia dla wejścia niesymetrycznego 10 bitowego przetwornika ADC wynosi 256 natomiast napięcie odniesienia ma wartość 5V Oznacza to że zmierzono napięcie":
    "Vin = (ADC*Vref)/2^n gdzie n bitów",
    "Układ slave podłączony do magistrali I-wire na szczelinę inicjującą układu master odpowie stanem":
    "0",
    "W systemie Bluetooth w pikosieci mogą znajdować się maksymalnie":
    "7 aktywnych węzeł/węzłów typu slave, ponieważ występuje 3-bitowa adresacja (1 master + 7 slave)",
    "Do jednego kontrolera USB może być podłączonych maksymalnie":
    "127, ponieważ 7-bitowa adresacja urządzeń",
    "Wymień 4 stany w których może znajdować się proces":
    "1. nowy 2. wykonywany 3. oczekujący 4. gotowy",
    "Wymień cztery rodzaje obiektów wykorzystywanych w metodzie projektowania systemów HRT-HOOD":
    "1. pasywne 2. aktywne 3. chronione 4. cykliczne 5. sporadyczne (wiem że miały być 4, ale w opracowaniu było 5)",
    "Który z interfejsów szeregowych wymaga zawsze wymiany danych":
    "SPI",
    "Czy czterordzeniowy mikroprocesor jest tak samo wydajny jak cztery jednordzeniowe":
    "Nie",
    "W jakim typie klocków łatwiej jest zaimplementować przetwarzanie potokowe":
    "RISC (np. DSP)",
    "Jakie są wspólne bloki w wielowątkowości":
    "ALU",
    "W przetwarzaniu programu przez PLC występują pętle":
    "Tak",
    "Na wejściu 10-bitowego niesymetrycznego pojawiła się wartość 512 przy napięciu odniesienia 5V. Jaką wartość napięcia zmierzono":
    "2,5V ADC=(VIN*1024)/VREF",
    "Architektura Harvardzka charakteryzuje się ... szyną danych i programu":
    "Rozdzielną",
    "Na wejściu 10-bitowego niesymetrycznego pojawiła się wartość 256 przy napięciu odniesienia 5V. Jaką wartość napięcia zmierzono":
    "2,5V ADC=(VIN*1024)/VREF",
    "Układ slave podłączony do magistrali 1-wire na szczelinie inicjującej układu master odpowie stanem":
    "0",
    "Do projetkowania jakich systemów wykorzystuje się metodę HRT-HOOD":
    "Systemów silnie uwarunkowanych czasowo",
    "Jakie są konsekwencje wykorzystania pamięci SRAM do konfiguracji układów FPGA":
    "SRAM – Bazuje na technologii pamięci statycznej, dlatego przy braku zasilania traci swoją konfigurację"
}

if __name__ == "__main__":
    while True:
        question_input_string = input("==========\nPodaj słowa kluczowe pytania: ")
        key_words = wordList = re.sub("[^\w]", " ",  question_input_string).split()
        for question, answers in questions.items():
            question_matches = True
            for key_word in key_words:
                if not key_word.lower() in question.lower():
                    question_matches = False
                    break
            if question_matches:
                print(f"{question}\nOdpowiedzi:\n{answers}\n")