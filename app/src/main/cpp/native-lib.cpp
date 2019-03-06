#include <jni.h>
#include <string.h>
#include "log/sdkLog.h"

/**
 * 获取字符长度
 */
jsize getStrLength(JNIEnv *env, const char *msg) {
    jstring msgJstr = env->NewStringUTF(msg);
    jsize length = env->GetStringLength(msgJstr);
    return length;
}

/**
 * 打印字符串内容
 */
void getObjectStr(JNIEnv *env, jstring msg) {
    const char *msgStr = env->GetStringUTFChars(msg, 0);

    size_t length = strlen(msgStr);
    jobject pJobject = env->NewDirectByteBuffer((void *) msgStr, length);

    char *result = static_cast<char *>(env->GetDirectBufferAddress(pJobject));
    for (int i = 0; i < length; ++i) {
        SDKLOG_DEBUG("result[%d]=%c", i, result[i]);
    }
}

/**
  * C/C++字符串转JNI字符串
  * <p>
  * NewString函数用来生成Unicode JNI字符串
  * NewStringUTF函数用来生成UTF-8 JNI字符串
  */
extern "C"
JNIEXPORT void JNICALL
Java_com_whz_ndk_MainActivity_NewStringTest(JNIEnv *env, jobject instance) {
    char *str = "Hello JNI";

    jstring mJstring = env->NewStringUTF(str);

    const jchar *mJchar = env->GetStringChars(mJstring, NULL);
    SDKLOG_DEBUG("%s", mJchar);

    jsize strLength = env->GetStringLength(mJstring);
    SDKLOG_DEBUG("strLength=%d", strLength);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_whz_ndk_MainActivity_NewStringTest__Ljava_lang_String_2(JNIEnv *env, jobject instance, jstring msg_) {
    const char *msg = env->GetStringUTFChars(msg_, 0);

    jstring strUTF = env->NewStringUTF(msg);
    jsize msgLength = env->GetStringLength(strUTF);
    SDKLOG_DEBUG("msgLength=%d", msgLength);

    env->ReleaseStringUTFChars(msg_, msg);
}

/**
  * JNI字符串转C/C++字符串
  * <p>
  * GetStringChars函数用来从jstring获取Unicode C/C++字符串
  * GetStringUTFChars函数用来从jstring获取UTF-8 C/C++字符串
  */
extern "C"
JNIEXPORT void JNICALL
Java_com_whz_ndk_MainActivity_GetStringTest(JNIEnv *env, jobject instance, jstring msg_) {
    const char *msg = env->GetStringUTFChars(msg_, 0);

    const jchar *jchar1 = env->GetStringChars(msg_, NULL);
    SDKLOG_DEBUG("jchar2_length=%s", jchar1);

    const char *jchar2 = env->GetStringUTFChars(msg_, NULL);
    jstring jchar2_jstring = env->NewStringUTF(jchar2);
    jsize jchar2_length = env->GetStringLength(jchar2_jstring);
    SDKLOG_DEBUG("jchar2_length=%d", jchar2_length);

    env->ReleaseStringUTFChars(msg_, msg);
}

/**
  * JNI字符串截取
  * <p>
  * GetStringRegion函数用来截取Unicode JNI字符串
  * GetStringUTFRegion函数用来截取UTF-8 JNI字符串
  */
extern "C"
JNIEXPORT void JNICALL
Java_com_whz_ndk_MainActivity_GetStringRegionTest(JNIEnv *env, jobject instance, jstring msg_) {
    const char *msg = env->GetStringUTFChars(msg_, 0);

    char *charBuf = new char;
    env->GetStringUTFRegion(msg_, 0, 3, charBuf);
    SDKLOG_DEBUG("msg'length=%d", getStrLength(env, charBuf));

    jchar *jcharBuf = new jchar;
    env->GetStringRegion(msg_, 0, 3, jcharBuf);
    SDKLOG_DEBUG("jcharBuf'length=%s", jcharBuf);

    env->ReleaseStringUTFChars(msg_, msg);
}


/**
 * 获取JNI字符串的长度
 * <p>
 * GetStringLength用来获取Unicode JNI字符串的长度
 * GetStringUTFLength函数用来获取UTF-8 JNI字符串的长度
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_whz_ndk_MainActivity_GetStringLengthTest(JNIEnv *env, jobject instance, jstring msg_) {
    const char *msg = env->GetStringUTFChars(msg_, 0);
    SDKLOG_DEBUG("GetStringLength=%d", getStrLength(env, msg));

    SDKLOG_DEBUG("GetStringLength=%d", env->GetStringLength(msg_));
    SDKLOG_DEBUG("GetStringLength=%d", env->GetStringUTFLength(msg_));

    env->ReleaseStringUTFChars(msg_, msg);
}

/**
  * 获取JNI基本类型数组元素
  */
extern "C"
JNIEXPORT void JNICALL
Java_com_whz_ndk_MainActivity_GetIntElementTest(JNIEnv *env, jobject instance, jintArray msg_) {
    jint *msg = env->GetIntArrayElements(msg_, NULL);

    jsize length = env->GetArrayLength(msg_);
    for (int i = 0; i < length; i++) {
        SDKLOG_DEBUG("msg[%d]=%d", i, msg[i]);
    }

    env->ReleaseIntArrayElements(msg_, msg, 0);
}

/**
  * 获取JNI基本类型数组的子数组
  */
extern "C"
JNIEXPORT void JNICALL
Java_com_whz_ndk_MainActivity_GetIntArrayRegionTest(JNIEnv *env, jobject instance, jintArray msg_) {
    jint *msg = env->GetIntArrayElements(msg_, NULL);

    jint *jintBuf = new jint;
    env->GetIntArrayRegion(msg_, 0, 3, jintBuf);

    for (int i = 0; i < 3; ++i) {
        SDKLOG_DEBUG("msg[%d]=%d", i, jintBuf[i]);
    }

    env->ReleaseIntArrayElements(msg_, msg, 0);
}

/**
  * 设置JNI基本类型数组的子数组
  */
extern "C"
JNIEXPORT void JNICALL
Java_com_whz_ndk_MainActivity_SetIntArrayRegionTest(JNIEnv *env, jobject instance, jintArray msg_) {
    jint *msg = env->GetIntArrayElements(msg_, NULL);

    jint *jintBuf = new jint;
    env->SetIntArrayRegion(msg_, 0, 3, jintBuf);
    for (int i = 0; i < 4; ++i) {
        SDKLOG_DEBUG("msg[%d]=%d", i, jintBuf[i]);
    }

    env->ReleaseIntArrayElements(msg_, msg, 0);
}

/**
  * JNI对象数组
  * <p>
  * GetObjectArrayElement函数用来获取JNI对象数组元素
  * SetObjectArrayElement函数用来设置JNI对象数组元素
  */
extern "C"
JNIEXPORT void JNICALL
Java_com_whz_ndk_MainActivity_GetObjectArrayRegionTest(JNIEnv *env, jobject instance, jobjectArray msg) {
    jsize length = env->GetArrayLength(msg);
    for (int i = 0; i < length; ++i) {
        jobject element = env->GetObjectArrayElement(msg, i);
    }
}

/**
  * JNI NIO缓冲区相关的函数
  * <p>
  * NewDirectByteBuffer函数用来创建NIO缓冲区
  * GetDirectBufferAddress函数用来获取NIO缓冲区的内容
  * GetDirectBufferCapacity函数用来获取NIO缓冲区的大小
  */
extern "C"
JNIEXPORT void JNICALL
Java_com_whz_ndk_MainActivity_DirectBuffer(JNIEnv *env, jobject instance, jstring msg_) {
    const char *msg = env->GetStringUTFChars(msg_, 0);

    size_t length = strlen(msg);
    SDKLOG_DEBUG("length=%d", length);

    jobject pJobject = env->NewDirectByteBuffer((void *) msg, length);
    jlong capacity = env->GetDirectBufferCapacity(pJobject);
    SDKLOG_DEBUG("capacity=%d", capacity);

    char *result = static_cast<char *>(env->GetDirectBufferAddress(pJobject));
    for (int i = 0; i < capacity; ++i) {
        SDKLOG_DEBUG("result[%d]=%c", i, result[i]);
    }

    env->ReleaseStringUTFChars(msg_, msg);
}

/**
  * JNI访问Java类的实例方法
  * <p>
  * GetObjectClass函数用来获取Java对象对应的类类型
  * GetMethodID函数用来获取Java类实例方法的方法ID
  * Call<Type>Method函数用来调用Java类实例特定返回值的方法
  */
extern "C"
JNIEXPORT void JNICALL
Java_com_whz_ndk_MainActivity_callHelloWorld(JNIEnv *env, jobject instance) {

    jclass aClass = env->GetObjectClass(instance);
    if (NULL == aClass) {
        return;
    }

    jmethodID methodID = env->GetMethodID(aClass, "helloWorld", "(Ljava/lang/String;)V");
    if (NULL == methodID) {
        return;
    }

    const char *world = "World";
    jstring worldStr = env->NewStringUTF(world);
    env->CallVoidMethod(instance, methodID, worldStr);
}

/**
  * JNI访问Java类实例字段
  * <p>
  * GetFieldID函数用来获取Java字段的字段ID
  * GetStatic<Type>Field用来获取Java类静态字段的值
  */
extern "C"
JNIEXPORT void JNICALL
Java_com_whz_ndk_MainActivity_callPersonBean(JNIEnv *env, jobject instance, jobject person) {

    jclass objectClass = env->GetObjectClass(person);
    if (NULL == objectClass) return;

    jfieldID nameFieldID = env->GetFieldID(objectClass, "name", "Ljava/lang/String;");
    if (NULL == nameFieldID) return;

    jstring name = static_cast<jstring>(env->GetObjectField(person, nameFieldID));
    getObjectStr(env, name);

    jfieldID ageFieldID = env->GetFieldID(objectClass, "age", "I");
    if (NULL == ageFieldID) return;
    jint age = env->GetIntField(person, ageFieldID);
    SDKLOG_DEBUG("age=%d", age);
}

/**
  * JNI访问Java类静态字段
  * <p>
  * GetStaticFieldID函数用来获取Java静态字段的字段ID
  * GetStatic<Type>Field用来获取Java类静态字段的值
  */
extern "C"
JNIEXPORT void JNICALL
Java_com_whz_ndk_MainActivity_callStaticPerson(JNIEnv *env, jobject instance, jobject person) {

    jclass aClass = env->GetObjectClass(person);
    if (NULL == aClass) return;

    jfieldID nameField = env->GetStaticFieldID(aClass, "nameStatic", "Ljava/lang/String;");
    if (NULL == nameField)return;

    jstring name = static_cast<jstring>(env->GetStaticObjectField(aClass, nameField));
    getObjectStr(env, name);


    jfieldID ageField = env->GetStaticFieldID(aClass, "ageStatic", "I");
    jint age = env->GetStaticIntField(aClass, ageField);
    SDKLOG_DEBUG("age=%d", age);
}

/**
  * JNI可以使用Java对象进行线程同步
  * MonitorEnter函数用来锁定Java对象
  * MonitorExit函数用来释放Java对象锁
  */
extern "C"
JNIEXPORT void JNICALL
Java_com_whz_ndk_MainActivity_joinLock(JNIEnv *env, jobject instance, jobject person) {

    env->MonitorEnter(person);
    //do something
    for (int i = 0; i < 10; ++i) {
        SDKLOG_DEBUG("i=%d", i);
    }
    env->MonitorExit(person);
}

/**
  * JNI处理Java异常
  */
extern "C"
JNIEXPORT void JNICALL
Java_com_whz_ndk_MainActivity_callHelloWorldException(JNIEnv *env, jobject instance) {

    jclass aClass = env->GetObjectClass(instance);
    if (NULL == aClass)return;

    jmethodID exceptionMethodID = env->GetMethodID(aClass, "helloWorldException", "()V");
    if (NULL == exceptionMethodID)return;

    env->CallVoidMethod(instance, exceptionMethodID);
    if (env->ExceptionOccurred() != NULL) {
        env->ExceptionClear();
        SDKLOG_DEBUG("excepton occurred");
        return;
    }
    SDKLOG_DEBUG("normal run");
}

/**
  * JNI抛出Java类型的异常
  * <p>
  * JNI通过ThrowNew函数抛出Java类型的异常
  */
extern "C"
JNIEXPORT void JNICALL
Java_com_whz_ndk_MainActivity_callNativeException(JNIEnv *env, jobject instance) {

    jclass aClass = env->FindClass("java/lang/NullPointerException");
    if (NULL == aClass)return;

    env->ThrowNew(aClass, "null pointer excepton occurred!");
}

/**
  * JNI对象的局部引用
  */
extern "C"
JNIEXPORT void JNICALL
Java_com_whz_ndk_MainActivity_deleteLocalRef(JNIEnv *env, jobject instance) {

    jclass aClass = env->GetObjectClass(instance);
    if (NULL == aClass)return;

    jmethodID methodID = env->GetMethodID(aClass, "helloWorld", "()V");
    if (NULL == methodID)return;

    env->CallVoidMethod(instance, methodID);
    env->DeleteLocalRef(aClass);
}

/**
  * 强全局引用
  *
  * NewGlobalRef用来创建强全局引用的JNI对象
  * DeleteGlobalRef用来删除强全局引用的JNI对象
  */
jobject globalRef;
extern "C"
JNIEXPORT void JNICALL
Java_com_whz_ndk_MainActivity_GlobalRef(JNIEnv *env, jobject instance) {

    //生成全局的JNI对象引用，这样生成的全局的JNI对象才可以在其它函数中使用
    globalRef = env->NewGlobalRef(instance);

    //假如我们不需要gThiz这个全局的JNI对象引用，我们可以把它删除掉
    env->DeleteGlobalRef(globalRef);

}

/**
  * 弱全局引用
  * <p>
  * NewWeakGlobalRef用来创建弱全局引用的JNI对象
  * DeleteWeakGlobalRef用来删除弱全局引用的JNI对象
  * IsSameObject用来判断两个JNI对象是否相同
  */
jweak weakGlobalRef;
extern "C"
JNIEXPORT void JNICALL
Java_com_whz_ndk_MainActivity_weakRef(JNIEnv *env, jobject instance) {

    //生成全局的JNI对象引用，这样生成的全局的JNI对象才可以在其它函数中使用
    weakGlobalRef = env->NewWeakGlobalRef(instance);

    if (env->IsSameObject(weakGlobalRef, NULL)) {
        //弱全局引用已经被Java的垃圾回收器回收
    }

    //弱全局引用已经被Java的垃圾回收器回收
    env->DeleteWeakGlobalRef(weakGlobalRef);
}