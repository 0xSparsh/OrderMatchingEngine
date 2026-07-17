#pragma once

#include <cstdint>
#include <string>
#include <stdexcept>
#include <ostream>

// Number of decimal places carried by every price
// NASDAQ ITCH 5.0 uses 4
inline constexpr int kPriceDecimals = 4;

// Number of ticks in one whole unit of price
inline constexpr int64_t kTickScale = 10000; // must match kPriceDecimals

class Ticks
{
public:
constexpr Ticks() noexcept : _value(0) {}
explicit constexpr Ticks(int64_t value) noexcept : _value(value) {}

constexpr int64_t raw() const noexcept { return _value; }

// Exact integer comparison
friend constexpr bool operator==(Ticks a, Ticks b) noexcept { return a._value == b._value; }
friend constexpr bool operator!=(Ticks a, Ticks b) noexcept { return a._value != b._value; }
friend constexpr bool operator<(Ticks a, Ticks b) noexcept { return a._value < b._value; }
friend constexpr bool operator<=(Ticks a, Ticks b) noexcept { return a._value <= b._value; }
friend constexpr bool operator>(Ticks a, Ticks b) noexcept { return a._value > b._value; }
friend constexpr bool operator>=(Ticks a, Ticks b) noexcept { return a._value >= b._value; }

// Arithmetic
constexpr Ticks operator+(Ticks o) const noexcept { return Ticks(_value + o._value); }
constexpr Ticks operator-(Ticks o) const noexcept { return Ticks(_value - o._value); }

static constexpr Ticks zero() noexcept { return Ticks(0); }

private:
    int64_t _value;
};

// Convert a decimal place string (e.g. 123.45) into an exact integer tick count.
// No floating point rounding error.
Ticks parseTicks(const std::string& text);

// Convert an integer tick count back into a fixed-decimal string (e.g. 123.4500)
std::string formatTicks(Ticks ticks);

// Allow printing a Ticks value directly with std::cout (uses formatTicks).
std::ostream& operator<<(std::ostream& os, Ticks ticks);
