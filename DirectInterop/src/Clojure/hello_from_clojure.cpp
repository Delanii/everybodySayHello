#include <jni.h>       /* where everything is defined */
#include <cstring>

extern "C" int hello_from_clojure() {
    JavaVM *jvm;       /* denotes a Java VM */
    JNIEnv *env;       /* pointer to native method interface */
    JavaVMInitArgs vm_args; /* JDK/JRE 6 VM initialization arguments */
    JavaVMOption* options = new JavaVMOption[1];
    options[0].optionString = "-Djava.class.path=/home/tomaskrulis/.m2/repository/org/clojure/spec.alpha/0.2.194/spec.alpha-0.2.194.jar:/home/tomaskrulis/.m2/repository/org/clojure/clojure/1.10.2/clojure-1.10.2.jar";
    vm_args.version = JNI_VERSION_1_6;
    vm_args.nOptions = 1;
    vm_args.options = options;
    vm_args.ignoreUnrecognized = false;
    /* load and initialize a Java VM, return a JNI interface
     * pointer in env */
    JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);
    delete options;

    jclass Clojure = env->FindClass("clojure/java/api/Clojure");
    jmethodID var = env->GetStaticMethodID(Clojure, "var", "(Ljava/lang/Object;Ljava/lang/Object;)Lclojure/lang/IFn;");
    jobject load_string = env->CallStaticObjectMethod(Clojure, var, env->NewStringUTF("clojure.core"), env->NewStringUTF("load-string"));
    jmethodID load_string_invoke = env->GetMethodID(env->GetObjectClass(load_string), "invoke", "(Ljava/lang/Object;)Ljava/lang/Object;");
    env->CallObjectMethod(load_string, load_string_invoke, env->NewStringUTF("(prn (+ 1 2 3 4 5))"));

    jvm->DestroyJavaVM();
    return 0;
}
