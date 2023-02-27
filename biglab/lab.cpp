#include "MultithreadMethod.h" 
#include <jni.h>
#include <fstream> #include <string> #include <omp.h>

using namespace std;

JNIEXPORT jint JNICALL Java_MultithreadMethod_multithreadMethod (JNIEnv *, jclass, jint number) 
{
ofstream fout; fout.open("results.txt");
 #pragma omp parallel for
for(long i = 0; i < number; i++) 
{
 string temp;
if(i % 3 == 0) 
{
temp += "Fizz";
}
if(i % 5 == 0) 
{
temp += "Buzz";
}
if(temp.length() > 0) 
{
temp += "\t" + to_string(i) + "\n"; fout << temp;
}
}
fout.close(); return 0;
}
