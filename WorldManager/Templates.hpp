#pragma once
#include <cstddef>
#pragma warning(disable : 4251)

typedef void* VTABLEFUNC;

template <class T, class RT> _declspec(naked) RT __stdcall CallVTable(VTABLEFUNC func, T* self) {
	_asm {
		POP EAX
		ADD ESP, 0x8
		MOV ECX, DWORD PTR DS : [ESP - 0x4]
		PUSH EAX
		MOV EAX, DWORD PTR DS : [ESP - 0x4]
		JMP EAX
	}
}

template <class T, class RT, class P1> _declspec(naked) RT __stdcall CallVTable(VTABLEFUNC func, T* self, P1 param1) {
	_asm {
		POP EAX
		ADD ESP, 0x8
		MOV ECX, DWORD PTR DS : [ESP - 0x4]
		PUSH EAX
		MOV EAX, DWORD PTR DS : [ESP - 0x4]
		JMP EAX
	}
}

template <class T, class RT, class P1, class P2> _declspec(naked) RT __stdcall CallVTable(VTABLEFUNC func, T* self, P1 param1, P2 param2) {
	_asm {
		POP EAX
		ADD ESP, 0x8
		MOV ECX, DWORD PTR DS : [ESP - 0x4]
		PUSH EAX
		MOV EAX, DWORD PTR DS : [ESP - 0x4]
		JMP EAX
	}
}

template <class T, class RT, class P1, class P2, class P3> _declspec(naked) RT __stdcall CallVTable(VTABLEFUNC func, T* self, P1 param1, P2 param2, P3 param3) {
	_asm {
		POP EAX
		ADD ESP, 0x8
		MOV ECX, DWORD PTR DS : [ESP - 0x4]
		PUSH EAX
		MOV EAX, DWORD PTR DS : [ESP - 0x4]
		JMP EAX
	}
}

template <class T, class RT, class P1, class P2, class P3, class P4> _declspec(naked) RT __stdcall CallVTable(VTABLEFUNC func, T* self, P1 param1, P2 param2, P3 param3, P4 param4) {
	_asm {
		POP EAX
		ADD ESP, 0x8
		MOV ECX, DWORD PTR DS : [ESP - 0x4]
		PUSH EAX
		MOV EAX, DWORD PTR DS : [ESP - 0x4]
		JMP EAX
	}
}

template <class T, class RT, class P1, class P2, class P3, class P4, class P5> _declspec(naked) RT __stdcall CallVTable(VTABLEFUNC func, T* self, P1 param1, P2 param2, P3 param3, P4 param4, P5 param5) {
	_asm {
		POP EAX
		ADD ESP, 0x8
		MOV ECX, DWORD PTR DS : [ESP - 0x4]
		PUSH EAX
		MOV EAX, DWORD PTR DS : [ESP - 0x4]
		JMP EAX
	}
}

template <class T, class RT> _declspec(naked) RT __stdcall CallMemberFunction(unsigned int func, T* self) {
	_asm {
		POP EAX
		ADD ESP, 0x8
		MOV ECX, DWORD PTR DS : [ESP - 0x4]
		PUSH EAX
		MOV EAX, DWORD PTR DS : [ESP - 0x4]
		JMP EAX
	}
}

template <class T, class RT, class A1> _declspec(naked) RT __stdcall CallMemberFunction(unsigned int func, T* self, A1 arg1) {
	_asm {
		POP EAX
		ADD ESP, 0x8
		MOV ECX, DWORD PTR DS : [ESP - 0x4]
		PUSH EAX
		MOV EAX, DWORD PTR DS : [ESP - 0x4]
		JMP EAX
	}
}

template <class T, class RT, class A1, class A2> _declspec(naked) RT __stdcall CallMemberFunction(unsigned int func, T* self, A1 arg1, A2 arg2) {
	_asm {
		POP EAX
		ADD ESP, 0x8
		MOV ECX, DWORD PTR DS : [ESP - 0x4]
		PUSH EAX
		MOV EAX, DWORD PTR DS : [ESP - 0x4]
		JMP EAX
	}
}

template <class T, class RT, class A1, class A2, class A3> _declspec(naked) RT __stdcall CallMemberFunction(unsigned int func, T* self, A1 arg1, A2 arg2, A3 arg3) {
	_asm {
		POP EAX
		ADD ESP, 0x8
		MOV ECX, DWORD PTR DS : [ESP - 0x4]
		PUSH EAX
		MOV EAX, DWORD PTR DS : [ESP - 0x4]
		JMP EAX
	}
}

template <class T, class RT, class A1, class A2, class A3, class A4> _declspec(naked) RT __stdcall CallMemberFunction(unsigned int func, T* self, A1 arg1, A2 arg2, A3 arg3, A4 arg4) {
	_asm {
		POP EAX
		ADD ESP, 0x8
		MOV ECX, DWORD PTR DS : [ESP - 0x4]
		PUSH EAX
		MOV EAX, DWORD PTR DS : [ESP - 0x4]
		JMP EAX
	}
}

template <class T, class RT, class A1, class A2, class A3, class A4, class A5> _declspec(naked) RT __stdcall CallMemberFunction(unsigned int func, T* self, A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5) {
	_asm {
		POP EAX
		ADD ESP, 0x8
		MOV ECX, DWORD PTR DS : [ESP - 0x4]
		PUSH EAX
		MOV EAX, DWORD PTR DS : [ESP - 0x4]
		JMP EAX
	}
}

template <class T, class RT, class A1, class A2, class A3, class A4, class A5, class A6> _declspec(naked) RT __stdcall CallMemberFunction(unsigned int func, T* self, A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5, A6 arg6) {
	_asm {
		POP EAX
		ADD ESP, 0x8
		MOV ECX, DWORD PTR DS : [ESP - 0x4]
		PUSH EAX
		MOV EAX, DWORD PTR DS : [ESP - 0x4]
		JMP EAX
	}
}

template <class T, class RT, class A1, class A2, class A3, class A4, class A5, class A6, class A7> _declspec(naked) RT __stdcall CallMemberFunction(unsigned int func, T* self, A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5, A6 arg6, A7 arg7) {
	_asm {
		POP EAX
		ADD ESP, 0x8
		MOV ECX, DWORD PTR DS : [ESP - 0x4]
		PUSH EAX
		MOV EAX, DWORD PTR DS : [ESP - 0x4]
		JMP EAX
	}
}

template <class T, class RT, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> _declspec(naked) RT __stdcall CallMemberFunction(unsigned int func, T* self, A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5, A6 arg6, A7 arg7, A8 arg8) {
	_asm {
		POP EAX
		ADD ESP, 0x8
		MOV ECX, DWORD PTR DS : [ESP - 0x4]
		PUSH EAX
		MOV EAX, DWORD PTR DS : [ESP - 0x4]
		JMP EAX
	}
}

template <class T, class RT, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9> _declspec(naked) RT __stdcall CallMemberFunction(unsigned int func, T* self, A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5, A6 arg6, A7 arg7, A8 arg8, A9 arg9) {
	_asm {
		POP EAX
		ADD ESP, 0x8
		MOV ECX, DWORD PTR DS : [ESP - 0x4]
		PUSH EAX
		MOV EAX, DWORD PTR DS : [ESP - 0x4]
		JMP EAX
	}
}

template <class T, class RT, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10> _declspec(naked) RT __stdcall CallMemberFunction(unsigned int func, T* self, A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5, A6 arg6, A7 arg7, A8 arg8, A9 arg9, A10 arg10) {
	_asm {
		POP EAX
		ADD ESP, 0x8
		MOV ECX, DWORD PTR DS : [ESP - 0x4]
		PUSH EAX
		MOV EAX, DWORD PTR DS : [ESP - 0x4]
		JMP EAX
	}
}

template <class T, class RT, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11> _declspec(naked) RT __stdcall CallMemberFunction(unsigned int func, T* self, A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5, A6 arg6, A7 arg7, A8 arg8, A9 arg9, A10 arg10, A11 arg11) {
	_asm {
		POP EAX
		ADD ESP, 0x8
		MOV ECX, DWORD PTR DS : [ESP - 0x4]
		PUSH EAX
		MOV EAX, DWORD PTR DS : [ESP - 0x4]
		JMP EAX
	}
}

template <class T, class RT, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12> _declspec(naked) RT __stdcall CallMemberFunction(unsigned int func, T* self, A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5, A6 arg6, A7 arg7, A8 arg8, A9 arg9, A10 arg10, A11 arg11, A12 arg12) {
	_asm {
		POP EAX
		ADD ESP, 0x8
		MOV ECX, DWORD PTR DS : [ESP - 0x4]
		PUSH EAX
		MOV EAX, DWORD PTR DS : [ESP - 0x4]
		JMP EAX
	}
}

template <class T, class RT, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13> _declspec(naked) RT __stdcall CallMemberFunction(unsigned int func, T* self, A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5, A6 arg6, A7 arg7, A8 arg8, A9 arg9, A10 arg10, A11 arg11, A12 arg12, A13 arg13) {
	_asm {
		POP EAX
		ADD ESP, 0x8
		MOV ECX, DWORD PTR DS : [ESP - 0x4]
		PUSH EAX
		MOV EAX, DWORD PTR DS : [ESP - 0x4]
		JMP EAX
	}
}

template <unsigned int tfunc, class RT> _declspec(naked) RT CallStaticFunction() {
	static unsigned int func = tfunc;
	_asm {
		JMP func
	}
}


template <int tfunc, class RT, class A1> _declspec(naked) RT CallStaticFunction(A1 arg1) {
	static unsigned int func = tfunc;
	_asm {
		JMP func
	}
}

template <int tfunc, class RT, class A1, class A2> _declspec(naked) RT CallStaticFunction(A1 arg1, A2 arg2) {
	static unsigned int func = tfunc;
	_asm {
		JMP func
	}
}

template <int tfunc, class RT, class A1, class A2, class A3> _declspec(naked) RT CallStaticFunction(A1 arg1, A2 arg2, A3 arg3) {
	static unsigned int func = tfunc;
	_asm {
		JMP func
	}
}

template <int tfunc, class RT, class A1, class A2, class A3, class A4> _declspec(naked) RT CallStaticFunction(A1 arg1, A2 arg2, A3 arg3, A4 arg4) {
	static unsigned int func = tfunc;
	_asm {
		JMP func
	}
}

template <int tfunc, class RT, class A1, class A2, class A3, class A4, class A5> _declspec(naked) RT CallStaticFunction(A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5) {
	static unsigned int func = tfunc;
	_asm {
		JMP func
	}
}

template <int tfunc, class RT, class A1, class A2, class A3, class A4, class A5, class A6> _declspec(naked) RT CallStaticFunction(A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5, A6 arg6) {
	static unsigned int func = tfunc;
	_asm {
		JMP func
	}
}

template <int tfunc, class RT, class A1, class A2, class A3, class A4, class A5, class A6, class A7> _declspec(naked) RT CallStaticFunction(A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5, A6 arg6, A7 arg7) {
	static unsigned int func = tfunc;
	_asm {
		JMP func
	}
}

template <int tfunc, class RT, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> _declspec(naked) RT CallStaticFunction(A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5, A6 arg6, A7 arg7, A8 arg8) {
	static unsigned int func = tfunc;
	_asm {
		JMP func
	}
}

inline __declspec(naked) void* MemberFuncToPtr(...) {
	__asm {
		mov eax, [esp + 4]
		retn
	}
}