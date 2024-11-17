#include "timer.h"

#include <iomanip>
#include <sstream>

Timer::Timer(float total_time, const sf::Font& font, const sf::Vector2f& position)
    : total_time_(total_time), elapsed_time_(0.0f), is_running_(false), paused_time_(0.0f) {
    text_.setFont(font);
    text_.setCharacterSize(30);
    text_.setFillColor(sf::Color(31, 27, 10));
    text_.setPosition(position);
    UpdateDisplay();
}

void Timer::Start() {
    if (!is_running_) {
        clock_.restart(); 
        is_running_ = true;
    }
}

void Timer::Stop() {
    if (is_running_) {
        paused_time_ += clock_.getElapsedTime().asSeconds();  
        is_running_ = false;
    }
}

void Timer::Reset() {
    elapsed_time_ = 0.0f;
    paused_time_ = 0.0f;
    is_running_ = false;
    clock_.restart();
    UpdateDisplay();
}

void Timer::Update() {
    if (is_running_) {
        elapsed_time_ = paused_time_ + clock_.getElapsedTime().asSeconds();  
        UpdateDisplay();
    }
}

bool Timer::IsTimeUp() const {
    return elapsed_time_ >= total_time_;
}

void Timer::Draw(sf::RenderWindow& window) {
    window.draw(text_);
}

float Timer::GetRemainingTime() const {
    return std::max(0.0f, total_time_ - elapsed_time_);
}

void Timer::SetRemainingTime(float time) {
    total_time_ = time;
    elapsed_time_ = 0.0f;
    paused_time_ = 0.0f;
    is_running_ = false;
    clock_.restart();
    UpdateDisplay();

}

void Timer::UpdateDisplay() {
    float remaining_time = GetRemainingTime();
    int minutes = static_cast<int>(remaining_time) / 60;
    int seconds = static_cast<int>(remaining_time) % 60;

    std::ostringstream ss;
    ss << std::setfill('0') << std::setw(2) << minutes << ":" << std::setfill('0') << std::setw(2) << seconds;
    text_.setString(ss.str());
}
