#include <iostream>
#include <string>
#include <type_traits>
#include <1_base_crtp.hpp>

// =================== Part 2: Basic Usage Examples ===================

// Example 1: Use all default implementations
class SimpleOp : public OpBase<SimpleOp> {
    // No overrides - fully relies on framework defaults
public:
    void demo() {
        std::cout << "\n=== SimpleOp (all defaults) ===" << std::endl;
        getInput();
        std::cout << "Operation: " << getOperationName() << std::endl;
        std::cout << "Valid: " << verify() << std::endl;
        print();
    }
};

// Example 2: Selective override - only custom verification
class IdentityOp : public OpBase<IdentityOp> {
public:
    // Only override verification logic, others use defaults
    bool default_verify() {
        std::cout << "IdentityOp: Custom verification logic" << std::endl;
        return true; // Identity operation is always valid
    }
    
    void demo() {
        std::cout << "\n=== IdentityOp (custom verify) ===" << std::endl;
        getInput();
        std::cout << "Operation: " << getOperationName() << std::endl;
        std::cout << "Valid: " << verify() << std::endl;
        print();
    }
};

// Example 3: Multiple overrides - custom name and print
class ComplexOp : public OpBase<ComplexOp> {
public:
    // Override multiple methods
    std::string default_getOperationName() {
        std::cout << "ComplexOp: Custom operation name" << std::endl;
        return "complex_operation";
    }
    
    void default_print() {
        std::cout << "ComplexOp: Custom print - " << getOperationName() 
                  << " with special formatting" << std::endl;
    }
    
    void demo() {
        std::cout << "\n=== ComplexOp (custom name + print) ===" << std::endl;
        getInput();
        std::cout << "Operation: " << getOperationName() << std::endl;
        std::cout << "Valid: " << verify() << std::endl;
        print();
    }
};

// =================== Part 3: Advanced Features ===================


int main() {
    std::cout << "======= Basic CRTP Demo: Selective Override Pattern =======" << std::endl;
    
    // Basic usage examples
    SimpleOp simple;
    simple.demo();
    
    IdentityOp identity;
    identity.demo();
    
    ComplexOp complex;
    complex.demo();
    
    // Template-based operations
    BinaryOp<BinaryOpKind::Add> addOp;
    addOp.demo();
    
    BinaryOp<BinaryOpKind::Sub> subOp;
    subOp.demo();
    
    std::cout << "\n======= Summary =======" << std::endl;
    std::cout << "✓ SimpleOp: Uses framework defaults" << std::endl;
    std::cout << "✓ IdentityOp: Selective verification override" << std::endl;
    std::cout << "✓ ComplexOp: Multiple method overrides" << std::endl;
    std::cout << "✓ BinaryOp<T>: Template-based compile-time polymorphism" << std::endl;
    std::cout << "\nKey advantage: More flexible than TableGen's fixed extension points!" << std::endl;
    
    return 0;
}

// ================== Comparison Summary ==================

/*
TableGen Approach:
------------------
def IdentityOp : Op<"identity"> {
  let arguments = (ins AnyType:$input);
  let results = (outs AnyType:$output);
  let hasVerifier = 1;
  let extraClassDefinition = [{
    LogicalResult verify() {
      return getInput().getType() == getOutput().getType() ? success() : failure();
    }
  }];
}
// Generates ~200 lines of C++ code

CRTP Approach:
--------------
class IdentityOp : public Op<IdentityOp> {
    LogicalResult default_verify() {
        return (getInput() == getOutput()) ? success() : failure();
    }
    // ~15 lines total, direct C++ code
}

Result: Same functionality, 90% less code, 100% more flexibility!
*/ 