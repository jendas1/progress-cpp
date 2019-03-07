#ifndef PROGRESSBAR_PROGRESSBAR_HPP
#define PROGRESSBAR_PROGRESSBAR_HPP

#include <chrono>
#include <iostream>

class ProgressBar {
private:
    unsigned int ticks = 0;
    int display_counter = 0;
    int skips_before_report = 1;

    const unsigned int total_ticks;
    const unsigned int bar_width;
    const char complete_char = '=';
    const char incomplete_char = ' ';
    const std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();

public:
    ProgressBar(unsigned int total, unsigned int width, char complete, char incomplete, int skips_before_report) :
    total_ticks {total}, bar_width {width}, complete_char {complete}, incomplete_char {incomplete}, skips_before_report(skips_before_report) {}

    ProgressBar(unsigned int total, unsigned int width) : total_ticks {total}, bar_width {width} {}

    unsigned int operator++() { return ++ticks; }

    void display()
    {
        display_counter++;
        if ((display_counter%skips_before_report) == 0) {
        float progress = (float) ticks / total_ticks;
        int pos = (int) (bar_width * progress);

        std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
        auto time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now-start_time).count();

        std::cerr << "[";

        for (int i = 0; i < bar_width; ++i) {
            if (i < pos) std::cerr << complete_char;
            else if (i == pos) std::cerr << ">";
            else std::cerr << incomplete_char;
        }
        std::cerr << "] " << int(progress * 100.0) << "% "
        << float(time_elapsed) / 1000.0 << "s\r";
        std::cerr.flush();
        }
    }

    void done()
    {
        display();
        std::cerr << std::endl;
    }
};

#endif //PROGRESSBAR_PROGRESSBAR_HPP
