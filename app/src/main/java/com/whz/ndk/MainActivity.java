package com.whz.ndk;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.CardView;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import com.whz.ndk.bean.Person;

public class MainActivity extends AppCompatActivity {

    private final String aTag = MainActivity.class.getSimpleName();
    private CardView mBtnClick;
    private TextView mResult;

    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        initView();
        initEvent();
    }


    /**
     * C/C++字符串转JNI字符串
     * <p>
     * NewString函数用来生成Unicode JNI字符串
     * NewStringUTF函数用来生成UTF-8 JNI字符串
     */
    public native void NewStringTest();

    public native void NewStringTest(String msg);

    /**
     * JNI字符串转C/C++字符串
     * <p>
     * GetStringChars函数用来从jstring获取Unicode C/C++字符串
     * GetStringUTFChars函数用来从jstring获取UTF-8 C/C++字符串
     */
    public native void GetStringTest(String msg);

    /**
     * JNI字符串截取
     * <p>
     * GetStringRegion函数用来截取Unicode JNI字符串
     * GetStringUTFRegion函数用来截取UTF-8 JNI字符串
     */
    public native void GetStringRegionTest(String msg);

    /**
     * 获取JNI字符串的长度
     * <p>
     * GetStringLength用来获取Unicode JNI字符串的长度
     * GetStringUTFLength函数用来获取UTF-8 JNI字符串的长度
     */
    public native void GetStringLengthTest(String msg);

    /**
     * 获取JNI基本类型数组元素
     */
    public native void GetIntElementTest(int[] msg);

    /**
     * 获取JNI基本类型数组的子数组
     */
    public native void GetIntArrayRegionTest(int[] msg);

    /**
     * 设置JNI基本类型数组的子数组
     */
    public native void SetIntArrayRegionTest(int[] msg);

    /**
     * JNI对象数组
     * <p>
     * GetObjectArrayElement函数用来获取JNI对象数组元素
     * SetObjectArrayElement函数用来设置JNI对象数组元素
     */
    public native void GetObjectArrayRegionTest(Object[] msg);

    /**
     * JNI NIO缓冲区相关的函数
     * <p>
     * NewDirectByteBuffer函数用来创建NIO缓冲区
     * GetDirectBufferAddress函数用来获取NIO缓冲区的内容
     * GetDirectBufferCapacity函数用来获取NIO缓冲区的大小
     */
    public native void DirectBuffer(String msg);

    /**
     * JNI访问Java类的实例方法
     * <p>
     * GetObjectClass函数用来获取Java对象对应的类类型
     * GetMethodID函数用来获取Java类实例方法的方法ID
     * Call<Type>Method函数用来调用Java类实例特定返回值的方法
     */
    public native void callHelloWorld();

    public void helloWorld(String msg) {
        Log.e(aTag, "Hello " + msg);
    }

    /**
     * JNI访问Java类实例字段
     * <p>
     * GetFieldID函数用来获取Java字段的字段ID
     * GetStatic<Type>Field用来获取Java类静态字段的值
     */
    public native void callPersonBean(Person person);

    public void personBean() {
        Person person = new Person();
        person.name = "whz";
        person.age = 18;
        callPersonBean(person);
    }

    /**
     * JNI访问Java类静态字段
     * <p>
     * GetStaticFieldID函数用来获取Java静态字段的字段ID
     * GetStatic<Type>Field用来获取Java类静态字段的值
     */
    public native void callStaticPerson(Person person);

    public void staticPersonBean() {
        Person.nameStatic = "whz";
        Person.ageStatic = 18;

        Person person = new Person();
        callStaticPerson(person);
    }

    /**
     * JNI可以使用Java对象进行线程同步
     * MonitorEnter函数用来锁定Java对象
     * MonitorExit函数用来释放Java对象锁
     */
    public native void joinLock(Person person);

    /**
     * JNI处理Java异常
     */
    public native void callHelloWorldException();

    public void helloWorldException() {
        throw new NullPointerException("pointer exception");
    }

    /**
     * JNI抛出Java类型的异常
     * <p>
     * JNI通过ThrowNew函数抛出Java类型的异常
     */
    public native void callNativeException();

    /**
     * JNI对象的局部引用
     */
    public native void deleteLocalRef();

    public void helloWorld() {
        Log.e(aTag, "Hello World");
    }

    /**
     * 强全局引用
     * <p>
     * NewGlobalRef用来创建强全局引用的JNI对象
     * DeleteGlobalRef用来删除强全局引用的JNI对象
     */
    public native void GlobalRef();

    /**
     * 弱全局引用
     * <p>
     * NewWeakGlobalRef用来创建弱全局引用的JNI对象
     * DeleteWeakGlobalRef用来删除弱全局引用的JNI对象
     * IsSameObject用来判断两个JNI对象是否相同
     */
    public native void weakRef();

    /**
     * 初始化事件
     */
    private void initEvent() {
        mBtnClick.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                deleteLocalRef();
            }
        });
    }

    /**
     * 初始化View
     */
    private void initView() {
        mBtnClick = findViewById(R.id.btn_click);
        mResult = findViewById(R.id.result_text);
    }
}
