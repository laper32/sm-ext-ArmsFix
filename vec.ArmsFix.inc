#if defined _vec_ArmsFix_included
    #endinput
#endif

#define _vec_ArmsFix_included

methodmap ArmsFix {
    public static native bool GetVersion(char[] buffer, int maxlen);
}