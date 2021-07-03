#if defined _vec_ArmsFix_included
    #endinput
#endif

#define _vec_ArmsFix_included

methodmap ArmsFix {
    public static native bool GetVersion(char[] buffer, int maxlen);
}

public Extension __ext_armsFix = 
{
	name = "ArmsFix",
	file = "ArmsFix.ext",
#if defined AUTOLOAD_EXTENSIONS
	autoload = 1,
#else
	autoload = 0,
#endif
#if defined REQUIRE_EXTENSIONS
	required = 1,
#else
	required = 0,
#endif
};
