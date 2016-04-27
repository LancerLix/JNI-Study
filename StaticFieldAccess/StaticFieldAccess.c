#include "StaticFieldAccess.h"
#include "stdio.h"

JNIEXPORT void JNICALL Java_StaticFieldAccess_accessField
  (JNIEnv *env, jobject obj){

  jfieldID fid;
  jint si;
  jclass cls = (*env) -> GetObjectClass(env, obj);
  printf("In C:\n");
  fid = (*env) -> GetStaticFieldID(env, cls, "si", "I");

  if(fid == NULL){
	return;
  }

  si = (*env) -> GetStaticIntField(env, cls, fid);
  
  printf("StaticFieldAccess.si = %d\n", si);

  (*env) -> SetStaticIntField(env, cls, fid, 200);

 }