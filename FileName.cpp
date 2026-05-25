#include <iostream>
#include <stack>
#include <string>
#include <cstdint>

struct LostWordVM_II {

	typedef std::intmax_t Register;

	//Register A = 0;
	Register B = 0;
	std::string TEXT;
	std::stack<Register> ST;

	enum OPERATIONS {
		ADD = 1,
		SUB = 2,
		MUL = 3,
		DIV = 4,
		MOD = 5,
		AND = 6,
		OR = 7,
		XOR = 8,
		NOT = 9,
		Nand = 10,
		Nor = 11,
		XNor = 12,
		LSH = 13,
		RSH = 14,

	};

};

void Push(LostWordVM_II& vm, const LostWordVM_II::Register& value) {
	vm.ST.push(value);
}
LostWordVM_II::Register Pop(LostWordVM_II& vm){
	if (vm.ST.empty()) {
		std::cerr << "Stack underflow!" << std::endl;
		return 0;
	}
	LostWordVM_II::Register value = vm.ST.top();
	vm.ST.pop();

	return value;
}

LostWordVM_II::Register Top(const LostWordVM_II& vm) {
	if (vm.ST.empty()) {
		std::cerr << "Stack is empty!" << std::endl;
		return 0;
	}
	return vm.ST.top();
}

void Clear(LostWordVM_II& vm) {
	while (!vm.ST.empty()) {
		vm.ST.pop();
	}
}

void Culc(LostWordVM_II& vm, LostWordVM_II::OPERATIONS op) {
	switch(op) {
	case LostWordVM_II::ADD:
		vm.B = Pop(vm);
		Push(vm, Pop(vm) + vm.B);
		break;
	case LostWordVM_II::SUB:
		vm.B = Pop(vm);
		Push(vm, Pop(vm) - vm.B);
		break;
	case LostWordVM_II::MUL:
		vm.B = Pop(vm);
		Push(vm, Pop(vm) * vm.B);
		break;
	case LostWordVM_II::DIV:
		vm.B = Pop(vm);
		if (vm.B == 0) {
			std::cerr << "Division by zero!" << std::endl;
			return;
		}
		Push(vm, Pop(vm) / vm.B);
		break;
	case LostWordVM_II::MOD:
		vm.B = Pop(vm);
		if (vm.B == 0) {
			std::cerr << "Division by zero!" << std::endl;
			return;
		}
		Push(vm, Pop(vm) % vm.B);
		break;

	//default:
		//std::cerr << "Unsupported operation!" << std::endl;

	}

	switch (op) {
	case LostWordVM_II::AND:
		vm.B = Pop(vm);
		Push(vm, Pop(vm) & vm.B);
		break;
	case LostWordVM_II::OR:
		vm.B = Pop(vm);
		Push(vm, Pop(vm) | vm.B);
		break;
	case LostWordVM_II::XOR:
		vm.B = Pop(vm);
		Push(vm, Pop(vm) ^ vm.B);
		break;
	case LostWordVM_II::NOT:
		Push(vm, ~Pop(vm));
		break;
	case LostWordVM_II::Nand:
		vm.B = Pop(vm);
		Push(vm, ~(Pop(vm) & vm.B));
		break;
	case LostWordVM_II::Nor:
		vm.B = Pop(vm);
		Push(vm, ~(Pop(vm) | vm.B));
		break;
	case LostWordVM_II::XNor:
		vm.B = Pop(vm);
		Push(vm, ~(Pop(vm) ^ vm.B));
		break;
	}
}

void Operation(LostWordVM_II& vm, LostWordVM_II::OPERATIONS op, LostWordVM_II::Register value) {
	switch (op) {
		case LostWordVM_II::ADD:
		case LostWordVM_II::SUB:
		case LostWordVM_II::MUL:
		case LostWordVM_II::DIV:
		case LostWordVM_II::MOD:
			Push(vm, value);
			Culc(vm, op);
			break;
		//default:
			//std::cerr << "Unsupported operation!" << std::endl;
	}
	switch (op) {
	case LostWordVM_II::AND:
	case LostWordVM_II::OR:
	case LostWordVM_II::XOR:
	case LostWordVM_II::NOT:
	case LostWordVM_II::Nand:
	case LostWordVM_II::Nor:
	case LostWordVM_II::XNor:
		Push(vm, value);
		Culc(vm, op);
		break;
	}
}

void PrintStack(const LostWordVM_II& vm) {
	std::stack<LostWordVM_II::Register> temp = vm.ST;
	while (!temp.empty()) {
		std::cout << temp.top() << std::endl;
		temp.pop();
	}
}

int main() {
	LostWordVM_II vm;
	Operation(vm, LostWordVM_II::ADD, 5);
	Operation(vm, LostWordVM_II::MUL, 3);
	PrintStack(vm); // Should print 15
	return 0;
}