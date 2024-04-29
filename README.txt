*******************************************************
Projekt 3 - Hubert Kowalski, Igor Kowalczyk
*******************************************************

Potrzebne Programy:
- GnuPlot - dla biblioteki matplotplusplus i uruchamiania bibliotek
- CMake - do kompilacji projektu
- Python 3.12 - obsługa Pythona


*************** KOMPILACJA ***************
W folderze build:
-> cmake ..
-> cmake --build .

*************** URUCHAMIANIE ***************
W folderze build/Debug:
-> Python
-> import projekt3
-> projekt3."komenda z KOMENDY"

*************** KOMENDY ***************
-> sin(), cos(), pilo(), prostokat() - w środku nawiasu podajemy częstotliwość np. 5
{
    sin() -> wykres sinusa
    cos() -> wykres cosinusa
    pilo() -> wykres piłokształtny
    prostokat() -> wykres przebiegu prostokątnego
}
-> show_audio() - pokazuje przebieg sygnału pliku dźwiękowego - "test-audio.wav", znajdującego się w pliku z biblioteką

-> DFT(), IDFT(), DFT_IDFT() -> Odwrotne transformacje Fouriera , z pliku dźwiękowego - "test-audio.wav", znajdującego się w pliku z biblioteką
{
    DFT() -> Dyretna Transformacja Fouriera
    IDFT() -> Odwrotna Transformacja Fouriera
    DFT_IDFT() -> Przekształca plik audio na DFT, a potem na IDFT, dzięki czemu uzyskamy ten sam sygnał, 
                    jak oryginalny (pokazuje poprawność danych algorytmów)
}

-> remove_high_freq() -> Usuwanie wysokich częstotliwości za pomocą DFT i IDFT,
                            pokazuje przebieg  zmodyfikowanego sygnału pliku dźwiękowego - "test-audio.wav", 
                            znajdującego się w pliku z biblioteką

**************** IMAGE_TESTS ****************
-> folder IMAGE_TESTS zawiera zrzuty ekranu funkcji remove_high_freq(), tzn.: Wykres oryginalnego przebiegu audio, oraz zmodyfikowanego