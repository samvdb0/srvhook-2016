#pragma once
#include "pch.h"

namespace LuaScriptArgument
{
    struct LuaArgumentDefault
    {
        virtual void* _Delete(uint);
        virtual int lad_ArgumentSet(lua_State*);
        virtual void lad_ReturnSet(lua_State*);
        virtual int lad_GetReturnNumber();
        virtual int lad_GetReturnValue();
    	
        int lad_ReturnNumber;
        int lad_ReturnValue;
    };

	// todo: implement all argsets.

}
