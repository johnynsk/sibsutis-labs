#include <iostream>
#include "hexsummator.hpp"
#include <cstdlib>
#include <string>
#include <stdexcept>

class assertionException : std::exception {};
int assertions;
using namespace HexSummator;
void assertLong(long long actual, long long expected, std::string message)
{
    assertions++;
    if (actual != expected) {
        std::cout << "x";
        throw std::runtime_error(message.append(". Actual: ").append(std::to_string(actual)).append("; Expected: ").append(std::to_string(expected)));
    }

    std::cout << ".";
}

void assertString(std::string actual, std::string expected, std::string message)
{
    assertions++;
    if (actual != expected) {
        std::cout << "x";
        throw std::runtime_error(message.append(". Actual: ").append(actual).append("; Expected: ").append(expected));
    }

    std::cout << ".";
}

void assertTrue(bool actual, std::string message)
{
    assertions++;
    if (actual != true) {
        std::cout << "x";
        throw std::runtime_error(message.append(". Actual: false; Expected: true"));
    }

    std::cout << ".";
}

void assertFalse(bool actual, std::string message)
{
    assertions++;
    if (actual != false) {
        std::cout << "x";
        throw std::runtime_error(message.append(". Actual: true; Expected: false"));
    }

    std::cout << ".";
}


int testDecHex()
{
    std::cout << "DecHex test: ";
    assertions = 0;

    try {
        assertString(dechex(0), "0", "zero test failed");
        assertString(dechex(255), "FF", "255 test failed");
        assertString(dechex(170), "AA", "AA test failed");
        assertString(dechex(-5), "-5", "subzero test failed");
    } catch (std::runtime_error &exception) {
        std::cout << "\n";
        std::cerr << "Assertion failed (run " << assertions <<"): " << exception.what() << "\n";
        return 1;
    }

    std::cout << "\n";
    std::cout << "Test passed (run " << assertions << ").\n";
    return 0;
}

int testSum()
{
    std::cout << "Sum test: ";
    assertions = 0;

    try {
        assertString(add("0", "0"), "0", "zero test");
        assertString(add("0", "1"), "1", "one test");
        assertString(add("0", "-1"), "-1", "minus one test");
        assertString(add("-AA", "-23"), "-CD", "sum both minus test");
        assertString(add("-AA", "23"), "-87", "sum A below zero");
        assertString(add("19", "1F"), "38", "sum both positive");
        assertString(add("19", "-1F"), "-6", "positive minus");
    } catch (std::runtime_error &exception) {
        std::cout << "\n";
        std::cerr << "Assertion failed (run " << assertions <<"): " << exception.what() << "\n";
        return 1;
    }

    std::cout << "\n";
    std::cout << "Test passed (run " << assertions << ").\n";
    return 0;
}

int testHexDec()
{
    std::cout << "HexDec test: ";
    assertions = 0;

    try {
        assertLong(hexdec("0"), 0, "zero test failed");
        assertLong(hexdec("FF"), 255, "255 test failed");
        assertLong(hexdec("-FF"), -255, "subzero test failed");
        assertLong(hexdec("00"), 0, "double 00 test failed");
    } catch (std::runtime_error &exception) {
        std::cout << "\n";
        std::cerr << "Assertion failed (run " << assertions <<"): " << exception.what() << "\n";
        return 1;
    }

    std::cout << "\n";
    std::cout << "Test passed (run " << assertions << ").\n";
    return 0;
}

int testValidator()
{
    std::cout << "Validator test: ";
    assertions = 0;

    try {
        assertTrue(validate("0"), "zero test");
        assertTrue(validate("-1"), "sub zero test");
        assertFalse(validate("--1"), "double minus test");
        assertTrue(validate("0123456789"), "numbers test");
        assertTrue(validate("ABCDEF"), "HEX test");
        assertFalse(validate("12-3"), "minus in expression");
        assertFalse(validate("EWQR"), "unknown range");
    } catch (std::runtime_error &exception) {
        std::cout << "\n";
        std::cerr << "Assertion failed (run " << assertions <<"): " << exception.what() << "\n";
        return 1;
    }

    std::cout << "\n";
    std::cout << "Test passed (run " << assertions << ").\n";
    return 0;
}

int main(int argc, char **argv)
{
    int r = 0;
    r += testHexDec();
    r += testDecHex();
    r += testValidator();
    r += testSum();
    return r;
}
