#include <jni.h>
#include <string>
#include <android/log.h>
#pragma GCC optimize ("O0")

const char* flag_store = "Spirit{th1z_15_a_fake_f1ag_plz_don't_try_me}";
const char* real_flag = "\x40\x4a\xa8\x09\x78\x25\xdb\x0b\x3e\x56\x69\x61\x23\xca\xf1\x59\x2b\x74\x18\x1d\xb0\x2a\xb3\x61\x5b\x7f\x0f\x8a\xff\xe0\xab\x4b\xa7\xb5\x08\x83\xad\x18\x65\x02\x78\x83\x01\xcb";
const char* keytbl = "\x13\x3a\xc1\x7b\x11\x51\xa0\x3a\x0a\x35\x0d\x03\x17\xab\xc8\x74\x19\x11\x20\x7e\x9d\x1e\xd6\x07\x3f\x52\x6d\xec\xcd\xd5\x86\x28\x95\xd0\x6a\xe0\x9a\x7b\x57\x3a\x1c\xb5\x32\xb6\x8b\x71\x42\x7e\x40\xa6\x6c\xe3\xa9\x28\x6b\x45\xbf\x5d\xb0\x24\xcd\x9b\x45\xa2";
char* flag_ptr = (char *)flag_store;

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    auto *flag_decrypted = new char[45];
    for(int i = 0; i < 44; i++) {
        flag_decrypted[i] = real_flag[i] ^ keytbl[i];
    }
    flag_decrypted[44] = 0;

    flag_ptr = flag_decrypted;
    return JNI_VERSION_1_6;
}

extern "C" JNIEXPORT jboolean JNICALL
Java_mk_a0x_crackme_MainActivity_checkFlag(
        JNIEnv* env,
        jobject /* this */,
        jstring flag) {
    jboolean isCopy;
    const char *convertedValue = env->GetStringUTFChars(flag, &isCopy);
    bool result = false;

    if (strcmp(convertedValue, flag_ptr) == 0) {
        result = true;
    }
    env->ReleaseStringUTFChars(flag, convertedValue);
    return result;
}
