#include <iostream>
#include <string>
#include <vector>
#include <type_traits>
#include <mpl_api.hpp>

// ================== FRAMEWORK BASE (Framework Base Section) ==================
// This part is the core of CRTP + trait_binding framework, usually users don't need to modify

using namespace mlir_crtp;

// Basic type aliases
using Value = int;
using LogicalResult = bool;

LogicalResult success() { return true; }
LogicalResult failure() { return false; }

// Default trait - provides minimal functionality for operations
template<typename Op>
class DefaultTrait {
public:
    std::string getTraitName() const { return "Default"; }
    void execute() { std::cout << "Using default trait behavior" << std::endl; }
};

// Core trait binding system - maps operation types to traits
// By default, all operations get DefaultTrait
template<typename OpType>
struct trait_binding : Type2Type<DefaultTrait<OpType>> {};

// Enhanced CRTP Base with automatic trait application
template<typename Derived>
class Op : public trait_binding<Derived>::type {
public:
    using TraitType = typename trait_binding<Derived>::type;
    
    // Core CRTP interface - these delegate to derived implementations
    Value getInput() { return derived()->default_getInput(); }
    Value getOutput() { return derived()->default_getOutput(); }
    LogicalResult verify() { return derived()->default_verify(); }
    void print() { derived()->default_print(); }
    std::string getOpName() { return derived()->default_getOpName(); }
    
    // Trait-aware methods
    std::string getTraitInfo() {
        return "Op: " + getOpName() + ", Trait: " + TraitType::getTraitName();
    }
    
    // Template method to check if operation has specific trait at compile time
    template<typename T>
    static constexpr bool hasTrait() {
        return std::is_same_v<TraitType, T>;
    }
    
    // Type-safe access to trait-specific functionality
    TraitType* getTrait() { return static_cast<TraitType*>(this); }
    
    // Default implementations - derived classes can override these selectively
    Value default_getInput() { return Value{0}; }
    Value default_getOutput() { return Value{0}; }
    LogicalResult default_verify() { return success(); }
    void default_print() { 
        std::cout << derived()->default_getOpName() << "(...)"; 
    }
    std::string default_getOpName() { return "unknown_op"; }

private:
    Derived* derived() { return static_cast<Derived*>(this); }
};


