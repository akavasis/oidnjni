#include <jni.h>
#include <limits.h>
#include <stdio.h>
#include <OpenImageDenoise/oidn.h>

JNIEXPORT jlong JNICALL
Java_net_time4tea_oidn_Oidn_jniNewDevice (JNIEnv *env, jobject obj, jint type) {
    return (jlong) oidnNewDevice(type);
}

JNIEXPORT void JNICALL
Java_net_time4tea_oidn_OidnDevice_jniCommit (JNIEnv *env, jobject obj, jlong ptr) {
    oidnCommitDevice( (OIDNDevice) ptr)  ;
}

JNIEXPORT void JNICALL
Java_net_time4tea_oidn_OidnDevice_jniRelease (JNIEnv *env, jobject obj, jlong ptr) {
    oidnReleaseDevice( (OIDNDevice) ptr)  ;
}

JNIEXPORT void JNICALL
Java_net_time4tea_oidn_OidnDevice_jniGetError(JNIEnv *env, jobject obj, jlong ptr) {

    const char* errorMessage;
    if (oidnGetDeviceError( (OIDNDevice) ptr, &errorMessage) != OIDN_ERROR_NONE) {
        printf("Error: %s\n", errorMessage);
    }
    else {
        printf("No error!");
    }
}

JNIEXPORT jlong JNICALL Java_net_time4tea_oidn_OidnDevice_jniNewFilter (JNIEnv *env, jobject obj, jlong ptr, jstring type) {
    const char *type_c= (*env)->GetStringUTFChars(env,type,0);
	OIDNFilter filter = oidnNewFilter ( (OIDNDevice) ptr, type_c );
	(*env)->ReleaseStringUTFChars(env, type, type_c);
	return (jlong) filter;
}

JNIEXPORT void JNICALL
Java_net_time4tea_oidn_OidnFilter_jniCommit (JNIEnv *env, jobject obj, jlong ptr) {
    oidnCommitFilter( (OIDNFilter) ptr)  ;
}

JNIEXPORT void JNICALL
Java_net_time4tea_oidn_OidnFilter_jniExecute (JNIEnv *env, jobject obj, jlong ptr) {
    oidnExecuteFilter( (OIDNFilter) ptr)  ;
}

JNIEXPORT void JNICALL
Java_net_time4tea_oidn_OidnFilter_jniRelease (JNIEnv *env, jobject obj, jlong ptr) {
    oidnReleaseFilter( (OIDNFilter) ptr)  ;
}

JNIEXPORT void JNICALL
Java_net_time4tea_oidn_OidnFilter_jniSetSharedFilterImage (JNIEnv *env, jobject obj, jlong ptr, jstring name, jobject buffer, jint width, jint height) {

    const char *name_c= (*env)->GetStringUTFChars(env,name,0);
    void *address = (*env)->GetDirectBufferAddress(env, buffer);

    oidnSetSharedFilterImage( (OIDNFilter) ptr, name_c,  address, OIDN_FORMAT_FLOAT3, width, height, 0, 0, 0);

	(*env)->ReleaseStringUTFChars(env, name, name_c);
}
