#include <iostream>
#include <climits>
#include "bigint.hpp"

void print_test_result(const std::string& test_name, bool passed) {
    std::cout << "  " << (passed ? "✅" : "❌") << " " << test_name;
    if (!passed) std::cout << " [FAILED]";
    std::cout << std::endl;
}

void print_value_test(const std::string& description, const std::string& expected, const std::string& actual) {
    bool passed = (expected == actual);
    std::cout << "  " << (passed ? "✅" : "❌") << " " << description;
    std::cout << " → Expected: " << expected << ", Got: " << actual;
    if (!passed) std::cout << " [FAILED]";
    std::cout << std::endl;
}

int main() {
    std::cout << "🚀 === BIGINT CLASS COMPREHENSIVE TEST SUITE === 🚀" << std::endl;
    int total_tests = 0, passed_tests = 0;
    
    // 1. Constructor Tests
    std::cout << "\n📝 CONSTRUCTOR TESTS" << std::endl;
    std::cout << "═══════════════════════════════════════════════════" << std::endl;
    
    bigint default_val;
    print_value_test("Default constructor", "0", default_val.get_digit());
    total_tests++; passed_tests += (default_val.get_digit() == "0");
    
    bigint num_val(12345);
    print_value_test("Number constructor (12345)", "12345", num_val.get_digit());
    total_tests++; passed_tests += (num_val.get_digit() == "12345");
    
    bigint zero_val(0);
    print_value_test("Zero constructor", "0", zero_val.get_digit());
    total_tests++; passed_tests += (zero_val.get_digit() == "0");
    
    bigint copy_val(num_val);
    print_value_test("Copy constructor", num_val.get_digit(), copy_val.get_digit());
    total_tests++; passed_tests += (copy_val.get_digit() == num_val.get_digit());
    
    // 2. Assignment Operator Tests
    std::cout << "\n📝 ASSIGNMENT OPERATOR TESTS" << std::endl;
    std::cout << "═══════════════════════════════════════════════════" << std::endl;
    
    bigint assign_test;
    assign_test = num_val;
    print_value_test("Assignment operator", num_val.get_digit(), assign_test.get_digit());
    total_tests++; passed_tests += (assign_test.get_digit() == num_val.get_digit());
    
    std::string before_self = assign_test.get_digit();
    assign_test = assign_test; // Self-assignment
    print_value_test("Self-assignment safety", before_self, assign_test.get_digit());
    total_tests++; passed_tests += (assign_test.get_digit() == before_self);
    
    // 3. Addition Operator Tests
    std::cout << "\n🔢 ADDITION OPERATOR TESTS" << std::endl;
    std::cout << "═══════════════════════════════════════════════════" << std::endl;
    
    bigint a(999), b(1);
    print_value_test("Simple carry: 999 + 1", "1000", (a + b).get_digit());
    total_tests++; passed_tests += ((a + b).get_digit() == "1000");
    
    bigint c(999999999), d(1);
    print_value_test("Large carry: 999999999 + 1", "1000000000", (c + d).get_digit());
    total_tests++; passed_tests += ((c + d).get_digit() == "1000000000");
    
    bigint e(0), f(123);
    print_value_test("Zero addition: 0 + 123", "123", (e + f).get_digit());
    total_tests++; passed_tests += ((e + f).get_digit() == "123");
    
    bigint g(999), h(999);
    print_value_test("Multiple carry: 999 + 999", "1998", (g + h).get_digit());
    total_tests++; passed_tests += ((g + h).get_digit() == "1998");
    
    // 4. Increment Operator Tests
    std::cout << "\n⬆️  INCREMENT OPERATOR TESTS" << std::endl;
    std::cout << "═══════════════════════════════════════════════════" << std::endl;
    
    bigint inc_test(99);
    bigint post_result = inc_test++;
    print_value_test("Postfix increment return value", "99", post_result.get_digit());
    total_tests++; passed_tests += (post_result.get_digit() == "99");
    
    print_value_test("After postfix increment", "100", inc_test.get_digit());
    total_tests++; passed_tests += (inc_test.get_digit() == "100");
    
    bigint pre_result = ++inc_test;
    print_value_test("Prefix increment return value", "101", pre_result.get_digit());
    total_tests++; passed_tests += (pre_result.get_digit() == "101");
    
    // 5. Shift Operator Tests
    std::cout << "\n🔄 SHIFT OPERATOR TESTS" << std::endl;
    std::cout << "═══════════════════════════════════════════════════" << std::endl;
    
    bigint shift_test(123);
    print_value_test("Left shift: 123 << 0", "123", (shift_test << 0).get_digit());
    total_tests++; passed_tests += ((shift_test << 0).get_digit() == "123");
    
    print_value_test("Left shift: 123 << 2", "12300", (shift_test << 2).get_digit());
    total_tests++; passed_tests += ((shift_test << 2).get_digit() == "12300");
    
    bigint zero_shift(0);
    print_value_test("Zero left shift: 0 << 3", "0", (zero_shift << 3).get_digit());
    total_tests++; passed_tests += ((zero_shift << 3).get_digit() == "0");
    
    bigint right_test(12345);
    print_value_test("Right shift: 12345 >> 0", "12345", (right_test >> 0).get_digit());
    total_tests++; passed_tests += ((right_test >> 0).get_digit() == "12345");
    
    print_value_test("Right shift: 12345 >> 2", "123", (right_test >> 2).get_digit());
    total_tests++; passed_tests += ((right_test >> 2).get_digit() == "123");
    
    print_value_test("Right shift overflow: 12345 >> 10", "0", (right_test >> 10).get_digit());
    total_tests++; passed_tests += ((right_test >> 10).get_digit() == "0");
    
    // 6. Comparison Operator Tests
    std::cout << "\n🔍 COMPARISON OPERATOR TESTS" << std::endl;
    std::cout << "═══════════════════════════════════════════════════" << std::endl;
    
    bigint eq1(12345), eq2(12345), eq3(54321);
    print_test_result("Equality: 12345 == 12345", eq1 == eq2);
    total_tests++; passed_tests += (eq1 == eq2);
    
    print_test_result("Inequality: 12345 != 54321", eq1 != eq3);
    total_tests++; passed_tests += (eq1 != eq3);
    
    bigint lt1(123), lt2(124), lt3(1234);
    print_test_result("Less than same length: 123 < 124", lt1 < lt2);
    total_tests++; passed_tests += (lt1 < lt2);
    
    print_test_result("Less than different length: 123 < 1234", lt1 < lt3);
    total_tests++; passed_tests += (lt1 < lt3);
    
    print_test_result("Greater than: 1234 > 123", lt3 > lt1);
    total_tests++; passed_tests += (lt3 > lt1);
    
    print_test_result("Less than or equal (equal): 123 <= 123", lt1 <= bigint(123));
    total_tests++; passed_tests += (lt1 <= bigint(123));
    
    print_test_result("Greater than or equal (greater): 124 >= 123", lt2 >= lt1);
    total_tests++; passed_tests += (lt2 >= lt1);
    
    // 7. Edge Cases
    std::cout << "\n⚠️  EDGE CASES & STRESS TESTS" << std::endl;
    std::cout << "═══════════════════════════════════════════════════" << std::endl;
    
    // Zero operations
    bigint zero(0);
    print_test_result("Zero equality: 0 == 0", zero == bigint(0));
    total_tests++; passed_tests += (zero == bigint(0));
    
    print_test_result("Zero comparison: 0 < 1", zero < bigint(1));
    total_tests++; passed_tests += (zero < bigint(1));
    
    // Large number test
    bigint max_val(ULONG_MAX);
    bigint overflow_result = max_val + bigint(1);
    std::cout << "  📋 ULONG_MAX: " << max_val << std::endl;
    std::cout << "  🔥 ULONG_MAX + 1: " << overflow_result << std::endl;
    print_test_result("Overflow handling works", overflow_result > max_val);
    total_tests++; passed_tests += (overflow_result > max_val);
    
    // Chain operations
    bigint chain_test(100);
    chain_test += bigint(50);
    chain_test <<= 1;
    print_value_test("Chain operations: (100 + 50) << 1", "1500", chain_test.get_digit());
    total_tests++; passed_tests += (chain_test.get_digit() == "1500");
    
    // 8. Practical Example
    std::cout << "\n🌟 PRACTICAL EXAMPLE: FIBONACCI SEQUENCE" << std::endl;
    std::cout << "═══════════════════════════════════════════════════" << std::endl;
    
    bigint fib1(0), fib2(1);
    std::cout << "  Computing first 8 Fibonacci numbers..." << std::endl;
    std::cout << "  F(0)=" << fib1 << ", F(1)=" << fib2;
    
    for (int i = 2; i < 8; ++i) {
        bigint fib_next = fib1 + fib2;
        std::cout << ", F(" << i << ")=" << fib_next;
        fib1 = fib2;
        fib2 = fib_next;
    }
    std::cout << std::endl;
    
    // Verify specific Fibonacci number
    print_value_test("Fibonacci F(7)", "13", fib2.get_digit());
    total_tests++; passed_tests += (fib2.get_digit() == "13");
    
    // 9. Test Summary
    std::cout << "\n📊 TEST SUMMARY" << std::endl;
    std::cout << "═══════════════════════════════════════════════════" << std::endl;
    
    double pass_rate = (double)passed_tests / total_tests * 100;
    std::cout << "  📈 Tests Passed: " << passed_tests << "/" << total_tests;
    std::cout << " (" << pass_rate << "%)" << std::endl;
    
    if (passed_tests == total_tests) {
        std::cout << "\n🎉 === ALL TESTS PASSED! BIGINT CLASS IS WORKING CORRECTLY === 🎉" << std::endl;
    } else {
        std::cout << "\n⚠️  === SOME TESTS FAILED! PLEASE CHECK THE IMPLEMENTATION === ⚠️" << std::endl;
    }
    
    return 0;
}
