#include "extension.h"
#include "eiface.h"

/**
 * @file extension.cpp
 * @brief Implement extension code here.
 */

Extension g_Extension;		/**< Global singleton for extension's main interface */

SMEXT_LINK(&g_Extension);

SH_DECL_HOOK2(IVEngineServer, PrecacheModel, SH_NOATTRIB, 0, int, const char *, bool);

namespace API
{
    static cell_t GetVersion(IPluginContext* pContext, const cell_t* params)
    {
        return pContext->StringToLocalUTF8(params[1], params[2], SMEXT_CONF_VERSION, nullptr);
    }
}

int Extension::PrecacheModel(const char* model, bool precache)
{
    if (V_strncmp(model, "models/weapons/v_models/arms/glove_hardknuckle/", 47) == 0)
    {
        // block
        RETURN_META_VALUE(MRES_SUPERCEDE, 0);
    }

    RETURN_META_VALUE(MRES_IGNORED, 0);
}

bool Extension::SDK_OnLoad(char *error, size_t maxlength, bool late)
{
    g_pShareSys->RegisterLibrary(myself, "ArmsFix");
    g_pShareSys->AddNatives(myself, g_Natives);
    return SDKExtension::SDK_OnLoad(error, maxlength, late);
}

void Extension::SDK_OnUnload()
{
    SH_REMOVE_HOOK(IVEngineServer, PrecacheModel, engine, SH_MEMBER(this, &Extension::PrecacheModel), false);

    return SDKExtension::SDK_OnUnload();
}

bool Extension::SDK_OnMetamodLoad(ISmmAPI *ismm, char *error, size_t maxlen, bool late)
{
    GET_V_IFACE_CURRENT(GetEngineFactory, engine, IVEngineServer, INTERFACEVERSION_VENGINESERVER);
    SH_ADD_HOOK(IVEngineServer, PrecacheModel, engine, SH_MEMBER(this, &Extension::PrecacheModel), false);

    return SDKExtension::SDK_OnMetamodLoad(ismm, error, maxlen, late);
}

sp_nativeinfo_t g_Natives[] = {
    {"ArmsFix.GetVersion", API::GetVersion},
    {nullptr, nullptr}
};