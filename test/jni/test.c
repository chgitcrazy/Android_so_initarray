/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <jni.h>
#include <android/log.h>
#include <sys/types.h>

void myinit(int argc, char **argv, char **envp) {
	__android_log_print(ANDROID_LOG_INFO, "tag", "init:%s",
			"hello init_array");
}

__attribute__((section(".init_array"))) typeof(myinit) *_myinit = myinit;

JNIEXPORT jstring JNICALL Java_com_example_test_MainActivity_test(JNIEnv *env,
		jclass clazz) {

	return (*env)->NewStringUTF(env, "hello world returned.");
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    int result = -1;
    JNIEnv* env = NULL;
	__android_log_print(ANDROID_LOG_INFO, "tag", "jni_onload:%s",
				"hello jni_onload");

	if ((*vm)->GetEnv(vm, (void**) &env, JNI_VERSION_1_4) != JNI_OK) {
		return -1;
	}
	/* success -- return valid version number */
	result = JNI_VERSION_1_4;
	return result;
}

