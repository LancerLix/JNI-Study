#include "InstanceFieldAccess.h"
#include "stdio.h"
#include "string.h"

JNIEXPORT void JNICALL Java_InstanceFieldAccess_accessField
	(JNIEnv * env, jobject obj) {

	jfieldID fid;
	jstring jstr;
	const char *str;

	jclass cls = (*env) -> GetObjectClass(env, obj);
	printf("In C:\n");

	fid = (*env) -> GetFieldID(env, cls, "s", "Ljava/lang/String;");
	if (fid ==NULL){
		return;
	}

	jstr = (*env) -> GetObjectField(env, obj, fid);

	str = (*env) -> GetStringUTFChars(env, jstr, NULL);
	printf("c.s = \"%s\"\n", str);
	(*env) -> ReleaseStringUTFChars(env, jstr ,str);

	jstr = (*env) -> NewStringUTF(env, "123");
	if(jstr == NULL){
		return;
	}

	(*env) -> SetObjectField(env, obj, fid, jstr);
}