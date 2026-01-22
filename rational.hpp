#pragma once
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <vector>

// rational number class, represents a number as p / q
// can be created with either just numerator, or numerator and denominator
class rational {
    int numerator;
    int denominator;
    void simplify() {
        int greatest_div = std::gcd(numerator, denominator);
        numerator /= greatest_div;
        denominator /= greatest_div;

        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

  public:
    rational() : numerator(0), denominator(1) {};
    rational(int numer) : numerator(numer), denominator(1) {};
    rational(int numer, int denom) : numerator(numer), denominator(denom) {
        if (denom == 0) {
            throw std::invalid_argument("denominator cannot be 0");
        }
        simplify();
    };

    // spaceship to generate inequalities etc.
    auto operator<=>(const rational &rhs) const {
        int common_denom = std::lcm(denominator, rhs.denominator);
        int l_multiplier = common_denom / denominator;
        int r_multiplier = common_denom / rhs.denominator;
        int l_val = numerator * l_multiplier;
        int r_val = rhs.numerator * r_multiplier;
        return l_val <=> r_val;
    }

    // use default equality operator
    bool operator==(const rational &rhs) const = default;

    // output stream operator to print
    friend std::ostream &operator<<(std::ostream &output, const rational &num) {
        output << num.numerator;
        if (num.denominator != 1) {
            output << "/" << num.denominator;
        }
        return output;
    }

    // input with x/y pattern
    friend std::istream &operator>>(std::istream &input, rational &num) {
        int numer;
        int denom = 1;
        input >> numer;

        if (input.peek() == '/') {
            input.ignore();
            input >> denom;
            if (denom == 0) {
                input.setstate(std::ios::failbit);
                return input;
            }
        }

        num.numerator = numer;
        num.denominator = denom;
        num.simplify();
        return input;
    }

    // output to double
    double to_double() const { return static_cast<double>(numerator) / static_cast<double>(denominator); }

    // negation operation
    rational operator-() const { return rational{-numerator, denominator}; }

    // basic operators with other rational types
    rational &operator-=(const rational &rhs) {
        int common_denom = std::lcm(denominator, rhs.denominator);
        int l_multiplier = common_denom / denominator;
        int r_multiplier = common_denom / rhs.denominator;

        numerator = (numerator * l_multiplier) - (rhs.numerator * r_multiplier);
        denominator = common_denom;
        simplify();
        return *this;
    }

    rational operator-(const rational &rhs) const {
        rational result = *this;
        result -= rhs;
        return result;
    }

    rational &operator+=(const rational &rhs) {
        int common_denom = std::lcm(denominator, rhs.denominator);
        int l_multiplier = common_denom / denominator;
        int r_multiplier = common_denom / rhs.denominator;

        numerator = (numerator * l_multiplier) + (rhs.numerator * r_multiplier);
        denominator = common_denom;
        simplify();
        return *this;
    }

    rational operator+(const rational &rhs) const {
        rational result = *this;
        result += rhs;
        return result;
    }

    rational &operator*=(const rational &rhs) {
        numerator *= rhs.numerator;
        denominator *= rhs.denominator;
        simplify();
        return *this;
    }

    rational operator*(const rational &rhs) const {
        rational result = *this;
        result *= rhs;
        return result;
    }

    rational &operator/=(const rational &rhs) {
        if (rhs.numerator == 0) {
            throw std::invalid_argument("Divison by 0");
        }
        numerator *= rhs.denominator;
        denominator *= rhs.numerator;
        simplify();
        return *this;
    }

    rational operator/(const rational &rhs) const {
        rational result = *this;
        result /= rhs;
        return result;
    }

    // integer operators
    rational &operator+=(int rhs) {
        numerator += rhs * denominator;
        simplify();
        return *this;
    }

    rational operator+(int rhs) const {
        rational result = *this;
        result += rhs;
        return result;
    }

    rational &operator-=(int rhs) {
        numerator -= rhs * denominator;
        simplify();
        return *this;
    }

    rational operator-(int rhs) const {
        rational result = *this;
        result -= rhs;
        return result;
    }

    rational &operator*=(int rhs) {
        numerator *= rhs;
        simplify();
        return *this;
    }

    rational operator*(int rhs) const {
        rational result = *this;
        result *= rhs;
        return result;
    }

    rational &operator/=(int rhs) {
        if (rhs == 0) {
            throw std::invalid_argument("Divison by 0");
        }
        denominator *= rhs;
        simplify();
        return *this;
    }

    rational operator/(int rhs) const {
        rational result = *this;
        result /= rhs;
        return result;
    }
};

// vector operators (element-wise, assumes same size)
inline std::vector<rational> &operator+=(std::vector<rational> &lhs, const std::vector<rational> &rhs) {
    for (size_t i = 0; i < lhs.size(); i++) {
        lhs[i] += rhs[i];
    }
    return lhs;
}

inline std::vector<rational> &operator-=(std::vector<rational> &lhs, const std::vector<rational> &rhs) {
    for (size_t i = 0; i < lhs.size(); i++) {
        lhs[i] -= rhs[i];
    }
    return lhs;
}

inline std::vector<rational> &operator*=(std::vector<rational> &lhs, const std::vector<rational> &rhs) {
    for (size_t i = 0; i < lhs.size(); i++) {
        lhs[i] *= rhs[i];
    }
    return lhs;
}

inline std::vector<rational> &operator/=(std::vector<rational> &lhs, const std::vector<rational> &rhs) {
    for (size_t i = 0; i < lhs.size(); i++) {
        lhs[i] /= rhs[i];
    }
    return lhs;
}

// vector scalar operators
inline std::vector<rational> &operator*=(std::vector<rational> &lhs, int rhs) {
    for (size_t i = 0; i < lhs.size(); i++) {
        lhs[i] *= rhs;
    }
    return lhs;
}

inline std::vector<rational> &operator/=(std::vector<rational> &lhs, int rhs) {
    for (size_t i = 0; i < lhs.size(); i++) {
        lhs[i] /= rhs;
    }
    return lhs;
}

inline std::vector<rational> &operator*=(std::vector<rational> &lhs, const rational &rhs) {
    for (size_t i = 0; i < lhs.size(); i++) {
        lhs[i] *= rhs;
    }
    return lhs;
}

inline std::vector<rational> &operator/=(std::vector<rational> &lhs, const rational &rhs) {
    for (size_t i = 0; i < lhs.size(); i++) {
        lhs[i] /= rhs;
    }
    return lhs;
}

inline std::vector<rational> operator*(std::vector<rational> lhs, int rhs) {
    lhs *= rhs;
    return lhs;
}

inline std::vector<rational> operator/(std::vector<rational> lhs, int rhs) {
    lhs /= rhs;
    return lhs;
}

inline std::vector<rational> operator*(std::vector<rational> lhs, const rational &rhs) {
    lhs *= rhs;
    return lhs;
}

inline std::vector<rational> operator/(std::vector<rational> lhs, const rational &rhs) {
    lhs /= rhs;
    return lhs;
}
