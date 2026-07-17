#include "Ticks.h"
#include <cctype>
#include <sstream>

namespace
{
    int64_t pow10(int n)
    {
        int64_t result = 1;
        for (int i = 0; i < n; ++i) result *= 10;
        return result;
    }
}

Ticks parseTicks(const std::string& text)
{
    if (text.empty())
        throw std::invalid_argument("parseTicks: empty price string");

    size_t i = 0;
    bool negative = false;
    if (text[i] == '+' || text[i] == '-')
    {
        negative = (text[i] == '-');
        ++i;
    }

    int64_t whole = 0;
    bool sawDigit = false;
    while (i < text.size() && std::isdigit(static_cast<unsigned char>(text[i])))
    {
        whole = whole * 10 + (text[i] - '0');
        ++i;
        sawDigit = true;
    }

    int64_t frac = 0;
    if (i < text.size() && text[i] == '.')
    {
        ++i;
        int fracDigits = 0;
        while (i < text.size() && std::isdigit(static_cast<unsigned char>(text[i])))
        {
            if (fracDigits < kPriceDecimals)
            {
                frac = frac * 10 + (text[i] - '0');
                ++fracDigits;
            }
            // Extra digits beyond kPriceDecimals are silently truncated here.
            // A real exchange feed would instead reject a sub-tick price.
            ++i;
            sawDigit = true;
        }
        frac *= pow10(kPriceDecimals - fracDigits); // pad e.g. "1.5" -> 5000
    }

    if (!sawDigit || i != text.size())
        throw std::invalid_argument("parseTicks: malformed price '" + text + "'");

    int64_t value = whole * kTickScale + frac;
    if (negative) value = -value;

    return Ticks(value);
}

std::string formatTicks(Ticks ticks)
{
    int64_t value = ticks.raw();
    bool negative = value < 0;
    if (negative) value = -value;

    int64_t whole = value / kTickScale;
    int64_t frac  = value % kTickScale;

    std::string fracStr = std::to_string(frac);
    fracStr.insert(fracStr.begin(), kPriceDecimals - static_cast<int>(fracStr.size()), '0');

    std::ostringstream oss;
    if (negative) oss << '-';
    oss << whole << '.' << fracStr;
    return oss.str();
}

std::ostream& operator<<(std::ostream& os, Ticks ticks)
{
    return os << formatTicks(ticks);
}