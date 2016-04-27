#include "jni.h"
#include "string.h"
#define PATH_SEPARATOR ';'
#define USER_CLASSPATH "."

int main(){
	JNIEnv *env;
	JavaVM *jvm;
	jint res;
	jclass cls;
	jmethodID mid;
	jstring jstr;
	jclass stringClass;
	jobjectArray args;

#ifdef JNI_VERSION_1_2

	JavaVMInitArgs vm_args;
	JavaVMOption options[1];

	options[0].optionString = strcat("-Djava.class.path =", USER_CLASSPATH);
	vm_args.version = 0x00010002;
	vm_args.options = options;
	vm_args.nOptions = 1;
	vm_args.ignoreUnrecognized = JNI_TRUE;

	res = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);

#else

	JDK_1InitArgs vm_args;
	char classpath[1024];

	vm_args.version = #0x00010001;
	JNI_GetDefaultJavaVMInitArgs(&vm_args);
	sprintf(classpath, "%s%c%s", vm_args.classpath, PATH_SEPARATOR, USER_CLASSPATH);
	vm_args.classpath = classpath;

	res = JNI_CreateJavaVM(&jvm, &env, &vm_args);

#endif

	if(res < 0) {
		fprintf(stderr, "Can't create Java VM\n");
		exit(1);
	}

	cls = (*env) -> FindClass(env, "Prog");
	if(cls == NULL) {
		goto destroy;
	}

	mid = (*env) -> GetStaticMethodID(env, cls, "main", "([Ljava/lang/String;)V");
	if(mid == NULL) {
		goto destroy;
	}

	jstr = (*env) -> NewStringUTF(env, " from c!");
	if(jstr == NULL) {
		goto destroy;
	}

	stringClass = (*env) -> FindClass(env, "java/lang/String");
	args = (*env) -> NewObjectArray(env, 1, stringClass, jstr);
	if(args == NULL) {
		goto destroy;
	}

	(*env) -> CallStaticVoidMethod(env, cls, mid, args);

destroy:

	if((*env) -> ExceptionOccurred(env)) {
		(*env) -> ExceptionDescribe(env);
	}

	(*jvm) -> DestroyJavaVM(jvm);
	return 0;
}