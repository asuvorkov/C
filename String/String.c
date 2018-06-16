#include "String.h"
#include <stdlib.h>


unsigned int strSize(char* str){
    sizetype size = 1;
    int i;
    for (i = 0; str[i] != '\0'; i++) {
        size++;
    }
    return size;
}

String mkStringFromChars(_char* str){
    String result = mkStringForLength(strSize(str));
    int x;
    for (x = 0; x <= result.length ; x++) {
        result.data[x] = str[x];
    }
    return result;
}

String mkStringForLength(sizetype l){
    String result;
    result.length = l;
    result.data = malloc((result.length + 1) * sizeof(char));
    result.data[result.length] = '\0';
    return result;
}

void strDelete(String this){
   free(this.data);
}

String strFromBool(bool b){
    if (b){
        return mkStringFromChars("true");
    } else{
        return mkStringFromChars("false");
    }
}
sizetype getIntLength(int i){
    sizetype len;
    for (len = 0; i % 10 > 0; i /= 10, ++len);
    return len;
}
String strFromInt(int i){
    sizetype strSize = getIntLength(i);
    String strObj = mkStringForLength(strSize);
    snprintf(strObj.data, strSize+1, "%d", i);
    return strObj;
}

void strPrintLn(String this){
    printf("length=%d;data=%s\n", this.length, this.data);
} 

String strAppend(String this,String that){
    String result = mkStringForLength(this.length + that.length);
    int x;
    for (x = 0; x <= this.length + that.length ; x++) {
        if (x < this.length){
            if (this.data[x] == '\0'){
                continue;
            }
            result.data[x] = this.data[x];
        } else{
            result.data[x - 1] = that.data[x - this.length];
        }
    }
    return result;
}

String strAppendInt(String this,int i){
    String that = strFromInt(i);
    return strAppend(this, that);
}

String strReverse(String this){
    String result = mkStringForLength(this.length);
    int x;
    int i = 0;
    for (x = this.length - 2; x > -1 ; x--) {
        result.data[i] = this.data[x];
        i++;
    }
    result.data[i] = '\0';
    return result;
}

String strMap(String this,_char f(_char)){
    String result = mkStringForLength(this.length);
    int x;
    for (x = 0; x <= result.length ; x++) {
        result.data[x] = f(this.data[x]);
    }
    return result;
}

String strToLowerCase(String this){
    String result = mkStringForLength(this.length);
    int x;
    for (x = 0; x <= result.length ; x++) {
        if (this.data[x] > 64 && this.data[x] < 91){
            result.data[x] = (char)((int)this.data[x] + 32);
        } else{
            result.data[x] = this.data[x];
        }
    }
    return result;
}

String strToUpperCase(String this){
    String result = mkStringForLength(this.length);
    int x;
    for (x = 0; x <= result.length ; x++) {
        if (this.data[x] > 96 && this.data[x] < 123){
            result.data[x] = (char)((int)this.data[x] - 32);
        } else{
            result.data[x] = this.data[x];
        }
    }
    return result;
}

String strSubstring(String this,sizetype from, sizetype to){
    sizetype newLen = to - from + 1;
    String subString = mkStringForLength(newLen);
    int begin = 0;
    int i;
    for (i = from; i <= to; i++)
        subString.data[begin++] = this.data[i];
    return subString;
}

bool issspace(unsigned char c){
    return c == ' ' || c == '\n' || c == '\t';
}

String strTrim(String this){
    char *end, *str;
    str = this.data;
    String trimmedString = mkStringForLength(this.length);
    while (issspace((unsigned char)*str)) str++;

    if (*str == 0)
        return this;
    end = str + trimmedString.length - 1;
    while (end > str && issspace((unsigned char)*end)) end--;

    *(end + 1) = 0;
    trimmedString.data = str;
    return trimmedString;
}

Ord strCompare(String this,String that){
    int i;
    for (i = 0; ; i++)
    {
        if (this.data[i] != that.data[i])
        {
            return this.data[i] < that.data[i] ? 0 : 2;
        }

        if (this.data[i] == '\0')
        {
            return 1;
        }
    }
}

bool strStartsWith(String this,String prefix){
    int x;
    for (x = 0; x <= prefix.length - 2; x++) {
        if (this.data[x] != prefix.data[x]){
            return false;
        }
    }
    return true;
}


bool strEndsWith(String this,String suffix){
    int x = this.length - 2;
    int i;
    for (i = suffix.length - 2; i >= 0; i--) {
        if (this.data[x] != suffix.data[i]){
            return false;
        }
        x--;
    }
    return true;
}

String strReplace(String this,_char oldChar, _char newChar){
    String result = mkStringForLength(this.length);
    int i;
    for (i = 0; i < result.length - 1; i++) {
        if (this.data[i] == oldChar){
            result.data[i] = newChar;
        } else{
            result.data[i] = this.data[i];
        }
    }
    result.data[i] = '\0';
    return result;
}

