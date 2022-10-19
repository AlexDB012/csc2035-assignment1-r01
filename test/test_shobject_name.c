/******** DO NOT EDIT THIS FILE ********/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "test_shobject_name.h"
#include "../sim_config.h"
#include "../shobject_name.h"

int main(int argc, char** argv) {
    return munit_suite_main(&suite, NULL, argc, argv);
}

static bool valid_shobject_name(char* actual_label, 
    char* expected_label, char* name_buf) {
    
    char expected_name[MAX_NAME_SIZE];
    
    char* user = getenv("USER");
 
    if (!user) user = "anon";
    
    if (!actual_label || !actual_label[0])
        expected_label = "none";
               
    if (!expected_label)
        expected_label = actual_label;

    (void) snprintf(expected_name, MAX_NAME_SIZE, SHOBJ_NAME_FMT, 
        user, expected_label);   
    
    char* actual_name = shobject_name(actual_label, name_buf); 
    
    bool valid = strncmp(actual_name, expected_name, MAX_NAME_SIZE) == 0 
            && strnlen(actual_name, MAX_NAME_SIZE) < MAX_NAME_SIZE;
            
    if (name_buf) {
        valid = valid && actual_name == name_buf;
    } else {
        free(actual_name);
    }
    
    return valid;
}

MunitResult test_shobject_name_short(const MunitParameter params[], 
    void* fixture) {
    char buf[MAX_NAME_SIZE];
    assert_true(valid_shobject_name("test", NULL, buf));
        
    return MUNIT_OK;
}      

MunitResult test_shobject_name_empty(const MunitParameter params[], 
    void* fixture) {      
    char buf[MAX_NAME_SIZE];
    assert_true(valid_shobject_name("", NULL, buf));

    return MUNIT_OK;
}      

MunitResult test_shobject_name_char(const MunitParameter params[], 
    void* fixture) {      
    char buf[MAX_NAME_SIZE];
    assert_true(valid_shobject_name("a", NULL, buf));
        
    return MUNIT_OK;
}      

MunitResult test_shobject_name_long(const MunitParameter params[], 
    void* fixture) {      
    char buf[MAX_NAME_SIZE];
    char* user = getenv("USER");

    int user_len = strnlen(user, 9);
    int chars_left = MAX_NAME_SIZE - 1 - user_len - 10;
    
    char expected_label[chars_left + 1];
    
    int i;
    for (i = 0; i < chars_left + 1; i++)
        expected_label[i] = 'x';
    
    expected_label[i] = '\0';
    
    assert_true(valid_shobject_name( 
        "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
        "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx", 
        expected_label, buf));  
        
    return MUNIT_OK;
}  

MunitResult test_shobject_name_null(const MunitParameter params[], 
    void* fixture) {      
    char buf[MAX_NAME_SIZE];
    assert_true(valid_shobject_name(NULL, NULL, buf));
        
    return MUNIT_OK;
}      

MunitResult test_shobject_name_short_heap(const MunitParameter params[], 
    void* fixture) {
    assert_true(valid_shobject_name(NULL, "test", NULL));
        
    return MUNIT_OK;
}      

MunitResult test_shobject_name_empty_heap(const MunitParameter params[], 
    void* fixture) {      
    assert_true(valid_shobject_name(NULL, "", NULL));

    return MUNIT_OK;
}      

MunitResult test_shobject_name_char_heap(const MunitParameter params[], 
    void* fixture) {      
    assert_true(valid_shobject_name(NULL, "a", NULL));
        
    return MUNIT_OK;
}      

MunitResult test_shobject_name_long_heap(const MunitParameter params[], 
    void* fixture) {      
    char* user = getenv("USER");

    int user_len = strnlen(user, 9);
    int chars_left = MAX_NAME_SIZE - 1 - user_len - 10;
    
    char expected_label[chars_left + 1];
    
    int i;
    for (i = 0; i < chars_left + 1; i++)
        expected_label[i] = 'x';
    
    expected_label[i] = '\0';
    
    assert_true(valid_shobject_name(
        "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
        "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx", 
        expected_label, NULL));  
        
    return MUNIT_OK;
}  

MunitResult test_shobject_name_null_heap(const MunitParameter params[], 
    void* fixture) {      
    assert_true(valid_shobject_name(NULL, NULL, NULL));
        
    return MUNIT_OK;
}      


