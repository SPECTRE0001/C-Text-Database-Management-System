#ifndef VIDEOGAME_H
#define VIDEOGAME_H
class videoGame {
private:
    int number;
    std::string title;
    int year;
    std::string system;
    std::string series;
    bool played;

public:
    videoGame(int n, const std::string& t, int y, const std::string& s, const std::string& ser, bool p)
        : number(n), title(t), year(y), system(s), series(ser), played(p) {}

    int getNumber() const { return number; }
    const std::string& getTitle() const { return title; }
    int getYear() const { return year; }
    const std::string& getSystem() const { return system; }
    const std::string& getSeries() const { return series; }
    bool isPlayed() const { return played; }

    void print() const {
        std::cout << "Number: " << number
                  << ", Title: " << title
                  << ", Year: " << year 
                  << ", System: " << system
                  << ", Series: " << series
                  << ", Played: " << (played ? "Yes" : "No") << std::endl;
    }
};
#endif
