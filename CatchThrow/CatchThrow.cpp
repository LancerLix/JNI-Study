#include "CatchThrow.h"
JNIEXPORT void JNICALL Java_CatchThrow_doit
	(JNIEnv *env, jobject obj){

	jthrowable exc;
	jclass cls = (env) -> GetObjectClass(obj);
	jmethodID mid = (env) -> GetMethodID(cls, "callback", "()V");
	if(mid == NULL){
		return;
	}

	(env) -> CallVoidMethod(obj, mid);
	exc = (env) -> ExceptionOccurred();
	if(exc){
		jclass newExcCls;
		(env) -> ExceptionDescribe();
		(env) -> ExceptionClear();

		newExcCls = (env) -> FindClass("Ljava/lang/IllegalArgumentException;");
		if(newExcCls == NULL){
			return;
		}

		(env) -> ThrowNew(newExcCls, "throw from C code");
	}
}